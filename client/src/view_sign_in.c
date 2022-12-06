#include "view_sign_in.h"

void view_sign_in(t_current_window_info *current_layout_info)
{

    GtkLayout *sign_up_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_up_layout"));
    if (current_layout_info->layout_exists)
    {
        gtk_widget_destroy(GTK_WIDGET(sign_up_layout));
    }
    gtk_builder_add_from_file(current_layout_info->builder, get_path_to_glade("sign_in_layout.glade"), NULL);

    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout_info->builder, "sign_in_layout"));

    GtkImage *sign_in_image = GTK_IMAGE(gtk_builder_get_object(current_layout_info->builder, "sign_in_image"));

    gtk_container_add(GTK_CONTAINER(current_layout_info->main_window), GTK_WIDGET(sign_in_layout));
    current_layout_info->layout_exists = true;


    GtkButton *sign_in_button = GTK_BUTTON(gtk_builder_get_object(current_layout_info->builder, "sign_in"));
    GtkButton *sign_up_button = GTK_BUTTON(gtk_builder_get_object(current_layout_info->builder, "sign_up"));

    g_signal_connect(sign_in_button, "clicked", G_CALLBACK(sign_in_clicked), current_layout_info);
    g_signal_connect(sign_up_button, "clicked", G_CALLBACK(sign_up_clicked), current_layout_info);
    // printf("asAFFASFAF\n");

}

G_MODULE_EXPORT void sign_in_clicked(GtkButton *button, t_current_window_info *current_layout_info)
{
    // printf("username: %s\npassword: %s\n", (char *)gtk_entry_get_text(sign_in_info[0]), (char *)gtk_entry_get_text(sign_in_info[1]));
    //check input

    GtkEntry **sign_in_info = (GtkEntry **)malloc(3 * sizeof(GtkEntry *));
    sign_in_info[0] = GTK_ENTRY(gtk_builder_get_object(current_layout_info->builder, "username_entry"));
    sign_in_info[1] = GTK_ENTRY(gtk_builder_get_object(current_layout_info->builder, "password_entry"));
    sign_in_info[2] = NULL;

    g_signal_connect(sign_in_info[0], "changed", G_CALLBACK(entry_activate), sign_in_info);
    g_signal_connect(sign_in_info[1], "changed", G_CALLBACK(entry_activate), sign_in_info);

    if (!is_valid_user_data(sign_in_info)){
        place_sign_entry_error(sign_in_info);
    }else{
        char* encrypted_password = encrypt_pswd((char *)gtk_entry_get_text(sign_in_info[1]));
        // printf("Encrypted password: %s\n", encrypted_password);
        int status = controller_sign_in((char *)gtk_entry_get_text(sign_in_info[0]), encrypted_password);
        // printf("\n\n\n\n");
        // printf("THERE SIGN IN CLIENT");
        // printf("%s", encrypted_password);
        // printf("\n\n\n\n");
        if (status){
            place_sign_entry_error(sign_in_info);
        } else {
            controller_view_user_era((GtkWidget**)sign_in_info, current_layout_info);
        }
    }
}

G_MODULE_EXPORT void sign_up_clicked(GtkButton *button, t_current_window_info *current_layout_info)
{
    view_sign_up(current_layout_info);
}
