///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	July 2022
//
//	Purpose:    	
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef CPV_BOGEY_H_
#define CPV_BOGEY_H_

#include "constants.h"

namespace cpv {


	class Bogey {
	// Attributes
	private:
		// BRA from the bogey to the bullseye
		BearingRangeAltitudeHeading brah_bogie_to_bulls_{ 0 , 0 , 0 , 0 };
		Coordinate bogey_position_{ 100,100 };

	protected:

	public:


	// Methods
	public:

	protected:

	public:
		Bogey();
		~Bogey();
		void SetBearing(int bearing);
		int GetBearing() const;
		void SetRange(int range);
		int GetRange() const;
		void SetAltitude(int altitude);
		int GetAltitude() const;
		void SetHeading(int aspect);
		int GetHeading() const;
		BearingRangeAltitudeHeading GetBRAH() const;
	};

}

#endif  // !CPV_BOGEY_H_
