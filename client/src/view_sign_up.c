#include "view_sign_up.h"

void view_sign_up(t_current_window_info *current_layout)
{
    GtkLayout *sign_in_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout->builder, "sign_in_layout"));
    gtk_widget_destroy(GTK_WIDGET(sign_in_layout));

    gtk_builder_add_from_file(current_layout->builder, get_path_to_glade("sign_up_layout.glade"), NULL);
    GtkLayout *sign_up_layout = GTK_LAYOUT(gtk_builder_get_object(current_layout->builder, "sign_up_layout"));

    GtkImage *sign_up_image = GTK_IMAGE(gtk_builder_get_object(current_layout->builder, "sign_up_image"));

    gtk_container_add(GTK_CONTAINER(current_layout->main_window), GTK_WIDGET(sign_up_layout));


    GtkButton *return_button = GTK_BUTTON(gtk_builder_get_object(current_layout->builder, "return_button"));
    GtkButton *sign_up_button = GTK_BUTTON(gtk_builder_get_object(current_layout->builder, "sign_up"));


    g_signal_connect(return_button, "clicked", G_CALLBACK(return_clicked), current_layout);
    g_signal_connect(sign_up_button, "clicked", G_CALLBACK(sign_up_insert_clicked), current_layout);
}

G_MODULE_EXPORT void return_clicked(GtkButton *button, t_current_window_info *current_layout)
{
    view_sign_in(current_layout);
}

G_MODULE_EXPORT void sign_up_insert_clicked(GtkButton *button, t_current_window_info *current_layout)
{

    //check if valid sign up info
    GtkEntry **sign_up_info = (GtkEntry **)malloc(4 * sizeof(GtkEntry *));
    sign_up_info[0] = GTK_ENTRY(gtk_builder_get_object(current_layout->builder, "username_entry"));
    sign_up_info[1] = GTK_ENTRY(gtk_builder_get_object(current_layout->builder, "password_entry"));
    sign_up_info[2] = GTK_ENTRY(gtk_builder_get_object(current_layout->builder, "password_entry1"));

    g_signal_connect(sign_up_info[0], "changed", G_CALLBACK(entry_activate), sign_up_info);
    g_signal_connect(sign_up_info[1], "changed", G_CALLBACK(entry_activate), sign_up_info);
    g_signal_connect(sign_up_info[2], "changed", G_CALLBACK(entry_activate), sign_up_info);

    printf("username: %s\npassword: %s\nrepeat password: %s\n", (char *)gtk_entry_get_text(sign_up_info[0]),
                                                                (char *)gtk_entry_get_text(sign_up_info[1]),
                                                                (char *)gtk_entry_get_text(sign_up_info[2]));
    if (!is_valid_user_data(sign_up_info)){
        place_sign_entry_error(sign_up_info);
    }else{
        char* encrypted = encrypt_pswd((char *)gtk_entry_get_text(sign_up_info[1]));
        int status = controller_sign_up((char *)gtk_entry_get_text(sign_up_info[0]), encrypted);
        printf("\n\n\n\n");
        printf("THERE SIGN UP CLIENT");
        printf("%s", encrypted);
        printf("\n\n\n\n");
        if(status){
            place_sign_entry_error(sign_up_info);
        }else {
            view_sign_in(current_layout); // or main page;

        }
    }
}
