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

int main()
{
    Equation eq(Constant("RAND", 5.1));
    std::cout << eq << std::endl;
    return 0;
}