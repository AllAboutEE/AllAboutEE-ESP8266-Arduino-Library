#include <AllAboutEE_ESP8266.h>

// TODO: add command verification on all functions

AllAboutEE::ESP8266::ESP8266(Stream *s,Stream *d,int8_t rp):stream(s),debug(d),resetPin(rp)
{

}


String AllAboutEE::ESP8266::getIPAddress()
{
    char command[] = "AT+CIFSR\r\n";
    return write(command,sizeof(command)/sizeof(command[0]),1000);
}

bool AllAboutEE::ESP8266::cwJap(const String SSID, const String PASSWORD)
{

    const int commandLength = 16+SSID.length()+PASSWORD.length();

    char command[100] = "AT+CWJAP=\""; // AT+CWJAP="ssid","pass"\r\n

    char s[SSID.length()];
    SSID.toCharArray(s,SSID.length()+1);
    strcat(command,s);
    strcat(command,"\",\"");

    char p[PASSWORD.length()];
    PASSWORD.toCharArray(p,PASSWORD.length()+1);
    strcat(command,p);
    strcat(command,"\"\r\n");
    write(command,commandLength,5000);

    return false;
}


bool AllAboutEE::ESP8266::cwMode(unsigned int mode)
{
    char command[13]="AT+CWMODE="; // AT+CWMODE=x\r\n
    char m[1];

    switch(mode)
    {
    case 1:
    case 2:
    case 3:
        sprintf(m,"%d",mode);
        strcat(command,m);
        strcat(command,"\r\n");
        write(command,sizeof(command)/sizeof(command[0]),1000);
        break;
    default:
        return false;
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

bool AllAboutEE::ESP8266::cipClose(unsigned int connectionId)
{
    char command[15]="AT+CIPCLOSE="; // AT+CIPCLOSE=x\r\n
    char connection[1];

    sprintf(connection,"%d",connectionId);
    strcat(command,connection);
    strcat(command,"\r\n");
    write(command,sizeof(command)/sizeof(command[0]),1000);

    return false;
}


bool AllAboutEE::ESP8266::cipServer(bool state, unsigned int port)
{
    return false;
}

bool AllAboutEE::ESP8266::cipMux(bool state)
{
    char command[13] = "AT+CIPMUX=";
    char s[1];

    if(state)
    {
        sprintf(s,"%d",1);
    }
    else
    {
        sprintf(s,"%d",1);
    }

    strcat(command,s);
    strcat(command,"\r\n");
    write(command,sizeof(command)/sizeof(command[0]),1000);

    return false;
}

String AllAboutEE::ESP8266::cipStatus()
{
    return "FAIL";
}

bool AllAboutEE::ESP8266::cwQap()
{
    char command[] = "AT+CWQAP\r\n";
    return  write(command,sizeof(command)/sizeof(command[0]),5000);
    return false;
}

String AllAboutEE::ESP8266::cwLap()
{
    char command[] = "AT+CWLAP\r\n";
    return  write(command,sizeof(command)/sizeof(command[0]),5000);
}

bool AllAboutEE::ESP8266::hardwareReset()
{
    if(resetPin < 0) return true;

    digitalWrite(resetPin, LOW);
    pinMode(resetPin, OUTPUT); // Open drain; reset -> GND
    delay(10);                  // Hold a moment
    pinMode(resetPin, INPUT);  // Back to high-impedance pin state

    return stream->find("Version");
}


bool AllAboutEE::ESP8266::softwareReset()
{
    char command[] = "AT+RST\r\n";
    write(command,sizeof(command)/sizeof(command[0]),2000);
    return false;
}

String AllAboutEE::ESP8266::write(char* data, int dataSize, unsigned long timeoutMs)
{
    String response = "";
    
    stream->write(data,dataSize);

    unsigned long time = millis();

    while((time+timeoutMs)>millis())
    {
        while(stream->available())
        {
            char c = stream->read();
            response +=c;
        }
    }

    if(response.length()==0)
    {
       // this command did not respond or does not have a response
       response = "NULL";
    }

    if(debug){
        debug->print(response);
    }


    return response;
}
