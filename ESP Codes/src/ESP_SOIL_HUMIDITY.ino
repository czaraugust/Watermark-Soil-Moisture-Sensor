
/*


ESSE CÓDIGO USA SOCKET, PORÉM É MAIS FÁCIL E SEGURO UTILIZAR MQTT.
VER: https://github.com/czaraugust/Weather_Station-MPPT/blob/master/ESP_Codes/src/main.ino

*/


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
String temp = " ";
const char* ssid = "IC-ALUNOS";
const char* password = "icomputacaoufal";
int count = 0;


const uint16_t port = 50939;
const char * host = "172.20.8.165"; // ip or dns

WiFiClient client;



char ControleMaquinaEstado;

void setup(){

    Serial.begin(115200);
    Serial.println("Setup done");
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0)
     Serial.println("no networks found");
    else
    {
     Serial.print(n);
     Serial.println(" networks found");
     for (int i = 0; i < n; ++i)
     {
       // Print SSID and RSSI for each network found
       Serial.print(i + 1);
       Serial.print(": ");
       Serial.print(WiFi.SSID(i));
       Serial.print(" (");
       Serial.print(WiFi.RSSI(i));
       Serial.print(")");
       Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
       delay(10);
     }
    }
    Serial.println("");


    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
   {
    delay(500);
    Serial.print(".");
   }

   Serial.println(WiFi.localIP());
   Serial.println("WiFi connected");
   delay (1000);

    Serial.print("connecting to ");
    Serial.println(host);
    }



  void loop() {

    long rssi  = WiFi.RSSI();


    if (!client.connect(host, port)) {

      Serial.println("connection failed");
      Serial.println("wait 5 sec...");
      delay(5000);
      Serial.print("connecting to ");
      Serial.println(host);
      count++;
      if (count > 50 && count < 75) {
        WiFi.begin(ssid, password);
        if (WiFi.status() != WL_CONNECTED)
        {
          delay(500);
          Serial.print(".");
        }


        Serial.println(WiFi.localIP());
        Serial.println("WiFi connected");
        count = 0;
      }
      return;
      }

            while (Serial.available() > 0) {

              char incomingByte = Serial.read();
              if (incomingByte == '@'){
                String values = String(rssi);
                 values +=  "|";
                values += Serial.readString();

                client.print(values);
              }

            }

    delay(1000);


  }
