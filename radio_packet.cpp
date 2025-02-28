#include "radio_packet.hpp"
#include <cstring>

#define CALLSIGN_FIELD_LEN 10

RadioPacket::RadioPacket(const char* callsign, PacketType type, PacketFlags flags)
    : callsign_(callsign), type_(type), flags_(flags) {}

size_t RadioPacket::serialize(uint8_t *buffer, size_t buflen) const {
    if (buflen < CALLSIGN_FIELD_LEN + 1 + 1 + sizeof(time_t)) {
        return 0; // Not enough space for preable
    }
    // add preamble
    size_t offset = 0;
    strncpy((char*) buffer + offset, callsign_, CALLSIGN_FIELD_LEN); offset+=CALLSIGN_FIELD_LEN;
    buffer[offset++] = static_cast<uint8_t>(type_); // Static cast compile-time converts the enum style class to dest type.
    buffer[offset++] = static_cast<uint8_t>(flags_);
    memcpy(buffer+offset, &timestamp_, sizeof(timestamp_)); offset += sizeof(timestamp_);
    return offset;
}

PacketType RadioPacket::parse_type(const uint8_t *buffer, size_t buflen) {
    if (buflen < CALLSIGN_FIELD_LEN + 1) {
        return PacketType::UNKNOWN;
    }
    PacketType type;
    uint8_t type_byte = buffer[CALLSIGN_FIELD_LEN + 1];
    if (type_byte > NUM_PACKET_TYPES) {
        type = PacketType::UNKNOWN;
    } else {
        type = static_cast<PacketType>(type_byte);
    }
    return type;
}