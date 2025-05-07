#include <memory>
#include <stdexcept>

#include "Player.h"
#include <iostream>

Player::Player(const std::string& playerName) : player_name_(playerName)
{
}

int Player::totalScore() const {
	int score = 0;
	for (size_t i = 0; i < 10; ++i) {
		const auto& f = frames_[i];
		score += f->getBaseScore();

		if (f->isStrike() && i + 1 < frames_.size()) {
			const auto& next = frames_[i + 1];
			score += next->firstRoll_;
			if (next->isStrike() && i + 2 < frames_.size()) {
				score += frames_[i + 2]->firstRoll_;
			}
			else {
				score += next->secondRoll_;
			}
		}
		else if (f->isSpare() && i + 1 < frames_.size()) {
			score += frames_[i + 1]->firstRoll_;
		}
	}
	return score;
}

void Player::clearFrames()
{
	frames_.clear();
}

void Player::addFrame(const IFramePtr frame)
{
	frames_.emplace_back(frame);
}

IFramePtr Player::getFrameAt(const size_t& index)
{
	if(frames_.size() < index)
		throw std::runtime_error("Invalid frame index.");

	return frames_[index];
}

std::vector<IFramePtr>& Player::getFrames()
{
	return frames_;
}
