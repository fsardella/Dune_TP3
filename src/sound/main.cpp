#include "sound.h"

int main() {
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Sound s("09_Options.wav");
    s.set_distance(220);
    s.play_sound(80);
    SDL_Delay(3000);

    return 0;
}