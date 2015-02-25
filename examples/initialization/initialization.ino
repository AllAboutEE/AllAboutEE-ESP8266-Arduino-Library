/**
 * @author Miguel 
 *  
 * @date (2/25/2015)
 *  
 * @brief This example shows how to intialize the ESP8266 for 
 *          use as a server on port 80. Simply change the SSID
 *          and PASSWORD values to match your internet router's.
 */

#include <AllAboutEE_ESP8266.h>
#include <SoftwareSerial.h>

// ESP pins. Connect Arduino pin 3 to ESP's TX, connect Arduino pin 4 to ESP's RX. Connect ESP's RST pin to Arduino pin 8;
#define ESP_RX 3
#define ESP_TX 4
#define ESP_RST 8

using namespace AllAboutEE;

SoftwareSerial espSerial(ESP_RX,ESP_TX); // create ESP serial object
boolean isReady = false; // variable used to know if the initialization went OK.

ESP8266 esp(&espSerial,&Serial,ESP_RST); // create instance of ESP8266 class

const char ssid[] = "SSID"; // your internet router's SSID name
const char password[] = "PASSWORD"; // your SSID's password

void setup()
{
  
  espSerial.begin(9600); // default baud rate for most ESP's. Check your vendor's page for your ESP's baud rate.
  Serial.begin(38400);
  
  String temp= ""; // variable used to store responses from functions when necessary
  
  Serial.println("Starting...");
  
  esp.cwQap(); // Quit/disconnect from any access point.
  
  if(esp.rst().indexOf("OK")!= -1) // reset the module
  {
    if(esp.cwLap().indexOf(ssid) != -1) // List Available Access Points, and make sure that the desired one (SSID) is in them.
    {
      temp = esp.cwMode(1); // set CW mode 1 = Station, 2 = Access Point, 3 = Both
      
      if( (temp.indexOf("OK") != -1) || (temp.indexOf("no change") != -1) ) // check that CWMODE command was succesfull
      {
        if(esp.cwJap(ssid,password).indexOf("OK") != -1) // join the Access Point
        {
          if(esp.cipMux(true).indexOf("OK") != -1) // enable multiple connections
          {
            if(esp.cipServer(true,80).indexOf("OK") != -1) // enable server on port 90
            {
                // Get the IP address. The IP address is needed to talk to the ESP8266
                String ipAddress = esp.ciFsr(); // send IP address command
                // remove all unecessary characters that the AT+CIFSR command returns.
                ipAddress.replace("AT+CIFSR","");
                ipAddress.replace("\r","");
                ipAddress.replace("\n","");
                ipAddress.replace("OK","");

                Serial.print("IP Address: ");
                Serial.println(ipAddress);

                isReady = true; // all commands have been successfully executed
            }
            else
            {
             Serial.println("Could not configure as server."); 
            }
          }
          else
          {
            Serial.println("Could not enable multiple connections.");
          }
          
        }
        else
        {
         Serial.println("Could not join AP"); 
        }
      }
      else
      {
       Serial.println("Could not configure CWMODE"); 
      }
    }
    else
    {
      Serial.println("Could not find the specified SSID");
    }

  }
  else
  {
   Serial.println("Could not reset."); 
  }
  
  if(!isReady)
  {
   // one of the commands failed
   Serial.println("Please reset the system e.g. restart program or remove power "); 
  }
  else
  {
    // none of the commands failed
   Serial.println("Module initialization success. Now moving on to main program i.e. loop()"); 
  }
}

void loop()
{
    // main application code here. See other examples.
}
