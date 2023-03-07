#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN   9
#define SS_PIN    10

MFRC522 mfrc522(SS_PIN, RST_PIN);

String read_rfid;
String ok_rfid_1="45e5ea2965c80";
String ok_rfid_2="45d2a9aed5c80";
int lock = 8;
int lock2 = 8;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  SPI.begin();
  mfrc522.PCD_Init();

  pinMode(lock, OUTPUT);
  pinMode(lock2, OUTPUT);
  digitalWrite(lock, HIGH);
  digitalWrite(lock2, HIGH);
}

void dump_byte_array(byte *buffer, byte bufferSize){
  read_rfid="";
  for (byte i=0; i<bufferSize; i++){
    read_rfid=read_rfid + String(buffer[i], HEX);
  }
}

void open_lock(){
  digitalWrite(lock,LOW);
  delay(3000);
  digitalWrite(lock,HIGH);
}

void close_lock2(){
  digitalWrite(lock2,LOW);
  delay(3000);
  digitalWrite(lock2,HIGH);
}

void loop() {

  if ( ! mfrc522.PICC_IsNewCardPresent())
      return;

  if ( ! mfrc522.PICC_ReadCardSerial())
      return;

dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
  Serial.println(read_rfid);
  if (read_rfid==ok_rfid_1){
    open_lock();
    Serial.println("OK");
  }

  Serial.println(read_rfid);
  if (read_rfid==ok_rfid_2){
    close_lock2();
    Serial.println("OK");
  }
}
