#include <iostream>
#include <SDL.h>
#include "Game.h"

#define WIDTH 1024
#define HEIGHT 768

void check_val(int val) {
	if (val < 0) {
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}

void *check_ptr(void *ptr) {
	if (ptr == NULL) {
		std::cerr << "Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
	return ptr;
}

int main() {
	check_val(SDL_Init(SDL_INIT_VIDEO));
	check_val(TTF_Init());
	SDL_Window *window = static_cast<SDL_Window *>(check_ptr(SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)));
	SDL_Renderer *renderer = static_cast<SDL_Renderer *>(check_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

	Game game(WIDTH, HEIGHT);
	game.init(renderer);

	bool quit = false, paused = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					quit = true;
				} break;
				case SDL_KEYDOWN: {
					switch (event.key.keysym.sym) {
						case SDLK_SPACE: {
							if (paused) {
								paused = !paused;
							}
						} break;
					}
				} break;
			}
		}

		if (game.scored()) {
			paused = true;
			game.update_score(renderer);
		}
		if (!paused) {
			game.update();
		}
		game.render(renderer);
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
