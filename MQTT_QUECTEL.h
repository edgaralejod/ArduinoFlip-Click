/*#ifndef _MQTT_QUECTEL_H_
#define _MQTT_QUECTEL_H_

#include "gprs_lib.h"
#include "Adafruit_MQTT.h"

#define MQTT_QUECTEL_INTERAVAILDELAY 100
#define MQTT_QUECTEL_QUERYDELAY 500



class MQTT_QUECTEL : public Adafruit_MQTT {
 public:
  MQTT_QUECTEL(QuectelM95GPRS *f, const char *server, uint16_t port,
                       const char *cid, const char *user, const char *pass):
    Adafruit_MQTT(server, port, cid, user, pass),
    quectel(f)
  {}

  MQTT_QUECTEL(QuectelM95GPRS *f, const char *server, uint16_t port,
                     const char *user, const char *pass):
    Adafruit_MQTT(server, port, user, pass),
    quectel(f)
  {}

  bool connectServer() {
    char server[40];
    strncpy_P(server, servername, 40);
   // Watchdog.reset();

    // connect to server
    DEBUG_PRINTLN(F("Connecting to TCP"));
    return quectel->TCPconnect(server, portnum);
  }

  bool disconnectServer() {
    return quectel->TCPclose();
  }

  bool connected() {
    // Return true if connected, false if not connected.
    return quectel->TCPconnected();
  }

  uint16_t readPacket(uint8_t *buffer, uint8_t maxlen, int16_t timeout,
                      bool checkForValidPubPacket = false) {
    uint8_t *buffp = buffer;
    DEBUG_PRINTLN(F("Reading a packet.."));

    if (!quectel->TCPconnected()) return 0;


    uint16_t len = 0;
    int16_t t = timeout;
    uint16_t avail;

    while (quectel->TCPconnected() && (timeout >= 0)) {
      DEBUG_PRINT('.');
      while (avail = quectel->TCPavailable()) {
        DEBUG_PRINT('!');

        if (len + avail > maxlen) {
	  avail = maxlen - len;
	  if (avail == 0) return len;
        }

        // try to read the data into the end of the pointer
        if (! quectel->TCPread(buffp, avail)) return len;

        // read it! advance pointer
        buffp += avail;
        len += avail;
        timeout = t;  // reset the timeout

        //DEBUG_PRINTLN((uint8_t)c, HEX);

        if (len == maxlen) {  // we read all we want, bail
          DEBUG_PRINT(F("Read packet:\t"));
          DEBUG_PRINTBUFFER(buffer, len);
    return len;
        }

        // special case where we just one one publication packet at a time
        if (checkForValidPubPacket) {
          if ((buffer[0] == (MQTT_CTRL_PUBLISH << 4)) && (buffer[1] == len-2)) {
            // oooh a valid publish packet!
            DEBUG_PRINT(F("Read PUBLISH packet:\t"));
            DEBUG_PRINTBUFFER(buffer, len);
            return len;
          }
        }

      }
      //Watchdog.reset();
      timeout -= MQTT_QUECTEL_INTERAVAILDELAY;
      timeout -= MQTT_QUECTEL_QUERYDELAY; // this is how long it takes to query the FONA for avail()
      delay(MQTT_QUECTEL_INTERAVAILDELAY);
    }

    return len;
  }

  bool sendPacket(uint8_t *buffer, uint8_t len) {
    DEBUG_PRINTLN(F("Writing packet"));
    if (quectel->TCPconnected()) {
      boolean ret = quectel->TCPsend((char *)buffer, len);
      //DEBUG_PRINT(F("sendPacket returned: ")); DEBUG_PRINTLN(ret);
      if (!ret) {
        DEBUG_PRINTLN("Failed to send packet.")
        return false;
      }
    } else {
      DEBUG_PRINTLN(F("Connection failed!"));
      return false;
    }
    return true;
  }

 private:
  uint32_t serverip;
  QuectelM95GPRS *quectel;
};
#endif*/
