#include "Sounds.h"
#include <string>
#include <iostream>

#define MUSIC_PATH "../client/sounds/dune.mp3"
#define SOUNDS_PATH "../client/sounds/"
#define EXTENTION ".wav"
#define MAX_EFFECTS 29

SoundManager::SoundManager(): musicIsPlaying(false)
{
}

//Primero pusheo con el sound id y el volumen que quiero de ese sonido, despues pongo play sounds. 

void SoundManager::push(int soundId, int volume) {
    Mix_Chunk* sound = sounds[soundId];
    Mix_VolumeChunk(sound, volume);
    soundsToPlay.push_back(sound);
}

void SoundManager::loadSounds() {
    music = Mix_LoadMUS(MUSIC_PATH);
    for (int i = 0; i <= MAX_EFFECTS; i++) {
        sounds.emplace_back(Mix_LoadWAV((SOUNDS_PATH + std::to_string(i) + EXTENTION).c_str()));
    }
}

void SoundManager::playSounds() {
    for (size_t i = 0; i < soundsToPlay.size() && i < 8; i++){
        Mix_PlayChannel(-1, soundsToPlay[i], 0);
    }

    if (!musicIsPlaying){
        if(Mix_PlayMusic(music, -1) == -1) {
            std::cout << "Failed reproducing music" << std::endl;
        }
        musicIsPlaying = true;
    }

    soundsToPlay.clear();
}

SoundManager::~SoundManager(){
    for (int i = 0; i < MAX_EFFECTS; i++) {
        Mix_FreeChunk(sounds[i]);
    }
    Mix_FreeMusic(music);
    Mix_Quit();
}