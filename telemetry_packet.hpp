#ifndef TELEMETRY_PACKET_HPP
#define TELEMETRY_PACKET_HPP

#include <utility>
#include "radio_packet.hpp"
#include "data_types.hpp"

class TelemetryPacket : RadioPacket
{
public:
    TelemetryPacket(
        const char *callsign,
        PacketFlags flags,
        struct MS8607Data *sensors,
        struct GPSData *gps,
        uint8_t relays) : RadioPacket(callsign, PacketType::TELEMETRY, flags),
                          sensors_(std::move(sensors)),
                          gps_(std::move(gps)),
                          relays_(relays) {}

    size_t serialize(uint8_t *buffer, size_t buflen) const override;
    // static std::unique_ptr<RadioPacket> deserialize(const uint8_t *buffer, size_t buflen);

private:
    struct MS8607Data *sensors_;
    struct GPSData *gps_;
    uint8_t relays_;
};

#endif // TELEMETRY_PACKET_HPP