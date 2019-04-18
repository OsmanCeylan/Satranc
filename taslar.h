#ifndef TASLAR_H_INCLUDED
#define TASLAR_H_INCLUDED

#include "load.h"
#include <iostream>

class taslar{
    SDL_Surface *img_ismi;
  public:
    std::string tas_ad;
    int tas_number;
    Uint16 tas_move_area();
    int get_tas_yeri();
    taslar(int );
    int tas_ozellikleri();
};

taslar::taslar(int numarasi){
        img_ismi = NULL;
        tas_number = numarasi;
}

int taslar::get_tas_yeri(){
        if (tas_number == 1)  return 0;     if (tas_number == 17)  return  63;
        if (tas_number == 2)  return 1;     if (tas_number == 18)  return  62;
        if (tas_number == 3)  return 2;     if (tas_number == 19)  return  61;
        if (tas_number == 4)  return 3;     if (tas_number == 20)  return  60;
        if (tas_number == 5)  return 4;     if (tas_number == 21)  return  59;
        if (tas_number == 6)  return 5;     if (tas_number == 22)  return  58;
        if (tas_number == 7)  return 6;     if (tas_number == 23)  return  57;
        if (tas_number == 8)  return 7;     if (tas_number == 24)  return  56;
        if (tas_number == 9)  return 8;     if (tas_number == 25)  return  55;
        if (tas_number == 10) return 9;     if (tas_number == 26)  return  54;
        if (tas_number == 11) return 10;    if (tas_number == 27)  return  53;
        if (tas_number == 12) return 11;    if (tas_number == 28)  return  52;
        if (tas_number == 13) return 12;    if (tas_number == 29)  return  51;
        if (tas_number == 14) return 13;    if (tas_number == 30)  return  50;
        if (tas_number == 15) return 14;    if (tas_number == 31)  return  49;
        if (tas_number == 16) return 15;    if (tas_number == 32)  return  48;

}

int taslar::tas_ozellikleri()
{
    std::cout << tas_number << tas_ad;
    if (img_ismi == NULL)  printf("0");
    else  printf("1");
    return tas_number;
}

#endif // TASLAR_H_INCLUDED
