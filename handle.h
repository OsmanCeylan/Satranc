#ifndef HANDLE_H_INCLUDED
#define HANDLE_H_INCLUDED

#include "tools.h"
#include "move_staffs.h"

bool switch_counter(bool *counter){
    if (*counter == false)
        *counter = true;
    else
        *counter = false;
}

void handle_events(union SDL_Event event,struct SDL_Surface *dot,struct SDL_Surface *screen,bool *click_counter,struct SDL_Surface *tahta
                   ,struct hash_tablosu *htable,bool *yeni,struct dugum **eski,bool *yeni1,struct surfacer as,TTF_Font *font,struct SDL_Surface *background){
    int x=0,y=0;
    curr_surface tmp;
    SDL_Surface *seconds=NULL;
    SDL_Color textColor = { 250, 0, 0 };

    Mix_Chunk *low = NULL;
    Mix_Chunk *medium=NULL;
    Mix_Chunk *high=NULL;

    low = Mix_LoadWAV("low.wav");
    medium = Mix_LoadWAV("medium.wav");
    high = Mix_LoadWAV("high.wav");

    if( event.type == SDL_MOUSEBUTTONDOWN ){

        if (event.button.button == SDL_BUTTON_RIGHT){
            seconds = TTF_RenderText_Solid( font, "Temizlendi" , textColor );

            apply_surface(0,650,background,screen);
            apply_surface(29,4,tahta,screen);
            apply_surface(300,650,seconds, screen );

            (*yeni)=false;(*yeni1)=false;
        }

        if( event.button.button == SDL_BUTTON_LEFT && (*yeni)==false)
        {
            Mix_PlayChannel( -1, low, 0);
            x = event.button.x;
            y = event.button.y;
            tmp = search_by_surface(x,y,htable);
            apply_surface(26,4,tahta,screen);
            get_moving(tmp.number,htable,dot,screen,*(click_counter),eski);

            dugum_yazdir(*eski);
            if (tmp.number<17 && (*click_counter)==false) {(*yeni)=false; (*yeni1)=false;
                 seconds = TTF_RenderText_Solid( font, "El Beyazda" , textColor );
                 apply_surface(0,650,background,screen);
                 apply_surface(300,650,seconds, screen );
             }

            else if (tmp.number>=17 && (*click_counter)==true) {
                 (*yeni)=false; (*yeni1)=false;
                 seconds = TTF_RenderText_Solid( font, "El Siyahta" , textColor );
                 apply_surface(0,650,background,screen);
                 apply_surface(300,650,seconds, screen );
                 }
            else{
                if ((htable->tablo_basi+tmp.index)->tas_no == 0) {
                    (*yeni)=false; (*yeni1)=false;
                    seconds = TTF_RenderText_Solid( font, "Burada Tas Yok" , textColor );
                    apply_surface(0,650,background,screen);
                    apply_surface(300,650,seconds, screen );
                 }

                 if ((*eski)->icerik==tmp.number) {
                      seconds = TTF_RenderText_Solid( font, "Tasin Oynayabilecek Yeri Yok Baska Tas Dene" , textColor );
                      apply_surface(0,650,background,screen);
                      apply_surface(30,650,seconds, screen ); (*yeni)=false;
                 }

                 if ((htable->tablo_basi+tmp.index)->tas_no != 0 && (*eski)->icerik!=tmp.number){
                     (*yeni)=true; seconds = TTF_RenderText_Solid( font, "  Hareket Icim 'm' ye Tiklayiniz", textColor );
                     apply_surface(0,650,background,screen);
                     apply_surface(100,650,seconds, screen );
                 }
            }
        }

        if( event.button.button == SDL_BUTTON_LEFT && (*yeni)==true && (*yeni1)==true)
        {
            bool ev=true;

            struct dugum *yedek=NULL;
            yedek=(*eski);

            x = event.button.x;
            y = event.button.y;
            tmp = search_by_surface(x,y,htable);
            Mix_PlayChannel( -1, high, 0);

            while(yedek){
                if (yedek->link==NULL) break;
                if ((yedek)->icerik==tmp.index){
                    ev=false;
                }
                yedek=yedek->link;
            }

            if (ev==false){
                bool check=false;
                check=check_options(htable,*(click_counter));

                if (check==false){
                    move_tas(tmp.index,yedek->icerik,htable,screen,as,tahta);
                    seconds = TTF_RenderText_Solid( font, "Hareket Tamamlandi" , textColor );
                    apply_surface(0,650,background,screen);
                    apply_surface(300,650,seconds, screen );
                    switch_counter(click_counter);
                    (*yeni)=false; (*yeni1)=false;
                }

                if (check==true){
                    seconds = TTF_RenderText_Solid( font, "Sah Tehlikede!Hareket tamamlanamadi" , textColor );
                    apply_surface(0,650,background,screen);
                    apply_surface(170,650,seconds, screen );
                    check=sahte_move_tas(tmp.index,yedek->icerik,htable,as,*(click_counter));
                    if (check==false){
                        move_tas(tmp.index,yedek->icerik,htable,screen,as,tahta);
                        seconds = TTF_RenderText_Solid( font, "Hareket Tamamlandi" , textColor );
                        apply_surface(0,650,background,screen);
                        apply_surface(300,650,seconds, screen );
                        switch_counter(click_counter);
                    }
                    (*yeni)=false; (*yeni1)=false;
                }
            }
        }
    }

    if (event.type == (SDL_KEYUP | SDL_KEYDOWN)){
        if(event.key.state=SDLK_m && (*yeni)==true){
            seconds = TTF_RenderText_Solid( font, " 'm' Ye Tikladiniz " , textColor );
            Mix_PlayChannel( -1, medium, 0);
            apply_surface(0,650,background,screen);
            apply_surface(300,650,seconds, screen );

            (*yeni1)=true;
        }
    }
}

#endif // HANDLE_H_INCLUDED
