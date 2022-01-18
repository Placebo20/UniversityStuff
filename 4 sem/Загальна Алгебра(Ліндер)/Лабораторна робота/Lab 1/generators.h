#pragma once
#include <vector>
#include "Number.h"
#include "Calculator.h"
#include <cmath>
#include <random>
#include <string>







static std::random_device d;
static std::mt19937 mers(d());
using namespace LongArithmetic;
class Generators
{
public:
	

	
	static Number gcd(Number a, Number b);
	static std::vector<Number> generators(const Number& number, char op);
	static std::vector<Number> prime_numbers(const Number& number);
	//static std::vector<Number> efficient_generator(const Number& number);
	static Number  efficient_generator( Number number);
	static Number pow(Number a, Number b);
	static Number power_modulus(Number a, Number b, Number mod);
	//static Number get_Random_value(Number number);
	static std::vector<Number> prime_factors( Number number);
	static Number sqrt_root(Number number);
private:

};

