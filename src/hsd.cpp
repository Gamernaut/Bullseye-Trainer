///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    Abstraction of the Horizontal Situation Display (HSD). This is a type of MFD (Multi Function Display) and is surrounded 
//				by OSBs (On-Screen Buttons).
//              This class holds the overall state of the HSD, it knows settings such as the range, in the app world, and where the 
//				various objects are on the HSD. It uses the maths functions and returns the in app distance and angles between various
//				objects. It also knows about the buttons around the edge and updates the state based on their settings.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "hsd.h"
#include "maths_functions.h"
#include "constants.h"

using namespace cpv;

HSD::HSD(SDL_Renderer* sdl_renderer_, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(sdl_renderer_, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
    PLOG_VERBOSE << "HSD constructor called";

    ////////////////////////////////////////////////////
    // 
    // Create all the image objects used by the HSD
    //
    ////////////////////////////////////////////////////

    // Main 3 ring "default" HSD Rings
    hsd_distance_rings_ = std::make_unique<ImageObject>(sdl_renderer_, kHSD_DistRingsFileName);
    if (!hsd_distance_rings_) {
        PLOG_ERROR << "HSD constructor: Could not create hsd_distance_rings_";
    }

    // 2 ring centered HSD image
    hsd_distance_rings_centered_ = std::make_unique<ImageObject>(sdl_renderer_, kHSD_DistRingsCenteredFileName);
    if (!hsd_distance_rings_centered_) {
        PLOG_ERROR << "HSD constructor: Could not create hsd_distance_rings_centered_";
    }

    // Bearing ring in the bottom left corner
    bearing_ring_ = std::make_unique<ImageObject>(sdl_renderer_, kBearingCircle);
    if (!bearing_ring_) {
        PLOG_ERROR << "HSD constructor: Could not create bearing_ring_";
    }

    // Bearing pointer
    bearing_pointer_ = std::make_unique<ImageObject>(sdl_renderer_, kBearingPointer);
    if (!bearing_pointer_) {
        PLOG_ERROR << "HSD constructor: Could not create bearing_pointer_";
    }

    // Increase scale arrow
    scale_up_arrow_ = std::make_unique<ImageObject>(sdl_renderer_, kIncScaleFileName);
    if (!scale_up_arrow_) {
        PLOG_ERROR << "HSD constructor: Could not create scale_up_arrow_";
    }

    // Decrease scale arrow
    scale_down_arrow_ = std::make_unique<ImageObject>(sdl_renderer_, kDecScaleFileName);
    if (!scale_down_arrow_) {
        PLOG_ERROR << "HSD constructor: Could not create scale_down_arrow_";
    }

    // Aircraft symbol in the middle of the HSD
    my_aircraft_ = std::make_unique<Aircraft>(sdl_renderer_, kAircraftFileName);
    if (!my_aircraft_) {
        PLOG_ERROR << "HSD constructor: Could not create my_aircraft_";
    } else {
        // TODO: remove this else clause, but heading needs to be set from somewhere, probably round manager during new round creation. Change this value to change my aircraft heading
        my_aircraft_->SetHeading(0);                                                                                // TESTING
    }

    // Bullseye symbol
    bullseye_ = std::make_unique<Bullseye>(sdl_renderer_, kBullsFileName);
    if (!bullseye_) {
        PLOG_ERROR << "HSD constructor: Could not create bullseye_";
    } else {
        // TODO: remove this else clause, but these need to be set from somewhere, probably round manager during new round creation. Change these values to affect bullseye position
        bullseye_->SetBearingFromBullseyeToMyAircraft(180);                                                          // TESTING
        bullseye_->SetRangeFromBullseyeToMyAircraft(8);
    }

    // Bogey symbol
    bogey_trace_ = std::make_unique<ImageObject>(sdl_renderer_, kBogeyFileName);
    if (!bogey_trace_) {
        PLOG_ERROR << "HSD constructor: Could not create bogey_trace_";
    }


    ////////////////////////////////////////////////////////
    // 
    //      Set up the game win/loose indicator graphics
    // 
    ///////////////////////////////////////////////////////

    // The green arc to display at the easier levels when the guess is correct
    correct_guess_arc_ = std::make_unique<ImageObject>(sdl_renderer_, kGreenPieSlice);
    if (!correct_guess_arc_) {
        PLOG_ERROR << "HSD constructor: Could not create correct_guess_arc_";
    };

    // The red arc to display at the easier levels when the guess is wrong
    wrong_guess_arc_ = std::make_unique<ImageObject>(sdl_renderer_, kRedPieSlice);
    if (!wrong_guess_arc_) {
        PLOG_ERROR << "HSD constructor: Could not create wrong_guess_arc_";
    };

    // The green rectangle to display at the harder levels when the guess is correct
    correct_guess_rect_ = std::make_unique<ImageObject>(sdl_renderer_, kGreenRectangle);
    if (!correct_guess_rect_) {
        PLOG_ERROR << "HSD constructor: Could not create correct_guess_rect_";
    };

    // The red rectangle to display at the harder levels when the guess is wrong
    wrong_guess_rect_ = std::make_unique<ImageObject>(sdl_renderer_, kRedRectangle);
    if (!wrong_guess_rect_) {
        PLOG_ERROR << "HSD constructor: Could not create wrong_guess_rect_";
    };


    ////////////////////////////////
    //       Set up the fonts       
    ///////////////////////////////

    font_20_ = std::make_unique<TextObject>(kFont2, 20);
    if (!font_20_) {
        PLOG_ERROR << "HSD constructor: Could not create font_20_";
    };

    font_18_ = std::make_unique<TextObject>(kFont2, 18);
    if (!font_18_) {
        PLOG_ERROR << "HSD constructor: Could not create font_14_";
    };

    font_16_ = std::make_unique<TextObject>(kFont2, 16);
    if (!font_16_) {
        PLOG_ERROR << "HSD constructor: Could not create font_16_";
    };

    font_14_ = std::make_unique<TextObject>(kFont2, 14);
    if (!font_14_) {
        PLOG_ERROR << "HSD constructor: Could not create font_16_";
    };
}


HSD::~HSD() {
    PLOG_VERBOSE << "HSD destructor called";

    TTF_CloseFont(font_);
}


void HSD::SetCenteredState(bool new_state) {
    PLOG_VERBOSE << "HSD::SetCenteredState() called";

    centered_ = new_state;
}


bool HSD::GetCenteredState(void) const {
    PLOG_VERBOSE << "HSD::GetCenteredState() called";

    return centered_;
}


void HSD::IncreaseRange(void) {
    PLOG_VERBOSE << "HSD::IncreaseRange() called";

    int range_size = HSD_ranges.size() - 1;

    if (range_level_ < range_size) {
        range_level_ += 1;
    }
    else {
        range_level_ = range_size;
    }
}


void HSD::DecreaseRange(void) {
    PLOG_VERBOSE << "HSD::DecreaseRange() called";

    if (range_level_ > 0) {
        range_level_ -= 1;
    }
    else {
        range_level_ = 0;
    }
}


void HSD::ResetHSDRange(void) {
    PLOG_VERBOSE << "HSD::ResetHSDRange() called";

    range_level_ = 0;
}


int HSD::GetHSDCurrentRange(void) const {
    PLOG_VERBOSE << "HSD::GetHSDCurrentRange() called";
    
    if (GetCenteredState()) {
        return HSD_centered_ranges[range_level_];
    }
    else {
        return HSD_ranges[range_level_];
    }
}


double HSD::GetMilesPerPixel(void) const {
    PLOG_VERBOSE << "HSD::GetMilesPerPixel() called";
    int range = GetHSDCurrentRange();

    // if centered then value is different
    if (GetCenteredState() == true) {
        // Number of pixels from the center of the display to the outer circle when centered is 233

        return range / 233.0;
    }
    else {
        // Number of pixels from the center of the display to the outer circle when NOT centered is 348

        return range / 348.0;
    }

}


void HSD::RotateHsdRingsTo(int final_angle) {
    PLOG_VERBOSE << "HSD::RotateHsdRingsTo() called";

    // TODO: Implement RotateHsdRingsTo
}


void HSD::BearingPointerTo(int final_angle) {
    PLOG_VERBOSE << "HSD::BearingPointerTo() called";

    // TODO:  Implement BearingPointerTo
}


void HSD::DrawCorrectGuessArc(int user_bearing_guess) {
    PLOG_VERBOSE << "HSD::DrawCorrectGuessArc() called";

    // TODO: Implement DrawCorrectGuessArc
}


void HSD::DrawWrongGuessArc(int user_bearing_guess) {
    PLOG_VERBOSE << "HSD::DrawWrongGuessArc() called";

    // TODO: Implement DrawWrongGuessArc
}


// Add each static UI item to the draw queue - check if round manager and game state are even needed is even needed
void HSD::AddStaticUIElementsToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_) {
    PLOG_VERBOSE << "HSD::AddStaticUIElementsToDrawQueue() called";

    // Depending on whether the user has selected Centered or not the position of the HSD distance rings and the Aircraft needs to change
    // Set the position depending on centered
    if (GetCenteredState()) {
        // Set the images at the correct position
        hsd_distance_rings_centered_->SetUIPosition(distRingsCenterWithOffset);
        my_aircraft_->SetUIPosition(aircraftDatumAbsoluteWithOffset);

        // The SDL rotate function rotates in the clockwise direction. So 90 deg rotation will actually look like 270
        // To compensate for this we use the rotate to heading method which negates the angle making it turn anti-clockwise
        hsd_distance_rings_centered_->RotateToFinalHeading(my_aircraft_->GetHeading());
        hsd_distance_rings_centered_->Draw(sdl_renderer);

        // Update OSB 2 to display CEN
        font_18_->Draw(sdl_renderer, kCenButtonText, kMfdWhiteColour, 183, 276);
    }
    else {
        hsd_distance_rings_->SetUIPosition(distRingsCenterNoOffset);
        my_aircraft_->SetUIPosition(aircraftDatumAbsoluteNoOffset);

        // The SDL rotate function rotates in the clockwise direction. So 90 deg rotation will actually look like 270
        // To compensate for this we use the rotate to heading method which negates the angle making it turn anti-clockwise
        hsd_distance_rings_->RotateToFinalHeading(my_aircraft_->GetHeading());
        hsd_distance_rings_->Draw(sdl_renderer);

        // Update OSB 2 to display DEP
        font_18_->Draw(sdl_renderer, kDepButtonText, kMfdWhiteColour, 183, 276);
    }

    // As Aircraft position is set above just draw it now, don't need to duplicate code in the if statement as it's the same call
    my_aircraft_->Draw(sdl_renderer);

    // Bearing ring and pointer
    //TODO: Adjust graphics so they rotate around each other correctly
    bearing_ring_->SetUIPosition(bearingCircleCenterAbsolute);
    bearing_ring_->Draw(sdl_renderer);
    bearing_pointer_->SetUIPosition(bearingCircleCenterAbsolute);
    // bearing is from bullseye to aircraft so need reciprocal to point towards bullseye
    bearing_pointer_->RotateToFinalAngle(reciprocate_heading(bullseye_->GetBearingFromBullseyeToMyAircraft()) - my_aircraft_->GetHeading());
    bearing_pointer_->Draw(sdl_renderer);

    // Increase/Decrease range arrows
    // If range is at maximum don't display the up arrow
    if (GetHSDCurrentRange() < 159) {
        scale_up_arrow_->SetUIPosition(Coordinate{ 105,385 });
        scale_up_arrow_->Draw(sdl_renderer);
    }

    // Likewise, if range is at minimum don't display the down arrow.
    if (GetHSDCurrentRange() > 9) {
        scale_down_arrow_->SetUIPosition(Coordinate{ 105,455 });
        scale_down_arrow_->Draw(sdl_renderer);
    }

    // Add the range text
    font_18_->DrawCenteredAt(sdl_renderer, std::to_string(GetHSDCurrentRange()), kMfdWhiteColour, 104, 420);

    // Add Exit button text to the HSD
    font_16_->Draw(sdl_renderer, kExitButtonText, kMfdWhiteColour, 433, 795);

    // Display the bullseye ring with the distance to bulls and the direction indicated by the rotation of the ring and the bearing
    if (bullseye_) {
        // display bulls distance
        std::string distance_text = std::to_string(bullseye_->GetRangeFromBullseyeToMyAircraft());
        std::string padded_dist_text = std::string(2 - distance_text.length(), '0') + distance_text;
        font_16_->Draw(sdl_renderer, padded_dist_text, kMfdBlueColour, bearingCircleCenterAbsolute.x - 9, bearingCircleCenterAbsolute.y - 2);

        // Bearing FROM bullseye
        std::string bearing_text = std::to_string(bullseye_->GetBearingFromBullseyeToMyAircraft());
        std::string padded_bearing_text = std::string(3 - bearing_text.length(), '0') + bearing_text; // Add leading zeros if bearing less than 100 deg
        font_16_->DrawCenteredAt(sdl_renderer, padded_bearing_text, kMfdBlueColour, bearingCircleCenterAbsolute.x, bearingCircleCenterAbsolute.y + 42);
    }

    // If the Game has just started then display the setup option button. options CANNOT be set whilst a round is playing
    if (game_state == GameState::kNewRound || game_state == GameState::kGameEnded) {
        font_16_->Draw(sdl_renderer, kSetupButtonText, kMfdWhiteColour, 260, 795); 
    }

    // Let the user know how many guesses they have left
    font_16_->Draw(sdl_renderer, "Guesses left: " + std::to_string(round_manager_->GetRemainingGuesses()), kMfdGreenColour, 450, 280);

}

// Uses round manager too access AWACS manager to get the calls for the panel
void HSD::AddPanelTextToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_) {
    PLOG_VERBOSE << "HSD::AddPanelTextToDrawQueue() called";

    font_20_->DrawCenteredInWindow(sdl_renderer, "AWACS Call:", kMfdGreenColour, 30);


    // There will always be 1 bogey so display info on that
    font_16_->DrawCenteredInWindow(sdl_renderer, round_manager_->GenerateAwacsCallString(1), kMfdWhiteColour, 65);

    // If difficulty is set to Ace then there could be 1 or 2 more bogies
    if (settings_manager_->GetGameDifficulty() == Difficulty::kAce) {
        font_16_->DrawCenteredInWindow(sdl_renderer, round_manager_->GenerateAwacsCallString(2), kMfdWhiteColour, 85);
        font_16_->DrawCenteredInWindow(sdl_renderer, round_manager_->GenerateAwacsCallString(3), kMfdWhiteColour, 105);
    }
 
    // Display the text that describes what the player should do at each difficulty level
    if (settings_manager_->GetGameDifficulty() == Difficulty::kAce && (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound)) {
        difficulty_text1 = "Difficulty: ACE";
        difficulty_text2 = "Click on HSD close to each group of bogey's";
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kCadet && (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound)) {
        difficulty_text1 = "Difficulty: CADET";
        difficulty_text2 = "Click on HSD close to the bullseye";
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kRecruit && (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound)) {
        difficulty_text1 = "Difficulty: RECRUIT";
        difficulty_text2 = "Click on HSD in the direction of the bullseye";
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kRookie && (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound)) {
        difficulty_text1 = "Difficulty: ROOKIE";
        difficulty_text2 = "Click on HSD in the direction of the bogey from the bullseye";
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kVeteran && (game_state == GameState::kRoundPlaying || game_state == GameState::kNewRound)) {
        difficulty_text1 = "Difficulty: VETERAN";
        difficulty_text2 = "Click on HSD close to the bogey";
    }

    if (difficulty_text1.length() > 0) {
        font_14_->DrawCenteredInWindow(sdl_renderer, difficulty_text1, kMfdBlueColour, 133);
        font_14_->DrawCenteredInWindow(sdl_renderer, difficulty_text2, kMfdBlueColour, 153);
    }
}

// Uses round manager too access enemy manager to get the positions of the things that can be in different positions between rounds (i.e. bogies and bulls)
void HSD::AddDynamicDataToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_) {
    PLOG_VERBOSE << "HSD::AddSensorDataToDrawQueue() called";

    // TODO: Implement display bulls in 3 higher levels but not in the 2 lower ones

    //////////////////////////
    // 
    // Add bulls eye
    //
    //////////////////////////
    
    // Get the bullseye position, if within HSD range convert to screen coordinates and draw on screen
    //        if (bullseye_range <= GetHSDCurrentRange()) { }


    // Bulls bearing value is the bearing FROM the bulls TO my aircraft to have to use the reciprocal for following call to work
    // also we need to subtract the difference between the aircraft heading and the bulls bearing so made the heading negative.
    Coordinate aircraft_start = my_aircraft_->GetPosition();
    int bulls_bearing = reciprocate_heading(bullseye_->GetBearingFromBullseyeToMyAircraft());
    int aircraft_heading = -my_aircraft_->GetHeading();     // This has to be negative for the bullseye to be positioned properly
    double distance_to_bulls = static_cast<double>(bullseye_->GetRangeFromBullseyeToMyAircraft());
    double milesperpixel = GetMilesPerPixel();

    Coordinate bulls_position = calc_endpoint_given_start_bearing_and_range(aircraft_start, bulls_bearing, aircraft_heading, distance_to_bulls, milesperpixel);

    bullseye_->SetUIPosition(bulls_position);
    bullseye_->Draw(sdl_renderer);

    // TODO: Implement display bogies only if correctly identified or round over
     
     
    //////////////////////////
    // 
    // Add bogies
    //
    //////////////////////////

    // TODO - change this so it only draws the appropriate number of bogies based on game difficulty
    int bogey_count = 0;

    if (settings_manager_->GetGameDifficulty() != Difficulty::kAce) {
        bogey_count = 1;
    } else {
        bogey_count = round_manager_->enemy_manager_->GetBogieCount();
    }

    // For each bogey, get the BRAH data, convert to screen position taking HSD scale and centered/non centered into account then set position and add to draw queue
    // Start count at 1 in case bogey count is 0 (as in easiest levels) of loop will always execute even with no bogies
    for (int j = 1; j <= bogey_count; j++) {

        // Bogey contains BRAA from bogey to bulls eye
        Bogey tempBogey = round_manager_->enemy_manager_->GetBogieAtVectorPosition(j - 1);

        Coordinate bulls_start = bullseye_->GetPosition();
        int bulls_bearing = tempBogey.GetBearing();
        int aircraft_heading = -my_aircraft_->GetHeading();     // This was 0 in the original code
        double bogey_range = static_cast<double>(tempBogey.GetRange());
        double milesperpixel = GetMilesPerPixel();

        Coordinate bogey_position = calc_endpoint_given_start_bearing_and_range(bulls_start, bulls_bearing, aircraft_heading, bogey_range, milesperpixel);
        bogey_trace_->SetUIPosition(bogey_position);
        bogey_trace_->Draw(sdl_renderer);



        // Draw a short line from the center of the bogey in the direction the bogey is traveling. Try and keep it about the same length irrespective of HSD scale.
        // The different range scale between centered and non centered means we need different starting sizes. 
        double line_length;
        
        if (GetCenteredState() == true) {
            line_length = 0.3;
        } else {
            line_length = 0.2;
        }

        // % is used as the denominator as it's the minimum size so all larger sizes should be scaled as a multiple of 5.
        line_length = line_length * (GetHSDCurrentRange() / 5.0);

        Coordinate line_end_point = calc_endpoint_given_start_bearing_and_range(bogey_position, tempBogey.GetHeading(), -my_aircraft_->GetHeading(), line_length, GetMilesPerPixel());

        SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(sdl_renderer, bogey_position.x, bogey_position.y, line_end_point.x, line_end_point.y);
    }
}


void HSD::Draw(SDL_Renderer* sdl_renderer, const std::unique_ptr<RoundManager>& round_manager_, const GameState& game_state, const std::unique_ptr<SettingsManager>& settings_manager_)  {
    PLOG_VERBOSE << "HSD::Draw(std::unique_ptr<EnemyManager>& enemy_manager_) called";
    
    // Draws all the static objects using their current states (ranges, angles etc)
    AddStaticUIElementsToDrawQueue(sdl_renderer, game_state, round_manager_);
    AddPanelTextToDrawQueue(sdl_renderer, game_state, round_manager_, settings_manager_);
    AddDynamicDataToDrawQueue(sdl_renderer, game_state, round_manager_, settings_manager_);

    // Outer MFD frame, calls method in MFD base class, centered in MFD by default so no need for SetUIPosition call. Drawn last so overwrites everything else
    DrawMFDFrame(sdl_renderer);
}