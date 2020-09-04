#define BLYNK_PRINT Serial

//  Library
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
 
char auth[] = "AUTH_TOKEN_BLYNK";
 
char ssid[] = "NAME_SSID";
char pass[] = "PASSWORD_SSID";

//Deklarasi 
#define IR_PIN D1        
#define PIR_IN D3
#define PIR_OUT D4

int ir = HIGH;
int pirStateIN = LOW;
int i = 1;
int pirStateOut = LOW;
int o = 1;
 
void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(PIR_IN, INPUT);
  pinMode(PIR_OUT, INPUT);
 
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

}
 
void loop()
{
  Blynk.run();

  // Motion Sensor IN
  i = digitalRead(PIR_IN);

  if ( i == HIGH) {            
    if (pirStateIN == LOW) {
      Serial.println("PIR_IN_RESPON");
      Blynk.notify("PIR IN NOTIFICATION");
      pirStateIN = HIGH;
    }
  } else {
    if (  pirStateIN == HIGH){
      pirStateIN = LOW;
    }
  }

  // Motion Sensor Out
  o = digitalRead(PIR_KELUAR);  

  if (o == HIGH) {            
    if (pirStateOut == LOW) {
      Serial.println("PIR_OUT_RESPON");
      Blynk.notify("PIR OUT NOTIFICATION");
      pirState_keluar = HIGH;
    }
  } else {
    if (pirStateOut == HIGH){
      pirStateOut = LOW;
    }
  }

  // Sensor IR
  ir = digitalRead(IR_INPUT_PIN);
  if (ir == LOW)
  {
    Serial.println("IR RESPON..");
    Blynk.notify("IR NOTIFICATION.....");
  }
}
