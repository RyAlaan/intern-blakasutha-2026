## DDS (Data Distribution System)
Untuk suatu publisher dan subscriber bisa berkomunikasi, mereka harus ada di dalam ROS_DOMAIN_ID yang sama. By default, ROS_DOMAIN_ID adalah 0. Untuk mengubahnya:

`export ROS_DOMAIN_ID=(value)`

Untuk testing bisa dengan membuka dua terminal, lalu mengganti ROS_DOMAIN_ID menjadi selain 0 di salah satu terminal, dan menjalankan:

`ros2 run demo_nodes_cpp talker` di terminal 1
`ros2 run demo_nodes_py listener` di terminal 2

Hasilnya, karena ROS_DOMAIN_ID tidak sama, komunikasi antara publisher dan subscriber tidak dapat berjalan.

## Workspace
Workspace berisi semua file untuk robot, mulai dari source code, konfigurasi, dan lain-lain. Untuk membuat workspace:

`mkdir -p ~/(name)/src`

Setelah itu, change directory ke file workspace yang telah di build dan run command:

`dir` 

Yang berfungsi untuk melihat isi file.


> **Integrate VS Code to WSL Ubuntu**
> 1. Pertama, download extension WSL di VS Code Windows.
> 2. Kedua, setup extensionnya agar bisa running.
> 3. Ketiga, buka terminal WSL Ubuntu, change directory ke workspace yang diinginkan, lalu tulis: `code .`
> 4. Keempat, di VS Code yang sudah terhubung ke Ubuntu, kalau tampilannya sama seperti terminal Ubuntu, harusnya sudah aman.

> **Why source setup.bash?**
> Kita perlu melakukan command:
> `source /opt/ros/jazzy/setup.bash`
> setiap kali ingin menggunakan ROS 2 karena perintah tersebut dibutuhkan agar environment variables bisa didaftarkan di terminal sehingga perintah, library, dan packages ROS 2 bisa digunakan.
> Kita bisa melakukan command:
> `echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc`
> Agar source setup.bash bisa dijalankan secara otomatis setiap kali kita membuka terminal.

> **Why source setup.bash untuk workspace?**
> Kita juga perlu melakukan command:
> `source ~/(name)/install/setup.bash`
> Karena environment variables untuk workspace yang kita buat sendiri belum terdaftar pada source setup.bash sebelumnya.
> Sama seperti sebelumnya, kita bisa melakukan command:
> `echo "source ~/(name)/install/setup.bash" >> ~/.bashrc`
> Agar command bisa dijalankan secara otomatis setiap kali kita membuka terminal.


