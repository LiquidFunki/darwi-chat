#include "settings.h"
#include "log_out.h"

typedef enum enum_edit_type {

    EDIT_NOTHING,
    EDIT_NAME,
    EDIT_PERSONAL,
    EDIT_PHONE,
    EDIT_EMAIL

}            e_edit_type;

static e_edit_type edit_type = EDIT_NOTHING;
static GtkEntry*   data_entry = NULL;

void edit_name_clicked(GtkButton* b, GtkBuilder* data) {
    edit_type = EDIT_NAME;
    GtkBuilder* builder = (GtkBuilder*)data;
    GtkEntry* edit_name = GTK_ENTRY(gtk_builder_get_object(builder, "edit_info_entry"));
    data_entry = edit_name;
}

void edit_personal_clicked(GtkButton* b, GtkBuilder* data) {
    edit_type = EDIT_PERSONAL;
    GtkBuilder* builder = (GtkBuilder*)data;
    GtkEntry* edit_name = GTK_ENTRY(gtk_builder_get_object(builder, "edit_info_entry"));
    data_entry = edit_name;
}

void edit_phone_clicked(GtkButton* b, GtkBuilder* data) {
    edit_type = EDIT_PHONE;
    GtkBuilder* builder = (GtkBuilder*)data;
    GtkEntry* edit_name = GTK_ENTRY(gtk_builder_get_object(builder, "edit_info_entry"));
    data_entry = edit_name;
}

void edit_email_clicked(GtkButton* b, GtkBuilder* data) {
    edit_type = EDIT_EMAIL;
    GtkBuilder* builder = (GtkBuilder*)data;
    GtkEntry* edit_name = GTK_ENTRY(gtk_builder_get_object(builder, "edit_info_entry"));
    data_entry = edit_name;

}

void accept_edit_button_clicked(GtkButton* b, GtkPopover* popover) {

    if (edit_type == EDIT_NAME) {
    } else if (edit_type == EDIT_PERSONAL) {
        send_set_user_about_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), gtk_entry_get_text(data_entry));
    } else if (edit_type == EDIT_PHONE) {
        send_set_user_tnumber_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), gtk_entry_get_text(data_entry));
    } else if (edit_type == EDIT_EMAIL) {
        send_set_user_email_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), gtk_entry_get_text(data_entry));
    } else {
        printf("Accept clicked: %s\n", "Nothing Selected");
    }

    gtk_popover_popdown(popover);
}

void decline_edit_button_clicked(GtkButton* b, GtkPopover* popover) {
    edit_type = EDIT_NOTHING;
    data_entry = NULL;
    gtk_popover_popdown(popover);
}

GtkBuilder *edit_info_on_button(GtkWidget *button, const gchar *title) {
    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("settings.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);
                                            
    GtkWidget *user_info_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("edit_info.glade"));
    GtkWidget *user_info_layout = GTK_WIDGET(gtk_builder_get_object(builder, "edit_info_layout"));
    GtkLabel *edit_title = GTK_LABEL( gtk_builder_get_object(builder, "edit_title"));
    gtk_label_set_text(GTK_LABEL(edit_title), title);
    
    user_info_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (user_info_popover), user_info_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), user_info_popover);
    gtk_popover_set_position(GTK_POPOVER(user_info_popover), GTK_POS_RIGHT);
    return builder;
}

void set_setting_on_button(GtkWidget *button, t_current_window_info *current_layout_info, GtkWidget *layout_to_destroy) {

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 
    gtk_css_provider_load_from_path(cssProvider, get_path_to_style("settings.css"), NULL); 
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *settings_popover;
    GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("settings.glade"));
    GtkWidget *settings_layout = GTK_WIDGET(gtk_builder_get_object(builder, "settings_layout"));
    
    settings_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (settings_popover), settings_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), settings_popover);
    gtk_popover_set_position(GTK_POPOVER(settings_popover), GTK_POS_RIGHT);
    GtkWidget *set_new_photo = GTK_BUTTON(gtk_builder_get_object(builder, "set_new_photo"));
    GtkWidget *edit_name = GTK_BUTTON(gtk_builder_get_object(builder, "edit_name"));
    GtkWidget *edit_personal_info = GTK_BUTTON(gtk_builder_get_object(builder, "edit_personal_info"));
    GtkWidget *edit_phone_number = GTK_BUTTON(gtk_builder_get_object(builder, "edit_phone_number"));
    GtkWidget *edit_email = GTK_BUTTON(gtk_builder_get_object(builder, "edit_email"));
    GtkWidget *log_out = GTK_BUTTON(gtk_builder_get_object(builder, "log_out"));


    // g_signal_connect(edit_name, "clicked", view_edit_window_on_button, current_layout_info);

    // g_signal_connect(edit_name, "clicked", G_CALLBACK(edit_name), builder);

    GtkBuilder* edit_name_builder = edit_info_on_button(edit_name, gtk_button_get_label(edit_name));
    GtkBuilder* edit_personal_info_builder = edit_info_on_button(edit_personal_info, gtk_button_get_label(edit_personal_info));
    GtkBuilder* edit_phone_number_builder = edit_info_on_button(edit_phone_number, gtk_button_get_label(edit_phone_number));
    GtkBuilder* edit_email_builder = edit_info_on_button(edit_email, gtk_button_get_label(edit_email));

    g_signal_connect(edit_name, "clicked", edit_name_clicked, edit_name_builder);
    g_signal_connect(edit_personal_info, "clicked", edit_personal_clicked, edit_personal_info_builder);
    g_signal_connect(edit_phone_number, "clicked", edit_phone_clicked, edit_phone_number_builder);
    g_signal_connect(edit_email, "clicked", edit_email_clicked, edit_email_builder);

    GtkWidget *accept_edit_email_button = GTK_WIDGET(gtk_builder_get_object(edit_email_builder, "accept_edit_button"));
    GtkWidget *decline_edit_email_button = GTK_WIDGET(gtk_builder_get_object(edit_email_builder, "decline_edit_button"));

    GtkWidget *accept_edit_phone_number_button = GTK_WIDGET(gtk_builder_get_object(edit_phone_number_builder, "accept_edit_button"));
    GtkWidget *decline_edit_phone_number_button = GTK_WIDGET(gtk_builder_get_object(edit_phone_number_builder, "decline_edit_button"));

    GtkWidget *accept_edit_personal_info_button = GTK_WIDGET(gtk_builder_get_object(edit_personal_info_builder, "accept_edit_button"));
    GtkWidget *decline_edit_personal_info_button = GTK_WIDGET(gtk_builder_get_object(edit_personal_info_builder, "decline_edit_button"));

    GtkWidget *accept_edit_name_button = GTK_WIDGET(gtk_builder_get_object(edit_name_builder, "accept_edit_button"));
    GtkWidget *decline_edit_name_button = GTK_WIDGET(gtk_builder_get_object(edit_name_builder, "decline_edit_button"));

    g_signal_connect(accept_edit_email_button, "clicked", accept_edit_button_clicked, settings_popover);
    g_signal_connect(decline_edit_email_button, "clicked", decline_edit_button_clicked, settings_popover);

    g_signal_connect(accept_edit_phone_number_button, "clicked", accept_edit_button_clicked, settings_popover);
    g_signal_connect(decline_edit_phone_number_button, "clicked", decline_edit_button_clicked, settings_popover);

    g_signal_connect(accept_edit_personal_info_button, "clicked", accept_edit_button_clicked, settings_popover);
    g_signal_connect(decline_edit_personal_info_button, "clicked", decline_edit_button_clicked, settings_popover);

    g_signal_connect(accept_edit_name_button, "clicked", accept_edit_button_clicked, settings_popover);
    g_signal_connect(decline_edit_name_button, "clicked", decline_edit_button_clicked, settings_popover);


    current_layout_info->data = (void*)layout_to_destroy;
    g_signal_connect(log_out, "clicked", log_out_func, current_layout_info);
}

// void edit_name(GtkWidget* widget, GtkBuilder *builder) {
    
// }
