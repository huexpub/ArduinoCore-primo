#include <BLEHIDPeripheral.h>
#include <BLEKeyboard.h>


// create peripheral instance, see pinouts above
BLEHIDPeripheral bleHIDPeripheral = BLEHIDPeripheral();
BLEKeyboard bleKeyboard;

void setup() {
  Serial.begin(9600);

  // clear bond store data
  bleHIDPeripheral.clearBondStoreData();


  bleHIDPeripheral.setReportIdOffset(1);


  bleHIDPeripheral.setLocalName("HID Keyboard");
  bleHIDPeripheral.addHID(bleKeyboard);

  bleHIDPeripheral.begin();

  Serial.println(F("BLE HID Keyboard"));
}

void loop() {
  BLECentral central = bleHIDPeripheral.central();

  if (central) {
    // central connected to peripheral
    Serial.print(F("Connected to central: "));
    Serial.println(central.address());

    while (central.connected()) {
      if (Serial.available() > 0) {
        // read in character
        char c = Serial.read();

        Serial.print(F("c = "));
        Serial.println(c);

        bleKeyboard.print(c);
      }
    }

    // central disconnected
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
