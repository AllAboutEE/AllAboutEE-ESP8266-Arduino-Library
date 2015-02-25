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

bool AllAboutEE::ESP8266::cwJap(const char* SSID, const char* PASSWORD)
{

    int ssidLength=0,passwordLength=0,count = 0;

    char command[100] = "AT+CWJAP=\""; // AT+CWJAP="ssid","pass"\r\n



    strcat(command,SSID);
    strcat(command,"\",\"");


    strcat(command,PASSWORD);
    strcat(command,"\"\r\n");

    while(*(SSID+count))
    {
        count++;
    }
    ssidLength=count;
    count=0;

    while(*(PASSWORD+count))
    {
        count++;
    }
    passwordLength=count;

    const int commandLength = 16+ssidLength+passwordLength;

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

    char command[] = "AT+CIPSEND="; // AT+CIPSEND=ID,dataLength\r\n

    // append connection ID
    int cidLength = intLength(connectionId);
    char cidStr[cidLength];
    sprintf(cidStr,"%d",connectionId);
    strcat(command,cidStr);

    // append comma
    strcat(command,",");

    // append data length
    int dataLength = data.length();
    char dlStr[dataLength];
    sprintf(dlStr,"%d",dataLength);
    strcat(command,dlStr);

    // append end of command chars
    strcat(command,"\r\n");

    String response = write(command,sizeof(command)/sizeof(command[0]),1000);

    if(response.indexOf('>') != -1)
    {
        // AT+CIPSEND command successfully received
        int dl = data.length();
        char dataArray[dl];
        data.toCharArray(dataArray,dl);
        write(dataArray,sizeof(dataArray)/sizeof(dataArray[0]),1000);

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

    char command[19]="AT+CIPSERVER="; // AT+CIPSERVER=x,xx\r\n

    if(state)
    {
        // turn server ON
        strcat(command,"1,");
    }else{
        // turn server OFF
        strcat(command,"0,");
    }
    
    char portNumberString[3];
    sprintf(portNumberString,"%d",port);
    strcat(command,portNumberString);
    strcat(command,"\r\n");

    write(command,sizeof(command)/sizeof(command[0]),1000);

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

/**
 * 
 * 
 * @author Miguel (2/24/2015)
 * 
 * @details This function was specifically created to find the 
 *        lenght of a port number for the AT+CIPSERVER command
 *        so we shouldn't expect huge numbers really. In fact I
 *        might be overdoing it with checking for integers
 *        largers than 4.
 * 
 */
int AllAboutEE::ESP8266::intLength(unsigned int num)
{
    if(num>=1000000000) return 10;
    if(num>=100000000) return 9;
    if(num>=10000000) return 8;
    if(num>=1000000) return 7;
    if(num>=100000) return 6;
    if(num>=10000) return 5;
    if(num>=1000) return 4;
    if(num>=100) return 3;
    if(num>=10) return 2;
    return 1;
}
