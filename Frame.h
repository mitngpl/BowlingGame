#pragma once
#include "IFrame.h"

class Frame : public IFrame {
public:
	Frame();
	int getBaseScore() const override;
	bool isStrike() const override;
	bool isSpare() const override;
	void setStrike(const bool& strike) override;
	void setSpare(const bool& spare) override;

private:
	bool isStrike_;
	bool isSpare_;
};