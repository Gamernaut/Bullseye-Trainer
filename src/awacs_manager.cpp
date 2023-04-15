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

#include "awacs_manager.h"


using namespace cpv;

AWACSManager::AWACSManager() {

}

AWACSManager::~AWACSManager() {

}

std::string AWACSManager::ConvertHeadingToCompass(int bogie_heading) {
    std::string heading_as_compass{ "" };

    if (bogie_heading >= 339 && bogie_heading <= 360) {
        heading_as_compass = "North";
    } else if (bogie_heading >= 0 && bogie_heading <= 22) {
        heading_as_compass = "North";
    } else if (bogie_heading >= 23 && bogie_heading <= 67) {
        heading_as_compass = "North East";
    } else if (bogie_heading >= 68 && bogie_heading <= 114) {
        heading_as_compass = "East";
    } else if (bogie_heading >= 115 && bogie_heading <= 157) {
        heading_as_compass = "South East";
    } else if (bogie_heading >= 158 && bogie_heading <= 202) {
        heading_as_compass = "South";
    } else if (bogie_heading >= 203 && bogie_heading <= 248) {
        heading_as_compass = "South West";
    } else if (bogie_heading >= 249 && bogie_heading <= 290) {
        heading_as_compass = "West";
    } else if (bogie_heading >= 291 && bogie_heading <= 338) {
        heading_as_compass = "North West";
    } else {
        heading_as_compass = "Unknown";
    }

    return heading_as_compass;
}

std::string AWACSManager::GetAWACSCall(std::unique_ptr<EnemyManager>& enemy_mananger, int bogey_index) {
    PLOG_VERBOSE << "AWACSManager::GetAWACSCall called";

    // Bogey contains BRAH from bogey to bulls eye
    Bogey tempBogey;
    BearingRangeAltitudeHeading bogeyData;

    if (bogey_index < 1) {
        bogey_awacs_call = "bogey index is less than 1";

    } else if (bogey_index > enemy_mananger->GetBogieCount()) {
        bogey_awacs_call = " ";

    } else {
        tempBogey = enemy_mananger->GetBogieAtVectorPosition(bogey_index - 1);
        bogeyData = tempBogey.GetBRAH();

        bogey_bearing = std::to_string(bogeyData.bearing_in_degrees);
        bogey_range = std::to_string(bogeyData.distance_in_miles);
        bogey_altitude = std::to_string(bogeyData.altitude_in_angels);
        bogey_heading = ConvertHeadingToCompass(bogeyData.heading_in_degrees);

        bogey_awacs_call = "Bulls " + bogey_bearing + " for " + bogey_range + " at Angles " + bogey_altitude + " tracking " + bogey_heading;
    }

    return bogey_awacs_call;
}