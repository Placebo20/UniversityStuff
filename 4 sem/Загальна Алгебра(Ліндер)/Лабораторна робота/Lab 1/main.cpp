#include "Number.h"
#include "Calculator.h"
#include "doctest.h"
#include "generators.h"

#include <random>
#include <string>
static std::random_device dev;
static std::mt19937 mersenne(dev());

Number evklid(Number a, Number b);

Number RandomNumber() {
	std::string s;
	if (mersenne() % 2) s.push_back('-');
	int length = mersenne() % 100;
	s.reserve(length);
	for (int i = 0; i < length; i++) {
		s.push_back('0' + mersenne() % 10);
	}
	return Number(s);
}

#define DOCTEST_CONFIG_IMPLEMENT

#ifdef DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "../lab7/OrderOfElement.h"

TEST_CASE("testing constructor & ToString & FromString") {
	std::string str;
	LongArithmetic::Number number(str);
	CHECK(number.ToString() == std::string("0"));
	str = "1";
	number.FromString(str);
	CHECK(number.ToString() == std::string(str));
	str = "-1";
	number.FromString(str);
	CHECK(number.ToString() == std::string(str));
	number.FromString("abc");
	CHECK(number.ToString() == std::string("0"));
	str = "1111111111111111111111111111";
	number.FromString(str);
	CHECK(number.ToString() == str);
	str = "1212121212121212121212121212";
	number.FromString(str);
	CHECK(number.ToString() == str);
	str = "54363465876869706345656867532443545767990828364735347564396485709658098097896785623546325478358734658468465469549867098456";
	number.FromString(str);
	CHECK(number.ToString() == str);
	str = "-234687365873465876987987097980923740734254365467567568678879098089089098956765867876946358325893";
	number.FromString(str);
	CHECK(number.ToString() == str);
	str = "-2346873658734658769879870979809237407342543654675675686788790980890t89098956765867876946358325893";
	number.FromString(str);
	CHECK(number.ToString() == std::string("0"));
	str = "234687365873465876987987097980923740734t54365467567568678879098089089098956765867876946358325893";
	number.FromString(str);
	CHECK(number.ToString() == std::string("0"));
	str = "2346873658734658769879870979809237407345436546756756867887909808908909895676586787694635832589a3";
	number.FromString(str);
	CHECK(number.ToString() == std::string("0"));
	str = "2b3468736587346587698798709798092374073454365467567568678879098089089098956765867876946358325893";
	number.FromString(str);
	CHECK(number.ToString() == std::string("0"));
}

TEST_CASE("testing Calculator") {
	using namespace LongArithmetic;
	Calculator calculator(Number("13124325346575678679789870899097686584677777775756756757658"));
	CHECK(calculator.Plus(Number("1111111111111111111111111111111111111111111111111"),
						  Number("2222222222222222222222222222222222222222222222222")) ==
						  Number("3333333333333333333333333333333333333333333333333"));
	CHECK(calculator.Minus(Number("2222222222222222222222222222222222222222222222222"),
						  Number("1111111111111111111111111111111111111111111111111")) ==
						  Number("1111111111111111111111111111111111111111111111111"));
	CHECK(calculator.Minus(Number("2222222222222222222222222222222222222222222222222"),
						  Number("0")) ==
						  Number("2222222222222222222222222222222222222222222222222"));
	CHECK(calculator.Division(Number("1111111111111111111111111111111111111111111111111"),
							  Number("1111111111111111111111111111111111111111111111111")) ==
							  Number("1"));
	CHECK(calculator.Division(Number("2222222222222222222222222222222222222222222222222"),
							  Number("1111111111111111111111111111111111111111111111111")) ==
							  Number("2"));
	
	calculator.SetModulus(Number("7"));

	calculator.SetModulus(Number("170141183460469231731687303715884105727"));

	CHECK(calculator.ModuloDivision(calculator.Multiplication(Number("123456789123"), Number("123456789123")), Number("123456789123")) == Number("123456789123"));
	CHECK(calculator.ModuloDivision(calculator.Multiplication(Number("1234564353453453454789123"), Number("1234567896786123")), Number("1234567896786123")) == Number("1234564353453453454789123"));
	CHECK(calculator.ModuloDivision(calculator.Multiplication(Number("1236353"), Number("250795")), Number("250795")) == Number("1236353"));
	
	CHECK(calculator.Division(calculator.Multiplication(Number("5555555"), Number("666666")), Number("666666")) == Number("5555555"));

	CHECK(calculator.Multiplication(calculator.Inverse(Number("1234789")), Number("1234789")) == Number("1"));
	CHECK(calculator.Multiplication(calculator.Inverse(Number("1233245325325425454354354345435344789")), Number("1233245325325425454354354345435344789")) == Number("1"));

	calculator.SetModulus(Number("170141183"));
	CHECK(calculator.Inverse(Number("123")) == Number("142475950"));

	calculator.SetModulus(Number("2222222222222222222222222222222222222222222222222"));

	CHECK(calculator.Modul(Number("1111111111111111111111111111111111111111111111111")) ==
						   Number("1111111111111111111111111111111111111111111111111"));

	calculator.SetModulus(Number("1111111111111111111111111111111111111111111111111"));
	CHECK(calculator.Modul(Number("2222222222222222222222222222222222222222222222222")) ==
						   Number("0"));
	CHECK(calculator.Modul(Number("-2222222222222222222222222222222222222222222222222")) ==
						   Number("0"));
	CHECK(calculator.Modul(Number("-2222222222222222222222222222222222222222222222221")) ==
						   Number("1"));

	calculator.SetModulus(Number("4"));
	CHECK(calculator.Modul(Number("-1")) ==
						   Number("3"));

	CHECK(calculator.Remainder(Number("179"), Number("96")) == Number("83"));
	CHECK(calculator.Remainder(Number("1111111111111111111111111111111111111111111111111"), 
							   Number("2222222222222222222222222222222222222222222222222")) == 
							   Number("1111111111111111111111111111111111111111111111111"));
	CHECK(calculator.Remainder(Number("123456789"), 
							   Number("123456789")) == 
							   Number("0"));

	calculator.SetModulus(Number("179"));
	CHECK(calculator.Inverse(Number("96")) == Number("69"));
	calculator.SetModulus(Number("132"));
	CHECK(calculator.Inverse(Number("25")) == Number("37"));
	calculator.SetModulus(Number("150"));
	CHECK(calculator.Inverse(Number("101")) == Number("101"));
	calculator.SetModulus(Number("123456789"));
	CHECK(calculator.Inverse(Number("1234567")) == Number("18033013"));

	calculator.SetModulus(Number("946457816401"));
	Number a = calculator.ModuloDivision(calculator.Multiplication(Number("12343453535345534234563"), Number("4654645")), Number("4654645"));
	CHECK(a == calculator.Modul(Number("12343453535345534234563")));
}

TEST_CASE("testing increment decrement") {
	using namespace LongArithmetic;
	Calculator calculator(Number("100"));
	Number number("99");
	SUBCASE("without modulus") {
		CHECK(number++ == Number("99"));
		CHECK(number == Number("100"));
		CHECK(number-- == Number("100"));
		CHECK(number == Number("99"));
		CHECK(++number == Number("100"));
		CHECK(number == Number("100"));
		CHECK(--number == Number("99"));
		CHECK(number == Number("99"));
	}
	SUBCASE("with modulus") {
		CHECK(calculator.Decrement(number) == Number("98"));
		CHECK(calculator.Increment(number) == Number("99"));
		CHECK(calculator.Increment(number) == Number("0"));
		CHECK(calculator.Increment(number) == Number("1"));
		CHECK(calculator.Decrement(number) == Number("0"));
		CHECK(calculator.Decrement(number) == Number("99"));
	}
}

TEST_CASE("random testing") {
	using namespace LongArithmetic;
	Calculator calculator(Number("100"));
	calculator.SetModulus(Number("487"));
	for (int i = 0; i < 100; i++) {
		int a = mersenne() % 1000;
		int b = mersenne() % 1000;
		if (mersenne() % 2) a *= -1;
		if (mersenne() % 2) b *= -1;
		CHECK(calculator.Plus(Number(std::to_string(a)),
			Number(std::to_string(b))) ==
			calculator.Modul(Number(std::to_string(a + b))));
		CHECK(calculator.Minus(Number(std::to_string(a)),
			Number(std::to_string(b))) ==
			calculator.Modul(Number(std::to_string(a - b))));
		CHECK(calculator.Multiplication(Number(std::to_string(a)),
			Number(std::to_string(b))) ==
			calculator.Modul(Number(std::to_string(a * b))));

		if (a >= 0 && b > 0 && Number("0") < calculator.Modul(Number(std::to_string(b)))) {
			CHECK(calculator.Division(Number(std::to_string(a)),
				Number(std::to_string(b))) ==
				calculator.Modul(Number(std::to_string((a % 487) / (b % 487)))));
		}
	}

	calculator.SetModulus(Number("20988936657440586486151264256610222593863921"));
	for (int i = 0; i < 1000; i++) {
		//calculator.SetModulus(Number(Number::Sign::Plus, RandomNumber().GetDigits()));
		Number a = RandomNumber();
		Number b = RandomNumber();
		CHECK(calculator.Modul(a) == calculator.Plus(calculator.Minus(a,b),b));
		Number sum = calculator.Plus(a, b);
		CHECK(calculator.Modul(a) == calculator.Minus(sum, b));
		CHECK(calculator.Modul(b) == calculator.Minus(sum, a));
		if (!(b == Number("0"))) {
			bool check = calculator.Modul(a) == calculator.Multiplication(calculator.ModuloDivision(a, b), b);
			CHECK(check);
			if (!check) {
				std::cout << "\n\n" << "Modul: " << calculator.GetModulus().ToString() << std::endl;
				std::cout << "a: " << a.ToString() << std::endl;
				std::cout << "b: " << b.ToString() << std::endl;
				std::cout << "Modul a: " << calculator.Modul(a).ToString() << std::endl;
				Number div = calculator.ModuloDivision(a, b);
				std::cout << "ModuloDivision: " << div.ToString() << std::endl;
				std::cout << "Multiplication: " << calculator.Multiplication(div, b).ToString() << std::endl;
			}
		}
		Number product = calculator.Multiplication(a, b);
		if (!(b == Number("0"))) {
			bool check = calculator.Modul(a) == calculator.ModuloDivision(product, b);
			CHECK(check);
			if (!check) {
				std::cout << "\n\n" << "Modul: " << calculator.GetModulus().ToString() << std::endl;
				std::cout << "a: " << a.ToString() << std::endl;
				std::cout << "b: " << b.ToString() << std::endl;
				std::cout << "Modul a: " << calculator.Modul(a).ToString() << std::endl;
				std::cout << "Multiplication: " << product.ToString() << std::endl;
				std::cout << "ModuloDivision: " << calculator.ModuloDivision(product, b).ToString() << std::endl;
			}
		}
		if (!(a == Number("0"))) {
			bool check = calculator.Modul(b) == calculator.ModuloDivision(product, a);
			CHECK(check);
			if (!check) {
				std::cout << "\n\n" << "Modul: " << calculator.GetModulus().ToString() << std::endl;
				std::cout << "a: " << a.ToString() << std::endl;
				std::cout << "b: " << b.ToString() << std::endl;
				std::cout << "Modul b: " << calculator.Modul(b).ToString() << std::endl;
				std::cout << "Multiplication: " << product.ToString() << std::endl;
				std::cout << "ModuloDivision: " << calculator.ModuloDivision(product, a).ToString() << std::endl;
			}
		}
	}
}
#endif

//алгоритм для инверсии
Number evklid(Number a, Number b)
{
	Number q(""), x(""), lastx(""), y(""), lasty(""), temp(""), temp1(""), temp2(""), temp3("");

	if (b > a) {
		temp = a; a = b; b = temp;
	}

	x = Number("0");
	y = Number("1");
	lastx = Number("1");
	lasty = Number("0");
	while (!(b == Number("0"))) {
		q = a / b;
		temp1 = a % b;
		a = b;
		b = temp1;

		temp2 = x;
		x = lastx - q * x;
		lastx = temp2;

		temp3 = y;
		y = lasty - q * y;
		lasty = temp3;

	}
	std::cout << "x=" << lastx.ToString() << std::endl;
	std::cout << "y=" << lasty.ToString() << std::endl;
	return lasty;
}

int gcdex(int a, int b, int& x, int& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int d1 = gcdex(b, a % b, x1, y1);
	x = y1;
	y = x1 - (a / b) * y1;
	return d1;
}

// Function returns 1 if such element doesn't exist and 0 if exists and puts it
// in result.
int ReverseElement(int a, int N) {
	int result;
	int x, y, d;
	d = gcdex(a, N, x, y);
	if (d != 1) {
		return 1;
	}
	else {
		result = x;
		return result;
	}
}

int Euler_fuction(int n) 
{
	int result = n;
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0) {
			while (n % i == 0)
				n /= i;
			result -= result / i;
		}
	if (n > 1)
		result -= result / n;
	return result;
}

int nsd(int a, int b) {
	int t;
	while (b) {
		t = b;
		b = a % b;
		a = t;
	}
	return a;
}
int ostacha(int a, int b, int c) {
	int t = 1;
	for (int e = 0; e < b; e++) {
		t = (t * a) % c;
	}
	return t;
}
int carmichael(int n) {
	int k = 1;
	for (;; ) {
		int done = 1;
		for (int x = 1; x < n; x++) {
			if (nsd(x, n) == 1 && ostacha(x, k, n) != 1) {
				done = 0;
				k++;
			}
		}
		if (done) break;
	}
	return k;
}

int main() {

	//	std::cout << ReverseElement(96, 179) << std::endl;
	//	evklid(Number("96"), Number("179"));
	//	evklid(1234567, 123456789);
	//	std::cout << Euler_fuction(12) << std::endl;
	//	std::cout << carmichael(12) << std::endl;

std::cout << LongArithmetic::find(Number("9"), Number("2")).ToString() << endl;

//#ifdef DOCTEST_CONFIG_IMPLEMENT
//	doctest::Context context;
//	int res = context.run();
//#endif
	cout << LongArithmetic::find(Number("10"), Number("9")).ToString() << endl;
	//LongArithmetic::Number number(str);
	
}