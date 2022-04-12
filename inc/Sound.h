#ifndef SOUND_H
#define SOUND_H

#define INCLUDE_SDL_MIXER
#define SOUND_TYPE "Sound"
#define CHANNEL -1

#include <Component.h>
#include "SDL_include.h"

class Sound : public Component{
public:
    explicit Sound(GameObject &associated);
    Sound(GameObject &associated, string file);
    ~Sound() override;

    void Play(int times = 1);
    void Stop();
    void Open(string file);
    bool IsOpen();

    void Update(float dt) override;
    void Render() override;
    bool Is(string type) override;
private:
    Mix_Chunk* chunk;
    int channel;
};

#endif 