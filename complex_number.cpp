#include <iostream>
#include <cmath>

class Complex
{
public:
    Complex(double a, double b): a(a), b(b) {}

    Complex(): a(0), b(0) {}

    Complex operator+(Complex num)
    {
        return Complex(this->a + num.a, this->b + num.b);
    }

    Complex operator-(Complex num)
    {
        return Complex(this->a - num.a, this->b - num.b);
    }

    Complex operator*(Complex num)
    {
        return Complex(this->a * num.a - this->b * num.b, this->a * num.b + this->b * num.a);
    }

    Complex operator*(int num)
    {
        return Complex(this->a * num, this->b * num);
    }

    Complex operator/(Complex num)
    {
        return Complex((this->a * num.a + this->b * num.b) / (num.a * num.a + num.b * num.b),
                       (this->b * num.a - this->a * num.b) / (num.a * num.a + num.b * num.b));
    }

    Complex operator++() {
        this->a += 1;
        return *this;
    }

    Complex operator++(int) {
        Complex old = *this;
        this->a += 1;
        return old;
    }

    Complex operator--() {
        this->a -= 1;
        return *this;
    }

    Complex operator--(int) {
        Complex old = *this;
        this->a -= 1;
        return old;
    }

    friend std::ostream& operator<<(std::ostream&, Complex);
    friend std::istream& operator>>(std::istream&, Complex&);
private:
    double a;
    double b;
};

std::ostream& operator<<(std::ostream& out, Complex n)
{
    if (n.b == 0)
    {
        return out << n.a;
    }
    else if ((n.a == 0) and (n.b == 1))
    {
        return out << 'i';
    }
    else if (n.a == 0)
    {
        return out << n.b << 'i';
    }
    else if (n.b == 1)
    {
        return out << n.a << "+i";
    }
    return out << n.a << '+' << n.b << 'i';
}

std::istream& operator>>(std::istream& in, Complex& n)
{
    char* arr = new char[100];
    int* x_i = new int[100];
    int* y_i = new int[100];
    double* x_f = new double[100];
    double* y_f = new double[100];
    int border = 0;
    int i = 0;
    n.a = 0;
    n.b = 0;
    in >> arr;
    if ((arr[0] == 'i') and !(arr[1]))
    {
        delete[] x_i;
        delete[] x_f;
        delete[] y_i;
        delete[] y_f;
        n.b = 1;
        return in;
    }
    if (arr[0] != 'i')
    for (; (arr[i]) and (arr[i] != '+'); i++)
    {
        if ((arr[i] != '.') and !(border))
        {
            n.a = n.a * 10 + (arr[i] - 48);
        }
        else if ((arr[i] != '.') and (border))
        {
            n.a += (arr[i] - 48) / std::pow(10, i - border);
        }
        else
        {
            border = i;
        }
    };
    if (arr[0] == 'i') i -= 1;
    i += 3;
    border = 0;
    for (; arr[i]; i++)
    {
        if ((arr[i] != '.') and !(border))
        {
            n.b = n.b * 10 + (arr[i] - 48);
        }
        else if ((arr[i] != '.') and (border))
        {
            n.b += (arr[i] - 48) / std::pow(10, i - border);
        }
        else
        {
            border = i;
        }
    }
    delete[] x_i;
    delete[] x_f;
    delete[] y_i;
    delete[] y_f;
    return in;
}

int main()
{
    Complex number_1(5, 1);
    Complex number_2(5, 10);
    Complex number_3;

    std::cout << "Complex number: a+i*b\n";
    std::cin >> number_3;
    std::cout << number_3 << '\n';

    std::cout << number_1 + number_3 << '\n';
    std::cout << number_2 - number_1 << '\n';
    std::cout << number_1 * number_3 << '\n';
    std::cout << number_2 / number_1 << '\n';
    std::cout << number_3 * 5 << '\n';

    std::cout << number_3++ << '\n';
    std::cout << ++number_3 << '\n';
    std::cout << number_3-- << '\n';
    std::cout << --number_3 << '\n';
}
