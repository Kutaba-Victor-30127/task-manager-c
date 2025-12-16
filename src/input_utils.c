#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "input_utils.h"

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int isValidDate(int day, int month, int year) {
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12)   return 0;
    if (day < 1)                   return 0;

    int daysInMonth;

    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            daysInMonth = 31; break;
        case 4: case 6: case 9: case 11:
            daysInMonth = 30; break;
        case 2:
            daysInMonth = isLeapYear(year) ? 29 : 28;
            break;
        default:
            return 0;
    }

    if (day > daysInMonth) return 0;
    return 1;
}

// INPUT NUMERIC CU LIMITA
int readIntInRange(const char *prompt, int min, int max) {
    char buffer[64];
    char *endptr;
    long value;
    
    while(1){
        printf("%s",prompt);
        if (!fgets(buffer,sizeof(buffer),stdin)){
            printf("Eroare la citire\n");
            continue;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';

        if (buffer[0] == '\0'){
            printf("Input gol. Introdu un numar\n");
            continue;
        }

        value = strtol(buffer,&endptr,10);

        if (*endptr != '\0'){
            printf("Input invalid. Foloseste doar cifre\n");
            continue;
        }

        if (value<min || value>max){
            printf("Input invalid. Trebuie sa fie intre %d si %d\n",min,max);
            continue;
        }
        return (int) value;
    }
}

// input numar pozitiv
int readPositiveInt(const char *prompt){
    char buffer[64];
    char *endptr;
    long value;

    while(1){
        printf("%s",prompt);
        if(!fgets(buffer,sizeof(buffer),stdin)){
            printf("Eroare la citire\n");
            continue;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        if (buffer[0] == '\0'){
            printf("Input gol.Adauga numar\n");
            continue;
        }
        value = strtol(buffer,&endptr,10);

        if (*endptr != '\0'){
            printf("Input invalid. Foloseste doar cifre\n");
            continue;
        }
        if (value <= 0){
            printf("Numarul trebuie sa fie pozitiv\n");
            continue;
        }
        if (value > 2147483647L){
            printf("Numarul e prea mare\n");
            continue;
        }
        return (int)value;
    }
}

// Citire data
Date readDate(void) {
    int day, month, year;

    while (1) {
        char buffer[64];
        int consumed;

        printf("Deadline: ");  

        if (!fgets(buffer, sizeof(buffer), stdin)) {
            printf("Eroare citire.\n");
            continue;
        }

        // incearca sa citeasca EXACT 3 numere
        if (sscanf(buffer, "%d %d %d%n", &day, &month, &year, &consumed) != 3 ||
            (buffer[consumed] != '\0' && buffer[consumed] != '\n' && buffer[consumed] != '\r')) {
            printf("Input invalid. Introdu formatul: zi luna an (ex: 12 12 2025)\n");
            continue;
        }

        if (!isValidDate(day, month, year)) {
            printf("Data invalida. Introdu o data calendaristica reala.\n");
            continue;
        }

        Date d = { day, month, year };
        return d;
    }
}

