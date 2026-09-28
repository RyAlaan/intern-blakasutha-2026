#nama program
print("program klasifikasi umur")

#deklarsi variabrle
umur = int(input("Masukan umur: "))

#program utama
if umur >= 0 and umur <=5 :
    print("Kategori: Balita")
elif umur >= 6 and umur <=12 :
    print("Kategori: Anak-anak")
elif umur >= 13 and umur <=17 :
    print("Kategori: Remaja")
elif umur >= 18 and umur <=59 :
    print("Kategori: Dewasa")
elif umur >= 60 :
    print("Kategori: Lansia")
else :
    print ("Umur tidak valid")
    
