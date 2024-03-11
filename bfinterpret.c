/* Todo: Implement all the command */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t data[32768]; /* 32 KB of RAM */
uint8_t* dataptr = data; /* Data pointer */
char inst[8192]; /* 8 KB of ROM */
char* instptr = inst; /* Instruction pointer */

void move_inst(char* ptr, int direction) {
    if (direction) ptr++; else ptr--;
}

void cmd_greater() {
    dataptr++;
}

void cmd_lesser() {
    dataptr--;
}

void cmd_plus() {
    (*dataptr)++;
}

void cmd_minus() {
    (*dataptr)--;
}
//maybe this is the culprit?
void cmd_dot() {
    char printable = (char) *dataptr;
    fputc(printable, stdout);
}

//fix this it does NOT work
void cmd_comma() {
    char readable[1] = {(char) fgetc(stdin)};
    fflush(stdin);
    *dataptr = (uint8_t) atoi(readable);
}
//also fix this it does nothing
char* check_brackets(int direction) {
    char* temp = instptr;
    char* temp2 = inst;
    if (direction) direction = 1;
    if (direction < 0) direction = 0;
    int open_brackets = 1;

    while ((direction && (temp - temp2 < sizeof(inst))) || ((!direction) &&  temp - temp2 > 0)) {
        if (direction) move_inst(temp, 1); else move_inst(temp, 0);
        if ((direction && *temp == '[') || (!direction && *temp == ']')) open_brackets++;
        if ((direction && *temp == ']') || (!direction && *temp == '[')) open_brackets--;
        if (!open_brackets) break;
    }

    if (open_brackets) {
        fputs("\nOpen brackets found. Aborting.", stdout);
        //somehow make this exit
    }

    return temp;
}

void cmd_leftbracket() {
    if(!(*dataptr)) instptr = check_brackets(1);
}

void cmd_rightbracket() {
    if(!(*dataptr)) instptr = check_brackets(0);
}

void reading_loop() {
    for (int i = 0; i <= sizeof(inst); i++){
        switch(*instptr){
            case '>':
                cmd_greater();
                break;
            
            case '<':
                cmd_lesser();
                break;
            
            case '+':
                cmd_plus();
                break;

            case '-':
                cmd_minus();
                break;
            
            case '.':
                cmd_dot();
                break;

            case ',':
                cmd_comma();
                break;
            
            case '[':
                cmd_leftbracket();
                break;
            
            case ']':
                cmd_rightbracket();
                break;
        }
        move_inst(instptr, 1);
    }
}

int main(int argc, char *argv[]) {
    FILE* fileptr;
    char exitcond [] = {'-', '1'};
    int errcatch = 0;

    if (!strcasecmp(argv[1], "-v")){
        fputs("v1.0\n", stdout);
        goto end;
    }

    else if (!strcasecmp(argv[1], "-f")){
        fileptr = fopen(argv[2], "r");
        if (fileptr == NULL){
            perror("File not specified or does not exist");
            errcatch = 1;
            goto end;
        }
        fgets(inst, sizeof(inst), fileptr);
        fclose(fileptr);
        reading_loop();
    }

    else {
        fputs("\nEnter Brainfuck code, -1 to exit: ", stdout);
        fgets(inst, sizeof(inst), stdin);
        if (!strncmp(inst, exitcond, 2)){
            goto end;
        }
        reading_loop(); 
    }

end:
    return errcatch;

}