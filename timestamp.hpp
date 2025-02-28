#ifndef TIMESTAMP_HPP
#define TIMESTAMP_HPP

#include<ctime>

enum class TimeFormat: char {
    HostRelativeTime,
    ExternalTimescale,
    GPSTime,
};

class SystemTimestamp {
    public:
        SystemTimestamp(TimeFormat format, time_t time): format(format), time(time) {}
        static SystemTimestamp from_GPS(time_t gps_time) { return SystemTimestamp(TimeFormat::GPSTime, gps_time); }
        static SystemTimestamp from_relative(time_t board_time) { return SystemTimestamp(TimeFormat::HostRelativeTime, board_time); }
        TimeFormat format;
        time_t time;
};


#endif // TIMESTAMP_HPP