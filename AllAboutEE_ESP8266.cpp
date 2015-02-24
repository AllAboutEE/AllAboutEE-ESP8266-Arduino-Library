#include <AllAboutEE_ESP8266.h>

String AllAboutEE::ESP8266::getIPAddress()
{
    return "192.168.0.1";
}

String AllAboutEE::ESP8266::sendCommand(String command, unsigned long timeout)
{
    return "FAIL";
}

bool AllAboutEE::ESP8266::ack(String m)
{
    return false;
}

bool AllAboutEE::ESP8266::joinAP(const String SSID, const String PASSWORD)
{
    return false;
}

bool AllAboutEE::ESP8266::cwMode(unsigned int mode)
{
    switch(mode)
    {
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    default:
        break;
    }
    
    return false;
}

bool AllAboutEE::ESP8266::cipSend(unsigned int connectionId, String data)
{
    if(connectionId>8)
    {
        // there cannot be more than 8 connections
        return false;
    }

    return false;
}

bool AllAboutEE::ESP8266::cipClose()
{

    return false;
}

bool AllAboutEE::ESP8266::cipServer(bool state, unsigned int port)
{
    return false;
}

bool AllAboutEE::ESP8266::cipMux(bool state)
{

}

bool AllAboutEE::ESP8266::hardwareReset()
{
    return false;
}

bool AllAboutEE::ESP8266::softwareReset()
{
    return false;
}


