#include "on_screen_button.h"

using namespace cpv;

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name)
{
    PLOG_VERBOSE << "OnSceenButton constructor called";
}

OnSceenButton::OnSceenButton(int xPos, int yPos, int xPosEnd, int yPosEnd, bool toggelable, std::string button_name, std::string onscreen_text)
{
    PLOG_VERBOSE << "OnSceenButton destructor called";
}

OnSceenButton::~OnSceenButton()
{
    PLOG_VERBOSE << "OnSceenButton::Draw() called";
}

void OnSceenButton::SetButtonName(std::string buttonText)
{
    PLOG_VERBOSE << "OnSceenButton::SetButtonName() called";
}

std::string OnSceenButton::GetButtonName()
{
    PLOG_VERBOSE << "OnSceenButton::GetButtonName() called";
    return std::string();
}

void OnSceenButton::SetOnScreenText(std::string text)
{
    PLOG_VERBOSE << "OnSceenButton::SetOnScreenText() called";
}

std::string OnSceenButton::GetOnScreenText()
{
    PLOG_VERBOSE << "OnSceenButton::GetOnScreenText() called";
    return std::string();
}

void OnSceenButton::HighlightOnScreenText(bool flag)
{
    PLOG_VERBOSE << "OnSceenButton::HighlightOnScreenText() called";
}

bool OnSceenButton::IsMousePointerOverButton(int mouse_x, int mouse_y)
{
    PLOG_VERBOSE << "OnSceenButton::IsMousePointerOverButton() called";
    return false;
}

void OnSceenButton::ToggleButtonState()
{
    PLOG_VERBOSE << "OnSceenButton::ToggleButtonState() called";
}

ButtonState OnSceenButton::GetButtonToggeledState()
{
    PLOG_VERBOSE << "OnSceenButton::GetButtonToggeledState() called";
    return ButtonState();
}

void OnSceenButton::DrawOutline(SDL_Renderer* renderer)
{
    PLOG_VERBOSE << "OnSceenButton::DrawOutline() called";
}
