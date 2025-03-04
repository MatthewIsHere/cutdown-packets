#ifndef TELEMETRY_PACKET_HPP
#define TELEMETRY_PACKET_HPP

#include <utility>
#include "timestamp.hpp"
#include "radio_packet.hpp"
#include "data_types.hpp"

class TelemetryPacket : public RadioPacket {
public:
    TelemetryPacket(
        const char *callsign,
        SystemTimestamp timestamp,
        struct MS8607Data *sensors,
        struct GPSData *gps,
        uint8_t relays);
    TelemetryPacket(const uint8_t *buffer, size_t buflen);

    size_t serialize(uint8_t *buffer, size_t buflen) const override;

    struct MS8607Data* getSensors() {
        return sensors_;
    }
    struct GPSData* getGPS() {
        return gps_;
    }

private:
    struct MS8607Data *sensors_;
    struct GPSData *gps_;
    uint8_t relays_;
};

#endif // TELEMETRY_PACKET_HPP