#include <ESP8266WiFi.h>
const char* ssid = "Zainab";
const char* password = "znbtabbu20";
int Motor = D4;

int WET = 16; // Wet Indicator at Digital PIN D0
int DRY = 0; // Dry Indicator at Digital PIN D3

int sense_Pin = 0; // Soil Sensor input at Analog PIN A0
int value = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(Motor, OUTPUT);
  digitalWrite(Motor, HIGH);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");


  server.begin();
  Serial.println("Server started");


  Serial.print("This is the IP for connection: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  {
    Serial.begin(9600);
    pinMode(WET, OUTPUT);
    pinMode(DRY, OUTPUT);
    delay(2000);
  }

  {
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
  }

}
void loop()
{

  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }


  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }


  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();


  if (request.indexOf("/On") != -1)  {
    digitalWrite(Motor, LOW);
    //delay(2000);

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("Motor is ON");
    client.println("</html>");
    client.stop();
    delay(1);
  }
  if (request.indexOf("/Off") != -1)  {
    digitalWrite(Motor, HIGH);
    // delay(2000);

    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("Motor is OFF");
    client.println("</html>");
    client.stop();
    delay(1);
  }
  {
    Serial.print("MOISTURE LEVEL : ");
    value = analogRead(sense_Pin);
    value = value / 10;
    Serial.println(value);
    if (value < 50)
    {
      digitalWrite(WET, HIGH);
    }
    else
    {
      digitalWrite(DRY, HIGH);
    }
    delay(1000);
    digitalWrite(WET, LOW);
    digitalWrite(DRY, LOW);
  }

  {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);

    // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    float voltage = sensorValue * (5.0 / 1023.0);

    // print out the value you read:
    Serial.println(voltage);
  }
}
