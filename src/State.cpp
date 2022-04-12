
#include "Face.h"
#include "State.h"
#include "Sound.h"
#include "Game.h"

State::State(){
    GameObject *gameObject = new GameObject();
    gameObject->AddComponent(new Sprite(*gameObject, "assets/img/ocean.jpg"));
    objectArray.emplace_back(gameObject);

    LoadAssets();
    quitRequested = false;
    music.Play(-1);
}

State::~State() {
    objectArray.clear();
}

bool State::QuitRequested(){
    return quitRequested;
}

void State::LoadAssets(){
    music.Open("assets/msc/stageState.ogg");
}

void State::Update(float dt){
    Input();
    for(size_t i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for(size_t i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render(){
    for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it)->Render();
    }
}

void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event)) {

        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN) {

            for(int i = objectArray.size() - 1; i >= 0; --i) {
                GameObject* go = (GameObject*) objectArray[i].get();

                if(go->box.Contains( {(float)mouseX, (float)mouseY} ) ) {
                    Face* face = (Face*)go->GetComponent(FACE_TYPE);
                    if (nullptr != face) {
                        face->Damage(std::rand() % 10 + 10);
                        break;
                    }
                }
            }
        }
        if( event.type == SDL_KEYDOWN ) {
            if(event.key.keysym.sym == SDLK_ESCAPE) {
                quitRequested = true;
            } else {
                Vec2 objPos = Vec2(200, 0).GetRotated((float)(-M_PI + M_PI * (rand() % 1001) / 500.0)) + Vec2(mouseX, mouseY );
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}

void State::AddObject(int mouseX, int mouseY) {
    GameObject *go = new GameObject();
    Sprite *sprite = new Sprite(*go, "assets/img/penguinface.png");

    go->box.x = mouseX - go->box.w/2;
    go->box.y = mouseY - go->box.h/2;

    go->AddComponent(sprite);

    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);

}
