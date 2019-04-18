#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "taslar.h"
#include "load.h"
#include "konumlar(hash).h"
#include "move_staffs.h"

struct SDL_Surface *search_by_number(int ,struct surfacer );
void move_on_surface(struct dugum *);
bool check_options(struct hash_tablosu *,bool );

struct curr_surface{
   int x;
   int y;
   int index;
   int number;
};

SDL_Surface *search_by_number(int numara,struct surfacer as){

    SDL_Surface *tmp=NULL;
  if (numara<=16){
    if (numara==1 || numara==8) tmp = as.s_kale;
    if (numara==2 || numara==7) tmp = as.s_at;
    if (numara==3 || numara==6) tmp = as.s_fil;
    if (numara==5) tmp = as.s_vezir;
    if (numara==4) tmp = as.s_sah;
    if (numara==9  || numara==10 || numara==11 || numara==12 || numara==13 || numara==14 || numara==15 || numara==16 )
        tmp = as.s_piyon;
    return tmp;
}
  else if (numara>=17){
    if (numara == 17 || numara==24) tmp = as.b_kale;
    if (numara == 18 || numara==23) tmp = as.b_at;
    if (numara == 19 || numara==22) tmp = as.b_fil;
    if (numara == 20) tmp = as.b_vezir;
    if (numara == 21) tmp = as.b_sah;
    if (numara==25  || numara==26 || numara==27 || numara==28 || numara==29 || numara==30 || numara==31 || numara==32 )
        tmp = as.b_piyon;
    return tmp;
}
  else
    return NULL;
}

struct curr_surface search_by_surface(int x,int y,struct hash_tablosu *htable){
    int inx;
    curr_surface arama;

    for(inx=0;inx<htable->tablo_uzunlugu;inx++){
        arama.x = (htable->tablo_basi+inx)->Tx;
        arama.y = (htable->tablo_basi+inx)->Ty;
        arama.number = (htable->tablo_basi+inx)->tas_no;
        arama.index=inx;

        if (arama.x<x && x<arama.x+93 && arama.y<y && y<arama.y+80) break;
    }

    return arama;
}


bool search_by_dugum(struct dugum **ilk,int icerik){
    while (*ilk){
        if (icerik==(*ilk)->icerik)
            return true;
        (*ilk)=(*ilk)->link;
    }
    return false;
}

bool check_options(struct hash_tablosu *htable,bool counter){
    int i,b_sah_konumu=-1;
    struct dugum *keyler=NULL;
    struct dugum *kontrol=NULL;

    if (counter==false){
        for (i=1;i<17;i++){
            get_moving(i,htable,NULL,NULL,true,&keyler);

            while (keyler){
                if (keyler->link==NULL) break;
                dugume_ekle(keyler->icerik,&kontrol);
                keyler=keyler->link;
            }
        }

        for (i=0;i<64;i++){
            if (((htable->tablo_basi+i)->tas_no)==20){
               b_sah_konumu=i;
            }
        }

        if (counter==false && dugum_arama(b_sah_konumu,kontrol)==true){
            return true;
        }
        return false;
    }

    if (counter==true){
        for (i=17;i<33;i++){
            get_moving(i,htable,NULL,NULL,false,&keyler);

            while (keyler){
                if (keyler->link==NULL) break;
                dugume_ekle(keyler->icerik,&kontrol);
                keyler=keyler->link;
            }
        }

        for (i=0;i<64;i++){
            if (((htable->tablo_basi+i)->tas_no)==5)
               b_sah_konumu=i;
        }

        if (dugum_arama(b_sah_konumu,kontrol)==true){
            return true;
        }
        return false;
    }

}

bool sahte_move_tas(int istenilen_konum,int tas_numara,struct hash_tablosu *htable,struct surfacer as,bool click){
    int i;
    bool check;
    struct hash_tablosu *ikinci;
    initialize_hash_table(&ikinci,7,64);

    ikinci->tablo_uzunlugu=htable->tablo_uzunlugu;
    ikinci->multiplier=htable->multiplier;
    for (i=0;i<64;i++){
        ((ikinci->tablo_basi+i)->tas_no)=((htable->tablo_basi+i)->tas_no);
        ((ikinci->tablo_basi+i)->Tx)=((htable->tablo_basi+i)->Ty);
        ((ikinci->tablo_basi+i)->Ty)=((htable->tablo_basi+i)->Tx);
    }

    for (i=0;i<64;i++){
        if (tas_numara==((ikinci->tablo_basi+i)->tas_no))
            ((ikinci->tablo_basi+i)->tas_no)=0;
    }
    ((ikinci->tablo_basi+istenilen_konum)->tas_no)=tas_numara;

    print_hash_table(ikinci);

    check=check_options(ikinci,(click));
    return check;
}

#endif // TOOLS_H_INCLUDED
