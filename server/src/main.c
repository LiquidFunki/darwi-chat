#include "server.h"


int main() {

    init_tables();
    rewrite_message();

    run_server();
}
