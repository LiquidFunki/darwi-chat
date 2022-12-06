
double mx_pow(double n, unsigned int pow) {

    if (pow == 0)
        return 1;
    if ((pow & 1) == 1) {
        return (mx_pow(n, pow - 1) * n);
    } else {
        return (mx_pow(n, pow / 2) * mx_pow(n, pow / 2));
    }
}
