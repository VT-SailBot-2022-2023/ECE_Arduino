// StepperMotor.hpp

#ifndef StepperMotor_h
#define StepperMotor_h
#include <Arduino.h>

#define STEP_PRECISION 1.8

enum step_resolution {full, half, quarter, _8th, _16th, _32nd, _64th, _128th};
enum direction {left, right};

class StepperMotor {
  public:
  StepperMotor();

  ~StepperMotor();

  /*sets pins for the StepperMotor object
  @post the motor controller has it's pins setup correctly*/
  void setPins(uint8_t torqe0, uint8_t torqe1, uint8_t torqe2, uint8_t mode0, uint8_t mode1, uint8_t mode2, uint8_t dir, uint8_t step);

  /*Causes the motor to rotate to the desired angle
  @param angle - the angle we desire the motor to be pointing to
  @post the motor points to that angle*/
  bool rotate(float angle);

  float getAngle();

  private:
  /*current angle of the motor. Can go from 0 degrees to 360 degrees*/
  float currentAngle;

  /*step resolution of the stepper motor*/
  step_resolution motorRes;

  // pin data
  uint8_t TORQE0;              
  uint8_t TORQE1;
  uint8_t TORQE2;
  uint8_t MODE0;
  uint8_t MODE1;
  uint8_t MODE2;
  uint8_t STEP;
  uint8_t DIR;

  // Helper functions
  //-----------------

  /*sets the step resolution of the Stepper Motor based on the enum input
  @param newRes - the enum that changes the step reolution of the motor*/
  void setStepResolution(step_resolution newRes);

  /*sets direction of motor based on input.
  IMPORTANT: assuming left is 0 and right is 1*/
  void setStepDirection(direction lr);  
};

#endif