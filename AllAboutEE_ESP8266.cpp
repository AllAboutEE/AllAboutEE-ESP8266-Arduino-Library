#include <AllAboutEE_ESP8266.h>

// TODO: add command verification on all functions

AllAboutEE::ESP8266::ESP8266(Stream *s,Stream *d,int8_t rp):stream(s),debug(d),resetPin(rp)
{

}


String AllAboutEE::ESP8266::ciFsr()
{
    char command[] = "AT+CIFSR\r\n";
    return write(command,strlen(command),1000);
}

String AllAboutEE::ESP8266::cwJap(const char* SSID, const char* PASSWORD)
{

    char command[100] = "AT+CWJAP=\""; // AT+CWJAP="ssid","pass"\r\n

    strcat(command,SSID);
    strcat(command,"\",\"");

    strcat(command,PASSWORD);
    strcat(command,"\"\r\n");

    const int commandLength = 16+strlen(SSID)+strlen(PASSWORD);
    command[commandLength+1] = '\0';

    return write(command,commandLength,5000);
}


String AllAboutEE::ESP8266::cwMode(unsigned int mode)
{
    char command[14]="AT+CWMODE="; // AT+CWMODE=x\r\n\0
    char m[2];

    switch(mode)
    {
    case 1:
    case 2:
    case 3:
        sprintf(m,"%d",mode);
        strcat(command,m);
        strcat(command,"\r\n");
        
        break;
    default:
        return "ERROR";
        break;
    }
    
    return write(command,strlen(command),1000);;
}

String AllAboutEE::ESP8266::cipSend(int connectionId, const char* data)
{
    if(connectionId>8)
    {
        // there cannot be more than 8 connections
        return "ERROR";
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
    int dataLength = strlen(data);
    char dlStr[dataLength];
    sprintf(dlStr,"%d",strlen(data));
    strcat(command,dlStr);

    // append end of command chars
    strcat(command,"\r\n");

    String response = write(command,strlen(command),1000);

    if(response.indexOf('>') != -1)
    {
        // AT+CIPSEND command successfully received
        return write(data,strlen(data),1000);

    }
    return "ERROR";
}

String AllAboutEE::ESP8266::cipClose(int connectionId)
{
    char command[16]="AT+CIPCLOSE="; // AT+CIPCLOSE=x\r\n\0
    char connection[2];

    sprintf(connection,"%d",connectionId);
    strcat(command,connection);
    strcat(command,"\r\n");
    return write(command,strlen(command),3000);

}


String AllAboutEE::ESP8266::cipServer(bool state, unsigned int port)
{

    char command[20]="AT+CIPSERVER="; // AT+CIPSERVER=x,xx\r\n\0

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

    return write(command,sizeof(command)/sizeof(command[0]),1000);
}

String AllAboutEE::ESP8266::cipMux(bool state)
{
    char command[14] = "AT+CIPMUX="; // AT+CIPMUX=x\r\n\0
    char s[2]="0";

    if(state)
    {
        s[0] = '1';
    }
    else
    {
        s[0] = '0';
    }

    strcat(command,s); // Alternative method, reduces progsize: command[10] = s[0];
    strcat(command,"\r\n"); // Alernative method, reduces progsize:
    /*
    command[11] = '\r';
    command[12] = '\n';
    command[13] = '\0';
    */
    
    return write(command,sizeof(command)/sizeof(command[0]),1000);
}

String AllAboutEE::ESP8266::cipStatus()
{
    char command[] = "AT+CIPSTATUS\r\n";
    return write(command,strlen(command),2000);
}

String AllAboutEE::ESP8266::cwQap()
{
    char command[] = "AT+CWQAP\r\n";
    return write(command,strlen(command),5000);
}

String AllAboutEE::ESP8266::cwLap()
{
    char command[] = "AT+CWLAP\r\n";
    return  write(command,strlen(command),5000);
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


String AllAboutEE::ESP8266::rst()
{
    char command[] = "AT+RST\r\n";
    return write(command,strlen(command),2000);
}

String AllAboutEE::ESP8266::write(const char* data, int dataSize, unsigned long timeoutMs)
{
    String response = "";
           
    stream->write(data,dataSize); // send the read character to the esp8266
    
    unsigned long time = millis();
    
    while( (time+timeoutMs) > millis())
    {
      while(stream->available())
      {
        
        // The esp has data so display its output to the serial window 
        char c = stream->read(); // read the next character.
        response+=c;
      }  
    }
    
    if(debug)
    {
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
