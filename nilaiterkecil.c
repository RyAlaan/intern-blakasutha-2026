#include <stdio.h>

int main(){
    int n, terkecil;

    for (int i = 1 ; i <= 10; i++) {
        printf("Masukan angka ke-%d: ", i);
        scanf("%d",&n);

        if ( i == 1 || n < terkecil ) {
            terkecil = n;
        }
    }

    printf ("angka terkecil adalah:%d\n", terkecil );
    return 0;
}