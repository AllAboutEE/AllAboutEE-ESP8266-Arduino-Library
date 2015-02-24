namespace AllAboutEE
{
    class ESP8266
    {
        void joinAP(const String SSID, const String PASSWORD);

        String getIPAddress(),
               sendCommand(String command, timeout);

        void cwMode(int mode),
             cipSend(int connectionId, String data),
             cipClose(),
             cipServer(bool state, int port),
             cipMux(bool state),
             hardwareReset(),
             softwareReset();
        
    };
}
