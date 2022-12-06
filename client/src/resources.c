#include "resources.h"

char* get_path_to_resources() {

    size_t path_max = 1024;
    char* pwd = mx_strnew(path_max);

    if (getcwd(pwd, path_max)) {
        printf("getcwd is null in get path to resources\n");
        free(pwd);
        return NULL;
    };

    char* resources = NULL;
    if (pwd[strlen(pwd) - 1] == '/') {
        resources = "client/resources/";
    } else {
        resources = "/client/resources/";
    }

    resources = mx_strjoin(pwd, resources);
    free(pwd);
    return resources;
}

char* get_path_to_glade(char *glade_name) {
    char *path_to_folder = "./client/resources/static/templates/";
    char *full_glade_path = mx_strjoin(path_to_folder, glade_name);
    return full_glade_path;
}

char* get_path_to_style(char *style_name) {
    char *path_to_folder = "./client/resources/static/styles/";
    char *full_style_path = mx_strjoin(path_to_folder, style_name);
    return full_style_path;
}

char* get_path_to_image(char *image_name) {
    char *path_to_folder = "./client/resources/static/images/";
    char *full_image_path = mx_strjoin(path_to_folder, image_name);
    return full_image_path;
}


