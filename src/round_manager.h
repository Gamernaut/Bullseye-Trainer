///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	Manages each round, is responsible for starting and ending a round and testing for a win condition
//
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_ROUND_MANAGER_H_
#define CPV_ROUND_MANAGER_H_

// Include core code
#include <iostream>

// Include 3rd party code
#include <plog/Log.h>

// Include my code
#include "enemy_manager.h"
#include "awacs_manager.h"
#include "game_enums.h"
#include "constants.h"
#include "settings_manager.h"
#include "maths_functions.h"
#include "bullseye.h"
// #include "display_manager.h"			possible circular reference with display_manager.h

namespace cpv {

	// Only added to avoid circular reference above and so it will compile but doesn't work on line 189 of roundmanager.cpp
	class DisplayManager;

	class RoundManager {
	// Attributes
	private:

	protected:
		int total_guesses_ = 0;
		int current_guess_ = 0;
		int bogey_count_ = 0;

		std::unique_ptr<AWACSManager> awacs_manager_ = nullptr;  

	public:
		// Needs to be public so HSD.cpp can access it
		std::unique_ptr<EnemyManager> enemy_manager_ = nullptr;


	// Methods
	protected:
		void CheckRecruitWinStatus(GameState& state, Coordinate aircraft_position, int aircraft_heading, int bulls_bearing, Coordinate bullseye_position);
		void CheckCadetWinStatus(GameState& state, Coordinate bullseye_position);
		void CheckRookieWinStatus(GameState& state, int aircraft_heading, Coordinate bullseye_position);
		void CheckVeteranWinStatus(GameState& state, Coordinate bullseye_position, int bulls_bearing, int aircraft_heading, double milesperpixel);
		void CheckAceWinStatus(GameState& state);
		void IncreaseGuessCount();


	public:
		RoundManager();
		~RoundManager();
		void SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_, std::unique_ptr<DisplayManager>& display_manager_);
		//void SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_);

		void CheckGuessAgainstWinCondition(GameState& state, const std::unique_ptr<SettingsManager>& settings_manager, Coordinate bullseye_position, int bulls_bearing, Coordinate aircraft_position, int aircraft_heading, double milesperpixel);
		int GetRemainingGuesses() const;
		//void ResetRound();
		std::string GenerateAwacsCallString(int bogey_index);
	};

}

#endif // CPV_ROUND_MANAGER_H_
