#include "../../StepperDriver/BasicStepperDriver.h"

double MOCK_ROTATION_RESULT[2];

BasicStepperDriver::BasicStepperDriver(int steps, int dir_pin, int step_pin)
:motor_steps(steps), dir_pin(dir_pin), step_pin(step_pin)
{}

BasicStepperDriver::BasicStepperDriver(int steps, int dir_pin, int step_pin, int enable_pin)
:motor_steps(steps), dir_pin(dir_pin), step_pin(step_pin), enable_pin(enable_pin)
{}

void BasicStepperDriver::init(void){ }

void BasicStepperDriver::calcStepPulse(void){ }

void BasicStepperDriver::setRPM(unsigned rpm){ }

unsigned BasicStepperDriver::setMicrostep(unsigned microsteps){ return microsteps; }

void BasicStepperDriver::setDirection(int direction){ }

void BasicStepperDriver::move(long steps){ }

void BasicStepperDriver::rotate(long deg){ MOCK_ROTATION_RESULT[this->dir_pin] += (long)deg; }

void BasicStepperDriver::rotate(double deg){ MOCK_ROTATION_RESULT[this->dir_pin] += deg; }

void BasicStepperDriver::enable(void){ }

void BasicStepperDriver::disable(void){ }

unsigned BasicStepperDriver::getMaxMicrostep(){
    return BasicStepperDriver::MAX_MICROSTEP;
}
