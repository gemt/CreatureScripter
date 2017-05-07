#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <ostream>

class Timer {
    typedef std::chrono::high_resolution_clock high_resolution_clock;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::nanoseconds nanoseconds;
public:
    explicit Timer(bool run = true)
    {
        if (run)
            Reset();
    }
    void Reset()
    {
        _start = high_resolution_clock::now();
    }
    int64_t Elapsed() const
    {
        return std::chrono::duration_cast<milliseconds>(high_resolution_clock::now() - _start).count();
    }
    int64_t NS() const
    {
        return std::chrono::duration_cast<nanoseconds>(high_resolution_clock::now() - _start).count();
    }
private:
    high_resolution_clock::time_point _start;
};

#endif // TIMER_H
