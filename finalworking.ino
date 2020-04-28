#include "SoftwareSerial.h"

//String servernew = "184.106.153.149";

String ssid ="Camimac";

String password="codefishacademy@123";
SoftwareSerial debug(6,7); // RX, TX
SoftwareSerial esp(6, 7);// RX, TX
#define IP "184.106.153.149" // ThingSpeak IP Address: 184.106.153.149
String GET = "GET /update?key=OH4FCUDMMEBRXUGY";

String data;
int value_temp;

int value_light;

int value_humid;
String server = "api.thinkspeak.com"; // www.example.com
String servernew = "api.thinkspeak.com"; // www.example.com

String uri = "yourURI";// our example is /esppost.php

int DHpin = 8;//sensor pin

byte dat [5];

String temp ,hum;

void setup() {

pinMode (DHpin, OUTPUT);

esp.begin(9600);

Serial.begin(9600);
debug.begin(9600);
Serial.println("Starting");
reset();

connectWifi();

}

//reset the esp8266 module

void reset() {

esp.println("AT+RST");
Serial.println("AT+RST");
delay(1000);

if(esp.find("OK") ) Serial.println("Module Reset");

}

//connect to your wifi network

void connectWifi() {
  
  delay(2000);
String cmd = "AT+CWJAP=\"" +ssid+"\",\"" + password + "\"";

esp.println(cmd);
Serial.println(cmd);
delay(4000);

if(esp.find("OK")) {

Serial.println("Connected!");

}

else {
Serial.println("Connecting again");
delay(10000);
connectWifi();

Serial.println("Cannot connect to wifi"); }

}



void loop () {

//start_test ();

// convert the bit data to string form

//hum = String(dat[0]);

//temp= String(dat[2]);

//data = "temperature=" + temp + "&humidity=" + hum;// data sent must be under this form //name1=value1&name2=value2.

//httppost();
//thingspeak();


  value_temp = 5.2;
  value_light = 4.8;
  value_humid = 11.6;
  String temp =String(value_temp);// turn integer to string
  String light= String(value_light);// turn integer to string
  String humid=String(value_humid);// turn integer to string
  updateTS(temp,light, humid);
  delay(3000); //
delay(1000);

}
void thingspeak(){
 
  float inputone=5.25;
  String value = String(inputone);
  
//http://api.thingspeak.com/update?key=API_KEY&field1=0
String getquery = "GET /update?key=OH4FCUDMMEBRXUGY&field1="+value ;
Serial.println(getquery);
esp.println("AT+CIPSTART=\"TCP\",\"" + servernew + "\",80");

if( esp.find("OK")) {

Serial.println("TCP connection ready");

} delay(1000);

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

esp.print(sendCmd);

esp.println(getquery.length() );

delay(500);

if(esp.find(">")) { Serial.println("Sending.."); esp.print(getquery);

if( esp.find("SEND OK")) { Serial.println("Packet sent");

while (esp.available()) {

String tmpResp = esp.readString();

Serial.println(tmpResp);
// close the connection

esp.println("AT+CIPCLOSE");

}

}}
}

void updateTS( String T, String L , String H)
{
  // ESP8266 Client
  String cmd = "AT+CIPSTART=\"TCP\",\"";// Setup TCP connection
  cmd += IP;
  cmd += "\",80";
  //Serial.println(cmd);
  Serial.println("cmd is :" +cmd);
  
  delay(2000);
  if( Serial.find( "Error" ) )
  {
    debug.print( "RECEIVED: Error\nExit1" );
    return;
  }

  cmd = GET + "&field1=" + T +"&field2="+ L + "&field3=" + H +"\r\n";
  Serial.print( "AT+CIPSEND=" );
  Serial.println( cmd.length() );
  if(Serial.find( ">" ) )
  {
    debug.print(">");
    debug.print(cmd);
    Serial.print(cmd);
  }
  else
  {
    Serial.println( "AT+CIPCLOSE" );//close TCP connection
  }
  if( Serial.find("OK") )
  {
    debug.println( "RECEIVED: OK" );
  }
  else
  {
    debug.println( "RECEIVED: Error\nExit2" );
  }
}

void httppost () {

esp.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");//start a TCP connection.

if( esp.find("OK")) {

Serial.println("TCP connection ready");

} delay(1000);

String postRequest =

"POST " + uri + " HTTP/1.0\r\n" +

"Host: " + server + "\r\n" +

"Accept: *" + "/" + "*\r\n" +

"Content-Length: " + data.length() + "\r\n" +

"Content-Type: application/x-www-form-urlencoded\r\n" +

"\r\n" + data;

String sendCmd = "AT+CIPSEND=";//determine the number of caracters to be sent.

esp.print(sendCmd);

esp.println(postRequest.length() );

delay(500);

if(esp.find(">")) { Serial.println("Sending.."); esp.print(postRequest);

if( esp.find("SEND OK")) { Serial.println("Packet sent");

while (esp.available()) {

String tmpResp = esp.readString();

Serial.println(tmpResp);

}

// close the connection

esp.println("AT+CIPCLOSE");

}

}}
