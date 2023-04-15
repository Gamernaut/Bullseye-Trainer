///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:    Stores the parameters for the various objects used byt the program. Sections are indentied to
//				aid visualisation of the heirarchical nature of the graphical design 
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
//////////////////////////////////////////////////////////////////////////////////////////////


#ifndef CPV_CONFIG_H_
#define CPV_CONFIG_H_

#include <string> 

// include 3rd party code
#include <SDL_ttf.h>


namespace cpv {

////////////////////////////////////////
// These custom data types hold info about absolute (Coordinate) and relative (BearingRangeAltitude) positions of objects in the program
////////////////////////////////////////

	typedef struct {
		int x;
		int y;
	} Coordinate;

	// Data type to hold the Bearing, Range/distance, Altitude and Aspect/Heading (BRAA) of an aircraft in relation to a defined point, such as the bullseye or players aircraft
	typedef struct {
		int bearing_in_degrees;
		int distance_in_miles;
		int altitude_in_angels;
		int heading_in_degrees;		// Is actually treated as the heading of the aircraft, not the aspect
	} BearingRangeAltitudeHeading;

////////////////////////////////////////
// Environment setup parameters
////////////////////////////////////////
	
	// Log file directory referenced from the running program
	inline const char* kLogPath = "Debug\\logs\\log.txt";	// based of the project folder "Bulls trainer - June 2022 rewrite"

	// Registry string for accessing registry entires
	inline const std::wstring kRegEntry = L"SOFTWARE\\Bulls_Trainer";
	inline const std::wstring kRegDifficulty = L"Bulls_Trainer_Difficulty";
	inline const std::wstring kDifficultyDefault = L"Recruit";
	inline const std::wstring kRegLogging = L"Bulls_Trainer_Logging";
	inline const std::wstring kLoggingDefault = L"info";

	// These are used by the "game loop" to determine how often to draw the screen, FPS not critical in this program
	const int kFPS = 10;
	const int kmilliseconds_per_frame = 1000 / kFPS;


////////////////////////////////////////
// Window set up parameters - everything is drawn inside the window so set these up first
////////////////////////////////////////
	
	// Sizes of the window (in Pixels)
	const int kWindowWidth = 730;
	const int kWindowHeight = 900;
	const Coordinate windowCenter{ kWindowWidth / 2, kWindowHeight / 2 };

	////////////////////////////////////////
	// AWACS Calls panel.
	// This panel sits at the top of the window above the MFD and displays text information to the user. 
	////////////////////////////////////////

		const int kTextPanelHeight = 180;
		const int kTextPanelWidth = kWindowWidth;
		inline Coordinate mouse_click_position = { 0 , 0 };

	////////////////////////////////////////
	// General MFD setup parameters.
	// The MFD sits inside the window and is capable of displaying various program modes, such as start screen,
	// option screen and "game" mode (HSD, FCR etc.). These parameters define the general MFD physical characteristics
	////////////////////////////////////////
	
		// MFD attributes (in pixels)
		inline const char* kMfdFrameFileName = "./assets/images/MFD_Frame.png";
		const int kMfdFrameWidth = 727;
		const int kMfdFrameHeight = 720;
	
		// Thickness of the frame on the 4 sides, might be the same so maybe reduce to 1 eventually
		const int kLeftMfdFrameSize = 83;		// need to check this value
		const int kRightMfdFrameSize = 83;		// need to check this value
		const int kTopMfdFrameSize = 83;		// need to check this value
		const int kBottomMfdFrameSize = 83;		// need to check this value

		// The size of the drawable area, this is the area inside the MFD frame (the sizes of which are defined above)
		const int kMfdDrawAreaWidth = kMfdFrameWidth - (kLeftMfdFrameSize + kRightMfdFrameSize);
		const int kMfdDrawAreaHeight = kMfdFrameHeight - (kTopMfdFrameSize + kBottomMfdFrameSize);
		const Coordinate kCenterMfdDrawArea{ 
			kLeftMfdFrameSize + (kMfdDrawAreaWidth / 2),
			kTextPanelHeight + kTopMfdFrameSize + (kMfdDrawAreaHeight / 2)
		};

		// On Screen Buttons, are part of the MFD frame
		const int kButtonWidth = 52;
		const int kButtonHeight = 52;

		// Set top and bottom edges of row of buttons across the top of the MFD
		const int kOSB1to5TopEdge = 190;
		const int kOSB1to5BottomEdge = 240;

		// Set left and right edges of column of buttons on right side the MFD
		const int kOSB6to10LeftEdge = 660;
		const int kOSB6to10RightEdge = 715;

		// Set top and bottom edges of row of buttons across the bottom of the MFD
		const int kOSB11to15TopEdge = 825;
		const int kOSB11to15BottomEdge = 875;

		// Set left and right edges of column of buttons on left side the MFD
		const int kOSB16to20LeftEdge = 15;
		const int kOSB16to20RightEdge = 65;

		// OSB 1 settings
		const int kOSB1LeftEdge = 170;
		const int kOSB1RightEdge = kOSB1LeftEdge + kButtonWidth;
		const int kOSB1TopEdge = kOSB1to5TopEdge;
		const int kOSB1BottomEdge = kOSB1to5BottomEdge;

		// OSB 7 settings
		const int kOSB7LeftEdge = kOSB6to10LeftEdge;
		const int kOSB7RightEdge = kOSB6to10RightEdge;
		const int kOSB7TopEdge = 435;
		const int kOSB7BottomEdge = kOSB7TopEdge + kButtonHeight;

		// OSB 8 settings
		const int kOSB8LeftEdge = kOSB6to10LeftEdge;
		const int kOSB8RightEdge = kOSB6to10RightEdge;
		const int kOSB8TopEdge = 512;
		const int kOSB8BottomEdge = kOSB8TopEdge + kButtonHeight;

		// OSB 9 settings
		const int kOSB9LeftEdge = kOSB6to10LeftEdge;
		const int kOSB9RightEdge = kOSB6to10RightEdge;
		const int kOSB9TopEdge = 590;
		const int kOSB9BottomEdge = kOSB9TopEdge + kButtonHeight;

		// OSB 12 settings
		const int kOSB12LeftEdge = 425;
		const int kOSB12RightEdge = kOSB12LeftEdge + kButtonWidth;
		const int kOSB12TopEdge = kOSB11to15TopEdge;
		const int kOSB12BottomEdge = kOSB11to15BottomEdge;

		// OSB 13 settings
		const int kOSB13LeftEdge = 339;
		const int kOSB13RightEdge = kOSB13LeftEdge + kButtonWidth;
		const int kOSB13TopEdge = kOSB11to15TopEdge;
		const int kOSB13BottomEdge = kOSB11to15BottomEdge;

		// OSB 14 settings
		const int kOSB14LeftEdge = 253;
		const int kOSB14RightEdge = kOSB14LeftEdge + kButtonWidth;
		const int kOSB14TopEdge = kOSB11to15TopEdge;
		const int kOSB14BottomEdge = kOSB11to15BottomEdge;

		// OSB 16 settings
		const int kOSB16LeftEdge = kOSB16to20LeftEdge;
		const int kOSB16RightEdge = kOSB16to20RightEdge;
		const int kOSB16TopEdge = 665;
		const int kOSB16BottomEdge = kOSB16TopEdge + kButtonHeight;

		// OSB 17 settings
		const int kOSB17LeftEdge = kOSB16to20LeftEdge;
		const int kOSB17RightEdge = kOSB16to20RightEdge;
		const int kOSB17TopEdge = 590;
		const int kOSB17BottomEdge = kOSB17TopEdge + kButtonHeight;

		// OSB 18 settings
		const int kOSB18LeftEdge = kOSB16to20LeftEdge;
		const int kOSB18RightEdge = kOSB16to20RightEdge;
		const int kOSB18TopEdge = 515;
		const int kOSB18BottomEdge = kOSB18TopEdge + kButtonHeight;

		// OSB 19 settings
		const int kOSB19LeftEdge = kOSB16to20LeftEdge;
		const int kOSB19RightEdge = kOSB16to20RightEdge;
		const int kOSB19TopEdge = 435;
		const int kOSB19BottomEdge = kOSB19TopEdge + kButtonHeight;

		// OSB 20 settings
		const int kOSB20LeftEdge = kOSB16to20LeftEdge;
		const int kOSB20RightEdge = kOSB16to20RightEdge;
		const int kOSB20TopEdge = 358;
		const int kOSB20BottomEdge = kOSB20TopEdge + kButtonHeight;

		// Colours to be used in the MFD
		const SDL_Color kMfdGreenColour{ 0, 175, 0 };
		const SDL_Color kMfdWhiteColour{ 255, 255, 255 };
		const SDL_Color kMfdYellowColour{ 178, 178, 14 };
		const SDL_Color kMfdBlueColour{ 0, 200, 200 };
		const SDL_Color kMfdBlackColour{ 0, 0, 0 };

		// Fonts used in the MFD
		inline const char* kFont1 = "C:/Windows/Fonts/Arial.ttf";
		inline const char* kFont2 = "./assets/fonts/white-rabbit/whitrabt.ttf";
		//inline const char* fontName1 = "./assets/fonts/digitgraphics/DigiGraphics.ttf";
		//inline const char* fontName1 = "./assets/fonts/visitor-brk/visitor2.ttf";
		inline const int kFontSize1 = 16;
		inline const int kFontSize2 = 18;

		////////////////////////////////////////
		// This section defines the objects that appear in the MFD Draw area (various images and geometric shapes)
		////////////////////////////////////////

			// These images are used to show whether the player has guessed correctly or not depending on difficulty level
			inline const char* kGreenPieSlice = "./assets/images/green_pie_slice_165x684.png";
			inline const char* kRedPieSlice = "./assets/images/red_pie_slice_165x684.png";
			inline const char* kRedRectangle = "./assets/images/red_rectangle_64x64.png";
			inline const char* kGreenRectangle = "./assets/images/green_rectangle_64x64.png";

		//////////////////////////////////////////
		// The program runs the MFD in 3 modes, the start up screen mode, the options screen mode and the actual "game" screen mode
		// these are the definitions that are specific to each one
		//////////////////////////////////////////

			//////////////////////////////////////////
			// Settings for Start screen mode. 
			// First screen shown when program starts
			//////////////////////////////////////////
				inline const char* kBullsTrainerStartScreenText = "./assets/images/main_title_396x74.png";
				inline const char* kBullsTrainerStartScreenImage = "./assets/images/main_menu_727x720.png";
				const int kBullsTrainerStartScreenTextWidth = 396;
				const int kBullsTrainerStartScreenTextHeight = 74;

			////////////////////////////////////////// 
			// Settings for options screen mode. 
			// This screen is shown when the setting button on the MFD is selected 
			//////////////////////////////////////////
				inline const char* kMfdSetupFileName = "./assets/images/setup_screen_727x720.png";
				inline const char* kAceLevelFileName = "./assets/images/ace_level_319x177.png";
				const int kAceImageWidth = 319;
				const int kAceImageHeight = 177;
				inline const char* kCadetLevelFileName = "./assets/images/cadet_level324x149.png";
				const int kCadetImageWidth = 324;
				const int kCadetImageHeight = 149;
				inline const char* kRecruitLevelFileName = "./assets/images/recruit_level317x123.png";
				const int kRecruitImageWidth = 317;
				const int kRecruitImageHeight = 123;
				inline const char* kRookieLevelFileName = "./assets/images/rookie_level_330x150.png";
				const int kRookieImageWidth = 330;
				const int kRookieImageHeight = 150;
				inline const char* kVeteranLevelFileName = "./assets/images/veteran_level_318x170.png";
				const int kVeteranImageWidth = 318;
				const int kVeteranImageHeight = 170;

			////////////////////////////////////////// 
			// Settings for main "game" screen mode. 
			// This screen is the main screen and is shown after the start screen and after exiting the options screen 
			//////////////////////////////////////////

				// This is the difference between the center of the HSD rings in their normal position (2/3 of the way down the MFD)
				// and their centered position in pixels. Used to toggle the position of the HSD rings each time the DEP button is pressed.
				const int kDepOffset = 102;

				// HSD Distance rings attributes. 
				// There are 2 HSD ring formats. This one is the default layout with 3 rings, centered about 2/3 of the way down the screen.
				// Needs to rotate, so define the center coordinates in the MFD draw area for the HSD rings in their normal position
				// when the HSD is toggled to center we can use the center of the MFD as the rotation point. 
				inline const char* kHSD_DistRingsFileName = "./assets/images/hsd_distance_rings_noncentered_698x698.png";
				const int kHSDDistRingsImageWidth = 698;
				const int kHSDDistRingsImageHeight = 682;

				// HSD Distance rings attributes. 
				// There are 2 HSD ring formats. This is the second HSD ring format with 2 rings and is used when the display is centered (DEP button pressed).
				// Needs to rotate, so define the center coordinates in the MFD draw area for the HSD rings in their normal position
				// when the HSD is toggled to center we can use the center of the MFD as the rotation point. 
				inline const char* kHSD_DistRingsCenteredFileName = "./assets/images/hsd_distance_rings_centered_466x466.png";


				// This sets the center of the HSD rings to the center of the MFD, this is the correct default positioning as it will always
				// be centered left to right but depending on the DEP toggle it may be centered top to bottom or not, thus added in the offset
				// to default it to the 2/3 of the way down the screen in its normal position
				inline Coordinate distRingsCenterNoOffset{ 363 , 667 };
				inline Coordinate distRingsCenterWithOffset{ 363 , 667 - kDepOffset };

				// Players aircraft image and attributes
				inline const char* kAircraftFileName = "./assets/images/Aircraft_datum_42x47.png";
				const int kAircraftImageWidth = 42;
				const int kAircraftImageHeight = 47;
				inline Coordinate aircraftDatumAbsoluteNoOffset{ 363, 667 };
				inline Coordinate aircraftDatumAbsoluteWithOffset{ 363, 667 - kDepOffset };

				// Bogey aircraft image
				inline const char* kBogeyFileName = "./assets/images/bogey_trace_15x15.png";

				// Bullseye image and attributes
				inline const char* kBullsFileName = "./assets/images/bullseye_28x28.png";
				const int kBullsImageWidth = 28;
				const int kBullsImageHeight = 28;

				// Blue bearing circle image and attributes.
				// Needs to rotate so needs to have a center
				inline const char* kBearingCircle = "./assets/images/blue_bearing_ring_55x60.png";							// TODO: The image is not square so doesn't rotate nicely
				const int kBearingCircleWidth = 55;
				const int kBearingCircleHeight = 60;
				inline const char* kBearingPointer = "./assets/images/bearing_pointer_53x65.png";							// TODO: The image is not square so doesn't rotate nicely
				// Is it best to set the absolute position on the MFD here as we've done with the HSD rings or should that be added in the draw code
				const Coordinate bearingCircleCenter{
							kBearingCircleWidth / 2,
							kBearingCircleHeight / 2
				};
				// Absolute version of the one above with 50 meaning 50 pixels to the right of the left hand frame and
				// 100 being 100 pixels less than (above) the bottom frame.
				const Coordinate bearingCircleCenterAbsolute{ 132, 755 };

				// Scale arrow buttons
				inline const char* kIncScaleFileName = "./assets/images/inc_scale_arrow_26x16.png";
				inline const char* kDecScaleFileName = "./assets/images/dec_scale_arrow_26x16.png";

				// Button Text
				inline const char* kSetupButtonText = "SETUP";
				inline const char* kExitButtonText = "EXIT";
				inline const char* kDepButtonText = "DEP";
				inline const char* kCenButtonText = "CEN";

				// Distance to bullseye Text
				inline const char* kDistanceText = "00";

				// Bearing to bullseye Text
				inline const char* kBearingText = "000";

}

#endif  // CPV_CONFIG_H_

