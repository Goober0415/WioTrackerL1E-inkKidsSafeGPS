#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO08x.h>
#include <Adafruit_USBD_CDC.h>
#include <GxEPD2_BW.h>  // For EINK display

// Display pins for WIO Tracker L1 EINK
static const uint8_t busy = D1;     // BUSY
static const uint8_t reset = D2;    // RST
static const uint8_t dc = D3;       // DC
static const uint8_t cs = D4;       // CS
static const uint8_t clk = D5;      // CLK
static const uint8_t din = D6;      // DIN

GxEPD2_BW<GxEPD2_213_B72> display(
  busy, reset, dc, cs, clk, din
);

struct TrackerData {
  float batteryVoltage;
  sensors_event_t orientation;
  sensors_event_t acceleration;
};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize display
  display.init(0);
 