#include "quiz.h"

static GtkWidget* quiz_question_label = NULL;
static GtkBuilder* quiz_builder = NULL;
static bool quiz_pop_opened = false;

int *get_array_of_diff_rand(int size) {
    int *elements = malloc(sizeof(int)*size);

    for (int i = 0; i < size; ++i)
        elements[i] = i;

    for (int i = size - 1; i > 0; --i) {
      int w = rand()%i;
      int t = elements[i];
    elements[i] = elements[w];
    elements[w] = t;
    }
    return elements;
}

void get_next_answer() {
    cJSON* random_question = NULL;
    if (!quiz_pop_opened) {
        cJSON* response = get_question_request(get_cookies());
        char* status = get_from_protocol_string(response, "STATUS");
        if (status != NULL && strcmp(status, "ERROR") != 0) {
            random_question = cJSON_Parse(get_from_protocol_string(response, "DATA"));
            char*  question_index = get_from_protocol_string(response, "QUESTION INDEX");
            if (get_from_protocol_string(get_cookies(), "QUESTION INDEX")) cJSON_DeleteItemFromObject(get_cookies(), "QUESTION INDEX");
            add_to_protocol_string(get_cookies(), "QUESTION INDEX", question_index);
        }
        cJSON_Delete(response);
    } else {
        if (get_from_protocol_string(get_cookies(), "QUESTION INDEX")) cJSON_DeleteItemFromObject(get_cookies(), "QUESTION INDEX");
        add_to_protocol_string(get_cookies(), "QUESTION INDEX", "-1");
    }
    show_quiz(random_question);
}
    
gboolean answer_clicked(GtkWidget *widget, t_quiz_info *quiz_info) {


    static int i = 0;

        // get question from server

        // random question = get question from server


    printf("iteration: %i\n", i++);

    if (quiz_pop_opened) {
        if (get_from_protocol_string(get_cookies(), "QUESTION INDEX") == NULL) return true;

        cJSON* response = check_answer_request(get_cookies(), (char*)gtk_button_get_label(GTK_BUTTON(widget)));
        if (get_from_protocol_string(get_cookies(), "QUESTION INDEX")) cJSON_DeleteItemFromObject(get_cookies(), "QUESTION INDEX");

        char* status = get_from_protocol_string(response, "STATUS");
        if (status != NULL && strcmp(status, "ERROR") != 0) {

            char* result = get_from_protocol_string(response, "DATA");

            if (strcmp(result, "CORRECT") == 0) {
                printf("correct answer\n");
            } else {
                // change answer
                printf("incorrect answer\n");
            }
            
        }
        quiz_pop_opened = false;
        get_next_answer();
    }

    return true;
}

// TODO: add show quiz function

gboolean quiz_button_clicked(GtkWidget *widget, t_quiz_info *quiz_info) {
    if(widget) {
        

        if (!quiz_pop_opened) {
            get_next_answer();
        } else {
            quiz_pop_opened = false;
        }

    } else {
        quiz_pop_opened = false;
    }
    return true;
}

void load_quiz_question_label() {
    quiz_builder        = gtk_builder_new_from_file(get_path_to_glade("quiz.glade"));
    quiz_question_label = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "quiz_label"));
}

void show_quiz(cJSON* question_data) {

    GtkWidget *answer_buttons[4];
    answer_buttons[0] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_1"));
    answer_buttons[1] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_2"));
    answer_buttons[2] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_3"));
    answer_buttons[3] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_4"));

    char *correct_answer = get_from_protocol_string(question_data, "CORRECT_ANSWER");

    int *rand_arr = get_array_of_diff_rand(4);
    gtk_label_set_text(GTK_LABEL(quiz_question_label), get_from_protocol_string(question_data, "QUESTION"));
    gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[0]]), get_from_protocol_string(question_data, "ANSWER_1"));
    gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[1]]), get_from_protocol_string(question_data, "ANSWER_2"));
    gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[2]]), get_from_protocol_string(question_data, "ANSWER_3"));
    gtk_button_set_label(GTK_BUTTON(answer_buttons[rand_arr[3]]), correct_answer);

    


    quiz_pop_opened = true;

}


void set_quiz_on_button(GtkWidget *button) {

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("quiz.css"), NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(cssProvider),
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);

    cJSON *quiz_questions;

    if (quiz_builder == NULL || quiz_question_label == NULL) {
        load_quiz_question_label();
    }

    // gtk_button_set_image (GTK_BUTTON (button), gtk_image_new_from_icon_name ("open-menu-symbolic", GTK_ICON_SIZE_BUTTON));

    GtkWidget *quiz_popover;
	GtkWidget *quiz_layout = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "quiz_layout"));
	
    quiz_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (quiz_popover), quiz_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), quiz_popover);
    gtk_popover_set_position(GTK_POPOVER(quiz_popover), GTK_POS_RIGHT);

    GtkWidget *answer_buttons[4];
    answer_buttons[0] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_1"));
    answer_buttons[1] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_2"));
    answer_buttons[2] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_3"));
    answer_buttons[3] = GTK_WIDGET(gtk_builder_get_object(quiz_builder, "answer_button_4"));

    g_signal_connect (G_OBJECT (answer_buttons[0]), "clicked", G_CALLBACK (answer_clicked), NULL);
    g_signal_connect (G_OBJECT (answer_buttons[1]), "clicked", G_CALLBACK (answer_clicked), NULL);
    g_signal_connect (G_OBJECT (answer_buttons[2]), "clicked", G_CALLBACK (answer_clicked), NULL);
    g_signal_connect (G_OBJECT (answer_buttons[3]), "clicked", G_CALLBACK (answer_clicked), NULL);


    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (quiz_button_clicked), NULL);

}
