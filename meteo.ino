#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <AM2320.h>
#include <ESP8266WiFi.h>

AM2320 th;
Adafruit_BMP085 bmp;

const char* ssid = "net-143";
const char* password = "atlm2346fglh2886bcer";

const char* server = "192.168.1.5";
const int porta=80;

WiFiClient client;

//WiFiServer server(80);
 

 
void setup() 
{
  Serial.begin(9600);
  //Wire.begin (4, 5);
  if (!bmp.begin()) 
  {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
    while (1) {}
  }
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
}
 
void loop() 
{

  th.Read();
  
  //Scrive sulla porta seriale i valori
  Serial.print("BMP180 -- Temperatura : ");
  Serial.print(bmp.readTemperature());
  Serial.print(" °C - Pressione : ");
  Serial.print(bmp.readPressure()/100);
  Serial.println(" hPascal");
  Serial.print("AM2302 -- Temperatura : ");
  Serial.print(th.t);
  Serial.print("°C - umidità : ");
  Serial.print(th.h);
  Serial.println("%");

  // si connette al server
  if (!client.connect(server, porta)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
  }


  // Stringa da inviare nel POST
  String PostData = "temp="+String(bmp.readTemperature())+"&pres="+String(bmp.readPressure())+"&umid="+String(th.h)+"&temp2="+String(th.t);

  // Crea chiamata POST
  client.println("POST / HTTP/1.1");
  client.println("Host: "+server);
  client.println("Cache-Control: no-cache");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(PostData.length());
  client.println();
  client.println(PostData);

  Serial.println("closing connection");
  client.stop();
 
  Serial.println();
  delay(5000);
}
