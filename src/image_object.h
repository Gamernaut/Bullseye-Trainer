///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_IMAGE_OBJECT_H
#define CPV_IMAGE_OBJECT_H

// Include core code
#include <iostream>

// Include 3rd party code
#include <SDL_Image.h>
#include <plog/Log.h>

// Include my code
#include "constants.h"

namespace cpv {

	class ImageObject {
		// Attributes
	protected:
		std::string name_;
		SDL_Surface* image_surface_ = nullptr;
		SDL_Texture* image_texture_ = nullptr;
		double rotation_angle_ = 0.0;
		int image_width_ = 0;
		int image_height_ = 0;
		// Actually holds the scale setting from 0 to 6 which when used with the right  array gives the current HSD range
//		int hsd_range_to_aircraft = 0;
		bool image_is_visable_ = true;
		// used by draw function to define the rectangle to draw
		Coordinate draw_position_{ 0,0 };

	public:
		Coordinate image_center_{ 0, 0 };

		// Methods

	public:
		ImageObject(SDL_Renderer* renderer, std::string filename);	// just creates the object and allows position setting separately
		~ImageObject();
		virtual void Draw(SDL_Renderer* renderer);
		//void DrawCenteredAt(SDL_Renderer* renderer, Coordinate center_point);
		//void DrawCenteredAt(SDL_Renderer* renderer, int x, int y);
		void DrawArc(SDL_Renderer* renderer, int user_bearing_guess);
		void DrawArc2(SDL_Renderer* renderer, int user_bearing_guess, Coordinate aircraft_center);
		void SetRandomPosition();
		Coordinate GetPosition() const;
		void SetUIPosition(Coordinate new_position);
		void RotateToFinalAngle(double angleInDegrees);
		void RotateToFinalHeading(double angleInDegrees);
		std::string GetObjectName() const;
		bool ValidPosition(int x, int y);
		int GetWidth() const;
		int GetHeight() const;
		bool IsVisable() const;
		void SetVisibility(bool flag);
	};

}
#endif		// CPV_IMAGE_OBJECT_H
