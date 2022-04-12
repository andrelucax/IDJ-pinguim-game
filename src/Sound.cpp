#include <Game.h>
#include "Sound.h"
#include "Errors.h"

Sound::Sound(GameObject &associated) : Component(associated), chunk(nullptr), channel(0) {}

Sound::Sound(GameObject &associated, string file) : Component(associated), chunk(nullptr), channel(0)  {
    Open(file);
}

Sound::~Sound(){
    if (!chunk) {
        Stop();
    }
    Mix_FreeChunk(chunk);
}

void Sound::Play(int times) {
    if(channel = Mix_PlayChannel(CHANNEL, chunk, times - 1)){
        cout << SDL_GetError() << endl;
        exit(MIX_PLAY_CHANNEL);
    }

}

void Sound::Stop() {
    if(chunk){
        Mix_HaltChannel(channel);
    }
}

void Sound::Open(string file) {
    if(!(chunk = Mix_LoadWAV(("assets/" + file).c_str()))){
        cout << SDL_GetError() << endl;
        exit(MIX_LOADWAV);
    }
}

bool Sound::IsOpen() {
    return chunk != nullptr;
}

void Sound::Update(float dt) {}

void Sound::Render() {}

bool Sound::Is(string type) {
    return type == SOUND_TYPE;
}