#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(80);
String jwt = "Insert JWT string here";

void setup() {
 
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  Serial.begin(115200);
  WiFi.begin("{ssid}", "{passcode}");  //Connect to the WiFi network
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
    delay(500);
    Serial.println("Waiting to connect…");
  }
 
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
 
 //Define the handling function for the config response
  server.on("/thing", []() {   
    String configThing = "{\
   \"name\": \"ESP8266\",\
   \"type\": \"thing\",\
   \"id\": \"ESP8266-01\",\
   \"description\": \"myESP8266\",\   
   \"properties\": {\
     \"Clock\": {\
       \"type\":  \"number\",\
       \"unit\":  \"Ticks\",\
       \"description\":  \"The millisec clock count\",\
       \"value\":  \"0\"\
    },\
     \"led\": {\
       \"type\":  \"boolean\",\
       \"description\":  \"The onboard LED\",\
       \"value\":  \"false\"\
    }\
  }\
}";
    server.send(200, "text/json", configThing);
  });
 
  // respond to setting LED on/off
  // attempts to set clock simply return current clock value
  server.on("/thing/set", []() {      //Define the handling function for the config response
    char respondThing[2048];
   
    if(server.arg("led")!= "") {
      if(server.arg("led")=="true" ) {
          digitalWrite(LED_BUILTIN, HIGH);
      } else {
          digitalWrite(LED_BUILTIN, LOW);
      }
      unsigned long currentMillis = millis();
      sprintf(respondThing, "%s{\"Clock\": %d}", hdr.c_str(), currentMillis);
    }

    if(server.arg("Clock")!= "") {
      unsigned long currentMillis = millis();
      sprintf(respondThing, "%s{\"Clock\": %d}", hdr.c_str(), currentMillis);
    }
    server.send(200, "text/json", respondThing); 
  });
 
  server.begin();                                       //Start the server
  Serial.println("Server listening");
 
}
 
void loop() {
 
  server.handleClient();         //Handling of incoming requests
 
}
