#include "core/Server.h"

#define PORT 8080

int main(int argc, char const *argv[]){
    Server S = Server();

    S.Run(PORT);

    return 0;
}
