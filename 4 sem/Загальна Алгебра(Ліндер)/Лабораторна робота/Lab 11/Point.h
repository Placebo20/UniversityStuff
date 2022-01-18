#pragma once

#include "../Lab1GA/Number.h"

/*!
* This class discribes point on elliptic curve
*/

class Point
{
private:
	/*!
	* This is coordinate x of our point
	*/
	LongArithmetic::Number _x;
	/*!
	* This is coordinate y of our point
	*/
	LongArithmetic::Number _y;
	/*!
	* If this parameter true - this is a point of infinity. False - this is normal point 
	*/
	bool endless;
public:
	/*!
	* This is basic constructer of our class. It sets A = 0, B = 0, endless = true
	*/
	Point () : _x{ LongArithmetic::Number("0") }, _y{ LongArithmetic::Number("0") }, endless{ true } {}
	/*!
	* This is constructer of our class. It has two parameters: first and second coordinate of our point. Parameter endless sets false 
	*/
	Point(const LongArithmetic::Number& x, const LongArithmetic::Number& y) : _x{ x }, _y{ y }, endless{ false } {}
	/*!
	* This function sets coordanate x
	*/
	void setX(const LongArithmetic::Number& x);
	/*!
	* This function sets coordanate y
	*/
	void setY(const LongArithmetic::Number& y);
	/*!
	* This function returns coordanate x
	*/
	LongArithmetic::Number x();
	/*!
	* This function returns coordanate y
	*/
	LongArithmetic::Number y();
	/*!
	* This function tranforms point into point of infinity
	*/
	void make_endless();
	/*!
	* This function tranforms point into normal point
	*/
	void make_normal(const LongArithmetic::Number& x, const LongArithmetic::Number& y);
	/*!
	* This function returns true, if our point is a point of infinity, otherwise false
	*/
	bool is_endless();
};