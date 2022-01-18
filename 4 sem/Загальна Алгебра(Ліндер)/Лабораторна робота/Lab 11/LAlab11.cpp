#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../Lab1GA/Number.h"
#include "../Lab1GA/Calculator.h"
#include "Point.h"
#include "../Lab1GA/doctest.h"
#include "EllipticCurve.h"
#include <string>

using namespace LongArithmetic;

TEST_CASE("Is point on curve") {
	EllipticCurve e1(Number("1"), Number("0"), Number("13"));
	e1.setA(Number("0"));
	CHECK(e1.a() == Number("1"));
	CHECK(e1.b() == Number("0"));
	CHECK(e1.Modul() == Number("13"));
	Point g;
	g.make_normal(Number("7"), Number("8"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("6"));
	g.setY(Number("12"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("10"));
	g.setY(Number("10"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("3"));
	g.setY(Number("11"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("7"));
	g.setY(Number("8"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("9"));
	g.setY(Number("6"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("11"));
	g.setY(Number("4"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("8"));
	g.setY(Number("0"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("3"));
	g.setY(Number("2"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("0"));
	g.setY(Number("0"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("2"));
	g.setY(Number("6"));
	CHECK(e1.is_curve_point(g));

	g.setX(Number("2"));
	g.setY(Number("7"));
	CHECK(e1.is_curve_point(g));


	g.setX(Number("11"));
	g.setY(Number("11"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("12"));
	g.setY(Number("12"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("1"));
	g.setY(Number("1"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("2"));
	g.setY(Number("2"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("3"));
	g.setY(Number("3"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("1"));
	g.setY(Number("11"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("1"));
	g.setY(Number("10"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("2"));
	g.setY(Number("0"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("3"));
	g.setY(Number("0"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("2"));
	g.setY(Number("12"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("3"));
	g.setY(Number("12"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("11"));
	g.setY(Number("6"));
	CHECK(!e1.is_curve_point(g));

	g.setX(Number("11"));
	g.setY(Number("7"));
	CHECK(!e1.is_curve_point(g));
}

TEST_CASE("Check sum")
{
	EllipticCurve e1(Number("1"), Number("0"), Number("13"));
	Point g1(Number("6"), Number("1")), g2(Number("2"), Number("6"));
	CHECK(e1.Sum(g1, g2).x() == Number("9"));
	CHECK(e1.Sum(g1, g2).y() == Number("6"));

	g1 = Point(Number("0"), Number("0")); g2 = Point(Number("5"), Number("0"));
	CHECK(e1.Sum(g1, g2).x() == Number("8"));
	CHECK(e1.Sum(g1, g2).y() == Number("0"));

	g1 = Point(Number("2"), Number("6")); g2 = Point(Number("2"), Number("6"));
	CHECK(e1.Sum(g1, g2).x() == Number("9"));
	CHECK(e1.Sum(g1, g2).y() == Number("7"));

	g1 = Point(Number("4"), Number("4")); g2 = Point(Number("4"), Number("4"));
	CHECK(e1.Sum(g1, g2).x() == Number("9"));
	CHECK(e1.Sum(g1, g2).y() == Number("6"));
	
	g1 = Point(Number("3"), Number("2")); g2 = Point(Number("8"), Number("0"));
	CHECK(e1.Sum(g1, g2).x() == Number("11"));
	CHECK(e1.Sum(g1, g2).y() == Number("9"));

	g1 = Point(Number("8"), Number("0")); g2 = Point(Number("9"), Number("6"));
	CHECK(e1.Sum(g1, g2).x() == Number("6"));
	CHECK(e1.Sum(g1, g2).y() == Number("12"));

	g1 = Point(Number("6"), Number("1")); g2 = Point(Number("10"), Number("10"));
	CHECK(e1.Sum(g1, g2).x() == Number("11"));
	CHECK(e1.Sum(g1, g2).y() == Number("4"));

	g1 = Point(Number("11"), Number("4")); g2 = Point(Number("2"), Number("7"));
	CHECK(e1.Sum(g1, g2).x() == Number("3"));
	CHECK(e1.Sum(g1, g2).y() == Number("2"));

	g1 = Point(Number("11"), Number("4")); g2 = Point(Number("6"), Number("1"));
	CHECK(e1.Sum(g1, g2).x() == Number("0"));
	CHECK(e1.Sum(g1, g2).y() == Number("0"));

	g1 = Point(Number("7"), Number("8")); g2 = Point(Number("11"), Number("9"));
	CHECK(e1.Sum(g1, g2).x() == Number("4"));
	CHECK(e1.Sum(g1, g2).y() == Number("9"));

	g1 = Point(Number("9"), Number("7")); g2 = Point(Number("4"), Number("9"));
	CHECK(e1.Sum(g1, g2).x() == Number("9"));
	CHECK(e1.Sum(g1, g2).y() == Number("6"));

	g1 = Point(Number("7"), Number("8")); g2 = Point(Number("6"), Number("12"));
	CHECK(e1.Sum(g1, g2).x() == Number("3"));
	CHECK(e1.Sum(g1, g2).y() == Number("2"));

	g1 = Point(Number("11"), Number("9")); g2 = Point(Number("0"), Number("0"));
	CHECK(e1.Sum(g1, g2).x() == Number("6"));
	CHECK(e1.Sum(g1, g2).y() == Number("1"));

	g1 = Point(Number("0"), Number("0")); g2 = Point(Number("0"), Number("0"));
	CHECK(e1.Sum(g1, g2).is_endless());

	g1 = Point(Number("2"), Number("7")); g2 = Point(Number("2"), Number("6"));
	CHECK(e1.Sum(g1, g2).is_endless());

	g1 = Point(Number("3"), Number("11")); g2 = Point(Number("3"), Number("2"));
	CHECK(e1.Sum(g1, g2).is_endless());

	g1 = Point(Number("4"), Number("9")); g2 = Point(Number("4"), Number("4"));
	CHECK(e1.Sum(g1, g2).is_endless());

	g1.make_endless();
	g2 = Point(Number("0"), Number("0"));
	CHECK(e1.Sum(g1, g2).x() == g2.x());
	CHECK(e1.Sum(g1, g2).y() == g2.y());

	g2 = Point(Number("3"), Number("2"));
	CHECK(e1.Sum(g1, g2).x() == g2.x());
	CHECK(e1.Sum(g1, g2).y() == g2.y());

	g2 = Point(Number("3"), Number("11"));
	CHECK(e1.Sum(g1, g2).x() == g2.x());
	CHECK(e1.Sum(g1, g2).y() == g2.y());
}