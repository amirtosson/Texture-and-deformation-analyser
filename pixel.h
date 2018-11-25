#ifndef PIXEL_H
#define PIXEL_H
#include <vector>

typedef struct  Pixel {
    Pixel():counts(0),eng_mode(0){
        hits_amp.clear();
    }
    int counts;
    std::vector<int> hits_amp;
    int eng_mode;
}pixelall;
extern pixelall pixel;


#endif // PIXEL_H
