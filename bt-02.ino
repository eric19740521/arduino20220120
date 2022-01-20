#include "BluetoothSerial.h"


BluetoothSerial SerialBT;

//58:bf:25:05:bb:8a
String MACadd = "58:BF:25:05:BB:8A";
uint8_t address[6]  = {0x58, 0xBF, 0x25, 0x05, 0xBB, 0x8A};
//uint8_t address[6]  = {0x00, 0x1D, 0xA5, 0x02, 0xC3, 0x22};
String name = "ESP_A01";
char *pin = "1234"; //<- standard pin would be provided by default
bool connected;



void setup() {


  Serial.begin(115200);
  //SerialBT.setPin(pin);
  SerialBT.begin("ESP_A02", true);
  //SerialBT.setPin(pin);
  Serial.println("The device started in master mode, make sure remote BT device is on!");

  // connect(address) is fast (upto 10 secs max), connect(name) is slow (upto 30 secs max) as it needs
  // to resolve name to address first, but it allows to connect to different devices with the same name.
  // Set CoreDebugLevel to Info to view devices bluetooth address and device names
  //connected = SerialBT.connect(name);
  
  connected = SerialBT.connect(address);

  if (connected) {
    Serial.println("Connected Succesfully!");
  } else {
    while (!SerialBT.connected(10000)) {
      Serial.println("Failed to connect. Make sure remote device is available and in range, then restart app.");
    }
  }
  // disconnect() may take upto 10 secs max
  if (SerialBT.disconnect()) {
    Serial.println("Disconnected Succesfully!");
  }
  // this would reconnect to the name(will use address, if resolved) or address used with connect(name/address).
  SerialBT.connect();
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());


  }



  delay(20);



}
