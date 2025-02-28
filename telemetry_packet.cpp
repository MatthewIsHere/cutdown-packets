#include "telemetry_packet.hpp"

#include <cstring>

size_t TelemetryPacket::serialize(uint8_t *buffer, size_t buflen) const {
    size_t preamble_offset = RadioPacket::serialize(buffer, buflen);
    if (preamble_offset == 0) {
        return 0;
    }
    size_t offset = preamble_offset;
    buffer[offset++] = static_cast<uint8_t>(relays_);
    memcpy(buffer+offset, sensors_, sizeof(*sensors_)); offset += sizeof(*sensors_);
    memcpy(buffer+offset, gps_, sizeof(*gps_)); offset += sizeof(*gps_);
    return offset;
}