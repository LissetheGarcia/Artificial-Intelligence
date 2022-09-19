//=========================================
//HTML + CSS + JavaScript codes for webpage
//=========================================
const char webpageCode[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>GPS Location</title>
   <script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
   <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
   <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>

    <link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
    <style>html{font-size:17px}body{font-family:"Open Sans",Helvetica,Arial,sans-serif;overflow-x:hidden}body{background-image:url(https://i.ibb.co/QXzJDyS/carretera-en-otono-2560x1440-xtrafondos-com.jpg);background-size:cover;background-repeat:no-repeat;background-position:center;background-attachment:fixed;padding-left:50px;padding-right:50px}.bg02{background-image:url(https://i.ibb.co/QXzJDyS/carretera-en-otono-2560x1440-xtrafondos-com.jpg)}a{transition:all .3s ease}a:focus,a:hover{text-decoration:none}.navbar-brand{display:flex;align-items:center}.tm-site-icon{color:#656565}.tm-site-title{display:inline-block;text-transform:uppercase;font-size:2rem;margin-left:1rem;color:rgba(40,57,101,.9);letter-spacing:1px}.navbar{height:100px;padding-left:20px;padding-right:20px;margin-top:50px}.tm-logout-icon{font-size:1.5em}.tm-bg-black{background-color:rgba(0,0,0,.5)}.tm-mt-big{margin-top:70px}.tm-mt-small{margin-top:20px}.tm-block{padding:50px 45px}.tm-block-title{font-size:1.4rem;color:rgba(40,57,101,.9);margin-bottom:30px}.navbar-light .navbar-nav .nav-link{color:#fff}.dropdown-item,.navbar-light .navbar-nav .nav-link{padding:15px 20px}.navbar-light .navbar-nav .active>.nav-link,.navbar-light .navbar-nav .nav-link.active,.navbar-light .navbar-nav .nav-link.show,.navbar-light .navbar-nav .show>.nav-link,.navbar-light .navbar-nav a:hover{background-color:rgba(40,57,101,.9)}.nav-item{margin-right:30px}.nav-item:last-child{margin-right:0}.tm-content-row{justify-content:space-between;margin-left:-20px;margin-right:-20px}.tm-col{padding-left:20px;padding-right:20px;margin-bottom:50px}.tm-col-big{width:39%}.tm-col-small{width:21.95%}.tm-link-black{color:#000}.tm-link-black:focus,.tm-link-black:hover{color:#0266c4}ol{margin-bottom:0}.tm-list-group{counter-reset:myOrderedListItemsCounter;padding-left:0}.tm-list-group>li{list-style-type:none;position:relative;cursor:pointer;transition:all .3s ease;padding:8px}.tm-list-group-pad-big>li{padding:20px}.tm-list-group>li:hover{color:#0266c4}.tm-list-group-alternate-color>li:nth-child(odd){background-color:#e6e6e6}.tm-list-group>li:before{counter-increment:myOrderedListItemsCounter;content:counter(myOrderedListItemsCounter) ".";margin-right:.5em}.tm-list{padding-left:30px}.tm-list>li{margin-bottom:20px}.form-control{margin-bottom:23px;padding:19px 18px;border-radius:0;height:50px}label{margin-bottom:18px}.btn{border-radius:0;padding:13px 28px;transition:all .2s ease;max-width:100%}.btn-small{padding:10px 24px}.btn-primary{background-color:transparent;color:#000;border-color:#999}.btn-primary:active,.btn-primary:hover,.btn-primary:not(:disabled):not(.disabled).active,.btn-primary:not(:disabled):not(.disabled):active,.show>.btn-primary.dropdown-toggle{color:#000;background-color:#cdd4da;border-color:#999}.btn-danger{color:#9f1321;background-color:transparent;border-color:#9f1321}.btn-danger:hover{color:#9f1321;background-color:rgba(159,19,32,.27);border-color:#9f1321}.custom-file-input{cursor:pointer}.custom-file-label{border-radius:0}.tm-btn-right{text-align:right}.table td,.table th{padding:20px 24px}.table-hover tbody tr:hover{background-color:#fff;color:#3aabd0}.tm-bg-gray{background-color:rgba(0,0,0,.05)}.tm-table-striped-even.table-striped tbody tr:nth-of-type(even){background-color:rgba(0,0,0,.05)}.tm-table-striped-even.table-striped tbody tr:nth-of-type(odd){background-color:#fff}.tm-table-mt{margin-top:66px}.page-item:first-child .page-link{border-top-left-radius:0;border-bottom-left-radius:0}.page-item:last-child .page-link{border-top-right-radius:0;border-bottom-right-radius:0}.page-link,.tm-dots{padding:12px 18px}.page-link,.page-link:hover{color:#000}.page-item{margin-right:18px}.page-item:last-child{margin-right:0}.page-item.active .page-link{background-color:#e9ecef;border-color:#dee2e6;color:#000}.tm-pagination{justify-content:flex-end}.tm-pagination-label{padding-bottom:15px;padding-right:15px;display:inline-block}.tm-table-actions-row{display:flex;justify-content:space-between}.tm-table-actions-col-right{text-align:right}input[type=checkbox]{cursor:pointer;-webkit-appearance:none;appearance:none;border:1px solid #000;box-sizing:border-box;position:relative;box-sizing:content-box;width:24px;height:24px;transition:all .1s linear}input[type=checkbox]:checked{background-color:#9f1321}input[type=checkbox]:focus{outline:0 none;box-shadow:none}.tm-trash-icon{color:#6e6c6c;cursor:pointer}.tm-trash-icon:hover{color:#9f1321}.tm-trash-icon-cell{width:15px}footer{margin-bottom:35px}.custom-select{height:50px;border-radius:0}.tm-product-img-dummy{max-width:100%;width:240px;height:240px;border:1px solid #ccc;display:flex;align-items:center;justify-content:center;color:#c8c8c8}.tm-login-col{max-width:600px}@media (min-width:992px){.navbar-expand-lg .navbar-nav .nav-link{padding:15px 20px}}@media (min-width:1200px){.container{max-width:1630px}}@media (max-width:1275px) and (min-width:1200px){.nav-item{margin-right:15px}}@media (max-width:1350px) and (min-width:1200px){.tm-table-actions-row{display:block}.tm-table-actions-col-right{margin-top:30px}}@media (max-width:1350px){.nav-item{margin-right:1px}}@media (max-width:1199px){.tm-col-big,.tm-col-small{width:49.65%}.navbar-collapse{background:#fff;padding:15px;box-shadow:rgba(108,117,125,.27) 0 1px 1px 0;position:absolute;top:77px;right:20px;width:245px;z-index:1000}.navbar-nav .nav-link{padding-right:15px;padding-left:15px}.nav-item{margin-right:0}}@media (max-width:991px){.tm-col-big,.tm-col-small{width:100%;min-height:383px;height:auto}.tm-block{padding:30px}.tm-table-actions-row{display:block}.tm-table-actions-col-right{text-align:left;margin-top:30px}.tm-edit-product-row{flex-direction:column-reverse}}@media (max-width:633px){.pagination{flex-wrap:wrap}.tm-pagination{justify-content:flex-start}.tm-pagination-label{display:inline-block;margin-right:0}.page-item{margin-top:10px}}@media (max-width:574px){.navbar-collapse{top:70px}.tm-btn-right{text-align:left;margin-top:20px}.navbar{margin-top:30px;height:auto}body{padding-left:15px;padding-right:15px}.tm-site-title{font-size:1.4rem;margin-left:7px}.tm-site-icon{font-size:2em}}@media (max-width:480px){.tm-mt-big{margin-top:45px}}@media (max-width:424px){.navbar-collapse{top:107px}}</style>  
</head>

<body id="reportsPage" class="bg02">
    <div class="" id="home">
        <div class="container">
            <div class="row">
                <div class="col-12">
                    <nav class="navbar navbar-expand-xl navbar-light bg-light">
                        <a class="navbar-brand" href="index.html">
                            <i class="fas fa-3x fa-tachometer-alt tm-site-icon"></i>
                            <h1 class="tm-site-title mb-0">Dashboard</h1>
                        </a>
                        <button class="navbar-toggler ml-auto mr-0" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent"
                            aria-expanded="false" aria-label="Toggle navigation">
                            <span class="navbar-toggler-icon"></span>
                        </button>

                        <div class="collapse navbar-collapse" id="navbarSupportedContent">
                            <ul class="navbar-nav mx-auto">
                                <li class="nav-item active">
                                    <a class="nav-link" href="index.html" style="color:#fff">Transporte
                                        <span class="sr-only">(current)</span>
                                    </a>
                                </li>            
                            </ul>
                        </div>
                    </nav>
                </div>
            </div>
            <!-- row -->
            <div class="row tm-content-row tm-mt-big">
                <div class="col-xl-8 col-lg-12 tm-md-12 tm-sm-12 tm-col">
                    <div class="bg-white tm-block h-100">
                        <div class="row">
                            <div class="col-md-8 col-sm-12">
                                <h2 class="tm-block-title d-inline-block">Localización del Vehículo</h2>
                            </div>
                        </div>
                        <div class="mapouter"><div class="gmap_canvas"><iframe width="600" height="500" id="gmap_canvas_frame" name="gmap_canvas" src="https://maps.google.com/maps?q=2880%20Broadway,%20New%20York&t=&z=13&ie=UTF8&iwloc=&output=embed" frameborder="0" scrolling="no" marginheight="0" marginwidth="0"></iframe><a href="https://123movies-to.org">123 movies</a><br><style>.mapouter{position:relative;text-align:right;height:500px;width:600px;}</style><a href="https://www.embedgooglemap.net">embedding google map in web page</a><style>.gmap_canvas {overflow:hidden;background:none!important;height:500px;width:600px;}</style></div></div>
                        <div class="tm-table-mt tm-table-actions-row">
                            <div class="tm-table-actions-col-left">
                            </div>
                            <div class="tm-table-actions-col-right">
                            </div>
                        </div>
                    </div>
                </div>

                <div class="col-xl-4 col-lg-12 tm-md-12 tm-sm-12 tm-col">
                    <div class="bg-white tm-block h-100">
                        <h1 class="tm-block-title d-inline-block">Información de la localización</h1>
                        <div  class="latlong-form" style="padding-top: 10px;">
                          <div class="group">
                           <label for="longitud" class="label text-uppercase">Longitud:</label>
                           <span id="LONGValue">0</span>
                         </div>
                         <div class="group">
                           <label for="latitud" class="label  text-uppercase">Latitud:</label>
                           <span id="LATValue">0</span>
                         </div>
                         <div class="group">
                             <label for="velocidad" class="labe  text-uppercase">Velocidad</label>
                             <span id="VELValue">0</span>
                           </div>
                       </div>   
                <hr>
                <h1 class="tm-block-title d-inline-block">Enviar mensaje</h1>

                <form>
                    <div class="form-group">
                      <label for="contacto">Teléfono de contacto</label>
                      <input type="input" class="form-control" id="contacto" aria-describedby="emailHelp" placeholder="Teclea el Teléfono ">
                      <small id="contactoHelp" class="form-text text-muted">Pon el teléfono con formato internacional.</small>
                    </div>
                    <div class="form-group">
                      <label for="mensaje">Mensaje</label>
                      <textarea class="form-control" id="mensaje" placeholder="Tu mensaje"></textarea>
                    </div>
                    <button type="submit" class="btn btn-primary" id="btnEnviar">Enviar</button>
                  </form>
                    </div>
                </div>
            </div>
            <footer class="row tm-mt-small">
                <div class="col-12 font-weight-light">
                    <p class="d-inline-block tm-bg-black text-white py-2 px-4">
                        Copyright &copy; 2021 Admin GPS Dashboard . Lissethe García y Mariam Castaneda 
                    </p>
                </div>
            </footer>
        </div>
    </div>
      <!-- Scripts -->
<div class="alert">  
    <!-- Modal -->
<div class="modal fade" id="modalAlerts" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <h5 class="modal-title" id="exampleModalLabel"><span id="mensajeAlerta"></span></h5>
          <button type="button" class="close" data-dismiss="modal" aria-label="Close">
            <span aria-hidden="true">&times;</span>
          </button>
        </div>
        <div class="modal-body">
          El mensaje de ayuda se envió correctamente
        </div>
        <div class="modal-footer">
          <button type="button" class="btn btn-info" data-dismiss="modal">Ok</button>
        </div>
      </div>
    </div>
  </div>
</div>
      <script>
       $(document).ready(function() {
            getGPSValues();
            console.log("llame gps");
        });

        setInterval(function() 
        {
          getGPSValues();
        }, 5000); 

        setInterval(function() 
        {
          getAlert();
          console.log("llame alert");
        }, 10000);
        
        function getGPSValues() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
              if (this.readyState == 4 && this.status == 200) {
                var allValues = this.responseText;
                var myValues = allValues.split(";");
                
                var longitude = myValues[0];
                var latitude  = myValues[1];
                var velocidad  = myValues[2];
                                
                $("span#LONGValue").text(longitude);
                $("span#LATValue").text(latitude);
                $("span#VELValue").text(velocidad);
                var googlemapsURL = "https://maps.google.com/maps?q="+latitude+"," +longitude+ "&t=&z=13&ie=UTF8&iwloc=&output=embed";
                console.log(googlemapsURL);
                $("#gmap_canvas_frame").attr("src",googlemapsURL);
            
              }
            };
            xhttp.open("GET","readGPSValues", true);
            xhttp.send();
          }
          
         function getAlert() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
              if (this.readyState == 4 && this.status == 200) {
                var  numAlert= this.responseText;
                console.log("numAlert"+ numAlert)
                 if(numAlert == "1"){
                    $("#mensajeAlerta ").text("¡ALERTA ACCIDENTE!");
                    $("#modalAlerts").modal('show');
                 }else if(numAlert == "2"){
                    $("#mensajeAlerta ").text("¡ALERTA ROBO!");
                    $("#modalAlerts").modal('show');
                  }else if(numAlert == "3"){
                    $("#mensajeAlerta ").text("¡ALERTA EL CONDUCTOR ESTÁ CANSADO!");
                    $("#modalAlerts").modal('show');
                 }else if(numAlert == "4"){
                    $("#mensajeAlerta ").text("¡ALERTA PROBLEMA EN CARRETERA!");
                    $("#modalAlerts").modal('show');
                 }
              }
            };
            xhttp.open("GET","readAlert", true);
            xhttp.send();
          }
        </script>
</body>
</html>
)=====";
