#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

#define ONE_WIRE_BUS 13
#define RELAY_PIN 10

static const int MAX_TEMPERATURE_PRIMARY 120
static const int MIN_TEMPERATURE_COOLING 82
static const int MAX_TEMPERATURE_HOLDING 89
static const int MIN_TEMPERATURE_HOLDING 87

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress crockPot = { 0x28, 0xFF, 0x91, 0x5A, 0x53, 0x15, 0x02, 0xC1 };
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void turnOn() {
  digitalWrite(RELAY_PIN, HIGH);
}
void turnOff() {
  digitalWrite(RELAY_PIN, LOW);
}

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  // Start up the library
  sensors.begin();
  // set the resolution to 10 bit (good enough?)
  sensors.setResolution(crockPot, 10);
  lcd.begin(16, 2);
  pinMode(RELAY_PIN, OUTPUT);
  lcd.setCursor(0,0);
  lcd.write("Hi Girlfriend");
  lcd.setCursor(0,1);
  lcd.write("Temp: ");
  delay(2000);

}

void printTemperature(DeviceAddress deviceAddress)
{
  sensors.requestTemperatures();
  lcd.setCursor(6,1);
  float tempC = sensors.getTempC(deviceAddress);
  if (tempC == -127.00) {
    lcd.print("Temp Error");
  } else {
    lcd.print(DallasTemperature::toFahrenheit(tempC));
  }
}

float measureTemp(DeviceAddress deviceAddress) {
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(deviceAddress);
  return DallasTemperature::toFahrenheit(tempC);
}

void heatUpPrimary() {
  lcd.setCursor(0,0);
  lcd.write("Warming up!");
  
  turnOn();
  while(measureTemp(crockPot) < MAX_TEMPERATURE_PRIMARY) {
    printTemperature(crockPot);
    delay(500);
  }
  turnOff();
}

void coolDownPrimary() {
  lcd.setCursor(0,0);
  lcd.write("Cooling Down!");  
  turnOff();
  while(measureTemp(crockPot) > MIN_TEMPERATURE_COOLING) {
    printTemperature(crockPot);
    delay(500);
  }
}

void maintainTemp() {
  turnOn();
  while(true) {
    if(measureTemp(crockPot) < MIN_TEMPERATURE_HOLDING) {
      turnOn();
    }
    if (measureTemp(crockPot) > MAX_TEMPERATURE_HOLDING) {
      turnOff();
    }
    printTemperature();
    delay(500);
  }

}

void loop(void)
{ 
  heatUpPrimary();
  coolDownPrimary();
  maintainTemp();
}

