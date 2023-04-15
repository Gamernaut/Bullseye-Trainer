///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	Dec 2022
//
//	Purpose:    Utilisation of the Multi Function Display (MFD) to display the various application options.	
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_OPTIONS_SCREEN_H_
#define CPV_OPTIONS_SCREEN_H_

#include "mfd.h"
#include "text_object.h"
#include "game_enums.h"
#include "round_manager.h"
#include "settings_manager.h"

namespace cpv {

	class OptionsScreen : public MFD {
		// Attributes
	private:


	protected:
		// On Screen Buttons used on Options Screen
		std::unique_ptr<OnSceenButton> recruit_button_;
		std::unique_ptr<OnSceenButton> cadet_button_;
		std::unique_ptr<OnSceenButton> rookie_button_;
		std::unique_ptr<OnSceenButton> veteran_button_;
		std::unique_ptr<OnSceenButton> ace_button_;
		std::unique_ptr<OnSceenButton> select_button_;
		std::unique_ptr<OnSceenButton> cancel_button_;
		std::unique_ptr<OnSceenButton> verbose_button_;
		std::unique_ptr<OnSceenButton> info_button_;
		std::unique_ptr<OnSceenButton> critical_button_;

		// Fonts for drawing text on screen
		std::unique_ptr<TextObject> font_18_ = nullptr;
		std::unique_ptr<TextObject> font_16_ = nullptr;

	public:



		// Methods
	protected:


	public:
		OptionsScreen(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~OptionsScreen();
		//void Draw(int loggingLevel);	// Future update, pass in the enum and figure out what to display in this call
		void DrawRecruitText(SDL_Renderer* sdl_renderer);
		void DrawCadetText(SDL_Renderer* sdl_renderer);
		void DrawRookieText(SDL_Renderer* sdl_renderer);
		void DrawVeteranText(SDL_Renderer* sdl_renderer);
		void DrawAceText(SDL_Renderer* sdl_renderer);
		//void Draw(SDL_Renderer* sdl_renderer, const Difficulty& game_difficulty, const int logging_level);
		void Draw(SDL_Renderer* sdl_renderer, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_);
		void DrawStaticText(SDL_Renderer* sdl_renderer);
	};
}



#endif // CPV_OPTIONS_SCREEN_H_