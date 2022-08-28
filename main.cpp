#include <iostream>
#include <SDL.h>

#define WIDTH 1024
#define HEIGHT 768
#define PADDING 25

#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 325
#define PADDLE_SPEED 6

#define BALL_WIDTH 40
#define BALL_HEIGHT 40

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
	SDL_Window *window = static_cast<SDL_Window *>(check_ptr(SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE)));
	SDL_Renderer *renderer = static_cast<SDL_Renderer *>(check_ptr(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

	SDL_Rect board = {0, 0, WIDTH, HEIGHT};
	SDL_Rect left_paddle = {board.x + PADDING, (board.h / 2) - (PADDLE_HEIGHT / 2), PADDLE_WIDTH, PADDLE_HEIGHT};
	SDL_Rect right_paddle = {(board.x + board.w) - (PADDING + PADDLE_WIDTH), (board.h / 2) - (PADDLE_HEIGHT / 2), PADDLE_WIDTH, PADDLE_HEIGHT};
	SDL_Rect ball = {(board.w / 2) - (BALL_WIDTH / 2), (board.h / 2) - (BALL_HEIGHT / 2), BALL_WIDTH, BALL_HEIGHT};

	int dx = 2, dy = 2;
	// TODO(__LUNA__): Research and implement game physics
	//float dt = 1.0 / 60.0;
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


		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_W] && left_paddle.y > 0) {
			left_paddle.y -= PADDLE_SPEED;
		}  else if (state[SDL_SCANCODE_S] && (left_paddle.y + left_paddle.h) < HEIGHT) {
			left_paddle.y += PADDLE_SPEED;
		}
		if (state[SDL_SCANCODE_UP] && right_paddle.y > 0) {
			right_paddle.y -= PADDLE_SPEED;
		} else if (state[SDL_SCANCODE_DOWN] && (right_paddle.y + right_paddle.h) < HEIGHT) {
			right_paddle.y += PADDLE_SPEED;
		}

		if ((ball.x < left_paddle.x + left_paddle.w  && (ball.y + ball.w > left_paddle.y && ball.y < left_paddle.y + left_paddle.h)) ||
			(ball.x + ball.w > right_paddle.x && (ball.y + ball.w > right_paddle.y && ball.y < right_paddle.y + right_paddle.h))) {
			dx = -dx;
		}
		if (ball.y < 0 || ball.y + ball.h > HEIGHT) {
			dy = -dy;
		}

		if (ball.x < 0) {
			ball = {(board.w / 2) - (BALL_WIDTH / 2), (board.h / 2) - (BALL_HEIGHT / 2), BALL_WIDTH, BALL_HEIGHT};
			dx = -dx;
			paused = true;
		} else if (ball.x + ball.w > WIDTH) {
			ball = {(board.w / 2) - (BALL_WIDTH / 2), (board.h / 2) - (BALL_HEIGHT / 2), BALL_WIDTH, BALL_HEIGHT};
			dx = -dx;
			paused = true;
		}

		if (!paused) {
			ball.x += dx;
			ball.y += dy;
		}

		SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);

		SDL_RenderFillRect(renderer, &board);
		SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &left_paddle);
		SDL_RenderFillRect(renderer, &right_paddle);
		SDL_RenderFillRect(renderer, &ball);

		SDL_RenderDrawLine(renderer, board.w / 2, 0, board.w / 2, board.h);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
