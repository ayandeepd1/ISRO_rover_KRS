#include <SPI.h>
#include <LoRa.h>

#define SCK 2
#define MISO 4
#define MOSI 3

#define NSS 5
#define NRESET 7
#define DIO0 6

char buff[100];
int pack_rssi, i;
volatile bool is_recv=0;

//SPISettings spisettings(1000000);// MSBFIRST, SPI_MODE0);
void onReceive(int packetSize) {
  is_recv=1;
  for (i = 0; i < packetSize; i++) {
    buff[i]=(char)LoRa.read();
  }
  buff[i]=='\0';
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
  if (!LoRa.begin(443E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.onReceive(onReceive);
  LoRa.dumpRegisters(Serial);
  LoRa.receive();
  Serial.println("Ready");  
}

void setup() {
  Serial.begin(115200);
  while (!Serial);  
}
void setup1() {
  delay(50);
  lora_setup();
}

void loop() {
  
  if(is_recv){
    Serial.print("Received packet: \"");
    Serial.print(buff);
    Serial.printf("\" with RSSI %d\n", pack_rssi);
    is_recv=0;
  }
  
}
void loop1(){  
  
}
