/*
	 Trapezoid.h - Library to create Trapezoid Motion Profiles
	 Created by Scott Davidson, June 28 2016.
	 Released into the public domain
*/

#ifndef Trapezoid_h
#define Trapezoid_h


class Trapezoid
{
	public:
	    Trapezoid();
		Trapezoid(int timeAccel,int minSpeed,int maxSpeed,long startTime,long runTime);
		int setPoint(long cTime);
		void setRunTime(long runTime);
		void setAcceleration(int timeAccel);
		void setStartTime(long startTime);

		bool IsValid();
		int Status() { return 0; };

	//private:
		void updateTrapezoidValues();
		int _timeAccel;
		int _minSpeed;
		int _maxSpeed;
		long _startTime;
		long _runTime;
		float _addSpeed;
		int _timeMaxSpeed;
};

#endif
