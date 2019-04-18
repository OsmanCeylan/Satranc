#ifndef MOVE_STAFFS_H_INCLUDED
#define MOVE_STAFFS_H_INCLUDED

#include "tools.h"
#include "taslar.h"

int get_moving(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,bool ,struct dugum **);
void kale_move(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,struct dugum **);
void draw(struct dugum *,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *);
void at_move(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,struct dugum **);
void piyon_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,int ,struct dugum **);
void fil_move(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,struct dugum **);
void vezir_move(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,struct dugum **);
void kral_move(int ,struct hash_tablosu *,struct SDL_Surface *,struct SDL_Surface *,struct dugum **);
void end_game(struct SDL_Surface *,int);

bool enemy_char(int number,int other){
    if (number>16 && other>16)
        return false;
    if (number<17 && other<17)
        return false;
    if (number>16 && other<17)
        return true;
    if (number<17 && other>16)
        return true;
}

int get_moving(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,bool renk,struct dugum **eski){
    if (renk==true){
       if (number==1 || number==8 )                                  kale_move(number,htable,dot,screen,eski);
       else if (number==2 || number==7 )                             at_move(number,htable,dot,screen,eski);
       else if (number>=9 && number<=16)                             piyon_move(number,htable,dot,screen,0,eski);
       else if (number==3 || number==6 )                             fil_move(number,htable,dot,screen,eski);
       else if (number==5)                                           vezir_move(number,htable,dot,screen,eski);
       else if (number==4)                                           kral_move(number,htable,dot,screen,eski);
    }

   if (renk==false){
        if (number==17 || number==24)                              kale_move(number,htable,dot,screen,eski);
        else if (number==18 || number==23)                         at_move(number,htable,dot,screen,eski);
        else if (number>=25 && number<=32)                         piyon_move(number,htable,dot,screen,1,eski);
        else if (number==22 || number==19)                         fil_move(number,htable,dot,screen,eski);
        else if (number==21)                                       vezir_move(number,htable,dot,screen,eski);
        else if (number==20)                                       kral_move(number,htable,dot,screen,eski);
    }
 }

void kale_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,struct dugum **eski){
    int index,i;
    int konum_negatif,konum_pozitif,konum;
    bool enemy;
    struct dugum *move_liste = NULL;

    for(index=0;index<htable->tablo_uzunlugu;index++){
        if (number == ((htable->tablo_basi+index)->tas_no)){
            konum_negatif = index;
        }
    }

    konum_pozitif=konum_negatif;
    konum = konum_pozitif;

    enemy=true;
    if (konum_negatif%8!=7) i=7;
    else i=0;
    while (konum_negatif%8!=i){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif--;

        if (konum_negatif<0)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if(enemy==true && i==0 && konum_negatif%8==0){
            if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
                dugume_ekle(konum_negatif,&move_liste);
            if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true){
                    dugume_ekle(konum_negatif,&move_liste); enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    enemy=true;
    if (konum_pozitif%8!=0) i=0;
    else i=7;
    while (konum_pozitif%8!=i){
        if (((htable->tablo_basi+konum_pozitif)->tas_no)==0)
            dugume_ekle(konum_pozitif,&move_liste);
        konum_pozitif++;

        if (konum_pozitif>64)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_pozitif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_pozitif)->tas_no))==true)
                 dugume_ekle(konum_pozitif,&move_liste);
            enemy=false;
        }

        if(enemy==true && i==7 && konum_pozitif%8==7){
            if (((htable->tablo_basi+konum_pozitif)->tas_no)==0)
                dugume_ekle(konum_pozitif,&move_liste);
            if (((htable->tablo_basi+konum_pozitif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_pozitif)->tas_no))==true){
                    dugume_ekle(konum_pozitif,&move_liste);
                    enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_pozitif=konum;
    while (konum_pozitif>0){
        if (((htable->tablo_basi+konum_pozitif)->tas_no)==0)
            dugume_ekle(konum_pozitif,&move_liste);
        konum_pozitif-=8;

        if (konum_pozitif<-1)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_pozitif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_pozitif)->tas_no))==true)
                 dugume_ekle(konum_pozitif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    enemy=true;
    konum_pozitif=konum;
    while (konum_pozitif<64){
        if (((htable->tablo_basi+konum_pozitif)->tas_no)==0)
            dugume_ekle(konum_pozitif,&move_liste);
        konum_pozitif+=8;

        if (konum_pozitif<-1)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_pozitif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_pozitif)->tas_no))==true)
                 dugume_ekle(konum_pozitif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    dugume_ekle(number,&move_liste);
    dugum_esitle(eski,move_liste);
    draw(move_liste,htable,dot,screen);
    dugum_yok_et(&move_liste);
}

void at_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,struct dugum **eski){
    int index,konum,konum_1;
    struct dugum *move_liste=NULL;

    for(index=0;index<htable->tablo_uzunlugu;index++){
        if (number == ((htable->tablo_basi+index)->tas_no))
            konum = index;
    }

    konum_1=konum;

    for(index=0;index<8;index++){
        if (index==0){
            konum_1=konum-(2*8+1);
            if (konum_1<0 || (konum_1+1)%8==0) index=1;
        }
        if (index==1){
            konum_1=konum-(2*8-1);
            if (konum_1<0 || konum%8==7) index=2;
        }

        if (index==2){
            konum_1=konum-(1*8+2);
            if (konum_1<0 || konum%8==0 || konum%8==1) index=3;
        }

        if (index==3){
            konum_1=konum-(1*8-2);
            if (konum_1<0 || konum%8==6|| konum%8==7) index=4;

        }

        if (index==4){
            konum_1=konum+(2*8-1);
            if (konum>64 || konum%8==0) index=5;
        }

        if (index==5){
            konum_1=konum+(2*8+1);
            if (konum>64 || konum%8==7) index=6;
        }

        if (index==6){
            konum_1=konum+(1*8-2);
            if (konum_1>64 || konum%8==0|| konum%8==1) index=7;
        }

        if (index==7){
            konum_1=konum+(1*8+2);
            if (konum_1>64 || konum%8==6|| konum%8==7) break;
        }

        if (((htable->tablo_basi+konum_1)->tas_no)==0)
            dugume_ekle(konum_1,&move_liste);
        else{
            if (enemy_char(number,((htable->tablo_basi+konum_1)->tas_no))==true)
               dugume_ekle(konum_1,&move_liste);
            }
    }

    dugume_ekle(number,&move_liste);
    dugum_esitle(eski,move_liste);
    draw(move_liste,htable,dot,screen);
    dugum_yok_et(&move_liste);
}

void piyon_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,int renk,struct dugum **eski){
    int index,konum,konum_1,i,j,k;
    struct dugum *move_liste=NULL;

    for(index=0;index<htable->tablo_uzunlugu;index++){
        if (number == ((htable->tablo_basi+index)->tas_no))
            konum = index;
    }

    if (renk==0)                 {i=1;j=16;k=8;}
    if (renk==1){
        j=-16;k=-8;
        if (number==32)  i=-16;     if (number==28)  i=-24;
        if (number==31)  i=-18;     if (number==27)  i=-26;
        if (number==30)  i=-20;     if (number==26)  i=-28;
        if (number==29)  i=-22;     if (number==25)  i=-30;

    }

    konum_1=konum;
    if (number==konum+i){
        konum_1=konum+j;
        if (((htable->tablo_basi+konum_1)->tas_no)==0)
           dugume_ekle(konum_1,&move_liste);
    }

    konum_1=konum+k;
    if (((htable->tablo_basi+konum_1)->tas_no)==0){
        dugume_ekle(konum_1,&move_liste);
    }

    konum_1=konum+k+1;
    if (konum%8!=7){
        if (((htable->tablo_basi+konum_1)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_1)->tas_no))==true)
                dugume_ekle(konum_1,&move_liste);
        }
    }

    konum_1=konum+k-1;
    if (konum%8!=0){
        if (((htable->tablo_basi+konum_1)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_1)->tas_no))==true){
                dugume_ekle(konum_1,&move_liste);
            }
        }
    }

    dugume_ekle(number,&move_liste);
    dugum_esitle(eski,move_liste);
    draw(move_liste,htable,dot,screen);
    dugum_yok_et(&move_liste);
}

void fil_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,struct dugum **eski){
    int index,i;
    int konum_negatif,konum_pozitif,konum;
    bool enemy;
    struct dugum *move_liste = NULL;

    for(index=0;index<htable->tablo_uzunlugu;index++){
        if (number == ((htable->tablo_basi+index)->tas_no)){
            konum_negatif = index;
        }
    }

    konum_pozitif=konum_negatif;
    konum = konum_pozitif;
    enemy=true;
    while (konum_negatif%8!=0){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif-=9;;

        if (konum_negatif<-1)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if(enemy==true && konum_negatif%8==0){
            if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
                dugume_ekle(konum_negatif,&move_liste);
            if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true){
                    dugume_ekle(konum_negatif,&move_liste); enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    konum_negatif=konum;
    enemy=true;
    while (konum_negatif%8!=7){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif+=9;

        if (konum_negatif>65)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if(enemy==true && konum_negatif%8==7){
            if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
                dugume_ekle(konum_negatif,&move_liste);
            if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true){
                    dugume_ekle(konum_negatif,&move_liste); enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_negatif=konum;
    while (konum_negatif%8!=0){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif+=7;

        if (konum_negatif>64)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if(enemy==true && konum_negatif%8==0){
            if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
                dugume_ekle(konum_negatif,&move_liste);
            if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true){
                    dugume_ekle(konum_negatif,&move_liste); enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_negatif=konum;
    while (konum_negatif%8!=7){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif-=7;

        if (konum_negatif<0)
            break;

        if (enemy==true && ((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if(enemy==true && konum_negatif%8==7){
            if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
                dugume_ekle(konum_negatif,&move_liste);
            if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
                if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true){
                    dugume_ekle(konum_negatif,&move_liste); enemy=false;
                }
            }
        }

        if (enemy==false) break;
    }

    dugume_ekle(number,&move_liste);
    dugum_esitle(eski,move_liste);
    draw(move_liste,htable,dot,screen);
    dugum_yok_et(&move_liste);
}

void vezir_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,struct dugum **eski){
    struct dugum *vezir=NULL,*yedek=NULL;
    kale_move(number,htable,dot,screen,eski);

     while (*eski){
        if ((*eski)->icerik!=number)
            dugume_ekle((*eski)->icerik,&vezir);
        (*eski)=(*eski)->link;
    }
    fil_move(number,htable,dot,screen,eski);

    while (vezir){
        dugume_ekle(vezir->icerik,eski);
        vezir=vezir->link;
    }
}

void kral_move(int number,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen,struct dugum **eski){
    int index,i;
    int konum_negatif,konum;
    bool enemy;
    struct dugum *move_liste = NULL;

    for(index=0;index<htable->tablo_uzunlugu;index++){
        if (number == ((htable->tablo_basi+index)->tas_no)){
            konum_negatif = index;
        }
    }
    konum = konum_negatif;

    enemy=true;
    for (i=0;i<2;i++){
        if (konum%8==0) break;
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif--;

        if (konum_negatif<0)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_negatif=konum;
    for (i=0;i<2;i++){
        if (konum%8==7) break;
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif++;

        if (konum_negatif>63)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_negatif=konum;
    for (i=0;i<2;i++){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif-=8;

        if (konum_negatif<0)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if (enemy==false) break;
    }

    enemy=true;
    konum_negatif=konum;
    for (i=0;i<2;i++){
        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif+=8;

        if (konum_negatif>63)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }

        if (enemy==false) break;
    }

    konum_negatif=konum;
    enemy=true;
    for (i=0;i<2;i++){
        if (konum%8==0) break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif-=9;

        if (konum_negatif<-1)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    konum_negatif=konum;
    enemy=true;
    for (i=0;i<2;i++){
        if (konum%8==7) break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif-=7;

        if (konum_negatif<0)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    konum_negatif=konum;
    enemy=true;
    for (i=0;i<2;i++){
        if (konum%8==7) break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif+=9;

        if (konum_negatif>64)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    konum_negatif=konum;
    enemy=true;
    for (i=0;i<2;i++){
        if (konum%8==0) break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)==0)
            dugume_ekle(konum_negatif,&move_liste);
        konum_negatif+=7;

        if (konum_negatif>64)
            break;

        if (((htable->tablo_basi+konum_negatif)->tas_no)!=0){
            if (enemy_char(number,((htable->tablo_basi+konum_negatif)->tas_no))==true)
                 dugume_ekle(konum_negatif,&move_liste);
            enemy=false;
        }
        if (enemy==false) break;
    }

    dugume_ekle(number,&move_liste);
    dugum_esitle(eski,move_liste);
    draw(move_liste,htable,dot,screen);
    dugum_yok_et(&move_liste);
}

void draw(struct dugum *dugum,struct hash_tablosu *htable,struct SDL_Surface *dot,struct SDL_Surface *screen){
    int index;
    dugum=dugum->link;
    while (dugum){
        index=0;
        for(index=0;index<htable->tablo_uzunlugu;index++){
            if (dugum->icerik == index){
                apply_surface((htable->tablo_basi+index)->Tx,(htable->tablo_basi+index)->Ty,dot,screen);
                break;
           }
        }
        dugum=dugum->link;
    }
}

void move_tas(int istenilen_konum,int tas_numara,struct hash_tablosu *htable,struct SDL_Surface *screen,struct surfacer as,
              struct SDL_Surface *bb){
    int indx,b_gameover=-1,s_gameover=-1;
    for (indx=0;indx<64;indx++){
        if (tas_numara==((htable->tablo_basi+indx)->tas_no))
            ((htable->tablo_basi+indx)->tas_no)=0;
    }

    ((htable->tablo_basi+istenilen_konum)->tas_no)=tas_numara;
    apply_surface(29,4,bb,screen);
    print_hash_table(htable);

    for (indx=0;indx<64;indx++){
        if (((htable->tablo_basi+indx)->tas_no)==20)
            b_gameover=indx;
    }

    if (b_gameover==-1) end_game(screen,1);

    for (indx=0;indx<64;indx++){
        if (((htable->tablo_basi+indx)->tas_no)==4)
            s_gameover=indx;
    }
    if (s_gameover==-1) end_game(screen,0);

}

void end_game(struct SDL_Surface *screen,int kazanan){
    SDL_Surface *message=NULL;
    TTF_Font *font=NULL;
    font = TTF_OpenFont("font.ttf",39);
    SDL_Color textColor = { 250, 0, 0 };
    if (kazanan==1)
        message = TTF_RenderText_Solid( font, "SIYAH KAZANDI! KAPANIYOR" , textColor );
    if (kazanan==0)
        message = TTF_RenderText_Solid( font, "BEYAZ KAZANDI! KAPANIYOR" , textColor );
    apply_surface(50,200,message,screen);
    SDL_QuitEvent(event);
    SDL_Flip(screen);
    SDL_Delay(2000);
    SDL_Quit();
}


#endif // MOVE_STAFFS_H_INCLUDED
