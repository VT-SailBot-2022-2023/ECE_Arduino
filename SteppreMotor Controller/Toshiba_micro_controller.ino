//////////////////////////////////////////////////////////////////////////////////////////////////
// TOSHIBA TB67S128FTG Stepper Motor Driver Carrier Interface
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "StepperMotor.hpp"

void setup() {
  // put your setup code here, to run once:

  // test for the Motor object
  Serial.begin(9600);
  StepperMotor motor1;
  Serial.println(motor1.getAngle());
  Serial.println("Required Angle : 0");
  motor1.setPins(2, 3, 4, 5, 6, 7, 8, 9);
  Serial.println(motor1.getAngle());

  motor1.rotate(270);
  Serial.print(motor1.getAngle());
  Serial.println("Required Angle : 270");
  delay(1000);

  Serial.println(motor1.getAngle());
  motor1.rotate(90);
  Serial.println(motor1.getAngle());
  Serial.println("Required Angle : 90");
  delay(1000);

  motor1.rotate(180);
  Serial.println(motor1.getAngle());
  Serial.println("Required Angle : 180");
  delay(1000);

  motor1.rotate(300);
  Serial.println(motor1.getAngle());
  Serial.println("Required Angle : 300");
  delay(1000);

  motor1.rotate(23);
  Serial.println(motor1.getAngle());
  Serial.println("Required Angle : 23");

  while(true) {
    delay(1000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
