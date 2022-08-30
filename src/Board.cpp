#include <iostream>
#include "Board.h"

TTF_Font *init_font() {
	TTF_Font *font = TTF_OpenFont("../fonts/Roboto-Regular.ttf", FONT_SIZE);
	if (!font) {
		std::cerr << "ERROR: " << TTF_GetError() << std::endl;
		exit(1);
	}
	return font;
}

void Board::query_text() {
	int w;
	int h;
	SDL_QueryTexture(m_player_one_score_t, NULL, NULL, &w, &h);
	m_player_one_score_board = {m_board.x + 5, 5, w, h};
	SDL_QueryTexture(m_player_two_score_t, NULL, NULL, &w, &h);
	m_player_two_score_board = {((m_board.x + m_board.w) - 5) - w, 5, w, h};
}

void Board::init_score_board(SDL_Renderer *renderer) {
	SDL_Color color = {255, 255, 255};
	m_surface = TTF_RenderText_Solid(m_font, std::to_string(m_player_one_score).c_str(), color);
	m_player_one_score_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, std::to_string(m_player_two_score).c_str(), color);
	m_player_two_score_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
	query_text();
}

Board::Board(int x, int y, int w, int h)
	// NOTE(__LUNA__): Open font causing memory leak...
	: m_board({x, y, w, h}), m_font(init_font()) {
		m_left_paddle = Paddle(m_board.x + PADDLE_PADDING, (m_board.h / 2) - (PADDLE_HEIGHT / 2), PADDLE_WIDTH, PADDLE_HEIGHT);
		m_right_paddle = Paddle((m_board.x + m_board.w) - (PADDLE_PADDING + PADDLE_WIDTH), (m_board.h / 2) - (PADDLE_HEIGHT / 2), PADDLE_WIDTH, PADDLE_HEIGHT);
		m_ball = Ball((m_board.w / 2) - (BALL_WIDTH / 2), (m_board.h / 2) - (BALL_HEIGHT / 2), BALL_WIDTH, BALL_HEIGHT);
	}

Board::~Board() {
	if (m_player_one_score_t) SDL_DestroyTexture(m_player_one_score_t);
	if (m_player_two_score_t) SDL_DestroyTexture(m_player_two_score_t);
}

bool Board::scored() {
	if (!m_ball.inLBoundsX(&m_board)) {
		m_player_two_score++;
		m_ball.reset();
		m_left_paddle.reset();
		m_right_paddle.reset();
		m_ball.invert_x();
		return true;
	}
	if (!m_ball.inUBoundsX(&m_board)) {
		m_player_one_score++;
		m_ball.reset();
		m_left_paddle.reset();
		m_right_paddle.reset();
		m_ball.invert_x();
		return true;
	}
	return false;
}

void Board::update_score(SDL_Renderer *renderer) {
	SDL_Color color = {255, 255, 255};
	m_surface = TTF_RenderText_Solid(m_font, std::to_string(m_player_one_score).c_str(), color);
	if (m_player_one_score_t) SDL_DestroyTexture(m_player_one_score_t);
	m_player_one_score_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);

	m_surface = TTF_RenderText_Solid(m_font, std::to_string(m_player_two_score).c_str(), color);
	if (m_player_two_score_t) SDL_DestroyTexture(m_player_two_score_t);
	m_player_two_score_t = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_FreeSurface(m_surface);
}

bool Board::paddle_hit() const {
	if ((m_ball.get_x() < (m_left_paddle.get_x() + m_left_paddle.get_w()) && ((m_ball.get_y() + m_ball.get_h()) > m_left_paddle.get_y() && m_ball.get_y() < (m_left_paddle.get_y() + m_left_paddle.get_h()))) ||
		((m_ball.get_x() + m_ball.get_w()) > m_right_paddle.get_x() && ((m_ball.get_y() + m_ball.get_h()) > m_right_paddle.get_y() && m_ball.get_y() < (m_right_paddle.get_y() + m_right_paddle.get_h())))) {
		return true;
	}
	return false;
}

void Board::update() {
	m_ball.update();
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W] && m_left_paddle.inLBounds(&m_board)) {
		m_left_paddle.move(UP);
	} else if (state[SDL_SCANCODE_S] && m_left_paddle.inUBounds(&m_board)) {
		m_left_paddle.move(DOWN);
	} else {
		m_left_paddle.move(STOP);
	}
	if (state[SDL_SCANCODE_UP] && m_right_paddle.inLBounds(&m_board)) {
		m_right_paddle.move(UP);
	} else if (state[SDL_SCANCODE_DOWN] && m_right_paddle.inUBounds(&m_board)) {
		m_right_paddle.move(DOWN);
	} else {
		m_right_paddle.move(STOP);
	}
	if (paddle_hit()) {
		m_ball.invert_x();
	}

	if (!m_ball.inBoundsY(&m_board)) {
		m_ball.invert_y();
	}
}

void Board::render(SDL_Renderer *renderer) const {
	SDL_SetRenderDrawColor(renderer, 150, 150, 150, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &m_board);
	SDL_RenderCopy(renderer, m_player_one_score_t, NULL, &m_player_one_score_board);
	SDL_RenderCopy(renderer, m_player_two_score_t, NULL, &m_player_two_score_board);
	SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, m_board.w / 2, 0, m_board.w / 2, m_board.h);
	m_left_paddle.render(renderer);
	m_right_paddle.render(renderer);
	m_ball.render(renderer);

	SDL_RenderPresent(renderer);
}
