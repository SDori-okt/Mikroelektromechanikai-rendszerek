#define ajto 2
#define led 7
#define w1 A1
#define w2 A2
#define sp 13

#include <Ethernet.h>
#include <MySQL_Connection.h>
#include <Servo.h>
#include <MySQL_Cursor.h>

Servo myservo;
int eso1=0;
int eso2=0;

/*MySQL-hez és hálózathoz */

byte mac_addr[] = { 0x08, 0x97, 0x98, 0xE5, 0x1F, 0x5A }; //08-97-98-E5-1F-5A

IPAddress server_addr(127,0,0,1);  // IP of the MySQL *server* here
char user[] = "root";              // MySQL user login username
char password[] = "";        // MySQL user login password

EthernetClient client;
MySQL_Connection conn((Client *)&client);




void setup() {
    myservo.attach(sp);
    pinMode(ajto, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    Serial.begin(9600);
    Serial.write("Hello");
    pinMode(w1, OUTPUT);
    pinMode(w2, OUTPUT);  
    digitalWrite(w1, HIGH); 
    digitalWrite(w2, HIGH); 
    
    //MySQL eleje
    while (!Serial); // wait for serial port to connect
    Ethernet.begin(mac_addr);
    Serial.println("Connecting...");
    if (conn.connect(server_addr, 3306, user, password)) {
    delay(1000);
    } else {
      Serial.println("Connection failed.");
    }
    conn.close();
      //MySQL vége
}

void loop() {
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  int state=0;
  int pre = 0;
  pre=state;
  state = digitalRead(ajto);
  
  if (state == HIGH && pre == LOW){
    cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 0)"); 
  }
  if(state == LOW && pre == HIGH){
    cur_mem->execute("INSERT INTO idopontok(ido, nyit) VALUES (NOW(), 1)");
  }
  delete cur_mem;
  /*
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
  */
  
}
