///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose: This class is the main part of the application, it codinates the rounds, manages graphical
//           display and user input via SDl.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
// 
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_BULLS_TRAINER_H_
#define CPV_BULLS_TRAINER_H_

// Include 3rd party code
#include <plog/Log.h>
#include <SDL.h>
#include <SDL_ttf.h>


// Include my code
#include "game_enums.h"
#include "round_manager.h"
#include "display_manager.h"
#include "enemy_manager.h"
#include "settings_manager.h"

namespace cpv {
    class Bulls_Trainer {
    // Properties
    public:
        GameState game_state{ GameState::kStartScreen };
        GameState temp_game_state{ game_state };

        // holds the original values when the user enters the options screen so they can be reapplied if they exit instead of selecting
        Difficulty tempDiff{};
        int tempLog = 0;
    
    protected:
        bool is_game_running_ = false;
        int milliseconds_previous_frame_ = 0;
 //       Difficulty game_difficulty{};
 //       int logging_level;

        // Pointers to manager objects
        std::unique_ptr<RoundManager> round_manager_ = nullptr;
        std::unique_ptr<DisplayManager> display_manager_ = nullptr;
        std::unique_ptr<SettingsManager> settings_manager_ = nullptr;


    
    private:
        int mouseX = 0, mouseY = 0;

    // Methods
    public:
        Bulls_Trainer();
        ~Bulls_Trainer();
        bool Initialise();
        void CloseDown();
        void Render();
        void ProcessInput();
        void Run();
    
    protected:
    
    private:

    };
}


#endif  // CPV_BULLS_TRAINER_H_
