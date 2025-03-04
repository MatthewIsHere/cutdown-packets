#include "telemetry_packet.hpp"

#include <cstring>

TelemetryPacket::TelemetryPacket(
    const char *callsign,
    SystemTimestamp timestamp,
    struct MS8607Data *sensors,
    struct GPSData *gps,
    uint8_t relays)
    : RadioPacket(callsign, PacketType::TELEMETRY, timestamp),
      sensors_(std::move(sensors)),
      gps_(std::move(gps)),
      relays_(relays) {}

TelemetryPacket::TelemetryPacket(const uint8_t *buffer, size_t buflen): RadioPacket(buffer, buflen) {
    size_t offset = this->data_offset_;
    this->relays_ = buffer[offset++];
    this->sensors_ = (struct MS8607Data*) (buffer + offset); offset += sizeof(struct MS8607Data);
    this->gps_ = (struct GPSData*) (buffer + offset); offset += sizeof(struct GPSData);
}

size_t TelemetryPacket::serialize(uint8_t *buffer, size_t buflen) const {
    size_t preamble_offset = RadioPacket::serialize(buffer, buflen);
    if (preamble_offset == 0) return 0;
    size_t offset = preamble_offset;
    buffer[offset++] = static_cast<uint8_t>(relays_);
    memcpy(buffer + offset, sensors_, sizeof(*sensors_));
    offset += sizeof(*sensors_);
    memcpy(buffer + offset, gps_, sizeof(*gps_));
    offset += sizeof(*gps_);
    return offset;
}