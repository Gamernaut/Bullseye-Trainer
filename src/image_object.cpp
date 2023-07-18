///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	June 2022
//
//	Purpose:	
// 
//   Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////

#include "image_object.h"

using namespace cpv;

ImageObject::ImageObject(SDL_Renderer* renderer, std::string filename) {
    PLOG_VERBOSE << "ImageObject constructor(SDL_Renderer* renderer, std::string filename) called";
    // Store parameters in object
    name_ = filename;

    image_surface_ = IMG_Load(filename.c_str());
    if (!image_surface_) {
        PLOG_ERROR << "ImageObject::ImageObject(): Couldn't load image " << filename;
        return;
    }
    image_texture_ = SDL_CreateTextureFromSurface(renderer, image_surface_);
    if (!image_texture_) {
        PLOG_ERROR << "ImageObject::ImageObject(): Couldn't create texture for " << filename << " SDL returned error: " << SDL_GetError();
        return;
    }

    image_width_ = image_surface_->w;
    image_height_ = image_surface_->h;

    // Default the position to the center of the MFD drawing area, should help with debugging because if 
    // SetUIPosition() is not called it will appear in the middle of the MFD.
    image_center_.x = kCenterMfdDrawArea.x;
    image_center_.y = kCenterMfdDrawArea.y;
}

ImageObject::~ImageObject()
{
    PLOG_VERBOSE << "ImageObject destructor called";

    SDL_FreeSurface(image_surface_);
    SDL_DestroyTexture(image_texture_);
}

void ImageObject::Draw(SDL_Renderer* renderer)
{
    PLOG_VERBOSE << "ImageObject::Draw() called";

    if (IsVisable()) {

        // Determine the top left corner of this image for the draw routine
        draw_position_.x = image_center_.x - (image_width_ / 2);
        draw_position_.y = image_center_.y - (image_height_ / 2);

        SDL_Rect imageDestinationRectangle = { draw_position_.x, draw_position_.y, image_width_, image_height_ };

        int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
        if (renderSuccess != 0) {
            PLOG_ERROR << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::Draw()";
        }

    }
}


void ImageObject::DrawArc(SDL_Renderer* renderer, int user_bearing_guess) {
    PLOG_VERBOSE << "ImageObject::DrawArc() called";

    // TODO: Implement DrawArc
    // Need to center the middle of the bottom of the image in the center of the aircraft.
    // then rotate the image to match the bearing the user selected with the center of the
    // pie slice aligning with the point the user clicked on.

    // Non matrix maths for rotating around an arbitary point https://academo.org/demos/rotation-about-point/

    int top_left_corner_x = 359 - (image_width_ / 2);
    int top_left_corner_y = 667 - (image_height_ / 2);

    SDL_Rect imageDestinationRectangle = { top_left_corner_x, top_left_corner_y, image_width_, image_height_ };

    RotateToFinalAngle(user_bearing_guess);

    int renderSuccess = SDL_RenderCopyEx(renderer, image_texture_, NULL, &imageDestinationRectangle, rotation_angle_, NULL, SDL_FLIP_NONE);
    if (renderSuccess != 0) {
        std::cout << "SDL_RenderCopy returned " << SDL_GetError() << "in ImageObject::Draw()" << std::endl;
    }
}

void ImageObject::DrawArc2(SDL_Renderer* renderer, int user_bearing_guess, Coordinate aircraft_center) {
    PLOG_VERBOSE << "ImageObject::DrawArc2() called";

    // TODO: Implement DrawArc2
}

void ImageObject::SetRandomPosition() {
    PLOG_VERBOSE << "ImageObject::SetRandomPosition() called";

    // TODO: Implement SetRandomPosition
}

// Returns the center of the Image as this is used in distance and bearing calculations
Coordinate ImageObject::GetPosition() const {
    PLOG_VERBOSE << "ImageObject::GetPosition() called";

    return image_center_;
}

// Sets the center of the Image as this is used in distance and bearing calculations
void ImageObject::SetUIPosition(Coordinate new_position) {
    PLOG_VERBOSE << "ImageObject::SetPositionUsingCenteredCoords() called";

    image_center_.x = new_position.x;
    image_center_.y = new_position.y;
}

// Need 2 versions of the set angle method. 
// Both versions sets the rotation angle in degrees so the SDL library renders it rotated during the draw function.
// The draw function rotates the image clockwise by the number of degrees.
// 
// This function sets the rotation angle in a clockwise direction and is used when the image needs to be turned clockwise
// Used mainly for the bearing pointer
void ImageObject::RotateToFinalAngle(double angleInDegrees) {
    PLOG_VERBOSE << "ImageObject::RotateToFinalAngle() called";

    rotation_angle_ = angleInDegrees;
}

// This function sets the rotation angle in an anti-clockwise direction by making the angle negative
// Used mainly for the HSD rings
void ImageObject::RotateToFinalHeading(double angleInDegrees) {
    PLOG_VERBOSE << "ImageObject::RotateToFinalAngle() called";

    rotation_angle_ = -angleInDegrees;
}

std::string ImageObject::GetObjectName() const {
    PLOG_VERBOSE << "ImageObject::GetObjectName() called";
    return name_;
}

bool ImageObject::ValidPosition(int x, int y) {
    PLOG_VERBOSE << "ImageObject::ValidPosition() called";

    // TODO: Implement ValidPosition
    return false;      // Update to actual code, this may give unexpected behaviour
}

int ImageObject::GetWidth() const {
    PLOG_VERBOSE << "ImageObject::GetWidth() called";

    return image_width_;
}

int ImageObject::GetHeight() const {
    PLOG_VERBOSE << "ImageObject::GetHeight() called";

    return image_height_;
}

bool ImageObject::IsVisable() const {
    PLOG_VERBOSE << "ImageObject::IsVisable() called";

    return image_is_visable_;
}

void ImageObject::SetVisibility(bool flag) {
    PLOG_VERBOSE << "ImageObject::SetVisibility() called";

    image_is_visable_ = flag;
}
