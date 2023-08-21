#include "PlayKey.h"

void create_cipher_table(wchar_t *key, wchar_t cipher_table[SIZE][SIZE]) {
    int key_length = wcslen(key);
    int alphabet[36] = {0};
    int index = 0;
  

    for (int i = 0; i < key_length; ++i) {
        if (key[i] >= L'а' && key[i] <= L'я' && !alphabet[key[i] - L'а']) {

            cipher_table[index / SIZE][index % SIZE] = key[i];

            alphabet[key[i] - L'а'] = 1;

            index++;
        }
        else if (key[i] == randsimvol && !alphabet[32]) {

            cipher_table[index / SIZE][index % SIZE] = key[i];

            alphabet[32] = 1;

            index++;

        }
        else if (key[i] == L' ' && !alphabet[33]) {

            cipher_table[index / SIZE][index % SIZE] = spaceequvilant;

            alphabet[33] = 1;

            index++;

        }        
        else if (key[i] == randsimvol2 && !alphabet[34]) {

            cipher_table[index / SIZE][index % SIZE] = key[i];

            alphabet[34] = 1;

            index++;

        }       
        else if (key[i] == L'ё' && !alphabet[35]) {

            cipher_table[index / SIZE][index % SIZE] = key[i];

            alphabet[35] = 1;

            index++;

        }               
    }

    for (int i = 0; i < 36; ++i) {

        if (!alphabet[i] && (L'а' + i)<= L'я') {
            cipher_table[index/ SIZE][index % SIZE] = L'а' + i;
            index++;
        }

        else if ((L'а' + i) > L'я'){
            if (!alphabet[32]) {cipher_table[index / SIZE][index % SIZE] = randsimvol; alphabet[32] = 1;} else
            if (!alphabet[33]) {cipher_table[index / SIZE][index % SIZE] = spaceequvilant; alphabet[33] = 1;} else
            if (!alphabet[34]) {cipher_table[index / SIZE][index % SIZE] = randsimvol2; alphabet[34] = 1;} else
            if (!alphabet[35]) {cipher_table[index / SIZE][index % SIZE] = L'ё'; alphabet[35] = 1;}

            index++;
        }

    }
    
}

void get_pos(const wchar_t cipher_table[SIZE][SIZE], wchar_t letter, int *row, int *col){
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (letter == ' ') return get_pos(cipher_table, spaceequvilant, row, col);
            if (cipher_table[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void PlayKey(wchar_t *input, wchar_t *key, wchar_t *output) {
    wchar_t cipher_table[SIZE][SIZE];
    create_cipher_table(key, cipher_table);
    int input_length = wcslen(input);
    int output_index = 0;
    
    int *reg = malloc(input_length * sizeof(int));


    int i = 0;

    for (int j = 0; j < input_length; j++){

            if (input[j] >= L'А' && input[j] <= L'Я'){

                reg[j] = 1;

                input[j] +=32;
            } 
            else if (input[j] == L'Ё'){
                input[j] = L'ё';
                reg[j] = 1;
            }
            else reg[j] = 0;

        }

    while(i < input_length){
        
        

        if (input[i] == L' ') {
            output[output_index++] = L' ';
            i++;
            continue;
        }

        wchar_t first = input[i];
        wchar_t second = i + 1 < input_length ? input[i + 1] : randsimvol; // randsimvol - rand simvol

        int row1, col1, row2, col2;
        get_pos(cipher_table, first, &row1, &col1);
        get_pos(cipher_table, second, &row2, &col2);

        if (row1 == row2) {
            output[output_index++] = cipher_table[row1][(col1 + 1) % SIZE];
            output[output_index++] = cipher_table[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            output[output_index++] = cipher_table[(row1 + 1) % SIZE][col1];
            output[output_index++] = cipher_table[(row2 + 1) % SIZE][col2];
        } else {
            output[output_index++] = cipher_table[row1][col2];
            output[output_index++] = cipher_table[row2][col1];
        }

        i += 2;
    }

    output[output_index] = L'\0';
    
        if (output[output_index - 1] == randsimvol) output[output_index - 1] = L'\0';
        else output[output_index] = L'\0';

        for(int i = 0; i < input_length; i++){

            if (reg[i] == 1) 
                
                if (output[i] == L'ё') output[i] = L'Ё';
                // else
                // if (output[i] == L' ') output[i] = upperspaceequivalent;
                else output[i] -= 32;
        }
    
}

void DePlayKey(wchar_t *input, wchar_t *key, wchar_t *output) {
    wchar_t cipher_table[SIZE][SIZE];
    create_cipher_table(key, cipher_table);

    int input_length = wcslen(input);
    int output_index = 0;

    int *reg = malloc(input_length * sizeof(int));


    int i = 0;

    for (int j = 0; j < input_length; j++){

            if (input[j] >= L'А' && input[j] <= L'Я' || input[j] == (L' ' - 32) || input[j] == (spaceequvilant - 32) ||input[j] == (randsimvol2 - 32) || input[j] == randsimvol - 32){

                reg[j] = 1;

                input[j] +=32;
            } 
            else if (input[j] == L'Ё'){
                input[j] = L'ё';
                reg[j] = 1;
            }
                else reg[j] = 0;

        }
    while(i < input_length){

        if (input[i] == L' ') {
            output[output_index++] = L' ';
            i++;
            continue;
        }

        wchar_t first = input[i];
        wchar_t second = i + 1 < input_length ? input[i + 1] : randsimvol; // randsimvol - rand simvol


        int row1, col1, row2, col2;
        get_pos(cipher_table, first, &row1, &col1);
        get_pos(cipher_table, second, &row2, &col2);

        if (row1 == row2) {
            output[output_index++] = cipher_table[row1][(col1 - 1 + SIZE) % SIZE];
            output[output_index++] = cipher_table[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            output[output_index++] = cipher_table[(row1 - 1 + SIZE) % SIZE][col1];
            output[output_index++] = cipher_table[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            output[output_index++] = cipher_table[row1][col2];
            output[output_index++] = cipher_table[row2][col1];
        }

        i += 2;
    }
   if (output[output_index - 1] == randsimvol) output[output_index - 1] = L'\0';
        else output[output_index] = L'\0';

        for(int i = 0; i < input_length; i++){

            if (reg[i] == 1) 
                
                if (output[i] == L'ё') output[i] = L'Ё';

                else output[i] -= 32;

            if (output[i] == spaceequvilant)

                output[i] = L' ';
        }
}