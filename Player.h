#pragma once
#include <vector>
#include<string>

#include "IPlayer.h"
#include "IFrame.h"

class Player : public IPlayer{
public:

	Player(const std::string& playerName);

	int totalScore() const override;
	void clearFrames() override;
	void addFrame(const IFramePtr frame) override;
	IFramePtr getFrameAt(const size_t& index) override;
	std::vector<IFramePtr>& getFrames() override;


private:
	std::string player_name_;
	std::vector<IFramePtr> frames_;

};