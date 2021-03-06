/**
 * @file      partie.c
 * @author    alpha-snake
 * @version   1
 * @date      16/05/2016
 * @brief     Toutes les fonctions permettant de créer et lancer une partie.
 * @details   ---
 */

#include "partie.h"

#include "bonus.h"
#include "affichage.h"
#include "ia.h"
#include "collisions.h"
#include "score.h"
#include <string.h>
#include <glib.h>
#include "config.h"

/**
 * @brief      La structure de la map.
 *
 * @use Map
 * @param[in]  width       La largeur de la map.
 * @param[in]  height      La hauteur de la map.
 */
struct _Map
{
    int width;
    int height;
};

/**
 * @brief      La structure d'une partie.
 *
 * @use Partie
 * @param[in]  btab         Tableau de bonus.
 * @param[in]  player       Le snake à jouer.
 * @param[in]  collisions   Le gestionnaire de collisions.
 * @param[in]  affichage    L'affichage de la partie.
 * @param[in]  en_cours     1 si la partie est en cours, 0 sinon.
 * @param[in]  config       Les configurations de la partie.
 * @param[in]  duree        Le nombre de déplacement effectué depuis le debut de la partie.
 */
struct _Partie
{


    //Bonus *nourriture;
    TabBonus *btab; // pour faire cour b = bonus  mais pas correct visuellement
    List *bonuseffect;
    Snake *player;
    TabSnakes *tab; // Il y a un probléme avec ce nom je voulais faire cour pour avoir à faire partie->tab−>snakes

    GestionCollisions *collisions;

    Affichage *affichage;

    gboolean en_cours;

    Map *map;

    Config *config;

    int duree; //Nombre de déplacement qui se sont effectué depuis le debut de la partie
};
/**
Snake * partie_snake(Partie *p)
{
    return p->snake;
}
void partie_set_snake(Partie *p,Snake *s)
{
    p->snake = s;
}
 Snake * partie_schlanga(Partie *p)
{
    return p->schlanga;
}
void partie_set_schlanga(Partie *p,Snake *s)
{
    p->schlanga = s;
}

 **/

/**
 * @brief   Permet d'accéder au tableau de snakes de la partie.
 *
 * @param[in]  p     La partie en cours.
 *
 * @return  Renvoie un tableau de snakes.
 */
TabSnakes * partie_tab(Partie *p)
{
    return p->tab;
}


/**
 * @brief   Permet d'accéder au joueur de la partie.
 *
 * @param[in]  p     La partie en cours.
 *
 * @return  Renvoie le snake du joueur.
 */
Snake * partie_player(Partie *p)
{
    return p->player;
}

/**
 * @brief   Permet de désigner un snake pour le joueur.
 *
 * @param[in]  p     La partie en cours.
 * @param[in]  s     Le snake.
 */
void partie_set_player(Partie *p,Snake *s)
{
    p->player = s;
}

/**
 * @brief   Permet d'accéder au tableau de bonus de la partie.
 *
 * @param[in]  p     La partie en cours.
 *
 * @return  Renvoie un tableau de bonus.
 */
TabBonus * partie_tab_bonus(Partie *p)
{
    return p->btab;
}

/**

 void partie_set_bonus(Partie *p,Bonus *s)
{
    p->nourriture = s;
}**/


/**
 * @brief   Crée le plateau d'une partie.
 *
 * @param[in]    width  La largeur du plateau en cases.
 * @param[in]    height La hauteur du plateau en cases.
 *
 * @return  Le plateau alloué.
 */
Map *create_map(int width, int height)
{
    Map *res;

    res = malloc(sizeof(Map));
    res->width = width;
    res->height = height;

    return res;
}

/**
 * @brief   Libère la mémoire consommée par un plateau.
 *
 * @param[in]    map    Le plateau à libérer.
 */
void free_map(Map *map)
{
    free(map);
}

/**
 * @brief   Permet d'obtenir la largeur d'un plateau.
 *
 * @param[in]    map    Un plateau.
 *
 * @return  La largeur du plateau.
 */
int map_width(Map *map)
{
    return map->width;
}

/**
 * @brief   Permet d'obtenir la hauteur d'un plateau.
 *
 * @param[in]    map    Un plateau.
 *
 * @return  La hauteur du plateau.
 */
int map_height(Map *map)
{
    return map->height;
}


/**
 * @brief   Crée une partie. Il faut appeler init_partie pour initaliser la
 *          partie.
 *
 * @return  La partie allouée.
 */
Partie *create_partie()
{
    Partie *res;

    res = malloc(sizeof(Partie));
    res->bonuseffect = NULL;
    res->btab = NULL;
    res->tab = NULL;
    res->map = NULL;
    res->affichage = NULL;
    res->collisions = NULL;
    res->config = NULL;

    return res;
}


/**
 * @brief   Permet de changer les configurations de la partie.
 *
 * @param[in]  p     La partie en cours.
 * @param[in]  c     COnfigurations de la partie.
*/
void partie_set_config(Partie * p,Config * c)
{
    p->config = c;
}

/**
 * @brief   Permet d'accéder aux configurations de la partie.
 *
 * @param[in]  p     La partie en cours.
 *
 * @return Renvoie les configurations de la partie.
*/
Config *partie_config(Partie * p)
{
    return p->config;
}

/**
 * @brief   Libère la mémoire consommée par une partie.
 *
 * @param[in]    partie La partie à supprimer.
 */
void free_partie(Partie *partie)
{
    free_affichage(partie->affichage);
    free_map(partie->map);
    free_gestion_collisions(partie->collisions);
    free_tab_snakes(partie->tab);
    free_tab_bonus(partie->btab);
    //TODO FREE_BONUSEFFECT
    free_list(partie->bonuseffect);
    free(partie);
}


/**
 * @brief   Permet d'obtenir le plateau d'une partie.
 *
 * @param[in]   partie  Une partie.
 *
 * @return  Le plateau de la partie.
 */
Map *partie_map(Partie *partie)
{
    return partie->map;
}

/**
 * @brief   Permet d'obtenir la durée d'une partie.
 *
 * @param[in]   partie  Une partie.
 *
 * @return  La durée depuis le début de la partie.
 */
int partie_duree(Partie *partie)
{
    return partie->duree;
}

/**
 * @brief   Permet de set la durée d'une partie.
 *
 * @param[in]   partie  Une partie.
 * @param[in]   duree   La nouvelle durée partie.
 *
 * @return  La durée depuis le début de la partie.
 */
int partie_set_duree(Partie *partie, int duree)
{
    return partie->duree = duree;
}

/**
 * @brief   Retourne le GStrind à afficher lorsqu'on demande les scores
 *
 * @return  etourne le GStrind à afficher lorsqu'on demande les scores
 */
GString *get_gstring_score()
{
    GString *res = g_string_new("\n\n === Top 10 === \n");
    List *tab_scores = get_table_scores();
    List *tab_trie = tri_max(tab_scores);
    Node n;
    void *s;
    char c_sc[100];
    char c_ligne[10];
    char c[2];
    int i=0;
    for(n = list_first_node(tab_trie); n != NULL && i<10; n = node_next(n))
    {
        sprintf(c_ligne, "%d) ", i+1);
        g_string_append(res, c_ligne);

        s = (Score *)node_elt(n);
        sprintf(c_sc, "%d", get_score(s));
        g_string_append(res, c_sc);
        g_string_append(res, " ");

        g_string_append(res, get_pseudo(s));
        g_string_append(res, " ");

        c[0] = get_gagnant(s);
        c[1] = '\0';
        g_string_append(res, c);
        g_string_append(res, "\n");
        i ++;
    }
    free_table_scores(tab_trie);
    return res;
}

/**
 * @brief   Fonction callback appelée quand un Snake entre en collision avec
 *          un Snake.
 *
 * @param[in]    snake  Le coupable.
 * @param[in]    obj2   La victime.
 * @param[in]    data   Un pointeur vers la partie en cours.
 */
static void collision_snake_vers_snake(Snake *snake, void *obj2, void *data)
{
    Partie *partie = data;


    if(partie->config->collision == 0) { // ON TERMINE LA FONCTION !! (A VOIR)
        return;
    }
    if(partie->config->type_partie == 2)
    {
        if(snake == partie->player) // on a perdu
        {
            ClutterScript *ui = affichage_ui(partie->affichage);
            ClutterActor *fin_partie;
            partie->en_cours = FALSE;
            GString *out = g_string_new(snake_pseudo(partie->player));
            g_string_append(out, "\n Perdu !");
            score_enregistre(partie->player, 'G');



            GString *gscore = get_gstring_score();
            g_string_append(out, gscore->str);

            clutter_text_set_text(
                    CLUTTER_TEXT(clutter_script_get_object(ui, "fin_partie_texte")),
                    out->str
            );

            fin_partie = CLUTTER_ACTOR(clutter_script_get_object(ui, "fin_partie"));
            clutter_actor_add_child(
                    CLUTTER_ACTOR(clutter_script_get_object(ui, "stage")),
                    fin_partie
            );

            clutter_actor_save_easing_state(fin_partie);
            clutter_actor_set_easing_duration(fin_partie, 250);
            clutter_actor_set_opacity(fin_partie, 255);
            clutter_actor_restore_easing_state(fin_partie);
        }
        else // un snake non joueur est mort
        {
            /**tab_snakes_remove_object(partie->tab,snake);
            gestion_collision_remove_object(partie->collisions,snake);
            free_snake(snake);
             **/
            Coord cp = snake_pos(snake);

            GRand * r = g_rand_new();
            gint32  rh = g_rand_int_range(r,1,partie->config->height-1);
            gint32  rw = g_rand_int_range(r,1,partie->config->width-1);
            Coord c;
            if(rh%4 == 0)
            {
                c = coord_from_xy(0,rh);
            }
            else if(rh%4 ==1)
            {
                c = coord_from_xy(rw,partie->config->height);
            }
            else if(rh%4 ==2)
            {
                c = coord_from_xy(partie->config->width,rh);
            }
            else
            {
                c = coord_from_xy(rw,0);
            }
            int i ;
            int l = snake_longueur(snake) - partie->config->taille_bot;
            for (i = 0; i < l; ++i) {
                free(list_pop_last(snake_liste_snake(snake)));

            }
            snake_set_longueur(snake,partie->config->taille_bot);
            snake_set_pos(snake,c,partie->config);
            if(partie->config->advanced_bonus)
            {
                Bonus * b = bonus_advanced_new(map_width(partie->map),map_height(partie->map));

                partie_add_bonus(partie,b);

            }
            else
            {
                partie_add_bonus(partie,bonus_init((cp.x+1)%(partie->config->width-1),(cp.y+1)%(partie->config->height-1)));

            }
            printf("[SCHLANGA] Dead  - auto respawn\n");
        }
    }
    else
    {
        ClutterScript *ui = affichage_ui(partie->affichage);
        ClutterActor *fin_partie;
        partie->en_cours = FALSE;
        GString *out = g_string_new(snake_pseudo(partie->player));



        if(snake == partie->player) // Si le snake en paramètre est le joueur on a perdu
        {
            g_string_append(out, "\n Perdu !");
            score_enregistre(partie->player, 'G');
        }
        else
        {
            g_string_append(out, "\n Gagné !");
            score_enregistre(partie->player, 'P');
        }

        GString *gscore = get_gstring_score();
        g_string_append(out, gscore->str);

        clutter_text_set_text(
                CLUTTER_TEXT(clutter_script_get_object(ui, "fin_partie_texte")),
                out->str
        );

        fin_partie = CLUTTER_ACTOR(clutter_script_get_object(ui, "fin_partie"));
        clutter_actor_add_child(
                CLUTTER_ACTOR(clutter_script_get_object(ui, "stage")),
                fin_partie
        );

        clutter_actor_save_easing_state(fin_partie);
        clutter_actor_set_easing_duration(fin_partie, 250);
        clutter_actor_set_opacity(fin_partie, 255);
        clutter_actor_restore_easing_state(fin_partie);
    }

}
/**
 * @brief   Libère la mémoire consommée par un bonus avancé.
 *
 * @param[in]    p      La partie en cours.
 * @param[in]    b      Le bonus à supprimer.
 */
void remove_advanced_bonus(Partie *p, Bonus *b)
{

    gestion_collision_remove_object(p->collisions, b);

    tab_bonus_remove_object(p->btab, b);
    printf("tab b rm ok\n");
    gestion_collision_remove_object(p->collisions, b);
    printf("col rm ok\n");
    affichage_remove_bonus_actor(p->affichage, b);

    printf("affichage rm ok\n");
}

/**
 * @brief   Fonction callback appelée quand un Snake entre en collision avec
 *          la nourriture.
 *
 * @param[in]    snake  Le coupable.
 * @param[in]    obj2   La victime.
 * @param[in]    data   Un pointeur vers la partie en cours.
 */
static void collision_snake_vers_nourriture(Snake *snake, void *obj2, void *data)
{
    Bonus *nourriture = obj2;
    Partie *partie = data;
    bonus_eat_callback(partie, snake, nourriture);
    BonusEffectApply * bea =bonus_effect_apply_init(snake,nourriture,BONUS_TIME);
    list_add_last(partie->bonuseffect,bea);
}

/**
 * @brief   Ajoute des bonus à la partie.
 *
 * @param[in]   partie  La partie en cours.
 * @param[in]   bonus   Le bonus à ajouter.
 */
void partie_add_bonus(Partie *partie, Bonus * bonus)
{
    tab_bonus_add_object(partie->btab,bonus);
    int j;
    CollisionObject*  co_bonus = gestion_collision_add_object(partie->collisions,
                                               bonus,
                                               COLLISION_BONUS);
    for (j = 0; j < partie->tab->nb_snakes ; ++j)
    {
        collision_object_add_collision(
                co_bonus,
                create_collision(partie->tab->snakes[j], collision_snake_vers_nourriture, partie)
        );
    }
    // On choisit une couleur
    GRand * randg = g_rand_new();
    gint32  r = g_rand_int_range(randg,0,360);

    ClutterColor * color = clutter_color_alloc();
    clutter_color_from_hls(color,(r)%360,0.4,1);
    affichage_add_bonus(partie->affichage, bonus, color,partie->config);

}

/**
 * @brief   Initialise une partie déjà allouée.
 *
 * @param[in]    partie Une partie.
 * @param[in]    ui     Le ClutterScript de la fenêtre.
 * @param[in]    width  La largeur du plateau.
 * @param[in]    height La hauteur du plateau.
 */
void init_partie(Partie *partie, ClutterScript *ui)
{

    int nb_snakes = partie->config->nb_snakes;
    int width = partie->config->width;
    int height = partie->config->height;
    int nb_bonus = partie->config->nb_bonus;
    int advanced_bonus = partie->config->advanced_bonus;

    CollisionObject **co_snakes = malloc(nb_snakes*sizeof(CollisionObject *));

    CollisionObject **co_bonus = malloc((nb_bonus+advanced_bonus)*sizeof(CollisionObject *)); // ON DIT QU'Il Y A QU'UN BONUS  TODO à changer

    CollisionObject *co_map;

    partie->bonuseffect = create_list();

    partie->map = create_map(width, height);
    partie->en_cours = TRUE;
    partie->duree = 0;

    // Initialisation du tableau de snake
    partie->tab = create_tab_snakes();

    // on ajoute le 1er snake comme player
    Snake * snk  = create_snake(
            partie->config->taille_snake,
            coord_from_xy(partie->config->width/2, partie->config->height/2),
            DROITE
    );
    tab_snakes_add_object(partie->tab,snk);
    int i;
    GRand * ra = g_rand_new();

    for (i = 1; i < nb_snakes; ++i)
    {
        int cw = partie->config->width*2/10;
        int ch = partie->config->width*2/10;
        gint32  rh = g_rand_int_range(ra,1+ch,partie->config->height-ch-1);
        gint32  rw = g_rand_int_range(ra,1+cw,partie->config->width-cw-1);
        Coord c;
        GRand * r = g_rand_new();


        if(rh%4 == 0)
        {
            c = coord_from_xy(1+cw,(rh-ch)%partie->config->height);
        }
        else if(rh%4 ==1)
        {
            c = coord_from_xy((rw-cw),partie->config->height-ch);
        }
        else if(rh%4 ==2)
        {
            c = coord_from_xy(partie->config->width-cw,(rh-ch)%partie->config->height);
        }
        else
        {
            c = coord_from_xy((rw-cw)%partie->config->width,0+ch);
        }

        snk  = create_snake_bot(
                partie->config->taille_bot,
                c,
                DROITE,
                "ia1"
        );
        tab_snakes_add_object(partie->tab,snk);

    }



    partie->player = partie->tab->snakes[0]; // On définit le player comme le 1er élément du tableau


    partie->btab = create_tab_bonus();

    // On crée pour l'instant qu'un bonus !

    if(partie->config->advanced_bonus != 0)
    {
        for (i = 0; i < nb_bonus; ++i) {
            tab_bonus_add_object(partie->btab, bonus_advanced_new(width, height));
        }
    }
    else{
        for (i = 0; i < nb_bonus; ++i) {
            tab_bonus_add_object(partie->btab, bonus_new(width, height));
        }

    }



    partie->collisions = create_gestion_collisions();// collisions.c

    for (i = 0; i < partie->tab->nb_snakes ; ++i)
    {
        co_snakes[i] = gestion_collision_add_object(partie->collisions, partie->tab->snakes[i],
                                                    COLLISION_SNAKE);
    }


    for (i = 0; i < partie->btab->nb_bonus; ++i) {
        co_bonus[i] = gestion_collision_add_object(partie->collisions,
                                                     partie->btab->bonus[i],
                                                     COLLISION_BONUS);
    }

    co_map = gestion_collision_add_object(partie->collisions, partie->map,
                                          COLLISION_MAP);

    int j;
    for (i = 0; i < partie->tab->nb_snakes ; ++i)
    {
        for (j = 0; j < partie->tab->nb_snakes ; ++j)
        {
            collision_object_add_collision(
                    co_snakes[i],
                    create_collision(partie->tab->snakes[j], collision_snake_vers_snake, partie)// collisions.c
            );

        }

        for (j = 0; j < partie->btab->nb_bonus ; ++j)
        {
            collision_object_add_collision(
                    co_bonus[j],
                    create_collision(partie->tab->snakes[i], collision_snake_vers_nourriture, partie)
            );
        }
        collision_object_add_collision(
                co_map,
                create_collision(partie->tab->snakes[i], collision_snake_vers_snake, partie)
        );
    }


    partie->affichage = create_affichage();// affichage.c
    init_affichage(partie->affichage, ui, partie, width, height);// affichage.c

    // On choisit une couleur
    GRand * randg = g_rand_new();
    gint32  r = g_rand_int_range(randg,0,360);
    int pas = 360/(partie->tab->nb_snakes);
    for (i = 0; i < partie->tab->nb_snakes ; ++i)
    {
        ClutterColor * color = clutter_color_alloc();
        clutter_color_from_hls(color,(r+pas*i)%360,0.4,1); // Puis le couleurs sont complémentaires
        affichage_add_snake(partie->affichage, partie->tab->snakes[i], color);// affichage.c
    }

    int pasb = 360/(partie->btab->nb_bonus);
    for (i = 0; i < partie->btab->nb_bonus ; ++i)
    {
        ClutterColor * color = clutter_color_alloc();
        clutter_color_from_hls(color,(r+pasb*i)%360,0.4,1);
        affichage_add_bonus(partie->affichage, partie->btab->bonus[i],  color,partie->config);
    }

    g_timeout_add(partie->config->interval_timeout, timeout_tick_cb, partie);

    free(co_snakes);
    free(co_bonus);
}


/**
 * @brief   Initialise le pseudo.
 *
 * @param[in]    partie     Une partie.
 * @param[in]    pseudo     Le pseudo.

 */
void init_pseudo(Partie *p, char *pseudo)
{
    if(strlen(pseudo) > 0)
    {
        snake_set_pseudo(p->player, pseudo);
    }
    else
    {
        snake_set_pseudo(p->player, "Anonyme");
    }
}

void bonus_reposition(Partie * partie)
{
    int i,j;
    Node n;
    Coord * cn;
    for (i = 0; i < partie->btab->nb_bonus; ++i)
    {

        for (j = 0; j < partie->tab->nb_snakes; ++j)
        {
            for(n = list_first_node(snake_liste_snake(partie->tab->snakes[j])); n != NULL; n = node_next(n))
            {
                cn = node_elt(n);
                if(coord_egales(*cn,bonus_coord(partie->btab->bonus[i])))
                {
                    bonus_update(partie->btab->bonus[i],map_width(partie->map),map_height(partie->map));
                }
            }
        }
        for (j = 0; j < partie->btab->nb_bonus; ++j)
        {
            if(i!=j)
            {
                if(coord_egales(bonus_coord(partie->btab->bonus[j]),bonus_coord(partie->btab->bonus[i])))
                {
                    bonus_update(partie->btab->bonus[i],map_width(partie->map),map_height(partie->map));
                }

            }
        }
    }
}
/**
 * @brief Fonction callback appelée à intervalles réguliers.
 *
 * @param[in]    data   Le SnakeActor du snake.
 */
gboolean timeout_tick_cb(gpointer data)
{
    Partie *partie = data;

    int i, t, r;
    for (i = 0; i < partie->tab->nb_snakes; ++i)
    {
        t = partie->duree;
        r = partie->config->interval_scale/snake_vitesse(partie->tab->snakes[i]);
        if(t % r == 0)
        {
            if(snake_is_bot(partie->tab->snakes[i]))
            {
                snake_set_direction_ia(partie->tab->snakes[i],partie, snake_script_name(partie->tab->snakes[i]));
                snake_forward(partie->tab->snakes[i]);
            }
            else
            {
                // TODO generaliser les forward ?  la direction se choisit comment ?
                snake_forward(partie->player);
            }
        }
    }

    /**for(i=0; i< partie->btab->nb_bonus;++i)
    {
        if(bonus_time_remaining(partie->btab->bonus[i]) == 0)
        {
            bonus_eat_callback()
        }
        else
        {
            bonus_decrease_time_remaining(partie->btab->bonus[i]);
        }
    }**/

    Node ls = list_first_node(partie->bonuseffect);
    BonusEffectApply * bea = NULL;
    int nombre_de_bonus_actif = 0;
    while( ls != NULL )
    {

         bea = node_elt(ls);
        // Regarde si le temps est écoulé et appel la fct callback sinon décroit le temps
        if(bonus_time_remaining(bea) == 0)
        {

            //   callback
            bonus_end_callback(partie,bonus_effect_apply_snake(bea),bonus_effect_apply_bonus(bea));
            //  Delete node
            list_delete_node(partie->bonuseffect,ls);
        }
        else
        {
            nombre_de_bonus_actif++;
            bonus_decrease_time_remaining(bea);
        }
        ls = node_next(ls);
    }

    gestion_collisions_check(partie->collisions);
    bonus_reposition(partie);
    if (partie->en_cours)
    {
        affichage_update(partie,partie->affichage);
        partie->duree += 1;
    }

    return partie->en_cours;
}
