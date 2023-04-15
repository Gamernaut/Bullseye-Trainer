///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    	
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "start_screen.h"

using namespace cpv;

StartScreen::StartScreen(SDL_Renderer* sdl_renderer_, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width) : MFD(sdl_renderer_, mfd_top_edge, mfd_left_edge, mfd_height, mfd_width) {
    PLOG_VERBOSE << "StartScreen constructor called";

    // Loads and creates the graphic which contains the name of the program
    start_screen_text_ = std::make_unique<ImageObject>(sdl_renderer_, kBullsTrainerStartScreenText);
    if (!start_screen_text_) {
        PLOG_ERROR << "StartScreen::StartScreen(): Could not create start_screen_text_";
    }

    // Loads and creates the graphic which contains the image on the start screen
    start_screen_image_ = std::make_unique<ImageObject>(sdl_renderer_, kBullsTrainerStartScreenImage);
    if (!start_screen_image_) {
        PLOG_ERROR << "StartScreen::StartScreen(): Could not create start_screen_image_";
    }

    // Add OSB13 for the start button
    start_button = std::make_unique<OnSceenButton>(kOSB13LeftEdge, kOSB13TopEdge, kOSB13RightEdge, kOSB13BottomEdge, false, "OSB13");
    if (!start_button) {
        PLOG_ERROR << "StartScreen::StartScreen(): Could not create start_button";
    }
}

StartScreen::~StartScreen() {
    PLOG_VERBOSE << "StartScreen destructor called";
}

void StartScreen::Draw(SDL_Renderer* sdl_renderer_) {
    PLOG_VERBOSE << "StartScreen:Draw() called";

    SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 255);
    SDL_RenderClear(sdl_renderer_);

    // This needs to be centered in the MFD so the default values when the image was created will do this
    start_screen_image_->Draw(sdl_renderer_);

    // Reset position of the text to the center of the text panel before drawing
    start_screen_text_->SetUIPosition(Coordinate{ (kTextPanelWidth / 2) , (kTextPanelHeight / 2) });
    start_screen_text_->Draw(sdl_renderer_);

    // Add code to render button stuff
    // start_button->DrawOutline(ss_renderer);

    SDL_RenderPresent(sdl_renderer_);
}
