#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 600
#define GAME_TITLE "Andre Lucas de Sousa Pinto 17/0068251"

#define SDL_FLAGS (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)
#define IMG_FLAGS IMG_INIT_JPG
#define MIX_FLAGS MIX_INIT_OGG
#define CHUNKSIZE 1024
#define CHANNELS 32
#define WINDOWS_FLAGS 0
#define RENDERER_INDEX -1
#define RENDERER_FLAGS SDL_RENDERER_ACCELERATED
#define GAMEDELAY 33

#include "Game.h"
#include "SDL_include.h"
#include "Errors.h"

Game* Game::instance = nullptr;

Game::Game(
    string title,
    int width,
    int height
){
    if (Game::instance != nullptr){
        cout << "Game already instancied" << endl;
        exit(MULTIPLE_GAMES_ERROR);
    }

    Game::instance = this;

    if (SDL_Init(SDL_FLAGS)){
        cout << SDL_GetError() << endl;
        exit(SDL_INIT_ERROR);
    }

    if (IMG_Init(IMG_FLAGS) != IMG_FLAGS){
        cout << SDL_GetError() << endl;
        exit(IMG_INIT_ERROR);
    }

    if (Mix_Init(MIX_FLAGS) != MIX_FLAGS){
        cout << SDL_GetError() << endl;
        exit(MIX_INIT_ERROR);
    }

    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY, 
        MIX_DEFAULT_FORMAT, 
        MIX_DEFAULT_CHANNELS,
        CHUNKSIZE
    )){
        cout << SDL_GetError() << endl;
        exit(MIX_OPEN_AUDIO_ERROR);
    }

    if (Mix_AllocateChannels(CHANNELS) != CHANNELS){
        cout << SDL_GetError() << endl;
        exit(MIX_ALLOCATE_CHANNELS_ERROR);
    }

    if (!(window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        WINDOWS_FLAGS
    ))) {
        cout << SDL_GetError() << endl;
        exit(SDL_CREATE_WINDOW_ERROR);
    }

    if (!(renderer = SDL_CreateRenderer(
        window,
        RENDERER_INDEX,
        RENDERER_FLAGS
    ))) {
        cout << SDL_GetError() << endl;
        exit(SDL_CREATE_RENDER_ERROR);
    }

    state = new State();
}

Game::~Game(){
    delete state;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_CloseAudio();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

Game& Game::GetInstance(){
    if(instance == nullptr){
        instance = new Game(
            GAME_TITLE, 
            SCREEN_WIDTH, 
            SCREEN_HEIGHT
        );
    }
    return *instance;
}

State& Game::GetState(){
    return *state;
}

SDL_Renderer* Game::GetRenderer(){
    return renderer;
}

void Game::Run(){
    while(!state->QuitRequested()){
        state->Update(GAMEDELAY);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(GAMEDELAY); 
    }
}