//
// Created by Domakingo on 08/07/2024.
//

#include "soundengine.hpp"
#include <thread>

// Define the global sound variables
shared_ptr<Sound> shotSfx;

SoundEngine::SoundEngine() {
    shotSfx = getSound("sfx/shot.wav", 30.0f);
}

shared_ptr<Sound> SoundEngine::getSound(const String& fileName, float volume) {
    auto sound = make_shared<Sound>();
    auto buffer = make_shared<SoundBuffer>();
    if (!buffer->loadFromFile("assets/audio/" + fileName)) {
        cerr << "Error loading sound file: " << fileName.toAnsiString() << endl;
        return nullptr;
    }
    sound->setBuffer(*buffer);
    sound->setVolume(volume);
    activeBuffers.push_back(buffer); // Keep the buffer alive
    return sound;
}

void SoundEngine::playSound(shared_ptr<Sound> sound) {
    lock_guard<mutex> lock(soundMutex);
    sound->play();
    activeSounds.push_back(sound);
}

void SoundEngine::stopSound(shared_ptr<Sound> sound) {
    lock_guard<mutex> lock(soundMutex);
    sound->stop();
    activeSounds.remove(sound);
}

void SoundEngine::fadeOutAndStopSound(shared_ptr<Sound> sound, float duration) {
    thread([this, sound, duration]() {
        float initialVolume = sound->getVolume();
        int steps = 30;
        float stepDuration = duration / steps;
        float volumeStep = initialVolume / steps;

        for (int i = 0; i < steps; ++i) {
            {
                lock_guard<mutex> lock(soundMutex);
                sound->setVolume(initialVolume - volumeStep * i);
            }
            this_thread::sleep_for(chrono::milliseconds(static_cast<int>(stepDuration * 1000)));
        }

        {
            lock_guard<mutex> lock(soundMutex);
            sound->stop();
            activeSounds.remove(sound);
        }

        cout << "finito";
    }).detach();
}

shared_ptr<Sound> SoundEngine::getShotSfx() {
    return shotSfx;
}

