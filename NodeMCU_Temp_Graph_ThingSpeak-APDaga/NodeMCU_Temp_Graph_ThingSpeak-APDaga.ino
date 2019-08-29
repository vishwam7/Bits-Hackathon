
#include <ESP8266WiFi.h>      // Import NodeMCU Libraries

const char* host = "api.thingspeak.com";              // Your cloud domain  
String ApiKey = "SUXRCOBGVZYS7BUR";                   // Change this key to your "Write API key"
String path = "/update?key=" + ApiKey + "&field1=";   // API Format


const char* ssid = "Zainab";            // Change this to your ssid_name (WiFi Name)
const char* pass = "znbtabbu20";         // Change this to your WiFi password

int sensor = A0;                         // Analog Input LM35 Output

float tempc;
float Digital_mVolt;
  

void setup(void){
  Serial.begin(115200);                 // PC Arduino Serial Monitor
  Serial.println("");
  
  WiFi.begin(ssid, pass);               // Func to Connect to WiFi
  
  while (WiFi.status() != WL_CONNECTED) {   // Wait for connection
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.print("Connected to ");    
  Serial.println(ssid);                   // Display confirmation msg to PC
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());         // Display IP Address to PC
}


void loop() {

  float analog_val = analogRead(sensor);      // Read Analog Input
  
  
  Digital_mVolt = (analog_val*3100.0)/1023;  // Analog temperature to mVolt //Max Analog Input = 3.1V
  tempc = Digital_mVolt/10;                  // Temperature from mVolt to degree Celsius 
  Serial.println(tempc);                     // Display Temperature to PC
  
   
  
  WiFiClient client;                      // Create object of Class WiFiClient
  const int httpPort = 80;                // Port No. 80
  if (!client.connect(host, httpPort)) {  // If Couldn't connect
    Serial.println("connection failed");  // Display error msg to PC
    return;
  }

  client.print(String("GET ") + path + String(tempc) + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");     // Send Temperature data to Cloud
  
  // thingspeak free version needs 16 sec delay between updates 
  delay(16000);                                       // wait for 16sec

}
