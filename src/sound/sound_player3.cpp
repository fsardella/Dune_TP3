#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

int main() {
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

    Mix_Chunk* sound_1 = Mix_LoadWAV("09_Options.wav");
    Mix_Chunk* sound_2 = Mix_LoadWAV("09_Options.wav");
    Mix_Chunk* sound_3 = Mix_LoadWAV("09_Options.wav");
    Mix_Chunk* sound_4 = Mix_LoadWAV("09_Options.wav");

    Mix_PlayChannel(-1, sound_1, 0);
    SDL_Delay(3000);
    Mix_PlayChannel(1, sound_2, 0);
    SDL_Delay(3000);
    Mix_PlayChannel(2, sound_3, 0);
    SDL_Delay(3000);
    Mix_PlayChannel(3, sound_4, 0);
    SDL_Delay(3000);

    return 0;

}