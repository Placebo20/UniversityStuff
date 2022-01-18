#pragma once
#include "/PROJECTS/GA-Lab/LabGeneralAlgebra/lab11/EllipticCurve.h"
#include "/PROJECTS/GA-Lab/LabGeneralAlgebra/Lab1GA/generators.h"
#include <utility>
#include <random>

namespace OrderOfEllipticCurve {

	class OrderOfEllipticCurve {
	public:
		EllipticCurve mainEllipticCurve;
		LongArithmetic::Number* m;
		std::vector<std::pair<LongArithmetic::Number,Point>> jPoints;
		LongArithmetic::Number* M;

		OrderOfEllipticCurve(const LongArithmetic::Number& a, const LongArithmetic::Number& b, const LongArithmetic::Number& mod);
		bool isPrime(const LongArithmetic::Number& mod);
		bool isPrime(const int mod);
		void chooseM();
		Number babyGiant(Point startPoint);
		std::vector<LongArithmetic::Number> primeFactorization(LongArithmetic::Number n);
		LongArithmetic::Number lcm(LongArithmetic::Number L, LongArithmetic::Number M);
	};
}