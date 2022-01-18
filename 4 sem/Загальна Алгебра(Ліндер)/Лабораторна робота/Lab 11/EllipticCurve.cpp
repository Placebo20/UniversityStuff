#include "EllipticCurve.h"
#include "../Lab1GA/Calculator.h"
#include "../Lab1GA/Number.h"
#include <iostream>

EllipticCurve::EllipticCurve(const LongArithmetic::Number& a, const LongArithmetic::Number& b, const LongArithmetic::Number& mod) : _a( a ), _b( b ), modul( mod )
{
	try
	{
		if (mod > LongArithmetic::Number("2")) EllipticCurve::calculator = new LongArithmetic::Calculator(mod);
		else throw std::exception();
	}
	catch (const std::exception&)
	{
		std::cerr << "modul < 3" << std::endl;
		modul = LongArithmetic::Number("3"); calculator = new LongArithmetic::Calculator(modul);
	}
	try
	{
		if (calculator->Plus(calculator->Multiplication(LongArithmetic::Number("4"), calculator->Multiplication(calculator->Multiplication(a, a), a)), calculator->Multiplication(LongArithmetic::Number("27"), calculator->Multiplication(b, b))) == LongArithmetic::Number("0")) {
			throw std::exception();
		}
		else {
			EllipticCurve::_a = a;
			EllipticCurve::_b = b;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "4*A*A*A + 27*B*B = 0" << std::endl;
		EllipticCurve::_a = LongArithmetic::Number("1");
		EllipticCurve::_b = LongArithmetic::Number("0");
	}
}

bool EllipticCurve::is_curve_point(Point x)
{
	if (x.is_endless()) return true;
	if (calculator->Multiplication(x.y(), x.y()) == calculator->Plus(calculator->Plus(calculator->Multiplication(EllipticCurve::_a, x.x()), EllipticCurve::_b), calculator->Multiplication(calculator->Multiplication(x.x(), x.x()), x.x()))) {
		return true;
	}
	return false;
}
void EllipticCurve::setA(const LongArithmetic::Number& a)
{
	try
	{
		if (calculator->Plus(calculator->Multiplication(LongArithmetic::Number("4"), calculator->Multiplication(calculator->Multiplication(a, a), a)), calculator->Multiplication(LongArithmetic::Number("27"), calculator->Multiplication(_b, _b))) == LongArithmetic::Number("0")) {
			throw std::exception();
		}
		else {
			EllipticCurve::_a = a;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "4*A*A*A + 27*B*B = 0" << std::endl;
	}
}
void EllipticCurve::setB(const LongArithmetic::Number& b)
{
	try
	{
		if (calculator->Plus(calculator->Multiplication(LongArithmetic::Number("4"), calculator->Multiplication(calculator->Multiplication(_a, _a), _a)), calculator->Multiplication(LongArithmetic::Number("27"), calculator->Multiplication(b, b))) == LongArithmetic::Number("0")) {
			throw std::exception();
		}
		else {
			EllipticCurve::_b = b;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "4*A*A*A + 27*B*B = 0" << std::endl;
	}
}
void EllipticCurve::setModul(const LongArithmetic::Number& mod)
{
	EllipticCurve::calculator->SetModulus(mod);
	EllipticCurve::modul = mod;
}
LongArithmetic::Number EllipticCurve::a()
{
	return EllipticCurve::_a;
}
LongArithmetic::Number EllipticCurve::b()
{
	return EllipticCurve::_b;
}
LongArithmetic::Number EllipticCurve::Modul()
{
	return EllipticCurve::modul;
}
Point EllipticCurve::Sum(Point p1, Point p2)
{
	try
	{
	if (!EllipticCurve::is_curve_point(p1) || !EllipticCurve::is_curve_point(p2)) throw std::exception();
	if (p1.is_endless()) return p2;
	if (p2.is_endless()) return p1;
	Point p;
	if (!(p1.x() == p2.x())) {
		LongArithmetic::Number m("0");
		p = Point(LongArithmetic::Number("0"), LongArithmetic::Number("0"));
		m = calculator->ModuloDivision(calculator->Minus(p2.y(), p1.y()), calculator->Minus(p2.x(), p1.x()));
		p.setX(calculator->Minus(calculator->Minus(calculator->Multiplication(m, m), p1.x()), p2.x()));
		p.setY(calculator->Minus(calculator->Multiplication(m, calculator->Minus(p1.x(), p.x())), p1.y()));
		return p;
	}
	else {
		if (!(p1.y() == p2.y())) return p;
		else if (!(p1.y() == LongArithmetic::Number("0"))) {
			LongArithmetic::Number m("0");
			p = Point(LongArithmetic::Number("0"), LongArithmetic::Number("0"));
			m = calculator->ModuloDivision(calculator->Plus(calculator->Multiplication(calculator->Multiplication(p1.x(), p1.x()), LongArithmetic::Number("3")), EllipticCurve::_a), calculator->Multiplication(LongArithmetic::Number("2"), p1.y()));
			p.setX(calculator->Minus(calculator->Minus(calculator->Multiplication(m, m), p1.x()), p2.x()));
			p.setY(calculator->Minus(calculator->Multiplication(m, calculator->Minus(p1.x(), p.x())), p1.y()));
			return p;
		}
		else return p;
	}
    }
	catch (const std::exception&)
	{
		std::cerr << "Points are not on a curve" << std::endl;
	}
}

Point EllipticCurve::Inverse(Point p)
{
	try
	{
		if (!EllipticCurve::is_curve_point(p)) throw std::exception();
		if (p.is_endless()) return p;
		if (p.y() == LongArithmetic::Number("0")) {
			return p;
		}
		else {
			p.setY(calculator->Minus(modul,p.y()));
			return p;
		}
	}
	catch (const std::exception&)
	{
		std::cerr << "Point is not on a curve" << std::endl;
	}
}