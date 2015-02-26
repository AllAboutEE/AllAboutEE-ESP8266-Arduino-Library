#ifndef _ALLABOUTEE_ESP8266_SERVER_H
#define _ALLABOUTEE_ESP8266_SERVER_H

#include <Arduino.h>
#include <AllAboutEE_ESP8266.h>

namespace AllAboutEE
{
/**
 * 
 * 
 * @author Miguel (2/25/2015) 
 *  
 * @details A class to use the ESP8266 WiFi module as an HTTP 
 *          webserver.
 */
    class ESP8266Server : public ESP8266
    {
    public:
        ESP8266Server(Stream *s,Stream *d = NULL, int8_t rp = -1);
    /**
     * 
     * 
     * @author Miguel (2/25/2015)
     *  
     * @brief Attempts to make the WiFi module a server. 
     * @param SSID The access point's SSID
     * @param PASSWORD The access point's password.
     * 
     * @return bool true if the module was succesfully configured as 
     *         a server, false otherwise.
     */
        bool begin(const char* SSID, const char* PASSWORD);

    /**
     * 
     * 
     * @author Miguel (2/25/2015)
     * 
     * @return String The server's IP address.
     */
        String getIpAddress();

        bool newConnection();

        bool closeConnection(int connectionId);

        void setCurrentConnectionId(int cid);

        int getCurrentConnectionId();

        void closeAllConnections();

    protected:

    private:
        String ipAddress;
        int currentConnectionId;
    /**
     * 
     * 
     * @author Miguel (2/25/2015) 
     *  
     * @warning The IP address is obtained from the AT+CIFSR 
     *          command, i.e. This function is not meant to be used
     *          to change/assign an IP address to the module.
     * 
     * @param ipAddress The server's IP address
     */
        void setIpAddress(String ipAddress);
    };
}

#endif
