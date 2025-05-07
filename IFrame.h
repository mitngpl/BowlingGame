#pragma once

#include <memory>
class IFrame {
public:
	virtual int getBaseScore() const = 0;
	virtual void setStrike(const bool& strike) = 0;
	virtual void setSpare(const bool& spare) = 0;
	virtual bool isStrike() const = 0;
	virtual bool isSpare() const = 0;

	virtual ~IFrame() = default;

public:
	int firstRoll_;
	int secondRoll_;
	//Only for 10th Roll
	int thirdRoll_;
};
using IFramePtr = std::shared_ptr<IFrame>;