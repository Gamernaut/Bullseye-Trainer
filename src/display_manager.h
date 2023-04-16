///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	Manages what is displayed on the screen
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_DISPLAY_MANAGER_H_
#define CPV_DISPLAY_MANAGER_H_

// Include 3rd party code
#include <SDL.h>
#include <plog/Log.h>

// include my code
#include "start_screen.h"
#include "options_screen.h"
#include "hsd.h"
#include "enemy_manager.h"
#include "settings_manager.h"

namespace cpv {

    class DisplayManager {
    // Attributes
    public:
        // So this can be accessed from Bulls_trainer
        std::unique_ptr<HSD> hsd_screen_ = nullptr;

    protected:
        // Pointers for the main SDL objects (to use smart pointers is more complex, need to use the SDL specific delete functions and need to add them to definition so not using them for now)
        SDL_Window* sdl_window_ = nullptr;
        SDL_Renderer* sdl_renderer_ = nullptr;

        // Pointers to screens
        std::unique_ptr<StartScreen> start_screen_ = nullptr;
        std::unique_ptr<OptionsScreen> options_screen_ = nullptr;
    private:
        

    // Methods
    public:
        DisplayManager();
        ~DisplayManager();
        void RenderStartScreen();
 //       void RenderOptionsSceen(const Difficulty& game_difficulty, const int logging_level) const;
        //void RenderOptionsSceen(const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_) const; 
        void RenderOptionsSceen(const std::unique_ptr<SettingsManager>& settings_manager_) const;
        void RenderGameScreen(const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& setting_manager_) const;
        bool InitialiseSDL();
        bool CreateScreens();
        void CloseDown();
    protected:

    private:
    };

}

#endif  //End of CPV_DISPLAY_MANAGER_H_