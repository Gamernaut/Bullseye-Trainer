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

void RoundManager::CheckRecruitWinStatus(GameState& state)
{
    PLOG_VERBOSE << "RoundManager::CheckRecruitWinStatus() called";

    // TODO: Implement CheckRecruitWinStatus
}

void RoundManager::CheckCadetWinStatus(GameState& state)
{
    PLOG_VERBOSE << "RoundManager::CheckCadetWinStatus() called";

    // TODO: Implement CheckCadetWinStatus
}

void RoundManager::CheckRookieWinStatus(GameState& state)
{
    PLOG_VERBOSE << "RoundManager::CheckRookieWinStatus() called";

    // TODO: Implement CheckRookieWinStatus
}

void RoundManager::CheckVeteranWinStatus(GameState& state)
{
    PLOG_VERBOSE << "RoundManager::CheckVeteranWinStatus() called";

    // TODO: Implement CheckVeteranWinStatus
}

void RoundManager::CheckAceWinStatus(GameState& state)
{
    PLOG_VERBOSE << "RoundManager::CheckAceWinStatus() called";

    // TODO: Implement CheckAceWinStatus
}

bool RoundManager::IsClickInRectAroundBulls()
{
    PLOG_VERBOSE << "RoundManager::IsClickInRectAroundBulls() called";
    return false;   // TODO: Update to actual code, this may give unexpected behaviour
}


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

void RoundManager::CheckGuessAgainstWinCondition(GameState& state, Coordinate mouse_click_position)
{
    PLOG_VERBOSE << "RoundManager::CheckGuessAgainstWinCondition() called";

    // TODO: Implement CheckGuessAgainstWinCondition
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

/*
Difficulty& RoundManager::GetGameDifficulty() {
    PLOG_VERBOSE << "RoundManager::GetGameDifficulty() called";

    return game_difficulty;
}

void RoundManager::SetGameDifficulty(const Difficulty& level) {
    PLOG_VERBOSE << "RoundManager::GetGameDifficulty() called";

    game_difficulty = level;
}


int RoundManager::GetLoggingLevel() const {
    PLOG_VERBOSE << "RoundManager::GetLoggingLevel() called";

    return logging_level;
}

void RoundManager::SetLoggingLevel(int log_level) {
    PLOG_VERBOSE << "RoundManager::SetLoggingLevel() called";

    logging_level = log_level;
}
*/

std::string RoundManager::GenerateAwacsCallString(int bogey_index) {
    PLOG_VERBOSE << "RoundManager::GenerateAwacsCallString() called";

    return awacs_manager_->GetAWACSCall(enemy_manager_, bogey_index);
}