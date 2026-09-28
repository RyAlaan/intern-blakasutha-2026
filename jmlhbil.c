#include <stdio.h>

int main(){
    int i = 1, n, jumlah = 0;

    printf("Masukan angka: ");
    scanf("%d", &n );

    while (i <= n) {
        jumlah += i;
        i++;
    }
    printf("jumlah = %d", jumlah);

    return 0;
}