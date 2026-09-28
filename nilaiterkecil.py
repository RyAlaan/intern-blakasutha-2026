terkecil = int(input("Masukan angka ke-1: "))

for i in range (2,11) :
   n = int(input(f"Masukan angka ke-{i}: "))

   if n < terkecil :
      terkecil = n


print ("Angka terkecil adalah: ",terkecil)

