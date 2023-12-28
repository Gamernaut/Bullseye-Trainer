///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    Definition of Bulls_Trainer class. This class is the main part of the application,
//              it co-ordinates the rounds, manages graphical display and user input via SDl.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Windows.h>    // For sleep function

// Include 3rd party code


// Include my code
#include "constants.h"
#include "bulls_trainer.h"

using namespace cpv;

Bulls_Trainer::Bulls_Trainer() {

}

Bulls_Trainer::~Bulls_Trainer() {

}

// Sets up SDL2 and creates handles to the various graphical displays used in the app
bool Bulls_Trainer::Initialise()  {
	PLOG_INFO << "Bulls_Trainer::Initialise() called";

	round_manager_ = std::make_unique<RoundManager>();
	if (!round_manager_) {
		PLOG_ERROR << "Bulls_Trainer::Initialise() failed to create round_manager_ object";
		return false;
	}

	// Create the settings manager to handle tracking and saving the app settings to the registry 
	settings_manager_ = std::make_unique<SettingsManager>();
	if (!settings_manager_) {
		PLOG_ERROR << "Bulls_Trainer::Initialise() failed to create settings_manager_ object";
		return false;
	}

	// Create the display manager and Initialise the graphics 
	display_manager_ = std::make_unique<DisplayManager>();
	if (!display_manager_) {
		PLOG_ERROR << "Bulls_Trainer::Initialise() failed to create display_manager_ object";
		return false;
	}

	// Setup the SDL library and screens
	if (!display_manager_->InitialiseSDL()) {
		PLOG_ERROR << "Bulls_Trainer::Initialise(): display_manager_->InitialiseSDL() failed";
		return false;
	}

	if (!display_manager_->CreateScreens()) {
		PLOG_ERROR << "Bulls_Trainer::Initialise(): display_manager_->CreateScreens() failed";
		return false;
	}


	// Set Random seed for creating distances and bearings for the enemy aircraft
	std::srand((unsigned int)std::time(NULL));

	// Set game flags/states to start conditions
	is_game_running_ = true;
	game_state = GameState::kStartScreen;
    
	return true;
}


void Bulls_Trainer::Run() {
	PLOG_INFO << "Bulls_Trainer::run() called";

	// This needs calling as soon as the player reaches the main screen or returns to the main screen after going to the options screen.
	// This will reset the round but that's fine as changes in difficulty level will affect the round so the round has to be set up once
	// the difficulty level is known

	//round_manager_->ResetRound();		// do we need to set the gamestate at this point or is it already set properly

	while (game_state != GameState::kGameEnded) {
		// Limit speed to consistent frame rate. Not really needed in this application, but good practice to include it anyway.
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), milliseconds_previous_frame_ + kmilliseconds_per_frame));

		// Store the current frame time
		milliseconds_previous_frame_ = SDL_GetTicks();

		ProcessInput();
		Render();
	}
	// Sleep(2000);
	if (game_state == GameState::kGameEnded && is_game_running_) {
		round_manager_->ResetRound();
		round_manager_->SetupRound(settings_manager_, display_manager_);
		// This is a work around to not being able to call this method from RoundManager watch ouit for problems with this set up
		display_manager_->hsd_screen_->RandomiseAircrafAndBullseye();
		//round_manager_->SetupRound(settings_manager_);
		game_state = GameState::kNewRound;
	}
	settings_manager_->WriteSettingsToRegistry();
}


void Bulls_Trainer::ProcessInput() {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			game_state = GameState::kGameEnded;
			is_game_running_ = false;
			PLOG_INFO << "Bulls_Trainer::ProcessInput() Close widget clicked -> game state set to kGameEnded";
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				game_state = GameState::kGameEnded;
				is_game_running_ = false;
				PLOG_INFO << "Bulls_Trainer::ProcessInput() ESC key pressed -> game state set to kGameEnded";
				break;
			}

		case SDL_MOUSEBUTTONUP:
			//Get mouse position on button release
			SDL_GetMouseState(&mouseX, &mouseY);

			// Handle clicks whilst on the start screen. Can only transition to the Main screen from here through OSB 13
			if (game_state == GameState::kStartScreen) {
				if (mouseX >= kOSB13LeftEdge && mouseX <= kOSB13RightEdge && mouseY >= kOSB13TopEdge && mouseY <= kOSB13BottomEdge) {
					game_state = GameState::kNewRound;
					// Start a new round as this is the first time the game has been played
					round_manager_->SetupRound(settings_manager_, display_manager_);
					// This is a work around to not being able to call this method from RoundManager watch ouit for problems with this set up
					display_manager_->hsd_screen_->RandomiseAircrafAndBullseye();
					PLOG_INFO << "Start screen -> Start button clicked";
					break;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////
			// 
			// Handle clicks when a new round has just begun. User can enter Options Screen from this state only
			// 
			// //////////////////////////////////////////////////////////////////////////////////////////////////
			
			// Once they make their first guess they cannot change their settings
			if (game_state == GameState::kNewRound) {
				// Handle Setup button press (should not be active when round is being played)
				if (mouseX >= kOSB14LeftEdge && mouseX <= kOSB14RightEdge && mouseY >= kOSB14TopEdge && mouseY <= kOSB14BottomEdge) {
					tempDiff = settings_manager_->GetGameDifficulty();	// Store the setting the user had when they enter the setup screen so if they cancel it can be restored
					temp_game_state = game_state;	// Store the game state so we can restore when we come out of the setup screen if they cancel
					tempLog = settings_manager_->GetLoggingLevel();
					game_state = GameState::kOptionsScreen;
					PLOG_INFO << "Main screen -> Setup button clicked, saving game difficulty and game state";
					break;
				}
				// Exit if OSB 12
				else if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					game_state = GameState::kGameEnded;
					is_game_running_ = false;
					PLOG_INFO << "Main screen -> Exit button clicked";
					break;
				}
			} // End of if (game_state == GameState::kNewRound)


			////////////////////////////////////////////////////////////////////////////////////////
			// 
			// Handle clicks in the options screen, can set the difficulty and logging level here
			// 
			////////////////////////////////////////////////////////////////////////////////////////

			if (game_state == GameState::kOptionsScreen) {

				// Set logging level to High
				if (mouseX >= kOSB7LeftEdge && mouseX <= kOSB7RightEdge && mouseY >= kOSB7TopEdge && mouseY <= kOSB7BottomEdge) {
					settings_manager_->SetLoggingLevel(1);
					plog::get()->setMaxSeverity(plog::verbose);
					PLOG_INFO << "Logging level changed to High";
					break;
				}

				// Set logging level to Medium
				if (mouseX >= kOSB8LeftEdge && mouseX <= kOSB8RightEdge && mouseY >= kOSB8TopEdge && mouseY <= kOSB8BottomEdge) {
					settings_manager_->SetLoggingLevel(2);
					plog::get()->setMaxSeverity(plog::info);
					PLOG_INFO << "Logging level changed to Medium";
					break;
				}

				// Set logging level to Low
				if (mouseX >= kOSB9LeftEdge && mouseX <= kOSB9RightEdge && mouseY >= kOSB9TopEdge && mouseY <= kOSB9BottomEdge) {
					settings_manager_->SetLoggingLevel(3);
					plog::get()->setMaxSeverity(plog::warning);
					PLOG_INFO << "Logging level changed to Low";
					break;
				}

				// Handle the Cancel button and restore previous difficulty and logging level as this was updated in real time to match the users clicks in the options screen
				if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					// Restore the difficulty level to the one before the user entered the setup screen
					settings_manager_->SetGameDifficulty(tempDiff);
					settings_manager_->SetLoggingLevel(tempLog);
					// Reset the game mode to NewRound from OptionsScreen
					game_state = GameState::kNewRound;
					PLOG_INFO << "Options screen Cancel button pressed -> restoring previous game state";
					break;
				}

				// Handle the select button (set the selected options as the current states)
				if (mouseX >= kOSB14LeftEdge && mouseX <= kOSB14RightEdge && mouseY >= kOSB14TopEdge && mouseY <= kOSB14BottomEdge) {
					settings_manager_->WriteSettingsToRegistry();
					// Reset the game mode to NewRound from OptionsScreen
					game_state = GameState::kNewRound;

					// User may have changed the difficulty level so need to create anew round based on this
					round_manager_->ResetRound();
					round_manager_->SetupRound(settings_manager_, display_manager_);
					// This is a work around to not being able to call this method from RoundManager watch ouit for problems with this set up
					display_manager_->hsd_screen_->RandomiseAircrafAndBullseye();

					PLOG_INFO << "Options screen Select button pressed -> Reset game state to NewRound";
					break;
				}

				// Set Recruit difficulty selection in options screen
				if (mouseX >= kOSB20LeftEdge && mouseX <= kOSB20RightEdge && mouseY >= kOSB20TopEdge && mouseY <= kOSB20BottomEdge) {
					settings_manager_->SetGameDifficulty(Difficulty::kRecruit);
					PLOG_INFO << "Difficulty changed to Recruit";
					break;
				}

				// Set Cadet difficulty selection in options screen
				if (mouseX >= kOSB19LeftEdge && mouseX <= kOSB19RightEdge && mouseY >= kOSB19TopEdge && mouseY <= kOSB19BottomEdge) {
					settings_manager_->SetGameDifficulty(Difficulty::kCadet);
					PLOG_INFO << "Difficulty changed to Cadet";
					break;
				}

				// Set Rookie difficulty selection in options screen
				if (mouseX >= kOSB18LeftEdge && mouseX <= kOSB18RightEdge && mouseY >= kOSB18TopEdge && mouseY <= kOSB18BottomEdge) {
					settings_manager_->SetGameDifficulty(Difficulty::kRookie);
					PLOG_INFO << "Difficulty changed to Rookie";
					break;
				}

				// Set Veteran difficulty selection in options screen
				if (mouseX >= kOSB17LeftEdge && mouseX <= kOSB17RightEdge && mouseY >= kOSB17TopEdge && mouseY <= kOSB17BottomEdge) {
					settings_manager_->SetGameDifficulty(Difficulty::kVeteran);
					PLOG_INFO << "Difficulty changed to Veteran";
					break;
				}

				// Set Ace difficulty selection in options screen
				if (mouseX >= kOSB16LeftEdge && mouseX <= kOSB16RightEdge && mouseY >= kOSB16TopEdge && mouseY <= kOSB16BottomEdge) {
					settings_manager_->SetGameDifficulty(Difficulty::kAce);
					PLOG_INFO << "Difficulty changed to Ace";
					break;
				}
			} // end of if (game_state == GameState::kOptionsScreen)

			////////////////////////////////////////////////////////////////////////////////////////
			// 
			// Handle clicks when game screen is running
			// 
			////////////////////////////////////////////////////////////////////////////////////////

			if (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound) {

				// Handle a click that's inside the MFD surround (not a button press but a guess by the user)
				if (mouseX >= kLeftMfdFrameSize && mouseX <= (kLeftMfdFrameSize + kMfdDrawAreaWidth) &&
					mouseY >= (kTextPanelHeight + kTopMfdFrameSize) && mouseY <= (kTextPanelHeight + kTopMfdFrameSize + kMfdDrawAreaHeight)) {
					g_mouse_click_pos.x = mouseX;
					g_mouse_click_pos.y = mouseY;
					PLOG_INFO << "HSD guess made -> Calling CheckGuessAgainstWinCondition()";
					game_state = GameState::kRoundPlaying;
					Coordinate bulls_position = display_manager_->hsd_screen_->bullseye_->GetPosition();
					Coordinate aircraft_position = display_manager_->hsd_screen_->my_aircraft_->GetPosition();
					int bulls_bearing = display_manager_->hsd_screen_->bullseye_->GetBearingFromBullseyeToMyAircraft();
					int aircraft_heading = display_manager_->hsd_screen_->my_aircraft_->GetHeading();
					double milesperpixel = display_manager_->hsd_screen_->GetMilesPerPixel();
					display_manager_->hsd_screen_->SetMouseClickPosition(mouseX, mouseY);
					round_manager_->CheckGuessAgainstWinCondition(game_state, settings_manager_, bulls_position, bulls_bearing, aircraft_position, aircraft_heading, milesperpixel);
					break;
				}

				// Handle DEP button press, toggle between centered and not centered
				if (mouseX >= kOSB1LeftEdge && mouseX <= kOSB1RightEdge && mouseY >= kOSB1TopEdge && mouseY <= kOSB1BottomEdge) {
					if (!display_manager_->hsd_screen_->GetCenteredState()) {
						display_manager_->hsd_screen_->SetCenteredState(true);
						PLOG_INFO << "HSD DEP button press -> HSD state changed to centered";
						break;
					}
					else {
						display_manager_->hsd_screen_->SetCenteredState(false);
						PLOG_INFO << "HSD DEP button press -> HSD centered state set to false";
					}
				}

				// Handle Increase Range button press
				if (mouseX >= kOSB20LeftEdge && mouseX <= kOSB20RightEdge && mouseY >= kOSB20TopEdge && mouseY <= kOSB20BottomEdge) {
					display_manager_->hsd_screen_->IncreaseRange();
					PLOG_INFO << "HSD increase range button pressed";
					break;
				}

				// Handle Decrease Range button press
				if (mouseX >= kOSB19LeftEdge && mouseX <= kOSB19RightEdge && mouseY >= kOSB19TopEdge && mouseY <= kOSB19BottomEdge) {
					display_manager_->hsd_screen_->DecreaseRange();
					PLOG_INFO << "HSD decrease range button pressed";
					break;
				}

				// Handle Exit button press
				else if (mouseX >= kOSB12LeftEdge && mouseX <= kOSB12RightEdge && mouseY >= kOSB12TopEdge && mouseY <= kOSB12BottomEdge) {
					game_state = GameState::kGameEnded;
					is_game_running_ = false;
					PLOG_INFO << "HSD Exit button pressed -> game state set to kGameEnded";
					break;
				}
			}	// end of game state == kRoundPlaying if loop

		}	// end of switch
	}	// end of while loop
}	// end of method


// Depending on the current game state render the appropriate screen.
void Bulls_Trainer::Render() {

	switch (game_state) {
		case GameState::kStartScreen:
			display_manager_->RenderStartScreen();
			break;
		case GameState::kOptionsScreen:
			display_manager_->RenderOptionsSceen(settings_manager_);
			break;
		// All other Game_states are only relevant to the game screen so they are handled there
		default:
			display_manager_->RenderGameScreen(game_state, round_manager_, settings_manager_);
			break;
	}

}



void Bulls_Trainer::CloseDown() {
	// TODO is this needed??
}