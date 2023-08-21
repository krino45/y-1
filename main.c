#include "PlayKey.h"

int main(int argc, char** argv){

    setlocale(LC_ALL, "");
    
    if(argc != 3){
        printf("Ошибка. При запуске программы, пишите: %s <файл для чтения> <файл для вывода> \n", argv[0]);
        exit(-1);
    }

    // Файл из командной строки
    FILE* inputFile = fopen(argv[1], "r");    

    if(inputFile == NULL){
        printf("Ошибка: файл не найден.\n");
        exit(-1);
    }
   
    // кол-во символов в файле
    long int size_words = 1;

    while(fgetwc(inputFile) != EOF){
        size_words++;
    }

    rewind(inputFile); // возвращаем указатель в начало файла
    wprintf(L"Размер: %ld\n", size_words);

    //Вводимый через файл текст
    wchar_t* text = (wchar_t*)malloc(size_words * sizeof(wchar_t));

    fgetws(text, size_words, inputFile);
    fclose(inputFile);

    for (int i = 0; i < size_words - 1; i++){

        if (!( (text[i] >= L'а' && text[i] <= L'я') || (text[i] >= L'А' && text[i] <= L'Я') || text[i] == L' ' || text[i] == L'ё' || text[i] == L'Ё') ){
            wprintf(L"\nОшибка: Текст файла содержит символы, не поддерживающиеся программой. Поддерживаемые символы: русский алфавит (оба регистра) и пробел. Символы новой строки не поддерживаются.\n");
            exit(-1);
        }

    }

    //Копия текста для проверки в конце программы
    wchar_t* textfortest = (wchar_t*)malloc(size_words * sizeof(wchar_t));

    wcscpy(textfortest, text);

    wprintf(L"Исходный текст: %ls\n", text);

    // заменяем символ переноса строки на символ конца строки
    int len = wcslen(text) + 1;
    if (text[len - 1] == L'\n') {
        text[len - 1] = L'\0';
        len--;
    }

    wchar_t* key = KEY;// Ключ шифрования. ТОЛЬКО НИЖНИЙ РЕГИСТР
    wchar_t* encrypted = (wchar_t*)malloc(2 * size_words * sizeof(wchar_t)); // зашифрованный текст

        PlayKey(text, key, encrypted);

    wprintf(L"Зашифрованный текст: %ls\n", encrypted);

    wchar_t* decrypted = (wchar_t*)malloc(size_words * sizeof(wchar_t)); // расшифрованный текст

    FILE* outputFile = fopen(argv[2], "w");
    
    fputws(encrypted, outputFile);
    
    fclose(outputFile);

        DePlayKey(encrypted, key, decrypted);

    wprintf(L"Расшифрованный текст: %ls\n", decrypted);

    if( wcscmp(textfortest, decrypted) == 0 ){
        wprintf(L"Совпало\n");
    }else{
        wprintf(L"Не совпало\n");
    }

    free(text);
    free(textfortest);
    free(encrypted);
    free(decrypted);
    return 0;
}