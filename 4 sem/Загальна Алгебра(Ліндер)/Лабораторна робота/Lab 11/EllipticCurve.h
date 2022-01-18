#pragma once

#include "../Lab1GA/Number.h"
#include "Point.h"
#include "../Lab1GA/Calculator.h"

/*!
* This class discribes elliptic curve
*/

class EllipticCurve
{
private:
    /*!
    * This is a parameter A of our elliptic curve
    */
	LongArithmetic::Number _a;
	/*!
    * This is a parameter B of our elliptic curve
    */
	LongArithmetic::Number _b;
	/*!
    * This is module of our elliptic curve
    */
	LongArithmetic::Number modul;
	/*!
	* This is a class for our calculations
	*/
	LongArithmetic::Calculator* calculator;
public:
	/*!
	* This is constructer of our class. It has three parameters: parameter A, parameter B, module
	*/
	EllipticCurve(const LongArithmetic::Number& a, const LongArithmetic::Number& b, const LongArithmetic::Number& mod);
	/*!
	* This function returns true, if point is on a curve, otherwise - false
	*/
	bool is_curve_point(Point x);
	/*!
	* This function sets parameter A
	*/
	void setA(const LongArithmetic::Number& a);
	/*!
	* This function sets parameter B
	*/
	void setB(const LongArithmetic::Number& b);
	/*!
	* This function sets module
	*/
	void setModul(const LongArithmetic::Number& mod);
	/*!
	* This function returns parameter A
	*/
	LongArithmetic::Number a();
	/*!
	* This function returns parameter B
	*/
	LongArithmetic::Number b();
	/*!
	* This function returns module
	*/
	LongArithmetic::Number Modul();
	/*!
	* This function returns sum of  two points on the ellptic curve
	*/
	Point Sum(Point p1, Point p2);
	/*!
	* This function returns inverse point
	*/
	Point Inverse(Point p);
};

