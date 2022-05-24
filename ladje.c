#include <stdio.h>
#include <stdlib.h>
#include "ladje.h"
#include "util.h"
#include <time.h>
#include <math.h>

int ladje_prejsnjiposkus[2];
int ladje_prejzadeta;
int ladje[5][6];

void ladje_init(int morje[10][10], int nasprotnikovo_morje[10][10]) {
    /*ta koda se izvede pred vsako igro, postavi spremenljivke na 0 in vse elemente tabele ladje na 0. Tabela ladje
     nam predstavlja evidenco vseh ladij, koordinate skrajnih tock zadete ladje, njeno tonažo in stanje potopljenosti*/
    ladje_prejzadeta = 0;

    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 6; j++) {
            ladje[i][j] = 0;
        }
    }
}

void ladje_postavi(int morje[10][10]) { //koda bi lahko bila bolj gnezdena
    /*Najprej postavimo 5 tonko random, zatem štirico random, potem trojko,...
    sproti preverja kam lahko postavi. Preverja stik, križanje. Če ne ustreza pogojem generira novo postavitev.
    Prvo sem naredil preverjanje za 4-tonko, to preverjanje sem nato kopiral in spremenil par števil za preverjanje pri 3 in 2-tonki.
    Preverjanje bi lahko lažje izvedel, če bi na začetku generiral polje 12x12x in bi vedno le preveril da okoli ni kakšni drugih števil
    zdaj pa sem moral preverjanje izvesti po posameznih primerih, saj nisem mogel gledati izven polja.  */
    int a,b,c,vsota;
    int i=0;
    /*5-tonka: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;
    }while(b>5);                        //število od 0 do 5
    c = rand() % 2;                     //vrne 0 ali 1, ki nam predstavlja orientacijo ladjice
    if (c==1){                          //vodoravno
        for (i = 0; i < 5; i++)         // [vrstica][stolpec] , zagotovo bo v polju, najprej postavimo 5tonko
        morje[a][b+i] = 5;              //prvi clen tabele se klice z 0
        }
    else {                              //navpicno
        for (i = 0; i < 5; i++)
        morje[b+i][a] = 5;
    }

     /*4-tonka: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    c = rand() % 2; //
    if (c==1){
    do {
    a = rand() % 10;
    do{
    b = rand() % 10;                    //število od 0 do 6, da gre stiritonka najvec do 9
    }while(b>6);
    int zasedeno[4]={0,0,0,0}; vsota=0;
    for (i = 0; i < 4; i++){
        if (morje[a][b+i] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je zgorej preverimo samo spodaj **************
                     if (morje[a+1][b+i] == 0){
                        switch(b) {     //preverjamo veljavnost ob strani
                          case 0 :      //ce je levo preverimo samo desno
                             if (morje[a][b+4] != 0 || morje[a+1][b+4] != 0){ //samo spodaj ce je gor
                             zasedeno[i] = 1;}
                             break;
                          case 6 :      //ce je desno preverimo samo levo
                             if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[a][b+4] != 0 || morje[a+1][b+4] != 0 ||
                                 morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je spodaj preverimo samo zgoraj ***************
                     if (morje[a-1][b+i] == 0){
                         switch(b) {    //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+4] != 0 || morje[a-1][b+4] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 6 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+4] != 0 || morje[a-1][b+4] != 0 ||
                                     morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[a-1][b+i] == 0 && morje[a+1][b+i] == 0){
                            switch(b) { //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+4] != 0 || morje[a+1][b+4] != 0 || morje[a-1][b+4] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 6 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+4] != 0 || morje[a+1][b+4] != 0 || morje[a-1][b+4] != 0 ||
                                     morje[a][b-1] != 0 || morje[a+1][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }

        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);                    //mora bit false (0), da gre ven iz zanke
    for (i = 0; i < 4; i++){
    morje[a][b+i] = 4;                  //postavitev ladjic vodoravno
        }
    }
    else { // ------------------------------------------------------------------------------------------
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 6
    }while(b>6);
    int zasedeno[4]={0,0,0,0}; vsota=0;
    for (i = 0; i < 4; i++){
                if (morje[b+i][a] == 0){ //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je levo preverimo samo desno **************
                     if (morje[b+i][a+1] == 0){
                        switch(b) {     //preverjamo veljavnost ob spodej
                          case 0 :      //ce je zgorej preverimo samo spodej
                             if (morje[b+4][a] != 0 || morje[b+4][a+1] != 0){       //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 6 :      //ce je spodej preverimo samo zgorej
                             if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[b+4][a] != 0 || morje[b+4][a+1] != 0 ||
                                 morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je desno preverimo samo levo ***************
                     if (morje[b+i][a-1] == 0){ //preverjamo veljavnost ob strani (levo)
                         switch(b) {
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+4][a] != 0 || morje[b+4][a-1] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 6 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+4][a] != 0 || morje[b+4][a-1] != 0 ||
                                     morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[b+i][a-1] == 0 && morje[b+i][a+1] == 0){
                            switch(b) {  //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+4][a] != 0 || morje[b+4][a+1] != 0 || morje[b+4][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 6 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+4][a] != 0 || morje[b+4][a+1] != 0 || morje[b+4][a-1] != 0 ||
                                     morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }
        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 4; i++){
    morje[b+i][a] = 4;
    }
    }
     /*3-tonka: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    c = rand() % 2;                     //vodoravno ali navpicno
    i=0;
    if (c==1){
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 7
    }while(b>7);
    int zasedeno[3]={0,0,0}; vsota=0;
    for (i = 0; i < 3; i++){
        if (morje[a][b+i] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je zgorej preverimo samo spodaj **************
                     if (morje[a+1][b+i] == 0){ //preverjamo veljavnost ob strani
                        switch(b) {
                          case 0 :      //ce je levo preverimo samo desno
                             if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0){ //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 7 :      //ce je desno preverimo samo levo
                             if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 ||
                                 morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je spodaj preverimo samo zgoraj ***************
                     if (morje[a-1][b+i] == 0){
                         switch(b) {    //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+3] != 0 || morje[a-1][b+3] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+3] != 0 || morje[a-1][b+3] != 0 ||
                                     morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[a-1][b+i] == 0 && morje[a+1][b+i] == 0){
                            switch(b) {  //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 || morje[a-1][b+3] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 || morje[a-1][b+3] != 0 ||
                                     morje[a][b-1] != 0 || morje[a+1][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }

        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 3; i++){
    morje[a][b+i] = 3;
        }
    }
    else { // -----------------------------------------------------------------------------------
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 7
    }while(b>7);
    int zasedeno[3]={0,0,0}; vsota=0;   //postavimo na 0
    for (i = 0; i < 3; i++){
        if (morje[b+i][a] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je levo preverimo samo desno **************
                     if (morje[b+i][a+1] == 0){
                        switch(b) {     //preverjamo veljavnost ob spodej
                          case 0 :      //ce je zgorej preverimo samo spodej
                             if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0){   //samo spodaj ce je gor
                             zasedeno[i] = 1;}
                             break;
                          case 7 :      //ce je spodej preverimo samo zgorej
                             if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo spodej in zgorej
                             if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 ||
                                 morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je desno preverimo samo levo ***************
                     if (morje[b+i][a-1] == 0){ //preverjamo veljavnost ob strani (levo)
                         switch(b) {
                              case 0 :  //ce je desno preverimo samo levo
                                 if (morje[b+3][a] != 0 || morje[b+3][a-1] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+3][a] != 0 || morje[b+3][a-1] != 0 ||
                                     morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[b+i][a-1] == 0 && morje[b+i][a+1] == 0){
                            switch(b) {  //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 || morje[b+3][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 || morje[b+3][a-1] != 0 ||
                                     morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }
        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 3; i++){
    morje[b+i][a] = 3;
    }
    }
     /*druga 3-tonka: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    c = rand() % 2;
    i=0;
    if (c==1){
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 7
    }while(b>7);
    int zasedeno[3]={0,0,0}; vsota=0;   //postavimo na 0
    for (i = 0; i < 3; i++){
        if (morje[a][b+i] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je zgorej preverimo samo spodaj **************
                     if (morje[a+1][b+i] == 0){
                        switch(b) {     //preverjamo veljavnost ob strani
                          case 0 :      //ce je levo preverimo samo desno
                             if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0){ //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 7 :      //ce je desno preverimo samo levo
                             if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 ||
                                 morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je spodaj preverimo samo zgoraj ***************
                     if (morje[a-1][b+i] == 0){
                         switch(b) {    //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+3] != 0 || morje[a-1][b+3] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+3] != 0 || morje[a-1][b+3] != 0 ||
                                     morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[a-1][b+i] == 0 && morje[a+1][b+i] == 0){
                            switch(b) { //preverjamo veljavnost ob strani
                              case 0 :  //èe je levo preverimo samo desno
                                 if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 || morje[a-1][b+3] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+3] != 0 || morje[a+1][b+3] != 0 || morje[a-1][b+3] != 0 ||
                                     morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }

        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 3; i++){
    morje[a][b+i] = 3;
        }
    }
    else { // ---------------------------------------------------------------------------
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 7
    }while(b>7);
    int zasedeno[3]={0,0,0}; vsota=0;
    for (i = 0; i < 3; i++){
        if (morje[b+i][a] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je levo preverimo samo desno **************
                     if (morje[b+i][a+1] == 0){
                        switch(b) {     //preverjamo veljavnost ob spodej
                          case 0 :      //ce je zgorej preverimo samo spodej
                             if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0){ //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 7 :      //ce je spodej preverimo samo zgorej
                             if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 ||
                                 morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je desno preverimo samo levo ***************
                     if (morje[b+i][a-1] == 0){ //preverjamo veljavnost ob strani (levo)
                         switch(b) {
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+3][a] != 0 || morje[b+3][a-1] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+3][a] != 0 || morje[b+3][a-1] != 0 ||
                                     morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[b+i][a-1] == 0 && morje[b+i][a+1] == 0){
                            switch(b) { //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 || morje[b+3][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 7 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+3][a] != 0 || morje[b+3][a+1] != 0 || morje[b+3][a-1] != 0 ||
                                     morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }
        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 3; i++){
    morje[b+i][a] = 3;
    }
    }
    /*2-tonka: +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
     ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
    c = rand() % 2;                     //vodoravno ali navpièno
    i=0;
    if (c==1){
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 8
    }while(b>8);
    int zasedeno[2]={0,0}; vsota=0;     //postavimo na 0
    for (i = 0; i < 2; i++){
        if (morje[a][b+i] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je zgorej preverimo samo spodaj **************
                     if (morje[a+1][b+i] == 0){
                        switch(b) {     //preverjamo veljavnost ob strani
                          case 0 :      //ce je levo preverimo samo desno
                             if (morje[a][b+2] != 0 || morje[a+1][b+2] != 0){ //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 8 :      //ce je desno preverimo samo levo
                             if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[a][b+2] != 0 || morje[a+1][b+2] != 0 ||
                                 morje[a][b-1] != 0|| morje[a+1][b-1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je spodaj preverimo samo zgoraj ***************
                     if (morje[a-1][b+i] == 0){
                         switch(b) {    //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+2] != 0 || morje[a-1][b+2] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 8 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+2] != 0 || morje[a-1][b+2] != 0 ||
                                     morje[a][b-1] != 0 || morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[a-1][b+i] == 0 && morje[a+1][b+i] == 0){
                            switch(b) { //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[a][b+2] != 0 || morje[a+1][b+2] != 0 || morje[a-1][b+2] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 8 :  //ce je desno preverimo samo levo
                                 if (morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[a][b+2] != 0 || morje[a+1][b+2] != 0 || morje[a-1][b+2] != 0 ||
                                     morje[a][b-1] != 0|| morje[a+1][b-1] != 0|| morje[a-1][b-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }

        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 2; i++){
    morje[a][b+i] = 2;
        }
    }
    else { // -------------------------------------------------------------------------------
    do {
    a = rand() % 10;                    //število od 0 do 9
    do{
    b = rand() % 10;                    //število od 0 do 8
    }while(b>8);
    int zasedeno[2]={0,0}; vsota=0;     //postavimo na 0
    for (i = 0; i < 2; i++){
        if (morje[b+i][a] == 0){        //prvo preveri križanje
                switch(a) {
                  case 0 :              //ce je levo preverimo samo desno **************
                     if (morje[b+i][a+1] == 0){
                        switch(b) {     //preverjamo veljavnost ob spodej
                          case 0 :      //ce je zgorej preverimo samo spodej
                             if (morje[b+2][a] != 0 || morje[b+2][a+1] != 0){ //samo spodaj èe je gor
                             zasedeno[i] = 1;}
                             break;
                          case 8 :      //ce je spodej preverimo samo zgorej
                             if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                             break;
                          default :     //ce je na sredini pogledamo desno in levo
                             if (morje[b+2][a] != 0 || morje[b+2][a+1] != 0 ||
                                 morje[b-1][a] != 0|| morje[b-1][a+1] != 0){
                             zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  case 9 :              //ce je desno preverimo samo levo ***************
                     if (morje[b+i][a-1] == 0){ //preverjamo veljavnost ob strani (levo)
                         switch(b) {
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+2][a] != 0 || morje[b+2][a-1] != 0){ //samo zgoraj
                                 zasedeno[i] = 1;}
                                 break;
                              case 8 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+2][a] != 0 || morje[b+2][a-1] != 0 ||
                                     morje[b-1][a] != 0 || morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                        }
                        else zasedeno[i] = 1;
                     break;
                  default :             //ce je na sredini pogledamo zgoraj in spodaj **********
                     if (morje[b+i][a-1] == 0 && morje[b+i][a+1] == 0){
                            switch(b) {  //preverjamo veljavnost ob strani
                              case 0 :  //ce je levo preverimo samo desno
                                 if (morje[b+2][a] != 0 || morje[b+2][a+1] != 0 || morje[b+2][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              case 8 :  //ce je desno preverimo samo levo
                                 if (morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                                 break;
                              default : //ce je na sredini pogledamo desno in levo
                                 if (morje[b+2][a] != 0 || morje[b+2][a+1] != 0 || morje[b+2][a-1] != 0 ||
                                     morje[b-1][a] != 0|| morje[b-1][a+1] != 0|| morje[b-1][a-1] != 0){
                                 zasedeno[i] = 1;}
                            }
                     }
                     else zasedeno[i] = 1;
                    }
        }
        else zasedeno[i] = 1;
    vsota+=zasedeno[i];
    }
    } while (vsota);
    for (i = 0; i < 2; i++){
    morje[b+i][a] = 2;
    }
    }
//    for (i=0;i<10;i++){               //tukaj je izpis ladij za preverjanje
//        for(j=0;j<10;j++){
//        printf("%2d",morje[i][j]);
//    }
//    printf("\n");
//}
    if (!preveri_postavitev(morje)) { //----------------------------------------------------
        printf("Napaka postavitve!\n");
    }
    return;
}

void ladje_ugibaj(int koordinata[2], int nasprotnikovo_morje[10][10]) {
    /*Najprej preverimo, če smo prejšno potezo zadeli. Če smo zadeli postavimo na diagonale zadete točke enke, ker upoštevamo pravilo, da se ladje
    ne smejo stikati.*/
    int ze_poskusano = 1;

    if (ladje_prejzadeta) {
    /*Enice ne smemo postavljati izven nasprotnikovega morja, saj so na tistih mestih definirane kakšne druge stvari. Tukaj najprej preverimo
    kje je prejšna zadeta ladjica in na podlagi tega izberemo na katere diagonale lahko postavimo enke. */
        if (ladje_prejsnjiposkus[0]+1 < 10 && ladje_prejsnjiposkus[1]+1 < 10)
            nasprotnikovo_morje[ladje_prejsnjiposkus[0]+1][ladje_prejsnjiposkus[1]+1]=1;    //postavi enko desno spodaj
        if (ladje_prejsnjiposkus[0]+1 < 10 && ladje_prejsnjiposkus[1]-1 > -1)
            nasprotnikovo_morje[ladje_prejsnjiposkus[0]+1][ladje_prejsnjiposkus[1]-1]=1;    //postavi enko levo spodaj
        if (ladje_prejsnjiposkus[0]-1 > -1 && ladje_prejsnjiposkus[1]+1 < 10)
            nasprotnikovo_morje[ladje_prejsnjiposkus[0]-1][ladje_prejsnjiposkus[1]+1]=1;    //postavi enko desno zgoraj
        if (ladje_prejsnjiposkus[0]-1 > -1 && ladje_prejsnjiposkus[1]-1 > -1)
            nasprotnikovo_morje[ladje_prejsnjiposkus[0]-1][ladje_prejsnjiposkus[1]-1]=1;    //postavi enko levo zgoraj

        int potapljanjeladje = -1;

        int zadetek[2];         //tukaj sem se odločil da skrajšam ime spremenljivke
        zadetek[0] = ladje_prejsnjiposkus[0];
        zadetek[1] = ladje_prejsnjiposkus[1];

        //Ugotavljanje ali smo na novo zadel (-1) ali potapljamo (index ladje)
        int i;
        for (i = 0; i < 5; i++) {
            if (ladje[i][0] > 0 && ladje[i][5] == 0) {      //peto mesto v tabeli [i][5] nam pove stanje potopljenosti, 1- potopljena, 0-nepotopljena
                potapljanjeladje = i;
            }
        }

        //Če smo na novo zadeli, bomo na prazno mesto v evidenci vpisali novo ladjo za potopit
        if (potapljanjeladje == -1) {                       //ce smo na novo zadeli in ni v postopku zadevanja kakšna druga ladja (vsako ladjo se najprej do konca potopi)
            int i;
            int mestozanovoladjo;
            for (i = 0; i < 5; i++) {
                if (ladje[i][0] == 0) {
                    mestozanovoladjo = i;                   //določi mesto v tabeli
                    break;
                }
            }

            /*
            Vnos nove ladje v evidenco:
            [0] - tonaza ladje
            [1][2] - koordinate 1. roba
            [3][4] - koordinate 2. roba (neznano, nastavimo -1)
            [5] - ladja potopljena? (ostane na 0)
            */
            ladje[mestozanovoladjo][0] = nasprotnikovo_morje[ladje_prejsnjiposkus[0]][ladje_prejsnjiposkus[1]];
            ladje[mestozanovoladjo][1] = ladje_prejsnjiposkus[0];
            ladje[mestozanovoladjo][2] = ladje_prejsnjiposkus[1];
            ladje[mestozanovoladjo][3] = -1;                //neznan drug rob ladje, saj je nov vpis
            ladje[mestozanovoladjo][4] = -1;
        } else {
            //Vpis potopljenosti potapljajoce ladje (ce je ta ladja v postopku potapljanja)
            //Usmerjenost ladje
            int vodoravna = 0;
            if (ladje[potapljanjeladje][1] == zadetek[0]) //ce so prve koordinate prve in druge tocke iste lahko recemo, da je ladja postavljena vodoravno, recimo [3][2] [3][1]
                vodoravna = 1;

            if (vodoravna == 1) {
                if (ladje[potapljanjeladje][3] == -1) {                 //Ce vpisujemo 2. zadetek (smo ugotovili smer)
                    if (ladje[potapljanjeladje][2] > zadetek[1]) {      /*Ce je nova koordinata manjsa od stare, jo zapisemo nav1. mesto v evidenci,
                                                                        staro 1. mesto pa premaknemo na 2. mesto evidenci (gledamo le vodoravno smer)*/
                        ladje[potapljanjeladje][3] = ladje[potapljanjeladje][1];
                        ladje[potapljanjeladje][4] = ladje[potapljanjeladje][2];
                        ladje[potapljanjeladje][1] = zadetek[0];
                        ladje[potapljanjeladje][2] = zadetek[1];
                    } else {                                            //Sicer samo vpisemo novo koordinato na 2. mesto v evidenci
                        ladje[potapljanjeladje][3] = zadetek[0];
                        ladje[potapljanjeladje][4] = zadetek[1];
                    }
                } else {                                                //Ce vpisujemo 3. ali visji zadetek
                    if (ladje[potapljanjeladje][2] > zadetek[1]) {      //Ce je nova koordinata manjsa od 1. mesta v evidenci jo vpisemo v 1. mesto v evidenci
                        ladje[potapljanjeladje][1] = zadetek[0];
                        ladje[potapljanjeladje][2] = zadetek[1];
                    } else {                                            //Ce je nova koordinata vecja od 1. mesta v evidenci jo vpisemo v 2. mesto v evidenci (ker ciljamo po vrst)
                        ladje[potapljanjeladje][3] = zadetek[0];
                        ladje[potapljanjeladje][4] = zadetek[1];
                    }
                }
            } else {                                                    //princip je analogen za vertikalno obrnjeno ladjo
                if (ladje[potapljanjeladje][3] == -1) {                 //Ce vpisujemo 2. zadetek (smo ugotovili smer)
                    if (ladje[potapljanjeladje][1] > zadetek[0]) {      //Ce je nova koordinata manjsa od stare, jo zapisemo na 1. mesto v evidenci, staro 1. mesto pa premaknemo na 2. mesto evidenci
                        ladje[potapljanjeladje][3] = ladje[potapljanjeladje][1];
                        ladje[potapljanjeladje][4] = ladje[potapljanjeladje][2];
                        ladje[potapljanjeladje][1] = zadetek[0];
                        ladje[potapljanjeladje][2] = zadetek[1];
                    } else {                                            //Sicer samo vpisemo novo koordinato na 2. mesto v evidenci
                        ladje[potapljanjeladje][3] = zadetek[0];
                        ladje[potapljanjeladje][4] = zadetek[1];
                    }
                } else {                                                //Ce vpisujemo 3. ali visji zadetek
                    if (ladje[potapljanjeladje][1] > zadetek[0]) {      //Ce je nova koordinata manjsa od 1. mesta v evidenci jo vpisemo v 1. mesto v evidenci
                        ladje[potapljanjeladje][1] = zadetek[0];
                        ladje[potapljanjeladje][2] = zadetek[1];
                    } else {                                            //Ce je nova koordinata vecja od 1. mesta v evidenci jo vpisemo v 2. mesto v evidenci (ker ciljamo po vrst)
                        ladje[potapljanjeladje][3] = zadetek[0];
                        ladje[potapljanjeladje][4] = zadetek[1];
                    }
                }
            }

            if (vodoravna == 1) {                                       //sedaj se pogleda, če je ladja že potopljena
            	int dolzinapotopljene =  ladje[potapljanjeladje][4] - ladje[potapljanjeladje][2] + 1;  //preveri, ce skrajne lege ze ustrezajo dolzini ladje
            	if (dolzinapotopljene == ladje[potapljanjeladje][0]) {	//Ce smo celo potopili
            		ladje[potapljanjeladje][5] = 1;                     //v evidenco oznaci, da je ladja potopljena
                    if (ladje[potapljanjeladje][2] - 1 > -1)            //ce je na levi strani končane ladje 0, tja postavimo 1, da zapremo ladjo
                            nasprotnikovo_morje[ladje[potapljanjeladje][1]][ladje[potapljanjeladje][2] - 1] = 1;
            		if (ladje[potapljanjeladje][4] + 1 < 10)            //na desni strani naredimo isto
                        nasprotnikovo_morje[ladje[potapljanjeladje][3]][ladje[potapljanjeladje][4] + 1] = 1;
            	}
            } else {                                                    //analogno se naredi za navpicno ladjo
            	int dolzinapotopljene =  ladje[potapljanjeladje][3] - ladje[potapljanjeladje][1] + 1;
            	if (dolzinapotopljene == ladje[potapljanjeladje][0]) {	//Ce smo celo potopili
            		ladje[potapljanjeladje][5] = 1;

                    if (ladje[potapljanjeladje][1] - 1 > -1)            //preveri, da ne vpisuje izven morja
                        nasprotnikovo_morje[ladje[potapljanjeladje][1] - 1][ladje[potapljanjeladje][2]] = 1;        //vpise 1 na vrh ladje in jo zapre
            		if (ladje[potapljanjeladje][3] + 1 < 10)
                        nasprotnikovo_morje[ladje[potapljanjeladje][3] + 1][ladje[potapljanjeladje][4]] = 1;
            	}
            }
        }
    }

    //Preverimo ce potapljamo ladjo (ce je ze bila zadeta ampak ni potopljena)
    int ciljamladjo = -1;
    int i;
    for (i = 0; i < 5; i ++) {
        if (ladje[i][0] > 0 && ladje[i][5] == 0) {
            ciljamladjo = i;
        }
    }
    if (ciljamladjo == -1) {	            //Iscemo ladjo, ni nobene na pol poteplejen v evidenci
        do {
        koordinata[0] = rand() % 10;        //random koordinata v y smeri

        if((koordinata[0]%2)==0){           //ce je sodo
            koordinata[1] = 1 + ((rand() % 5)*2);  //streljanje v šahovnici
        }
        else{                               //ce je liho
            koordinata[1] = (rand() % 5)*2;
        }

        if (nasprotnikovo_morje[koordinata[0]][koordinata[1]] == 0)     //preveri, ce tja se nismo streljali
            ze_poskusano = 0;               //ce na lokacijo se nismo streljali omogoci izhod iz zanke
        } while (ze_poskusano);
    } else {
    	//Ugotovimo ce ze poznamo smer. Ce je ne, streljamo po vrsti v 4 smeri okoli ene znane tocke. Sicer v smeri znanih tock ladje streljamo pred in za njimi.
    	if (ladje[ciljamladjo][3] == -1) {			//Ne poznamo smeri, saj poznamo le eno tocko
    		if (nasprotnikovo_morje[ladje[ciljamladjo][1]][ladje[ciljamladjo][2] + 1] == 0 && (ladje[ciljamladjo][2] + 1) < 10) {			//Ciljamo desno, sproti preverimo pozicijo v polju
    			koordinata[0] = ladje[ciljamladjo][1];
    			koordinata[1] = ladje[ciljamladjo][2] + 1;
    		} else if (nasprotnikovo_morje[ladje[ciljamladjo][1] - 1][ladje[ciljamladjo][2]] == 0 && (ladje[ciljamladjo][1] - 1) > -1) {	//Ciljamo gor
    			koordinata[0] = ladje[ciljamladjo][1] - 1;
    			koordinata[1] = ladje[ciljamladjo][2];
    		} else if (nasprotnikovo_morje[ladje[ciljamladjo][1]][ladje[ciljamladjo][2] - 1] == 0 && (ladje[ciljamladjo][2] - 1) > -1) {	//Ciljamo levo
    			koordinata[0] = ladje[ciljamladjo][1];
    			koordinata[1] = ladje[ciljamladjo][2] - 1;
    		} else if (nasprotnikovo_morje[ladje[ciljamladjo][1] + 1][ladje[ciljamladjo][2]] == 0 && (ladje[ciljamladjo][1] + 1) < 10) {	//Ciljamo dol
    			koordinata[0] = ladje[ciljamladjo][1] + 1;
    			koordinata[1] = ladje[ciljamladjo][2];
    		}
            //else {                                //s tem sem si pomagal pri ugotavljanju problema
//                    printf("C(%i): %i x %i\n", ciljamladjo, ladje[ciljamladjo][1], ladje[ciljamladjo][2]);
//                    int k, l;
//                    for (k = 0; k < 10; k++) {
//                        for (l = 0; l < 10; l++) {
//                            printf("%i ", nasprotnikovo_morje[k][l]);
//                        }
//                        printf("\n");
//                    }
//            }
    	} else {                            //v tem primeru ze poznamo smer
    		int horizontalno = 0;
    		if (ladje[ciljamladjo][1] == ladje[ciljamladjo][3])     //preverimo, ce je smer horizontalna
    			horizontalno = 1;

    		if (horizontalno == 1) {							    //Streljamo na horizontalno orientirano ladjo
    			if (nasprotnikovo_morje[ladje[ciljamladjo][3]][ladje[ciljamladjo][4] + 1] == 0 && (ladje[ciljamladjo][4] + 1) < 10) {		    //Streljamo desno desno
    				koordinata[0] = ladje[ciljamladjo][3];
    				koordinata[1] = ladje[ciljamladjo][4] + 1;
    			} else if (nasprotnikovo_morje[ladje[ciljamladjo][1]][ladje[ciljamladjo][2] - 1] == 0 && (ladje[ciljamladjo][2] - 1) > -1) {	//Streljamo levo levo
    				koordinata[0] = ladje[ciljamladjo][1];
    				koordinata[1] = ladje[ciljamladjo][2] - 1;
    			}
//    			else {      //za preverjanje napak
//                    printf("B\n");
//    			}
    		} else {										        //Streljamo na vertikalno orientirano ladjo
    			if (nasprotnikovo_morje[ladje[ciljamladjo][1] - 1][ladje[ciljamladjo][2]] == 0 && (ladje[ciljamladjo][1] - 1) > -1) {		    //Streljamo gor gor
    				koordinata[0] = ladje[ciljamladjo][1] - 1;
    				koordinata[1] = ladje[ciljamladjo][2];
    			} else if (nasprotnikovo_morje[ladje[ciljamladjo][3] + 1][ladje[ciljamladjo][4]] == 0 && (ladje[ciljamladjo][3] + 1) < 10) {	//Streljamo dol dol
    				koordinata[0] = ladje[ciljamladjo][3] + 1;
    				koordinata[1] = ladje[ciljamladjo][4];
    			}
//    			else {      //za preverjanje napak
//                    printf("A\n");
//    			}
    		}
    	}
    }

    /*                      //to je bilo prvotno ugibanje
    if (ladje_prejzadeta) {
        koordinata[0] = ladje_prejsnjiposkus[0];
        koordinata[1] = ladje_prejsnjiposkus[1] + 1;  //desno
        if (koordinata[1] > 9)
            koordinata[1] = rand() % 10;
    }
	*/

    ladje_prejsnjiposkus[0] = koordinata[0];        //tukaj se zapiše sedanji poskus, ki ga bomo uporabili v naslenjem poskusu
    ladje_prejsnjiposkus[1] = koordinata[1];

    //printf("\nUgibam na: %d %d\n", koordinata[0], koordinata[1]);         //tukaj je bil se izpis ugibanja
    //getchar();
//for (i=0;i<10;i++){
//    for(j=0;j<10;j++){
//        printf("%2d",nasprotnikovo_morje[i][j]);
//    }
//    printf("\n");
//}
//printf("------------------\n");
    return;
}

void ladje_obnovi(int koordinata[2], int zadeta) {
    //Tukaj se preveri, ce smo prejsni poskus zadeli. To nam postavi vrednost na spremenljivko s katero operiramo v funkciji ugibanje.
     if (zadeta) {
        ladje_prejzadeta = 1;
    } else {
        ladje_prejzadeta = 0;
    }
}

void ladje_nasprotnik(int koordinata[2]) {
    // sem pride dodatna logika po nasprotnikovem poskusu in obnavljanju stanja
}
