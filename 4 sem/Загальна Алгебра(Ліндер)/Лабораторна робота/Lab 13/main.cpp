#include <iostream>
#include "orderOfEllipticCurve.h"
#include "/PROJECTS/GA-Lab/LabGeneralAlgebra/Lab1GA/Number.h"

void scenario(OrderOfEllipticCurve::OrderOfEllipticCurve& core) {
    core.chooseM();

    LongArithmetic::Number tmp(Number("0"));
    for (Number i("0"); i < core.mainEllipticCurve.Modul(); i++) {
        for (Number j("0"); j < core.mainEllipticCurve.Modul(); j++) {
            Point startPoint(LongArithmetic::Number(std::to_string(i.GetDigits()[0])), LongArithmetic::Number(std::to_string(j.GetDigits()[0])));
            if (!core.mainEllipticCurve.is_curve_point(startPoint)) {
                continue;
            }
            tmp = core.babyGiant(startPoint);
            if (!(tmp == LongArithmetic::Number("0"))) {
                for (int k = 0; k < tmp.GetDigits().size(); k++) {
                    std::cout << "Count of points: " << tmp.GetDigits()[k];
                }
                return;
            }
        }
    }
}

int main()
{   
    std::cout << "Input a: ";
    std::string buffer = "";
    std::cin >> buffer;
    LongArithmetic::Number a(buffer);
    std::cout << "Input b: ";
    std::cin >> buffer;
    LongArithmetic::Number b(buffer);
    std::cout << "Input modul: ";
    std::cin >> buffer;
    LongArithmetic::Number modul(buffer);
    OrderOfEllipticCurve::OrderOfEllipticCurve core(a, b, modul);
    while (!core.isPrime(modul)) {
        std::cout << "Modul is not a prime number, try again please: ";
        std::cin >> buffer;
        modul = buffer;
        core.mainEllipticCurve.setModul(modul);
    }
    scenario(core);

    return 0;
}