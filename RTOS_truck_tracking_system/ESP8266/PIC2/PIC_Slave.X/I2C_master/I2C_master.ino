#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
// These define's must be placed at the beginning before #include 
// "ESP8266TimerInterrupt.h"
#define TIMER_INTERRUPT_DEBUG      1
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"
#include <Wire.h>

// ::: I2C <<-----------------------------------------------------------
unsigned char uchAddress;       // slave address

void find_First_I2C_Module( void );

// ::: WiFi <<----------------------------------------------------------
ESP8266WiFiMulti wifiMulti;     // Create an instance of the 
                                //    ESP8266WiFiMulti class, 
                                //    called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that
                                //    listens for HTTP request on
                                //    port 80

void initWiFi( void );
void handleRoot();              // function prototypes for HTTP 
                                //   handlers
void handleLogin();
void handleNotFound();
void handleUser();

// ::: Timer <<---------------------------------------------------------
ESP8266Timer ITimer;
void ICACHE_RAM_ATTR TimerHandler( void ); 

// ::: uKaos <<---------------------------------------------------------
// This counter is the central part to the ukaos OS.
// Each group of tasks running on the same time slot are triggered
// by the change on sate of the corresponding bit of this counter. 

// Time slot by bit position:
//
//  Hi byte
//< 33.5s - 16.7s - 8.3s - 4.1s - 2.0s - 1.0s - 524.2ms - 262.1ms >
//  LO byte
//< 131.0ms - 65.5ms - 32.7ms - 16.3ms - 8.1ms - 4.9ms - 2.0ms - 1.0ms >
unsigned short usRippleCount = 0;

unsigned short usRipplePast  = 0;
unsigned short usActiveTaskGroup;

// ::: Application <<---------------------------------------------------
const int     led    =  2;
const int     in_sw  = 16;
const int     sw_led = 14;
unsigned int  sw_actual, sw_past;
unsigned char water;
unsigned char alarm;
unsigned int  humidity;
unsigned char address;

void task_list_32ms( void );
void task_list_1s  ( void );
void task_list_4s  ( void );

    void 
setup()
    {
    serial:
       Serial.begin( 115200 );
       while (!Serial);         // wait for serial monitor
   
    i2c:
       uchAddress = 0;
       Wire.begin( 4, 5 );
       find_First_I2C_Module();
       
    beat:
        pinMode( led, OUTPUT );
        digitalWrite( led, 0 );
       
    wifi:
        wifiMulti.addAP( "DARKNET", "CJih2wnXba" );   // add Wi-Fi 
                                //    networks you want to connect to
        initWiFi();    
        
    tasks:
        // up to 16 task handlers.......
        ITimer.attachInterruptInterval( 500, TimerHandler);
        
    app:
        water = 0; sw_actual = 0; sw_past = 0; humidity = 0; alarm = 0;
        pinMode( in_sw , INPUT  );
        pinMode( sw_led, OUTPUT );
    }

void loop() 
    {
    web_server:
        server.handleClient();
        
    // uKaos
    idle:
        {
        // Wait until a time slot passes
        if ( usRippleCount == usRipplePast ) goto exit;
        
        // Find active slot
        usActiveTaskGroup = usRippleCount;
        usActiveTaskGroup ^= usRipplePast;
        usActiveTaskGroup &= usRippleCount;
        
        usRipplePast = usRippleCount;
        }

    task_32ms:
        {
        if  ( ( usActiveTaskGroup ^ 0x0020 ) == 0 )
            {
            // Activate tasks running every 32ms
            task_list_32ms(); 
            }
        }
 
    task_500ms:              
        {
        if  ( ( usActiveTaskGroup ^ 0x0200 ) == 0 )
            {
            // Toggle hearthbeat Built in LED    
            digitalWrite( led, !digitalRead( led ) );  
            }
        }
        
    task_1s:
        {
        if  ( ( usActiveTaskGroup ^ 0x0400 ) == 0 )
            {
            // Activate tasks running each second
            task_list_1s(); 
            }
        }
        
    task_4s:
        {
        if  ( ( usActiveTaskGroup ^ 0x1000 ) == 0 )
            {
            // Activate tasks running each 4 seconds
            task_list_4s(); 
            }
        }
    
    exit:
        return;
    }

// ::: Init section <<--------------------------------------------------

    void
initWiFi( void )
    {
    Serial.println("Connecting ...");
    int i = 0;
    
    while (wifiMulti.run() != WL_CONNECTED) 
       { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and
         //   connect to the strongest of the networks above
       delay(250);
       Serial.print('.');
       }
    Serial.println('\n');
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());    // Tell us what network we're 
                                    // connected to
    Serial.print("IP address:\t");
    Serial.println(WiFi.localIP()); // Send the IP address of the 
                                    //    ESP8266 to the computer
    
    if (MDNS.begin("esp8266")) 
       {              // Start the mDNS responder for esp8266.local
       Serial.println("mDNS responder started");
       } 
    else 
       {
       Serial.println("Error setting up MDNS responder!");
       }
    
    server.on("/", HTTP_GET, handleRoot);        // Call the 
                                //    'handleRoot' function when a 
                                //    client requests URI "/"
    server.on("/login", HTTP_POST, handleLogin); // Call the 
                                //    'handleLogin' function when a POST
                                //    request is made to URI "/login"
    server.on("/user",HTTP_GET, handleUser );
    server.onNotFound(handleNotFound);           // When a client 
                                //    requests an unknown URI (i.e. 
                                //    something other than "/"), call
                                //    function "handleNotFound"
    
    server.begin();             // Actually start the server
    Serial.println("HTTP server started");
    }

// ---------------------------------------------------------------------
    void 
find_First_I2C_Module() 
    {
    byte error;
    
    Serial.println
        ( 
        "\n\nScan for I2C devices on port pair D4(SDA)and D5(SCL)" 
        )
        ;
    Serial.print( "Scanning (SDA : SCL) - D4 : D5 - " );
    
    for ( address = 1; address < 128; address++ )  
        {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission( address );
        error = Wire.endTransmission();
       
        if  ( error == 0 )
            {
            Serial.print( "I2C device found at address 0x" );
            if ( address < 16 ) Serial.print( "0" );
            Serial.print( address, HEX );
            Serial.println("  !");      
            uchAddress = address;
            
            break;
            } 
        } 
    if  ( address == 128 ) Serial.println("No I2C devices found");
    else Serial.println("**********************************\n");
    }

// ::: App. tasks section <<--------------------------------------------
    void
readSwitch( void )
    {
    sw_actual = digitalRead( in_sw );
    water     = sw_actual & sw_past;
    sw_past   = sw_actual;
    }
    
    void
echoSwitch( void )
    {
    digitalWrite( sw_led, water );
    }    
    
    void 
task_list_32ms( void )
    {
    readSwitch();
    echoSwitch();
    }

// ---------------------------------------------------------------------
    void
alarmLogic( void )
    {
    alarm = 0;
    
    // Alarm rules
    if  ( water    == 0    ) goto exit;
    if  ( humidity <  0x80 ) goto exit;
    
    alarm = 1;
    
    exit:
        return;
    }

    void
txAlarmLevel( void )
    {
    Wire.beginTransmission( address ); // transmit to dev. <address>
    Wire.write( alarm );               // sends value byte  
    Wire.endTransmission();            // stop transmitting
    }    
    
    void 
task_list_1s( void )
    {
    alarmLogic();
    txAlarmLevel();
    }

// ---------------------------------------------------------------------
    void
readHumidity( void )
    {
    // request 1 bytes from slave
    Wire.requestFrom( ( uint8_t )address, ( uint8_t )1 );

    if  ( Wire.available() )        // read available data
        {
        humidity = Wire.read();     // receive a data byte
        }
    }

    void 
task_list_4s( void )
    {
    readHumidity();
    }

// ::: Event handlers section <<----------------------------------------

    void ICACHE_RAM_ATTR 
TimerHandler( void )
    {
    usRippleCount++;
    }

    void 
handleRoot() 
    {                          
    // When URI / is requested, send a web page with a button to toggle 
    // the LED
    server.send
        (
        200, 
        "text/html", 
        "<form action=\"/login\" method=\"POST\">"
        "  <input type=\"text\" name=\"username\" "
           "placeholder=\"Username\">"
        "  </br>"
        "  <input type=\"password\" name=\"password\" "
           "placeholder=\"Password\">"
        "  </br>"
        "  <input type=\"submit\" value=\"Login\">"
        "</form>"
        "<p>Try 'Ulises Davalos' and 'pwd123' ...</p>"
        )
        ;
    }
    
    void 
handleLogin() 
    {                         // If a POST request is made to URI /login
    if  ( 
        ! server.hasArg("username")         || 
        ! server.hasArg("password")         || 
          server.arg   ("username") == NULL || 
          server.arg   ("password") == NULL
        ) 
        {
        // If the POST request doesn't have username and password data 
        // The request is invalid, so send HTTP status 400
        server.send(400, "text/plain", "400: Invalid Request");   
        return;
        }
    if  ( 
           server.arg( "username" ) == "Ulises Davalos" 
        && server.arg( "password" ) == "pwd123"
        ) 
        { // If both the username and the password are correct
        server.send
           (
           200, 
           "text/html", 
           "<h1>Welcome, " + server.arg("username") + "!</h1>"
           "<p>Login successful <a href=\"/user\">Go to ESP8266"
           " I/O!!!</a> </p>"
           )
           ;
        } 
    else 
        {
        // Username and password don't match            
        server.send(401, "text/plain", "401: Unauthorized");
        }
    }

    static char
response[ 200 ]
    ;
   
   void 
handleUser() 
    {                         
    // When URI / is requested, send a web page with a button to toggle 
    // the LED
    sprintf
       (
       response,
       "<p>Water Reserve status  = %d </p>"
       "<p>Humidity = %d </p>"
       "<hr>"
       "<p><a href=\"/\">Log out!</a></p>",
       digitalRead( in_sw ),
       255 - humidity
       )
       ;
    server.send
       (
       200, 
       "text/html",
       response
       )
       ;
    }
   
    void 
handleNotFound()
    {
    // Send HTTP status 404 (Not Found) when there's no handler for the 
    // URI in the request
    server.send
        (
        404, 
        "text/plain", 
        "404: Not found"
        )
        ; 
    }

// *********************************************************************
// ::: END OF FILE <<---------------------------------------------------
// *********************************************************************
