/*
 * No-op stub for nfc::ProbesManager.
 *
 * Used when SCORBIT_SDK_ENABLE_NFC_TPM is OFF (e.g. on Windows, where the real
 * nfc library's serial-port transport relies on POSIX termios/ioctl APIs).
 *
 * This provides the same public surface that net/game_state consume, with every
 * method a no-op: nfc() returns a null probe, so the NFC code paths (gated on
 * "m_isNfcCapable") stay inert at runtime.
 */

#pragma once

#include <string>
#include <memory>
#include <functional>
#include <optional>
#include <cstdint>

class ProbeBase;
class ProbeNFC;

namespace nfc {

using probe_t = uint32_t;

enum ProbeType : probe_t {
    None = 0,
    NFC = 1u << 2,

    All = NFC
};

enum class NfcLedMode {
    Idle,
    GameSession,
};

using ProbeDisplayCallback = std::function<void(ProbeBase *probe, const std::string &device)>;

class ProbesManager
{
public:
    ProbesManager() = default;

    auto enumerate(probe_t /*probesSet*/, const std::string /*pbspk2commPath*/ = {},
                   const ProbeDisplayCallback & /*callback*/ = nullptr) -> void { }

    auto nfc() const -> const std::shared_ptr<ProbeNFC> & { return m_nfc; }

    auto isNfcTagRead() const -> bool { return false; }
    auto setNfcTag(const std::string & /*tag*/) -> bool { return false; }
    auto setNfcLeds(NfcLedMode /*mode*/) -> bool { return false; }

    auto setDiscoveryDescription(uint64_t /*providerSerial*/, const std::string & /*gameName*/,
                                 const std::string & /*providerInfo*/,
                                 const std::string & /*extraInfo*/) -> bool { return false; }

    auto probesBootReason(ProbeType /*probeType*/) -> std::optional<std::string> { return std::nullopt; }

private:
    std::shared_ptr<ProbeNFC> m_nfc;
};

} // namespace nfc
