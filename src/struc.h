/**
 * @file      struc.h
 * @author    alpha-snake
 * @version   1
 * @date      25/02/2016
 * @brief     Toutes les fonctions permettant d'utiliser la structure et de jouer
 * @details   ---
 */



#ifndef _STRUCT_
#define _STRUCT_

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "config.h"
/**
 * @brief    liste de Snake
 */
//typedef struct maillon_snake *ListeSnake;



typedef struct _snake Snake;
typedef struct _tabsnakes TabSnakes;

/**
 * @brief      La structure du tableau de Snake.
 *
 * @use TabSnakes
 * @param[in]  snakes 		    Le tableau de tout les snakes.
 * @param[in]  nb_snakes  	    Le nombre de snake.
 * @param[in]  taille_snakes	La taille en mémoire.
 */
struct _tabsnakes
{
	Snake **snakes; // pour acceder au tableau de snake ts->snakes
	int nb_snakes;
	int taille_snakes;
};


/**
 * @brief      La structure des coordonnées.
 *
 * @use Coord
 * @param[in]  x		Abscisses.
 * @param[in]  y  	    Ordonnées.
 */
typedef struct
{
	int x;
	int y;
} Coord;

typedef enum
{
	/* Sens trigo */
	GAUCHE = 180, DROITE = 0, BAS = 270, HAUT = 90, ARRET = -1
} Direction;

/* Fonction de base de coord */

Coord coord_from_xy(int x,int y);
void print_coord(Coord c);
int coord_egales(Coord c1, Coord c2);
double coord_distance(Coord c1, Coord c2);

/*Fonctions de base de TabSnakes*/

TabSnakes *create_tab_snakes();
void free_tab_snakes(TabSnakes *ts);
Snake *tab_snakes_add_object(TabSnakes *ts, Snake *obj);
void tab_snakes_remove_object(TabSnakes *ts, Snake *obj);
int tab_snakes_length(TabSnakes *ts);
int tab_snakes_memory_length(TabSnakes *ts);

/* Fonctions de base de Snake */

Snake *create_snake(int longueur, Coord c, Direction dir);
Snake *create_snake_bot(int longueur, Coord c, Direction dir,char * str);
void free_snake(Snake *snake);
void print_snake(Snake *snake);

Coord snake_pos(Snake *snake);
int snake_longueur(Snake *snake);
void snake_set_longueur(Snake *snake,int nl);
int snake_indic_duree(Snake *snake);
void snake_set_indic_duree(Snake *snake, int d);
int snake_num_ia(Snake *snake);
void snake_set_num_ia(Snake *snake, int n);
int snake_vitesse(Snake *snake);
void snake_set_vitesse(Snake *snake, int v);
List *snake_liste_snake(Snake *snake);
Node snake_dernier(Snake *snake);
Node snake_premier(Snake *snake);
Direction snake_direction(Snake *snake);
int snake_set_direction(Snake *snake, Direction dir);

int snake_set_pos(Snake *snake,Coord pos,Config * config );
void snake_set_liste(Snake *snake, List *ls);
char *snake_pseudo(Snake *snake);
void snake_set_pseudo(Snake *snake, char *pseudo);

void snake_forward(Snake *snake);

void snake_increase(Snake *snake);


int snake_is_bot(Snake *snake);
char * snake_script_name(Snake * snake);

#endif