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

#ifndef CPV_TEXT_OBJECT_H
#define CPV_TEXT_OBJECT_H

#include <iostream>

#include <SDL_ttf.h>
#include <plog/Log.h>
#include "constants.h"

namespace cpv {

	class TextObject {
		// Attributes
	protected:
		SDL_Surface* text_surface_ = nullptr;
		SDL_Texture* text_texture_ = nullptr;
		TTF_Font* font_ = nullptr;
		std::string text_to_display_ = "";
		Coordinate draw_position_{ kCenterMfdDrawArea };

	public:

		// Methods
	private:

	public:
		TextObject(std::string font_name, int font_size);
		~TextObject();
		void SetPosition(int x_position, int y_position);
		void Draw(SDL_Renderer* renderer, std::string text_to_display, SDL_Color text_colour, int x_position, int y_position);
		void HighlightedDraw(SDL_Renderer* renderer, std::string text, SDL_Color fg_colour, SDL_Color bg_colour, int x_position, int y_position);
		void DrawCenteredInWindow(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int y_position);
		void DrawCenteredAt(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int x_position, int y_position);
	};

}

#endif	// CPV_TEXT_OBJECT_H