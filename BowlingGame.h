/*************************************************************************
BowlingGame.h
Created By Amit Nagpal
*************************************************************************/

#include <string>
#include <memory>

#include "IGame.h"
#include "IPlayer.h"

class BowlingGame : public IGame {
public:
	BowlingGame(const std::string& playerName);
	void inputRolls(const std::vector<int>& rolls) override;
	int calculateScore() const override;

private:
	bool isStrike(const int& frame_count, const std::vector<int>& rolls, size_t& roll_position) const;
	void checkExtra(const int& frame_count, const std::vector<int>& rolls, size_t& roll_position);

private:
	IPlayerPtr player_ = nullptr;
};

