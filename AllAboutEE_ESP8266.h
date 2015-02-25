#ifndef _ALLABOUTEE_ESP8266_H
#define _ALLABOUTEE_ESP8266_H

#include <Arduino.h>

namespace AllAboutEE
{
    /**
     * 
     * 
     * @author Miguel (2/24/2015) 
     *  
     * @details The "ESP8266" can be used to interface with the 
     *        ESP8266 module via UART. The class has functions which
     *        can send the ESP8266 commands, and display their
     *        response.
     */
    class ESP8266
    {
    public:
    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param s The ESP UART/serial object
     * @param d The serial debug object i.e. the serial object for 
     *          the debug console
     * @param rp The ESP's reset pin
     */
        ESP8266(Stream *s,Stream *d = NULL, int8_t rp = -1);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @return String The IP address assigned to the ESP8266 by the 
     *         access point.
     */
        String getIPAddress();

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param SSID The access point's SSID (network name)
     * @param PASSWORD The access point's password/passphrase
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cwJap(const char* SSID, const char* PASSWORD);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param mode 1 = station, 2 = access point, 3 = both
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cwMode(unsigned int mode);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param connectionId The ID of the connection you wish to send 
     *                     the data to
     * @param data The data to send
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cipSend(unsigned int connectionId, String data);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param connectionId The ID of the connection you wish to 
     *                     close.
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cipClose(unsigned int connectionId);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param state Turn the server on/off (true/false) 
     * @param port The server port, where it will receive 
     *             connections
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cipServer(bool state, unsigned int port);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param state Enable multiple connections? yes/no (true/false)
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool cipMux(bool state);
     

        String cipStatus(); 

        bool cwQap();

        String cwLap();

     /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool hardwareReset();

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @return bool Command execution success/failure (true/false)
     */
        bool softwareReset();

    private:
    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param data The data bytes to send to the ESP8266
     * @param dataSize Size of the data array
     * @param timeoutMs time to wait for a response from the ESP8266
     *                  (if one is expected)
     * 
     * @return String The response from the ESP8266
     */
        String write(char* data, int dataSize, unsigned long timeoutMs);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     * 
     * @param num The number from which you wish to find the length 
     *            of
     * 
     * @return int The length of the given number
     */
        int intLength(unsigned int num);

        Stream *stream,
               *debug;

        int8_t resetPin;
        
    };
}

#endif
