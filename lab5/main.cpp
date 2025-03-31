#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Функция для вывода содержимого файла
void view_file() {
    FILE *in;
    char name[50];
    
    printf("Введите имя файла для просмотра: ");
    scanf("%49s", name);
    
    if ((in = fopen(name, "r")) == NULL) {
        perror("Ошибка открытия файла");
        return;
    }
    
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        putchar(ch);
    }
    
    fclose(in);
}

// Функция для подсчета пустых и непустых символов
void count_chars() {
    FILE *in;
    char name[50];
    int empty = 0, non_empty = 0;
    
    printf("Введите имя файла: ");
    scanf("%49s", name);
    
    if ((in = fopen(name, "r")) == NULL) {
        perror("Ошибка открытия файла");
        return;
    }
    
    int ch;
    while ((ch = fgetc(in)) != EOF) {
        if (isspace(ch) || !isprint(ch)) {
            empty++;
        } else {
            non_empty++;
        }
    }
    
    printf("Пустых символов: %d\nНепустых символов: %d\n", empty, non_empty);
    fclose(in);
}

// Функция для поиска подстроки в файле
void search_in_file() {
    FILE *in, *out;
    char name[50], substr[100];
    char line[1024];
    int line_num = 1;
    
    printf("Введите имя файла: ");
    scanf("%49s", name);
    printf("Введите подстроку для поиска: ");
    scanf("%99s", substr);
    
    if ((in = fopen(name, "r")) == NULL) {
        perror("Ошибка открытия файла");
        return;
    }
    
    if ((out = fopen("results.txt", "w")) == NULL) {
        perror("Ошибка создания файла результатов");
        fclose(in);
        return;
    }
    
    while (fgets(line, sizeof(line), in) != NULL) {
        if (strstr(line, substr) != NULL) {
            fprintf(out, "Строка %d: %s", line_num, line);
        }
        line_num++;
    }
    
    fclose(in);
    fclose(out);
    printf("Результаты поиска сохранены в файле results.txt\n");
}

// Функция для обработки номеров страниц
void process_page_numbers() {
    FILE *in, *out;
    char name[50];
    char buffer[1024];
    char page_num[20] = "";
    int in_page_header = 1;
    
    printf("Введите имя файла: ");
    scanf("%49s", name);
    
    if ((in = fopen(name, "r")) == NULL) {
        perror("Ошибка открытия файла");
        return;
    }
    
    if ((out = fopen("processed.txt", "w")) == NULL) {
        perror("Ошибка создания выходного файла");
        fclose(in);
        return;
    }
    
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        if (in_page_header) {
            int num, n;
            if (sscanf(buffer, "- %d -%n", &num, &n) == 1 && n == strlen(buffer)-1) {
                sprintf(page_num, "%d", num);
                in_page_header = 0;
                continue;
            }
            in_page_header = 0;
        }
        
        if (strchr(buffer, '\f') != NULL) {
            fprintf(out, "%s\n", page_num);
            page_num[0] = '\0';
            in_page_header = 1;
        } else {
            fputs(buffer, out);
        }
    }
    
    if (page_num[0] != '\0') {
        fprintf(out, "%s\n", page_num);
    }
    
    fclose(in);
    fclose(out);
    printf("Обработка завершена. Результат в файле processed.txt\n");
}

// Функция для шифрования/дешифрования файла
void encrypt_decrypt_file(const char *input_file, const char *output_file, const char *key) {
    FILE *in = fopen(input_file, "rb");
    if (in == NULL) {
        perror("Ошибка открытия входного файла");
        return;
    }
    
    FILE *out = fopen(output_file, "wb");
    if (out == NULL) {
        perror("Ошибка создания выходного файла");
        fclose(in);
        return;
    }
    
    int key_len = strlen(key);
    int key_index = 0;
    int ch;
    
    while ((ch = fgetc(in)) != EOF) {
        char encrypted = ch ^ key[key_index];
        fputc(encrypted, out);
        key_index = (key_index + 1) % key_len;
    }
    
    fclose(in);
    fclose(out);
    printf("Файл успешно обработан\n");
}

// Главное меню программы
int main(int argc, char *argv[]) {
    if (argc == 4) {
        // Режим шифрования/дешифрования из командной строки
        encrypt_decrypt_file(argv[1], argv[2], argv[3]);
        return 0;
    }
    
    int choice;
    do {
        printf("\nМеню:\n");
        printf("1. Просмотр содержимого файла\n");
        printf("2. Подсчет пустых и непустых символов\n");
        printf("3. Поиск подстроки в файле\n");
        printf("4. Обработка номеров страниц\n");
        printf("5. Шифрование/дешифрование файла (требует аргументов командной строки)\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                view_file();
                break;
            case 2:
                count_chars();
                break;
            case 3:
                search_in_file();
                break;
            case 4:
                process_page_numbers();
                break;
            case 5:
                printf("Для шифрования используйте командную строку:\n");
                printf("%s входной_файл выходной_файл ключ\n", argv[0]);
                break;
            case 0:
                printf("Выход...\n");
                break;
            default:
                printf("Неверный выбор\n");
        }
    } while (choice != 0);
    
    return 0;
}