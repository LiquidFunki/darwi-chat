#include "user_info.h"

void set_user_info_on_button(GtkWidget *button, t_current_window_info *current_window_info) {
    t_model_user_data *model_user_data = send_user_data_request(get_from_protocol_string(get_cookies(), "USERNAME"));

    GtkWidget *user_info_popover;
    gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("user_info.glade"), NULL);
    // GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("user_info.glade"));
    GtkWidget *user_info_layout = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "user_info_layout"));
    
    user_info_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (user_info_popover), user_info_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), user_info_popover);
    gtk_popover_set_position(GTK_POPOVER(user_info_popover), GTK_POS_RIGHT);
    // gtk_widget_show_all (user_info_popover); TODO: mojet delete ?

    GtkLabel *status_info = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "status_info"));
    GtkLabel *phone_info = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "phone_info"));
    GtkLabel *email_info = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "email_info"));
    GtkLabel *era_info = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "era_info"));
    GtkLabel *money = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "money"));

    if (model_user_data->status)
        gtk_label_set_text(status_info, model_user_data->status);
    else
        gtk_label_set_text(status_info, "no info");
    if (model_user_data->t_number)
        gtk_label_set_text(phone_info, model_user_data->t_number);
    else
        gtk_label_set_text(phone_info, "no info");
    if (model_user_data->email)
        gtk_label_set_text(email_info, model_user_data->email);
    else
        gtk_label_set_text(email_info, "no info");

    gtk_label_set_text(money, mx_itoa(model_user_data->money));

    int era = mx_itoa(model_user_data->era);
    if (era == STONE_AGE)
        printf("GKGKJJ\n");
        gtk_label_set_text(era_info, "Stone Age");
    if (era == 1)
        gtk_label_set_text(era_info, "Egypt");
    if (era == 2)
        gtk_label_set_text(era_info, "Middle Ages");
    if (era == 3)
        gtk_label_set_text(era_info, "Age of Enlightment");
    if (era == 4)
        gtk_label_set_text(era_info, "Modern Times");


    current_window_info->data = (void*)model_user_data->id;

    g_signal_connect (G_OBJECT (button), "clicked", G_CALLBACK (menu_button_clicked), current_window_info);
}


void menu_button_clicked(GtkWidget *widget, t_current_window_info *current_window_info) {
    int money_int = send_money_request((int)(current_window_info->data));
    GtkLabel *money = GTK_LABEL( gtk_builder_get_object(current_window_info->builder, "money"));

    gtk_label_set_text(money, mx_itoa(money_int));
}
