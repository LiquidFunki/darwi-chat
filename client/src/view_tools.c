#include "view_tools.h"

t_current_window_info *create_current_window_info(void) {
  t_current_window_info* current_window_info = (t_current_window_info*)malloc(sizeof(t_current_window_info));
  current_window_info->builder = gtk_builder_new();
  current_window_info->main_window = NULL;
  current_window_info->layout_exists = false;
  current_window_info->message_position_y = 0;
  return current_window_info;
}

G_MODULE_EXPORT void entry_activate(GtkEntry* entry, GtkEntry **info) {
  delete_sign_entry_error(info);
}

int is_valid_user_data(GtkEntry **info) {
    // int status = 0;
    if(!strlen((char*)gtk_entry_get_text(info[0])) && !strlen((char*)gtk_entry_get_text(info[1]))) {
      return 0;   
    } 
    if(info[2] != NULL) {
      if(!strlen((char*)gtk_entry_get_text(info[2]))) {
        return 0;
      }
      if(!g_str_equal(gtk_entry_get_text(info[1]), gtk_entry_get_text(info[2]))) {
        return 0;
      }
    }
    
  return 1;
}



void place_answer_error(GtkWidget *button) {
    GtkStyleContext *answer_context = gtk_widget_get_style_context(button);
    gtk_style_context_remove_class(answer_context, "answer");
    gtk_style_context_add_class(answer_context, "answer_error");
}


void delete_answer_error(GtkWidget *button) {
    GtkStyleContext *answer_context = gtk_widget_get_style_context(button);
    gtk_style_context_remove_class(answer_context, "answer_error");
    gtk_style_context_add_class(answer_context, "answer");
}





void place_sign_entry_error(GtkEntry **entries) {
    GtkStyleContext *entry_context_username = gtk_widget_get_style_context(GTK_WIDGET(entries[0]));
    GtkStyleContext *entry_context_password = gtk_widget_get_style_context(GTK_WIDGET(entries[1]));
    if(entries[2] != NULL) {
        GtkStyleContext *entry_context_password1 = gtk_widget_get_style_context(GTK_WIDGET(entries[2]));
        gtk_style_context_remove_class(entry_context_password, "user_n_password");
        gtk_style_context_add_class(entry_context_password1, "user_n_password_error");
    }
    gtk_style_context_remove_class(entry_context_username, "user_n_password");
    gtk_style_context_remove_class(entry_context_password, "user_n_password");

    gtk_style_context_add_class(entry_context_password, "user_n_password_error");
    gtk_style_context_add_class(entry_context_username, "user_n_password_error");
}

// TODO do it in loop
void delete_sign_entry_error(GtkEntry **entries) {
    GtkStyleContext *entry_context_username = gtk_widget_get_style_context(GTK_WIDGET(entries[0]));
    GtkStyleContext *entry_context_password = gtk_widget_get_style_context(GTK_WIDGET(entries[1]));

    if(entries[2] != NULL) {
        GtkStyleContext *entry_context_password1 = gtk_widget_get_style_context(GTK_WIDGET(entries[2]));
        gtk_style_context_remove_class(entry_context_password1, "user_n_password_error");
        gtk_style_context_add_class(entry_context_password1, "user_n_password");
    }
    
    gtk_style_context_remove_class(entry_context_username, "user_n_password_error");
    gtk_style_context_remove_class(entry_context_password, "user_n_password_error");

    gtk_style_context_add_class(entry_context_password, "user_n_password");
    gtk_style_context_add_class(entry_context_username, "user_n_password");
} 