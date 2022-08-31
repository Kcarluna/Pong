#include <iostream>
#include "Game.h"

Game::Game(int w, int h)
	: m_w(w), m_h(h) {
		// NOTE(__LUNA__): Switch this to w and h... only using member vars to silence warning
		m_board = Board(0, 0, m_w, m_h);
	}

void Game::init(SDL_Renderer *renderer) {
	m_board.init_score_board(renderer);
}

bool Game::scored() {
	if (m_board.scored()) {
		return true;
	}
	return false;
}

void Game::update_score(SDL_Renderer *renderer) {
	m_board.update_score(renderer);
}

void Game::update(double dt) {
	m_board.update(dt);
}

void Game::render(SDL_Renderer *renderer) const {
	m_board.render(renderer);
}
