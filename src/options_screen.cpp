///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	Dec 2022
//
//	Purpose:	
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "options_screen.h"

using namespace cpv;

OptionsScreen::OptionsScreen(SDL_Renderer* sdl_renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(sdl_renderer, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
    PLOG_VERBOSE << "OptionsScreen constructor called";

    font_18_ = std::make_unique<TextObject>(kFont2, 18);
    font_16_ = std::make_unique<TextObject>(kFont2, 16);

}

OptionsScreen::~OptionsScreen() {
    PLOG_VERBOSE << "OptionsScreen destructor called";

}

void OptionsScreen::DrawStaticText(SDL_Renderer* sdl_renderer) {
    font_18_->Draw(sdl_renderer, "Training Difficulty", kMfdGreenColour, 103, 302);
    font_18_->Draw(sdl_renderer, "Logging Level", kMfdGreenColour, 477, 302);
    font_16_->Draw(sdl_renderer, "Recruit", kMfdWhiteColour, 95, 380);
    font_16_->Draw(sdl_renderer, "Cadet", kMfdWhiteColour, 95, 454);
    font_16_->Draw(sdl_renderer, "Rookie", kMfdWhiteColour, 95, 532);
    font_16_->Draw(sdl_renderer, "Veteran", kMfdWhiteColour, 95, 609);
    font_16_->Draw(sdl_renderer, "Ace", kMfdWhiteColour, 95, 688);
    font_16_->Draw(sdl_renderer, "High", kMfdWhiteColour, 597, 454);
    font_16_->Draw(sdl_renderer, "Medium", kMfdWhiteColour, 578, 535);
    font_16_->Draw(sdl_renderer, "Low", kMfdWhiteColour, 599, 609);
    font_16_->Draw(sdl_renderer, "Click on a button to get a description.", kMfdWhiteColour, 189, 750);
    font_16_->Draw(sdl_renderer, "SELECT", kMfdWhiteColour, 254, 792);
    font_16_->Draw(sdl_renderer, "CANCEL", kMfdWhiteColour, 430, 792);
    font_16_->Draw(sdl_renderer, "Contact: Gamernaut19@gmail.com", kMfdBlueColour, 210, 690);
    font_16_->Draw(sdl_renderer, "Version: 0.1a", kMfdBlueColour, 300, 710);
}

void OptionsScreen::DrawRecruitText(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "OptionsScreen::DrawRecruitText() called";

    font_16_->HighlightedDraw(sdl_renderer, "Recruit", kMfdBlackColour, kMfdWhiteColour, 95, 380);
    font_16_->Draw(sdl_renderer, "Description for Recruit level", kMfdGreenColour, 190, 400);
    font_16_->Draw(sdl_renderer, "Click on the HSD as close as you can", kMfdWhiteColour, 190, 440);
    font_16_->Draw(sdl_renderer, "to where you think the bullseye is,", kMfdWhiteColour, 190, 460);
    font_16_->Draw(sdl_renderer, "distance is NOT important.", kMfdWhiteColour, 190, 480);
    font_16_->Draw(sdl_renderer, "Objective", kMfdGreenColour, 190, 580);
    font_16_->Draw(sdl_renderer, "Get within +/- 15 deg of the bearing", kMfdWhiteColour, 190, 600);
    font_16_->Draw(sdl_renderer, "to the bullseye.", kMfdWhiteColour, 190, 620);
}

void OptionsScreen::DrawCadetText(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "OptionsScreen::DrawCadetText() called";

    font_16_->HighlightedDraw(sdl_renderer, "Cadet", kMfdBlackColour, kMfdWhiteColour, 95, 454);
    font_16_->Draw(sdl_renderer, "Description for Cadet level", kMfdGreenColour, 190, 400);
    font_16_->Draw(sdl_renderer, "Click on the HSD as close as you can to", kMfdWhiteColour, 190, 440);
    font_16_->Draw(sdl_renderer, "where you think the bullseye is. Both", kMfdWhiteColour, 190, 460);
    font_16_->Draw(sdl_renderer, "bearing and distance count.", kMfdWhiteColour, 190, 480);
    font_16_->Draw(sdl_renderer, "Objective", kMfdGreenColour, 190, 580);
    font_16_->Draw(sdl_renderer, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, 190, 600);
    font_16_->Draw(sdl_renderer, "distance to the bullseye.", kMfdWhiteColour, 190, 620);
}

void OptionsScreen::DrawRookieText(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "OptionsScreen::DrawRookieText() called";

    font_16_->HighlightedDraw(sdl_renderer, "Rookie", kMfdBlackColour, kMfdWhiteColour, 95, 532);
    font_16_->Draw(sdl_renderer, "Description for Rookie level", kMfdGreenColour, 190, 400);
    font_16_->Draw(sdl_renderer, "Click on the HSD as close as you can to", kMfdWhiteColour, 190, 440);
    font_16_->Draw(sdl_renderer, "where you think the bogey is, using", kMfdWhiteColour, 190, 460);
    font_16_->Draw(sdl_renderer, "where you think the bullseye is. Only ", kMfdWhiteColour, 190, 480);
    font_16_->Draw(sdl_renderer, "bearing to the bogey from the bullseye", kMfdWhiteColour, 190, 500);
    font_16_->Draw(sdl_renderer, "counts.", kMfdWhiteColour, 190, 520);
    font_16_->Draw(sdl_renderer, "Objective", kMfdGreenColour, 190, 580);
    font_16_->Draw(sdl_renderer, "Get within +/- 15 deg of the bearing to", kMfdWhiteColour, 190, 600);
    font_16_->Draw(sdl_renderer, "the bogey from the bullseye.", kMfdWhiteColour, 190, 620);
}

void OptionsScreen::DrawVeteranText(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "OptionsScreen::DrawVeteranText() called";

    font_16_->HighlightedDraw(sdl_renderer, "Veteran", kMfdBlackColour, kMfdWhiteColour, 95, 609);
    font_16_->Draw(sdl_renderer, "Description for Veteran level", kMfdGreenColour, 190, 400);
    font_16_->Draw(sdl_renderer, "Click on the HSD as close as you can to", kMfdWhiteColour, 190,440);
    font_16_->Draw(sdl_renderer, "where you think the bogey is, using", kMfdWhiteColour, 190, 460);
    font_16_->Draw(sdl_renderer, "where you think the bullseye is. Both ", kMfdWhiteColour, 190, 480);
    font_16_->Draw(sdl_renderer, "bearing and distance to the bogey", kMfdWhiteColour, 190, 500);
    font_16_->Draw(sdl_renderer, "count.", kMfdWhiteColour, 190, 520);
    font_16_->Draw(sdl_renderer, "Objective", kMfdGreenColour, 190, 580);
    font_16_->Draw(sdl_renderer, "Get within +/- 15 deg and 20% of", kMfdWhiteColour, 190, 600);
    font_16_->Draw(sdl_renderer, "distance to the bogey.", kMfdWhiteColour, 190, 620);
}

void OptionsScreen::DrawAceText(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "OptionsScreen::DrawAceText() called";

    font_16_->HighlightedDraw(sdl_renderer, "Ace", kMfdBlackColour, kMfdWhiteColour, 95, 688);
    font_16_->Draw(sdl_renderer, "Description for Ace level", kMfdGreenColour, 190, 400);
    font_16_->Draw(sdl_renderer, "Click on the HSD as close as you can to", kMfdWhiteColour, 190, 440);
    font_16_->Draw(sdl_renderer, "where you think the bogey's are, using", kMfdWhiteColour, 190, 460);
    font_16_->Draw(sdl_renderer, "where you think the bullseye is. Both ", kMfdWhiteColour, 190, 480);
    font_16_->Draw(sdl_renderer, "bearing and distance from the bullseye", kMfdWhiteColour, 190, 500);
    font_16_->Draw(sdl_renderer, "to each bogey counts.", kMfdWhiteColour, 190, 520);
    font_16_->Draw(sdl_renderer, "Objective", kMfdGreenColour, 190, 580);
    font_16_->Draw(sdl_renderer, "Click within +/- 15 deg and 20% of", kMfdWhiteColour, 190, 600);
    font_16_->Draw(sdl_renderer, "distance to the bogey's.", kMfdWhiteColour, 190, 620);
}

void OptionsScreen::Draw(SDL_Renderer * sdl_renderer, const std::unique_ptr<SettingsManager>&settings_manager_) {
    DrawStaticText(sdl_renderer);

    // Draw the correct text for the appropriate difficulty and logging level
    if (settings_manager_->GetGameDifficulty() == Difficulty::kRecruit) {
        DrawRecruitText(sdl_renderer);
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kCadet) {
        DrawCadetText(sdl_renderer);
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kRookie) {
        DrawRookieText(sdl_renderer);
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kVeteran) {
        DrawVeteranText(sdl_renderer);
    }
    else if (settings_manager_->GetGameDifficulty() == Difficulty::kAce) {
        DrawAceText(sdl_renderer);
    }

    // Reverse the text on the 
    if (settings_manager_->GetLoggingLevel() == 1) {
        font_16_->HighlightedDraw(sdl_renderer, "High", kMfdBlackColour, kMfdWhiteColour, 597, 454);
    }
    else if (settings_manager_->GetLoggingLevel() == 2) {
        font_16_->HighlightedDraw(sdl_renderer, "Medium", kMfdBlackColour, kMfdWhiteColour, 578, 535);
    }
    else if (settings_manager_->GetLoggingLevel() == 3) {
        font_16_->HighlightedDraw(sdl_renderer, "Low", kMfdBlackColour, kMfdWhiteColour, 599, 609);
    }

    // Outer MFD frame, calls method in MFD base class, centered in MFD by default so no need for SetUIPosition call
    DrawMFDFrame(sdl_renderer);
}
