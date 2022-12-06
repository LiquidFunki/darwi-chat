
int mx_strcmp(const char *s1, const char *s2) {

    int result = 0;
    int index = 0;

    for ( ; s1[index] != '\0' && s2[index] != '\0'; index++) {
        result = (int)*(s1 + index) - *(s2 + index);
        if (result != 0) {
            break;
        }
    }

    if (*(s1 + index) != *(s2 + index) && result == 0) {
        if (*(s1 + index) == '\0') result = -1;
        else result = 1;
    }

    return result;
}
