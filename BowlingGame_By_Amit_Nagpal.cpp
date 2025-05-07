// BowlingGame_By_Amit_Nagpal.cpp : 
// This file contains the 'main' function, Factory and Testcases
//  Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cassert>

#include "GameCommon.h"
#include "IGame.h"
#include "BowlingGame.h"

class GameFactory {
public:
	static IGamePtr GetInstance(const std::string& player_name, const GameType& game_type) {
		switch (game_type)
		{
		case GameType::BOWLING:
			return std::make_shared<BowlingGame>(player_name);
		default:
			throw std::runtime_error("Invalid Game Type.");
		}
	}
};


int main()
{
	auto runBowlingGameTest = [](const std::string& player_name, const std::vector<int>& vec, const int& expected_score) {

		try {
			const auto bowling_game = GameFactory::GetInstance(player_name, GameType::BOWLING);
			bowling_game->inputRolls(vec);
			const auto actual_score = bowling_game->calculateScore();
			assert(expected_score == actual_score);
			std::cout << player_name << " Test passed. count : " << actual_score << "\n\n";
		}
		catch (const std::exception& ex) {
			std::cerr << "Exception caught for " << player_name << ": " << ex.what() << "\n\n";
		}

	};

	std::cout << "Rolls:     1 4 | 4 5 | 6 4 | 5 5 | 10 | 0 1 | 7 3 | 6 4 | 10 | 2 6\n";
	std::cout << "Score:     5 +    9 +   15 +  20 + 11 +  1 +  16  +  20 + 18 +  8 = 123\n";
	runBowlingGameTest("Test Player", { 1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 6 }, 123);

	std::cout << "Rolls:     10 | 10 | 10 | 10 | 10 | 10 | 10 | 10 | 10 | 10 10 10\n";
	std::cout << "Score:     30 + 30 + 30 + 30 + 30 + 30 + 30 + 30 + 30 + 30 = 300\n";
	runBowlingGameTest("Perfect Player", { 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 }, 300);

	std::cout << "Rolls:     5 5 | 5 5 | 5 5 | 5 5 | 5 5 | 5 5 | 5 5 | 5 5 | 5 5 | 5 5 5\n";
	std::cout << "Score:     15 x 10 frames = 150\n";
	runBowlingGameTest("AllSpares Player", { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 }, 150);

	std::cout << " Rolls:     9 0 | 8 1 | 7 2 | 6 3 | 5 4 | 4 5 | 3 6 | 2 7 | 1 8 | 0 9\n";
	std::cout << " Score:     9 +    9 +   9  +  9  +  9  +  9  +  9  +  9  +  9  +  9 = 90\n";
	runBowlingGameTest("OpenFrames Player", { 9, 0, 8, 1, 7, 2, 6, 3, 5, 4, 4, 5, 3, 6, 2, 7, 1, 8, 0, 9 }, 90);

	std::cout << "Rolls:     1 4 | 4 5 | 6 4 | 5 5 | 10 | 0 1 | 7 3 | 6 4 | 10 | 2 8 (EXTRA) 6\n";
	std::cout << "Score:     5   +  9 +  15 +   20 + 11 +  1  +  16 +  20 + 20 +  16 = 133\n";
	runBowlingGameTest("10th Frame Spare Player", { 1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 8, 6 }, 133);

	std::cout << "Rolls:     1 4 | 4 5 | 6 4 | 5 5 | 10 | 0 1 | 7 3 | 6 4 | 10 | 10 10 (EXTRA) 10\n";
	std::cout << "Score:     5   +  9 +  15 +   20 + 11 +  1  +  16 +  20 + 30 +  30 = 157\n";
	runBowlingGameTest("9th and 10th Frame Strike Player", { 1, 4, 4, 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 10, 10, 10 }, 157);

	std::cout << "Rolls:     5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 6\n";
	runBowlingGameTest("Invalid pin count", { 5, 6, 4, 5, 5, 10, 0, 1, 7, 3, 6, 4, 10, 2, 6 }, 123);


	return 0;
}