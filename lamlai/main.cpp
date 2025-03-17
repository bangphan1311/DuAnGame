#include <SDL.h>
#include <vector>
#include "graphics.h"
#include "game.h"

int main(int argc, char* argv[]) {
    Graphics gfx;
    gfx.init();
    SDL_Texture* obstacleTex1 = gfx.loadTexture("bt-removebg-preview.png");
    SDL_Texture* obstacleTex2 = gfx.loadTexture("rắn-removebg-preview.png");
    SDL_Texture* obstacleTex3 = gfx.loadTexture("gầ-removebg-preview.png");
    std::vector<Obstacle> obstacles;
    obstacles.push_back(Obstacle(obstacleTex1, 500, GROUND_Y + 5, 70, 70));
    obstacles.push_back(Obstacle(obstacleTex2, 1000, GROUND_Y - 10, 80, 85));
    obstacles.push_back(Obstacle(obstacleTex3, 2500, GROUND_Y - 8, 80, 80));

    SDL_Texture* mouseTexture = gfx.loadTexture("shin2-removebg-preview.png");
    Mouse mouse(mouseTexture);
    SDL_Texture* background = gfx.loadTexture("bground.jpg");
    SDL_Texture* gameOverTexture = gfx.loadTexture("over.png");

    bool running = true;
    bool gameOver = false;  // Đặt biến ngoài vòng lặp để giữ trạng thái
    int bgX = 0;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (!gameOver && event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_SPACE:
                    case SDLK_UP:
                        mouse.jump();
                        break;
                }
            }
        }

        if (!gameOver) {
            mouse.update();
            for (auto& obstacle : obstacles) {
                obstacle.update();
                if (checkCollision(mouse, obstacle)) {
                    SDL_Log("Game Over!");
                    gameOver = true;  // Khi va chạm, dừng game
                }
            }


            if (!gameOver) {
                bgX -= BACKGROUND_SPEED;
                if (bgX <= -SCREEN_WIDTH) {
                    bgX = 0;
                }
            }
        }

        gfx.prepareScene();
        gfx.renderScrollingBackground(background, bgX);

        if (gameOver) {

            SDL_Rect dest = {SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT / 2 - 260, 620, 520};
            SDL_RenderCopy(gfx.renderer, gameOverTexture, NULL, &dest);
        } else {
            for (const auto& obstacle : obstacles) {
                obstacle.render(gfx);
            }
            render(mouse, gfx);
        }

        gfx.presentScene();
        SDL_Delay(16);
    }

    gfx.quit();
    return 0;
}
