#include "vector2D.h"
#include "math.h"


Vector2D::Vector2D(): XValue(0), YValue(0)
{
}

Vector2D::Vector2D(double x, double y): XValue(x), YValue(y)
{
}

Vector2D::Vector2D(const Vector2D& copyVector)
{
	XValue=copyVector.XValue;
	YValue=copyVector.YValue;
}

void Vector2D::set(double x, double y)
{
	XValue=x;
	YValue=y;
}

void Vector2D::set(const Vector2D& copyVector)
{
	XValue=copyVector.XValue;
	YValue=copyVector.YValue;
}

double Vector2D::magnitude() const
{
	return sqrt(XValue*XValue + YValue*YValue);
}

Vector2D Vector2D::unitVector() const
{
	double divideBy = magnitude();

	if(divideBy==0)
	{
		return Vector2D(0,0);
	}
		else
	return Vector2D(XValue/divideBy, YValue/divideBy);
}

Vector2D Vector2D::operator+(const Vector2D& addVector) const
{
	return Vector2D (XValue+addVector.XValue,YValue+addVector.YValue);
}

void Vector2D::operator+=(const Vector2D& addVector)
{
 	XValue+=addVector.XValue;
	YValue+=addVector.YValue;
}

void Vector2D::operator-=(const Vector2D& addVector)
{
	XValue-=addVector.XValue;
	YValue-=addVector.YValue;
}

void Vector2D::operator/=(double divisor)
{
	XValue/=divisor;
	YValue/=divisor;
}

void Vector2D::operator*=(double multiplier)
{
	XValue*=multiplier;
	YValue*=multiplier;
}

void Vector2D::operator*=(int multiplier)
{
	XValue*=multiplier;
	YValue*=multiplier;
}


Vector2D Vector2D::operator-(const Vector2D& addVector) const
{
	return Vector2D (XValue-addVector.XValue,YValue-addVector.YValue);
}

Vector2D Vector2D::operator -() const
{
	return Vector2D (-this->XValue,-this->YValue);
}

Vector2D Vector2D::operator*(double multiplier) const
{
	return Vector2D(XValue*multiplier,YValue*multiplier);
}

Vector2D Vector2D::operator*(int multiplier) const
{
	return Vector2D(XValue*multiplier,YValue*multiplier);
}

double Vector2D::operator*(const Vector2D& otherVector) const
{
	return XValue*otherVector.XValue+YValue*otherVector.YValue;
}

bool Vector2D::operator==(const Vector2D& otherVector) const
{
	return (XValue == otherVector.XValue && YValue == otherVector.YValue);
}

Vector2D Vector2D::operator/(double divisor) const
{
	return Vector2D(XValue/divisor,YValue/divisor);
}

double Vector2D::angle() const
// Working in radians
{
	double answer;

	answer=atan2(XValue, YValue);

	while(answer<0) answer+=6.28319;
	while(answer>=6.28319) answer-=6.28319;

	return answer;
}

void Vector2D::setBearing(double angle, double magnitude)
{
// Working in radians
	XValue = magnitude*sin(angle);
	YValue = magnitude*cos(angle);
}

bool Vector2D::isParallelTo(const Vector2D &otherVector) const
{
	if(this->unitVector() == otherVector.unitVector()) return true;
	if(this->unitVector() == -otherVector.unitVector()) return true;
	else return false;
}

bool Vector2D::isPerpendicularTo(const Vector2D &otherVector) const
{
	return((*this*otherVector)==0);
}

Vector2D Vector2D::perpendicularVector() const
{
	return Vector2D(this->YValue, -this->XValue);
}

Vector2D Vector2D::rotatedBy(double angle) const
{
	double s = sin(angle);
	double c = cos(angle);
	return Vector2D(this->XValue * c - this->YValue*s, this->XValue * s + this->YValue * c);
	
}

Vector2D operator*(double multiplier, Vector2D v) 
{
	return v*multiplier;
}