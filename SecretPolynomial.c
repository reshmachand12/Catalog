#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int x; // key
    long long y; // decoded value
} Point;

// Function to convert a string from a specific base to a decimal integer
long long convert_to_decimal(const char *value, int base) {
    long long result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++) {
        char digit = value[length - 1 - i];
        int digit_value;

        if (digit >= '0' && digit <= '9') {
            digit_value = digit - '0';
        } else if (digit >= 'A' && digit <= 'F') {
            digit_value = digit - 'A' + 10;
        } else if (digit >= 'a' && digit <= 'f') {
            digit_value = digit - 'a' + 10;
        } else {
            return -1; // Invalid character
        }

        if (digit_value >= base) {
            return -1; // Invalid digit for the base
        }

        result += digit_value * (long long)pow(base, i);
    }
    return result;
}

// Function to perform Lagrange interpolation to evaluate polynomial at x = 0
long long lagrange_interpolation(Point *points, int k, int x) {
    long long total = 0;
   
    for (int i = 0; i < k; i++) {
        long long xi = points[i].x;
        long long yi = points[i].y;
        long long term = yi;

        for (int j = 0; j < k; j++) {
            if (j != i) {
                long long xj = points[j].x;
                term *= (x - xj);
                term /= (xi - xj);
            }
        }
        total += term;
    }
    return total;
}

int main() {
    // Example of first test case
    // Simplified for testing; normally you would parse JSON
    Point points1[3] = {
        {1, convert_to_decimal("4", 10)},
        {2, convert_to_decimal("111", 2)},
        {3, convert_to_decimal("12", 10)}
    };
   
    // Example of second test case
    Point points2[6] = {
        {1, convert_to_decimal("28735619723837", 10)},
        {2, convert_to_decimal("1A228867F0CA", 16)},
        {3, convert_to_decimal("32811A4AA0B7B", 12)},
        {4, convert_to_decimal("917978721331A", 11)},
        {5, convert_to_decimal("1A22886782E1", 16)},
        {6, convert_to_decimal("28735619654702", 10)}
    };
   
    // Process first test case
    long long c1 = lagrange_interpolation(points1, 3, 0);
    printf("The constant term c for test case 1 is: %lld\n", c1);
   
    // Process second test case
    long long c2 = lagrange_interpolation(points2, 6, 0);
    printf("The constant term c for test case 2 is: %lld\n", c2);

    return 0;
}
