#include "MFD.h"

using namespace cpv;

MFD::MFD(SDL_Renderer* sdl_renderer, int mfd_top_edge, int mfd_left_edge, int mfd_height, int mfd_width)
{
    PLOG_VERBOSE << "MFD constructor called";

    // Create MFD frame and button here 
    mfd_frame_ = std::make_unique<ImageObject>(sdl_renderer, kMfdFrameFileName);
    if (!mfd_frame_) {
        PLOG_ERROR << "HSD constructor: Could not create mfd_frame_";
    }
}

MFD::~MFD()
{
    PLOG_VERBOSE << "MFD destructor called";
}

Coordinate MFD::GetCenterPoint(void)
{
    PLOG_VERBOSE << "MFD::GetCenterPoint() called";
    return Coordinate();
}

void MFD::DrawMFDFrame(SDL_Renderer* sdl_renderer)
{
    PLOG_VERBOSE << "MFD::Draw() called";

    mfd_frame_->Draw(sdl_renderer);
}
