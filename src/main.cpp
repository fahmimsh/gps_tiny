#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
unsigned long start;
static void GPSDelay(unsigned long ms);
TinyGPSPlus gps;
SoftwareSerial ss(4, 3);
void get_gps(){
  GPSDelay(100);
  double lat_val, lng_val;
  bool loc_valid; //gps.location.isUpdated();
  lat_val = gps.location.lat();
  loc_valid = gps.location.isValid(); 
  lng_val = gps.location.lng();   
  if(!loc_valid){
    Serial.println("Menunggu data");
  } else {
    Serial.print("Lokasi: "); Serial.print(lat_val, 6);Serial.print(", ");
    Serial.println(lng_val, 6);
  }
}
void blink(){
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  ss.begin(115200);
  Serial.println("Baca data GPS");
}
void loop() {
  get_gps();
}
static void GPSDelay(unsigned long ms) 
{
  unsigned long start = millis();
  do
  {
    while (ss.available()) 
    gps.encode(ss.read());
  } while (millis() - start < ms);

}