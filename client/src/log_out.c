#include "log_out.h"
#include "send_request.h"

void log_out_func(GtkWidget *widget, t_current_window_info *current_window_info) {

    system("rm -f db_client.sqlite");

    system("rm ./client/resources/tmp/*");

    system("touch ./client/resources/tmp/to_delete.txt");

    if(!current_window_info) {
        gtk_main_quit();
    } else {
        GtkWidget *current_layout = (GtkWidget*)current_window_info->data;
        gtk_widget_destroy(current_layout);
        t_current_window_info *window_info = create_current_window_info();
        window_info->main_window = current_window_info->main_window;
        window_info->builder = gtk_builder_new();
        view_sign_in(window_info);
    }

    close_connection();
}
