// Library
#include "CTBot.h"

// Deklarasi
#define GAS_PIN A0
#define alarm D1
    
CTBot myBot;

String ssid = "NAME_SSID";
String pass = "PASSOWORD_SSID"; 
String token = "BOT_TOKEN_API";

// User get message from telegram-bot
const int id_1 = 1234567 ; // <-- ID Telegram
const int id_2 = 1234567 ;
const int id_n = 1234567 ;

int gasValue   = 600; // <-- The value adjusted the need for the indicator
int smokeValue = 400;
           
void setup() {
	// initialize the Serial
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	// connect ESP8266
	myBot.wifiConnect(ssid, pass);

	// set telegram bot token
	myBot.setTelegramToken(token);

	// check connection
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

	// set pinMode
	pinMode(GAS_PIN, INPUT);
  pinMode(alarm, OUTPUT);
  digitalWrite(alarm, LOW);
}

void loop() {
	TBMessage msg;

  // GAS Sensor
  int analogSensor = analogRead(GAS_PIN);

  Serial.print("GAS SENSOR : ");
  Serial.println(analogSensor);

  if (analogSensor > gas_indikator){
    digitalWrite(alarm, HIGH);
    myBot.sendMessage(id_1, "GAS DETECTED");
    myBot.sendMessage(id_2, "GAS DETECTED");
    myBot.sendMessage(id_n, "GAS DETECTED");
  }
  else
  {
    digitalWrite(alarm, LOW);
  }

  if (analogSensor > asap_indikator){
    digitalWrite(alarm, HIGH);
    myBot.sendMessage(id_1, "SMOKE DETECTED");
    myBot.sendMessage(id_2, "SMOKE DETECTED");
    myBot.sendMessage(id_n, "SMOKE DETECTED");
  }
  else
  {
    digitalWrite(alarm, LOW);
  }
  
	// Cek new message.
	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("/start")) {                                             
			String reply;
      reply = (String)"Welcome" + msg.sender.username +
      (String)"\n\n/cek_gas  : To check the gas value on the sensor."; 
      myBot.sendMessage(msg.sender.id, reply);  
		}
    else if (msg.text.equalsIgnoreCase("/cek_gas")) {              
      String gas = "Present GAS value : ";
      gas += int(analogSensor);
      myBot.sendMessage(msg.sender.id, gas, ""); 
    }
  }
}
