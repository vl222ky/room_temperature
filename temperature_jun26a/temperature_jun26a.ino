#include "arduino_secrets.h"
/* 
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/69e196c7-9ee0-4465-878b-9e26fd683007 

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float avg_temp;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/



#include "Arduino_LSM6DSOX.h"
#include "thingProperties.h"

unsigned long previousMillis = 0UL;
unsigned long interval = 5000UL;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  

  while(!Serial); // Prevents sketch from running until Serial Monitor opens.

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

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
  //resets the temperature value each loop.
  avg_temp = 0;
  
  for (int external_samples = 0; external_samples < 10; external_samples++)
	{
	// reads the external temperature sensor
  int externalSensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = externalSensorValue * (3.3 / 1023.0);
  // Convert the voltage to temperature in degrees Celsius
  float temperature = voltage - 0.5;
  temperature = temperature / 0.01;
  avg_temp = avg_temp + temperature;
  //// reads the internal temperature sensor
  int internalSensorValue;
  IMU.readTemperature(internalSensorValue);
  avg_temp = avg_temp + internalSensorValue;
	}
	
	// since we add two different values, 10 times each we must divide it by 20 to get the correct value
  avg_temp = avg_temp / 20;
  
  // replacement for delay which interrupts the connection to the cloud.
  unsigned long currentMillis = millis();

  while (millis() < currentMillis + interval)
  {
	  // The Arduino executes this code once every 10 seconds (interval = 10000 (ms) = 10 second)
  }
  previousMillis = currentMillis;
}











