#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

const int N = 100000000;

template <typename Units = chrono::nanoseconds>
class Timer
{
public:
    Timer()
    {
        start = chrono::steady_clock::now();
    }

    ~Timer()
    {
        auto finish = chrono::steady_clock::now();
        cout << chrono::duration_cast<Units>(finish - start).count() << '\n';
    }
private:
    chrono::steady_clock::time_point start;
};

template <typename Iter, typename T>
void inner_product_wrapper(Iter begin_a, Iter end_a, Iter begin_b, T init, T& result)
{
    result = inner_product(begin_a, end_a, begin_b, init);
}

template <typename Iter, typename T>
T parallel_inner_product(Iter begin_a, Iter end_a, Iter begin_b, T init, auto num_threads)
{
    if (distance(begin_a, end_a) < 75000)
    {
        return inner_product(begin_a, end_a, begin_b, 0ll);
    }
    auto batch_size = distance(begin_a, end_a) / num_threads;

    vector<thread> threads;
    vector<T> results(num_threads);

    for(auto i = 0; i + 1 < num_threads; i++)
    {
        threads.push_back(thread(
            inner_product_wrapper<Iter, T>,
            next(begin_a, i * batch_size),
            next(begin_a, (i + 1) * batch_size),
            next(begin_b, i * batch_size),
            T(0),
            ref(results[i])));
    }

    results[results.size() - 1u] = inner_product(
        next(begin_a, (num_threads - 1) * batch_size),
        end_a,
        next(begin_b, (num_threads - 1) * batch_size), T(0));

    for (auto i = 0; i + 1 < num_threads; i++)
    {
        threads[i].join();
    }

    return accumulate(results.begin(), results.end(), init);
}

int main()
{
    vector<long long> nums_a(N);
    vector<long long> nums_b(N);
    iota(nums_a.begin(), nums_a.end(), 5);
    iota(nums_b.begin(), nums_b.end(), 1);

    long long res;
    {
        cout << "inner_product: ";
        Timer<chrono::microseconds> t;
        res = inner_product(nums_a.begin(), nums_a.end(), nums_b.begin(), 0ll);
    }
    cout << res << '\n';

    for (auto x = 2; x <= thread::hardware_concurrency(); x++)
    {
        cout << x << ": ";
        {
            Timer<chrono::microseconds> t;
            res = parallel_inner_product(nums_a.begin(), nums_a.end(), nums_b.begin(), 0ll, x);
        }
        cout << res << '\n';
    }
}
