#include <iostream>
#include "Ball.h"

Ball::Ball(int x, int y, int w, int h)
	: m_ball({x, y, w, h}), m_x(x), m_y(y) {
	}

int Ball::get_x() const {
	return m_ball.x;
}

int Ball::get_y() const {
	return m_ball.y;
}

int Ball::get_w() const {
	return m_ball.w;
}

int Ball::get_h() const {
	return m_ball.h;
}

void Ball::reset() {
	m_ball.x = m_x;
	m_ball.y = m_y;
	m_dx = BALL_SPEED;
	m_dy = BALL_SPEED;
	m_acceleration = 0.0;
}

bool Ball::inLBoundsX(SDL_Rect *board) const {
	if (m_ball.x > board->x) {
		return true;
	}
	return false;
}

bool Ball::inUBoundsX(SDL_Rect *board) const {
	if ((m_ball.x + m_ball.w) < (board->x + board->w)) {
		return true;
	}
	return false;
}

bool Ball::inBoundsY(SDL_Rect *board) const {
	if (m_ball.y > board->y && (m_ball.y + m_ball.h) < (board->y + board->h)) {
		return true;
	}
	return false;
}

void Ball::hit(double bounce_angle) {
	m_acceleration += 0.1;
	m_dx = (BALL_SPEED + m_acceleration) * std::cos(bounce_angle);
	m_dy = (BALL_SPEED + m_acceleration) * -std::sin(bounce_angle);
}

void Ball::invert_x() {
	m_dx = -m_dx;
}

void Ball::invert_y() {
	m_dy = -m_dy;
}

void Ball::update(double dt) {
	m_ball.x += m_dx * dt;
	m_ball.y += m_dy * dt;
}

void Ball::render(SDL_Renderer *renderer) const {
	SDL_RenderFillRect(renderer, &m_ball);
}
