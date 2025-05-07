
/*************************************************************************
BowlingGame.cpp
Created By Amit Nagpal
*************************************************************************/

#include"Player.h"
#include"Frame.h"
#include"BowlingGame.h"
#include <stdexcept>
constexpr uint16_t MAX_FRAME = 10;


BowlingGame::BowlingGame(const std::string& playerName): player_(std::make_shared<Player>(playerName))
{
}

void BowlingGame::inputRolls(const std::vector<int>& rolls) {
	//Clear the frames we are staring new game
	player_->clearFrames();

	size_t roll_position = 0;
	auto frame_count = 0;

	while (frame_count < MAX_FRAME && roll_position < rolls.size()) {

		auto frame_ptr = std::make_shared<Frame>();
		frame_ptr->firstRoll_ = rolls[roll_position];

		if (isStrike(frame_count, rolls, roll_position)) { // Check for Strike
			frame_ptr->setStrike(true);
			frame_ptr->secondRoll_ = 0;
			player_->addFrame(frame_ptr);
			++roll_position;
		}
		else {
			if (roll_position + 1 >= rolls.size())
			{
				throw std::runtime_error("Incomplete frame input.");
			}

			frame_ptr->secondRoll_ = rolls[roll_position + 1];

			if (frame_ptr->firstRoll_ + frame_ptr->secondRoll_ > MAX_FRAME && frame_count < MAX_FRAME)
			{
				throw std::runtime_error("Invalid pin count in a frame.");
			}
			auto is_spare = MAX_FRAME == frame_ptr->firstRoll_ + frame_ptr->secondRoll_;
			frame_ptr->setSpare(is_spare);
			roll_position += 2;
			player_->addFrame(frame_ptr);
		}
		++frame_count;
	}

	// 10th frame logic
	checkExtra(frame_count, rolls, roll_position);

	// Append extra frames for lookahead (up to 2)
	while (roll_position < rolls.size()) {
		auto frame_ptr = std::make_shared<Frame>();

		frame_ptr->firstRoll_ = rolls[roll_position++];
		frame_ptr->secondRoll_ = (roll_position < rolls.size()) ? rolls[roll_position++] : 0;
		player_->addFrame(frame_ptr);
	}

	if (player_->getFrames().size() < MAX_FRAME) {
		throw std::runtime_error("Less than 10 frames provided.");
	}
}

int BowlingGame::calculateScore() const {
	return player_->totalScore();
}

bool BowlingGame::isStrike(const int& frame_count, const std::vector<int>& rolls, size_t& roll_position) const
{
	if (rolls.size() < roll_position)
		throw std::runtime_error("Invalid roll position.");

	return rolls[roll_position] == MAX_FRAME && frame_count < MAX_FRAME;
}

void BowlingGame::checkExtra(const int& frame_count, const std::vector<int>& rolls, size_t& roll_position)
{
	if (frame_count == MAX_FRAME) {
		auto last = player_->getFrameAt(MAX_FRAME - 1);
		if (last->isStrike() || last->isSpare()) {
			if (roll_position >= rolls.size()) 
			{ 
				throw std::runtime_error("Missing bonus roll for 10th frame.");
			}
			last->thirdRoll_ = rolls[roll_position++];
		}
	}
}

