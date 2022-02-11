#include "State.h"

State::State(){
    quitRequested = false;
    bg = *new Sprite();
    music = *new Music();

    LoadAssets();

    music.Play(-1);
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    bg.Open("./img/ocean.jpg");
    music.Open("./msc/stageState.ogg");
}

void State::Update(float dt){
    if (SDL_QuitRequested()){
        quitRequested = true;
    }
}

void State::Render(){
    bg.Render(0, 0);
}