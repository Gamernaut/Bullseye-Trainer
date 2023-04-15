

#include <plog/Log.h>


#include "aircraft.h"

using namespace cpv;

Aircraft::Aircraft(SDL_Renderer* renderer, std::string filename) : ImageObject(renderer, filename) {

}

Aircraft::~Aircraft() {

}

void Aircraft::SetHeading(int new_heading) {
    PLOG_VERBOSE << "Aircraft::SetHeading() called";

    current_heading_ = new_heading;
}

int Aircraft::GetHeading() const {

    PLOG_VERBOSE << "Aircraft::GetHeading() called";

    return current_heading_;
}

void Aircraft::SetAltitude(int new_altitude) {

    PLOG_VERBOSE << "Aircraft::SetAltitude() called";

    altitude_ = new_altitude;
}

int Aircraft::GetAltitude() const {

    PLOG_VERBOSE << "Aircraft::GetAltitude() called";

    return altitude_;
}



