#include "orderOfEllipticCurve.h"
#include <math.h>
#include <ctime>
#include "pointDegree.h"

namespace OrderOfEllipticCurve {

    OrderOfEllipticCurve::OrderOfEllipticCurve(const LongArithmetic::Number& a, const LongArithmetic::Number& b, const LongArithmetic::Number& mod) : mainEllipticCurve(a, b, mod) {
        //main constructor of lab
        mainEllipticCurve.setA(a);
        mainEllipticCurve.setB(b);
        mainEllipticCurve.setModul(mod);
    }
    bool OrderOfEllipticCurve::isPrime(const LongArithmetic::Number& num)
        //Prime Number check
    {
        if (num.GetDigits().size() == 1 && (num.GetDigits().at(0) == 0 || num.GetDigits().at(0) == 1)) {
            return false;
        }
        else {
            LongArithmetic::Number tmp("0");
            LongArithmetic::Number temp("2");
            for (LongArithmetic::Number i("2"); i <= num / temp; ++i) {
                if (num % i == tmp) {
                    return false;
                }
            }
        }
        return true;
    }

    bool OrderOfEllipticCurve::isPrime(const int mod)
    {   //Prime Number check
        if (mod == 0 || mod == 1) {
            return false;
        }
        else {
            for (int i = 2; i <= mod / 2; ++i) {
                if (mod % i == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void OrderOfEllipticCurve::chooseM()
    {   //choosing of *m
        double buff = sqrt(sqrt(mainEllipticCurve.Modul().GetDigits()[0]));
        int tmp = buff + 1;
        m = new LongArithmetic::Number(std::to_string(tmp));
    }

    Number OrderOfEllipticCurve::babyGiant(Point startPoint)
    {//realization of baby step, giant step algorythm
        M = new Number("");

        Point Q = PointDegree::pointDegree(startPoint, mainEllipticCurve.Modul() + LongArithmetic::Number("1"), mainEllipticCurve.a(), mainEllipticCurve.b(), mainEllipticCurve.Modul());
        if (Q.is_endless() == true) return LongArithmetic::Number("0");
        LongArithmetic::Number L("1");
        Point zeroPoint(LongArithmetic::Number("0"), LongArithmetic::Number("0"));
        for (LongArithmetic::Number j("1"); j <= *m; j++) {
            Point jPointTemp = PointDegree::pointDegree(startPoint, j, mainEllipticCurve.a(), mainEllipticCurve.b(), mainEllipticCurve.Modul());
            if (jPointTemp.is_endless() == false) 
                jPoints.push_back(std::make_pair(j, jPointTemp));
        }

        LongArithmetic::Number k = *m;
        k.SetSign(LongArithmetic::Number::Sign::Minus);
        Point tempComparePoint(LongArithmetic::Number("0"), LongArithmetic::Number("0"));

        std::vector<std::pair<LongArithmetic::Number, Point>> jPointsMinus;

        for (int j = 0; j < jPoints.size(); j++) {
            Point bufferVariable = jPoints[j].second;
            bufferVariable.setX(-bufferVariable.x());
            bufferVariable.setY(-bufferVariable.y());
            jPointsMinus.push_back(std::make_pair(jPoints[j].first, bufferVariable));
        }

        for (k; k < *m; k++) {
            Point variableComparePoint1 = PointDegree::pointDegree(startPoint, *m * LongArithmetic::Number("2"), mainEllipticCurve.a(), mainEllipticCurve.b(), mainEllipticCurve.Modul());
            Point variableComparePoint2 = PointDegree::pointDegree(variableComparePoint1, k, mainEllipticCurve.a(), mainEllipticCurve.b(), mainEllipticCurve.Modul());
            tempComparePoint = mainEllipticCurve.Sum(Q, variableComparePoint2);
            if(tempComparePoint.is_endless() == true)tempComparePoint.make_normal(LongArithmetic::Number("0"), LongArithmetic::Number("0"));
            for (int i = 0; i < jPoints.size(); i++) {
                if ((tempComparePoint.is_endless() == jPoints[i].second.is_endless()) && ((tempComparePoint.is_endless() && jPoints[i].second.is_endless()) || tempComparePoint.x() == jPoints[i].second.x())) { 
                    *M = mainEllipticCurve.Modul() + LongArithmetic::Number("1") + *m * k * LongArithmetic::Number("2") - jPoints[i].first;
                    break;
                }

                if ((tempComparePoint.is_endless() == jPointsMinus[i].second.is_endless()) && ((tempComparePoint.is_endless() && jPointsMinus[i].second.is_endless()) || tempComparePoint.x() == jPointsMinus[i].second.x())) {
                    *M = mainEllipticCurve.Modul() + LongArithmetic::Number("1") + *m * k * LongArithmetic::Number("2") + jPoints[i].first;
                    break;
                }
            }
        }
        std::vector<LongArithmetic::Number> primeNumbaersM = primeFactorization(*M);
        int i = 0;
        while (i < primeNumbaersM.size()) {
            Point v1 = PointDegree::pointDegree(startPoint, *M / primeNumbaersM[i], mainEllipticCurve.a(), mainEllipticCurve.b(), mainEllipticCurve.Modul());
            Point O;
            if ((v1.is_endless() == O.is_endless()) &&
                ((v1.is_endless() && O.is_endless()) ||
                    (v1.x() == O.x() && v1.y() == O.y()))) {
                *M = *M / primeNumbaersM[i];
                primeNumbaersM = primeFactorization(*M);
                i = 0;
            }
            else {
                i++;
            }
        }
        L = lcm(L, *M);
        int buff = sqrt(mainEllipticCurve.Modul().GetDigits()[0]);
        LongArithmetic::Number min = mainEllipticCurve.Modul() + LongArithmetic::Number("1") - LongArithmetic::Number("2") * LongArithmetic::Number(std::to_string(buff));
        LongArithmetic::Number max = mainEllipticCurve.Modul() + LongArithmetic::Number("1") + LongArithmetic::Number("2") * LongArithmetic::Number(std::to_string(buff));
        int checker = 0;
        LongArithmetic::Number N("");
        while (min < max) {
            if (min % L == LongArithmetic::Number("0")) {
                checker++;
                N = min;
            }
            if (checker >= 2) return LongArithmetic::Number("0");
            min++;
        }
       
        return N;
    }

    std::vector<LongArithmetic::Number> OrderOfEllipticCurve::primeFactorization(LongArithmetic::Number n)
        //Factorization of Number
    {
        std::vector<LongArithmetic::Number> primeNumbers;
        while (n % LongArithmetic::Number("2") == LongArithmetic::Number("0"))
        {
            primeNumbers.push_back(LongArithmetic::Number("2"));
            n = n / LongArithmetic::Number("2");
        }

        int buff = sqrt(n.GetDigits()[0]);
        for (LongArithmetic::Number i("3"); i <= LongArithmetic::Number(std::to_string(buff)); i = i + LongArithmetic::Number("2"))
        {
            while (n % i == LongArithmetic::Number("0"))
            {
                primeNumbers.push_back(i);
                n = n / i;
            }
        }
        if(n > LongArithmetic::Number("2")) primeNumbers.push_back(n);
        return primeNumbers;
    }

    LongArithmetic::Number OrderOfEllipticCurve::lcm(LongArithmetic::Number L, LongArithmetic::Number M)
    { return (L / Generators::gcd(L, M)) * M; }
}
