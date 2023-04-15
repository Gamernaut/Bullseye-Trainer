#include "bogey.h"

using namespace cpv;

Bogey::Bogey() {

}

Bogey::~Bogey() {
}

void Bogey::SetBearing(int bearing) {
    brah_bogie_to_bulls_.bearing_in_degrees = bearing;
}

int Bogey::GetBearing() const {
    return brah_bogie_to_bulls_.bearing_in_degrees;
}

void Bogey::SetRange(int range) {
    brah_bogie_to_bulls_.distance_in_miles = range;
}

int Bogey::GetRange() const {
    return brah_bogie_to_bulls_.distance_in_miles;
}

void Bogey::SetAltitude(int altitude) {
    brah_bogie_to_bulls_.altitude_in_angels = altitude;
}

int Bogey::GetAltitude() const {
    return brah_bogie_to_bulls_.altitude_in_angels;
}

void Bogey::SetHeading(int aspect) {
    brah_bogie_to_bulls_.heading_in_degrees = aspect;
}

int Bogey::GetHeading() const {
    return brah_bogie_to_bulls_.heading_in_degrees;
}

BearingRangeAltitudeHeading Bogey::GetBRAH() const {
    return brah_bogie_to_bulls_;
}
