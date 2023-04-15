#include "Arduino.h"
#include "StepperMotor.hpp"

  StepperMotor::StepperMotor() {
    //setting step resolution to full
    this->motorRes = full;
    this->currentAngle = 0;
  }

  StepperMotor::~StepperMotor() {
    this->rotate(1);
  }

  void StepperMotor::setPins(uint8_t torqe0, uint8_t torqe1, uint8_t torqe2, uint8_t mode0, uint8_t mode1, uint8_t mode2, uint8_t dir, uint8_t step) {
    //setting internal pin assignemnts
    this->TORQE0 = torqe0;
    this->TORQE1 = torqe1;
    this->TORQE2 = torqe2;

    this->MODE0 = mode0;
    this->MODE1 = mode1;
    this->MODE2 = mode2;

    this->STEP = step;
    this->DIR = dir;

    //setting outputs based on pins
    pinMode(MODE0, OUTPUT);
    pinMode(MODE1, OUTPUT);
    pinMode(MODE2, OUTPUT);

    pinMode(STEP, OUTPUT);
    pinMode(DIR, OUTPUT);
   
    pinMode(TORQE0, OUTPUT);
    pinMode(TORQE1, OUTPUT);
    pinMode(TORQE2, OUTPUT);

    setStepResolution(motorRes);
  }

void StepperMotor::setStepResolution(step_resolution newRes) {
  switch(newRes) {
    case full:
      digitalWrite(MODE2, LOW);
      digitalWrite(MODE1, LOW);
      digitalWrite(MODE0, LOW);
      break;
    case half:
      digitalWrite(MODE2, HIGH);
      digitalWrite(MODE1, LOW);
      digitalWrite(MODE0, LOW);
      break;
    case quarter:
      digitalWrite(MODE2, LOW);
      digitalWrite(MODE1, HIGH);
      digitalWrite(MODE0, LOW);
      break;
    case _8th:
      digitalWrite(MODE2, LOW);
      digitalWrite(MODE1, HIGH);
      digitalWrite(MODE0, HIGH);
      break;
    case _16th:
      digitalWrite(MODE2, HIGH);
      digitalWrite(MODE1, LOW);
      digitalWrite(MODE0, LOW);
      break;
    case _32nd:
      digitalWrite(MODE2, HIGH);
      digitalWrite(MODE1, LOW);
      digitalWrite(MODE0, HIGH);
      break;
    case _64th:
      digitalWrite(MODE2, HIGH);
      digitalWrite(MODE1, HIGH);
      digitalWrite(MODE0, LOW);
      break;
    case _128th:
      digitalWrite(MODE2, HIGH);
      digitalWrite(MODE1, HIGH);
      digitalWrite(MODE0, HIGH);
      break;
  }
}

void StepperMotor::setStepDirection(direction lr) {
  switch (lr) {
    case left:
      digitalWrite(this->DIR, LOW);
      break;
    case right:
      digitalWrite(this->DIR, HIGH);
      break;
  }
}

bool StepperMotor::rotate(float angle) {
  if (angle > 360) {
    return false;
  }

  if (this->currentAngle > 360) {
    this->currentAngle -= 360;
  }
  else if (this->currentAngle < 0) {
    this->currentAngle += 360;
  }

  float anglePlus = int(this->currentAngle + 180) % 360;
  direction direc;
  bool inc_dec;

  if (this->currentAngle >= anglePlus) {
    if (this->currentAngle >= angle) {
      direc = left;
      inc_dec = false;
    }
    else if (this->currentAngle < angle) {
      direc = right;
      inc_dec = true;
    }
  }
  else if (this->currentAngle < anglePlus) {
    if (this->currentAngle >= angle) {
      direc = right;
      inc_dec = false;
    }
    else if (this->currentAngle < angle) {
      direc = left;
      inc_dec = true;
    }
  }

  if (inc_dec == true) {
    while ((angle - this->currentAngle) > STEP_PRECISION) {
      digitalWrite(this->STEP, HIGH);
      delayMicroseconds(5);
      digitalWrite(this->STEP, LOW);
      delay(5);
      this->currentAngle += 1.8;
      if (this->currentAngle > 360) {
      this->currentAngle -= 360;
      }
      else if (this->currentAngle < 0) {
        this->currentAngle += 360;
      }
    }
  }
  else {
    while ((this->currentAngle - angle) > STEP_PRECISION) {
      digitalWrite(this->STEP, HIGH);
      delayMicroseconds(5);
      digitalWrite(this->STEP, LOW);
      delay(5);
      this->currentAngle -= 1.8;
      if (this->currentAngle > 360) {
      this->currentAngle -= 360;
      }
      else if (this->currentAngle < 0) {
        this->currentAngle += 360;
      }
    }
  }
  return true;
}

float StepperMotor::getAngle() {
  return this->currentAngle;
}
