///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	Manages the enemy aircraft. Is responsible for creating them, randomising their position
//              and destroying them at the end of each round
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_ENEMY_MANAGER_H_
#define CPV_ENEMY_MANAGER_H_

// include core code


// Include 3rd party code
#include <SDL.h>
#include <plog/Log.h>

// include my code
#include "constants.h"
#include "bogey.h"

namespace cpv {

    class EnemyManager {
    //Attributes
    public:

    protected:

    private:
        std::vector<Bogey> bogie_vector_ = { };

    // Methods
    public:
        EnemyManager();
        ~EnemyManager();
        int GetBogieCount();
        void CreateBogey(int bogey_count);
        Bogey GetBogieAtVectorPosition(int bogieIndex);
        void DeleteBogies();

    protected:

    private:

    };

}

#endif  // End of CPV_ENEMY_MANAGER_H_