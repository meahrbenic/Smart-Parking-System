/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
*/
#include "mbed.h"
#include "stdio.h"
#include "SPI_TFT_ILI9341.h"
#include "string"
#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"
#include "font_big.h"

SPI_TFT_ILI9341 TFT(PTD2,PTD3,PTD1,PTD0,PTE0,PTE1,"TFT");

DigitalOut red1(D2);
DigitalOut red2(D3);
DigitalOut red3(D4);
DigitalOut red4(D5);

DigitalIn kolona1(D6);
DigitalIn kolona2(D7);
DigitalIn kolona3(D8);
DigitalIn kolona4(D9);

int brojac = -1;
char rez;

char dozvola[18] = "Ulaz je slobodan!";
char zabrana[19] = "Ulaz je zabranjen!";
char greska1[16] = "Pogresna sifra!";
char greska2[18] = "Pokusajte ponovo.";

char uneseno[4] = {'0', '0', '0', '0'}; 

//Function prototypes
bool provjeriSifru();
void unosNaTastaturu();
void defaultScreen();
void promijeniObavijest();
void greska();
int main();

//Functions
bool provjeriSifru() {
    if(uneseno[0] == '4' && uneseno[1] == '2' &&
        uneseno[2] == '4' && uneseno[3] == '2') return true;

    return false;
}

void unosNaTastaturu() {
    if(brojac >= 3) brojac = -1;

    red1 = 0;
    red2 = 1;
    red3 = 1;
    red4 = 1;

    if(rez != '1' && kolona1 == 0 && kolona2 == 1 && kolona3 == 1 && kolona4 == 1) {
        rez = '1';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '2' && kolona1 == 1 && kolona2 == 0 && kolona3 == 1 && kolona4 == 1) {
        rez = '2';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '3' && kolona1 == 1 && kolona2 == 1 && kolona3 == 0 && kolona4 == 1) {
        rez = '3';
        brojac++;
        uneseno[brojac] = rez;
    }

    red1 = 1;
    red2 = 0;
    red3 = 1;
    red4 = 1;

    if(rez != '4' && kolona1 == 0 && kolona2 == 1 && kolona3 == 1 && kolona4 == 1) {
        rez = '4';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '5' && kolona1 == 1 && kolona2 == 0 && kolona3 == 1 && kolona4 == 1) {
        rez = '5';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '6' && kolona1 == 1 && kolona2 == 1 && kolona3 == 0 && kolona4 == 1) {
        rez = '6';
        brojac++;
        uneseno[brojac] = rez;
    }

    red1 = 1;
    red2 = 1;
    red3 = 0;
    red4 = 1;

    if(rez != '7' && kolona1 == 0 && kolona2 == 1 && kolona3 == 1 && kolona4 == 1) {
        rez = '7';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '8' && kolona1 == 1 && kolona2 == 0 && kolona3 == 1 && kolona4 == 1) {
        rez = '8';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '9' && kolona1 == 1 && kolona2 == 1 && kolona3 == 0 && kolona4 == 1) {
        rez = '9';
        brojac++;
        uneseno[brojac] = rez;
    }

    red1 = 1;
    red2 = 1;
    red3 = 1;
    red4 = 0;

    if(rez != '*' && kolona1 == 0 && kolona2 == 1 && kolona3 == 1 && kolona4 == 1) {
        rez = '*';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '0' && kolona1 == 1 && kolona2 == 0 && kolona3 == 1 && kolona4 == 1) {
        rez = '0';
        brojac++;
        uneseno[brojac] = rez;
    }
    if(rez != '#' && kolona1 == 1 && kolona2 == 1 && kolona3 == 0 && kolona4 == 1) {
        rez = '#';
        brojac++;
        uneseno[brojac] = rez;
    }
}

void defaultScreen() {
    TFT.claim(stdout);
    TFT.set_orientation(1);
    TFT.background(Red);
    TFT.cls();
    TFT.set_font((unsigned char*) Arial24x23);

    TFT.locate(5,5);
    TFT.foreground(Black);

    TFT.locate(30,100); 
    TFT._printf(zabrana, 18);
}

void promijeniObavijest() {
    TFT.claim(stdout);
    TFT.set_orientation(1);
    TFT.background(Green);
    TFT.cls();
    TFT.set_font((unsigned char*) Arial24x23);

    TFT.locate(5,5);
    TFT.foreground(Black);

    TFT.locate(30,100); 
    TFT._printf(dozvola, 18);
}

void greska() {
    TFT.claim(stdout);
    TFT.set_orientation(1);
    TFT.background(Red);
    TFT.cls();
    TFT.set_font((unsigned char*) Arial24x23);

    TFT.locate(5,5);
    TFT.foreground(Black);

    TFT.locate(30,75); 
    TFT._printf(greska1, 16);
    TFT.locate(30,125); 
    TFT._printf(greska2, 18);
}


int main() {
    defaultScreen();

    while(1) {
        unosNaTastaturu();
        if(provjeriSifru()) {

            promijeniObavijest();
            wait_us(5*1e6);
            defaultScreen();

            uneseno[0] = '0';
            uneseno[1] = '0';
            uneseno[2] = '0';
            uneseno[3] = '0';
        }
        else if(uneseno[3] != '0'){
            greska();
            uneseno[0] = '0';
            uneseno[1] = '0';
            uneseno[2] = '0';
            uneseno[3] = '0';
        }
    }
}

