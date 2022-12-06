#include "shop.h"
#include "user_data_request.h"
#include "encrypt.h"

static t_current_window_info* static_current_window_info = NULL;

bool is_in_bought(cJSON* bought, size_t id);
void buy_item(GtkWidget *widget, t_model_store* model_store);
void money_view(GtkWidget *widget, GtkBuilder* builder);
void change_background();

void set_shop_on_button(GtkWidget *button, t_current_window_info* current_window_info) {
    // send_set_user_era_request("n", (get_from_protocol_string(get_cookies(), "TOKEN")), 3);

    static_current_window_info = current_window_info;

    GtkCssProvider *cssProvider = gtk_css_provider_new(); 

    t_model_user_data* model_user_data = send_user_data_request(get_from_protocol_string(get_cookies(), "USERNAME"));
    t_model_store** model_store = send_store_request(model_user_data->era);

    cJSON* bought = cJSON_Parse(model_user_data->bought_items);


    GtkBuilder *builder;
    if (model_user_data->era == 0) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("stone_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_stone_age.glade"));
    }
    else if (model_user_data->era == 1) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("egypt_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_egypt.glade"));
    }
    else if (model_user_data->era == 2) {
        model_user_data->era = 3;
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("enlightment_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_enlightment.glade"));
    }
    else if (model_user_data->era == 3) {
        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("enlightment_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("shop_enlightment.glade"));
    }
    else if (model_user_data->era == 4) {

        gtk_css_provider_load_from_path(cssProvider, get_path_to_style("modern_era_shop.css"), NULL);
        builder = gtk_builder_new_from_file(get_path_to_glade("modern_shop.glade"));
        // only one item
    }
    // GtkBuilder *builder = gtk_builder_new_from_file(get_path_to_glade("shop.glade"));
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                            GTK_STYLE_PROVIDER(cssProvider), 
                                            GTK_STYLE_PROVIDER_PRIORITY_USER);

    GtkWidget *shop_popover;

    GtkWidget *shop_layout = GTK_WIDGET(gtk_builder_get_object(builder, "shop_layout"));


    shop_popover = gtk_popover_new (button);
    gtk_container_add (GTK_CONTAINER (shop_popover), shop_layout);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (button), shop_popover);
    gtk_popover_set_position(GTK_POPOVER(shop_popover), GTK_POS_RIGHT);

    GtkBuilder *builder_explanation = gtk_builder_new_from_file(get_path_to_glade("shop_explanation.glade"));
    GtkWidget *shop_layout_explanation = GTK_WIDGET(gtk_builder_get_object(builder_explanation, "shop_explanation_layout"));
    GtkWidget *explanation_button = GTK_WIDGET(gtk_builder_get_object(builder, "explanation_button"));

    GtkWidget *shop_item1 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item1"));
    GtkWidget *shop_item2 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item2"));
    GtkWidget *shop_item3 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item3"));
    GtkWidget *shop_item4 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item4"));
    GtkWidget *shop_item5 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item5"));
    GtkWidget *shop_item6 = GTK_WIDGET(gtk_builder_get_object(builder, "shop_item6"));

    int size = 6;
    if(model_user_data->era == 4) {
        size = 1;
    }

    // for (int i = 0; i < size; i++) {
    // printf("\n\n %s \n\n", model_store[i]->path); }

    GdkPixbuf *image_pixbuf1 = gdk_pixbuf_new_from_file_at_size(model_store[0]->path, -1, -1, NULL);
    GtkWidget *image_shop_item1 = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item1), image_pixbuf1);
    gtk_button_set_image(shop_item1, image_shop_item1);

    if(size > 1) {
        GdkPixbuf *image_pixbuf2 = gdk_pixbuf_new_from_file_at_size(model_store[1]->path, -1, -1, NULL);
        GtkWidget *image_shop_item2 = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item2), image_pixbuf2);
        gtk_button_set_image(shop_item2, image_shop_item2);

        GdkPixbuf *image_pixbuf3 = gdk_pixbuf_new_from_file_at_size(model_store[2]->path, -1, -1, NULL);
        GtkWidget *image_shop_item3 = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item3), image_pixbuf3);
        gtk_button_set_image(shop_item3, image_shop_item3);

        GdkPixbuf *image_pixbuf4 = gdk_pixbuf_new_from_file_at_size(model_store[3]->path, -1, -1, NULL);
        GtkWidget *image_shop_item4 = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item4), image_pixbuf4);
        gtk_button_set_image(shop_item4, image_shop_item4);

        GdkPixbuf *image_pixbuf5 = gdk_pixbuf_new_from_file_at_size(model_store[4]->path, -1, -1, NULL);
        GtkWidget *image_shop_item5 = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item5), image_pixbuf5);
        gtk_button_set_image(shop_item5, image_shop_item5);

        GdkPixbuf *image_pixbuf6 = gdk_pixbuf_new_from_file_at_size(model_store[5]->path, -1, -1, NULL);
        GtkWidget *image_shop_item6 = gtk_image_new();
        gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item6), image_pixbuf6);
        gtk_button_set_image(shop_item6, image_shop_item6);
    }




    GtkWidget* shop_popover_explanation = gtk_popover_new (explanation_button);
    gtk_container_add (GTK_CONTAINER (shop_popover_explanation), shop_layout_explanation);
    gtk_menu_button_set_popover (GTK_MENU_BUTTON (explanation_button), shop_popover_explanation);
    gtk_popover_set_position(GTK_POPOVER(shop_popover_explanation), GTK_POS_RIGHT);

    g_signal_connect(button, "clicked", G_CALLBACK(money_view), builder);

    if (!is_in_bought(bought, model_store[0]->id))
        g_signal_connect(shop_item1, "clicked", G_CALLBACK(buy_item), model_store[0]);
    // else 
    //     // grey
    if(size > 1) {

        if (!is_in_bought(bought, model_store[1]->id))
            g_signal_connect(shop_item2, "clicked", G_CALLBACK(buy_item), model_store[1]);
        if (!is_in_bought(bought, model_store[2]->id))
            g_signal_connect(shop_item3, "clicked", G_CALLBACK(buy_item), model_store[2]);
        if (!is_in_bought(bought, model_store[3]->id))
            g_signal_connect(shop_item4, "clicked", G_CALLBACK(buy_item), model_store[3]);
        if (!is_in_bought(bought, model_store[4]->id))
            g_signal_connect(shop_item5, "clicked", G_CALLBACK(buy_item), model_store[4]);
        if (!is_in_bought(bought, model_store[5]->id))
            g_signal_connect(shop_item6, "clicked", G_CALLBACK(buy_item), model_store[5]);
    }
}

void money_view(GtkWidget *widget, GtkBuilder* builder) {
    GtkLabel *money_label = GTK_LABEL(gtk_builder_get_object(builder, "money_label"));
    gtk_label_set_text(money_label, mx_itoa(send_money_request_by_username(get_from_protocol_string(get_cookies(), "USERNAME"))));
}

void buy_item(GtkWidget *widget, t_model_store* model_store) {

    send_buy_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), model_store->id);

    if (model_store->id == 1) {
        // change era 
        send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 1);

        GtkLayout *first_era_layout = GTK_LAYOUT(gtk_builder_get_object(static_current_window_info->builder, "home_page_layout"));
        if (static_current_window_info->layout_exists)
            gtk_widget_destroy(GTK_WIDGET(first_era_layout));
    
        view_egypt(static_current_window_info);
    }

    // if (model_store->id == 2) {
    //     // clear stone
    // }

    // if (model_store->id == 3) {
    //     // change rock
    // }

    // if (model_store->id == 4) {
    //     // change rock
    // }

    // if (model_store->id == 5) {
    //     // change rock
    // }

    // if (model_store->id == 6) {
    //     // change rock
    // }

    if (model_store->id == 7) {
        // change era 
        send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 3);

        GtkLayout *egypt_layout = GTK_LAYOUT(gtk_builder_get_object(static_current_window_info->builder, "home_page_layout"));
        if (static_current_window_info->layout_exists)
            gtk_widget_destroy(GTK_WIDGET(egypt_layout));
        
        view_enlightenment_era(static_current_window_info);
    }

    // //8-12 add words

    // if (model_store->id == 19) {
    //     // change era 
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 4);

    //     GtkLayout *first_era_layout = GTK_LAYOUT(gtk_builder_get_object(static_current_window_info->builder, "home_page_layout"));
    //     if (static_current_window_info->layout_exists)
    //         gtk_widget_destroy(GTK_WIDGET(first_era_layout));
        
    //     view_stone_age_page(static_current_window_info);
    // }

    // if (model_store->id == 20) {
    //     // unlock sending files
    // }

    // if (model_store->id == 21) {
    //     // educate
    // }


    if (model_store->id == 22) {
        change_background();
        // change background
    //     GtkWidget *background1 = GTK_WIDGET(gtk_builder_get_object(static_current_window_info->builder, "chat_window_scrolled"));

    //     GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file_at_size("./client/resources/static/images/enlightenment_bckg1.jpeg", -1, -1, NULL);
    //     GtkWidget *image_shop_item3 = gtk_image_new();
    //     gtk_image_set_from_pixbuf(GTK_IMAGE(image_shop_item3), image_pixbuf);
    //  (background1, image_shop_item3);
    }

    if (model_store->id == 23) {
        // change background

    }

    if (model_store->id == 24) {
        // change background
    }

    // if (model_store->id == 25) {
    //     // change era, gift
    //     send_set_user_era_request(get_from_protocol_string(get_cookies(), "USERNAME"), get_from_protocol_string(get_cookies(), "TOKEN"), 0);

    //     GtkLayout *first_era_layout = GTK_LAYOUT(gtk_builder_get_object(static_current_window_info->builder, "home_page_layout"));
    //     if (static_current_window_info->layout_exists)
    //         gtk_widget_destroy(GTK_WIDGET(first_era_layout));
        
    //     view_stone_age_page(static_current_window_info);
    // }
}

bool is_in_bought(cJSON* bought, size_t id) {
    int arr_size = cJSON_GetArraySize(bought);

    for (int i = 0; i < arr_size; i++) {
        if (cJSON_GetArrayItem(bought, i)->valueint == id)
            return true;
    }

    return false;
}

void change_background () {
    GtkStyleContext *background_old = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(static_current_window_info->builder, "chat_window_scrolled")));
    // GtkStyleContext *background_new = gtk_widget_get_style_context(GTK_WIDGET(gtk_builder_get_object(static_current_window_info->builder, "chat_window_scrolled_background1")));
    gtk_style_context_remove_class(background_old, "chat_window_scrolled");
    gtk_style_context_add_class(background_old, "chat_window_scrolled_background1");
}

