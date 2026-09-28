#include <stdio.h>

int main() {
    int i, hasil = 0;

    for (i = 1; i <= 10; i++) {
        if (i % 1 != 0) {
            hasil = hasil + (i * i);
        }
    }

    printf("Hasil = %d", hasil);

    return 0;
}