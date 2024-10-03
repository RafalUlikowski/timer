#include <chrono>
#include <fstream>
#include "Timer.h"

namespace ite {
    std::string getUnit(const size_t time) {
        switch (time) {
            case NANOSECONDS_TIME:
                return "ns";
            case MICROSECONDS_TIME:
                return "us";
            case MILLISECONDS_TIME:
                return "ms";
            case SECONDS_TIME:
                return "s";
            default:
                return "";
    }
}

    Timer::Timer() = default;

    void Timer::start() {
        // Ustawienie ostatniego czasu startowego na teraz
        mStartTime = std::chrono::high_resolution_clock ::now();
    }
    std::chrono::duration<long long, std::ratio<1, 1000000000>> Timer::mStop() {
        // Odjecie ostatniego czasu startowego od teraz
        return std::chrono::high_resolution_clock::now() - mStartTime;
    }
    void Timer::save_time(const std::string &key) {
        // Zapisanie wartosci zwroconej przez mStop()
        add_time(key, mStop());
    }
    void Timer::add_time(const std::string &key, std::chrono::duration<long long, std::ratio<1, 1000000000>> value) {
        // Zapisanie nowego czasu badz nadpisanie istniejacego o danym kluczu
        if (mSavedTimes.find(key) == mSavedTimes.end())
            mSavedTimes.emplace(key, value);
        else
            mSavedTimes[key] = value;
    }
    void Timer::remove_time(const std::string &key) {
        // Usuniecie czasu z zapisanych
        mSavedTimes.erase(key);
    }
    std::chrono::duration<long long int, std::ratio<1, 1000000000>> Timer::operator[](const std::string &key) {
        return mSavedTimes.at(key);
    }

    std::string Timer::operator()(const std::string &key, TimeConsts unit) {
        return std::to_string(operator[](key).count() / unit).append(" ").append(getUnit(unit));
    }
} // ite