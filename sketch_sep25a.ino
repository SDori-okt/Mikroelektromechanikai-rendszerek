#define w1 A1
#define w2 A2
#define hang A3
#define alkony A5
#define mozgas 8
#define ajto 9
#define lampa 11
#define hom 7
#define servo 13

#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <Servo.h>
#include <MySQL_Cursor.h>
#include <DHT.h>
#include <U8glib.h>

DHT dht(hom, DHT22);
U8GLIB_SH1106_128X64 u8g(2, 3, 10, 5, 4);

Servo myservo;
int eso1=0;
int eso2=0;
int state=0;
int pre = 0;

/*
byte mac_addr[] = { 0x08, 0x97, 0x98, 0xE5, 0x1F, 0x5A }; //08-97-98-E5-1F-5A

IPAddress server_addr(127,0,0,1);  // server ip
char user[] = "root";              // MySQL felhasználónév
char password[] = "";        // MySQL jelszó

EthernetClient client;
MySQL_Connection conn((Client *)&client);
*/

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
    /*
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
    
    if (conn.connect(server_addr, 3306, user, password)) {
      Serial.println("Csatlakoztatva.");
    } else {
      Serial.println("Nem sikerült kapcsolódni.");
    }
    conn.close();
    */
}

void loop() {
  //MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  pre=state;
  state = digitalRead(ajto);
  
  if (state == HIGH && pre == LOW){
      Serial.print("Nyit");
     //cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 0)"); 
  }
  if(state == LOW && pre == HIGH){
     Serial.print("Csuk");
    //cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 1)");
  }
  //delete cur_mem;
  
  int reading = analogRead(13);
  int currentangle = map(reading, 0, 1023, 0, 180); 
  Serial.print("Szög:");
  Serial.print(currentangle);
  delay(10);  
  eso1 = analogRead(w1);
  eso2 = analogRead(w2);
  Serial.print("szenzorok: ");
  Serial.print(eso1);
  Serial.print(" ");
  Serial.println(eso2);
  if(eso1 > 170 and eso2 > 170 and currentangle<170){
    myservo.write(180);
  }
  /*
  float t = dht.readTemperature();
  Serial.println(t);*/
    
  u8g.firstPage();  
  do{
     kijelzo();
  }while(u8g.nextPage());
   
  Serial.print("alkony: ");
  Serial.println(analogRead(alkony));
  Serial.print("mozgas: ");
  Serial.println(digitalRead(mozgas));
  if(digitalRead(mozgas)==1 and analogRead(alkony)>800){
    digitalWrite(lampa, HIGH);
  }else{
    digitalWrite(lampa, LOW);
  }
  delay(1000);
}
