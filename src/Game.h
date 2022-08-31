#pragma once
#include <SDL.h>
#include "Board.h"

class Game {
private:
	Board m_board;
	int m_w;
	int m_h;
public:
	Game(int w, int h);
	void init(SDL_Renderer *renderer);

	bool scored();
	void update_score(SDL_Renderer *renderer);
	void update(double dt);
	void render(SDL_Renderer *renderer) const;
};
