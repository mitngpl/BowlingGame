#pragma once
#include<vector>

class IGame {
public:
	virtual void inputRolls(const std::vector<int>& rolls) = 0;
	virtual int calculateScore() const = 0;

	virtual ~IGame() = default;
};
using IGamePtr = std::shared_ptr<IGame>;

