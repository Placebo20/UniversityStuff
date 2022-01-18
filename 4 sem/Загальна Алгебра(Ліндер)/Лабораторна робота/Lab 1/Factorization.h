#pragma once

#include <vector>
#include <utility>
using namespace std;

#include "Calculator.h"

namespace LongArithmetic {
	class Factorization
	{
	public:

		const static pair<Number, Number> NO_FACTOR;

		Factorization();

		// return all factors
		vector<Number> NaiveFactorization(const Number& number);

		// Euclidean algorithm (return 0 if numbers aren't both pozitive)
		Number GCD(const Number& number1, const Number& number2);

		// return pair of factors (NO_FACTOR if failed)
		pair<Number, Number> PollardRhoFactorization(const Number& number);

		// return all prime factors (with repeating if it exists)
		vector<Number> PrimeFactors(const Number& number);

	private:

		Calculator self_mod;

		// recursive part of PrimeFactors()
		void RecursiveSearchingPrimeFactors(const Number& number, vector<Number>* list);
	};
}