#include <IRremote.h>
IRrecv irrecv(3);
int ENA = 6;
int IN1 = 2;
int IN2 = 4;

int ENB = 5;
int IN3 = 7;
int IN4 = 8;
#define MotorASpeedLF 80      
#define MotorBSpeedLF 80  
#define MotorASpeed 80  
#define MotorBSpeed 80  
bool lineFollowingMode = true;

int Sensor1 = 0;
int Sensor2 = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(10, INPUT);
  irrecv.enableIRIn();
  Serial.begin(9600);
}

void loop() {
  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
    if (irrecv.decode()){ 
    Serial.println(irrecv.decodedIRData.decodedRawData);
    switch(irrecv.decodedIRData.decodedRawData){
      case 568261889:
      //move forward
      if(!lineFollowingMode){
            digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, MotorASpeed);
    analogWrite(ENB, MotorBSpeed);
      delay(1000);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
      }
      break;
       case 701955329:
      //move backword
          if(!lineFollowingMode){
             digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, MotorASpeed);
    analogWrite(ENB, MotorBSpeed);
      delay(1000);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
          }
      break;
      case 1905196289:
      //move right
          if(!lineFollowingMode){
         digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, MotorASpeed);
    analogWrite(ENB, MotorBSpeed / 2);  // Reduce speed of the right motor
    //Serial.println("Move right");
      delay(1000);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
          }
      break;
      case 1888484609:
      //move left{
      if(!lineFollowingMode){
            digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, MotorASpeed / 2);  // Reduce speed of the left motor
    analogWrite(ENB, MotorBSpeed);
   // Serial.println("Move left");
     delay(1000);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, LOW);
          digitalWrite(IN3, LOW);
          digitalWrite(IN4, LOW);
          analogWrite(ENA, 0);
          analogWrite(ENB, 0);
    }
      break;
      case 601685249:
        lineFollowingMode = !lineFollowingMode;
        delay(500);
        break;

    }
     irrecv.resume(); 
     }

  Sensor1 = digitalRead(A0);//left
  Sensor2 = digitalRead(10);//right
  if (lineFollowingMode){
  if (Sensor1 == HIGH && Sensor2 == HIGH) {
    // IR is on the black line
    // Stop both Motors
    digitalWrite(IN1, LOW);//left forward
    digitalWrite(IN2, LOW);//left backword
    digitalWrite(IN3, LOW);//right backword
    digitalWrite(IN4, LOW);//right forward
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
     
 delay(10);
    
    //Serial.println("Both IR sensors are on the black line - stop");
  } else if (Sensor1 == LOW && Sensor2 == LOW) {
    // IR not on the black line
   
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, MotorASpeedLF);
    analogWrite(ENB, MotorBSpeedLF);
      
   delay(10);
   // Serial.println("IR not on the black line - go forward");
  } else if (Sensor1 == LOW && Sensor2 == HIGH) {
    // IR on the RIGHT
    
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA, MotorASpeedLF);
    analogWrite(ENB, MotorBSpeedLF / 2);  // Reduce speed of the right motor
   // Serial.println("Move right");
      delay(10);
     
  } else if (Sensor1 == HIGH && Sensor2 == LOW) {
    // IR on the LEFT
    
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA, MotorASpeedLF / 2);  // Reduce speed of the left motor
    analogWrite(ENB, MotorBSpeedLF);

      delay(10);
   // Serial.println("Move left");
  }
  }

}
