/**
 * @file      alpha-field.h
 * @author    alpha-snake
 * @version   1
 * @date      16/05/2016
 * @brief     Classe AlphaField pour pouvoir rentrer du texte sur le menu.
 * @details   ---
 */
#include <clutter/clutter.h>

#ifndef ALPHA_SNAKE_ALPHA_FIELD_H
#define ALPHA_SNAKE_ALPHA_FIELD_H

#define ALPHA_TYPE_FIELD (alpha_field_get_type())
#define ALPHA_FIELD(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), ALPHA_TYPE_FIELD, AlphaField))
#define ALPHA_IS_FIELD(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), ALPHA_TYPE_FIELD))
#define ALPHA_FIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), ALPHA_TYPE_FIELD,AlphaFieldClass))
#define ALPHA_IS_FIELD_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), ALPHA_TYPE_FIELD))
#define ALPHA_FIELD_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS((obj), ALPHA_TYPE_FIELD, AlphaFieldClass))

typedef struct _AlphaField AlphaField;
typedef struct _AlphaFieldClass AlphaFieldClass;

struct _AlphaField
{
    ClutterActor parent_instance;

    ClutterActor *text;
    
    ClutterImage *img_hd;
    ClutterImage *img_d;
    ClutterImage *img_bd;
    ClutterImage *img_b;
    ClutterImage *img_bg;
};

struct _AlphaFieldClass
{
    ClutterActorClass parent_class;
};

GType alpha_field_get_type();
gchar *alpha_field_get_text(AlphaField *self);

#endif //ALPHA_SNAKE_ALPHA_FIELD_H
