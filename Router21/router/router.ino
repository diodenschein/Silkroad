
#include "TimerOne.h" // https://github.com/PaulStoffregen/TimerOne.git

//Pin definitions
#define DIRECTIONPIN 2
#define TURNPIN  3
#define BRAKEPIN 4
#define SPEEDPIN 5
#define ENDSTOP1 6
#define ENDSTOP2 7


//default pwm Speeds
#define SLOW 127
#define FAST 129

#define DEFAULTTIMEOUT 15 //seconds

//global speed variable
volatile uint8_t fastness = SLOW;
volatile uint8_t timeout = DEFAULTTIMEOUT;

void fullstop(){
  //insert ramp if nessesary
  analogWrite(SPEEDPIN, 0);
  digitalWrite(TURNPIN,HIGH);
  delay(200); //wait for bouncing
  digitalWrite(BRAKEPIN,LOW);  
}

void go(){
  digitalWrite(BRAKEPIN, HIGH);
  delay(200); //wait for bouncing
  analogWrite(SPEEDPIN, fastness);
  digitalWrite(TURNPIN,LOW);
}

void dir_to_one(){
    analogWrite(DIRECTIONPIN, LOW);
}

void dir_to_two(){
    analogWrite(DIRECTIONPIN, HIGH);
}

void error(){
 //handle this 
  while (1){

  } 
}

void SetTimeout(){
 Timer1.stop();
 timeout = DEFAULTTIMEOUT;
 Timer1.restart(); 
}

void NextSecond(){
  if (timeout){
    timeout--;
  }
  else{
    fullstop();
    error(); 
    Timer1.stop();
  }
}


void setup(){
  pinMode(DIRECTIONPIN, OUTPUT);
  pinMode(TURNPIN, OUTPUT);
  pinMode(BRAKEPIN, OUTPUT);
  pinMode(SPEEDPIN, OUTPUT);
  pinMode(ENDSTOP1, INPUT_PULLUP);
  pinMode(ENDSTOP2, INPUT_PULLUP);
  
  Timer1.initialize(10000000);
  Timer1.attachInterrupt(NextSecond);
  
  
  //fastness is globally set to SLOW
  dir_to_one();
  go();
  SetTimeout();
  while(digitalRead(!ENDSTOP1)){
    
  }
  fullstop; 
}


void loop(){
  
  
  //doo the right thing 



}



