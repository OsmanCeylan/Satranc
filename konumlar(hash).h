#ifndef KONUMLAR(HASH)_H_INCLUDED
#define KONUMLAR(HASH)_H_INCLUDED

#include "taslar.h"

struct hash_tablosu
{
    struct table_node *tablo_basi;
    int tablo_uzunlugu;
    int multiplier;
};

struct table_node
{
    uint16_t tas_no;
    int Tx,Ty;
};


struct dugum{
    int icerik;
    struct dugum *link;
};


struct dugum * dugum_olustur(int icerik){
    struct dugum *d;
    d=(struct dugum*)malloc(sizeof(struct dugum));
    if(d==NULL){
        printf("Yer ayrilamadi.....");
        exit(1);
    }
    d->icerik=icerik;
    d->link=NULL;
    return d;
}


void dugume_ekle(int icerik,struct dugum **dugum_gostergesi){
    struct dugum *gecici=dugum_olustur(icerik);
    gecici->link=*dugum_gostergesi;
    *dugum_gostergesi=gecici;
}

void dugum_yazdir(struct dugum *yigin_gostergesi){
    while(yigin_gostergesi){
        printf("%4d",yigin_gostergesi->icerik);
        yigin_gostergesi=yigin_gostergesi->link;
    }
    printf("\n");
}

bool dugum_arama(int num,struct dugum *yigin_gostergesi){
    while(yigin_gostergesi){
        if (num==yigin_gostergesi->icerik)
            return true;
        yigin_gostergesi=yigin_gostergesi->link;
    }
    return false;
}

void dugum_esitle(struct dugum **ilk,struct dugum *ikinci){
    (*ilk)=NULL;
    if (ikinci==NULL) (*ilk)=NULL;
    else{
        while (ikinci){
            dugume_ekle(ikinci->icerik,ilk);
            ikinci=ikinci->link;
        }
    }
}

void dugum_yok_et(struct dugum **y){
    if ((*y)!=NULL){
        free((*y)->link);
        free(*y);
        *y=NULL;
    }
}

void initialize_hash_table(struct hash_tablosu **hash_table,int multiplier,int table_size)
{
    int i;
    *hash_table=(struct hash_tablosu*)malloc(sizeof(struct hash_tablosu));
    if(*hash_table==NULL){
        printf("hash tablosu icin gerkli? yer ayrilmadi...");
        exit(1);
    }
    (*hash_table)->tablo_basi=(struct table_node*)malloc(table_size*sizeof(struct table_node));
    if((*hash_table)->tablo_basi==NULL)
    {
        printf("hash tablosu icin gerkli? yer ayrilmadi...");
        exit(1);
    }
    (*hash_table)->tablo_uzunlugu=table_size;
    (*hash_table)->multiplier=multiplier;
}

void insert_hash_table(struct hash_tablosu *hash_table,int anahtar,int hash_index)
{
    ((hash_table->tablo_basi + hash_index)->tas_no) = anahtar;

}

void insert_pixel_hash(struct hash_tablosu *hash_table,int x,int y,int hash_index){

    ((hash_table->tablo_basi + hash_index)->Tx) = x;
    ((hash_table->tablo_basi + hash_index)->Ty) = y;

}

void print_hash_table(struct hash_tablosu *hash_table)
{
    if(hash_table)
    {
        int index;
        printf("----------HASH TABLOSU-------\n");
        for(index=0;index<hash_table->tablo_uzunlugu;index++)
        {
            printf("%5d : (%4d) : %5d %4d ",index,(hash_table->tablo_basi+index)->tas_no,
                   (hash_table->tablo_basi+index)->Tx,(hash_table->tablo_basi+index)->Ty);
            printf("\n");
        }
    }
    else printf("Hash tablosu bos...\n");
}

void taslar_yerlestir(class taslar tas,struct hash_tablosu *htable){

    int i;
    if (tas.tas_number<=16)
        insert_hash_table(htable,tas.tas_number,tas.get_tas_yeri());
    for (i=16;i<48;i++)
        insert_hash_table(htable,0,i);
    if (tas.tas_number>16)
        insert_hash_table(htable,tas.tas_number,tas.get_tas_yeri());
}

void pixel_gir(struct hash_tablosu *htable){
    int i,j,m=0,k=8;
    int x=20,y=6;
    for (j=0;j<8;j++){
        for (i=0;i<k;i++){
            insert_pixel_hash(htable,x,y,m);
            m++;
            x+=93;
        }
        x=20;y+=80;i=0;
    }
    print_hash_table(htable);
}

#endif // KONUMLAR(HASH)_H_INCLUDED
