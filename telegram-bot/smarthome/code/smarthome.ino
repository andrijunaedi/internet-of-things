// Library
#include "CTBot.h"
#include "DHT.h"

//  Variable Declaration
#define DHTPIN D8
#define PIR_PIN D7
#define lamp D1
#define AC D2
#define doorlock D3
#define alarm D4
    
CTBot myBot;

String ssid   = "NAME_SSID";
String pass   = "PASSWORD_SSID"; 
String token  = "API_BOT_TOKEN";

int pirState = LOW;
int pirValue = 0;

#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
           
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
	pinMode(lamp, OUTPUT);
  pinMode(AC, OUTPUT);
  pinMode(doorlock, OUTPUT);
  pinMode(alarm, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  
	digitalWrite(lamp, HIGH); 
  digitalWrite(AC, HIGH);
  digitalWrite(doorlock, HIGH);
  digitalWrite(alarm, HIGH);

}

void loop() {
	TBMessage msg;

  // Motion Sensor
   pirValue = digitalRead(PIR_PIN);  
   if (pirValue == HIGH) {            
    if (pirState == LOW) {
      Serial.println("Motion detected!");
      String reply;
      reply = (String)"Motion Detected. \n \n" + 
      (String)"/alarmon  : To turn on the alarm.\n" +
      (String)"/lampon   : To turn on the lamp. \n";
      myBot.sendMessage(msg.sender.id, reply);
      pirState = HIGH;
      }
    } else {
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
      }
    }

    // dht11 sensor
    float t = dht.readTemperature();
    if(t > 28){
    digitalWrite(AC, LOW);
    String reply;
    reply = (String)"Temperature over 28 *C\n" +
    (String)"The air conditioner is automatically turned on.\n\n" +
    (String)"/cektemp     : To check the temperature. \n"; 
    myBot.sendMessage(msg.sender.id, reply);
  }
  
	// Cek new message.
	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("/start")) {                                             
			String reply;
      reply = (String)"Welcome\n" + msg.sender.username +
      (String)"\n\n/cmd  : To see the available commands."; 
      myBot.sendMessage(msg.sender.id, reply);  
		}
    else if (msg.text.equalsIgnoreCase("/cmd")) {                                            
      String reply;
      reply = (String)"List of commands.\n\n"+
      (String)"/lampon      : To turn on the lamp. \n" +
      (String)"/lampoff     : To turn off the lamp. \n" + 
      (String)"/ACon        : To turn on AC. \n" +
      (String)"/ACoff       : To turn off AC. \n" +
      (String)"/openDoor    : To open the door. \n" +
      (String)"/lockDoor    : To lock the door. \n" +
      (String)"/cektemp     : To check the temperature. \n" + 
      (String)"/cekhum      : To check humidity. \n" +
      (String)"/alarmon     : To turn on the alarm \n" +
      (String)"/alarmoff    : To turn off the alarm \n";
      myBot.sendMessage(msg.sender.id, reply);  
    }
    else if (msg.text.equalsIgnoreCase("/lampon")) {              
      digitalWrite(lamp, LOW);                              
      String reply;
      reply = (String)"The lamp was turned on. \n\n" +
      (String)"/lampoff    : To turn off the lamp. ";
      myBot.sendMessage(msg.sender.id, reply); 
    }
		else if (msg.text.equalsIgnoreCase("/lampoff")) {        
			digitalWrite(lamp, HIGH);                              
			String reply;
      reply = (String)"the lamp was turned off \n\n" +
      (String)"/lampon    : To turn on the lamp. ";
      myBot.sendMessage(msg.sender.id, reply); 
		}
    else if (msg.text.equalsIgnoreCase("/ACon")) {              
      digitalWrite(AC, LOW);                               
      String reply;
      reply = (String)"AC turned on. \n\n" +
      (String)"/ACoff    : To turn off AC. ";
      myBot.sendMessage(msg.sender.id, reply);  
    }
    else if (msg.text.equalsIgnoreCase("/ACoff")) {        
      digitalWrite(AC, HIGH);                              
      String reply;
      reply = (String)"AC turned off. \n\n" +
      (String)"/ACon    : To turn on AC ";
      myBot.sendMessage(msg.sender.id, reply); 
    }
    else if (msg.text.equalsIgnoreCase("/openDoor")) {              
      digitalWrite(doorlock, LOW);                               
      String reply;
      reply = (String)"The door is open\n\n" +
      (String)"/closeDoor    : To lock the door. ";
      myBot.sendMessage(msg.sender.id, reply);  
    }
    else if (msg.text.equalsIgnoreCase("/closeDoor")) {        
      digitalWrite(doorlock, HIGH);                              
      String reply;
      reply = (String)"The door is locked \n\n" +
      (String)"/openDoor    : To open the door";
      myBot.sendMessage(msg.sender.id, reply);
    }
    else if (msg.text.equalsIgnoreCase("/cektemp")) { 
      float t = dht.readTemperature();
      String suhu = "Current temperature : ";
      suhu += int(t);
      suhu += " *C";       
      myBot.sendMessage(msg.sender.id, suhu, ""); 
    }
    else if (msg.text.equalsIgnoreCase("/cekhum")) { 
      float t = dht.readTemperature();
      String hum = "Current humidity : ";
      hum += int(t);
      hum += " %";       
      myBot.sendMessage(msg.sender.id, hum, ""); 
    }
    else if (msg.text.equalsIgnoreCase("/alarmon")) {              
      digitalWrite(alarm, LOW);                               
      String reply;
      reply = (String)"The alarm was turned on. \n\n" +
      (String)"/alarmoff    : To turn off the alarm. ";
      myBot.sendMessage(msg.sender.id, reply);  
    }
    else if (msg.text.equalsIgnoreCase("/alarmoff")) {        
      digitalWrite(alarm, HIGH);                              
      String reply;
      reply = (String)"The alarm was turned off.  \n\n" +
      (String)"/alarmon    : To turn on the alarm. ";
      myBot.sendMessage(msg.sender.id, reply); 
    }
		else {                                                  
			String reply;
			reply = (String)"Sorry, the command entered is not available. \n\n" +
      (String)"/cmd  : To see the available commands. ";
			myBot.sendMessage(msg.sender.id, reply);             
		}
	}
	delay(500);
}
