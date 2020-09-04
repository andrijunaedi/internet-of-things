#define BLYNK_PRINT Serial

//  Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
char auth[] = "AUTH_TOKEN_BLYNK";
 
char ssid[] = "NAME_SSID";
char pass[] = "PASSWORD_SSID";

// Variable declaration
#define BUTTON_PIN D1     
#define IR_INPUT_PIN D2
#define IR_OUT_PIN D3
 
int irInput = HIGH;
int irOut = HIGH;
int button = 0;
 
void setup()
{
  // Debug console
  Serial.begin(9600);

  // Setup PinMode
  pinMode(IR_INPUT_PIN, INPUT);
  pinMode(IR_OUT_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  // Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  // Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

}
 
void loop()
{
  Blynk.run();

  // Sensor IR_INPUT
  irInput = digitalRead(IR_INPUT_PIN);
  if (irInput == LOW)
  {
    Serial.println("IR INPUT..");
    Blynk.notify("Visitors enter NOTIFICATION.....");
  }

  // Sensor IR_OUT
  irOut = digitalRead(IR_OUT_PIN);
  if (irOut == LOW)
  {
    Serial.println("IR OUT..");
    Blynk.notify("Outgoing visitors NOTIFICATION.....");
  }

  // Button ON
  button = digitalRead(BUTTON_PIN);
  if (button == HIGH)
  {
    Serial.println("BUTTON ON..");
    Blynk.notify("BUTTON PUSH NOTIFICATION...");
  }
  
}
