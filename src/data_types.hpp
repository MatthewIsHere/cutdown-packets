#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <cstdint>

struct MS8607Data {
    int32_t temperature;
    int32_t pressure;
    int32_t humidity;
};

struct GPSData {
    int32_t latitude;    // Latitude in millionths of degrees
    int32_t longitude;   // Longitude in millionths of degrees
    int32_t altitude;    // Altitude in tenths of meters
    int32_t satellites;  // Number of satellites
    int32_t fix_quality; // GPS fix quality
};


#endif // DATA_TYPES_HPP