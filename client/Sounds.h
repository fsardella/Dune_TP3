#ifndef __SOUNDS_H__
#define __SOUNDS_H__

#include <SDL_mixer.h>
#include <vector>


class SoundManager {
    Mix_Music* music;
    bool musicIsPlaying;
    std::vector<Mix_Chunk*> sounds;
    std::vector<Mix_Chunk*> soundsToPlay;
    public:
        SoundManager();
        void push(int soundId, int volume);
        void loadSounds();
        void playSounds();
       ~SoundManager();
};


#endif /*__SOUNDS_H__*/