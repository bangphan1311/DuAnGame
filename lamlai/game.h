#ifndef GAME_H
#define GAME_H

#include "graphics.h"  /

#define INITIAL_SPEED 3
#define JUMP_STRENGTH -18
#define GRAVITY 0.65
#define GROUND_Y 400
#define BACKGROUND_SPEED 5

struct Mouse {
    int x, y;
    double dy;
    bool isJumping;
    SDL_Texture* texture;

    Mouse(SDL_Texture* tex,int startX = 100, int startY = GROUND_Y)
        : x(startX), y(startY), dy(0), isJumping(false), texture(tex) {}

    void jump() {
        if (!isJumping) {
            dy = JUMP_STRENGTH;
            isJumping = true;
        }
    }

    void applyGravity() {
        if (isJumping) {
            dy += GRAVITY;
            y += dy;

            if (y >= GROUND_Y) {
                y = GROUND_Y;
                dy = 0;
                isJumping = false;
            }
        }
    }

    void update() {
        applyGravity();
    }
};
struct Obstacle {
    int x, y, width, height;
    SDL_Texture* texture;

    Obstacle(SDL_Texture* tex, int startX, int startY, int w, int h)
        : x(startX), y(startY), width(w), height(h), texture(tex) {}

    void update() {
        x -= BACKGROUND_SPEED;
        if (x + width < 0) {
            x = SCREEN_WIDTH;
        }
    }

    void render(const Graphics& graphics) const{

    SDL_Rect dest = {x, y, width, height};
    SDL_RenderCopy(graphics.renderer, texture, NULL, &dest);
}




};

bool checkCollision(const Mouse& mouse, const Obstacle& obstacle) {
    SDL_Rect mouseRect = {mouse.x + 20, mouse.y + 30, 40, 40};
    SDL_Rect obstacleRect = {obstacle.x + 10, obstacle.y + 10, obstacle.width - 20, obstacle.height - 20};
    return SDL_HasIntersection(&mouseRect, &obstacleRect);
}




void render(const Mouse& mouse, const Graphics& graphics) {
    SDL_Rect dest = {mouse.x+10, mouse.y-15, 95, 95};
    SDL_RenderCopy(graphics.renderer, mouse.texture, NULL, &dest);
}




#endif
