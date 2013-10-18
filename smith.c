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

#define MAX_FACTOR (int) (max-1)/2
#define ASCII_TO_NUM 48
#define MAX_COL 10

void primeFactors(int max, int *factors);
int addFactors(int max, int *factors);
int isSmith (int max);

int main (int argc, char *argv[]) {
    assert(argc == 3);
    int max = atoi(argv[2]), count;
    assert (max > 0);
    int col = 0;
    if (!strcmp(argv[1], "-all")) {
        for (count = 2; count <= max; count++) {
            if (isSmith (count)) {printf("%d\t", count); col++;}
            if (col == MAX_COL) {printf("\n"); col = 0;}
        }
    } else if (!strcmp(argv[1], "-check")) {
        if (isSmith (max)) printf("%d is a Smith number!\n", max);
        else printf("%d is not a Smith number!\n", max);
    } else printf("Invalid arguments. Valid arguments are '-all' and '-check'.\n");
    return EXIT_SUCCESS;
}

int isSmith (int max) {
    int i, factors[MAX_FACTOR], sumDigits = 0, sumFactors = 0;
    char digits[50];
    primeFactors(max, factors);
    sprintf(digits, "%d", max);
    for (i = 0; digits[i] != '\0'; i++) sumDigits += (int) digits[i] - ASCII_TO_NUM;
    sumFactors = addFactors(max, factors);
    return (sumFactors == sumDigits);
}

void primeFactors(int max, int *factors) {
    int remain = max;
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

int addFactors(int max, int *factors) {
    int i = 0, sum = 0, n;
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