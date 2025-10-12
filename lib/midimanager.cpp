#include "midimanager.h"
#include "RtMidi.h"

namespace Sculpt {

    MidiManager::~MidiManager() = default;

    MidiManager::MidiManager() {
        m_midiIn = std::make_unique<RtMidiIn>();
    }

    MidiManager& MidiManager::GetInstance() {
        static MidiManager instance;
        return instance;
    }

    uint32_t MidiManager::GetDeviceCount() {
        return m_midiIn->getPortCount();
    }

    std::string MidiManager::GetDeviceName(const uint32_t index) {
        return m_midiIn->getPortName(index);
    }

    bool MidiManager::ConnectDevice(const uint32_t index) {
        try {
            m_midiIn->openPort(index);
            return true;
        } catch (const std::exception& ) {
            return false;
        }
    }

    void MidiManager::AssignCallback(std::function<void(double, const std::vector<uint8_t>&)> callback) {
        m_userCallback = std::move(callback);
        // Set RtMidi callback to the static wrapper
        m_midiIn->setCallback(&MidiManager::Callback, this);
        // Don't ignore any messages
        m_midiIn->ignoreTypes(false, false, false);
    }

    void MidiManager::Callback(double deltatime, std::vector<uint8_t>* message, void* userData) {
        auto* manager = static_cast<MidiManager*>(userData);
        if (manager->m_userCallback && message) {
            manager->m_userCallback(deltatime, *message);
        }
    }
}