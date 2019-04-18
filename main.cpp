#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_mixer.h"
#include <string>
#include "time.h"
#include "taslar.h"
#include "load.h"
#include "rules.h"
#include "konumlar(hash).h"
#include "handle.h"

const int SCREEN_WIDTH = 780;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP = 32;

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *tahta = NULL;
SDL_Surface *dot = NULL;
SDL_Surface *bg=NULL;
TTF_Font *font=NULL;
SDL_Event event;

bool init(){
    SDL_Init( SDL_INIT_EVERYTHING );
    TTF_Init();
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 );
    SDL_WM_SetCaption( "Satranc", NULL );
    return true;
}

bool load_files(){

    background = load_image( "bg.png" );
    tahta = load_image ("tahta.png");
    dot = load_image("dot.png");
    font = TTF_OpenFont("font.ttf",20);
    return true;
}

int main( int argc, char* args[] )
{
    bool quit = false;
    init();  load_files();

    struct hash_tablosu *htable;
    initialize_hash_table(&htable,7,64);

    bool click_counter=false,*counter,sira=false,*yeni;
    bool yeni0=false,*yeni1;
    yeni1=&yeni0;
    counter=&click_counter;
    yeni=&sira;

    struct dugum *eski=NULL;
    struct surfacer as;
    as=memory_load();

    first_screen(screen,event,background);
    apply_surface(29,4,tahta,screen);

    while( quit == false ){
        if( SDL_PollEvent( &event ) ){
            handle_events(event,dot,screen,counter,tahta,htable,yeni,&eski,yeni1,as,font,background);
            if( event.type == SDL_QUIT ){
                quit = true;
            }
        }
        game_start(htable,screen,as);
        SDL_Flip(screen);
    }
    return 0;
}
