#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "fauxmoESP.h"
#include "credentials.h"
#define WIFI_SSID "New Curiosity Gym"
#define WIFI_PASS "CuriosityTwinkle"
#define SERIAL_BAUDRATE                 115200
#define LED                             2
# define delayInMillis 1
fauxmoESP fauxmo;
int Pin1 = 14; 
int Pin2 = 0; 
int Pin3 = 4; 
int Pin4 = 5; 
int _step = 0; 
int revolutions = 1;


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
void openBlinds(int rev)
    {
      for(int j=0; j<rev; j++)
         { 
           Serial.println("Fwd");   
           for(int i=0; i<8;i++){
           _step = i;   
          // Serial.println(_step);  
           switch(_step){ 
               
              case 0: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              case 1: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              case 2: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 3: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 4: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 5:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;   
              case 6:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 7:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              default:  
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
             }
            delay(1); 
          }
       }
    }        

void closeBlinds(int rev)
    {
      for(int j=0; j<rev; j++)
         { 
           Serial.println("Backwd");   
            //case 0: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, HIGH); 
   delay(delayInMillis);  
   //case 1: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, HIGH); 
   delay(delayInMillis);  
   //case 2: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, LOW); 
   delay(delayInMillis); 
   //case 3: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, HIGH); 
     digitalWrite(Pin4, LOW); 
   delay(delayInMillis);  
   //case 4: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   delay(delayInMillis);  
   //case 5: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, HIGH); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   delay(delayInMillis);  
     //case 6: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
   delay(delayInMillis);  
   //case 7: 
     digitalWrite(Pin1, HIGH);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, HIGH); 
   delay(delayInMillis);  
   //default: 
     digitalWrite(Pin1, LOW);  
     digitalWrite(Pin2, LOW); 
     digitalWrite(Pin3, LOW); 
     digitalWrite(Pin4, LOW); 
  delay(delayInMillis);  
       }
    }        

void setup() {
    revolutions = revolutions*512;
    pinMode(Pin1, OUTPUT);  
    pinMode(Pin2, OUTPUT);  
    pinMode(Pin3, OUTPUT);  
    pinMode(Pin4, OUTPUT); 
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
    fauxmo.addDevice("Fan");
  //fauxmo.addDevice("switch two"); // You can add more devices
  //fauxmo.addDevice("switch three");

    // fauxmoESP 2.0.0 has changed the callback signature to add the device_id,
    // this way it's easier to match devices to action without having to compare strings.
    fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state) {
        Serial.printf("[MAIN] Device #%d (%s) state: %s\n", device_id, device_name, state ? "ON" : "OFF");
       // digitalWrite(LED, !state);
        if(state==0)
          {
           digitalWrite(LED, HIGH); 
         for(int j=0; j<512; j++)
         { 
           Serial.println("Fwd");   
           for(int i=0; i<8;i++){
           _step = i;   
          // Serial.println(_step);  
           switch(_step){ 
               
              case 0: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              case 1: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              case 2: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 3: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, HIGH); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 4: 
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 5:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, HIGH); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;   
              case 6:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
              case 7:
                     Serial.println(_step);  
                     digitalWrite(Pin1, HIGH);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, HIGH); 
                     break;  
              default:  
                     Serial.println(_step); 
                     digitalWrite(Pin1, LOW);  
                     digitalWrite(Pin2, LOW); 
                     digitalWrite(Pin3, LOW); 
                     digitalWrite(Pin4, LOW); 
                     break;  
             }
            delay(1); 
          }
       }
          }
        if(state==1)
          {
           digitalWrite(LED, LOW); 
           closeBlinds(revolutions);
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

   // static unsigned long last = millis();
    //if (millis() - last > 5000) {
    //    last = millis();
   //     Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
       // Serial.println(revolutions);
    //}

}

