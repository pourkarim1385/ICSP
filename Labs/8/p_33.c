#include <stdio.h>
#include <stdlib.h>

int len_file(FILE *file){
    char temp = '\0';
    int length=0 ;
    while ( 1 ){
        temp = getc(file);
        if (feof(file))
        {
            break ;
        }
        length++;
    }
    return length;
}

char *read_input_file (char *file_address, int *file_length)
{
    FILE *input = fopen (file_address , "r");
    *file_length = len_file(input);
    fseek (input, 0, SEEK_SET);

    char *in_order_array = ( char *) calloc((*file_length) , sizeof (char));

    fread (in_order_array, sizeof(char), *file_length, input);
    fclose(input);

    for (int i = 0; i < *file_length; i++) {
        printf("%c", in_order_array[i]);
    }

    return in_order_array ;
}

char reverse_char (char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
    }
    else if (ch >= 'a' && ch <= 'z') {
        ch = ch - 'a' + 'A';
    }
    return ch;
}

char *reverse_array (char *in_order_array, const int size){
    char *reversed_array = ( char *) calloc ( size, sizeof ( char ));
    for (int i = 0 , j = size - 1; i < size; i++, j--){
        char a = reverse_char(in_order_array[i]);
        char b = reverse_char(in_order_array[j]);
        reversed_array[i] = b;
        reversed_array[j] = a;
    }
    return reversed_array;
}

void write_reversed_array_in_file (char *in_order_array, char *file_address, const int file_length){
    char *reversed_array = reverse_array (in_order_array, file_length);
    FILE *output = fopen(file_address, "w");
    fwrite(reversed_array, sizeof(char), file_length, output);
    free(reversed_array);
    fclose(output);
}

int main (void) {
    char input_address[] = "Input.txt";
    char output_address[] = "Output.txt";
    int file_length = 0;
    char *in_order_array = read_input_file (input_address, &file_length);
    write_reversed_array_in_file(in_order_array, output_address, file_length);
    return 0 ;
}
