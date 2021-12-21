#define ajto 2
#define w1 A1
#define w2 A2
#define sp 13
#define oled0 0
#define oled1 1
#define oled2 2
#define oled3 3
#define hom 7

#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <Servo.h>
#include <MySQL_Cursor.h>
#include <DHT.h>

DHT dht(hom, DHT22);
U8GLIB_SH1106_128X64 u8g(2, 3, 10, 5, 4);

Servo myservo;
int eso1=0;
int eso2=0;

/*MySQL-hez és hálózathoz */

byte mac_addr[] = { 0x08, 0x97, 0x98, 0xE5, 0x1F, 0x5A }; //08-97-98-E5-1F-5A

IPAddress server_addr(127,0,0,1);  // server ip
char user[] = "root";              // MySQL felhasználónév
char password[] = "";        // MySQL jelszó

EthernetClient client;
MySQL_Connection conn((Client *)&client);

void draw(void) 
{
   u8g.setFont(u8g_font_courR14);
   u8g.drawStr(0, 20, "Hőm: ");
   u8g.drawStr(0, 60, "Pára: ");
   u8g.setPrintPos(60, 20);
   u8g.print(dht.readTemperature(), 0);
   u8g.println("°C");
   u8g.setPrintPos(72, 60);
   u8g.print(dht.readHumidity(), 0);
   u8g.println("%");
}


void setup() {
    myservo.attach(sp);
    pinMode(ajto, INPUT_PULLUP);
    Serial.begin(9600);
    while (!Serial);
    pinMode(w1, OUTPUT);
    pinMode(w2, OUTPUT);  
    digitalWrite(w1, HIGH); 
    digitalWrite(w2, HIGH); 

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
  int state=0;
  int pre = 0;
  pre=state;
  state = digitalRead(ajto);
  
  if (state == HIGH && pre == LOW){
    //cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 0)"); 
  }
  if(state == LOW && pre == HIGH){
    //cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 1)");
  }
  //delete cur_mem;
  
  int reading = analogRead(13);
  int currentangle = map(reading, 0, 1023, 0, 180); 

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
    
  draw();

  delay(1000);
}
