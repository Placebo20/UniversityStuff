#include "Number.h"

#include <cmath>
#include <iomanip>
#include <sstream>

namespace LongArithmetic {
    Number::Number(const std::string& str) {
        FromString(str);
    }

    Number::Number(const Number& another) :
        m_Sign(another.m_Sign), m_Digits(another.m_Digits) {}

    Number::Number(Sign sign, const std::vector<std::uint64_t>& digits) :
        m_Sign(sign), m_Digits(digits) {}

    Number Number::operator-() const {
        return Number(m_Sign == Sign::Plus ? Sign::Minus : Sign::Plus, m_Digits);;
    }

    Number::Sign Number::GetSign() const {
        return m_Sign;
    }

    const std::vector<std::uint64_t>& Number::GetDigits() const {
        return m_Digits;
    }

    void Number::FromString(const std::string& str)
    {
        try
        {
            m_Digits.clear();
            if (str.length() == 0) {
                m_Sign = Sign::Plus;
                m_Digits = { 0 };
                return;
            }
            if (str[0] == '-') {
                m_Sign = Sign::Minus;
            }
            else {
                m_Sign = Sign::Plus;
            }

            int power = 0;

            auto end = m_Sign == Sign::Plus ? str.rend() : --str.rend();

            m_Digits.push_back(0);

            for (auto i = str.rbegin(); i != end; i++) {
                if (*i < '0' || *i > '9') {
                    //throw std::exception("");
                }
                m_Digits.back() += static_cast<uint64_t>(*i - '0') * powl(10, power);
                if (++power == 9) {
                    power = 0;
                    m_Digits.push_back(0);
                }
            }

            RemoveLeadingZeros();
        }
        catch (const std::exception&) {
            m_Sign = Sign::Plus;
            m_Digits = { 0 };
        }
    }

    std::ostream& operator <<(std::ostream& os, const Number& number) {
        if (number.GetDigits().empty()) {
            os << 0;
            return os;
        }
        if (number.GetSign() == Number::Sign::Minus) {
            os << '-';
        }
        os << number.GetDigits().back();
        char old_fill = os.fill('0');
        for (auto it = ++number.GetDigits().rbegin(); it != number.GetDigits().rend(); it++) {
            os << std::setw(9) << *it;
        }
        os.fill(old_fill);
        return os;
    }

    std::string Number::ToString() const
    {
        std::ostringstream oss;
        oss << *this;
        return oss.str();
    }

    bool Number::operator==(const Number& another) const {
        return m_Digits == another.GetDigits() && m_Sign == another.GetSign();
    }

    void Number::RemoveLeadingZeros() {
        while (this->m_Digits.size() > 1 && this->m_Digits.back() == 0) {
            this->m_Digits.pop_back();
        }
        if (this->m_Digits.size() == 1 && this->m_Digits[0] == 0) {
            m_Sign = Sign::Plus;
        }
    }

    void Number::ShiftRight() {
        if (this->m_Digits.size() == 0) {
            this->m_Digits.push_back(0);
            return;
        }
        this->m_Digits.push_back(this->m_Digits[this->m_Digits.size() - 1]);
        for (size_t i = this->m_Digits.size() - 2; i > 0; --i) this->m_Digits[i] = this->m_Digits[i - 1];
        this->m_Digits[0] = 0;
    }

    bool Number::operator<(const Number& right) const {
        if (m_Digits == right.GetDigits() && m_Sign == right.GetSign()) return false;
        else if (m_Sign == Number::Sign::Minus && right.GetSign() == Number::Sign::Plus) return true;
        else {
            if (m_Digits.size() != right.GetDigits().size()) {
                return m_Digits.size() < right.GetDigits().size();
            }
            else {
                for (long long i = m_Digits.size() - 1; i >= 0; --i) {
                    if (m_Digits[i] != right.GetDigits()[i]) return m_Digits[i] < right.GetDigits()[i];
                }
                return false;
            }
        }
    }

    void Number::SetSign(Sign sing){
        m_Sign = sing;
    }

    bool Number::operator<=(const Number& right) const {
        return (*this < right || *this == right);
    }

    bool Number::operator>(const Number& right) const {
        return !(*this <= right);
    }

    /*Number Number::operator+(const Number& right) const {
        Number answer(*this);
        if (GetSign() == Number::Sign::Minus) {
            if (right.GetSign() == Number::Sign::Minus) return -((-*this) + (-right));
            else return right - (-*this);
        }
        else if (right.GetSign() == Number::Sign::Minus) return *this - (-right);
        bool carry = false;
        for (size_t i = 0; i < answer.GetDigits().size() || carry; i++) {
            if (i == answer.GetDigits().size()) {
                answer.m_Digits.push_back(0);
            }
            answer.m_Digits[i] += carry + right.GetDigits()[i];
            carry = answer.GetDigits()[i] >= Number::Base;
            if (carry) {
                answer.m_Digits[i] -= Number::Base;
            }
        }
        /*if (m_Modulus < answer) {
            answer = Minus(answer, m_Modulus);
        }////
        return answer;
    }*/
    int my_div(int num, int diver) {
        if ((num < 0) && (num % diver))
            return num / diver - 1;
        else
            return num / diver;
    }
    int my_mod(int num, int diver) {
        if ((num < 0) && (num % diver))
            return num % diver + diver;
        else
            return num % diver;
    }
    Number Number::operator + (const Number& num) const {

        Number res("0");
        std::vector<std::uint64_t> reschunks;
        //a+b
        Number a = *this;
        Number b = num;
        if (a.GetDigits().size() > b.GetDigits().size()) {
            b.m_Digits.resize(a.GetDigits().size());
        }
        else {
            a.m_Digits.resize(b.m_Digits.size());
        }

        if (m_Sign == b.GetSign()) {

            res.SetSign(a.GetSign());

            int over = 0;
            for (int i = 0; i < a.m_Digits.size(); i++) {
                reschunks.push_back(a.m_Digits[i] + b.m_Digits[i]);
                reschunks[i] += over;
                over = my_div(reschunks[i], Base);
                reschunks[i] = my_mod(reschunks[i], Base);
            }

            if (over != 0) {
                reschunks.push_back(over);
            }

        }
        else {
            res.SetSign(a.GetSign());
            int over = 0;
            a.SetSign(static_cast<Sign>((int)a.GetSign() * (-1)));
            if (a >= b) {

                for (int i = 0; i < a.m_Digits.size(); i++) {
                    reschunks.push_back(a.m_Digits[i] - b.m_Digits[i]);
                    reschunks[i] += over;
                    over = my_div(reschunks[i], Base);
                    reschunks[i] = my_mod(reschunks[i], Base);
                }
            }
            else {
                res.SetSign(static_cast<Sign>((int)res.GetSign() * (-1)));
                for (int i = 0; i < a.m_Digits.size(); i++) {
                    reschunks.push_back(b.m_Digits[i] - a.m_Digits[i]);
                    reschunks[i] += over;
                    over = my_div(reschunks[i], Base);
                    reschunks[i] = my_mod(reschunks[i], Base);
                }
            }
            a.SetSign(static_cast<Sign>((int)a.GetSign() * (-1)));

        }

        res.SetDigits(reschunks);
        res.RemoveLeadingZeros();

        return res;
    }



    /*Number Number::operator-(const Number& right) const {
        if (right.ToString() == "0") return *this;  //TODO
        Number answer(*this);
        if (right.GetSign() == Number::Sign::Minus) return *this + (-right);
        else if (GetSign() == Number::Sign::Minus) return -((-*this) + right);
        else if (*this < right) {
            answer = -(right - *this);
            answer.RemoveLeadingZeros();
            return answer;
        }
        bool carry = false;
        for (size_t i = 0; i < right.GetDigits().size() || carry != 0; ++i) {
            answer.m_Digits[i] -= carry + right.GetDigits()[i];
            carry = GetDigits()[i] < 0;
            if (carry) {
                answer.m_Digits[i] += Number::Base;
            }
        }
        answer.RemoveLeadingZeros();
        return answer;
    }*/

    Number Number::operator - (const Number& num) const {

        Number res("0");
        std::vector<std::uint64_t> reschunks;
        //a-b
        Number a = *this;
        Number b = num;
        if (a.GetDigits().size() > b.GetDigits().size()) {
            b.m_Digits.resize(a.GetDigits().size());
        }
        else {
            a.m_Digits.resize(b.m_Digits.size());
        }

        if (m_Sign != b.GetSign()) {

            res.SetSign(a.GetSign());

            int over = 0;
            for (int i = 0; i < a.GetDigits().size(); i++) {
                reschunks.push_back(a.GetDigits()[i] + b.GetDigits()[i]);
                reschunks[i] += over;
                over = my_div(reschunks[i], Base);
                reschunks[i] = my_mod(reschunks[i], Base);
            }

            if (over != 0) {
                reschunks.push_back(over);
            }

        }
        else {
            res.SetSign(a.GetSign());
            int over = 0;

            if (a >= b) {
                for (int i = 0; i < a.GetDigits().size(); i++) {
                    reschunks.push_back(a.GetDigits()[i] - b.GetDigits()[i]);
                    reschunks[i] += over;
                    over = my_div(reschunks[i], Base);
                    reschunks[i] = my_mod(reschunks[i], Base);
                }
            }
            else {
                res.SetSign(static_cast<Sign>((int)res.GetSign() * (-1)));
                for (int i = 0; i < a.GetDigits().size(); i++) {
                    reschunks.push_back(b.GetDigits()[i] - a.GetDigits()[i]);
                    reschunks[i] += over;
                    over = my_div(reschunks[i], Base);
                    reschunks[i] = my_mod(reschunks[i], Base);
                }
            }

        }

        res.SetDigits(reschunks);
        res.RemoveLeadingZeros();

        return res;
    }

    Number Number::operator*(const Number& right) const {
        Number answer("");
        if (GetSign() == Number::Sign::Minus && right.GetSign() == Number::Sign::Minus)
            answer.SetSign(Number::Sign::Plus);
        else if (GetSign() == Number::Sign::Plus && right.GetSign() == Number::Sign::Plus)
            answer.SetSign(Number::Sign::Plus);
        else
            answer.SetSign(Number::Sign::Minus);

        answer.m_Digits.resize(GetDigits().size() + right.GetDigits().size());
        for (size_t i = 0; i < GetDigits().size(); ++i) {
            uint64_t carry = 0;
            for (size_t j = 0; j < right.GetDigits().size() || carry != 0; ++j) {
                uint64_t cur = answer.GetDigits()[i + j] +
                    GetDigits()[i] * 1LL * (j < right.GetDigits().size() ? right.GetDigits()[j] : 0) + carry;
                answer.m_Digits[i + j] = static_cast<int>(cur % Number::Base);
                carry = static_cast<uint64_t>(cur / Number::Base);
            }
        }
        answer.RemoveLeadingZeros();
        return answer;
    }

    Number Number::operator/(const Number& right) const {
        //if (right.ToString() == "0") throw std::exception{ "Divide By Zero" };
        Number b(right.ToString());
        b.SetSign(Number::Sign::Plus);
        Number result(""), current("");
        result.m_Digits.resize(GetDigits().size());

        for (long long i = static_cast<long long>(GetDigits().size()) - 1; i >= 0; --i) {
            current.ShiftRight();
            current.m_Digits[0] = GetDigits()[i];
            current.RemoveLeadingZeros();
            int x = 0, l = 0, r = Number::Base;
            while (l <= r) {
                int m = (l + r) / 2;
                Number _m(std::to_string(m));
                Number t(b * _m);
                if (t <= current) {
                    x = m;
                    l = m + 1;
                }
                else r = m - 1;
            }
            Number _x(std::to_string(x));
            result.m_Digits[i] = x;
            current = current - (b * _x);
        }

        if (GetSign() == Number::Sign::Minus && right.GetSign() == Number::Sign::Minus)
            result.SetSign(Number::Sign::Plus);
        else if (GetSign() == Number::Sign::Plus && right.GetSign() == Number::Sign::Plus)
            result.SetSign(Number::Sign::Plus);
        else
            result.SetSign(Number::Sign::Minus);
        result.RemoveLeadingZeros();

        return result;
    }
    Number& Number::operator++() {
        *this = *this + Number("1");
        return *this;
    }
    Number& Number::operator--() {
        *this = *this - Number("1");
        return *this;
    }

    Number Number::operator++(int) {
        Number temp = *this;
        ++*this;
        return temp;
    }

    Number Number::operator--(int) {
        Number temp = *this;
        --*this;
        return temp;
    }
    Number Number::operator%(const Number& right) const {
        Number result(*this - ((*this / right) * right));
        if (result.GetSign() == Number::Sign::Minus) result = result + right;
        return result;
    }
    bool Number::operator>=(const Number& right) const {
        return (*this > right || *this == right) ? true : false;
    }
}