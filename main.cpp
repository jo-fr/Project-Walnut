#include "core/Server.h"

#define PORT 8080

int main(){
    Server S = Server();

    S.Run(PORT);

    return 0;
}
