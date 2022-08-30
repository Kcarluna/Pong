#pragma once
#include <SDL.h>

class Ball {
private:
	SDL_Rect m_ball;
	int m_x;
	int m_y;

	int m_dx = 2;
	int m_dy = 2;
public:
	Ball() = default;
	Ball(int x, int y, int w, int h);
	int get_x() const;
	int get_y() const;
	int get_w() const;
	int get_h() const;

	void reset();
	bool inLBoundsX(SDL_Rect *board) const;
	bool inUBoundsX(SDL_Rect *board) const;
	bool inBoundsY(SDL_Rect *board) const;
	void invert_x();
	void invert_y();
	void update();
	void render(SDL_Renderer *renderer) const;
};
