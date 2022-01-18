#include "generators.h"

using namespace LongArithmetic;
Number Generators::gcd(Number a, Number b) {
	if (a - (a / b) * b == Number("0"))
		return b;
	if (b - (b / a) * a == Number("0"))
		return a;
	if (a > b)
		return gcd(a - (a / b) * b, b);
	return gcd(a, b - (b / a) * a);
}
Number Generators::sqrt_root( Number number) {
	Calculator calc(number);
	/*Number div = Number("1");
	Number result = Number("0");
	
	while (number > Number("0")) {
		number = number - div, div = div + Number("2");
		result = result+number < Number("0") ? Number("0") : Number("1");
	}
	return result;*/
	if (number == Number("0") || number == Number("1")) {
		return number;
	}
	Number div = Number("1");
	Number result = Number("1");
	while (result <= number) {
		div++;
		result = div * div;
	}
	return div-Number("1");
}
std::vector<Number> Generators::prime_factors(Number n) {
	Calculator calc(n);
	std::vector<Number> result;
	Number z = Number("2");
	while (z * z <= n) {
		if (n % z == Number("0")) {
			result.push_back(z);
			n = n / z;
		}
		else z++;
	}
	if (n > Number("1")) result.push_back(n);
	return result;
}
Number Generators::power_modulus(Number a, Number b, Number mod) {
	Number res("1");
	for (int i = 0; i < std::stoi(b.ToString()); i++) {
		res = res * a;
	}
	return res - (res / mod) * mod;
}
Number Generators::pow(Number a, Number b) {
	Number res("1");
	for (int i = 0; i < std::stoi(b.ToString()); i++) {
		res = res * a;
	}
	return res;
}
std::vector<Number> Generators::prime_numbers(const Number& number) {
	std::vector<Number> result;
	result.push_back(Number("1"));
	for (Number i = Number("2"); i < number; i++) {
		if (Generators::gcd(i,number) == Number("1")) {
			result.push_back(i);
				
		}
	}
	
	return result;
}
std::vector<Number> Generators::generators(const Number& number,char op) {
	std::vector<Number> order;
	std::vector<Number> generators_vector;
	std::vector<Number> result = prime_numbers(number);
	Calculator calc(number);
	/*result.push_back(Number("1"));
	for (Number i = Number("2"); i < number; i++) {
		if (Generators::gcd(i, number) == Number("1")) {
			result.push_back(i);

		}
	}*/
	Number val = Number("0");
	for (std::vector<int>::size_type i = 0;i < result.size();i++) {
		Number temp = Number("1");
		
		while (true) {
		if (op == '+') {
			return result;
		}
		else if (op == '*')
		{
			//val % number
				val = pow(result[i],temp);
				if (calc.Remainder(val,number) == Number("1")) {
					order.push_back(temp);
					//std::cout << order[i].ToString() << ' ';
					break;
				}
				
			}
		temp++;
		}
		
	}
	//return order;
	
	//Number count = Number("0");
	
	bool cyclic = false;
	for (std::vector<int>::size_type i = 0;i < order.size();i++) {
		if (order[i] == Number(std::to_string(order.size()))) {
			generators_vector.push_back(result[i]);
			cyclic = true;
			//count++;
		}
	}
	if (cyclic) {
		/*std::cout << count.ToString() << ' ';
		for (std::vector<int>::size_type i = 0;i < generators_vector.size();i++) {
			std::cout << generators_vector[i].ToString() << ' ';
			}*/
		return generators_vector;	
	}
	else std::cout << "The group is not a cyclic group " << std::endl;
}
//Number Generators::get_Random_value(Number number) {
//	std::default_random_engine generator;
//	std::uniform_int_distribution<Number> distribution(Number("1"), number);
//	Number dice_roll = distribution(generator);
//	return dice_roll;
//	std::cout << dice_roll.ToString() << ' ';
//}
Number RandomNum(int size) {
	std::string s;
	if (mers() % 2) s.push_back('-');
	int length = mers() % size;
	s.reserve(length);
	for (int i = 0; i < length; i++) {
		s.push_back('0' + mers() % (size/10));
	}
	return Number(s);
}
Number Generators::efficient_generator( Number number) {
	Number alpha =  RandomNum(std::stoi(number.ToString()));
	//= RandomNum(std::stoi(number.ToString()));
	//Number alpha = RandomNum();
	Number cycle = Number("0");
	Calculator calc(number);
	Number res = Number("0");
	
	Number b = Number("0");
	std::vector<Number> prime_fact = prime_factors(number);
	
	while (cycle < number) {
		 alpha = RandomNum(std::stoi(number.ToString()));
		for (auto i = 0;i < prime_fact.size();i++) {
			
			b = power_modulus(alpha, number/prime_fact[i],number);
			//b = pow(alpha, number/prime_fact[i]);
			if (b == Number("1"))
			{
				cycle++;
				
				break;
			}
			//else 
			//res.push_back(calc.Modul(alpha));		
		}
		
	}
	return calc.Modul(alpha);
}