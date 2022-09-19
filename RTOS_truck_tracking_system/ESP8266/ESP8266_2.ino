#include <ESP8266mDNS.h>

//FOR WEB PAGE
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFiMulti.h> 

#include <Wire.h>
#include <WiFiUdp.h>
#include "webpage.h";
#include "login.h";
// These define's must be placed at the beginning before #include 
// "ESP8266TimerInterrupt.h"
#define TIMER_INTERRUPT_DEBUG      1
#include "ESP8266TimerInterrupt.h"
#include "ESP8266_ISR_Timer.h"

//#include <Key.h>
#include <Keypad.h>


// ::: WiFi <<----------------------------------------------------------
ESP8266WiFiMulti wifiMulti;     // Create an instance of the 2
                                //    ESP8266WiFiMulti class, 
                                //    called 'wifiMulti'
ESP8266WebServer server(80);    // Create a webserver object that
                                //    listens for HTTP request on
                                //    port 80
//void serverRouting();

void initWiFi( void );           // function prototypes for HTTP 
                                //   handlers
void handleLogin();
void handleNotFound();
void handleWebpage();
void handleGPSValues();
void handleAlert();
void handleNotFound();

const char* http_username = "admin";
const char* http_password = "admin";

float longitude = 99.38;
float latitude = 19.16;
float speed_kph = 14.00;

//The content of messages recieved
#define MESSAGE_LENGTH 160
char messageRecieved[MESSAGE_LENGTH];
int messageRecievedIndex = 0;
char phone[16];
char datetime[24];

//int teclado = 1;

//String alert = "1";


// ::: I2C <<-----------------------------------------------------------
unsigned char uchAddress;       // slave address

void find_First_I2C_Module( void );

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
const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando
char hexaKeys[ROWS][COLS] ={ //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {0, 2, 14, 12}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {13, 15, 3, 1}; //Seleccionamos los pines en el arduino donde iran conectadas las columnas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

const int     led    =  2;
unsigned int  sw_actual, sw_past;
unsigned char address;
unsigned int  readLocation;
unsigned char alarm;

void task_list_1min( void );
void task_list_1s  ( void );
void task_list_4s( void );
void task_list_33s( void );
//------------------------------------------
//=================================================================
void  setup()
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
        wifiMulti.addAP( "Almendra", "aMRCEy3XbC" );   // add Wi-Fi 
                                //    networks you want to connect to
        initWiFi();    
        
    tasks:
        // up to 16 task handlers.......
        ITimer.attachInterruptInterval( 500, TimerHandler);
        
    app:
        sw_actual = 0; sw_past = 0;
        //pinMode( in_sw , INPUT  );
        //pinMode( sw_led, OUTPUT );
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

    task_1min:
        {
        if  ( ( usActiveTaskGroup ^ 0xEA60 ) == 0 )
            {
            // Activate tasks running every minute
            task_list_1min(); 
            }
        }
 
    task_1s:              
        {
        if  ( ( usActiveTaskGroup ^ 0x0400 ) == 0 )
            {
            // Toggle hearthbeat Built in LED    
            digitalWrite( led, !digitalRead( led ) );  
            }
        } 
    task_list_4s:
    {
      if  ( ( usActiveTaskGroup ^ 0x1000 ) == 0 )
            {
            // Activate tasks running every minute
            task_list_4s(); 
            }
    }
    task_list_33s:
    {
      if  ( ( usActiveTaskGroup ^ 0x8000 ) == 0 )
            {
            // Activate tasks running every minute
            task_list_33s(); 
            }
    }   
    exit:
        return;
    }    
// ::: Init section <<--------------------------------------------------
void initWiFi( void )
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
        
   server.on("/", handleLogin);
   server.on("/login", handleWebpage);
   server.on("/readGPSValues", handleGPSValues);
   server.on("/readAlert", handleAlert); 
   server.onNotFound(handleNotFound);

    server.begin();             // Actually start the server
    Serial.println("HTTP server started");
    }


// ---------------------------------------------------------------------
    void find_First_I2C_Module() 
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
    void handleAlert( void )
    {
    alarm = 0;
    
    // Alarm rules
    char key = customKeypad.getKey();

    if (key){
      Serial.println(key);}
    //else:
      //alarm = 0;
    if(key == 1)
    {
      Serial.println("Accidente externo para paso en carretera, evitar que otros traílers transiten esta ruta\n");
     }
    else if(key == 2)
    {
      Serial.println("¡Ayuda! Me quieren asaltar/robar\n");
    }
    else if(key == 3)
    {
      Serial.println("Por favor manda una ambulancia, acabo de tener un accidente\n");
    }
    else if(key == 4)
    {
      Serial.println("Estoy varado porque acabo de tener un inconveniente: se poncho una llanta, se me apagó el trailer etc.\n");
    }
    else if(key == 5)
    {
      Serial.println("Parare mi ruta para descansar y evitar accidentes directos o indirectos.\n");
    }
    //if  ( water    == 0    ) goto exit;
    //if  ( humidity <  0x80 ) goto exit;
    
    alarm = 1;
    Serial.println("Todo en orden\n");

    
    exit:
        return;
    }

    void txAlarmLevel( void )
    {
    Wire.beginTransmission( address ); // transmit to dev. <address>
    Wire.write( alarm );               // sends value byte  
    Wire.endTransmission();            // stop transmitting
    }    
    
    void task_list_4s( void )
    {
    handleAlert();
    txAlarmLevel();
    }

// ---------------------------------------------------------------------
    void readLocationGPS( void )
    {
    // request 1 bytes from slave
    Wire.requestFrom( ( uint8_t )address, ( uint8_t )1 );

    if  ( Wire.available() )        // read available data
    {
      readLocation = Wire.read();     // receive a data byte
    }
    }

    void task_list_33s( void )
    {
      readLocationGPS();
    }

// ::: Event handlers section <<----------------------------------------

    void ICACHE_RAM_ATTR 
TimerHandler( void )
    {
    usRippleCount++;
    }

void handleLogin()
{
  server.send(200,"text/html", loginCode);
}

void handleWebpage() 
{
   if(server.arg( "usernameLogin" ) == "admin" && server.arg( "passLogin"  == "admin" )){
        Serial.println("Log in Successful");
        return server.send(200, "text/html", webpageCode);
   }                  
}
void handleGPSValues() {
 String ALLValues = String(longitude,2) + ";" + String(latitude,2) + ";" + String(speed_kph,2);
 server.send(200, "text/plane", ALLValues); //Send Longitude value only to client ajax request
}

/*void handleAlert() {
 Serial.println("mi alerta es:");
 Serial.println(alert);
 server.send(200, "text/plane", alert); //Send Longitude value only to client ajax request
}*/
void handleNotFound(){
    // Send HTTP status 404 (Not Found) when there's no handler for the 
    // URI in the request
    server.send(404, "text/plain","404: Not found"); 
}

// *********************************************************************
// ::: END OF FILE <<---------------------------------------------------
// *********************************************************************
