#include <iostream>
#include <cmath>
using namespace std;

class Polyline {
public:
    // ����������� � ����������, ���� ����������
    Polyline()
    {
        this->p_x = new double[100];
        this->p_y = new double[100];
        this->n_p = 0;
        this->length = 0;
        this->capacity = 100;
    }

    ~Polyline()
    {
        delete[] this->p_x;
        delete[] this->p_y;
        this->n_p = 0;
        this->length = 0;
    }
    // �������� ��������� ����� � �������
    void addPoint(double x, double y)
    {
        this->n_p++;
        if (this->n_p == this->capacity)
        {
            this->capacity *= 2;
            double* new_p_x = new double[this->capacity];
            double* new_p_y = new double[this->capacity];
            for (int i = 0; i < (n_p - 1); i++)
            {
                new_p_x[i] = this->p_x[i];
                new_p_y[i] = this->p_y[i];
            }
            delete[] this->p_x;
            delete[] this->p_y;
            this->p_x = new_p_x;
            this->p_y = new_p_y;
        }
        this->p_x[n_p - 1] = x;
        this->p_y[n_p - 1] = y;
        if (n_p != 1)
        {
            this->length += sqrt((x - this->p_x[n_p - 2]) * (x - this->p_x[n_p - 2]) +
                                 (y - this->p_y[n_p - 2]) * (y - this->p_y[n_p - 2]));
        }
    }

    // �������� ��������� ����� � ������� � ������ ������
    unsigned int getNumberOfPoints() const
    {
        return this->n_p;
    }

    // �������� ����� ������� � ������ ������
    double getLength() const
    {
        return this->length;
    }

    // �������� x-���������� i-�� ����� �������, ����� ���������� � ������� ����������
    // (�������������, ��� ����� i ������ ������, ��� ��, ������� ���� getNumberOfPoints())
    double getX(unsigned int i) const
    {
        return p_x[i];
    }

    // �������� y-���������� i-�� ����� �������, ����� ���������� � ������� ����������
    // (�������������, ��� ����� i ������ ������, ��� ��, ������� ���� getNumberOfPoints())
    double getY(unsigned int i) const
    {
        return p_y[i];
    }
private:
    unsigned int n_p;
    double length;
    double* p_x;
    double* p_y;
    unsigned int capacity;
};

int main()
{
    Polyline p;
    p.addPoint(0.0, 0.0);
    p.addPoint(4.0, 0.0);
    p.addPoint(4.0, 4.0);
    cout << "Length: " << p.getLength() << endl;
    cout << "Points:" << endl;
    for(unsigned int i = 0; i < p.getNumberOfPoints(); i++) {
        cout << p.getX(i) << " " << p.getY(i) << endl;
    }
    return 0;
}
