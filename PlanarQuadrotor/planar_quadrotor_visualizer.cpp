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
    int quadrotor_size[2] = {160,15};
    int connector_size[2] = {4,25};
    int propeller_size[2] = {15,5};
    float connector_distance[2] = {quadrotor_size[0]*0.9*cos(q_theta),quadrotor_size[0]*0.9*sin(q_theta)};
    float connector_length[2] = {-connector_size[1]*sin(q_theta), connector_size[1]*cos(q_theta)};

    SDL_GetRendererOutputSize(gRenderer.get(), &scrWidth, &scrHeight);
    x = scrWidth/2;
    y = scrHeight/2;
    middle_x = x + q_x - 650;
    middle_y = y + q_y - 350;


    // thickLineColor(gRenderer.get(),middle_x-(90/2)*cos(q_theta),middle_y-(90/2)*sin(q_theta), middle_x+(90/2)*cos(q_theta), middle_y+(90/2)*sin(q_theta), 10, 0xFF000000);
    float quadrotor_left[2] = {middle_x-quadrotor_size[0]/2*cos(q_theta),middle_y-quadrotor_size[0]/2*sin(q_theta)};  
    float quadrotor_right[2] = {middle_x+quadrotor_size[0]/2*cos(q_theta),middle_y+quadrotor_size[0]/2*sin(q_theta)};
    
    float connector_left_1[2] = {quadrotor_right[0]-connector_distance[0],quadrotor_right[1]-connector_distance[1]};
    float connector_left_2[2] = {quadrotor_right[0]-connector_distance[0]-connector_length[0],quadrotor_right[1]-connector_distance[1]-connector_length[1]};
    float connector_right_1[2] = {quadrotor_left[0]+connector_distance[0],quadrotor_left[1]+connector_distance[1]};
    float connector_right_2[2] = {quadrotor_left[0]+connector_distance[0]-connector_length[0],quadrotor_left[1]+connector_distance[1]-connector_length[1]};

    float propeller_left_1[2] = {connector_left_2[0]+propeller_size[0], connector_left_2[1]};
    float propeller_left_2[2] = {connector_left_2[0]-propeller_size[0], connector_left_2[1]};
    float propeller_right_1[2] = {connector_right_2[0]+propeller_size[0], connector_right_2[1]};
    float propeller_right_2[2] = {connector_right_2[0]-propeller_size[0], connector_right_2[1]};

    thickLineColor(gRenderer.get(),quadrotor_left[0], quadrotor_left[1], quadrotor_right[0], quadrotor_right[1], quadrotor_size[1], 0xFF000000);
    
    thickLineColor(gRenderer.get(),connector_left_1[0], connector_left_1[1], connector_left_2[0], connector_left_2[1],connector_size[0], 0xFFFF00FF);
    thickLineColor(gRenderer.get(),connector_right_1[0], connector_right_1[1], connector_right_2[0], connector_right_2[1],connector_size[0], 0xFFFF00FF);

    filledEllipseColor(gRenderer.get(),propeller_left_1[0], propeller_left_1[1], propeller_size[0], propeller_size[1], 0xFFFF0000);
    filledEllipseColor(gRenderer.get(),propeller_right_1[0], propeller_right_1[1], propeller_size[0], propeller_size[1], 0xFFFF0000);
    filledEllipseColor(gRenderer.get(),propeller_left_2[0], propeller_left_2[1], propeller_size[0], propeller_size[1], 0xFFFF0000);
    filledEllipseColor(gRenderer.get(),propeller_right_2[0], propeller_right_2[1], propeller_size[0], propeller_size[1], 0xFFFF0000);
    
    // filledEllipseColor(gRenderer.get(),q_x-41, q_y-30, 20, 5, 0xFFFF00FF);
    // filledEllipseColor(gRenderer.get(),q_x+41, q_y-30, 20, 5, 0xFFFF00FF);
    // filledEllipseColor(gRenderer.get(),q_x+81, q_y-30, 20, 5, 0xFFFF00FF);
    
    // thickLineColor(gRenderer.get(),(q_x-70)-(90/2)*cos(q_theta), (q_y-5)-(90/2)*sin(q_theta), (q_x+50)+(90/2)*cos(q_theta), (q_y-5)+(90/2)*sin(q_theta), 10, 0xFF000000);


    // SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0x00);
    // SDL_Rect base = {(middle_x-730)*cos(q_theta), (middle_y-350)*sin(q_theta), 140, 10};
    // SDL_RenderFillRect(gRenderer.get(), &base);

    // SDL_SetRenderDrawColor(gRenderer.get(), 0xFF, 0x00, 0x00, 0x00);
    // SDL_Rect connector_left = {q_x-62, q_y-27, 4, 22};
    // SDL_Rect connector_right = {q_x+60, q_y-27, 4, 22};
    // SDL_RenderFillRect(gRenderer.get(), &connector_left);
    // SDL_RenderFillRect(gRenderer.get(), &connector_right);

    // SDL_SetRenderDrawColor(gRenderer.get(), 0x00, 0x00, 0x00, 0x00);
    // SDL_ wing = {q_x-70, q_y-5, 140, 10};
    // SDL_RenderFillRect(gRenderer.get(), &wing);

    // boxColor(gRenderer.get(),q_x-70, q_y-5, q_x+70, q_y+5, 0xFF000000);
    // boxColor(gRenderer.get(), q_x-62, q_y-6, q_x-60, q_y-30, 0xFF0000FF);
    // boxColor(gRenderer.get(), q_x+60, q_y-6, q_x+62, q_y-30, 0xFF0000FF);
}
