// Stablefree's Smith Number Generator
// smith.c
// Generates all the Smith numbers up to a passed integer variable.
// Feel free to use it as you please!

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define MAX_FACTOR (int) (max-1)/2
#define ASCII_TO_NUM 48
#define MAX_COL 10

void primeFactors(int max, int *factors);
int addFactors(int max, int *factors);

int main (int argc, char *argv[]) {
    assert(argc == 2);
    int max = atoi(argv[1]), i, count, factors[MAX_FACTOR], sumDigits, sumFactors;
    char digits[strlen(argv[1])+1];
    int col = 0;
    for (count = 2; count <= max; count++) {
        sumDigits = 0;
        sumFactors = 0;
        primeFactors(count, factors);
        sprintf(digits, "%d", count);
        for (i = 0; digits[i] != '\0'; i++) sumDigits += (int) digits[i] - ASCII_TO_NUM;
        sumFactors = addFactors(count, factors);
        if (sumFactors == sumDigits) {printf("%d\t", count); col++;}
        if (col == MAX_COL) {printf("\n"); col = 0;}
    }
    return EXIT_SUCCESS;
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