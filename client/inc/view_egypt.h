#ifndef VIEW_EGYPT_H
#define VIEW_EGYPT_H

#include <gtk/gtk.h>
#include "libmx.h"
#include "view_sign_in.h"
#include "view_tools.h"
#include "quiz.h"
#include "resources.h"

typedef struct s_egypt_elements {
    GtkWidget **buttons;
    char **words;
    int word_count;
    int page;
    char *message;
    GtkWidget *entry;
}               t_egypt_elements;

t_egypt_elements *create_egypt_elements();
void view_egypt(t_current_window_info *current_layout_info);
char **get_words_from_file(char *file_name);
void set_words_on_buttons(t_egypt_elements *egypt_elements);
void refresh_words(GtkWidget *widget, t_egypt_elements *egypt_elements);
void add_word_to_message(GtkWidget *widget, t_egypt_elements *second_era_ellements);
void count_words(t_egypt_elements *egypt_elements);

t_egypt_elements *get_egypt_element();

#endif