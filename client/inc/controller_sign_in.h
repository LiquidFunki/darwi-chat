#ifndef CONTROLLER_SIGN_IN_H
#define CONTROLLER_SIGN_IN_H

#include "model.h"
#include "sign_requests.h"
#include "view_tools.h"
#include "view_stone_age_page.h"
#include "view_egypt.h"
#include "view_home_page.h"
#include "view_enlightenment_era.h"
#include "view_modern_era.h"

int controller_sign_in(char* user_name, char* password);
void controller_view_user_era(GtkWidget **sign_in_info, t_current_window_info *current_window_info);

#endif
