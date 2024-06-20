#include "planar_quadrotor_visualizer.h"
//#include <SDL_mixer.h>
#include <SDL.h>
#include <cmath>

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr)
    : quadrotor_ptr(quadrotor_ptr), leftBladeAngle(0.0f), rightBladeAngle(0.0f) {}

void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    q_x = state[0] * 10000000 + 640;
    q_y = state[1] * 10000000 + 360;
    q_theta = state[2];

// Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
 //Mix_Music *backgroundSong = Mix_LoadMUS("audio/quadcopter.wav");
 //Mix_FreeMusic(backgroundSong);

    SDL_Texture* QuadrotorTexture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 30);
    if (!QuadrotorTexture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }
    
    SDL_Rect quadbody;
    quadbody.x = q_x - 75;
    quadbody.y = q_y - 5;
    quadbody.w = 150;
    quadbody.h = 20;
    SDL_Rect leftvert;
    leftvert.x = q_x - 75;
    leftvert.y = q_y - 25;
    leftvert.w = 5;
    leftvert.h = 20;
    SDL_Rect rightvert;
    rightvert.x = q_x + 70;
    rightvert.y = q_y - 25;
    rightvert.w = 5;
    rightvert.h = 30;

   
    SDL_Rect leftBlade;
    leftBlade.w = 60;
    leftBlade.h = 3;
    leftBlade.x = q_x - 75 - leftBlade.w / 2;
    leftBlade.y = q_y - 28; 

    SDL_Rect rightBlade;
    rightBlade.w = 60;
    rightBlade.h = 3;
    rightBlade.x = q_x + 75 - rightBlade.w / 2;
    rightBlade.y = q_y - 28; 

    leftBladeAngle += 5.0f; 
    if (leftBladeAngle >= 360.0f) leftBladeAngle -= 360.0f;

    rightBladeAngle -= 5.0f;  
    if (rightBladeAngle <= -360.0f) rightBladeAngle += 360.0f;

    SDL_Point rotationCenter = { q_x, q_y };

    SDL_RenderCopyEx(gRenderer.get(), QuadrotorTexture, nullptr, &quadbody, q_theta * -80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(gRenderer.get(), 0, 0, 0, 0);
    filledCircleColor(gRenderer.get(), mousex, mousey, 3, 0xFF0000FF);

    SDL_RenderCopyEx(gRenderer.get(), QuadrotorTexture, nullptr, &leftvert, q_theta * -80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(), QuadrotorTexture, nullptr, &rightvert, q_theta * -80000, &rotationCenter, SDL_FLIP_NONE);

    SDL_RenderCopyEx(gRenderer.get(), QuadrotorTexture, nullptr, &leftBlade, leftBladeAngle, nullptr, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(), QuadrotorTexture, nullptr, &rightBlade, rightBladeAngle, nullptr, SDL_FLIP_NONE);

    SDL_SetRenderDrawColor(gRenderer.get(), 0, 0, 0, 0);
    filledCircleColor(gRenderer.get(), mousex, mousey, 3, 0xFF0000FF);
}