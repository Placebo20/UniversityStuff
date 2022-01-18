#include "Point.h"

void Point::setX(const LongArithmetic::Number& x)
{
	try
	{
		if (endless) throw std::exception();
		else _x = x;
	}
	catch (const std::exception&)
	{
		std::cout << "This is the point of infinity" << std::endl;
	}
	
}
void Point::setY(const LongArithmetic::Number& y)
{
	try
	{
		if (endless) throw std::exception();
		else _y = y;
	}
	catch (const std::exception&)
	{
		std::cout << "This is the point of infinity" << std::endl;
	}
}
LongArithmetic::Number Point::x()
{
	try
	{
		if (endless) throw std::exception();
		else return _x;
	}
	catch (const std::exception&)
	{
		std::cout << "This is the point of infinity" << std::endl;
	}
}
LongArithmetic::Number Point::y()
{
	try
	{
		if (endless) throw std::exception();
		else return _y;
	}
	catch (const std::exception&)
	{
		std::cout << "This is the point of infinity" << std::endl;
	}
}
void Point::make_endless()
{
	Point::endless = true;
}
void Point::make_normal(const LongArithmetic::Number& x, const LongArithmetic::Number& y)
{
	Point::endless = false;
	Point::_x = x;
	Point::_y = y;
}
bool Point::is_endless()
{
	return Point::endless;
}