#include "Microchip24AA02E.h"

Microchip24AA02E::Microchip24AA02E(TwoWire *theWire, const byte device_address) {
  this->device_address = device_address;
  _wire = theWire;  
}


const void Microchip24AA02E::readMac48(mac48 mac_address)  const {
  readMac48(mac_address, readDeviceAddress());
}

const void Microchip24AA02E::readMac64(mac64 mac_address)  const {
  readMac64(mac_address, readDeviceAddress());
}

const void Microchip24AA02E::readMac48(mac48 mac_address, const byte device_address) const {
  int offset = 0;
  for (int address = 0xFA; address <= 0xFF; address++) {
    mac_address[offset] = readRegister(address, device_address);
    offset++;
  }
}

const void Microchip24AA02E::readMac64(mac64 mac_address, const byte device_address) const {
  int offset = 0;
  for (int address = 0xF8; address <= 0xFF; address++) {
    mac_address[offset] = readRegister(address, device_address);
    offset++;
  }
}

const byte Microchip24AA02E::readDeviceAddress() const {
  return this->device_address;
}

const byte Microchip24AA02E::readRegister(const byte registry_address, const byte device_address, const int32_t timeout_ms) const {
  _wire->beginTransmission(device_address);
  _wire->write(registry_address);  // register to read
  _wire->endTransmission();

  _wire->requestFrom(device_address, (byte)1); // read a byte
  unsigned long previousMillis = millis(); 
  const long interval = timeout_ms;  
  while (!_wire->available()) { 
    unsigned long currentMillis = millis();
    if (interval > 0) { // if timeout_ms <= 0 this blocks forever, my default uses 100ms
      if (currentMillis - previousMillis >= interval) {
        return 0xFF;
      }
    }
  }
  return _wire->read();
}

// Microchip24AA02E MacReader = Microchip24AA02E();
