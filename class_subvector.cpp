#include <iostream>
using namespace std;

class Subvector
{
public:
    Subvector()
    {
        this->top = 0;
        this->capacity = 0;
        this->mas = nullptr;
    }

    ~Subvector()
    {
        delete[] this->mas;
    }

    bool resize(unsigned int new_capacity)
    {
        if (new_capacity == 0)
        {
            delete[] this->mas;
            this->top = 0;
            this->capacity = 0;
            this->mas = nullptr;
        }
        else
        {
            int* new_mas = new int[new_capacity];
            if (this->top > new_capacity)
            {
                this->top = new_capacity;
            }
            for (unsigned int i = 0; i < this->top; i++)
            {
                new_mas[i] = this->mas[i];
            }
            delete[] this->mas;
            this->mas = new_mas;
            this->capacity = new_capacity;
        }
    }

    bool push_back(int d)
    {
        if (this->top == this->capacity)
        {
            resize(this->capacity * 2 + 1);
        }
        this->mas[this->top] = d;
        this->top++;
        return true;
    }

    int pop_back()
    {
        if (this->top == 0)
        {
            return 0;
        }
        this->top--;
        return this->mas[this->top];
    }

    void shrink_to_fit()
    {
        if (this->top < this->capacity)
        {
            resize(this->top);
        }
    }

    void clear()
    {
        this->top = 0;
    }
private:
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

int main()
{
    Subvector* v = new Subvector;

    v->push_back(1);
    v->push_back(2);
    v->push_back(3);
    cout << "In: 1, 2, 3" << '\n';

    int check = v->pop_back();
    check += v->pop_back();
    cout << "Pop_back x2: " << (5 == check) << '\n';

    for (int i = 0; i < 10; i++)
    {
        v->push_back(i);
    }
    v->resize(5);
    check = v->pop_back();
    cout << "Resize: " << (3 == check) << '\n';

    v->resize(50);
    v->shrink_to_fit();
    check = v->pop_back();
    cout << "Shrink_to_fit: " << (2 == check) << '\n';

    v->clear();
    v->shrink_to_fit();;
    if (!(v->pop_back()))
    {
        cout << "Clear: 1";
    }
}
