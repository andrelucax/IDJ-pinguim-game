#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <iostream>
#include <vector>
#include <memory>

#include "Component.h"
#include "Rect.h"

using namespace std;

class Component;

class GameObject{
public:
    GameObject();
    ~GameObject();
    
    void Update(float dt);
    void Render();
    bool IsDead();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component* GetComponent(string type);

    Rect box;
private: 
    vector<unique_ptr<Component>> components;
    bool isDead;
};

#endif