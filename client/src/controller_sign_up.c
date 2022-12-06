#include "controller_sign_up.h"


int controller_sign_up(char* user_name, char* password) {

    t_model_user* user = new_model_user(user_name, password);
    int exit_status;
    if(send_sign_up_request(user)){
        exit_status = 0;
    }else {
        exit_status = 1;
    }
    // send_set_user_era_request(user_name, encrypt_pswd(password), ENLIGHTMENT); //TODO: CHAGE/REMOVE IT  !!!!
    free_model_user(&user);

    return exit_status;

}