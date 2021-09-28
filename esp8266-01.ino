#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
#define pir 0
const char* ssid="Kiril";
const char* password="kiril12345";
bool pir_val = false;
String Website,data,XML,Javascript;

void javascriptContent(){
    Javascript ="<script>\n";
    Javascript+="var xmlHttp=createXmlHttpObject();\n";
    Javascript+="var number=0;\n";
    Javascript+="var months = ['January','February','March','April','May','June','July','August','September','October','November','December'];\n";
    Javascript+="if(localStorage.getItem('number')!=null){\n";
    Javascript+="\tnumber=localStorage.getItem('number');\n";
    Javascript+="}\n";
    Javascript+="function start(){\n";
    Javascript+="\tdata();\n";
    Javascript+="\tprocess();\n";
    Javascript+="}\n";
    Javascript+="function data(){\n";
    Javascript+="\tfor(var i=0;i<number;i++){\n";
    Javascript+="\t\tvar date = localStorage.getItem(i);\n";
    Javascript+="\t\t\tif(date!=null){\n";
    Javascript+="\t\t\t\tdate = date.split(' ');\n";
    Javascript+="\t\t\t\tvar table_Ref = document.getElementsByTagName('tbody')[0];\n";
    Javascript+="\t\t\t\tvar row = table_Ref.insertRow(table_Ref.rows.length);\n";
    Javascript+="\t\t\t\tvar cell0 = row.insertCell(0);\n";
    Javascript+="\t\t\t\tvar cell1 = row.insertCell(1);\n";
    Javascript+="\t\t\t\tvar cell2 = row.insertCell(2);\n";
    Javascript+="\t\t\t\tvar cell3 = row.insertCell(3);\n";
    Javascript+="\t\t\t\tvar cell4 = row.insertCell(4);\n";
    Javascript+="\t\t\t\tvar cell5 = row.insertCell(5);\n";
    Javascript+="\t\t\t\tcell0.innerHTML = date[0];\n";
    Javascript+="\t\t\t\tcell1.innerHTML = date[1];\n";
    Javascript+="\t\t\t\tcell2.innerHTML = date[2];\n";
    Javascript+="\t\t\t\tcell3.innerHTML = date[3];\n";
    Javascript+="\t\t\t\tcell4.innerHTML = date[4];\n";
    Javascript+="\t\t\t\tcell5.innerHTML = date[5];\n";
    Javascript+="\t\t\t}\n";
    Javascript+="\t\t}\n";
    Javascript+="}\n";
    Javascript+="function createXmlHttpObject(){\n";
    Javascript+="\tif(window.XMLHttpRequest){\n";
    Javascript+="\t\txmlHttp=new XMLHttpRequest();\n";
    Javascript+="\t}else{\n";
    Javascript+="\t\txmlHttp=new ActiveXObject('Microsoft.XMLHTTP');\n";
    Javascript+="\t}\n";
    Javascript+="\treturn xmlHttp;\n";
    Javascript+="}\n";
    Javascript+="function saveNumber(){\n";
    Javascript+="\tlocalStorage.setItem('number',number);\n";
    Javascript+="}\n";
    Javascript+="function response(){\n";
    Javascript+="\txmlResponse=xmlHttp.responseXML;\n";
    Javascript+="\tif(xmlResponse==null)return;\n";
    Javascript+="\txmldoc = xmlResponse.getElementsByTagName('data');\n";
    Javascript+="\tmessage = xmldoc[0].firstChild.nodeValue;\n";
    Javascript+="\tif(message=='1'){\n";
    Javascript+="\t\tvar table_Ref = document.getElementsByTagName('tbody')[0];\n";
    Javascript+="\t\tvar row = table_Ref.insertRow(table_Ref.rows.length);\n";
    Javascript+="\t\tvar d = new Date();\n";
    Javascript+="\t\tvar year = d.getFullYear();\n";
    Javascript+="\t\tvar month = months[d.getMonth()];\n";
    Javascript+="\t\tvar day = d.getDate();\n";
    Javascript+="\t\tvar hour = d.getHours();\n";
    Javascript+="\t\tvar minutes = d.getMinutes();\n";
    Javascript+="\t\tvar seconds = d.getSeconds();\n";
    Javascript+="\t\tvar cell0 = row.insertCell(0);\n";
    Javascript+="\t\tvar cell1 = row.insertCell(1);\n";
    Javascript+="\t\tvar cell2 = row.insertCell(2);\n";
    Javascript+="\t\tvar cell3 = row.insertCell(3);\n";
    Javascript+="\t\tvar cell4 = row.insertCell(4);\n";
    Javascript+="\t\tvar cell5 = row.insertCell(5);\n";
    Javascript+="\t\tcell0.innerHTML = year;\n";
    Javascript+="\t\tcell1.innerHTML = month;\n";
    Javascript+="\t\tcell2.innerHTML = day;\n";
    Javascript+="\t\tcell3.innerHTML = hour;\n";
    Javascript+="\t\tcell4.innerHTML = minutes;\n";
    Javascript+="\t\tcell5.innerHTML = seconds;\n";
    Javascript+="\t\tlocalStorage.setItem(String(number),year+' '+month+' '+day+' '+hour+' '+minutes+' '+seconds);;\n";
    Javascript+="\t\tnumber++;\n";
    Javascript+="\t}\n";
    Javascript+="}\n";
    Javascript+="function process(){\n";
    Javascript+="\txmlHttp.open('PUT','xml',true);\n";
    Javascript+="\txmlHttp.onreadystatechange=response;\n";
    Javascript+="\txmlHttp.send(null);\n";
    Javascript+="\tsetTimeout('process()',2500);\n";
    Javascript+="}\n";
    Javascript+="</script>\n";
}

void WebsiteContent(){
    javascriptContent();
    Website="<html>\n";
    Website+="<style>\n";
    Website+=".content-table{\n";
    Website+="\tborder-collapse: collapse;\n";
    Website+="\tmargin:25px 0;\n";
    Website+="\tfont-size: 0.9em;\n";
    Website+="\tmin-width: 400px;\n";
    Website+="\tborder-radius: 5px 5px 0 0;\n";
    Website+="\toverflow: hidden;\n";
    Website+="}\n";
    Website+=".content-table thead tr{\n";
    Website+="\tbackground-color: #00D1FF;\n";
    Website+="\tcolor: #FFFFFF;\n";
    Website+="\ttext-align: left;\n";
    Website+="\tfont-weight: bold;\n";
    Website+="}\n";
    Website+=".content-table th .content-table td{\n";
    Website+="\tpadding: 12px 15px;\n";
    Website+="}\n";
    Website+=".content-table tbody tr{\n";
    Website+="\tborder-bottom: 1px solid #DDDDDD;\n";
    Website+="}\n";
    Website+=".content-table tbody tr:nth-of-type(even){\n";
    Website+="\tbackground-color: #F3F3F3;\n";
    Website+="}\n";
    Website+="</style>\n";
    Website+=Javascript;
    Website+="<body onload='start()' onunload='saveNumber()'>";
    Website+="<table class='content-table'>";
    Website+="<thead>";
    Website+="<th>";
    Website+="Year";
    Website+="</th>";
    Website+="<th>";
    Website+="Month";
    Website+="</th>";
    Website+="<th>";
    Website+="Day";
    Website+="</th>";
    Website+="<th>";
    Website+="Hour";
    Website+="</th>";
    Website+="<th>";
    Website+="Minute";
    Website+="</th>";
    Website+="<th>";
    Website+="Second";
    Website+="</th>";
    Website+="</thead>";
    Website+="<tbody>";
    Website+="</tbody>";
    Website+="</table>";
    Website+="</body>";
    server.send(200,"text/html",Website);
}
void XMLcontent(){
  XML="<?xml version='1.0'?>";
  XML+="<data>";
  XML+=pir_val;
  XML+="</data>";
  server.send(200,"text/xml",XML);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(pir,INPUT);
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)delay(500);
  WiFi.mode(WIFI_STA);
  server.on("/",WebsiteContent);
  server.on("/xml",XMLcontent);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  pir_val = false;
  if(digitalRead(pir) == HIGH){
    pir_val = true;
  }
}
