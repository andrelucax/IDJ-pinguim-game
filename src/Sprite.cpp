#include "Sprite.h"
#include "Game.h"
#include "Errors.h"

Sprite::Sprite(GameObject& gameObject) : Component(gameObject){
    texture = nullptr;
}

Sprite::Sprite(GameObject& gameObject, string file) : Component(gameObject){
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
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

    associated.box.h = height;
    associated.box.w = width;

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

void Sprite::Render(){
    SDL_Rect dstrect;
    dstrect.x = (int)associated.box.x;
    dstrect.y = (int)associated.box.y;
    dstrect.h = (int)associated.box.h;
    dstrect.w = (int)associated.box.w;

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

void Sprite::Update(float dt){}

bool Sprite::Is(string type){
    return type == SPRITE_TYPE;
}