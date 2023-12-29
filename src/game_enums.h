///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    Stores more of the config and types for the program
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
//////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_GAME_ENUMS_H
#define CPV_GAME_ENUMS_H

namespace cpv {

	enum class GameState {
		// The starting state and shows the start screen
		kStartScreen,
		// Shows the options screen
		kOptionsScreen,
		// This is after the user moves from the start or options screen to the "Game" screen but before the first guess.
		kNewRound,
		// User has clicked on the MFD and made a guess but after kNewRound state but has not used all their guesses yet. 
		// Round is still playing so hidden bogies are not displayed.
		kRoundPlaying,
		// User guessed correctly, either before or at the total number of allowable guesses.
		// Round is over so can display the hidden bogies on the HSD.
		kRoundWon,
		// User failed to guess the correct location after the predefined number of attempts.
		// Round is over so can display the hidden bogies on the HSD.
		kRoundEnded,
		// Used to signal that the user wants to quit the game
		kGameEnded
	};

	enum class Difficulty {
		kRecruit,
		kCadet,
		kRookie,
		kVeteran,
		kAce
	};
}

#endif  // CPV_GAME_ENUMS_H
