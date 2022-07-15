#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "Params";
const char* password = "sharmanPMP";


const char* serverName = "http://192.168.171.229:3000/home";


unsigned long lastTime = 0;
unsigned long timerDelay = 5000;


void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
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
   
  if ((millis() - lastTime) > timerDelay) 
  {
    if (WiFi.status() == WL_CONNECTED) 
    {
      WiFiClient client;
      HTTPClient http;

      http.begin(client, serverName);

      int Temperature = 10;int True_RH = 1;int F_Frequency_0 = 12;int soil_temp=34;int F_Frequency_1=123;int Bat_Val= 1;
      
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
