#ifndef SOUND_H
#define SOUND

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

class Sound {
    Mix_Chunk* sound;

 public:
    Sound(const char* path); // o string const std::string& path
    int set_panning(int left_panning, int right_panning);
    int set_distance(int distance);
    int set_position(int left_position, int right_position);
    int set_reverse_stereo();
    int play_sound(int volume);
    
    Sound(const Sound& other) = delete;
    Sound& operator=(const Sound& other) = delete;

    Sound(Sound&& other);
    Sound& operator=(Sound&& other);

    ~Sound();
};


#endif