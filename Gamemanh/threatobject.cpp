#include "threatobject.h"


Threatsobject::Threatsobject()
{
    width_frame_=0;
    height_frame_=0;
    x_val_=0.0;
    y_val_=0.0;
    x_pos_=0.0;
    y_pos=0.0;
    on_ground_=0;
    come_back_time_=0;
    frame_=0;
}
Threatsobject::~Threatsobject()
{

}
bool Threatsobject::LoadImg(std::string path,SDL_Renderer* screen)
{

    bool ret= BaseObject::LoadImg(path,screen);
if(ret==true)
{
  width_frame_=rect_.w/THREAT_FRAME_NUM;
  height_frame_=rect_.h;


}
return ret;

}
void Threatsobject::set_clips()
{
     if(width_frame_>0&&height_frame_>0)
    {
       frame_clip_[0].x=0;
       frame_clip_[0].y=0;
       frame_clip_[0].w=width_frame_;
       frame_clip_[0].h=height_frame_;

        frame_clip_[1].x=width_frame_;
       frame_clip_[1].y=0;
       frame_clip_[1].w=width_frame_;
       frame_clip_[1].h=height_frame_;

        frame_clip_[2].x=2*width_frame_;
       frame_clip_[2].y=0;
       frame_clip_[2].w=width_frame_;
       frame_clip_[2].h=height_frame_;

        frame_clip_[3].x=3*width_frame_;
       frame_clip_[3].y=0;
       frame_clip_[3].w=width_frame_;
       frame_clip_[3].h=height_frame_;

        frame_clip_[4].x=4*width_frame_;
       frame_clip_[4].y=0;
       frame_clip_[4].w=width_frame_;
       frame_clip_[4].h=height_frame_;

        frame_clip_[5].x=5*width_frame_;
       frame_clip_[5].y=0;
       frame_clip_[5].w=width_frame_;
       frame_clip_[5].h=height_frame_;

        frame_clip_[6].x=6*width_frame_;
       frame_clip_[6].y=0;
       frame_clip_[6].w=width_frame_;
       frame_clip_[6].h=height_frame_;

        frame_clip_[7].x=7*width_frame_;
       frame_clip_[7].y=0;
       frame_clip_[7].w=width_frame_;
       frame_clip_[7].h=height_frame_;




    }
}
void Threatsobject::Show(SDL_Renderer* des)
{
    if(come_back_time_==0)
    {
        rect_.x= x_pos_- map_x_;

        rect_.y=y_pos_ - map_y_;
        frame_++;
        if(frame_>=8)
        {
            frame_=0;
        }
        SDL_Rect* currentClip =&frame_clip_[frame_];
        SDL_Rect renderQuad={rect_.x,rect_.y,width_frame_,height_frame_};
        SDL_RenderCopy(des,p_object_,current_clip,&renderQuad);
    }
}
void Threatsobject::DoPlayer(Map& gmap)
{
    if(come_back_time_==0)
    {
        x_val_=0;
        y_val_+=THREAT_GRAVITY_SPEED;
    }
}
