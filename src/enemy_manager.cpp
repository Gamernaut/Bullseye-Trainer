///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	Manages the enemy aircraft. Is responsible for creating them, randomizing their position
//              and destroying them at the end of each round
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "enemy_manager.h"

using namespace cpv;

EnemyManager::EnemyManager()
{
    PLOG_VERBOSE << "EnemyManager constructor called";
}

EnemyManager::~EnemyManager()
{
    PLOG_VERBOSE << "EnemyManager destructor called";
}

int EnemyManager::GetBogieCount()
{
    PLOG_VERBOSE << "EnemyManager::GetBogieCount() called.";

    return bogie_vector_.size();
}

void EnemyManager::CreateBogey(int bogey_count)
{
    PLOG_VERBOSE << "EnemyManager::CreateBogey() called";

    // Create a temporary bogey object on stack before adding to vector
    Bogey tempBogey;

    if (bogey_count > 0 && bogey_count <= 3) {
        // TESTING: Set it's position attributes relative to the bulls eye
        // TODO: Set these as random values once testing is finished
        tempBogey.SetBearing(180);
        tempBogey.SetRange(17);
        tempBogey.SetAltitude(17);
        tempBogey.SetHeading(0);

        // Add a copy of tempBogey to vector, tempBogey destroyed when function returns
        bogie_vector_.push_back(tempBogey);
    }

    if (bogey_count > 1 && bogey_count <= 3) {
        // TESTING: Set it's position attributes relative to the bulls eye
        // TODO: Set these as random values once testing is finished
        tempBogey.SetBearing(90);
        tempBogey.SetRange(15);
        tempBogey.SetAltitude(22);
        tempBogey.SetHeading(90);

        // Add a copy of tempBogey to vector, tempBogey destroyed when function returns
        bogie_vector_.push_back(tempBogey);
    }

    if (bogey_count == 3) {
        // TESTING: Set it's position attributes relative to the bulls eye
        // TODO: Set these as random values once testing is finished
        tempBogey.SetBearing(200);
        tempBogey.SetRange(15);
        tempBogey.SetAltitude(18);
        tempBogey.SetHeading(180);

        // Add a copy of tempBogey to vector, tempBogey destroyed when function returns
        bogie_vector_.push_back(tempBogey);
    }

}

Bogey EnemyManager::GetBogieAtVectorPosition(int bogieIndex) {
    return bogie_vector_.at(bogieIndex);
}

void EnemyManager::DeleteBogies() {

}

