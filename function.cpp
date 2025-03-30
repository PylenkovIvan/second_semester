#include <iostream>
#include <functional>
using namespace std;

template<typename T, typename... Types>
void func_for_func(T func, Types... args)
{
    func(forward<Types>(args)...);
}

void func(int x, int y)
{
    cout << x + y;
}

int main()
{
    func_for_func(&func, 20, 10);
}
