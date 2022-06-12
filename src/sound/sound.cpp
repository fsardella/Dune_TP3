#include "sound.h"

Sound::Sound(const char* path) : sound(Mix_LoadWAV(path)) {}

int Sound::set_panning(int left_panning, int right_panning) { // returns 0 on error
    return Mix_SetPanning(MIX_CHANNEL_POST, left_panning, right_panning);
}

int Sound::set_distance(int distance) { // returns 0 on error
    return Mix_SetDistance(MIX_CHANNEL_POST, distance);
}

int Sound::set_position(int left_position, int right_position) { // returns 0 on error
    return Mix_SetPosition(MIX_CHANNEL_POST, left_position, right_position);
}

int Sound::set_reverse_stereo() { // returns 0 on error
    return Mix_SetReverseStereo(MIX_CHANNEL_POST, 1);
}

int Sound::play_sound(int volume) { // returns -1 on error
    // Mix_VolumeChunk(this->sound, volume);
    return Mix_PlayChannel(-1, this->sound, 0);
}

Sound::Sound(Sound&& other): sound(other.sound) {
    other.sound = nullptr;
}

Sound &Sound::operator=(Sound&& other) {
    if (this == &other) {
        return *this;
    }
    if ((sound != nullptr) && (sound != other.sound)) {
        Mix_FreeChunk(this->sound);
    }

    this->sound = other.sound;
    other.sound = nullptr;

    return *this;
}

Sound::~Sound() {
    Mix_FreeChunk(this->sound);
}