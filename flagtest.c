#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_BITS 30

int userflags = 0;
int flagsin = 0;
char catcher [300];
char exitcond [] = {'-', '1'};

void write_flag (int applier) {
    userflags |= (1 << applier);
}

int read_flag (int applier) {
    int flag = userflags & (1 << applier);
    return flag;
}

void safety_check (char* applier) {
    flagsin = atoi (applier);

    for (int i = 0; !(applier[i] == '\n'); i++){
        if ((applier[i] < '0') || (applier[i] > '9')){
            flagsin = -2;
            break;
        }
    }

    if (flagsin < -1 || flagsin > MAX_BITS){
        printf ("Invalid data\n");
    }
    else{
        write_flag (flagsin);
    }
}

int find_log (int applier) {
    return log (applier) / log(2);
}

int main() {
    printf ("Enter a number from 0 to %d, -1 to exit\n", MAX_BITS);

    while (1) {
        fgets (catcher, sizeof(catcher), stdin);
        if (!(strncmp(catcher, exitcond, 2))) {
            break;
        }
        safety_check (catcher);
    }

    printf ("Value of userflags is %d\n", userflags);

    for (int i = 0; i <= MAX_BITS; i++) {
        if (read_flag(i) != 0)
            printf ("Flag %d is set\n", find_log(read_flag(i)));
    }

    return 0;
}