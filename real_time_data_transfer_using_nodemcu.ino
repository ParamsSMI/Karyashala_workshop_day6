#include <ESP8266WiFi.h>  
#include <ESP8266HTTPClient.h> // Library to easily make HTTP GET, POST and PUT requests to a web server.
#include <WiFiClient.h>

/*
   Nodemcu has 3 WIFI Modes
   1. STATION MODE : 
      Station (STA) mode is used to get the ESP8266 connected to a WiFi network established by an access point.
   2. SOFT-AP MODE :
      An access point (AP) is a device that provides access to Wi-Fi network to other devices (stations)
   3. STATION + AP MODE :
      ESP can operate in both soft-AP and Station mode so it can act as a node of a mesh network


     For more Documentation refer : https://nodemcu.readthedocs.io/en/release/modules/wifi/
*/
// WIFI credentails on which you want to connect your nodemcu
const char* ssid = "Params";  
const char* password = "sharmanPMP";

/* url of the server machine [ you can get the IP of the server by typing ipconfig command in your terminal, make sure that
  your machine and nodemcu both are on same network
*/

const char* serverName = "http://192.168.171.229:3000/home";


unsigned long lastTime = 0;
unsigned long timerDelay = 5000;  


void setup() {
 
  Serial.begin(115200); // Baudrateof 115200 (pulses/second)
  WiFi.begin(ssid, password);  // It will make your nodemcu in STATION MODE and connect to specified wifi network
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  
}

void loop() {
    /*
       we are sending sensor data from nodemcu to our server after every 5 seconds.
       millis() - Returns the number of milliseconds passed since the Arduino board began running
                  the current program.
       here, we need to send data after every 5 second,so to do that we have to keep track of every 5 second window
       somehow we can able to store that, last when we have send the data then after 5 second of that, we can send the data again.
       Now think!! 
    */
  if ((millis() - lastTime) > timerDelay) 
  {
    if (WiFi.status() == WL_CONNECTED) 
    {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);
      
      /* here, for demo purpose, we have not taken any sensor but you can connect any sensr to nodemcu and just take value in one variable */
      int Temperature = 10;
      int True_RH = 1;
      int F_Frequency_0 = 12;
      int soil_temp=34;
      int F_Frequency_1=123;
      int Bat_Val= 1;
      
      http.addHeader("Content-Type", "application/json");
      int httpResponseCode = http.POST("{ \"node_id\":22, \"temperature\":"  + String(Temperature)+ ",\"humidity\":" + String(True_RH) + ",\"LWS\":" + String(F_Frequency_0) + ",\"soil_temperature\":" + String(soil_temp) + ",\"soil_moisture\":" + String(F_Frequency_1) + ",\"battery_status\":" + String(Bat_Val) + "}");
      
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      http.end();
      
    }
    else {
      Serial.println("WiFi Disconnected"); 
    }
    lastTime = millis();
    Serial.println(lastTime);
  }

}
