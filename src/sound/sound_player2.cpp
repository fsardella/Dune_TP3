#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <iostream>

std::vector<Mix_Chunk*> sounds; // Cortos
std::vector<Mix_Music*> music;


void load_sound(const char* path) {
    Mix_Chunk* s = Mix_LoadWAV(path);
    sounds.push_back(s);
}

void load_music(const char* path) {
    Mix_Music* m = Mix_LoadMUS(path); // Mix_LoadMUS
    music.push_back(m);
}

void play_sound(int s) {
    // Mix_Volume(-1, v); // Mix_VolumeChunk(sound, volume)
    Mix_PlayChannel(-1, sounds[s], 0);
}

void play_music(int m) {
    // Mix_Volume(-1, v);
    Mix_PlayMusic(music[m], -1);
}

void togglePlay() {
    if (Mix_PausedMusic() == 1) {
        Mix_ResumeMusic();
    } else {
        Mix_PauseMusic();
    }
}

void with_effects() {
    std::cout << "Panning: left" << std::endl;
    Mix_SetPanning(MIX_CHANNEL_POST, 255, 0);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Panning: right" << std::endl;
    Mix_SetPanning(MIX_CHANNEL_POST, 0, 255);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Distance: somewhat far" << std::endl;
    Mix_SetDistance(MIX_CHANNEL_POST, 128);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Distance: further" << std::endl;
    Mix_SetDistance(MIX_CHANNEL_POST, 192);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Distance: even further" << std::endl;
    Mix_SetDistance(MIX_CHANNEL_POST, 224);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Position: closest left" << std::endl;
    Mix_SetPosition(MIX_CHANNEL_POST, 270, 0);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Position: even further back" << std::endl;
    Mix_SetPosition(MIX_CHANNEL_POST, 180, 224);
    play_sound(0);
    SDL_Delay(3000);
    std::cout << "Reverse stereo" << std::endl;
    Mix_SetReverseStereo(MIX_CHANNEL_POST, 1);
    play_sound(0);
    SDL_Delay(3000);
}

int main() {
    // Mix_Init(MIX_INIT_MP3);
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    load_sound("09_Options.wav");
    load_music("09_Options.wav");

    // play_music(0);
    // play_sound(0);
    // SDL_Delay(3000);
    // togglePlay();

    with_effects();

    for (int s = 0; s < sounds.size(); s++) {
        Mix_FreeChunk(sounds[s]);
        sounds[s] = NULL;
    }
    for (int m = 0; m < music.size(); m++) {
        Mix_FreeMusic(music[m]);
        music[m] = NULL;
    }
    Mix_Quit();
}