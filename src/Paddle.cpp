#include <iostream>
#include "Paddle.h"

Paddle::Paddle(int x, int y, int w, int h)
	: m_paddle({x, y, w, h}), m_x(x), m_y(y) {
	}

int Paddle::get_x() const {
	return m_paddle.x;
}

int Paddle::get_y() const {
	return m_paddle.y;
}

int Paddle::get_w() const {
	return m_paddle.w;
}

int Paddle::get_h() const {
	return m_paddle.h;
}


bool Paddle::inLBounds(SDL_Rect *rect) const {
	if (m_paddle.y > rect->y) {
		return true;
	}
	return false;
}

bool Paddle::inUBounds(SDL_Rect *rect) const {
	if ((m_paddle.y + m_paddle.h) < (rect->y + rect->h)) {
		return true;
	}
	return false;
}

void Paddle::reset() {
	m_paddle.x = m_x;
	m_paddle.y = m_y;
}

void Paddle::move(int dir) {
	m_vy = dir;
}

void Paddle::update(double dt) {
	m_paddle.y += m_vy * (PADDLE_SPEED * dt);
}

void Paddle::render(SDL_Renderer *renderer) const {
	SDL_RenderFillRect(renderer, &m_paddle);
}
