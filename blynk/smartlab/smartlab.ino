#define BLYNK_PRINT Serial

// Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
char auth[] = "AUTH_TOKEN_BLYNK";
 
char ssid[] = "NAME_SSID";
char pass[] = "PASSWORD_SSID";

// Variable declaration
#define DHTPIN D8         
#define IR_PIN D1
#define AC D7

int irState = HIGH;
 
#define DHTTYPE DHT11     
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

//Function DHT11
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);

  if(t > 28){
    digitalWrite(AC, LOW);
    Blynk.notify("Temperature over 28 *C\n The air conditioner is automatically turned on.");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(IR_PIN, INPUT);
 
  Blynk.begin(auth, ssid, pass);
 
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();

  // Sensor IR
  irState = digitalRead(IR_PIN);
  if (irState == LOW)
  {
    Serial.println("There is action...");
  }else{
    Serial.println("No action....");
    Blynk.notify("NO action notification");
  }
}
