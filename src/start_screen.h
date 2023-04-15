///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	December 2021
//
//	Purpose:    Utilisation of the Multi Function Display (MFD) to display the start up splash screen.	
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_START_SCREEN_H_
#define CPV_START_SCREEN_H_

#include <plog/Log.h>
#include "mfd.h"

namespace cpv {

	class StartScreen : public MFD {
		// Attributes
	private:

	protected:
		std::unique_ptr<ImageObject> start_screen_image_ = nullptr;
		std::unique_ptr<ImageObject> start_screen_text_ = nullptr;
		std::unique_ptr<OnSceenButton> start_button = nullptr;

		SDL_Renderer* ss_renderer = nullptr;

	public:



		// Methods
	protected:


	public:
		StartScreen(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~StartScreen();
		void Draw(SDL_Renderer* sdl_renderer_);
	};
}



#endif // CPV_START_SCREEN_H_