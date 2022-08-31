#pragma once
#include <SDL.h>

#define PADDLE_SPEED 2

class Paddle {
private:
	SDL_Rect m_paddle;
	int m_x;
	int m_y;
	int m_vy;
public:
	Paddle() = default;
	Paddle(int x, int y, int w, int h);
	int get_x() const;
	int get_y() const;
	int get_w() const;
	int get_h() const;

	bool inLBounds(SDL_Rect *rect) const;
	bool inUBounds(SDL_Rect *rect) const;
	void reset();
	void move(int dir);
	void update(double dt);
	void render(SDL_Renderer *renderer) const;
};
