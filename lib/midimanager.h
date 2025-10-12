#ifndef MUSICLANGUAGE_LIB_MIDIMANAGER_H
#define MUSICLANGUAGE_LIB_MIDIMANAGER_H

#include <memory>
#include <functional>

class RtMidiIn;

namespace Sculpt {
    class MidiManager {
    public:
        ~MidiManager();
        static MidiManager& GetInstance();
        uint32_t GetDeviceCount();
        std::string GetDeviceName(const uint32_t index);
        bool ConnectDevice(const uint32_t index);
        void AssignCallback(std::function<void(double, const std::vector<uint8_t>&)> callback);
    private:
        MidiManager();
        std::function<void(double, const std::vector<uint8_t>&)> m_userCallback;
        static void Callback(double deltatime, std::vector<uint8_t>* message, void* userData);
        std::unique_ptr<RtMidiIn> m_midiIn { nullptr };
    };
}

#endif // MUSICLANGUAGE_LIB_MIDIMANAGER_H