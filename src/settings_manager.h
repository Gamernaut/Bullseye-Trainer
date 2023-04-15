///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	April 2023
//
//	Purpose:	Manages the difficulty and login settings, reads and stores them to the registry.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_SETTINGS_MANAGER_H_
#define CPV_SETTINGS_MANAGER_H_

// System includes


// Include 3rd party code
#include "WinReg.hpp"

// include my code
#include "game_enums.h"
#include "constants.h"


namespace cpv {

    class SettingsManager {

    //Attributes
    public:

    protected:
        Difficulty game_difficulty{};
        int logging_level = 0;
        // Use the registry to preserve setting between runs, uses https://github.com/GiovanniDicanio/WinReg (or https://github.com/m4x1m1l14n/Registry) 
        winreg::RegKey bulls_trainer_key;
        winreg::RegResult bulls_trainer_result;

    private:

    // Methods
    public:
        SettingsManager();
        ~SettingsManager();
        void WriteSettingsToRegistry();
        bool ReadSettingsFromRegistry();
        Difficulty& GetGameDifficulty();
        void SetGameDifficulty(const Difficulty& level);
        void SetLoggingLevel(int log_level);
        int GetLoggingLevel() const;

    protected:

    private:

    };

}

#endif     // end of CPV_SETTINGS_MANAGER_H_