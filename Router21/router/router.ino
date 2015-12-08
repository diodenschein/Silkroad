

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

//global speed variable
volatile uint8_t fastness = SLOW;

void fullstop(){
  //insert ramp if nessesary
  analogWrite(SPEEDPIN, 0);
  digitalWrite(TURNPIN,HIGH);
  delay_ms(200);
  digitalWrite(BRAKEPIN,LOW);  
}

void go(){
  digitalWrite(BRAKEPIN, HIGH);
  delay_ms(200);
  analogWrite(SPEEDPIN, fastness);
  digitalWrite(TURNPIN,LOW);
}

void to_one(){
    analogWrite(DIRPIN, LOW);
}

void to_two(){
    analogWrite(DIRPIN, HIGH);
}

void setup(){
  pinMode(DIRECTIONPIN, OUTPUT);
  pinMode(TURNPIN, OUTPUT);
  pinMode(BRAKEPIN, OUTPUT);
  pinMode(SPEEDPIN, OUTPUT);
  pinMode(ENDSTOP1, INPUT_PULLUP);
  pinMode(ENDSTOP2, INPUT_PULLUP);
  
  //fastness is globally set to SLOW
  to_one();
  go();
  while(digitalRead(!ENDSTOP1)){
    
  }
  fullstop; 
}


void loop(){
  
  
  



}



