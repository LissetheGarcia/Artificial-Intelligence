//=========================================
//HTML + CSS + JavaScript codes for login
//=========================================
const char loginCode[] PROGMEM =
R"=====(
<!DOCTYPE html>
<html>
<!------------------------------C S S--------------------------------->
<head>
    <style>
       body{
           margin:0;
            color:#6a6f8c;
            background:#c8c8c8;
            font:600 16px/18px 'Open Sans',sans-serif;
          }
          *,:after,:before{box-sizing:border-box}
          .clearfix:after,.clearfix:before{content:'';display:table}
          .clearfix:after{clear:both;display:block}
          a{color:inherit;text-decoration:none}
          
          .login-wrap{
            width:100%;
            margin:auto;
            max-width:525px;
            min-height:670px;
            position:relative;
            background:url(https://i.ibb.co/QXzJDyS/carretera-en-otono-2560x1440-xtrafondos-com.jpg) no-repeat center;
            box-shadow:0 12px 15px 0 rgba(0,0,0,.24),0 17px 50px 0 rgba(0,0,0,.19);
          }
          .login-html{
            width:100%;
            height:100%;
            position:absolute;
            padding:90px 70px 50px 70px;
            background:rgba(40,57,101,.9);
          }
          .login-html .sign-in-htm,
          .login-html .sign-up-htm{
            top:0;
            left:0;
            right:0;
            bottom:0;
            position:absolute;
            backface-visibility:hidden;
            transition:all .4s linear;
          }
          .login-html .sign-in,
          .login-html .sign-up,
          .form .group .check{
            display:none;
          }
          .login-html .tab,
          .form .group .label,
          .form .group .button{
            text-transform:uppercase;
          }
          .login-html .tab{
            font-size:22px;
            margin-right:15px;
            padding-bottom:5px;
            margin:0 15px 10px 0;
            display:inline-block;
            border-bottom:2px solid transparent;
          }
          .login-html .sign-in:checked + .tab,
          .login-html .sign-up:checked + .tab{
            color:#fff;
            border-color:#1161ee;
          }
          .form{
            min-height:345px;
            position:relative;
            perspective:1000px;
            transform-style:preserve-3d;
          }
          .form .group{
            margin-bottom:15px;
          }
          .form .group .label,
          .form .group .input,
          .form .group .button{
            width:100%;
            color:#fff;
            display:block;
          }
          .form .group .input,
          .form .group .button{
            border:none;
            padding:15px 20px;
            border-radius:25px;
            background:rgba(255,255,255,.1);
          }
          .form .group input[data-type="password"]{
            text-security:circle;
            -webkit-text-security:circle;
          }
          .form .group .label{
            color:#aaa;
            font-size:12px;
          }
          .form .group .button{
            background:#1161ee;
          }
          .form .group label .icon{
            width:15px;
            height:15px;
            border-radius:2px;
            position:relative;
            display:inline-block;
            background:rgba(255,255,255,.1);
          }
          .form .group label .icon:before,
          .form .group label .icon:after{
            content:'';
            width:10px;
            height:2px;
            background:#fff;
            position:absolute;
            transition:all .2s ease-in-out 0s;
          }
          .form .group label .icon:before{
            left:3px;
            width:5px;
            bottom:6px;
            transform:scale(0) rotate(0);
          }
          .form .group label .icon:after{
            top:6px;
            right:0;
            transform:scale(0) rotate(0);
          }
          .form .group .check:checked + label{
            color:#fff;
          }
          .form .group .check:checked + label .icon{
            background:#1161ee;
          }
          .form .group .check:checked + label .icon:before{
            transform:scale(1) rotate(45deg);
          }
          .form .group .check:checked + label .icon:after{
            transform:scale(1) rotate(-45deg);
          }
          .login-html .sign-in:checked + .tab + .sign-up + .tab + .form .sign-in-htm{
            transform:rotate(0);
          }
          .login-html .sign-up:checked + .tab + .form .sign-up-htm{
            transform:rotate(0);
          }
          
          .hr{
            height:2px;
            margin:60px 0 50px 0;
            background:rgba(255,255,255,.2);
          }
          .foot-lnk{
            text-align:center;
          }
    </style>
</head>
<!------------------------------H T M L--------------------------------->
<body>
<div class="login-wrap">
  <div class="login-html">
    <input id="tab-1" type="radio" name="tab" class="sign-in" checked><label for="tab-1" class="tab">Sign In</label>
    <div class="form">
      <div class="sign-in-htm">
      <form action="/login" method="POST" class="login-form" style="padding-top: 20px;">
        <div class="group">
          <label for="user" class="label">Username</label>
          <input id="user" type="text" class="input" name="usernameLogin">
        </div>
        <div class="group">
          <label for="pass" class="label">Password</label>
          <input id="pass" type="password" class="input" data-type="password" name="passLogin">
        </div>
        <div class="group">
          <input type="submit" class="button" value="Login">
        </div>
        </form>
        <div class="hr"></div>
      </div>
    </div>
  </div>
</div>
</body>
<script>
function getURLParameter(sParam)
{
var sPageURL = window.location.search.substring(1);
var sURLVariables = sPageURL.split('&');
for (var i = 0; i < sURLVariables.length; i++)
{
var sParameterName = sURLVariables[i].split('=');
if (sParameterName[0] == sParam)
{
return sParameterName[1];
}
}
}
if (getURLParameter("msg")) {
document.getElementById("message").innerText = decodeURI(getURLParameter("msg"));
}
</script>
</html>
)=====";
