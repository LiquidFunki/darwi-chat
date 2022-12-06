#include "wrong_messages.h"
static cJSON* alphabet = NULL;

cJSON* get_alphabet(){
    return alphabet;
}

void rewrite_message() {
    alphabet = create_protocol();

    add_to_protocol_string(alphabet, "a", "xeo");
    add_to_protocol_string(alphabet, "b", "dgq");
    add_to_protocol_string(alphabet, "c", "szk");
    add_to_protocol_string(alphabet, "d", "bpg");
    add_to_protocol_string(alphabet, "e", "iox");
    add_to_protocol_string(alphabet, "f", "vph");
    add_to_protocol_string(alphabet, "g", "pq9");
    add_to_protocol_string(alphabet, "h", "fpn");
    add_to_protocol_string(alphabet, "i", "lej");
    add_to_protocol_string(alphabet, "j", "lit");
    add_to_protocol_string(alphabet, "k", "gcq");
    add_to_protocol_string(alphabet, "l", "itj");
    add_to_protocol_string(alphabet, "m", "nwm");
    add_to_protocol_string(alphabet, "n", "mvh");
    add_to_protocol_string(alphabet, "o", "cax");
    add_to_protocol_string(alphabet, "p", "qgb");
    add_to_protocol_string(alphabet, "q", "gdp");
    add_to_protocol_string(alphabet, "r", "kxn");
    add_to_protocol_string(alphabet, "s", "zxc");
    add_to_protocol_string(alphabet, "t", "jil");
    add_to_protocol_string(alphabet, "u", "voy");
    add_to_protocol_string(alphabet, "v", "wyv");
    add_to_protocol_string(alphabet, "w", "vmn");
    add_to_protocol_string(alphabet, "x", "ayo");
    add_to_protocol_string(alphabet, "y", "uvj");
    add_to_protocol_string(alphabet, "z", "csx");

    add_to_protocol_string(alphabet, "A", "FXH");
    add_to_protocol_string(alphabet, "B", "DRP");
    add_to_protocol_string(alphabet, "C", "OGK");
    add_to_protocol_string(alphabet, "D", "BPO");
    add_to_protocol_string(alphabet, "E", "FAL");
    add_to_protocol_string(alphabet, "F", "ELT");
    add_to_protocol_string(alphabet, "G", "CQK");
    add_to_protocol_string(alphabet, "H", "TFL");
    add_to_protocol_string(alphabet, "I", "JLT");
    add_to_protocol_string(alphabet, "K", "RCG");
    add_to_protocol_string(alphabet, "L", "JTI");
    add_to_protocol_string(alphabet, "M", "NWH");
    add_to_protocol_string(alphabet, "N", "MVH");
    add_to_protocol_string(alphabet, "O", "QCX");
    add_to_protocol_string(alphabet, "P", "QBR");
    add_to_protocol_string(alphabet, "Q", "OGP");
    add_to_protocol_string(alphabet, "R", "KPB");
    add_to_protocol_string(alphabet, "S", "ZCZ");
    add_to_protocol_string(alphabet, "T", "ILJ");
    add_to_protocol_string(alphabet, "U", "VWN");
    add_to_protocol_string(alphabet, "V", "WUN");
    add_to_protocol_string(alphabet, "W", "VUM");
    add_to_protocol_string(alphabet, "X", "AOY");
    add_to_protocol_string(alphabet, "Y", "XUJ");
    add_to_protocol_string(alphabet, "Z", "CSK");
}

void wrong_message(char** str) {
    char* message = *str ;
    srand(time(NULL));
    int random = rand() % 7 + 5;
    char key[2]; key[1] = '\0';
    for(int i = rand() % 3; i < mx_strlen(message); i += random) {
        if((message + i) != NULL) {
            key[0] = message[i];
            char* value = get_from_protocol_string(alphabet, key);
            if(value){
                int random_pos = rand() % 3;
                message[i] = value[random_pos];
            }
        }
    }
}