/*
Copyright 2019 runcpp
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies
or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <string>

class DecimalFraction
{
private:
    long long numerator;
    long long denominator;
    static long long GCD(long long a, long long b);
    [[nodiscard]] long long LCM(const DecimalFraction& rhs) const;
    [[nodiscard]] long long GCD(const DecimalFraction& rhs) const;
    [[nodiscard]] long long fractionGCD() const;

public:
    DecimalFraction(long long numerator, long long denominator);
    DecimalFraction operator + (const DecimalFraction& rhs) const;
    DecimalFraction operator + (long long rhs) const;

    friend DecimalFraction operator + (long long lhs, DecimalFraction& rhs);
    friend DecimalFraction operator + (long long lhs, DecimalFraction&& rhs);

    DecimalFraction operator - (const DecimalFraction& rhs) const;
    DecimalFraction operator - (long long rhs) const;

    friend DecimalFraction operator - (long long lhs, DecimalFraction& rhs);
    friend DecimalFraction operator - (long long lhs, DecimalFraction&& rhs);

    DecimalFraction operator * (const DecimalFraction& rhs) const;
    DecimalFraction operator * (long long rhs) const;

    friend DecimalFraction operator * (long long lhs, DecimalFraction& rhs);
    friend DecimalFraction operator * (long long lhs, DecimalFraction&& rhs);

    DecimalFraction operator / (const DecimalFraction& rhs) const;
    DecimalFraction operator / (long long rhs) const;

    friend DecimalFraction operator / (long long lhs, DecimalFraction& rhs);
    friend DecimalFraction operator / (long long lhs, DecimalFraction&& rhs);

    friend std::ostream& operator << (std::ostream& os, const DecimalFraction& fraction);

    void reduce();
};

DecimalFraction::DecimalFraction(long long numerator, long long denominator):
        numerator(numerator),denominator(denominator)
{
    if (denominator < 0)
    {
        this->denominator = -denominator;
        this->numerator = -numerator;
    }
}

DecimalFraction DecimalFraction::operator+(const DecimalFraction &rhs) const
{
    //Common denominator
    long long lcm = LCM(rhs);
    long long lhsDenominator = denominator;
    long long rhsDenominator = rhs.denominator;

    long long lhsNumerator = numerator * lcm / lhsDenominator;
    long long rhsNumerator = rhs.numerator * lcm / rhsDenominator;


    DecimalFraction value(lhsNumerator + rhsNumerator, lcm);
    value.reduce();

    return value;
}

DecimalFraction DecimalFraction::operator+(const long long rhs) const
{
    return *this + DecimalFraction(rhs, 1);
}

std::ostream& operator<<(std::ostream& os, const DecimalFraction& fraction)
{
    os << fraction.numerator;
    if (fraction.denominator != 1)
    {
        os << "/" << fraction.denominator;
    }

    return os;
}

long long DecimalFraction::LCM(const DecimalFraction &rhs) const
{
    return this->denominator*rhs.denominator/GCD(rhs);
}

long long DecimalFraction::GCD(const DecimalFraction &rhs) const
{
    return DecimalFraction::GCD(denominator, rhs.denominator);
}

void DecimalFraction::reduce()
{
    long long gcd = fractionGCD();
    denominator /= gcd;
    numerator /= gcd;
}

long long DecimalFraction::fractionGCD() const
{
    long long a = llabs(denominator);
    long long b = llabs(numerator);

    return DecimalFraction::GCD(a, b);
}

DecimalFraction operator+(long long lhs, DecimalFraction &rhs)
{
    return rhs + lhs;
}

DecimalFraction operator+(long long lhs, DecimalFraction &&rhs)
{
    return rhs + lhs;
}

DecimalFraction DecimalFraction::operator-(const DecimalFraction &rhs) const
{
    //Common denominator
    long long lcm = LCM(rhs);
    long long lhsDenominator = denominator;
    long long rhsDenominator = rhs.denominator;

    long long lhsNumerator = numerator * lcm / lhsDenominator;
    long long rhsNumerator = rhs.numerator * lcm / rhsDenominator;


    DecimalFraction value(lhsNumerator - rhsNumerator, lcm);
    value.reduce();

    return value;
}

DecimalFraction DecimalFraction::operator-(long long rhs) const
{
    return *this - DecimalFraction(rhs, 1);
}

DecimalFraction operator-(long long lhs, DecimalFraction &rhs)
{
    return DecimalFraction(lhs, 1) - rhs;
}

DecimalFraction operator-(long long lhs, DecimalFraction &&rhs)
{
    return DecimalFraction(lhs, 1) - rhs;
}

DecimalFraction DecimalFraction::operator*(const DecimalFraction &rhs) const
{
    //Common denominator
    long long gcd1 = DecimalFraction::GCD(llabs(numerator), llabs(rhs.denominator));
    long long lhsNumerator = numerator / gcd1;
    long long rhsDenominator = rhs.denominator / gcd1;

    long long gcd2 = DecimalFraction::GCD(denominator, rhs.numerator);
    long long rhsNumerator = rhs.numerator / gcd2;
    long long lhsDenominator = denominator / gcd2;

    DecimalFraction value(lhsNumerator * rhsNumerator, lhsDenominator * rhsDenominator);
    value.reduce();

    return value;
}

long long DecimalFraction::GCD(long long a, long long b)
{
    while (a != b && a >= 1 && b >= 1)
    {
        if (a < b)
        {
            b -= a;
        }
        else
        {
            a -= b;
        }
    }

    return a;
}

DecimalFraction DecimalFraction::operator*(long long rhs) const
{
    return *this * DecimalFraction(rhs, 1);
}

DecimalFraction operator*(long long lhs, DecimalFraction &rhs)
{
    return DecimalFraction(lhs, 1) * rhs;
}

DecimalFraction operator*(long long lhs, DecimalFraction &&rhs)
{
    return DecimalFraction(lhs, 1) * rhs;
}

DecimalFraction DecimalFraction::operator/(const DecimalFraction &rhs) const
{
    return *this * DecimalFraction(rhs.denominator, rhs.numerator);
}

DecimalFraction DecimalFraction::operator/(long long rhs) const
{
    return *this / DecimalFraction(rhs, 1);
}

DecimalFraction operator/(long long lhs, DecimalFraction &rhs)
{
    return DecimalFraction(lhs, 1) / rhs;
}

DecimalFraction operator/(long long lhs, DecimalFraction &&rhs)
{
    return DecimalFraction(lhs, 1) / rhs;
}

int main()
{
    DecimalFraction lhs1 = DecimalFraction(-4, 5);
    long long rhs1 = 2;
    long long lhs2 = 1;
    DecimalFraction rhs2 = DecimalFraction(1, 3);
    DecimalFraction lhs3 = DecimalFraction(1, 3);
    DecimalFraction rhs3 = DecimalFraction(1, 6);
    DecimalFraction lhs4 = DecimalFraction(15, 4);
    DecimalFraction rhs4 = DecimalFraction(2, 14);

    std::cout << "Addition:" << std::endl;
    std::cout << lhs1 << " + " << rhs1 << " = " << lhs1 + rhs1 << std::endl;
    std::cout << lhs2 << " + " << rhs2 << " = " << lhs2 + rhs2 << std::endl;
    std::cout << lhs3 << " + " << rhs3 << " = " << lhs3 + rhs3 << std::endl;
    std::cout << lhs4 << " + " << rhs4 << " = " << lhs4 + rhs4 << std::endl;
    std::cout << std::endl;

    std::cout << "Subtraction:" << std::endl;
    std::cout << lhs1 << " - " << rhs1 << " = " << lhs1 - rhs1 << std::endl;
    std::cout << lhs2 << " - " << rhs2 << " = " << lhs2 - rhs2 << std::endl;
    std::cout << lhs3 << " - " << rhs3 << " = " << lhs3 - rhs3 << std::endl;
    std::cout << lhs4 << " - " << rhs4 << " = " << lhs4 - rhs4 << std::endl;
    std::cout << std::endl;

    std::cout << "Multiplication:" << std::endl;
    std::cout << lhs1 << " * " << rhs1 << " = " << lhs1 * rhs1 << std::endl;
    std::cout << lhs2 << " * " << rhs2 << " = " << lhs2 * rhs2 << std::endl;
    std::cout << lhs3 << " * " << rhs3 << " = " << lhs3 * rhs3 << std::endl;
    std::cout << lhs4 << " * " << rhs4 << " = " << lhs4 * rhs4 << std::endl;
    std::cout << std::endl;

    std::cout << "Division:" << std::endl;
    std::cout << lhs1 << " / " << rhs1 << " = " << lhs1 / rhs1 << std::endl;
    std::cout << lhs2 << " / " << rhs2 << " = " << lhs2 / rhs2 << std::endl;
    std::cout << lhs3 << " / " << rhs3 << " = " << lhs3 / rhs3 << std::endl;
    std::cout << lhs4 << " / " << rhs4 << " = " << lhs4 / rhs4 << std::endl;
    std::cout << std::endl;

    return 0;
}