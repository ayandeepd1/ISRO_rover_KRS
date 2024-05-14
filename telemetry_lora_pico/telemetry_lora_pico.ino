#include <SPI.h>
#include <LoRa.h>

#define lora_freq 443E6

#define SCK 2
#define MISO 4
#define MOSI 3

#define NSS 5
#define NRESET 7
#define DIO0 6

char buff[100];
int pack_rssi, i;
volatile bool is_recv=0;

long t1=0;
//SPISettings spisettings(1000000);// MSBFIRST, SPI_MODE0);

void onReceive(int packetSize) {
  digitalWrite(LED_BUILTIN, HIGH);
  is_recv=1;
  for (i = 0; i < packetSize; i++) {
    buff[i]=(char)LoRa.read();
  }
  buff[i]=='\0';
  pack_rssi=LoRa.packetRssi();
  digitalWrite(LED_BUILTIN, LOW);
}

void lora_setup(){
  SPI.setRX(MISO);
  SPI.setCS(NSS);
  SPI.setSCK(SCK);
  SPI.setTX(MOSI);
  SPI.begin(true);
  LoRa.setSPI(SPI);
  LoRa.setPins(NSS, NRESET, DIO0);
  Serial.print("LoRa Receiver: ");
  if (!LoRa.begin(lora_freq)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.onReceive(onReceive);
  LoRa.dumpRegisters(Serial);
  LoRa.receive();
  for(int i=0; i<5; i++){
    pinMode(LED_BUILTIN,HIGH);
    Serial.println("Ready");  
    delay(100);
    pinMode(LED_BUILTIN,LOW);
    delay(100);
  }
}

void setup() {
  Serial.begin(1000000);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);  
  for(int i=0; i<5; i++){
    Serial.println("ready");
    delay(100);
  }
    
}
void setup1() {
  delay(50);
  lora_setup();
}

void loop() {
  
  if(is_recv){
    long t2=millis();
    //Serial.print("Received packet: \"");
    Serial.write(buff, i);
    Serial.println();
    //Serial.printf("\" with RSSI %d ", pack_rssi);
    //Serial.printf("ping: %d\n", t2-t1);
    t1=t2;
    is_recv=0;
  }
  
}
void loop1(){  
  
}
