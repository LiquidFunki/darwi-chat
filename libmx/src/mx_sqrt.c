
int mx_sqrt(int x) {
    if (x <= 0) return 0;
    int square_root = x;
    int div = x;

    while (1) {
        div = (x / div + div) / 2;
        if (square_root > div) square_root = div;
        else break;
    }
    if (square_root * square_root != x) square_root = 0;
    return square_root;
}
