# Usage

run tests with ```make```

# Structure

## CommandListener

Facilitates the communication with the Android App and retrieves the new absolute orientation, the pen commands and the new current path to work on.
It also transmits the events and the new pen offset as feedback.

## Sensor Fusor

Takes the fast orientation delta from the mouse sensors and the slower absolute orientation update from the Android App and calculates a new absolute orientation as best as possible.

## MotionCoordinator

Calculates the new pen offset from the previous and current absolute orientation and the current path.

## InverseKinematicSolver

solves the IK.

## MotorController

Moves the motors to their intended positions.
