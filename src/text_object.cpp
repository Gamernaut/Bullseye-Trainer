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


#include "text_object.h"

using namespace cpv;

TextObject::TextObject(std::string font_name, int font_size) {
    PLOG_VERBOSE << "TextObject constructor called";

    font_ = TTF_OpenFont(font_name.c_str(), font_size);
    if (!font_) {
        PLOG_ERROR << "Error opening font " << font_name << SDL_GetError() << " in TextObject::TextObject()";
        return;
    }
}


TextObject::~TextObject() {
    PLOG_VERBOSE << "TextObject destructor called";

    TTF_CloseFont(font_);

//    SDL_FreeSurface(text_surface_);
//    SDL_DestroyTexture(text_texture_);
}


void TextObject::SetPosition(int x_position, int y_position) {
    
    PLOG_VERBOSE << "TextObject destructor called";

    draw_position_.x = x_position;
    draw_position_.y = y_position;
}


void TextObject::Draw(SDL_Renderer* renderer, std::string text_to_display, SDL_Color text_colour, int x_position, int y_position) {
    PLOG_VERBOSE << "TextObject::Draw() called";

    text_surface_ = TTF_RenderText_Blended(font_, text_to_display.c_str(), text_colour);
    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    SDL_Rect textDestinationRectangle = { x_position, y_position , text_surface_->w, text_surface_->h };

    SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);

    SDL_FreeSurface(text_surface_);
    SDL_DestroyTexture(text_texture_);
}


// Invert the text so the background is coloured but the text is the colour of the background
void TextObject::HighlightedDraw(SDL_Renderer* renderer, std::string text, SDL_Color fg_colour, SDL_Color bg_colour, int x_position, int y_position) {
    PLOG_VERBOSE << "TextObject::HighlightedDraw() called";

    text_surface_ = TTF_RenderText_Shaded(font_, text.c_str(), fg_colour, bg_colour);
    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    SDL_Rect textDestinationRectangle = { x_position, y_position, text_surface_->w, text_surface_->h };

    SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);

    SDL_FreeSurface(text_surface_);
    SDL_DestroyTexture(text_texture_);
}


// Use the Y position but center in the X
void TextObject::DrawCenteredInWindow(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int y_position) {
    PLOG_VERBOSE << "TextObject::DrawCenteredText() called";

    text_surface_ = TTF_RenderText_Blended(font_, text.c_str(), text_colour);
    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    SDL_Rect textDestinationRectangle = { (kWindowWidth / 2) - (text_surface_->w / 2) , y_position, text_surface_->w , text_surface_->h };

    SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);

    SDL_FreeSurface(text_surface_);
    SDL_DestroyTexture(text_texture_);
}

// Draws the text with the point passed in as the center of the text (goes left and right of that point as above and below that point)
void TextObject::DrawCenteredAt(SDL_Renderer* renderer, std::string text, SDL_Color text_colour, int x_position, int y_position) {
    PLOG_VERBOSE << "TextObject::DrawCenteredText() called";

    text_surface_ = TTF_RenderText_Blended(font_, text.c_str(), text_colour);
    text_texture_ = SDL_CreateTextureFromSurface(renderer, text_surface_);

    SDL_Rect textDestinationRectangle = { x_position - (text_surface_->w / 2), y_position - (text_surface_->h / 2), text_surface_->w , text_surface_->h };

    SDL_RenderCopy(renderer, text_texture_, NULL, &textDestinationRectangle);

    SDL_FreeSurface(text_surface_);
    SDL_DestroyTexture(text_texture_);
}
