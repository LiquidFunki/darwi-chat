#ifndef VIEW_TOOLS_H
#define VIEW_TOOLS_H
#include <gtk/gtk.h>
#include "libmx.h"

typedef struct s_current_window_info {
  GtkBuilder *builder;
  GtkWidget *main_window;
  bool layout_exists;
  void *data;
  int message_position_y;
}               t_current_window_info;

void delete_sign_entry_error(GtkEntry **entries);
void place_answer_error(GtkWidget *button);
void delete_answer_error(GtkWidget *button);
void place_sign_entry_error(GtkEntry **entries);
int is_valid_user_data(GtkEntry **info);
G_MODULE_EXPORT void entry_activate(GtkEntry* entry, GtkEntry **info);
t_current_window_info *create_current_window_info(void);

#endif
