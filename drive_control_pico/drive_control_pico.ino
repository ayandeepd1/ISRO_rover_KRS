#define chan1p D27
#define chan1d D26

#define chan2p D21
#define chan2d D20

#define chan3p D8
#define chan3d D7

#define chan4p D4
#define chan4d D3

#define in1 D14
#define in2 D13
#define in3 D12
#define in4 D11

#define LED D25

const int chanp[4]={chan1p, chan2p, chan3p, chan4p};
const int chand[4]={chan1d, chan2d, chan3d, chan4d};
const int chani[4]={in1, in2, in3, in4};

int pw_speed=70;
bool dir_stat[4];

void dr1_drive(bool pw, bool dr){
  analogWrite(chan1p, pw*pw_speed);
  if(dir_stat[0])
    digitalWrite(chan1d, dr); 
  else
    digitalWrite(chan1d, !dr); 
}

void dr2_drive(bool pw, bool dr){
  analogWrite(chan2p, pw*pw_speed);
  if(dir_stat[1])
    digitalWrite(chan2d, dr); 
  else
    digitalWrite(chan2d, !dr); 
}

void dr3_drive(bool pw, bool dr){
  analogWrite(chan3p, pw*pw_speed);
  if(dir_stat[2])
    digitalWrite(chan3d, dr); 
  else
    digitalWrite(chan3d, !dr); 
}

void dr4_drive(bool pw, bool dr){
  analogWrite(chan4p, pw*pw_speed);
  if(dir_stat[3])
    digitalWrite(chan4d, dr); 
  else
    digitalWrite(chan4d, !dr); 
}
void set_dir(){
  dir_stat[0]=digitalRead(in1);
  dir_stat[1]=digitalRead(in2);
  dir_stat[2]=digitalRead(in3);
  dir_stat[3]=digitalRead(in4);
}
void run_forward(){
  dr1_drive(1,0);  
  dr2_drive(1,0);
  
  dr3_drive(1,0);
  dr4_drive(1,0);

}
void run_backward(){
  dr1_drive(1,1);
  dr2_drive(1,1);
  
  dr3_drive(1,1);
  dr4_drive(1,1);
  
}
void run_rotate_left(){
  dr1_drive(1,0);
  dr2_drive(1,0);
  
  dr3_drive(1,1);
  dr4_drive(1,1);
  
}
void run_rotate_right(){
  dr1_drive(1,1);
  dr2_drive(1,1);
  
  dr3_drive(1,0);
  dr4_drive(1,0);
  
}
void stop_all(){
  dr1_drive(0,0);
  dr2_drive(0,0);
  
  dr3_drive(0,0);
  dr4_drive(0,0);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  for(int i=0; i<4; i++){
  pinMode(chanp[i], OUTPUT);
  pinMode(chand[i], OUTPUT);
  pinMode(chani[i], INPUT_PULLUP);  
  }
  
}

void loop() {
  set_dir();
  digitalWrite(LED, HIGH);  
  
  if(Serial.available()>0){
    char c = Serial.read();
    //Serial.println(c);
    switch(c){
      case 'f':run_forward();Serial.print("ok\n");break;
      case 'b':run_backward();Serial.print("ok\n");break;
      case 'r':run_rotate_right();Serial.print("ok\n");break;
      case 'l':run_rotate_left();Serial.print("ok\n");break;
      case 's':stop_all();Serial.print("ok\n");break;    
    }
    Serial.flush();
  }
  
  digitalWrite(LED, LOW);
  
}
