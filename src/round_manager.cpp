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

    // TODO: Implement RoundManager
}

void RoundManager::CheckRecruitWinStatus(GameState& state) {
    PLOG_VERBOSE << "RoundManager::CheckRecruitWinStatus() called";

    // TODO    1 - Implement CheckRecruitWinStatus
    // Win condition is to correctly identify the bearing of the bullseye from the aircraft (within a cone 30 deg wide, +/- 15 deg of the point clicked on)

    //// Calculate the actual and user guessed bearing
    //int actual_bearing = bullseye_->GetHeading();
    //int user_bearing_guess = angle_between_point_a_and_b(hsd_->my_aircraft_->GetPosition(), mouse_click_pos_);

    //// set State to win if the bearing is within acceptable win condition
    //if (user_bearing_guess >= (actual_bearing - 15) && user_bearing_guess <= (actual_bearing + 15)) {
    //    // Set the game state so the HSD Draw method can display the guess
    //    state = GameState::kRoundWon;
    //}
    //// set State to playing if not correct and not last guess
    //else if (current_guess_ < total_guesses_) {
    //    // Set the game state so the HSD Draw method can display the guess
    //    state = GameState::kRoundPlaying;
    //    std::cout << "Keep going Recruit" << std::endl;
    //}
    //// set State to fail if this is the last guess and it's wrong
    //else {
    //    // Set the game state so the HSD Draw method can display the guess
    //    state = GameState::kRoundFail;
    //    std::cout << "Better luck next time Recruit" << std::endl;
    //}
}
//
//void RoundManager::CheckCadetWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_)
//{
//    PLOG_VERBOSE << "RoundManager::CheckCadetWinStatus() called";
//
//    // TODO    2- Implement CheckCadetWinStatus
//}
//
//void RoundManager::CheckRookieWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_)
//{
//    PLOG_VERBOSE << "RoundManager::CheckRookieWinStatus() called";
//
//    // TODO    3- Implement CheckRookieWinStatus
//}
//
//void RoundManager::CheckVeteranWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_)
//{
//    PLOG_VERBOSE << "RoundManager::CheckVeteranWinStatus() called";
//
//    // TODO    4 - Implement CheckVeteranWinStatus
//}
//
//void RoundManager::CheckAceWinStatus(GameState& state, const std::unique_ptr<Bullseye>& bullseye_, const std::unique_ptr<HSD>& hsd_)
//{
//    PLOG_VERBOSE << "RoundManager::CheckAceWinStatus() called";
//
//    // TODO    5 - Implement CheckAceWinStatus
//}
//
//bool RoundManager::IsClickInRectAroundBulls()
//{
//    PLOG_VERBOSE << "RoundManager::IsClickInRectAroundBulls() called";
//    return false;   // TODO: Update to actual code, this may give unexpected behaviour
//}


void RoundManager::SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_) {
    PLOG_VERBOSE << "RoundManager::SetupRound() called";

    // TODO - should this be in round_manager or bulls_trainer?
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

    // TODO: set the F16 heading and the bulls position here
    // Might need to pass the HSD reference to this object so we can set the values from here
}

void RoundManager::CheckGuessAgainstWinCondition(GameState& state, Coordinate mouse_click_position, const std::unique_ptr<SettingsManager>& settings_manager) {
    
    PLOG_VERBOSE << "RoundManager::CheckGuessAgainstWinCondition() called";

    current_guess_ += 1;

    mouse_click_pos_ = mouse_click_position;

    if (current_guess_ <= total_guesses_) {
        // Check the win condition for this round based on level of difficulty
        switch (settings_manager->GetGameDifficulty()) {
            case Difficulty::kRecruit:
                CheckRecruitWinStatus(state);
            //case Difficulty::kRookie:
            //    CheckRookieWinStatus(state, bullseye);
            //case Difficulty::kCadet:
            //    CheckCadetWinStatus(state, bullseye);
            //case Difficulty::kVeteran:
            //    CheckVeteranWinStatus(state, bullseye);
            //case Difficulty::kAce:
            //    CheckAceWinStatus(state, bullseye);
         }

    }

}

int RoundManager::GetRemainingGuesses() const
{
    PLOG_VERBOSE << "RoundManager::GetRemaingGuesses() called";
    return total_guesses_;
}

void RoundManager::ResetRound() {
    PLOG_VERBOSE << "RoundManager::ResetRound() called";

    enemy_manager_.get()->DeleteBogies();
}

std::string RoundManager::GenerateAwacsCallString(int bogey_index) {
    PLOG_VERBOSE << "RoundManager::GenerateAwacsCallString() called";

    return awacs_manager_->GetAWACSCall(enemy_manager_, bogey_index);
}