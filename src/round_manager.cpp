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

//#include "constants.h"
#include "round_manager.h"

// Neede for atan2 function
#include <cmath>

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
}

void RoundManager::CheckRecruitWinStatus(GameState& state, Coordinate aircraft_position, int aircraft_heading, int bulls_bearing, Coordinate bullseye_position) {
    // Win condition is to correctly identify the bearing of the bullseye from the aircraft (within a band 50 deg wide, +/- 25 deg of the point clicked on)

    PLOG_VERBOSE << "RoundManager::CheckRecruitWinStatus() called";

    // Version 3

    int user_angle_guess = angle_between_point_a_and_b(aircraft_position, g_mouse_click_pos);
    int bulls_angle = angle_between_point_a_and_b(aircraft_position, bullseye_position);

    if (user_angle_guess >= (bulls_angle - 15) && (user_angle_guess <= bulls_angle + 15)) {
        // Player has picked a direction that is within +/- 15 deg of the actual direction
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct direction but still has some turns left
        state = GameState::kRoundPlaying;
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundEnded;
    }

    //  Version 2
    //// Calculate the slope of the lines from the aircraft to the bullseye and the clicked point
    // 
    //double slope1 = (static_cast<double>(bullseye_position.y) - static_cast<double>(aircraft_position.y)) / (static_cast<double>(bullseye_position.x) - static_cast<double>(aircraft_position.x));
    //double slope2 = (static_cast<double>(g_mouse_click_pos.y) - static_cast<double>(aircraft_position.y)) / (static_cast<double>(g_mouse_click_pos.x) - static_cast<double>(aircraft_position.x));

    //double differenceInSlopes = abs(slope2 - slope1);

    //if (differenceInSlopes <= 0.1) {
    //    // Player has picked a direction that is within +/- 15 deg of the actual direction
    //    state = GameState::kRoundWon;
    //} else if (current_guess_ < total_guesses_) {
    //    // player didn't pick correct direction but still has some turns left
    //    state = GameState::kRoundPlaying;
    //} else {
    //    // Player has run out of turns so the round ends
    //    state = GameState::kRoundEnded;
    //}
     
    ///  Version 1
    //// The arctan function breaks the circle into 4 quarters as it goes from -90 to 90 deg (start at 0 at North then 90 at east, back to 0 for south and then 90 for west)
    //// TODO: Next line is NOT working correctly seems to be an issue of heading is greater than 180, needs checking

    //int user_bearing_guess = angle_between_point_a_and_b(aircraft_position, g_mouse_click_pos);

    //// First quadrant we just add the heading to the angle
    //if (aircraft_heading >= 0 && aircraft_heading <= 90) {
    //    user_bearing_guess += aircraft_heading;
    //}
    //// Second quadrant 
    //else if (aircraft_heading >= 90 && aircraft_heading <= 360) {
    //    user_bearing_guess = (user_bearing_guess - 360) + aircraft_heading;
    //}

    //int reciprocal_bulls_bearing = reciprocate_angle(bulls_bearing);

    //// This needs to handle the situation where the bullseye is 180 to the aircraft as +/- 15 goes past the 360/0 boundary which complicates the maths
    //// Check to see if the user bearing is up to 15 deg past 360/0 and if the reciprocal bulls heading is within 15 deg of 360.
    //// If this is true then they can be added to account for clicking on the right side of 360 
    //if (reciprocal_bulls_bearing >= 345 && user_bearing_guess >= 0 && user_bearing_guess <= 15) {
    //    user_bearing_guess = user_bearing_guess + reciprocal_bulls_bearing;
    //}
    ////if ((user_bearing_guess >= (reciprocate_angle(bulls_bearing) - 15) || user_bearing_guess >= (360 - 15)) && (user_bearing_guess <= (reciprocate_angle(bulls_bearing) + 15) || user_bearing_guess >= (0 + 15)) ) {
    ////if (user_bearing_guess >= (reciprocal_bulls_bearing - (kPieSliceWidth / 2)) && (user_bearing_guess <= reciprocal_bulls_bearing + (kPieSliceWidth / 2))) {
    //if (user_bearing_guess >= (reciprocal_bulls_bearing - 25) && (user_bearing_guess <= reciprocal_bulls_bearing + 25)) {
    //    // Player has picked a direction that is within +/- 15 deg of the actual direction
    //    state = GameState::kRoundWon;
    //} else if (current_guess_ < total_guesses_) {
    //    // player didn't pick correct direction but still has some turns left
    //    state = GameState::kRoundPlaying;
    //} else {
    //    // Player has run out of turns so the round ends
    //    state = GameState::kRoundEnded;
    //}
}


void RoundManager::CheckCadetWinStatus(GameState& state, Coordinate bullseye_position) {
    // Win condition is to correctly identify the position of the bullseye within +/- 20 pixels

    PLOG_VERBOSE << "RoundManager::CheckCadetWinStatus() called";

    int x_difference = bullseye_position.x - g_mouse_click_pos.x;
    int y_difference = bullseye_position.y - g_mouse_click_pos.y;

    if (x_difference <= (kRectangleWidth / 2) && x_difference >= -(kRectangleWidth / 2) && y_difference <= (kRectangleHeight / 2) && y_difference >= -(kRectangleHeight / 2)) {
        // Player has picked the location of the bulls eye so set game state to display the green box over the bullseye
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct location but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Cadet to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundEnded;
        // Display "Better luck next time Cadet" 
    }
}
 

void RoundManager::CheckRookieWinStatus(GameState& state, int aircraft_heading, Coordinate bullseye_position) {
    // Win condition is to correctly identify the bearing from the bullseye to the bogey within +/- 25 deg of actual.

    PLOG_VERBOSE << "RoundManager::CheckRookieWinStatus() called";

    // Get the bearing from bulls to the bogey (will only be 1 bogey at this difficulty level)
    int bulls_heading_to_bogey = enemy_manager_->GetBogieAtVectorPosition(0).GetBearing();
    int user_bearing_guess = angle_between_point_a_and_b(bullseye_position, g_mouse_click_pos);

    // needs to account for aircraft heading so need to convert to absolute heading so it matches heading from North from bullseye
    user_bearing_guess = abs(user_bearing_guess - (360 - aircraft_heading));


    if (user_bearing_guess >= (bulls_heading_to_bogey - (kPieSliceWidth / 2)) && user_bearing_guess <= (bulls_heading_to_bogey + (kPieSliceWidth / 2))) {
        // Player has picked a direction that is within +/- 15 deg of the actual direction
        state = GameState::kRoundWon;
    } else if (current_guess_ < total_guesses_) {
        // player didn't pick correct direction but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Rookie to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundEnded;
        // Display "Better luck next time Rookie" 
    }
}


void RoundManager::CheckVeteranWinStatus(GameState& state, Coordinate bullseye_position, int bulls_bearing, int aircraft_heading, double milesperpixel) {
    // Win condition is to correctly identify the position of the bogey within 30 x 30 pixels of the center of the bogey

    PLOG_VERBOSE << "RoundManager::CheckVeteranWinStatus() called";

    double  bogey_range = static_cast<double>(enemy_manager_->GetBogieAtVectorPosition(0).GetRange());
    // Negative aircraft heading is CRITICAL for this to work
    Coordinate bogey_position = calc_endpoint_given_start_bearing_and_range(bullseye_position, enemy_manager_->GetBogieAtVectorPosition(0).GetBearing(), -aircraft_heading, bogey_range, milesperpixel);

    int x_difference = bogey_position.x - g_mouse_click_pos.x;
    int y_difference = bogey_position.y - g_mouse_click_pos.y;

    if (x_difference <= (kRectangleWidth / 2) && x_difference >= -(kRectangleWidth / 2) && y_difference <= (kRectangleHeight / 2) && y_difference >= -(kRectangleHeight / 2)) {
        // Player has picked the location of the bulls eye so set game state to display the green box over the bullseye
        state = GameState::kRoundWon;
    }
    else if (current_guess_ < total_guesses_) {
        // player didn't pick correct location but still has some turns left
        state = GameState::kRoundPlaying;
        // Display message to Veteran to keep trying
    } else {
        // Player has run out of turns so the round ends
        state = GameState::kRoundEnded;
        // Display "Better luck next time Veteran" 
    }
}


void RoundManager::CheckAceWinStatus(GameState& state) {
    PLOG_VERBOSE << "RoundManager::CheckAceWinStatus() called";

    // TODO: Implement CheckAceWinStatus with multi win conditions
}


void RoundManager::SetupRound(const std::unique_ptr<SettingsManager>& settings_manager_, std::unique_ptr<DisplayManager>& display_manager_) {
   // void RoundManager::SetupRound(const std::unique_ptr<SettingsManager>&settings_manager_) {
    PLOG_VERBOSE << "RoundManager::SetupRound() called";

    settings_manager_->ReadSettingsFromRegistry();

    // Clear any previous bogies as this should only get called when anew round starts
    if (enemy_manager_->GetBogieCount() > 0) {
        enemy_manager_->DeleteBogies();
    }

    // Enemies not needed for lowest difficulty as they are about finding the bullseye 
    // but still need to set the number of guesses so do that up front

    total_guesses_ = 3;
    current_guess_ = 0;
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
    // Use the display manager pointer to access the HSD reference so we can call the method in the HSD object

    // Compiler doesn't know what this is as I can't include the deceleration of the call, just a forward definition but that doesn;t include any details
    // display_manager_->hsd_screen_->RandomiseAircrafAndBullseye();
}

void RoundManager::CheckGuessAgainstWinCondition(GameState& state, const std::unique_ptr<SettingsManager>& settings_manager, Coordinate bullseye_position, int bulls_bearing, Coordinate aircraft_position, int aircraft_heading, double milesperpixel) {
    
    PLOG_VERBOSE << "RoundManager::CheckGuessAgainstWinCondition() called";

    IncreaseGuessCount();

    if (GetRemainingGuesses() >= 0) {
        // Check the win condition for this round based on level of difficulty
        switch (settings_manager->GetGameDifficulty()) {
            case Difficulty::kRecruit:
                CheckRecruitWinStatus(state, aircraft_position, aircraft_heading, bulls_bearing, bullseye_position);
                break;
            case Difficulty::kCadet:
                CheckCadetWinStatus(state, bullseye_position);
                break;
            case Difficulty::kRookie:
                CheckRookieWinStatus(state, aircraft_heading, bullseye_position);
                break;
            case Difficulty::kVeteran:
                CheckVeteranWinStatus(state, bullseye_position, bulls_bearing, aircraft_heading, milesperpixel);
                break;
            case Difficulty::kAce:
                CheckAceWinStatus(state);
         }

    } else {
        // No guesses remaining
        state = GameState::kRoundEnded;
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


std::string RoundManager::GenerateAwacsCallString(int bogey_index) {
    PLOG_VERBOSE << "RoundManager::GenerateAwacsCallString() called";

    return awacs_manager_->GetAWACSCall(enemy_manager_, bogey_index);
}