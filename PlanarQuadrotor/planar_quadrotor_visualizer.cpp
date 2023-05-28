#include "planar_quadrotor_visualizer.h"

PlanarQuadrotorVisualizer::PlanarQuadrotorVisualizer(PlanarQuadrotor *quadrotor_ptr): quadrotor_ptr(quadrotor_ptr) {}

/**
 * TODO: Improve visualizetion
 * 1. Transform coordinates from quadrotor frame to image frame so the circle is in the middle of the screen
 * 2. Use more shapes to represent quadrotor (e.x. try replicate http://underactuated.mit.edu/acrobot.html#section3 or do something prettier)
 * 3. Animate proppelers (extra points)
 */
void PlanarQuadrotorVisualizer::render(std::shared_ptr<SDL_Renderer> &gRenderer) {
    Eigen::VectorXf state = quadrotor_ptr->GetState();
    float q_x, q_y, q_theta;
    int o_x, o_y;
    q_x = state[0];
    q_y = state[1];
    q_theta = state[2];

    int scrWidth, scrHeight;
    int x, y;
    int middle_x, middle_y;

    SDL_GetRendererOutputSize(gRenderer.get(), &scrWidth, &scrHeight);
    x = scrWidth/2;
    y = scrHeight/2;
    middle_x = x + q_x;
    middle_y = y + q_y;


    thickLineColor(gRenderer.get(),(middle_x-730)-((middle_x-730)/2)*cos(q_theta), (middle_y-350)-((middle_y-350)/2)*sin(q_theta), (middle_x-590)+((middle_x-590)/2)*cos(q_theta), (middle_y-350)+((middle_y-350)/2)*sin(q_theta), 10, 0xFF000000);


    // SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0x00);
    // SDL_Rect base = {(middle_x-730)*cos(q_theta), (middle_y-350)*sin(q_theta), 140, 10};
    // SDL_RenderFillRect(gRenderer.get(), &base);

    // SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0x00);
    // SDL_Rect connector_left = {q_x-62, q_y-27, 4, 22};
    // SDL_Rect connector_right = {q_x+60, q_y-27, 4, 22};
    // SDL_RenderFillRect(gRenderer.get(), &connector_left);
    // SDL_RenderFillRect(gRenderer.get(), &connector_right);

    // filledEllipseColor(gRenderer.get(),q_x-81, q_y-30, 20, 5, 0xFFFF00FF);
    // filledEllipseColor(gRenderer.get(),q_x-41, q_y-30, 20, 5, 0xFFFF00FF);
    // filledEllipseColor(gRenderer.get(),q_x+41, q_y-30, 20, 5, 0xFFFF00FF);
    // filledEllipseColor(gRenderer.get(),q_x+81, q_y-30, 20, 5, 0xFFFF00FF);

    // SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0x00);
    // SDL_ wing = {q_x-70, q_y-5, 140, 10};
    // SDL_RenderFillRect(gRenderer.get(), &wing);

    // boxColor(gRenderer.get(),q_x-70, q_y-5, q_x+70, q_y+5, 0xFF000000);
    // boxColor(gRenderer.get(), q_x-62, q_y-6, q_x-60, q_y-30, 0xFF0000FF);
    // boxColor(gRenderer.get(), q_x+60, q_y-6, q_x+62, q_y-30, 0xFF0000FF);
}
