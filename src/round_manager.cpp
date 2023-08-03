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

#include "round_manager.h"

using namespace cpv;

RoundManager::RoundManager() {
    PLOG_VERBOSE << "RoundManager constructor called";

    enemy_manager_ = std::make_unique<EnemyManager>();
    if (!enemy_manager_) {
        PLOG_ERROR << "RoundManager constructor failed to create enemy_manager_ object";
    }

    awacs_manager_ = std::make_unique<AWACSManager>();
    if (!awacs_manager_) {
        PLOG_ERROR << "RoundManager constructor failed to create enemy_manager_ object";
    }

}

RoundManager::~RoundManager()
{
    PLOG_VERBOSE << "RoundManager destructor called";
#
    // TODO: Implement ~RoundManager
}

void RoundManager::CheckRecruitWinStatus(GameState& state, Coordinate aircraft_position, int bulls_bearing) {
    // Win condition is to correctly identify the bearing of the bullseye from the aircraft (within a cone 30 deg wide, +/- 15 deg of the point clicked on)

    PLOG_VERBOSE << "RoundManager::CheckRecruitWinStatus() called";

    // Calculate the user guessed bearing (the order is important)
    int user_bearing_guess = angle_between_point_a_and_b(aircraft_position, mouse_click_pos_);

    // This needs to handle 360/0 as well
    if ((user_bearing_guess >= (bulls_bearing - 15) || user_bearing_guess >= (360 - 15)) && (user_bearing_guess <= (bulls_bearing + 15) || user_bearing_guess >= (0 + 15)) ) {
        // Player has picked a direction that is within +/- 15 deg of the actual direction
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct direction but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Recruit to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundFail;
        // Display "Better luck next time Recruit" 
    }
}


void RoundManager::CheckCadetWinStatus(GameState& state, Coordinate bullseye_position) {
    // Win condition is to correctly identify the position of the bullseye within the size of the bulls eye (30 x 30 pixels)

    PLOG_VERBOSE << "RoundManager::CheckCadetWinStatus() called";

    int x_difference = bullseye_position.x - mouse_click_position.x;
    int y_difference = bullseye_position.y - mouse_click_position.y;

    if (x_difference <= 15 && x_difference >= -15 && y_difference <= 15 && y_difference >= -15) {
        // Player has picked the location of the bulls eye so set game state to display the green box over the bullseye
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct location but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Cadet to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundFail;
        // Display "Better luck next time Cadet" 
    }
}
 

void RoundManager::CheckRookieWinStatus(GameState& state, Coordinate bullseye_position) {
    // Win condition is to correctly identify the bearing from the bullseye to the bogey within +/- 15 deg of actual.

    PLOG_VERBOSE << "RoundManager::CheckRookieWinStatus() called";

    // Get the bearing from bulls to the bogey (will only be 1 bogey at this difficulty level)
    int bulls_heading_to_bogey = enemy_manager_->GetBogieAtVectorPosition(0).GetBearing();
    int user_bearing_guess = angle_between_point_a_and_b(bullseye_position, mouse_click_pos_);

    if (user_bearing_guess >= (bulls_heading_to_bogey - 15) && user_bearing_guess <= (bulls_heading_to_bogey + 15)) {
        // Player has picked a direction that is within +/- 15 deg of the actual direction
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct direction but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Rookie to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundFail;
        // Display "Better luck next time Rookie" 
    }
}


void RoundManager::CheckVeteranWinStatus(GameState& state, Coordinate bullseye_position, int bulls_bearing, int aircraft_heading, double milesperpixel) {
    // Win condition is to correctly identify the position of the bogey within 30 x 30 pixels of the center of the bogey

    PLOG_VERBOSE << "RoundManager::CheckVeteranWinStatus() called";

    double  bogey_range = static_cast<double>(enemy_manager_->GetBogieAtVectorPosition(0).GetRange());
    Coordinate bogey_position = calc_endpoint_given_start_bearing_and_range(bullseye_position, bulls_bearing, aircraft_heading, bogey_range, milesperpixel);

    int x_difference = bogey_position.x - mouse_click_position.x;
    int y_difference = bogey_position.y - mouse_click_position.y;

    if (x_difference <= 15 && x_difference >= -15 && y_difference <= 15 && y_difference >= -15) {
        // Player has picked the location of the bulls eye so set game state to display the green box over the bullseye
        state = GameState::kRoundWon;
    }
    else if (current_guess_ < total_guesses_) {
        // player didn't pick correct location but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Veteran to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundFail;
        // Display "Better luck next time Veteran" 
    }
}


void RoundManager::CheckAceWinStatus(GameState& state) {
    PLOG_VERBOSE << "RoundManager::CheckAceWinStatus() called";

    // TODO: Implement CheckAceWinStatus with multi win conditions
}


void RoundManager::SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_) {
    PLOG_VERBOSE << "RoundManager::SetupRound() called";

    // TODO: Should this be in round_manager or bulls_trainer?
    settings_manager_->ReadSettingsFromRegistry();

    // Clear any previous bogies as this should only get called when anew round starts
    if (enemy_manager_->GetBogieCount() > 0) {
        enemy_manager_->DeleteBogies();
    }

    // Enemies not needed for lowest difficulty as they are about finding the bullseye 
    // but still need to set the number of guesses so do that up front

    total_guesses_ = 3;
    bogey_count_ = 1;

    // Highest difficulty - so randomly pick either 2 or 3 enemies and each enemy is 3 guesses.
    if (settings_manager_->GetGameDifficulty() == Difficulty::kAce) {
        bogey_count_ = std::rand() % 2 + 2;
        enemy_manager_->CreateBogey(bogey_count_);
        total_guesses_ = 3 * bogey_count_;
    }
    // Medium difficulty - just need to create 1 bogey and the guesses is already set as 3
    else {
        enemy_manager_->CreateBogey(bogey_count_);
    }

    // TODO: Set the F16 heading and the bulls position here
    // Might need to pass the HSD reference to this object so we can set the values from here
}

void RoundManager::CheckGuessAgainstWinCondition(GameState& state, Coordinate mouse_click_position, const std::unique_ptr<SettingsManager>& settings_manager, Coordinate bullseye_position, int bulls_bearing, Coordinate aircraft_position, int aircraft_heading, double milesperpixel) {
    
    PLOG_VERBOSE << "RoundManager::CheckGuessAgainstWinCondition() called";

    mouse_click_pos_ = mouse_click_position;
    IncreaseGuessCount();

    if (GetRemainingGuesses() > 0) {
        // Check the win condition for this round based on level of difficulty
        switch (settings_manager->GetGameDifficulty()) {
            case Difficulty::kRecruit:
                CheckRecruitWinStatus(state, aircraft_position, bulls_bearing);
                break;
            case Difficulty::kCadet:
                CheckCadetWinStatus(state, bullseye_position);
                break;
            case Difficulty::kRookie:
                CheckRookieWinStatus(state, bullseye_position);
                break;
            case Difficulty::kVeteran:
                CheckVeteranWinStatus(state, bullseye_position, bulls_bearing, aircraft_heading, milesperpixel);
                break;
            case Difficulty::kAce:
                CheckAceWinStatus(state);
         }

    } else {
        // No guesses remaining
        // TODO: check how we clean up at the end of a round. Probably want to pause to allow the user to restart etc.
        state = GameState::kGameEnded;
    }
}

int RoundManager::GetRemainingGuesses() const
{
    PLOG_VERBOSE << "RoundManager::GetRemaingGuesses() called";
    return total_guesses_ - current_guess_;
}

void RoundManager::IncreaseGuessCount(){
    PLOG_VERBOSE << "RoundManager::DecreaseRemainingGuesses() called";
    current_guess_ += 1;
}


// TODO: This needs to be called from the main event loop where a player comes out of the setup screeen has has chnaged the difficulty level. 
void RoundManager::ResetRound() {
    PLOG_VERBOSE << "RoundManager::ResetRound() called";

    enemy_manager_.get()->DeleteBogies();
}

std::string RoundManager::GenerateAwacsCallString(int bogey_index) {
    PLOG_VERBOSE << "RoundManager::GenerateAwacsCallString() called";

    return awacs_manager_->GetAWACSCall(enemy_manager_, bogey_index);
}