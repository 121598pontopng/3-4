#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, vec[100] = {0};
    char str[100];

    printf("Enter the number of integers: ");
    scanf("%d", &n);
    printf("Enter the integers:\n");
    read_vector(vec, n);
    encode_vector(vec, n, str);
    printf("Encoded string: %s\n", str);
    for (i = 0; i < 100; i++) {
        vec[i] = 0; // reset vector for decoding
    }
    decode_string(str, vec);
    printf("Decoded vector: ");
    for (i = 0; i < n; i++) {
        printf("%d", vec[i]);
    }
    printf("\n");
    return 0;
}


void read_vector(int *vec, int n) {
    int i, num, digit;
    for (i = 0; i < n; i++) {
        scanf("%d", &num);
        while (num > 0) {
            digit = num % 10;
            vec[i * 10 + digit]++; // store digit count in vector
            num /= 10;
        }
    }
}

void encode_vector(int *vec, int n, char *str) {
    int i, j, k, count;
    for (i = 0, j = 0; i < n * 10; i++) {
        if (vec[i] > 0) {
            count = vec[i];
            while (count > 0) {
                if (count >= 9) {
                    str[j++] = '9' + '0'; // encode count of 9 repetitions
                    str[j++] = i % 10 + '0'; // encode digit
                    count -= 9;
                } else {
                    str[j++] = count + '0'; // encode count of repetitions
                    str[j++] = i % 10 + '0'; // encode digit
                    count = 0;
                }
            }
        }
    }
    str[j] = '\0'; // add null terminator to string
}

void decode_string(char *str, int *vec) {
    int i, j, count, digit;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] >= '1' && str[i] <= '9') {
            count = str[i] - '0';
            digit = str[i+1] - '0';
            vec[j * 10 + digit] += count; // store digit count in vector
            if (count == 9) {
                vec[j * 10 + digit + 1] += 1; // handle case of 9 repetitions
            }
            i++; // skip next character
        } else {
            printf("Error: invalid encoding.\n");
            exit(1);
        }
    }
}

