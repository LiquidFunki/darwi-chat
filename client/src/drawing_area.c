#include "drawing_area.h"



t_point* saved = NULL;

char *file_to_save_draw = NULL;

cairo_t *global_cr = NULL;

void draw_transparent(cairo_t *cr);

void add_to_saved(t_point* point) {
    if (saved == NULL) {
        saved = (t_point*)malloc(sizeof(t_point));
        saved->x = point->x;
        saved->y = point->y;
        saved->next = NULL;
    }
    else {

        t_point* last = saved;

        while(last->next != NULL) last = last->next;

        last->next = (t_point*)malloc(sizeof(t_point));
        last->next->x = point->x;
        last->next->y = point->y;
        last->next->next = NULL;
    }
}

void save_saved_to_file(t_point* saved, char* path_to_file) {

    t_point* current = saved;
	int size_of_saved = 0;
	while(current != NULL) {
		size_of_saved++;
		current = current->next;
	}
	fflush(stdout);
	t_point saved_points[size_of_saved];

	current = saved;

    FILE* file = fopen(path_to_file, "w");


	for(int i = 0; i < size_of_saved - 1; i++) {
		saved_points[i].x = current->x;
		saved_points[i].y = current->y;
		saved_points[i].next = current->next;
		current = current->next;
	}

	current->next = NULL;

	fwrite(saved_points, sizeof(t_point), (size_of_saved - 1) , file);

    fclose(file);
	
}

t_point* read_saved_from_file(char* path_to_file) {
    t_point* read = (t_point*)malloc(sizeof( t_point));

    FILE* file = fopen(path_to_file, "r");

    if (file == NULL) {
        free(read);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
	int size_of_array = size / sizeof(t_point);
	t_point points[size_of_array];
 
    if (size == 0) {
        free(read);
        return NULL;
    }
    fseek(file, 0, SEEK_SET);

	fflush(stdout);
    
	fread(points, sizeof( t_point), size_of_array, file);


    t_point* current = read;

	for(int i = 0; i < size_of_array; i++) {
		current->x = points[i].x;
		current->y = points[i].y;
		current->next = NULL;
		if(i < size_of_array - 1) {
			current->next = (t_point*)malloc(sizeof( t_point));
			current = current->next;
		}
	}
    fclose(file);
    return read;
}





void draw_brush(GtkWidget *widget, gdouble x, gdouble y, GtkWidget *draw_area)
{
	point = malloc(sizeof(struct s_point));
	if (point == NULL)
	{
		printf("out of memory\n");
		abort();
	}

	point->x = x;
	point->y = y;
	point->next = s_point_start;
	s_point_start = point;

	add_to_saved(point);

	gtk_widget_queue_draw_area(draw_area, 0, 0, 1214, 668);
	
}

gboolean on_draw_button_press_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info)
{
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
    draw_brush(widget, event->x, event->y, draw_area);
	return TRUE;
}

gboolean on_draw_button_release_event(GtkWidget *widget, GdkEventButton *event,  t_current_window_info* current_window_info)
{
	save_saved_to_file(saved, file_to_save_draw);
	char *to_user = get_current_user_to_talk();
	t_model_message *message = controller_send_message(to_user, MESSAGE_STONE, file_to_save_draw);
    return TRUE;
}

void draw_saved(cairo_t *cr){

    cairo_surface_t *cairo_image_surface = cairo_image_surface_create_from_png(get_path_to_image("surface.png"));
	cairo_set_line_width(cr, 4.0);

	t_point *temp = saved;
	while (temp->next != NULL) {
		// cairo_set_source_rgb(cr, 1, 0, 0);
        cairo_set_source_surface(cr, cairo_image_surface, 0, 0);
        
		cairo_move_to(cr, (double)temp->x, (double)temp->y);
		if(ABS((temp->next->x - temp->x)) < cairo_get_line_width(cr) * 5 && ABS((temp->next->y - temp->y)) < cairo_get_line_width(cr) * 5) {
			cairo_line_to(cr, (double)temp->next->x, (double)temp->next->y);
			// weird line version
	        // cairo_curve_to(cr, point->x, point->y, point->x + 3, point->y + 3, point->x + 5, point->y + 5);
        }
        cairo_stroke(cr);
        temp = temp->next;
	}

}

gboolean on_draw_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{	
	global_cr = cr;
	if(saved){
		draw_saved(cr);
	}
    cairo_surface_t *cairo_image_surface = cairo_image_surface_create_from_png(get_path_to_image("surface.png"));

	guint width, height;
	width = gtk_widget_get_allocated_width(widget);
	height = gtk_widget_get_allocated_height(widget);

	cairo_set_line_width(cr, 4.0);

	if (s_point_start == NULL) {
    	return FALSE;
    }

	int old_x = s_point_start->x;
	int old_y = s_point_start->y;

	point = s_point_start->next;
	
	while (point != NULL)
	{
		// to lay texture
        cairo_set_source_surface(cr, cairo_image_surface, 0, 0);
        // cairo_set_source_rgb(cr, 0.2, 0.3, 0.2);
        
		cairo_move_to(cr, (double)old_x, (double)old_y);
        if(ABS((point->x - old_x)) < cairo_get_line_width(cr) * 5 && ABS((point->y - old_y)) < cairo_get_line_width(cr) * 5) {
		    cairo_line_to(cr, (double)point->x, (double)point->y);

			// weird line version
	        // cairo_curve_to(cr, point->x, point->y, point->x + 3, point->y + 3, point->x + 5, point->y + 5);
        }

        cairo_stroke(cr);

		// pixel version !!!!

		// cairo_rectangle(cr, old_x, old_y, 4, 4);
        // cairo_fill(cr);
		old_x = point->x;
        old_y = point->y;

        point = point->next;
	}
	
	return TRUE;
}



gboolean on_draw_motion_notify_event(GtkWidget *widget, GdkEventMotion *event, t_current_window_info* current_window_info)
{
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
	if (event->state & GDK_BUTTON1_MASK) {
		draw_brush(widget, event->x, event->y, draw_area);
    }
    return TRUE;
}





void draw_transparent(cairo_t *cr){

    cairo_surface_t *cairo_image_surface = cairo_image_surface_create_from_png(get_path_to_image("stone.png"));
	cairo_set_line_width(cr, 4.0);

	t_point *temp = saved;
	while (temp->next != NULL) {
		// cairo_set_source_rgb(cr, 1, 0, 0);
        cairo_set_source_surface(cr, cairo_image_surface, 0, 0);
        
		cairo_move_to(cr, (double)temp->x, (double)temp->y);
		if(ABS((temp->next->x - temp->x)) < cairo_get_line_width(cr) * 5 && ABS((temp->next->y - temp->y)) < cairo_get_line_width(cr) * 5) {
			cairo_line_to(cr, (double)temp->next->x, (double)temp->next->y);
			// weird line version
	        // cairo_curve_to(cr, point->x, point->y, point->x + 3, point->y + 3, point->x + 5, point->y + 5);
        }
        cairo_stroke(cr);
        temp = temp->next;
	}

}



void add_draw_area(t_current_window_info *current_window_info, t_model_message *model_message) {
	// TODO: CLEAR DRAW AREA for users
	system(mx_strjoin("rm ", "./client/resources/tmp/temp_draw"));
	if(global_cr){
		printf("\n\nTRANSPARENT\n\n");
		draw_transparent (global_cr);
	}
	saved = NULL;
	if(model_message){
		t_model_stone *stone_msg = get_stone_by_id(model_message->data);
		request_file_if_not_exist(stone_msg->path);
		fprintf(stderr, "\n\n STONE ID: %s\n\n", model_message->data);

		fprintf(stderr, "\n\n STONE MODEL: %s\n\n", to_string_model_stone(stone_msg));
		fprintf(stderr, "\n\n STONE PATH: %s\n\n", stone_msg->path);
		// saved = read_saved_from_file("test_saved_points");
		char *draw_file_to_save_draw = mx_replace_substr(stone_msg->path, "./server", "./client");
		saved = read_saved_from_file( draw_file_to_save_draw);
	} else {
		saved = NULL;
	}
	file_to_save_draw = mx_strdup("./client/resources/tmp/temp_draw");



    GtkLayout *rock_layout = GTK_LAYOUT(gtk_builder_get_object(current_window_info->builder, "chat_window_layout"));

	gtk_builder_add_from_file(current_window_info->builder, get_path_to_glade("drawing_area.glade"), NULL);
    
	GtkLayout *drawing_layout = GTK_LAYOUT(gtk_builder_get_object(current_window_info->builder, "draw_layout"));

	gtk_widget_set_size_request(GTK_WIDGET(drawing_layout), 1214, 668);
	gtk_container_add(GTK_CONTAINER(rock_layout), GTK_WIDGET(drawing_layout));

	current_window_info->layout_exists = true;

	// GdkPixbuf *image_pixbuf = gdk_pixbuf_new_from_file(get_path_to_image("rock.png"), NULL);
    // GtkWidget *image = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw_image"));
	// gtk_image_set_from_pixbuf(GTK_IMAGE(image), image_pixbuf);


    
	GtkWidget *draw_area = GTK_WIDGET(gtk_builder_get_object(current_window_info->builder, "draw"));
    g_signal_connect(draw_area, "button-press-event", G_CALLBACK(on_draw_button_press_event), current_window_info);
    g_signal_connect(draw_area, "button-release-event", G_CALLBACK(on_draw_button_release_event), current_window_info);
    g_signal_connect(draw_area, "draw", G_CALLBACK(on_draw_draw), current_window_info);
    g_signal_connect(draw_area, "motion-notify-event", G_CALLBACK(on_draw_motion_notify_event), current_window_info);
	gtk_widget_add_events(draw_area, GDK_BUTTON_MOTION_MASK | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);


}

void view_stone(t_model_message *model_message, t_current_window_info *current_layout_info){
	// if( !strcmp (get_current_user_to_talk(), model_message->from_user)){
	// 	printf("\n\n THERE %s", model_message->data);
		t_model_stone *stone_to_draw = get_stone_by_id(model_message->data);
		request_file_if_not_exist(stone_to_draw->path);
		saved = read_saved_from_file(stone_to_draw->path);
		add_to_saved(saved);
	// } else {

	// }

}

