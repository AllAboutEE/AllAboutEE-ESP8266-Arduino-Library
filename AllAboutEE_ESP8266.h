
#ifndef _ALLABOUTEE_ESP8266_H
#define _ALLABOUTEE_ESP8266_H

#include <Arduino.h>

namespace AllAboutEE
{
    class ESP8266
    {

        String getIPAddress(),
               sendCommand(String command, unsigned long timeout);

        bool    ack(String m),
                joinAP(const String SSID, const String PASSWORD),
                cwMode(unsigned int mode),
                cipSend(unsigned int connectionId, String data),
                cipClose(),
                cipServer(bool state, unsigned int port),
                cipMux(bool state),
                hardwareReset(),
                softwareReset();
        
    };
}

#endif
