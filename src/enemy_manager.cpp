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

EnemyManager::EnemyManager() {
    PLOG_VERBOSE << "EnemyManager constructor called";
}

EnemyManager::~EnemyManager() {
    PLOG_VERBOSE << "EnemyManager destructor called";
}

int EnemyManager::GetBogieCount() {
    PLOG_VERBOSE << "EnemyManager::GetBogieCount() called.";

    return bogie_vector_.size();
}

void EnemyManager::CreateBogey(int bogey_count) {
    PLOG_VERBOSE << "EnemyManager::CreateBogey() called";

    // Create a temporary bogey object on stack before copying to vector (original is not added to the vector)
    Bogey tempBogey;

    if (bogey_count > 3) bogey_count = 3;

    int bearingFromBullsToBogey = 0;
    int rangeFromBullsToBogey = 0;
    int bogeyAltitude = 0;
    int bogeyHeading = 0;

    if (bogey_count > 0 && bogey_count <= 3) {
        // Avoid 0 and 360 as these can cause issues
        bearingFromBullsToBogey = 1 + rand() % 358;
        tempBogey.SetBearing(bearingFromBullsToBogey);

        // Range to between 5 miles and 40 miles
        rangeFromBullsToBogey = 5 + (rand() % 35);
        tempBogey.SetRange(rangeFromBullsToBogey);

        // Between angels 5 and 40
        bogeyAltitude = 5 + (rand() % 35);
        tempBogey.SetAltitude(bogeyAltitude);

        // Same and bulls stay away from 0 and 360
        bogeyHeading = 1 + rand() % 358;
        tempBogey.SetHeading(bogeyHeading);

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
    bogie_vector_.clear();
}

