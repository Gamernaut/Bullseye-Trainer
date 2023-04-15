///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    Abstraction of the Horizontal Situation Display (HSD). This is a type of Multi Function Display (MFD) and is surrounded 
//				by OSBs (On-Screen Buttons).
//              This class holds the overall state of the HSD, it knows settings such as the range, in the program world, and where the 
//				various objects are on the HSD. It uses the maths functions and returns the in app distance and angles between various
//				objects. It also knows about the buttons around the edge and updates the appearance based on their settings.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_HSD_H_
#define CPV_HSD_H_

#include "mfd.h"
#include "text_object.h"
#include "enemy_manager.h"
#include "round_manager.h"
#include "settings_manager.h"
#include "aircraft.h"
#include "bullseye.h"
#include "game_enums.h"

//#include "maths_functions.h"
//#include "game_enums.h"


namespace cpv {

	class HSD : public MFD {
		// Attributes
	private:

	protected:
		bool centered_ = false;
		std::vector<int> HSD_centered_ranges = { 5, 10, 20, 40, 80, 160 };
		std::vector<int> HSD_ranges = { 8, 15, 30, 60, 120, 240 };
		std::string difficulty_text1, difficulty_text2;

		// Various graphical objects on the HSD
		std::unique_ptr<ImageObject> hsd_distance_rings_ = nullptr;
		std::unique_ptr<ImageObject> hsd_distance_rings_centered_ = nullptr;
		std::unique_ptr<ImageObject> bearing_ring_ = nullptr;
		std::unique_ptr<ImageObject> bearing_pointer_ = nullptr;
		std::unique_ptr<ImageObject> scale_up_arrow_ = nullptr;
		std::unique_ptr<ImageObject> scale_down_arrow_ = nullptr;
		 
		// On Screen Buttons used on HSD
		std::unique_ptr<OnSceenButton> setup_button = nullptr;
		std::unique_ptr<OnSceenButton> exit_button = nullptr;
		std::unique_ptr<OnSceenButton> inc_rng_button = nullptr;
		std::unique_ptr<OnSceenButton> dec_rng_button = nullptr;
		std::unique_ptr<OnSceenButton> dep_rng_button = nullptr;

		// Fonts for drawing text on screen
		TTF_Font* font_ = nullptr;
		std::unique_ptr<TextObject> font_20_ = nullptr;
		std::unique_ptr<TextObject> font_18_ = nullptr;
		std::unique_ptr<TextObject> font_16_ = nullptr;
		std::unique_ptr<TextObject> font_14_ = nullptr;

		// The images to display if the user made a correct guess or not. 
		// Part of this program, not found on the real aircraft
		std::unique_ptr<ImageObject> correct_guess_arc_;
		std::unique_ptr<ImageObject> wrong_guess_arc_;
		std::unique_ptr<ImageObject> correct_guess_rect_;
		std::unique_ptr<ImageObject> wrong_guess_rect_;

	public:
		std::unique_ptr<Aircraft> my_aircraft_ = nullptr;
		std::unique_ptr<Bullseye> bullseye_ = nullptr;
		std::unique_ptr<ImageObject> bogey_trace_ = nullptr;
		std::unique_ptr<ImageObject> bogey_heading_ = nullptr;

		// Methods
	protected:
		// Main method(s) to draw the static text/images which comprise the instrumentation
		void AddStaticUIElementsToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_);
		// Main method(s) to draw the dynamic images to represent what the sensors see
		void AddDynamicDataToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_);
		// Adds the text to the AWACS panel at the top of the window
		void AddPanelTextToDrawQueue(SDL_Renderer* sdl_renderer, const GameState& game_state, const std::unique_ptr<RoundManager>& round_manager_, const std::unique_ptr<SettingsManager>& settings_manager_);


	public:
		HSD(SDL_Renderer* renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width);
		~HSD();
		//void AddRandomBullsToHSD(std::unique_ptr<Bullseye>& bullseye);
		//void AddRandomBogeyToHSD(std::unique_ptr<Aircraft>& bogey);
		//void AddAwacsCallToDisplay(std::string awacs_call);
		
		// Methods to simulate button presses on the buttons around the HSD
		void SetCenteredState(bool new_state);
		bool GetCenteredState(void) const;
		void IncreaseRange(void);
		void DecreaseRange(void);
		void ResetHSDRange(void);
		int GetHSDCurrentRange(void) const;
		double GetMilesPerPixel(void) const;
		void RotateHsdRingsTo(int final_angle);
		void BearingPointerTo(int final_angle);
		//void Draw(SDL_Renderer* renderer, std::unique_ptr<Bullseye>& bullseye, std::unique_ptr<Aircraft>& bogey1, std::string const& bogey_1_awacs, std::unique_ptr<Aircraft>& bogey2, std::string bogey_2_awacs, std::unique_ptr<Aircraft>& bogey3, std::string bogey_3_awacs, int remaining_guesses);
//		void Draw(SDL_Renderer* renderer, std::unique_ptr<Bullseye>& bullseye, std::unique_ptr<Aircraft>& bogey1, std::unique_ptr<Aircraft>& bogey2, std::unique_ptr<Aircraft>& bogey3, int remaining_guesses, const Difficulty& level, GameState& state, Coordinate mouse_click_position);
		void Draw(SDL_Renderer* sdl_renderer, const std::unique_ptr<RoundManager>& round_manager_, const GameState& game_state, const std::unique_ptr<SettingsManager>& settings_manager_) ;
		void DrawCorrectGuessArc(int user_bearing_guess);
		void DrawWrongGuessArc(int user_bearing_guess);
		
	};
}



#endif // CPV_HSD_H_