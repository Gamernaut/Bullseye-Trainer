///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	Junw 2022
//
//	Purpose:    Abstraction of the On-Screen Button, the small push buttons around the edge of the MFD (Multi Function Display).
//              This class contains the position and size of the button, it knows when the mouse pointer is clicked inside a 
//              button and it knows what to display on screen in the unclicked, clicked or toggled state.
// 
//  Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef CPV_OSB_H
#define CPV_OSB_H

// Include core code
#include <iostream>

// include 3rd party code
#include <SDL.h>
#include <plog/Log.h>

namespace cpv {
    enum class ButtonState {
        kButtonActive,
        kButtonInactive,
    };

    class OnSceenButton {
        // Attributes
    protected:
        int button_x_pos_ = 0;
        int button_y_pos_ = 0;
        int button_x_pos_end_ = 0;
        int button_y_pos_end_ = 0;
        std::string button_name_;
        std::string button_onscreen_text_;
        ButtonState buttonState_{ ButtonState::kButtonInactive };

    private:
        bool is_button_toggelable_ = false;

        // Methods
    protected:


    public:
        OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name);
        OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text);
        ~OnSceenButton();
        void SetButtonName(std::string buttonText);
        std::string GetButtonName();
        void SetOnScreenText(std::string text);
        std::string GetOnScreenText();
        void HighlightOnScreenText(bool flag);
        bool IsMousePointerOverButton(int mouse_x, int mouse_y);
        void ToggleButtonState();
        ButtonState GetButtonToggeledState();
        void DrawOutline(SDL_Renderer* renderer);
    };
}

#endif // CPV_OSB_H