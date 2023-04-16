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

// TODO: need to include info from HSD in the functions which check for the correct guess but includes and forward declaration not working.
// #include "display_manager.h"
// #include "hsd.h"
// class HSD;

namespace cpv {

	class RoundManager {
	// Attributes
	private:

	protected:
		int total_guesses_ = 0;
		int current_guess_ = 0;
		int bogey_count_ = 0;

		Coordinate mouse_click_pos_ = { 0,0 };

		std::unique_ptr<AWACSManager> awacs_manager_ = nullptr;  

	public:
		// Needs to be public so HSD.cpp can access it
		std::unique_ptr<EnemyManager> enemy_manager_ = nullptr;


	// Methods
	protected:
		void CheckRecruitWinStatus(GameState& state);
		//void CheckCadetWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_);
		//void CheckRookieWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_);
		//void CheckVeteranWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_);
		//void CheckAceWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_);
		bool IsClickInRectAroundBulls();
//		bool IsClickInRectAroundBogey(Aircraft* bogey1, Aircraft* bogey2);


	public:
		RoundManager();
		~RoundManager();
		void SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_);
		void CheckGuessAgainstWinCondition(GameState& state, Coordinate mouse_click_position, const std::unique_ptr<SettingsManager>& settings_manager);
		int GetRemainingGuesses() const;
		void ResetRound();
		std::string GenerateAwacsCallString(int bogey_index);
	};

}

#endif // CPV_ROUND_MANAGER_H_
