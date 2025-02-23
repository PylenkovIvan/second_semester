#include <iostream>
#include <cmath>
using namespace std;

class Figure
{
public:
    Figure() {}
    virtual double s() = 0;
    virtual double p() = 0;
};

class Parallelogram: public Figure
{
public:
    Parallelogram(double a, double b, double alpha)
    {
        this->a = a;
        this->b = b;
        this->alpha = alpha;
    }

    virtual double s() override
    {
        return this->a * this->b * sin(this->alpha);
    }

    virtual double p() override final
    {
        return 2 * (this->a + this->b);
    }
protected:
    double a;
    double b;
    double alpha;
};

class Rhomb: public Parallelogram
{
public:
    Rhomb(double a, double alpha): Parallelogram(a, a, alpha) {}
};

class Rectangle: public Parallelogram
{
public:
    Rectangle(double a, double b): Parallelogram(a, b, acos(-1) / 2) {}

    virtual double s() override final
    {
        return this->a * this->b;
    }
};

class Square: public Rectangle
{
public:
    Square(double a): Rectangle(a, a) {}
};

class Ellipse: public Figure
{
public:
    Ellipse(double a, double b)
    {
        this->a = a;
        this->b = b;
    }

    virtual double s() override final
    {
        return acos(-1) * this->a * this->b;
    }

    virtual double p() override
    {
        return 2 * acos(-1) * sqrt((this->a * this->a + this->b * this->b) / 2);
    }
protected:
    double a;
    double b;
};

class Circle: public Ellipse
{
public:
    Circle(double a): Ellipse(a, a) {}

    virtual double p() override
    {
        return 2 * acos(-1) * this->a;
    }
};

int main()
{
    Parallelogram p(5, 10, acos(-1) / 6);
    Rhomb rhomb(3, acos(-1) / 6);
    Rectangle r(7, 8);
    Square s(5);
    Ellipse e(12, 10);
    Circle c(15);
    Figure* arr[] = {&p, &rhomb, &r, &s, &e, &c};

    for (int i = 0; i != 6; i++)
    {
        cout << arr[i]->p() << ' ' << arr[i]->s() << '\n';
    }
}
