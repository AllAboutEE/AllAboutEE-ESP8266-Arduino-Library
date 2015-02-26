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
     *        provide and interface to the ESP8266 AT+ commands
     *        set. The functions' names are derived from the AT+
     *        commands e.g. AT+CIFSR becomes ciFsr(), AT+CIPCLOSE
     *        becomes cipClose()
     */
    class ESP8266
    {
    public:

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Instatiates the class and assings the stream for 
     *        communication with the ESP module and debug console.
     *        Assings hardware reset pin.
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
     * @brief Sends the AT+CIFSR command. Returns the IP Address 
     *        (with other characters around)
     * @return String Response from AT+CIFSR command.
     */
        String ciFsr();

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sends the AT+CWJAP=ssid,pass command. Attempts to make
     *        the ESP module join an Access Point (JAP)
     * @param SSID The access point's SSID (network name)
     * @param PASSWORD The access point's password/passphrase
     * 
     * @return String Response from the AT+CWJAP command
     */
        String cwJap(const char* SSID, const char* PASSWORD);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sets the module's mode. Station: can connect to an 
     *        access point; Access Point: can become an access point
     *        for other devices to connect to; Both: becomes both a
     *        station and access point. This will make.
     * @warning Mode 3 (Both), will cause ciFsr to return two IP 
     *          addresses, one for the station and for the access
     *          point.
     * @param mode 1 = station, 2 = access point, 3 = both
     * 
     * @return String Response from AT+CWMODE command
     */
        String cwMode(unsigned int mode);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief   Sends the "AT+CIPSEND=id,length" command. and 
     *          responds to the ">" command with data. Sends data to
     *          a connection.
     * @param connectionId The ID of the connection you wish to send 
     *                     the data to
     * @param data The data to send
     * 
     * @return String Response form AT+CIPSEND command
     */
        String cipSend(int connectionId, const char* data);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sends the AT+CIPCLOSE=id command. Closes an open 
     *        connection.
     * @param connectionId The ID of the connection you wish to 
     *                     close.
     * 
     * @return String Response from AT+CIPCLOSE command
     */
        String cipClose(int connectionId);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sends the command AT+CIPSERVER=x,y. Configures the 
     *        module as a server, if state = true, at the given
     *        port.
     * @param state Turn the server on/off (true/false) 
     * @param port The server port, where it will receive 
     *             connections
     * 
     * @return String Response from AT+CIPSERVER command
     */
        String cipServer(bool state, unsigned int port);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sends the AT+CIPMUX=1/0 command. Enables multiple 
     *        connections.
     * @param state Enable multiple connections? yes/no (true/false)
     * 
     * @return String Response from AT+CIPMUX command
     */
        String cipMux(bool state);
     
    /**
     * 
     * 
     * @author Miguel (2/25/2015)
     *  
     * @brief Sends AT+CIPSTATUS command. Returns the module's 
     *        connection status string.
     *  
     * @return String Response from the AT+CIPSTATUS command
     */
        String cipStatus(); 

    /**
     * 
     * 
     * @author Miguel (2/25/2015) 
     *  
     * @brief Sends AT+CWQAP command to quits/disconnect from the 
     *        Access Point (AP)
     * 
     * @return String Response from AT+CWQAP command.
     */
        String cwQap();

    /**
     * 
     * 
     * @author Miguel (2/25/2015)
     *  
     * @brief Sends the AT+CWLAP command. Scans for and lists the 
     *        available access points and each of their options.
     *  
     * @return String Response from the AT+CWLAP command.
     */
        String cwLap();

     /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Resets the module using its reset pin.
     *  
     * @return bool Command execution success/failure (true/false)
     */
        bool hardwareReset();

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Sends the AT+RST command. Software rests the module by
     *        sending the AT+RST command.
     *  
     * @return String Response from AT+RST command
     */
        String rst();

    protected:
    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Writes data via stream to the ESP modules. 
     * @param data The data bytes to send to the ESP8266
     * @param dataSize Size of the data array
     * @param timeoutMs time to wait for a response from the ESP8266
     *                  (if one is expected)
     * 
     * @return String The response from the ESP8266 after sending it 
     *         data
     */
        String write(const char* data, int dataSize, unsigned long timeoutMs);

    /**
     * 
     * 
     * @author Miguel (2/24/2015)
     *  
     * @brief Finds the length of an integer. The function was 
     *        created for the cipServer command specifically which
     *        require the port number's length to be calculated so
     *        that it could be sent in a character array/string. 
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
