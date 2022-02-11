#include "Sprite.h"
#include "Game.h"
#include "Errors.h"

Sprite::Sprite(){
    texture = nullptr;
}

Sprite::Sprite(string file){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    SDL_DestroyTexture(texture);
}

void Sprite::Open(string file){
    if (IsOpen()){
        SDL_DestroyTexture(texture);
    }

    if (!(texture = IMG_LoadTexture(
        Game::GetInstance().GetRenderer(),
        file.c_str()
    ))) {
        cout << SDL_GetError() << endl;
        exit(IMG_LOAD_TEXTURE_ERROR);
    }

    if (SDL_QueryTexture(
        texture, 
        nullptr, 
        nullptr, 
        &width, 
        &height
    )) {
        cout << SDL_GetError() << endl;
        exit(SDL_QUERY_TEXTURE_ERROR);
    }

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(
    int x, 
    int y, 
    int w, 
    int h
){
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(
    int x, 
    int y
){
    SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;
    dstrect.h = clipRect.h;
    dstrect.w = clipRect.w;

    if(SDL_RenderCopy(
        Game::GetInstance().GetRenderer(),
        texture,
        &clipRect,
        &dstrect
    )){
        cout << SDL_GetError() << endl;
        exit(SDL_RENDER_COPY_ERROR);
    }
}

int Sprite::GetWidth(){
    return width;
}

int Sprite::GetHeight(){
    return height;
}

bool Sprite::IsOpen(){
    return texture != nullptr;
}
