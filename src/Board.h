#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include "Paddle.h"
#include "Ball.h"

#define PADDLE_PADDING 25
#define PADDLE_WIDTH 25
#define PADDLE_HEIGHT 325

#define BALL_WIDTH 40
#define BALL_HEIGHT 40

#define FONT_SIZE 64

typedef enum {
	UP = -1,
	STOP,
	DOWN = 1
} Dir;

class Board {
private:
	SDL_Rect m_board;
	Paddle m_left_paddle;
	Paddle m_right_paddle;
	Ball m_ball;
	int m_player_one_score = 0;
	int m_player_two_score = 0;

	SDL_Surface *m_surface;
	SDL_Texture *m_player_one_score_t;
	SDL_Rect m_player_one_score_board;
	SDL_Texture *m_player_two_score_t;
	SDL_Rect m_player_two_score_board;

	TTF_Font *m_font;
public:
	Board() = default;
	Board(int x, int y, int w, int h);
	~Board();
	void query_text();
	void init_score_board(SDL_Renderer *renderer);

	bool scored();
	void update_score(SDL_Renderer *renderer);
	bool paddle_hit() const;
	void update();
	void render(SDL_Renderer *renderer) const;
};
