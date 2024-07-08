//
// Created by Domakingo on 08/07/2024.
//

#ifndef CPP_SHOOTER_SOUNDENGINE_HPP
#define CPP_SHOOTER_SOUNDENGINE_HPP


#include <SFML/Audio.hpp>
#include <iostream>
#include <memory>
#include <mutex>
#include <list>

using namespace sf;
using namespace std;

class SoundEngine {
public:
    SoundEngine();

    shared_ptr<Sound> getSound(const String& fileName, float volume);

    void playSound(shared_ptr<Sound> sound);
    void stopSound(shared_ptr<Sound> sound);
    void fadeOutAndStopSound(shared_ptr<Sound> sound, float duration);

    shared_ptr<Sound> getShotSfx();

private:
    mutex soundMutex;
    list<shared_ptr<Sound>> activeSounds; // List to keep track of active sounds
    list<shared_ptr<SoundBuffer>> activeBuffers; // List to keep track of active buffers

    shared_ptr<Sound> shotSfx;
};


#endif //CPP_SHOOTER_SOUNDENGINE_HPP
