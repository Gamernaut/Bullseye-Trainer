///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	Manages the AWACS aircraft. Is responsible for generating the AWACS calls displayed in the panel 
//              above the HSD in the main game screen.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_AWACS_MANAGER_H_
#define CPV_AWACS_MANAGER_H_

// include core code
#include <iostream>

// Include 3rd party code


// include my code
#include "enemy_manager.h"
#include "bogey.h"


namespace cpv {

    class AWACSManager {
        //Attributes
    public:

    protected:
        std::string bogey_awacs_call{""};
        std::string bogey_bearing{""};
        std::string bogey_range{""};
        std::string bogey_altitude{""};
        std::string bogey_heading{""};

    private:

        // Methods
    public:
        AWACSManager();
        ~AWACSManager();
        std::string GetAWACSCall(std::unique_ptr<EnemyManager>& enemy_mananger, int bogey_index);

    protected:
        std::string ConvertHeadingToCompass(int bogie_heading);

    private:

    };

}

#endif  // End of CPV_ENEMY_MANAGER_H_