#include <AllAboutEE_ESP8266Server.h>

AllAboutEE::ESP8266Server::ESP8266Server(Stream *s,Stream *d,int8_t rp):ESP8266(s,d,rp)
{
    
}

bool AllAboutEE::ESP8266Server::begin(const char* SSID, const char* PASSWORD)
{
    bool isReady = false;
    String temp = "";

    cwQap(); // Quit/disconnect from any access point.
  
    if(rst().indexOf("OK")!= -1) // reset the module
    {
        if(cwLap().indexOf(SSID) != -1) // List Available Access Points, and make sure that the desired one (SSID) is in them.
        {
          temp = cwMode(1); // set CW mode 1 = Station, 2 = Access Point, 3 = Both
          
          if( (temp.indexOf("OK") != -1) || (temp.indexOf("no change") != -1) ) // check that CWMODE command was succesfull
          {
            if(cwJap(SSID,PASSWORD).indexOf("OK") != -1) // join the Access Point
            {
              if(cipMux(true).indexOf("OK") != -1) // enable multiple connections
              {
                if(cipServer(true,80).indexOf("OK") != -1) // enable server on port 90
                {
                    // get the IP address
                    String ipAddress = ciFsr();
                    ipAddress.replace("AT+CIFSR","");
                    ipAddress.replace("\r","");
                    ipAddress.replace("\n","");
                    ipAddress.replace("OK","");
                    setIpAddress(ipAddress);
                    if(debug)
                    {
                        debug->print("IP Address Length: ");
                        debug->println(ipAddress.length());

                        debug->print("IP Address: ");
                        debug->println(ipAddress);
                    }

                    isReady = true;
                }
                else
                {
                    if(debug)
                        debug->println("Could not configure as server."); 
                }
              }
              else
              {
                  if(debug)
                      debug->println("Could not enable multiple connections.");
              }
              
            }
            else
            {
                if(debug)
                    debug->println("Could not join AP"); 
            }
          }
          else
          {
              if(debug)
                  debug->println("Could not configure CWMODE"); 
          }
        }
        else
        {
            if(debug)
                debug->println("Could not find the specified SSID");
        }

    }
    else
    {
        if(debug)
            debug->println("Could not reset."); 
    }

    if(!isReady)
    {
        // one of the commands failed
        if(debug)
            debug->println("Please reset the system e.g. restart program or remove power "); 
    }
    else
    {
        // none of the commands failed
        if(debug)
            debug->println("Server initialization success."); 
    }

    return isReady;
}

String AllAboutEE::ESP8266Server::getIpAddress()
{
    return ipAddress;
}

bool AllAboutEE::ESP8266Server::newConnection()
{
    if(stream->available())
    {
       if(stream->find("+IPD,"))
       {
           do{
               setCurrentConnectionId(stream->read()-48);
           }while(getCurrentConnectionId()<0);

           if(debug)
           {
               debug->print("+IPD,");
               debug->print(getCurrentConnectionId());
           }

           while(stream->available())
           {
               char c = stream->read();
               if(debug)
               {
                   debug->print(c);
               }
           }

           return true;
       }
    }
    return false;
}

bool AllAboutEE::ESP8266Server::closeConnection(int connectionId)
{
    while(stream->available())
    {
       char c = stream->read();
       if(debug)
       {
           debug->print(c);
       }
    }

    if(cipClose(connectionId).indexOf("ink")!= -1)
    {
        return true;
    }
    if(debug)
    {
        debug->println("Connection may not have closed.");
    }
    return false;
}

void AllAboutEE::ESP8266Server::setCurrentConnectionId(int cid)
{
    this->currentConnectionId = cid;
}

int AllAboutEE::ESP8266Server::getCurrentConnectionId()
{
    return currentConnectionId;
}

void AllAboutEE::ESP8266Server::closeAllConnections()
{

    for(int i=0;i<8;i++)
    {
        cipClose(i);
    }
}

void AllAboutEE::ESP8266Server::setIpAddress(String ipAddress)
{
    this->ipAddress = ipAddress;
}
