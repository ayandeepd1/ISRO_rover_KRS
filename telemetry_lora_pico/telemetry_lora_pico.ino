#include <SPI.h>
#include <LoRa.h>

#define lora_freq 443E6

#define SCK 2
#define MISO 4
#define MOSI 3

#define NSS 5
#define NRESET 7
#define DIO0 6

char buff[102400];
volatile int pack_rssi, pack_size;
volatile bool is_recv=0;

long t1=0;
//SPISettings spisettings(1000000);// MSBFIRST, SPI_MODE0);

void onReceive(int packetSize) {
  is_recv=1; digitalWrite(LED_BUILTIN,HIGH);
  pack_size=packetSize;
  for (int i = 0; i < packetSize; i++) {
    buff[i]=(char)LoRa.read();
  }
  //buff[packetSize]=='\n';
  pack_rssi=LoRa.packetRssi();
  
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
  //LoRa.dumpRegisters(Serial);
  LoRa.receive();
  for(int i=0; i<10; i++){
    digitalWrite(LED_BUILTIN,HIGH);
    Serial.println("Ready");  
    delay(100);
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
  }
}

void setup() {
  Serial.begin(1000000);
  pinMode(LED_BUILTIN, OUTPUT);
  while (!Serial);  
   
}

void loop() {
  if(is_recv){
    //long t2=millis();
    Serial.write(buff, pack_size);
    Serial.printf("\n");
    //Serial.printf("\n%d with RSSI %d \n", pack_size, pack_rssi);
    //Serial.printf("ping: %d\n", t2-t1);
    
    pack_size=0;
    is_recv=0;digitalWrite(LED_BUILTIN,LOW);
  }
}

void setup1() {
  delay(50);
  lora_setup();
}
void loop1(){  
  
}
