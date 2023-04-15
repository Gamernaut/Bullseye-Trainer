///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "image_object.h"

namespace cpv {

	class Aircraft : public ImageObject {
	public:

	protected:
		int	current_heading_ = 0;
		int	altitude_ = 20000;

	public:
		Aircraft(SDL_Renderer* renderer, std::string filename);
		~Aircraft();
		void SetHeading(int new_heading);
		int GetHeading() const;
		void SetAltitude(int new_altitude);
		int GetAltitude() const;
	};

}
#endif // AIRCRAFT_H