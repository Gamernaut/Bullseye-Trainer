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


#include "bullseye.h"

using namespace cpv;

Bullseye::Bullseye(SDL_Renderer* renderer, std::string filename) : ImageObject(renderer, filename) {
}

Bullseye::~Bullseye() {
}

void Bullseye::SetBearingFromBullseyeToMyAircraft(int bearing) {
    brah_bulls_to_aircraft_.bearing_in_degrees = bearing;
}

int Bullseye::GetBearingFromBullseyeToMyAircraft() const {
    return brah_bulls_to_aircraft_.bearing_in_degrees;
}

void Bullseye::SetRangeFromBullseyeToMyAircraft(int range) {
    brah_bulls_to_aircraft_.distance_in_miles = range;
}

int Bullseye::GetRangeFromBullseyeToMyAircraft() const {
    return brah_bulls_to_aircraft_.distance_in_miles;
}

void Bullseye::SetAltitude(int altitude) {
    brah_bulls_to_aircraft_.altitude_in_angels = altitude;
}

int Bullseye::GetAltitude() const {
    return brah_bulls_to_aircraft_.altitude_in_angels;
}

void Bullseye::SetHeading(int aspect) {
    brah_bulls_to_aircraft_.heading_in_degrees = aspect;
}

int Bullseye::GetHeading() const {
    return brah_bulls_to_aircraft_.heading_in_degrees;
}
