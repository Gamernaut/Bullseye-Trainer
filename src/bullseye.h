///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BULLSEYE_H
#define BULLSEYE_H

#include "image_object.h"
#include "constants.h"

namespace cpv {

	class Bullseye : public ImageObject {
	private:
		// Bearing from the bulls eye to my aircraft
		BearingRangeAltitudeHeading brah_bulls_to_aircraft_ = { 0, 7, 20000, 0 };

	protected:

	public:
		SDL_Surface* bullseye_surface_ = nullptr;
		SDL_Texture* bullseye_texture_ = nullptr;
		const double PI_ = 3.14159265;

	public:
		Bullseye(SDL_Renderer* renderer, std::string filename);
		~Bullseye();
		void SetBearingFromBullseyeToMyAircraft(int bearing);
		int GetBearingFromBullseyeToMyAircraft() const;
		void SetRangeFromBullseyeToMyAircraft(int range);
		int GetRangeFromBullseyeToMyAircraft() const;
		void SetAltitude(int altitude);
		int GetAltitude() const;
		void SetHeading(int aspect);
		int GetHeading() const;
	};

}

#endif	// BULLSEYE_H
