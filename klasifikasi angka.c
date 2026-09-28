#include <stdio.h>

int main() {
    int angka;

    printf("Masukkan angka: ");
    scanf("%d", &angka);

    if (angka > 0) {
        printf("Bilangan Positif");
    } else if (angka == 0) {
        printf("Nol");
    } else if (angka < 0) {
        printf("Bilangan Negatif");
    } else {
        printf("Eror");
    }

    return 0;
}