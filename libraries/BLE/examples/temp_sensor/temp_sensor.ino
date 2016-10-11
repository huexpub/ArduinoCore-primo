// TimerOne library: https://code.google.com/p/arduino-timerone/
#include <TimerOne.h>
// DHT library: https://github.com/adafruit/DHT-sensor-library
#include "DHT.h"
#include <BLEPeripheral.h>

#define DHTTYPE DHT22
#define DHTPIN 3

DHT dht(DHTPIN, DHTTYPE);

BLEPeripheral blePeripheral = BLEPeripheral();

BLEService tempService = BLEService("CCC0");
BLEFloatCharacteristic tempCharacteristic = BLEFloatCharacteristic("CCC1", BLERead | BLENotify);
BLEDescriptor tempDescriptor = BLEDescriptor("2901", "Temp Celsius");

BLEService humidityService = BLEService("DDD0");
BLEFloatCharacteristic humidityCharacteristic = BLEFloatCharacteristic("DDD1", BLERead | BLENotify);
BLEDescriptor humidityDescriptor = BLEDescriptor("2901", "Humidity Percent");

volatile bool readFromSensor = false;

float lastTempReading;
float lastHumidityReading;

void setup() {
  Serial.begin(115200);

  blePeripheral.setLocalName("Temperature");

  blePeripheral.setAdvertisedServiceUuid(tempService.uuid());
  blePeripheral.addAttribute(tempService);
  blePeripheral.addAttribute(tempCharacteristic);
  blePeripheral.addAttribute(tempDescriptor);

  blePeripheral.setAdvertisedServiceUuid(humidityService.uuid());
  blePeripheral.addAttribute(humidityService);
  blePeripheral.addAttribute(humidityCharacteristic);
  blePeripheral.addAttribute(humidityDescriptor);

  blePeripheral.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  blePeripheral.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  blePeripheral.begin();

  Timer1.initialize(2 * 1000000); // in milliseconds
  Timer1.attachInterrupt(timerHandler);

  Serial.println(F("BLE Temperature Sensor Peripheral"));
}

void loop() {
  blePeripheral.poll();

  if (readFromSensor) {
    setTempCharacteristicValue();
    setHumidityCharacteristicValue();
    readFromSensor = false;
  }
}

void timerHandler() {
  readFromSensor = true;
}

void setTempCharacteristicValue() {
  float reading = dht.readTemperature();
//  float reading = random(100);

  if (!isnan(reading) && significantChange(lastTempReading, reading, 0.5)) {
    tempCharacteristic.setValue(reading);

    Serial.print(F("Temperature: ")); Serial.print(reading); Serial.println(F("C"));

    lastTempReading = reading;
  }
}

void setHumidityCharacteristicValue() {
  float reading = dht.readHumidity();
//  float reading = random(100);

  if (!isnan(reading) && significantChange(lastHumidityReading, reading, 1.0)) {
    humidityCharacteristic.setValue(reading);

    Serial.print(F("Humidity: ")); Serial.print(reading); Serial.println(F("%"));

    lastHumidityReading = reading;
  }
}

boolean significantChange(float val1, float val2, float threshold) {
  return (abs(val1 - val2) >= threshold);
}

void blePeripheralConnectHandler(BLECentral& central) {
  Serial.print(F("Connected event, central: "));
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLECentral& central) {
  Serial.print(F("Disconnected event, central: "));
  Serial.println(central.address());
}

