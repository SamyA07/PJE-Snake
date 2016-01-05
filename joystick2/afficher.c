/* This file is part of rflpc. Copyright 2010-2011 Michael Hauspie
 *
 * rflpc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rflpc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rflpc.  If not, see <http://www.gnu.org/licenses/>.
 */
/*
  Author: Michael Hauspie <michael.hauspie@univ-lille1.fr>
  Created:
  Time-stamp: <2014-05-30 09:55:41 (mickey)>
*/
  /*
<generator>
    <handlers init="doInit" doGet="doGet"/>
    <args>
     <arg name="chiffre" type="str" size="10"/>
     <arg name="score" type="str" size="10"/>
     <arg name="prenom" type="str" size="10"/>
     <arg name="niveau" type="uint8"/>
    </args>
</generator>
*/
#include <rflpc17xx/rflpc17xx.h>
#include "nhd_spi_lcd.h"
#include "lettreChiffre.h"

#define WIDTH 128
#define HEIGHT 32

#define BUFFER_SIZE (WIDTH * (HEIGHT >> 3))

uint8_t buffer[BUFFER_SIZE];
static int compteur = 0;
static int ligne = 0;

#define COORD_TO_BYTE(x,y) ((((y)>>3) * WIDTH) + (x))
#define COORD_TO_BIT(x,y) (((y) & 7))

void set_pixel(uint8_t x, uint8_t y)
{
   int byte_idx = COORD_TO_BYTE(x,y);
   buffer[byte_idx] |= (1 << COORD_TO_BIT(x,y));
}
void clr_pixel(uint8_t x, uint8_t y)
{
   int byte_idx = COORD_TO_BYTE(x,y);
   buffer[byte_idx] &= ~(1 << COORD_TO_BIT(x,y));
}

void clr_buffer(void)
{
   memset(buffer, 0, BUFFER_SIZE);
}

void clr_score(void)
{
    int k;
    for(k = WIDTH ; k < BUFFER_SIZE ; k++)
        buffer[k]=0;
}

void afficher(int tab[]){
	int i,j,k;
	for(k=0;k<40;k++){
		i = k%5 + compteur;
        j = k/5 + ligne;
		if(tab[k] == 1)set_pixel(i,j);
	}
    //nhd_spi_lcd_display_buffer(buffer);
    compteur+=8;
}

static char doInit(void){
    rflpc_uart_init(RFLPC_UART0);
    nhd_spi_lcd_init(NHD_MAKE_SIZE(WIDTH,HEIGHT), MBED_DIP6, MBED_DIP8, MBED_DIP11, RFLPC_SPI1);
    rflpc_led_init();
    clr_buffer();
    nhd_spi_lcd_display_buffer(buffer);
    return 0;
}

static char doGet(struct args_t *args) {
    clr_score();
    compteur = 0;
    ligne = 0;
    if(args->niveau) {
        int lvl = args->niveau;
        switch(lvl){
            case 1 : 
                rflpc_led_clr(RFLPC_LED_2);
                rflpc_led_clr(RFLPC_LED_3);
                rflpc_led_clr(RFLPC_LED_4); 
                rflpc_led_set(RFLPC_LED_1);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_1);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_2);
                rflpc_gpio_set_pin(RFLPC_PIN_P2_3);
                break;
            case 2 : 
                rflpc_led_clr(RFLPC_LED_3);
                rflpc_led_clr(RFLPC_LED_4); 
                rflpc_led_set(RFLPC_LED_2);
                rflpc_led_set(RFLPC_LED_1); 
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_1);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_2);
                rflpc_gpio_set_pin(RFLPC_PIN_P2_3);
                break;
            case 3 : 
                rflpc_led_clr(RFLPC_LED_4); 
                rflpc_led_set(RFLPC_LED_3);
                rflpc_led_set(RFLPC_LED_2);
                rflpc_led_set(RFLPC_LED_1);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_1);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_3); 
                rflpc_gpio_set_pin(RFLPC_PIN_P2_2);
                break;
            case 4 : 
                rflpc_led_set(RFLPC_LED_4);
                rflpc_led_set(RFLPC_LED_3);
                rflpc_led_set(RFLPC_LED_2);
                rflpc_led_set(RFLPC_LED_1); 
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_3);
                rflpc_gpio_clr_pin(RFLPC_PIN_P2_2);
                rflpc_gpio_set_pin(RFLPC_PIN_P2_1);
                break;
            default:break;            
        }
    }
    if(args->prenom) {
        int taille;
        char * lettres ;
        lettres = args->prenom;
        for(taille = 0 ; lettres[taille]!='\0' ; taille++);        
        int i;
        for(i = 0 ; i < taille ; i++){
          switch(lettres[i]){
            case 'a' : afficher(A); break;
            case 'b' : afficher(B); break;
            case 'c' : afficher(C); break;
            case 'd' : afficher(D); break;
            case 'e' : afficher(E); break; 
            case 'f' : afficher(F); break; 
            case 'g' : afficher(G); break; 
            case 'h' : afficher(H); break; 
            case 'i' : afficher(I); break; 
            case 'j' : afficher(J); break; 
            case 'k' : afficher(K); break; 
            case 'l' : afficher(L); break; 
            case 'm' : afficher(M); break; 
            case 'n' : afficher(N); break; 
            case 'o' : afficher(O); break; 
            case 'p' : afficher(P); break; 
            case 'q' : afficher(Q); break; 
            case 'r' : afficher(R); break; 
            case 's' : afficher(S); break; 
            case 't' : afficher(T); break; 
            case 'u' : afficher(U); break; 
            case 'v' : afficher(V); break; 
            case 'w' : afficher(W); break; 
            case 'x' : afficher(X); break; 
            case 'y' : afficher(Y); break; 
            case 'z' : afficher(Z); break;
            case ' ' : afficher(espace); break;
            default:break;
          }
        }
    }
    if(args->score) {
        ligne +=15;
        compteur = 0;
        afficher(S);
        afficher(C);
        afficher(O);
        afficher(R);
        afficher(E);
        afficher(deuxPoints);
        afficher(espace);
        int taille2;
        char * score ;
        score = args->score;
        for(taille2 = 0 ; score[taille2]!='\0' ; taille2++); 
        int j;
        for(j = 0 ; j < taille2 ; j++){       
            switch(score[j]){
                case '0' : afficher(zero); break;
                case '1' : afficher(un); break;
                case '2' : afficher(deux); break;
                case '3' : afficher(trois); break;
                case '4' : afficher(quatre); break;
                case '5' : afficher(cinq); break;
                case '6' : afficher(six); break;
                case '7' : afficher(sept); break;
                case '8' : afficher(huit); break;
                case '9' : afficher(neuf); break;
                default:break;
            }
        }
    }   

    nhd_spi_lcd_display_buffer(buffer);
    /*while (1)
       rflpc_idle;
    return 0;
    */
    return 0;
}
