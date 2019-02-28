#ifndef _MIXPARAMATERS_H_
#define _MIXPARAMATERS_H_

class MixParameters
{
public:
    typedef enum enum_mix_method
    {
        OVERWRITE,
        CHANNEL_ADD,
        CHANNEL_MEAN,
        CHANNEL_DIFF
    } mix_method;
    
    float opacity = 1;
    mix_method method = OVERWRITE;

};

#endif