#ifndef QUIZ_H
#define QUIZ_H

#include "protocol.h"
#include "view_tools.h"
#include "libmx.h"
#include "resources.h"
#include "quiz_requests.h"
#include "user_data.h"
#include "user_info.h"

typedef struct s_quiz_info {
    GtkBuilder *builder;
    cJSON *questions;
    char *correct_answer;
    GtkWidget *quiz_popover;
    int quiz_quiestions_number;
    int pop_opened;
}               t_quiz_info;

void set_quiz_on_button(GtkWidget *button);
// int set_quiz_from_file(cJSON **questions_arr, char *file_name);
gboolean quiz_button_clicked(GtkWidget *widget, t_quiz_info *quiz_info);
gboolean answer_clicked(GtkWidget *widget, t_quiz_info *quiz_info);
void show_quiz(cJSON* question_data);
// int *get_array_of_diff_rand(int size);

#endif
