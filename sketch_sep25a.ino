#define w1 A1
#define w2 A2
#define hang A3
#define alkony A5
#define mozgas 8
#define ajto 9
#define lampa 11
#define hom 7
#define servo 13
#define riaszto 12

#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <Servo.h>
#include <MySQL_Cursor.h>
#include <DHT.h>
#include <U8glib.h>
#include <SPI.h>

DHT dht(hom, DHT22);
U8GLIB_SH1106_128X64 u8g(2, 3, 10, 5, 4);
Servo myservo;
int eso1=0;
int eso2=0;
int allas=LOW;
int pre = LOW;
int sotet=900;
int mozog=0;

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 10, 3 }; 
byte subnet[] = {255, 255, 255, 0};

EthernetClient client;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET";
char   HOST_NAME[] = "192.168.10.2"; 
String PATH_NAME   = "/test.php";
String nyit = "?state=1";
String csuk = "?state=0";

void kijelzo(void) 
{
   u8g.setFont(u8g_font_fub17r);
   u8g.drawStr(0, 20, "Hom: ");
   u8g.drawStr(0, 60, "Para: ");
   u8g.setPrintPos(72, 20);
   u8g.print(dht.readTemperature(), 0);
   u8g.println("°C");
   u8g.setPrintPos(72, 60);
   u8g.print(dht.readHumidity(), 0);
   u8g.println("%");
}

void adatbazis(String val)
{
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    Serial.println("Connected to server");
    client.println(HTTP_METHOD + " " + PATH_NAME + val + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println(); 
    while(client.connected()) {
      if(client.available()){
        char c = client.read();
        Serial.print(c);
      }
    }
    client.stop();
    Serial.println();
    Serial.println("disconnected");
  } else {// if not connected:
    Serial.println("connection failed");
  }
}

void setup() {
    myservo.attach(servo);
    pinMode(ajto, INPUT_PULLUP);
    Serial.begin(9600);
    while (!Serial);
    pinMode(w1, OUTPUT);
    pinMode(w2, OUTPUT);  
    digitalWrite(w1, HIGH); 
    digitalWrite(w2, HIGH); 
    pinMode(lampa, OUTPUT);
    digitalWrite(lampa, LOW);
    myservo.write(100);

    dht.begin();

    Ethernet.begin(mac, ip);
    
    Serial.println("Connecting...");
    
    Serial.print("- Arduino's IP address   : ");
    Serial.println(Ethernet.localIP());

    Serial.print("- Gateway's IP address   : ");
    Serial.println(Ethernet.gatewayIP());

    Serial.print("- Network's subnet mask  : ");
    Serial.println(Ethernet.subnetMask());

    Serial.print("- DNS server's IP address: ");
    Serial.println(Ethernet.dnsServerIP());
    
}

void loop() {
  pre=allas;
  allas = digitalRead(ajto);
  if (allas == HIGH && pre == LOW){
      Serial.print("Nyit");
      adatbazis(nyit);    
  }
  if(allas == LOW && pre == HIGH){
     Serial.print("Csuk");
     adatbazis(csuk);
  }
  delay(10);
  
  eso1 = analogRead(w1);
  eso2 = analogRead(w2);
  Serial.print("szenzorok: ");
  Serial.print(eso1);
  Serial.print(" ");
  Serial.println(eso2);
  if(eso1 > 300 and eso2 > 300){
    myservo.write(0);
  }
    
  u8g.firstPage();  
  do{
     kijelzo();
  }while(u8g.nextPage());
  
  sotet=analogRead(alkony);
  Serial.print(sotet);
  Serial.print("-");
  mozog=digitalRead(mozgas);
  Serial.println(mozog);
  if(mozog>0 and sotet>800){
    digitalWrite(lampa, HIGH);
  }else{
    digitalWrite(lampa, LOW);
  }
  
  delay(2000);
  
}
