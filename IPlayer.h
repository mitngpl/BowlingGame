#pragma once
#include "IFrame.h"

class IPlayer {
public:
	virtual int totalScore() const = 0;
	virtual void clearFrames() = 0;

	virtual void addFrame(const IFramePtr frame) = 0;
	virtual IFramePtr getFrameAt(const size_t& index) = 0;
	virtual std::vector<IFramePtr>& getFrames() = 0;

	virtual ~IPlayer() = default;
};
using IPlayerPtr = std::shared_ptr<IPlayer>;