#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
using namespace std;

mutex m;
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
void accumulate_wrapper(Iter b, Iter e, T init, T& result) {
    auto sum = accumulate(b, e, init);
    m.lock();
    result += sum;
    m.unlock();
}

template <typename Iter, typename T>
T parallel_accumulate(Iter b, Iter e, T init)
{
    auto num_threads = thread::hardware_concurrency();
    auto batch_size = distance(b, e) / num_threads;

    vector<thread> threads;
    T result = T(0);

    for(auto i = 0; i + 1 < num_threads; i++)
    {
        threads.push_back(thread(accumulate_wrapper<Iter, T>,
                          next(b, i * batch_size),
                          next(b, (i + 1) * batch_size), T(0), ref(result)));
    }
    accumulate_wrapper(next(b, (num_threads - 1) * batch_size), e, init, result);
    for (auto i = 0; i + 1 < num_threads; i++)
    {
        threads[i].join();
    }
    return result;
}

int main()
{
    vector<long long> nums(N);
    iota(nums.begin(), nums.end(), 1ll);

    long long res;
    {
        Timer<chrono::milliseconds> t;
        res = accumulate(nums.begin(), nums.end(), 0ll);
    }
    cout << res << '\n';

    {
        Timer<chrono::milliseconds> t;
        res = parallel_accumulate(nums.begin(), nums.end(), 0ll);
    }
    cout << res << '\n';
}
