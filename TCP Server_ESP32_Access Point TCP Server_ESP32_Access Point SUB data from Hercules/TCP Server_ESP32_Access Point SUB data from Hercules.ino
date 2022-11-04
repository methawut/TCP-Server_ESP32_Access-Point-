//------------------------------------< Use With Hercules >
#include <WiFi.h>

//----- Create New WiFi 
char ssid[] = "ESP32 WiFi {por}";
char pass[] = "por150444";

WiFiServer server(88);  //----- TCP server Port:88

String message;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);

  server.begin();

  Serial.begin(115200);

  //----- Show IP of AP
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  WiFiClient client = server.available(); //Connect with New Client

  if (!client) // ถ้าไม่มีการเชื่อมต่อมาใหม่
  return; // ส่งลับค่าว่าง ทำให้ลูปนี้ถูกยกเลิก
 
  Serial.println("New client");
  while (client.connected()){             //if data is sending
    if (client.available()){              //if data is sent
      char c = client.read();             //data is 1 byte
      //---------------------------------------------------------< should deflaut >
      if (c == '\r'){                     //if data is Return 
        Serial.println(message); 
        //---------------------------------------------------------< condition >
        if (message == "LEDON"){
          Serial.println("ON");
        }
        else if (message == "LEDOFF"){
          Serial.println("OFF");
        }
        message = ""; 
        break;
        
      }

      //---------------------------------------------------------< should deflaut >
      else if (c == '\n'){}                //if data is New Line
      else{
        message += c;                     
        /* //-----< "c" is read data from client and add to "message" type: string >-----//
           Example : write : "go" --->
                  round 1 --> c == 'g' --> message == "g"
                  round 2 --> c == 'o' --> message == "go"
        */
      }
    }
  }

  delay(1);
  client.stop();                          //Stop Connect with Client
  Serial.println("Client disconnect");
}
