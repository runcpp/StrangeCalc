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
#include <memory>
#include <string>
#include <utility>

class MathematicalConstruct
{
public:
    virtual void print(std::ostream& os) const = 0;
};

class Constant: public MathematicalConstruct
{
private:
    long double value;
    std::string name;

public:
    explicit Constant(std::string  name, long double value);
    void print(std::ostream& os) const override;
};

void Constant::print(std::ostream& os) const
{
    os << value;
}

Constant::Constant(std::string  name, const long double value) : value(value), name(std::move(name))
{

}

class Equation: public MathematicalConstruct
{
private:
    std::unique_ptr<MathematicalConstruct> child;
public:
    explicit Equation(MathematicalConstruct& operation);
    explicit Equation(MathematicalConstruct&& operation);
    friend std::ostream& operator << (std::ostream& os, const Equation& eq);
    void print(std::ostream& os) const override;
};

void Equation::print(std::ostream &os) const
{
    if (child)
    {
        child->print(os);
    }
}

Equation::Equation(MathematicalConstruct &operation) : child(&operation)
{}

Equation::Equation(MathematicalConstruct &&operation) : child(&operation)
{}

std::ostream& operator<<(std::ostream& os, const Equation& eq)
{
    eq.print(os);

    return os;
}

class DecimalFraction
{
private:
    long long numerator;
    long long denominator;
    [[nodiscard]] long long LCM(const DecimalFraction& rhs) const;
    [[nodiscard]] long long GCD(const DecimalFraction& rhs) const;
    long long fractionGCD() const;

public:
    DecimalFraction(long long numerator, long long denominator);
    DecimalFraction operator + (const DecimalFraction& rhs) const;
    DecimalFraction operator + (long long rhs) const;
    friend std::ostream& operator << (std::ostream& os, const DecimalFraction& fraction);
    friend DecimalFraction operator + (long long lhs, DecimalFraction& rhs);
    friend DecimalFraction operator + (long long lhs, DecimalFraction&& rhs);

    void recduce();
};

DecimalFraction::DecimalFraction(long long numerator, long long denominator):
        numerator(numerator),denominator(denominator)
{}

DecimalFraction DecimalFraction::operator+(const DecimalFraction &rhs) const
{
    //Common denominator
    long long lcm = LCM(rhs);
    long long lhsDenominator = denominator;
    long long rhsDenominator = rhs.denominator;

    long long lhsNumerator = numerator * lcm / lhsDenominator;
    long long rhsNumerator = rhs.numerator * lcm / rhsDenominator;


    DecimalFraction value(lhsNumerator + rhsNumerator, lcm);
    value.recduce();

    return value;
}

DecimalFraction DecimalFraction::operator+(const long long rhs) const
{
    return *this + DecimalFraction(rhs, 1);
}

std::ostream& operator<<(std::ostream& os, const DecimalFraction& fraction)
{
    os << fraction.numerator << "/" << fraction.denominator;

    return os;
}

long long DecimalFraction::LCM(const DecimalFraction &rhs) const {
    return this->denominator*rhs.denominator/GCD(rhs);
}

long long DecimalFraction::GCD(const DecimalFraction &rhs) const {
    long long a = denominator;
    long long b = rhs.denominator;

    while(a != b)
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

void DecimalFraction::recduce()
{
    long long gcd = fractionGCD();
    denominator /= gcd;
    numerator /= gcd;
}

long long DecimalFraction::fractionGCD() const {
    long long a = denominator;
    long long b = numerator;

    while (a != b)
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

DecimalFraction operator+(long long lhs, DecimalFraction &rhs) {
    return rhs + lhs;
}

DecimalFraction operator+(long long lhs, DecimalFraction &&rhs) {
    return rhs + lhs;
}

int main()
{
    std::cout << 1 + DecimalFraction(1, 3) << std::endl;
    std::cout << DecimalFraction(1, 3) + DecimalFraction(1, 6) << std::endl;
    std::cout << DecimalFraction(15, 4) + DecimalFraction(2, 14) << std::endl;
    return 0;
}