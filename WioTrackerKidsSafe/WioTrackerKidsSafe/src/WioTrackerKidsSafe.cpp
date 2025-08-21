/* 
 * Project WioTrackerKidsSafe (homeBase)
 * Author: Jamie Dowden-Duarte
 * Date: 8/21/2025
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"
#include "Adafruit_GPS.h"

TCPClient TheClient;

// Define global variables
unsigned int currentTime = millis();
unsigned int lastTime;
float lon,lat;
String dateTime, timeOnly;

// Define User and Credentials
String password = "AA4104132968BA2224299079021594AB"; // AES128 password
String myName = "WioTracker";
const int RADIOADDRESS = 0xB1; // Get address from Instructor, it will be a value between 0xC1 - 0xCF
const int TIMEZONE = -6;

// Define Constants
const int RADIONETWORK = 7;    // range of 0-16
const int SENDADDRESS = 302;   // address of radio to be sent to
const int OLEDRESET = -1;
const int OLEDADDRESS = 0x3C;
const int GPSADDRESS = 0x10;

Adafruit_SSD1306 display(OLEDRESET);
Adafruit_GPS GPS(&Wire);

void getGPS(float *latittude, float *longitude, int *satellites, float *speed);
void createEventPayLoad (float lat, float lon);

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  Particle.syncTime();
  dateTime = Time.timeStr(); //current date and time from particle cloud
  timeOnly = dateTime.substring(11,19); //extracting time from dateTime

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setCursor(0,0);
  display.printf("Time: %s\n", dateTime);
  
  Serial1.begin(115200);
  //reyaxSetup(password);

   //Initialize GPS
  GPS.begin(GPSADDRESS);  // The I2C address to use is 0x10
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); 
  GPS.sendCommand(PGCMD_ANTENNA);

  if ((currentTime -lastTime)>1000){
  GPS.println(PMTK_Q_RELEASE);
  lastTime = currentTime;
  }
}

void loop() {
 
}
