#include "threatobject.h"


Threatsobject::Threatsobject()
{
    width_frame_=0;
    height_frame_=0;
    x_val_=0.0;
    y_val_=0.0;
    x_pos_=0.0;
    y_pos_=0.0;
    on_ground_=0;
    come_back_time_=0;
    frame_=0;
    animation_a_=0;
    animation_b_=0;
    input_type_.left_=0;
    type_move_=STATIC_THREAT;
}
Threatsobject::~Threatsobject()
{

}
bool Threatsobject::LoadImg(std::string path,SDL_Renderer* screen)
{

    bool ret= BaseObject::LoadImg(path,screen);
if(ret)
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
        SDL_RenderCopy(des,p_object_,currentClip,&renderQuad);
    }
}
void Threatsobject::DoPlayer(Map& gMap)
{
    if(come_back_time_==0)
    {
        x_val_=0;
        y_val_+=THREAT_GRAVITY_SPEED;
        if(y_val_>=THREAT_MAX_FALL_SPEED)
        {
            y_val_=THREAT_MAX_FALL_SPEED;
        }
        if(input_type_.left_==1)
        {
            x_val_-=THREAT_SPEED;

        }
        else if(input_type_.right_==1)
        {
            x_val_+=THREAT_SPEED;
        }
        CheckToMap(gMap);
    }
    else if(come_back_time_>0)
    {
        come_back_time_--;
        if(come_back_time_==0)
        {
          InitThreats();

        }
    }
}

void Threatsobject::InitThreats()
{

  x_val_=0;
            y_val_=0;
            if(x_pos_>256)
            {
                x_pos_-=256;
                animation_a_-=256;
                animation_b_-=256;
            }
            else
            {
                x_pos_=0;
            }
            y_pos_=0;
            come_back_time_=0;


}
void Threatsobject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    int height_min=height_frame_ <TITLE_SIZE ? height_frame_: TITLE_SIZE;

    x1=(x_pos_+x_val_)/TITLE_SIZE;
    x2=(x_pos_+x_val_+width_frame_-1)/TITLE_SIZE;

    y1=(y_pos_)/TITLE_SIZE;
    y2=(y_pos_+height_min -1)/TITLE_SIZE;


    if(x1>=0 && x2<MAX_MAP_X && y1>=0&&y2<MAX_MAP_Y)
    {
        if(x_val_ >0)
        {

            int val1=map_data.title[y1][x2];
            int val2=map_data.title[y2][x2];



            if((val1!= BLANK_TILE&&val1!=STATE_MONEY)|| (val2!= BLANK_TILE&&val2!=STATE_MONEY))
            {
                x_pos_=x2*TITLE_SIZE;
                x_pos_-= width_frame_+1;
                x_val_=0;
            }

        }
        else if(x_val_<0)
        {
            int val1= map_data.title[y1][x1];
            int val2=map_data.title[y2][x1];
            if(val1!= BLANK_TILE&&val1!=STATE_MONEY||val2 != BLANK_TILE&&val2!=STATE_MONEY)
            {
                x_pos_=(x1+1)*TITLE_SIZE;
                x_val_=0;
            }
        }
    }

     int width_min= width_frame_ <TITLE_SIZE ?width_frame_:TITLE_SIZE;
     x1=(x_pos_)/TITLE_SIZE;
     x2=(x_pos_+width_min)/TITLE_SIZE;

     y1= (y_pos_+ y_val_)/TITLE_SIZE;
     y2= (y_pos_+ y_val_ +height_frame_-1)/TITLE_SIZE;
        if(x1>=0 && x2<MAX_MAP_X && y1>=0&&y2<MAX_MAP_Y)
        {
            if(y_val_>0)
            {
                 int val1=map_data.title[y2][x1];
                 int val2=map_data.title[y2][x2];


                      if(val1!= BLANK_TILE&&val1!=STATE_MONEY|| val2!= BLANK_TILE&&val2!=STATE_MONEY)
                  {
                      y_pos_=y2*TITLE_SIZE;
                      y_pos_-=(height_frame_+1);
                      y_val_=0;
                      on_ground_= true;
                  }



            }
            else if(y_val_<0)
            {
                 int val1=map_data.title[y1][x1];
                 int val2=map_data.title[y1][x2];


                      if(val1!= BLANK_TILE&&val1!=STATE_MONEY|| val2!= BLANK_TILE&&val2!=STATE_MONEY)
                 {
                     y_pos_=(y1+1)*TITLE_SIZE;
                     y_val_=0;
                 }



            }
        }


        x_pos_+=x_val_;
        y_pos_+=y_val_;
        if(x_pos_<0)
        {
            x_pos_=0;
        }
        else if(x_pos_+width_frame_>map_data.max_x_)
        {
            x_pos_=map_data.max_x_-width_frame_-1;
        }
        if(y_pos_>map_data.max_y_)
        {
            come_back_time_=60;
        }
}
void Threatsobject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move_==STATIC_THREAT)
    {
        ;
    }
    else
    {
        if(on_ground_=true)
        {
            if(x_pos_>animation_a_)
            {
                input_type_.left_=1;
                input_type_.right_=0;
                LoadImg("img//threat_left.png",screen);
            }
            else if(x_pos_<animation_b_)
            {
                input_type_.left_=0;
                input_type_.right_=1;
                LoadImg("img//threat_right.png",screen);
            }

        }
        else
        {
            if(input_type_.left_=1)
            {
                LoadImg("img//threat_left.png",screen);
            }
        }

    }
}
