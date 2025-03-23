#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
using namespace std;


bool find_odd(int value)
{
    return (value % 2);
}


bool find_simple(int value)
{
    if (value <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= value; i++)
    {
        if (value % i == 0)
        {
            return false;
        }
    }
    return true;
}


int square(int value)
{
    return value * value;
}


int main()
{
    vector<int> v(10);
    iota(v.begin(), v.end(), 1);

    v.resize(15);
    for (int i = 10; i < 15; i++)
    {
        cin >> v[i];
    }

    random_shuffle(v.begin(), v.end());

    auto odd = count_if(v.begin(), v.end(), find_odd);
    auto max_v = *max_element(v.begin(), v.end());
    auto min_v = *min_element(v.begin(), v.end());
    auto simple = *find_if(v.begin(), v.end(), find_simple);

    transform(v.begin(), v.end(), v.begin(), square);

    auto sum = accumulate(v.begin(), v.end(), 0);

    replace_if(v.begin(), v.begin() + 5, [](auto item){return item;}, 1);

    auto new_end = remove_if (v.begin(), v.end(), [](auto item){return item == 0;});
    v.erase(new_end, v.end());

    reverse(v.begin(), v.end());

    partial_sort(v.begin(), v.begin() + 3, v.end(), greater<int>());
    cout << "Max elements: " << v[0] << ' ' << v[1] << ' ' << v[2] << '\n';

    partial_sort(v.begin(), v.end(), v.end());

    auto range = equal_range(v.begin(), v.end(), 3);

    cout << "Count odd: " << odd << '\n';
    cout << "Max value: " << max_v << '\n';
    cout << "Min value: " << min_v << '\n';
    cout << "Simple number: " << simple << '\n';
    cout << "Sum: " << sum << '\n';
    cout << "Range: " << range.first - v.begin() << ' ' << range.second - v.begin() << '\n';
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << ' ';
    }

    fstream f_out("output.txt", ios::out);

    copy(v.begin(), v.end(), ostream_iterator<int>(f_out, " "));
    f_out << '\n';

    f_out.close();
}
