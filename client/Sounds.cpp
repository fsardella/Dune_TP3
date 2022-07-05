#include "Sounds.h"
#include <string>
#include <iostream>

#define MUSIC_PATH "../client/sounds/dune.mp3"
#define SOUNDS_PATH "../client/sounds/"
#define EXTENTION ".wav"
#define MAX_EFFECTS 29
#define VOLUME 50
#define MAX_PLAYING 8

/*
Pre-Condiciones: Constructor de Sound Manager.
Post-Condiciones: -
*/

SoundManager::SoundManager()
: music(nullptr),
  musicIsPlaying(false) {
}

/*
Pre-Condiciones: Se pushea en un vector de reproducibles los sonidos que
actualmente se quieren reproducir en el juego.
Post-Condiciones: -
*/

void SoundManager::push(int soundId, int volume) {
    Mix_Chunk* sound = sounds[soundId];
    Mix_VolumeChunk(sound, volume);
    soundsToPlay.push_back(sound);
}

/*
Pre-Condiciones: Se cargan los sonidos que se van a reproducir durante
el transcurso del juego en un vector.
Post-Condiciones: -
*/

void SoundManager::loadSounds() {
    music = Mix_LoadMUS(MUSIC_PATH);
    for (int i = 0; i <= MAX_EFFECTS; i++) {
        sounds.emplace_back(Mix_LoadWAV((SOUNDS_PATH + std::to_string(i)
                                         + EXTENTION).c_str()));
    }
}

/*
Pre-Condiciones: Reproduce los sonidos guardados en un vector de reproducibles 
y la música.
Post-Condiciones: -
*/

void SoundManager::playSounds() {
    for (size_t i = 0; i < soundsToPlay.size() && i < MAX_PLAYING; i++) {
        if (Mix_Playing(i) != 1) {
            Mix_PlayChannel(i, soundsToPlay[i], 0);
        }
    }

    if (!musicIsPlaying) {
        Mix_VolumeMusic(VOLUME);
        if (Mix_PlayMusic(music, -1) == -1) {
            std::cout << "Failed reproducing music" << std::endl;
        }
        musicIsPlaying = true;
    }

    soundsToPlay.clear();
}

/*
Pre-Condiciones: Destructor de Sound Manager.
Post-Condiciones: -
*/

SoundManager::~SoundManager() {
    for (int i = 0; i < MAX_EFFECTS; i++) {
        Mix_FreeChunk(sounds[i]);
    }
    Mix_FreeMusic(music);
    Mix_Quit();
}
