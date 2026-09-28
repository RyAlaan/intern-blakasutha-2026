#program penentuan ZODIAK dari tanggal lahir
print ("Menentukan Zodiak ")

#ini deklarasi inputan variable
print ("Mohon Masukan tanggal, bulan dan tahun menggunakan angka")
tanggal = int (input("Masukan tanggal lahir: "))
bulan = int (input ("Masukan bulan lahir: "))
tahun = int (input ("Masukan tahun lahir: "))

#ini program pemrosesan penentuan zodiak
if (bulan == 3 and tanggal >= 21) or (bulan == 4 and tanggal <= 19 ) :
    print (" Zodiak : Aries")
elif (bulan == 4 and tanggal >= 20) or (bulan == 5 and tanggal <= 20 ) :
    print (" Zodiak : Taurus")
elif (bulan == 5 and tanggal >= 21) or (bulan == 6 and tanggal <= 20 ) :
    print (" Zodiak : Gemini")
elif (bulan == 6 and tanggal >= 21) or (bulan == 7 and tanggal <= 20 ) :
    print (" Zodiak : Cancer")
elif (bulan == 7 and tanggal >= 23) or (bulan == 8 and tanggal <= 22 ) :
    print (" Zodiak : Leo")
elif (bulan == 8 and tanggal >= 23) or (bulan == 9 and tanggal <= 22 ) :
    print (" Zodiak : Virgo")
elif (bulan == 9 and tanggal >= 23) or (bulan == 10 and tanggal <= 23 ) :
    print (" Zodiak : Libra")
elif (bulan == 10 and tanggal >= 23) or (bulan == 11 and tanggal <= 21 ) :
    print (" Zodiak : Scorpio")
elif (bulan == 11 and tanggal >= 22) or (bulan == 12 and tanggal <= 21 ) :
    print (" Zodiak : Sagitarius")
elif (bulan == 12 and tanggal >= 22) or (bulan == 1 and tanggal <= 19 ) :
    print (" Zodiak : Capricon")
elif (bulan == 1 and tanggal >= 20) or (bulan == 2 and tanggal <= 18 ) :
    print (" Zodiak : Aquarius")
elif (bulan == 2 and tanggal >= 19) or (bulan == 3 and tanggal <= 20 ) :
    print (" Zodiak : Pisces")
else :
    print ("Tanggal atau bulan tidak valid mohon coba lagi")

