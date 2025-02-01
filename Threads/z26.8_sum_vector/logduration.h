#pragma once

#include <chrono>
#include <iostream>
#include <string>
/*
#define PROFILE_CONCAT_INTERNAL(X, Y) X##Y
#define PROFILE_CONCAT(X, Y) PROFILE_CONCAT_INTERNAL(X, Y)

//Уникальное имя переменной для названия объекта
#define UNIQUE_VAR_NAME_PROFILE PROFILE_CONCAT(profileGuard, __LINE__)

#define LOG_DURATION(x) LogDuration UNIQUE_VAR_NAME_PROFILE(x)
#define LOG_DURATION_STREAM(x, y) LogDuration UNIQUE_VAR_NAME_PROFILE(x, y)
*/

// Моя реализация макроса
#define CONCAT(x, y) x##y
#define UNIQ_CONCAT(x, y) CONCAT(x,y)
#define UNIQ_OBJ_NAME UNIQ_CONCAT(logduri, __LINE__)
#define LOG_DURATION(str) LogDuration UNIQ_OBJ_NAME(str)


class LogDuration {
public:
    // заменим имя типа std::chrono::steady_clock
    // с помощью using для удобства
    using Clock = std::chrono::steady_clock;

    LogDuration(const std::string& id, std::ostream& dst_stream = std::cerr)
        : id_(id)
        , dst_stream_(dst_stream) {
    }

    ~LogDuration() {
        using namespace std::chrono;
        using namespace std::string_literals;

        const auto end_time = Clock::now();
        const auto dur = end_time - start_time_;
        dst_stream_ << id_ << ": "s << duration_cast<milliseconds>(dur).count() << " ms"s << std::endl;
    }

private:
    const std::string id_;
    const Clock::time_point start_time_ = Clock::now();
    std::ostream& dst_stream_;
};



/*Чтобы посмотреть скомпилированные директивы препроцессора - 2 способа, предварительно закоментить includ'ы 
 *gcc -o log.ii logduration.h   или g++ -E -o log.ii logduration.h
 *
LOG_DURATION("Hello");

*/
