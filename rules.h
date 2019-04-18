#ifndef RULES_H_INCLUDED
#define RULES_H_INCLUDED

#include "taslar.h"
#include "load.h"
#include "tools.h"
#include "konumlar(hash).h"

void game_start(struct hash_tablosu *,struct SDL_Surface *,struct surfacer );
void taslar_yap(struct hash_tablosu *);
void taslari_goster(struct hash_tablosu *,struct SDL_Surface *,struct surfacer );
void first_screen(struct SDL_Surface *,union SDL_Event,struct SDL_Surface *,TTF_Font *);

void game_start(struct hash_tablosu *htable,struct SDL_Surface *scr,struct surfacer as){
    static int i=0;
    while (i==0){
        taslar_yap(htable); i++;}
    taslari_goster(htable,scr,as);
}

void taslar_yap(struct hash_tablosu *htable){
    taslar sol_at(2);                                            taslar b_sag_at(18);
    taslar sol_kale(1);                                          taslar b_sag_kale(17);
    taslar sol_fil(3);                                           taslar b_sag_fil(19);
    taslar vezir(5);                                             taslar b_vezir(20);
    taslar sah(4);                                               taslar b_sah(21);
    taslar sag_fil(6);                                           taslar b_sol_fil(22);
    taslar sag_at(7);                                            taslar b_sol_at(23);
    taslar sag_kale(8);                                          taslar b_sol_kale(24);
    taslar s_piyon1(9);                                          taslar b_piyon1(25);
    taslar s_piyon2(10);                                         taslar b_piyon2(26);
    taslar s_piyon3(11);                                         taslar b_piyon3(27);
    taslar s_piyon4(12);                                         taslar b_piyon4(28);
    taslar s_piyon5(13);                                         taslar b_piyon5(29);
    taslar s_piyon6(14);                                         taslar b_piyon6(30);
    taslar s_piyon7(15);                                         taslar b_piyon7(31);
    taslar s_piyon8(16);                                         taslar b_piyon8(32);

    taslar_yerlestir(sol_at,htable);                             taslar_yerlestir(b_sag_at,htable);
    taslar_yerlestir(sol_kale,htable);                           taslar_yerlestir(b_sag_kale,htable);
    taslar_yerlestir(sol_fil,htable);                            taslar_yerlestir(b_sag_fil,htable);
    taslar_yerlestir(vezir,htable);                              taslar_yerlestir(b_vezir,htable);
    taslar_yerlestir(sah,htable);                                taslar_yerlestir(b_sah,htable);
    taslar_yerlestir(sag_fil,htable);                            taslar_yerlestir(b_sol_fil,htable);
    taslar_yerlestir(sag_at,htable);                             taslar_yerlestir(b_sol_at,htable);
    taslar_yerlestir(sag_kale,htable);                           taslar_yerlestir(b_sol_kale,htable);
    taslar_yerlestir(s_piyon1,htable);                           taslar_yerlestir(b_piyon1,htable);
    taslar_yerlestir(s_piyon2,htable);                           taslar_yerlestir(b_piyon2,htable);
    taslar_yerlestir(s_piyon3,htable);                           taslar_yerlestir(b_piyon3,htable);
    taslar_yerlestir(s_piyon4,htable);                           taslar_yerlestir(b_piyon4,htable);
    taslar_yerlestir(s_piyon5,htable);                           taslar_yerlestir(b_piyon5,htable);
    taslar_yerlestir(s_piyon6,htable);                           taslar_yerlestir(b_piyon6,htable);
    taslar_yerlestir(s_piyon7,htable);                           taslar_yerlestir(b_piyon7,htable);
    taslar_yerlestir(s_piyon8,htable);                           taslar_yerlestir(b_piyon8,htable);

    pixel_gir(htable);

}

void taslari_goster(struct hash_tablosu *hash_table,struct SDL_Surface *scr,struct surfacer as){
    int index;
    int anki_tas;
    int Ax_x,Ax_y;
    for (index=0;index<64;index++){
       anki_tas = (hash_table->tablo_basi+index)->tas_no;
       Ax_x = (hash_table->tablo_basi+index)->Tx;
       Ax_y = (hash_table->tablo_basi+index)->Ty;
       apply_surface(Ax_x,Ax_y,search_by_number(anki_tas,as),scr);
    }
}

void first_screen(struct SDL_Surface *screen,union SDL_Event event,struct SDL_Surface *bg){
    int x=0,y=0;
    SDL_Surface *click=NULL;
    SDL_Surface *message_start = NULL;
    SDL_Surface *message_quit=NULL;

    TTF_Font *font = NULL;
    click=load_image("menu_button.png");
    font = TTF_OpenFont( "font.ttf", 80 );
    SDL_Color textColor = { 250, 0, 0 };
    message_start = TTF_RenderText_Solid( font, "   BASLA  ", textColor );
    message_quit = TTF_RenderText_Solid( font, "   CIK  ", textColor );

    bool first=true;
    apply_surface(0,0,bg,screen);
    apply_surface(300,200,message_start,screen);
    apply_surface(200,200,click,screen);
    apply_surface(200,400,click,screen);
    apply_surface(300,400,message_quit,screen);
    while (first){
        if( SDL_PollEvent( &event ) ){
            if( event.type == SDL_MOUSEBUTTONDOWN ){
                 if( event.button.button == SDL_BUTTON_LEFT ){
                     x = event.button.x;
                     y = event.button.y;

                     if( ( x > 210 ) && ( x < 800 ) && ( y > 213 ) && ( y < 315 ) ){
                        first=false;
                        SDL_FreeSurface(click);
                        SDL_FreeSurface(message_quit);
                        SDL_FreeSurface(message_start);
                     }

                     if( ( x > 210 ) && ( x < 800 ) && ( y > 413 ) && ( y < 515 ) )
                        SDL_Quit();
                 }
            }
        }
       SDL_Flip(screen);
    }
}

#endif // RULES_H_INCLUDED
