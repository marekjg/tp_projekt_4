#include "planar_quadrotor_visualizer.h"


PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}
/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen V
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier) V
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;

    /* x, y, theta coordinates */
    q_x = state[0]*10000000+640;
    q_y = state[1]*10000000+360;
    q_theta = state[2];

    SDL_Texture* QuadrotorTexture = SDL_CreateTexture(gRenderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 200, 30);
   /* SDL_Surface* image =NULL;
    image = SDL_LoadBMP("QuadkopterWING4.bmp");
    if (NULL==image)
    {
        std::cout<<"error\n"<<SDL_GetError;
    }
    //SDL_Surface* image = SDL_LoadBMP("QuadkopterWING4.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer.get(), image);*/
    
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
    leftBlade.x = q_x - 105;
    leftBlade.y = q_y - 25;
    leftBlade.w = 60;
    leftBlade.h = 3;
    SDL_Rect rightBlade;
    rightBlade.x = q_x + 45;
    rightBlade.y = q_y - 25;
    rightBlade.w = 60;
    rightBlade.h = 3;
    //SDL_RenderFillRect(gRenderer.get(), &quadbody);
    SDL_Point rotationCenter = {q_x,q_y};
    SDL_RenderCopyEx(gRenderer.get(),QuadrotorTexture, nullptr, &quadbody, q_theta*-80000, &rotationCenter, SDL_FLIP_NONE);
  //  SDL_RenderPresent(gRenderer.get());
    SDL_SetRenderDrawColor(gRenderer.get(),0,0,0,0);
    filledCircleColor(gRenderer.get(), mousex, mousey, 3, 0xFF0000FF);
    SDL_RenderCopyEx(gRenderer.get(),QuadrotorTexture, nullptr, &leftvert, q_theta*-80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(),QuadrotorTexture, nullptr, &rightvert, q_theta*-80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(),QuadrotorTexture, nullptr, &leftBlade, q_theta*-80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_RenderCopyEx(gRenderer.get(),QuadrotorTexture, nullptr, &rightBlade, q_theta*-80000, &rotationCenter, SDL_FLIP_NONE);
    SDL_SetRenderDrawColor(gRenderer.get(),0,0,0,0);
    filledCircleColor(gRenderer.get(), mousex, mousey, 3, 0xFF0000FF);
    //std::cout<<"mousex= "<<mousex<<" mousey= "<<mousey;

    
    
   
    //SDL_RenderCopyEx(gRenderer.get(), &quadbody, )
   /* SDL_SetRenderDrawColor(gRenderer.get(), 3, 20, 41, 1);
    
    SDL_RenderFillRect(gRenderer.get(), &leftvert);

    SDL_SetRenderDrawColor(gRenderer.get(), 3, 20, 41, 1);
    
    SDL_RenderFillRect(gRenderer.get(), &rightvert);

    SDL_SetRenderDrawColor(gRenderer.get(), 164, 157, 166, 1);
    
    SDL_RenderFillRect(gRenderer.get(), &leftBlade);

    SDL_SetRenderDrawColor(gRenderer.get(), 164, 157, 166, 1);
    
    SDL_RenderFillRect(gRenderer.get(), &rightBlade);*/



}