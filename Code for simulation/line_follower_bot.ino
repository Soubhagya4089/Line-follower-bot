#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 3
#define IR_SENSOR_MID 4
#define IR_SENSOR_RED 2
#define IR_SENSOR_GREEN 12

#define MOTOR_SPEED 180

//Right motor
int enableRightMotor=6;
int rightMotorPin1=10;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=5;
int leftMotorPin1=9;
int leftMotorPin2=7;

void setup()
{
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   
}


void loop()
{

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  int midIRSensorValue = digitalRead(IR_SENSOR_MID);

  //track A and B1.
  //If both left and right sensors detects black line,(middle sensor not used) then go straight
  if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }

  //If left sensor detects black line,right sensor detects white line then go straight.
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW)
  {
    rotateMotor(MOTOR_SPEED, MOTOR_SPEED);
  }
  //If right sensor detects white line, left sensor detects white line then motor turns left 
  else if (rightIRSensorValue == LOW && leftIRSensorValue == LOW )
  {
      rotateMotor(MOTOR_SPEED,-MOTOR_SPEED); 
  }

  //track B2
  //If left sensor detects white line, right sensor black line go straight
  if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
      rotateMotor(MOTOR_SPEED,MOTOR_SPEED); 
  } 
  //If both the sensors detect white line, motor turns right
  else if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
      rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);
  }

  //track C1,C2
  if (rightIRSensorValue == LOW && leftIRSensorValue == LOW && midIRSensorValue == HIGH)
  {
      rotateMotor(MOTOR_SPEED,MOTOR_SPEED);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW && midIRSensorValue == HIGH)
  {
      rotateMotor(-MOTOR_SPEED,MOTOR_SPEED);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH && midIRSensorValue == HIGH)
  {
      rotateMotor(-MOTOR_SPEED,MOTOR_SPEED);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW && midIRSensorValue == HIGH)
  {
      rotateMotor(-MOTOR_SPEED,MOTOR_SPEED);
  }
  //track C3
  if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW && midIRSensorValue == HIGH)

}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}




