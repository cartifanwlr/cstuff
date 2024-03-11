/* Todo: Implement all the command */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

uint8_t data[32768]; /* 32 KB of RAM */
uint8_t* dataptr = data; /* Data pointer */
char inst[8192]; /* 8 KB of ROM */
char* instptr = inst; /* Instruction pointer */

void move_inst() {
    instptr++;
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

void cmd_dot() {
    char printable = (char) *dataptr;
    fputc(printable, stdout);
}
//fix this it does NOT work
void cmd_comma() {
    char readable[1] = {(char) fgetc(stdin)};
    *dataptr = (uint8_t) atoi(readable);
}

/* record first bracket, move until you see second bracket, find the offset*/
char* check_brackets(int direction) {
    
}

//code should ideally run within these two funcs
void cmd_leftbracket() {
    

}

void cmd_rightbracket() {

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
        move_inst();
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