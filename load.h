#ifndef LOAD_H_INCLUDED
#define LOAD_H_INCLUDED

#include "SDL/SDL.h"


SDL_Surface *load_image(std::string filename ){
    SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){

        optimizedImage = SDL_DisplayFormatAlpha( loadedImage );
        SDL_FreeSurface( loadedImage );

        Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );
        SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );

    }
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}

struct surfacer{
    SDL_Surface *s_kale;        SDL_Surface *b_kale;
    SDL_Surface *s_at;          SDL_Surface *b_at;
    SDL_Surface *s_vezir;       SDL_Surface *b_vezir;
    SDL_Surface *s_sah;         SDL_Surface *b_sah;
    SDL_Surface *s_fil;         SDL_Surface *b_fil;
    SDL_Surface *s_piyon;       SDL_Surface *b_piyon;
};

struct surfacer memory_load(){

    surfacer yeni;
    yeni.s_kale=load_image("s_kale.png");
    yeni.s_at=load_image("s_at.png");
    yeni.s_fil=load_image("s_fil.png");
    yeni.s_vezir=load_image("s_vezir.png");
    yeni.s_sah=load_image("s_sah.png");
    yeni.s_piyon=load_image("s_piyon.png");
    yeni.b_kale=load_image("b_kale.png");
    yeni.b_at=load_image("b_at.png");
    yeni.b_fil=load_image("b_fil.png");
    yeni.b_vezir=load_image("b_vezir.png");
    yeni.b_sah=load_image("b_sah.png");
    yeni.b_piyon=load_image("b_piyon.png");
    return yeni;
}


#endif // LOAD_H_INCLUDED
