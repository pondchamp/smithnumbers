// Stablefree's Smith Number Generator
// smith.c
// Generates all the Smith numbers up to a passed integer variable.
// Feel free to use it as you please!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define MAX_FACTOR (unsigned long long) (max-1)/2
#define ASCII_TO_NUM 48
#define MAX_COL 10

void primeFactors(unsigned long long max, unsigned long long *factors);
unsigned long long addFactors(unsigned long long max, unsigned long long *factors);
int isSmith (unsigned long long max);

int main (int argc, char *argv[]) {
    assert(argc == 3);
    unsigned long long max = atoi(argv[2]), count;
    assert (max > 0);
    int col = 0;
    if (!strcmp(argv[1], "-all")) {
        for (count = 2; count <= max; count++) {
            if (isSmith (count)) {printf("%llu\t", count); col++;}
            if (col == MAX_COL) {printf("\n"); col = 0;}
        }
    } else if (!strcmp(argv[1], "-check")) {
        if (isSmith (max)) printf("%llu is a Smith number!\n", max);
        else printf("%llu is not a Smith number!\n", max);
    } else printf("Invalid arguments. Valid arguments are '-all' and '-check'.\n");
    return EXIT_SUCCESS;
}

int isSmith (unsigned long long max) {
    int i, sumDigits = 0, sumFactors = 0;
    unsigned long long *factors = malloc(sizeof(unsigned long long)*MAX_FACTOR);
    assert(factors != NULL);
    char digits[50];
    primeFactors(max, factors);
    sprintf(digits, "%llu", max);
    for (i = 0; digits[i] != '\0'; i++) sumDigits += (int) digits[i] - ASCII_TO_NUM;
    sumFactors = addFactors(max, factors);
    free(factors);
    return (sumFactors == sumDigits);
}

void primeFactors(unsigned long long max, unsigned long long *factors) {
    unsigned long long remain = max;
    int i, j = 0;
    for (i = 0; i < MAX_FACTOR; i++) factors[i] = -1;
    while (remain != 1) {
        for (i = 2; i < remain/2; i++) {
            if (round(remain/(float) i) == (remain/(float) i)) {
                factors[j++] = i;
                remain /= i;
                break;
            }
        }
        if (i >= remain/2) {
            factors[j++] = remain;
            break;
        }
    }
}

unsigned long long addFactors(unsigned long long max, unsigned long long *factors) {
    int i = 0, n;
    unsigned long long sum = 0;
    while ((i < MAX_FACTOR) && (factors[i] != -1)) {
        n = factors[i];
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }
        i++;
    }
    return sum;
}