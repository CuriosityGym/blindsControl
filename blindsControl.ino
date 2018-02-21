#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "fauxmoESP.h"
#include <AccelStepper.h>


#define REVOLUTIONS 512
#define WIFI_SSID "New Curiosity Gym"
#define WIFI_PASS "CuriosityTwinkle"
#define SERIAL_BAUDRATE                 115200
#define LED                             2
# define delayInMillis 1

#define CCW 0
#define CW 1
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  14     // IN1 on the ULN2003 driver 1
#define motorPin2  0     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5     // IN4 on the ULN2003 driver 1

byte motorDirection=CW;
// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
fauxmoESP fauxmo;





// -----------------------------------------------------------------------------
// Wifi
// -----------------------------------------------------------------------------

void wifiSetup() {

  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());

}


void setup() {
  
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
  stepper1.setSpeed(200);
  stepper1.moveTo(20000);
  // Init serial port and clean garbage
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  Serial.println();

  // Wifi
  wifiSetup();

  // LED
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);

  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);

  // Add virtual devices
  fauxmo.addDevice("Helios");
  

  // fauxmoESP 2.0.0 has changed the callback signature to add the device_id,
  // this way it's easier to match devices to action without having to compare strings.
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s\n", device_id, device_name, state ? "ON" : "OFF");
   
   if(state)
   {
     stepper1.moveTo(2000);
     digitalWrite(LED, LOW);
   }
   if(!state)
   {
      stepper1.moveTo(-2000);
      digitalWrite(LED, HIGH);
   }
   
    
  });

  // Callback to retrieve current state (for GetBinaryState queries)
  fauxmo.onGetState([](unsigned char device_id, const char * device_name) {
    return !digitalRead(LED);
  });

}

void loop() {

  // Since fauxmoESP 2.0 the library uses the "compatibility" mode by
  // default, this means that it uses WiFiUdp class instead of AsyncUDP.
  // The later requires the Arduino Core for ESP8266 staging version
  // whilst the former works fine with current stable 2.3.0 version.
  // But, since it's not "async" anymore we have to manually poll for UDP
  // packets
  
  fauxmo.handle();
  stepper1.run();
  

}



