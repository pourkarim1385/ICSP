#include <stdio.h>
#include <string.h>
#define INPUT_FILE_ADDRESS " Input.txt "
int main () {
    FILE *input = fopen ( INPUT_FILE_ADDRESS , " r+");
    char *text = " we love coding!!" ;
    char *text2 = "Now we know how to use files in c:)"
    ;
    fseek (input , 14, SEEK_SET);
    fwrite (text , sizeof(char) , 17 , input);
    fseek (input , 0 , SEEK_END);
    fprintf(input, "\n%s", text2);
    return 0 ;
}
