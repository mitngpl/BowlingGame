
#include "Frame.h"


Frame::Frame() : isStrike_(false), isSpare_(false)
{
	firstRoll_ = 0;
	secondRoll_ = 0;
	thirdRoll_ = 0;
}

int Frame::getBaseScore() const
{
	return firstRoll_ + secondRoll_ + thirdRoll_;
}

void Frame::setStrike(const bool& strike) {
	isStrike_ = strike;
}

void Frame::setSpare(const bool& spare) {
	isSpare_ = spare;
}

bool Frame::isStrike() const
{
	return isStrike_;
}

bool Frame::isSpare() const
{
	return isSpare_;
}
