#include <stdio.h>

int faktorial (int n) {
    if (n == 0 || n == 1){
    return 1;
    }else{
    return n*faktorial(n-1)

    }
}
int main() {
    int angka, hasil;

    printf("Masukan angka: ");
    scanf("%d", &angka);

    hasil = faktorial(angka);

    printf("faktorial dari %d adalah %d/n",angka, hasil)

    return 0;

}