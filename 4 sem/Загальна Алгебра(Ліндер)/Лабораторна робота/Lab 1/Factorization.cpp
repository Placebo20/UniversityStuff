#include "Factorization.h"

namespace LongArithmetic {
	const pair<Number, Number> Factorization::NO_FACTOR = make_pair(Number("0"), Number("0"));

	// only for creating calculator object - it will be updated after all function calling
	Factorization::Factorization() : self_mod(Calculator(Number("1"))) {}

	vector<Number> Factorization::NaiveFactorization(const Number& number)
	{
		// ! added Number initializer because don't realized default constructor !
		vector<Number> factor_list = vector<Number>(0, Number("0"));

		if (number.GetSign() == Number::Sign::Plus)
		{
			// may be optimized with 4 lab var - calc sqrt(number) once time and don't calculate on each iteration
			for (Number i = Number("2"); /*at this place -> */ i * i <= number; i++)
			{
				// this can be changed at : ((number % i) == 0) (don't realized at 1st var)
				if (/*at this place ->*/((number / i) * i) == number)
				{
					factor_list.push_back(i);
				}
			}
		}

		return factor_list;
	}

	Number Factorization::GCD(const Number& number1, const Number& number2)
	{
		if (number1.GetSign() == Number::Sign::Plus && number2.GetSign() == Number::Sign::Plus)
		{
			// defining because Number don't has default constructor
			Number bigger = Number("0");
			Number smaller = Number("0");
			Number rest = Number("0");
			Number zero = Number("0");

			if (number1 > number2)
			{
				bigger = number1;
				smaller = number2;
			}
			else
			{
				bigger = number2;
				smaller = number1;
			}

			do
			{
				// this can be changed at : rest = bigger % smaller; (don't realized at 1st var)
				rest = bigger - (bigger / smaller) * smaller;
				
				// for next step
				bigger = smaller;
				smaller = rest;
			}
			// don't realized !=
			while(!(rest == zero));

			// last non-zero rest (changed for no-next step)
			return bigger;
		}
		else
		{
			return Number("0");
		}
	}

	pair<Number, Number> Factorization::PollardRhoFactorization(const Number& number)
	{
		if (number.GetSign() == Number::Sign::Plus)
		{
			self_mod.SetModulus(number);

			Number a = Number("2");
			Number b = Number("2");
			// defining because Number don't has default constructor
			Number d = Number("0");

			Number diff = Number("0");
			Number one = Number("1");

			do
			{
				// a = a^2 + 1 mod n
				a = a * a;
				a++;
				a = self_mod.Modul(a);

				// b = b^2 + 1 mod n (twice)
				b = b * b;
				b++;
				b = self_mod.Modul(b);
				b = b * b;
				b++;
				b = self_mod.Modul(b);

				// working as |a - b|
				if (a > b)
				{
					diff = a - b;
				}
				else
				{
					diff = b - a;
				}

				d = GCD(diff, number);

				if (d > one && d < number)
				{
					return make_pair(d, number / d);
				}
			}
			// terminating algoritm with failure
			while(!(d == number));
			// terminating algoritm with failure
			return NO_FACTOR;
		}
		else
		{
			return NO_FACTOR;
		}
	}

	vector<Number> Factorization::PrimeFactors(const Number& number)
	{
		// ! added Number initializer because don't realized default constructor !
		vector<Number> list = vector<Number>(0, Number("0"));

		RecursiveSearchingPrimeFactors(number, &list);

		return list;
	}

	// recursive part of PrimeFactors()
	void Factorization::RecursiveSearchingPrimeFactors(const Number& number, vector<Number>* list)
	{
		pair<Number, Number> pollard_result = PollardRhoFactorization(number);

		if (pollard_result == NO_FACTOR)
		{
			list->push_back(number);
		}
		else
		{
			RecursiveSearchingPrimeFactors(pollard_result.first, list);
			RecursiveSearchingPrimeFactors(pollard_result.second, list);
		}
	};
}