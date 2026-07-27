#pragma once
#include <iostream>
#include <chrono>

class Timer
{
public:
    void start();
    void stop();
    double get_time() const;
    Timer() : is_measuring(false) {}
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop_time;
    bool is_measuring;
};


void Timer::start()
{
    if (is_measuring) return;
    is_measuring = true;
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop()
{
    if (!is_measuring) return;
    is_measuring = false;
    stop_time = std::chrono::high_resolution_clock::now();
}

double Timer::get_time() const
{
    if(is_measuring) return std::chrono::duration<double, std::micro>(std::chrono::high_resolution_clock::now() - start_time).count();
    return std::chrono::duration<double, std::micro>(stop_time - start_time).count();
}