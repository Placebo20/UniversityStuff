#include "Calculator.h"

namespace LongArithmetic {
    Calculator::Calculator(const Number& modulus) :
        m_Modulus("0") {
        SetModulus(modulus);
    }
    
    Number Calculator::Remainder(const Number& left, const Number& right) {
        Number result(left -  ((left / right) * right));
        if (result.GetSign() == Number::Sign::Minus) result = result + right;
        return result;
    }

    Number Calculator::Plus(const Number& left, const Number& right) {
        return Modul(Modul(left) + Modul(right));
    }

    Number Calculator::Minus(const Number& left, const Number& right) {
        return Modul(Modul(left) - Modul(right));
    }

    Number Calculator::Multiplication(const Number& left, const Number& right) {
        return Modul(Modul(left) * Modul(right));
    }

    Number Calculator::Division(const Number& left, const Number& right) {
        return Modul(Modul(left)/Modul(right));
    }

    Number Calculator::Modul(const Number& number) {
        if (number > m_Modulus || number == m_Modulus) {
            return Remainder(number, m_Modulus);
        }
        else if (number.GetSign() == Number::Sign::Minus) {
            Number result(number + ((-(number / m_Modulus)) * m_Modulus));
            if (result.GetSign() == Number::Sign::Minus) result = result + m_Modulus;
            return result;
        }
        return number;
    }

    /*Number Calculator::Inverse(const Number& number) {
        Number q(""), x("0"), lastx("1"), y("1"), lasty("0"), temp1(""), temp2(""), temp3(""), _a(""), _b("");

        if (m_Modulus > number) {
            _a = m_Modulus;
            _b = number;
        }
        else {
            _a = number;
            _b = m_Modulus;
        }
        while (_b.ToString() != "0") {
            q = _a / _b;
            temp1 = Remainder(_a, _b);

            _a = _b;
            _b = temp1;

            temp2 = x;
            x = (lastx -(q * x));
            lastx = temp2;

            temp3 = y;
            y = (lasty -(q * y));
            lasty = temp3;
        }
        return Modul(lasty);
    }*/

    void Calculator::SetModulus(const Number& modulus) {
        if (Number("-1") < modulus) {
            m_Modulus = modulus;
        }
        else {
            throw std::invalid_argument("modulus can't be less than 0!");
        }
    }

    Number Calculator::GetModulus() const {
        return m_Modulus;
    }

    Number Calculator::ModuloDivision(const Number& left, const Number& right) {
        return Modul(Multiplication(Modul(left), Inverse(Modul(right))));
    }

    Number& Calculator::Increment(Number& number) {
        number = Modul(++number);
        return number;
    }

    Number& Calculator::Decrement(Number& number) {
        number = Modul(--number);
        return number;
    }
    void Calculator::decrease(const Number& a, Number& b, const Number& a_count_in_a, Number& a_count_in_b)
    {
/*        if (b.getN() == "0") {
            std::string N = a.getN();
        }
        else {
            std::string N = b.getN();
        }*/
        Number one("1");
        Number ten("10");
        Number modifier("0");
        Number count("0");
        for (int i = b.GetDigits().size() - 1; i >= 0; i--) {
            count = count * ten;
            modifier = modifier * ten;
            modifier = modifier + Number(std::to_string(b.GetDigits()[i]));
            while (modifier >= a) {
                count = count + (modifier / a);
                modifier = modifier%a;
            }
        }
        Modul(modifier);
        Modul(count);
        b = modifier;
        a_count_in_b = a_count_in_b - count * a_count_in_a;
    }

    /*Number Calculator::Inverse(const Number& number) {
        Number a = number;
        Number b(m_Modulus);
        Number one("1");
        Number zero("0");
        Number a_1("1"); //a count in a
        Number b_1("0"); //a count in b
        Number x("0");//result
        while (!(a == one) && !(b == one)) {
            if ((a == zero) || (b == zero)) {
                return zero;
            }
            if (a >= b) {
                decrease(b, a, b_1, a_1);
            }
            else {
                decrease(a, b, a_1, b_1);
            }
        }
        if (a == one) {
            x = a_1;
        }
        else {
            x = b_1;
        }
        return Modul(x);
    }*/
    Number Calculator::Inverse(Number a) {
        Number b = m_Modulus;
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
        return Modul(lasty);
    }
   /* Number DiscretLog(Number& left, Number& right, Number& modul)
    {
        Number n = (Number)sqrt(modul) + 1;

        Number an("1");
        for (Number i("0"); i < n; i++)
            an = (an * left) % modul;

        std::map<Number, Number> vals;
        for (Number i("1"), cur = an; i <= n; i++) {
            if (!vals.count(cur))
                vals[cur] = i;
            cur = (cur * an) % modul;
        }

        for (Number i("0"), cur = right; i <= n; i++) {
            if (vals.count(cur)) {
                Number ans = vals[cur] * n - i;
                if (ans < modul)
                    return ans;
            }
            cur = (cur * left) % modul;
        }
        Number noAns("-1");
        return noAns;
    }*/
}