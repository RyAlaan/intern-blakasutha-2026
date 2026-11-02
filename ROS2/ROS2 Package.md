Kalau workspace berisi semua file untuk robot, package berisi file spesifik untuk fungsi spesifik tertentu. Mengapa file untuk robot perlu dipisah lagi dalam package? Agar pengerjaan proyek lebih terstruktur, maintenance lebih mudah, dan program program tertentu bisa dicari dengan lebih mudah. Untuk membuat package:
```
cd (nama workspace)/

cd src/

ros2 pkg create --build-type ament_cmake --license Apache-2.0 (nama package)
```
Run command:

`dir` 

Untuk mengecek package yang telah dibuat. Lalu, run command:
```
cd ..

colcon build
```
Untuk kembali keluar dari file source, lalu melakukan build untuk package yang ada di source workspace.
