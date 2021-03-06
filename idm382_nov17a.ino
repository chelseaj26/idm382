/* 
  Sketch generated by the Arduino IoT Cloud Thing "ProximityMeasurer"
  https://create.arduino.cc/cloud/things/d26eb210-9e1a-42cd-a190-4144c0a7dc8f 

  Arduino IoT Cloud Properties description

  The following variables are automatically generated and updated when changes are made to the Thing properties

  String measurer;
  bool lightswitch;

  Properties which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
// sensor
int cm = 0;

int distance = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

//CUSTOM TIMERS
long lastMessageTime = 0;
long messagedDelay = 3000;

String lastMessageTimeStr = "";


void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500); 
  pinMode(5, OUTPUT);
 // pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here 
  {
      cm = 0.01723 * readUltrasonicDistance( A1, A2);
      Serial.print(cm);
      Serial.println(" cm");
      // if the distance is further than 350 turn LED off
      //350cm = 11.5 feet
      if (cm > 350) {
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
      }
      // GREEN ON = SAFE
      //250cm= 8.2 ft
      if (cm <= 350 && cm > 183) {
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(7, LOW);
      }
      
      
      //RED ON= NOT SAFE
      //6 feet= 182.88 cm
      if (cm <= 183 && cm > 0) {
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
      }
      // RED ON= REALLY NOT SAFE
      if (cm <= 0) {
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        digitalWrite(7, HIGH);
      }
     }
  
  // Serial.println("looping");
  
  
// if ((millis()- lastMessageTime) > messagedDelay) {
//     Serial.println("Update Message");
    
//     lastMessageTimeStr = String(lastMessageTime);
//     measurer =  lastMessageTimeStr;
    
//     // reset to current time
//     lastMessageTime = millis();
// }
  
  //RED light switch
if (cm <= 183 && cm > 0) {
   lightswitch = false;
   measurer =  lastMessageTimeStr +"Too close!! Your distance is " + cm + "cm!";
   messagedDelay;
} else {
   lightswitch = true;
   measurer =  lastMessageTimeStr +"Safe! Your distance is " + cm + "cm!";
   messagedDelay;
}
}
 
  //END LOOP
  


void onMeasurerChange() {
  // Do something
}







void onLightswitchChange() {
  // Do something
}




















