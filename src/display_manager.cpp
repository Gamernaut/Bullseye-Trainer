///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    This class is responsible for initializing SDL and creating the 3 screens used by the program;
//				the start screen which holds the intro text & image, the main game screen and the options screen.
//				Each screen (which is derived from HSD) knows how to draw itself, this class has 3 thin wrapper 
//				methods to abstract away the details from the main logic code
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "display_manager.h"

using namespace cpv;

DisplayManager::DisplayManager()
{
    PLOG_VERBOSE << "DisplayManager constructor called";
}

DisplayManager::~DisplayManager()
{
    PLOG_VERBOSE << "DisplayManager destructor called";
}


bool DisplayManager::InitialiseSDL() {
	PLOG_VERBOSE << "DisplayManager::InitialiseSDL() called";
	
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		PLOG_ERROR << "Error initializing SDL library";
		return false;
	}

	if (TTF_Init() != 0) {
		PLOG_ERROR << "Error initializing TTF library";
		return false;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	sdl_window_ = SDL_CreateWindow(
		"Bulls Trainer",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		kWindowWidth,
		kWindowHeight,
		NULL
	);

	if (!sdl_window_) {
		PLOG_ERROR << "DisplayManager::InitialiseSDL(): Error creating SDL window";
		return false;
	}
	PLOG_VERBOSE << "DisplayManager::InitialiseSDL(): SDL window created";

	sdl_renderer_ = SDL_CreateRenderer(sdl_window_, -1, 0);

	if (!sdl_renderer_) {
		PLOG_ERROR << "DisplayManager::InitialiseSDL(): Error creating SDL Renderer";
		return false;
	}
	PLOG_VERBOSE << "DisplayManager::InitialiseSDL(): SDL Renderer created";

	//sdl_font_ = TTF_OpenFont(kFont2, kFontSize1);
	//if (!sdl_font_) {
	//	PLOG_ERROR << "DisplayManager::InitialiseSDL(): Error opening font Renderer";
	//	return false;
	//}
	PLOG_VERBOSE << "DisplayManager::InitialiseSDL(): Font Renderer created";

	return true;
}


bool DisplayManager::CreateScreens()
{
	PLOG_VERBOSE << "DisplayManager::CreateScreens() called";

	// Create the screens (Start screen, Options and main HSD)
	start_screen_ = std::make_unique<StartScreen>(sdl_renderer_, 0, 180, kMfdFrameHeight, kMfdFrameWidth);
	if (!start_screen_) {
		PLOG_ERROR << "DisplayManager::CreateScreens failed to create start_screen";
		return false;
	}

	options_screen_ = std::make_unique<OptionsScreen>(sdl_renderer_, 0, 180, kMfdFrameHeight, kMfdFrameWidth);
	if (!options_screen_) {
		PLOG_ERROR << "DisplayManager::CreateScreens failed to create options_screen";
		return false;
	}

	hsd_screen_ = std::make_unique<HSD>(sdl_renderer_, 0, 180, kMfdFrameHeight, kMfdFrameWidth);
	if (!hsd_screen_) {
		PLOG_ERROR << "DisplayManager::CreateScreens failed to create hsd_screen";
		return false;
	}

	return true;
}


void DisplayManager::RenderStartScreen()
{
    PLOG_VERBOSE << "DisplayManager:RenderStartScreen() called";

	start_screen_->Draw(sdl_renderer_);
	SDL_RenderPresent(sdl_renderer_);
}


void DisplayManager::RenderOptionsSceen(const std::unique_ptr<SettingsManager>& settings_manager_) const {
	PLOG_VERBOSE << "DisplayManager:RenderOptionsSceen() called";

	// options_screen_->Draw(sdl_renderer_);
	SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 255);
	SDL_RenderClear(sdl_renderer_);

	options_screen_->Draw(sdl_renderer_, settings_manager_);
	SDL_RenderPresent(sdl_renderer_);
}


// This method uses the information about the enemy aircraft and passes it to the HSD draw function as a read only attribute.
// Maybe add game state so HSD can draw arcs/boxes accordingly once round manager has determined guess state
void DisplayManager::RenderGameScreen(const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& setting_manager_) const {
	PLOG_VERBOSE << "DisplayManager:RenderGameScreen() called";

	// Currently render screen green
	SDL_SetRenderDrawColor(sdl_renderer_, 0, 0, 0, 255);
	SDL_RenderClear(sdl_renderer_);

	hsd_screen_->Draw(sdl_renderer_, round_manager_, game_state, setting_manager_);
	SDL_RenderPresent(sdl_renderer_);
}


void DisplayManager::CloseDown() {
	PLOG_VERBOSE << "DisplayManager:CloseDown() called";

//	TTF_CloseFont(sdl_font_);
	SDL_DestroyRenderer(sdl_renderer_);
	SDL_DestroyWindow(sdl_window_);
	TTF_Quit();
	SDL_Quit();
}