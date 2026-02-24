
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*------------Basic Encoder 2026 Apache License 2.0------------*/


int Encoder(FILE *file){
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed\n");
        return 1;
    }
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    for (long i = 0; i < file_size; i++) {
        buffer[i] = buffer[i] + 612; // Shift character by 612
    }
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    free(buffer);
    return 0;
}

int unencoder(FILE *file){
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Memory allocation failed\n");
        return 1;
    }
    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    for (long i = 0; i < file_size; i++) {
        buffer[i] = buffer[i] - 612; // Shift character back by 612
    }
    fseek(file, 0, SEEK_SET);
    fwrite(buffer, 1, file_size, file);
    free(buffer);
    return 0;
}
int main(){
    if (__argc != 3) {
        puts("Usage: <input_file> <Mode e-encoder u-unencoder>\n");
        return 1;
    }
    FILE *input_file = fopen(__argv[1], "rb+");
    if (input_file == NULL) {
        perror("Error opening file\n");
        return 1;
    }
    if (__argv[2][0] == 'e')
    {
        Encoder(input_file);
    }
    else if (__argv[2][0] == 'u')
    {
        unencoder(input_file);
    }
    else{
        puts("Usage: <input_file> <Mode e-encoder u-unencoder>\n");
    }
    fclose(input_file);
    return 0;


}
