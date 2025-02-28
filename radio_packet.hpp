#ifndef RADIO_PACKET_HPP
#define RADIO_PACKET_HPP

#include <cstdint>
#include <cstddef>
#include <time.h>
#include <memory>

#include "timestamp.hpp"

enum class PacketType : uint8_t {
    UNKNOWN = 0,
    TELEMETRY,
    EXECUTED,
    COMMAND
};
#define NUM_PACKET_TYPES 3 // Update as new packet types are created

enum class PacketFlags : uint8_t {
    NONE = 0,
    RELATIVE_TIME = 1 << 0,
    // Not yet exhaustive
};

class RadioPacket {
public:
    RadioPacket(const char *callsign, PacketType type, SystemTimestamp timestamp);

    // to convert into a binary representation and back
    virtual size_t serialize(uint8_t *buffer, size_t buffer_size) const;
    static PacketType parse_type(const uint8_t *buffer, size_t buflen);
    // static std::unique_ptr<RadioPacket> deserialize(const uint8_t *buffer, size_t buflen);

    bool hasFlag(PacketFlags flag) const;

    // Crazy voodoo c++ magic
    virtual ~RadioPacket() = default;

protected:
    const char *callsign_;
    PacketType type_;
    PacketFlags flags_;
    time_t timestamp_;
};

#endif // RADIO_PACKET_HPP
