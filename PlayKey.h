#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <wchar.h>
#define randsimvol 666
#define randsimvol2 667
#define spaceequvilant 6666

#define KEY L"соревы" // Ключ шифрования. ТОЛЬКО НИЖНИЙ РЕГИСТР
#define SIZE 6

void PlayKey(wchar_t *input, wchar_t *key, wchar_t *output);
void DePlayKey(wchar_t *input, wchar_t *key, wchar_t *output);