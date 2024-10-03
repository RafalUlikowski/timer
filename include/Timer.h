#ifndef TIMER_LIBRARY_H
#define TIMER_LIBRARY_H

#include <string>
#include <memory>
#include <map>
#include <chrono>

namespace ite {
    enum TimeConsts {
        NANOSECONDS_TIME    =   1,
        MICROSECONDS_TIME   =   1000,
        MILLISECONDS_TIME   =   1000000,
        SECONDS_TIME        =   1000000000
    };

    std::string getUnit(size_t);

    class Timer {
    public:
        Timer();

        // Ustawia czas startowy na moment wywolania metody
        void start();

        // Dodanie czasu do tych zapisanych przez licznik
        // Jest tez wykorzystywane wewnetrzenie do zapisywania czasow licznika
        void add_time(const std::string&, std::chrono::duration<long long, std::ratio<1, 1000000000>>);

        // Zapisuje czas miedzy wywolanie start(), a wywolaniem tej metody
        void save_time(const std::string&);

        // Usuwa czas przechowywany przez obiekt
        void remove_time(const std::string&);

        // Zwraca dany czas w ns
        std::chrono::duration<long long, std::ratio<1, 1000000000>> operator[](const std::string&);

        // Zwraca dany czas w przeliczeniu na wybrana jednostke czasu
        std::string operator()(const std::string&, TimeConsts);

    private:
        // Zwraca czas miedzy ostatnim start(), a wywolaniem tej metody
        std::chrono::duration<long long int, std::ratio<1, 1000000000>> mStop();

        // Ostatnie wywolanie start()
        std::chrono::time_point<std::chrono::high_resolution_clock , std::chrono::duration<long long, std::ratio<1, 1000000000>>> mStartTime;

        // Zapisane czasy
        std::map<std::string, std::chrono::duration<long long, std::ratio<1, 1000000000>>> mSavedTimes;
    };
} // ite

#endif //TIMER_LIBRARY_H
