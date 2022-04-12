#include "Music.h"
#include "Errors.h"

Music::Music(){
    music = nullptr;
}

Music::Music(string file){
    Open(file);
}

Music::~Music(){
    Mix_FreeMusic(music);
}

void Music::Play(int times){
    if(!music) {
        throw("nullptr music");
    }
    if(Mix_PlayMusic(music, times)){
        cout << SDL_GetError() << endl;
        exit(MIX_PLAY_MUSIC_ERROR);
    }
}

void Music::Stop(int msToStop){
    if(Mix_FadeOutMusic(msToStop)){
        cout << SDL_GetError() << endl;
        exit(MIX_FADE_OUT_ERROR);
    }
}

void Music::Open(string file){
    if (!(music = Mix_LoadMUS(file.c_str()))) {
        cout << SDL_GetError() << endl;
        exit(MIX_OPEN_ERROR);
    }
}

bool Music::IsOpen(){
    return music != nullptr;
}