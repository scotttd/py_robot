/*
	 TankDrive.cpp - Library to create TankDrive
	 Created by Scott Davidson, June 28 2016.
	 Released into the public domain
*/

#include <Arduino.h>
#include "TankDrive.h"

setupPins ()
{
	// set all the motor control pins to outputs
	pinMode(_speedPinLeft, OUTPUT);
    pinMode(_speedPinRight, OUTPUT);
    pinMode(_forwardPinLeft, OUTPUT);
    pinMode(_reversePinLeft, OUTPUT);
    pinMode(_forwardPinRight, OUTPUT);
    pinMode(_reversePinRight, OUTPUT);

}

TankDrive::TankDrive ()
{
	_speedPinLeft = 10;
	_speedPinRight= 5;
	_forwardPinLeft = 9;
	_reversePinLeft = 8;
	_forwardPinRight = 7;
	_reversePinRight = 6;
	
	setupPins();
}

TankDrive::TankDrive(int speedPinLeft, int speedPinRight, int forwardPinRight, int reversePinRight, int forwardPinLeft, int reversePinLeft):_trapezoid()
{
	// connect motor controller pins to Arduino digital pins
	// motor Left
	_speedPinLeft = speedPinLeft;
	_forwardPinLeft = forwardPinLeft;
	_reversePinLeft = reversePinLeft;
	// motor two
	_speedPinRight = speedPinRight;
	_forwardPinRight = forwardPinRight;
	_reversePinRight = reversePinRight;

	setupPins();
}


void TankDrive::fullStop ()
{
  // now turn off motors
  digitalWrite(_forwardPinLeft, LOW);
  digitalWrite(_reversePinLeft, LOW);
  digitalWrite(_forwardPinRight, LOW);
  digitalWrite(_reversePinRight, LOW);
}

void TankDrive::doDrive(int driveTime)
{
	  long startTime = millis();
	  long cTime = 0;
	  int cSpeed = 150;


	 while (millis() - startTime < driveTime) {
		digitalWrite(_speedPinLeft, cSpeed);
		digitalWrite(_speedPinRight, cSpeed);
	 }
	 fullStop();
 }

void TankDrive::driveForward(int driveTime)
{
  // Set motor directions to move forward
  digitalWrite(_forwardPinLeft, HIGH);
  digitalWrite(_reversePinLeft, LOW);
  digitalWrite(_forwardPinRight, HIGH);
  digitalWrite(_reversePinRight, LOW);

  char b;
  Serial.println(String(_speedPinLeft));

  doDrive (driveTime);
}

void TankDrive::driveReverse(int driveTime)
{
  // Set motor directions to move in reverse
  digitalWrite(_forwardPinLeft, LOW);
  digitalWrite(_reversePinLeft, HIGH);
  digitalWrite(_forwardPinRight, LOW);
  digitalWrite(_reversePinRight, HIGH);
  
  doDrive (driveTime);
}


void TankDrive::turnLeft(int turnAngle)
{
	 // Set motor directions to Turn Left
	  digitalWrite(_forwardPinLeft, LOW);
	  digitalWrite(_reversePinLeft, LOW);
	  digitalWrite(_forwardPinRight, HIGH);
	  digitalWrite(_reversePinRight, LOW);
}

void TankDrive::turnRight(int turnAngle)
{
	// Set motor directions to turn Right
	  digitalWrite(_forwardPinLeft, HIGH);
	  digitalWrite(_reversePinLeft, LOW);
	  digitalWrite(_forwardPinRight, LOW);
	  digitalWrite(_reversePinRight, LOW);
}
/*
int TankDrive::TimeAccel() const
{
	return m_trapezoid._timeAccel;
}

void TankDrive::SetTimeAccel(int timeAccel)
{
	m_trapezoid.setAcceleration(timeAccel);
}
*/
Trapezoid& TankDrive::getTrapezoid()
{
	return _trapezoid;
}

/*const Trapezoid& TankDrive::GetTrapazoid()
{
	return m_trapazoid;
}

void Trapezoid::SetTrapezoid(const Trapezoid& trapezoid)
{
	if (trapezoid.IsValid())
		m_trapezoid = trapezoid;
}

*/
