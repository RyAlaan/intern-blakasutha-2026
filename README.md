# intern-blakasutha-2026

Repositori pembelajaran magang yang berisi kumpulan program dari beberapa area:

- **Microcontroller** — dasar Arduino, ESP32, dan STM32 (LED, tombol, joystick, WiFi, UART).
- **OOP** — contoh konsep Object-Oriented Programming dalam C++.
- **RangkaBawah** — program kendali rangka bawah robot 4 roda: joystick PS2, keypad, keyboard, ESP-NOW, dan motor driver.
- **ROS2** — catatan belajar ROS 2 Jazzy (workspace, topic, service).

Dokumen ini menjelaskan struktur folder, fungsi tiap file, alur komunikasi, pemetaan pin, dan cara menjalankan programnya.

---

## Daftar Isi

1. [Struktur Repository](#struktur-repository)
2. [Cara Menjalankan](#cara-menjalankan)
3. [Arsitektur Komunikasi RangkaBawah](#arsitektur-komunikasi-rangkabawah)
4. [Microcontroller](#1-microcontroller)
   - [Arduino](#11-arduino)
   - [ESP32](#12-esp32)
   - [STM32](#13-stm32)
5. [OOP](#2-oop)
6. [RangkaBawah](#3-rangkabawah)
   - [AnalogStick](#31-analogstick)
   - [Controller ESP-32](#32-controller-esp-32)
   - [Keyboard](#33-keyboard)
   - [KeyPad](#34-keypad)
7. [ROS2](#4-ros2)
8. [Peta Pin](#peta-pin)
9. [Catatan Teknis](#catatan-teknis)

---

## Struktur Repository

```text
.
├── Microcontroller/
│   ├── arduino/
│   │   ├── blink.ino
│   │   ├── push_button.ino
│   │   └── 5_lampu.ino
│   ├── esp32/
│   │   ├── blink.cpp
│   │   ├── joy_stick.cpp
│   │   ├── rgb.cpp
│   │   ├── rx_wifi.cpp
│   │   ├── tx_wifi.cpp
│   │   └── MAC_ADDRES.png
│   └── stm32/
│       ├── rx_stm32.cpp
│       └── tx_stm32.cpp
├── oop/
│   ├── class.cpp
│   ├── encapsulation.cpp
│   ├── inheretence.cpp
│   ├── inh_protected.cpp
│   ├── kontruktor.cpp
│   ├── polymorph.cpp
│   └── class/                 # binary hasil kompilasi (ELF)
├── RangkaBawah/
│   ├── AnalogStick/
│   │   ├── esp32_joystick.cpp
│   │   ├── esp32s3.cpp
│   │   └── stm32/
│   │       ├── platformio.ini
│   │       └── src/
│   │           ├── main.cpp
│   │           ├── inverseKinematik.h
│   │           ├── Moving.h
│   │           ├── Normalize.h
│   │           └── Variable.h
│   ├── Controller/ESP-32/
│   │   ├── rx_analog.cpp
│   │   └── tx_analog.cpp
│   ├── Keyboard/
│   │   ├── demux_motor.cpp
│   │   ├── motor_4.cpp
│   │   ├── moto_serong.cpp
│   │   └── pwm_motor.cpp
│   └── KeyPad/
│       ├── esp32_keypad.cpp
│       ├── esp32s3.cpp
│       └── stm32_wheel.cpp
└── ROS2/
    ├── 01 - Setup Workspace and Packages.md
    ├── 02 - Publisher and Subscriber.md
    └── 03 - Service and Client.md
```

> Folder `.pio/` di dalam `RangkaBawah/AnalogStick/stm32/` adalah hasil build PlatformIO (generated), bukan source code.

---

## Cara Menjalankan

### Arduino (`Microcontroller/arduino`)

1. Buka file `.ino` dengan Arduino IDE.
2. Pilih board Arduino yang sesuai (contoh: Arduino Uno/Nano).
3. Pilih port, lalu **Upload**.

### ESP32 (`Microcontroller/esp32`, `RangkaBawah/**/esp32*.cpp`)

1. Buka file `.cpp` sebagai sketch Arduino (rename/duplikasi menjadi folder sketch jika perlu).
2. Pilih board ESP32 yang sesuai (ESP32 Dev Module / ESP32-S3 Dev Module).
3. Library yang dibutuhkan:
   - `PS2X_lib` (Bill Porter) untuk joystick PS2.
   - `SerialTransfer` (PowerBroker2) untuk komunikasi UART terstruktur.
   - `esp_now` dan `WiFi` sudah termasuk dalam core ESP32.
4. Upload, lalu buka Serial Monitor pada **115200 baud**.

### STM32 Blackpill (`RangkaBawah/AnalogStick/stm32`)

Project menggunakan PlatformIO:

```bash
cd RangkaBawah/AnalogStick/stm32
pio run                 # build
pio run -t upload       # upload via DFU
pio device monitor      # serial monitor 115200
```

Konfigurasi ada di `platformio.ini`:

- Board: `blackpill_f411ce`
- Framework: Arduino
- Upload: DFU (`dfu-util`) ke `/dev/ttyACM0`
- Dependency: `powerbroker2/SerialTransfer@^3.1.5`
- USB CDC diaktifkan lewat `-DUSBCON -DUSBD_USE_CDC`

Untuk masuk mode DFU, tahan tombol **BOOT0** saat reset. Sesuaikan `upload_command` jika port serial berbeda.

### OOP (`oop`)

Kompilasi manual dengan `g++`:

```bash
cd oop
g++ class.cpp -o class
./class
```

> Beberapa file contoh masih memiliki kesalahan sintaks/logika. Lihat [Catatan Teknis](#catatan-teknis).

### ROS 2

Ikuti catatan berurutan di folder `ROS2/`:

1. `01 - Setup Workspace and Packages.md`
2. `02 - Publisher and Subscriber.md`
3. `03 - Service and Client.md`

Prasyarat: **ROS 2 Jazzy**, `colcon`, `rosdep`, dan `git`.

---

## Arsitektur Komunikasi RangkaBawah

RangkaBawah memiliki dua jalur kendali:

### A. Analog Stick (PS2)

```text
[PS2 Controller]
      │ (SPI-like: CLK=18, CMD=23, ATT=5, DAT=19)
      ▼
[ESP32 / ESP32-S3 pengirim]  ──ESP-NOW──▶  [ESP32-S3 penerima]
   esp32_joystick.cpp                        esp32s3.cpp
                                                   │ UART Serial1
                                                   │ RX=44, TX=43
                                                   ▼
                                            [STM32 Blackpill F411]
                                              main.cpp
                                                   │ PWM + pin mux
                                                   ▼
                                            [4 Motor DC + driver]
```

### B. Keypad (D-pad)

```text
[PS2 Controller]
      │
      ▼
[ESP32 pengirim]  ──ESP-NOW──▶  [ESP32-S3 penerima]  ──UART──▶  [STM32]
   esp32_keypad.cpp                esp32s3.cpp                 stm32_wheel.cpp
                                                                    │
                                                                    ▼
                                                              [4 Motor DC]
```

### MAC Address Peer ESP-NOW

| Lokasi | File | MAC receiver |
| --- | --- | --- |
| `Microcontroller/esp32` | `tx_wifi.cpp`, `rx_wifi.cpp` | `1C:DB:D4:D2:C0:94` |
| `RangkaBawah/Controller/ESP-32` | `tx_analog.cpp` | `68:EE:8F:4F:04:1C` |
| `RangkaBawah/AnalogStick` | `esp32_joystick.cpp` | `98:88:E0:03:F8:AC` |
| `RangkaBawah/KeyPad` | `esp32_keypad.cpp` | `98:88:E0:03:F8:AC` |

MAC address harus sesuai dengan perangkat penerima. MAC ESP32-S3 penerima dicetak oleh `esp32s3.cpp` pada Serial Monitor saat `setup()`.

### Format Data

Semua program rangka bawah mengirim struct yang sama:

```cpp
struct STRUCT {
  int LY, LX, rX, rY;              // nilai analog stick (0–255)
  bool arUp, arDw, arRt, arLt;     // tombol D-pad
};
```

Nilai tersebut dikirim lewat ESP-NOW, lalu diteruskan ke STM32 menggunakan **SerialTransfer** agar batas paket data jelas.

---

## 1. Microcontroller

### 1.1 Arduino

Folder: `Microcontroller/arduino`

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `blink.ino` | `setup()`, `loop()` | Menyalakan 3 LED (pin 7, 8, 13) bergantian: 2 detik ON, 0,5 detik OFF. |
| `push_button.ino` | `setup()`, `loop()` | Tombol di pin 12 (`INPUT_PULLUP`) menjadi toggle 3 LED (pin 7, 8, 13). |
| `5_lampu.ino` | `setup()`, `loop()`, `map()` | Potensiometer di `A0` mengatur 5 LED (pin 5, 6, 3, 2, 7) berdasarkan rentang nilai hasil `map()`. |

**Detail perilaku:**

- `blink.ino`
  - `int pin[3] = {7, 8, 13};`
  - Setiap LED menyala 2000 ms lalu mati 500 ms secara berurutan.
- `push_button.ino`
  - Saat tombol ditekan (`LOW`), nilai `last_state` dibalik.
  - LED menyala jika `last_state == LOW`.
  - Tidak ada debounce atau deteksi tepi (edge detection), sehingga selama tombol ditahan status dapat berubah berulang.
- `5_lampu.ino`
  - `analogRead(A0)` menghasilkan 0–1023, lalu di-`map` ke 0–255.
  - Rentang yang dipakai: 1–51, 52–102, 103–153, 154–204, dan 105–255.
  - LED yang aktif diberi `analogWrite` sebesar nilai hasil mapping; selain rentang tersebut semua LED dimatikan.

### 1.2 ESP32

Folder: `Microcontroller/esp32`

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `blink.cpp` | `setup()`, `loop()` | Blink LED di pin `PC13`: 5 detik ON, 1 detik OFF. |
| `joy_stick.cpp` | `setup()`, `loop()` | Membaca controller PS2 dan menampilkan nilai analog stick saat L1/R1 ditekan. |
| `rgb.cpp` | `setup()`, `loop()` | Menampilkan teks ke Serial dan mengatur LED RGB built-in (`neopixelWrite`): merah → hijau → biru. |
| `rx_wifi.cpp` | `onSent()`, `setup()`, `loop()` | Inisialisasi ESP-NOW dan mengirim karakter dari Serial ke MAC receiver. |
| `tx_wifi.cpp` | `onSent()`, `setup()`, `loop()` | Sama dengan `rx_wifi.cpp` (duplikat): berfungsi sebagai pengirim ESP-NOW. |
| `MAC_ADDRES.png` | — | Screenshot MAC address untuk keperluan konfigurasi peer ESP-NOW. |

**Detail:**

- `joy_stick.cpp`
  - Konfigurasi PS2X: `ps2x.config_gamepad(18, 23, 5, 19, false, false)`.
  - Urutan pin: `CLK=18`, `CMD=23`, `ATT=5`, `DAT=19`.
  - Percobaan koneksi maksimal 5 kali; jika gagal, program tetap berjalan untuk debugging.
  - Saat `L1` atau `R1` ditekan, mencetak `LX, LY, RY, RX`.
- `rx_wifi.cpp` / `tx_wifi.cpp`
  - Mode `WIFI_STA`, inisialisasi `esp_now`, daftarkan callback `onSent`.
  - Peer ditambahkan dengan `peer.channel = 0` dan `encrypt = false`.
  - `loop()` membaca `Serial.readString()`, mengambil karakter pertama, lalu mengirim struct `{ char cmd; }`.
  - Catatan: `rx_wifi.cpp` saat ini **identik** dengan `tx_wifi.cpp`; belum ada callback penerima di file tersebut.
- `blink.cpp`
  - Menggunakan nama pin `PC13` (penamaan khas STM32/Blackpill). Jika dijalankan di board ESP32, sesuaikan nomor pin-nya.

### 1.3 STM32

Folder: `Microcontroller/stm32`

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `tx_stm32.cpp` | `setup()`, `loop()` | Mengirim struct `{ char z; float y; }` lewat `Serial1` memakai SerialTransfer setiap 500 ms. |
| `rx_stm32.cpp` | `setup()`, `loop()` | Menerima struct dari `Serial1` dan mencetak isinya ke Serial Monitor. |

**Detail:**

- Keduanya memakai `Serial.begin(115200)` (USB serial) dan `Serial1.begin(115200)` (UART ke perangkat lain).
- `SerialTransfer myTransfer;` lalu `myTransfer.begin(Serial1);`.
- Pengiriman: `txObj(testStruct, sendSize)` → `sendData(sendSize)`.
- Penerimaan: `available()` → `rxObj(testStruct, recSize)`.
- Data contoh: `char z` dan `float y = 4.5`.

---

## 2. OOP

Folder: `oop` — contoh konsep C++ untuk pembelajaran.

| File | Konsep | Isi |
| --- | --- | --- |
| `class.cpp` | Class & object | Class `Ras` dengan atribut `nama`, `umur`, dan metode `getRas()`. Membuat objek `ras` lalu mengisi atributnya. |
| `encapsulation.cpp` | Encapsulation | Atribut `atribut` dan `mana_power` dibuat `private`, diakses lewat `setAtribut()`, `getAtribut()`, dan `getManaPower()`. |
| `inheretence.cpp` | Inheritance (public) | Class `Dwarf : public Ras` mewarisi `nama`, `umur`, dan `getRas()` dari class `Ras`. |
| `inh_protected.cpp` | Inheritance (protected) | Atribut `Ras` dibuat `protected`; class turunan `Dwarf` mengaksesnya lewat metode `getRas()`. |
| `kontruktor.cpp` | Constructor | Constructor default `Ras()` dan constructor berparameter `Ras(string m, int i)` untuk mengisi `nama` dan `umur`. |
| `polymorph.cpp` | Polymorphism (overriding) | Class `Manusia`, `Elf`, dan `Dwarf` menimpa metode `skill()` milik `Ras` dengan perilaku masing-masing. |

**Fungsi/metode penting:**

| File | Metode |
| --- | --- |
| `class.cpp` | `Ras::getRas()` |
| `encapsulation.cpp` | `Ras::getRas()`, `Ras::setAtribut(string)`, `Ras::getAtribut()`, `Ras::getManaPower()` |
| `inheretence.cpp` | `Ras::getRas()` (diwarisi `Dwarf`) |
| `inh_protected.cpp` | `Dwarf::getRas()` |
| `kontruktor.cpp` | `Ras::Ras()`, `Ras::Ras(string, int)`, `Ras::getRas()` |
| `polymorph.cpp` | `Ras::skill()`, `Manusia::skill()`, `Elf::skill()`, `Dwarf::skill()` |

**Output yang diharapkan:**

- `class.cpp` → `Manusia 18`
- `encapsulation.cpp` → `Elf 100` lalu `Angin 100.5`
- `inheretence.cpp` → `Dwarf 50`
- `inh_protected.cpp` → `Dwarf 50`
- `kontruktor.cpp` → `Manusia 18`, lalu `Elf 30`
- `polymorph.cpp` → empat baris teks skill dari `Ras`, `Manusia`, `Elf`, dan `Dwarf`

**Binary hasil kompilasi:**

File berikut adalah executable ELF x86-64, bukan source code:

```text
oop/class/encapsulation
oop/class/object
oop/inheretence
oop/inh_protected
oop/kontruktor
oop/polymorph
```

Binary tersebut bisa dijalankan langsung di Linux, tetapi sebaiknya tidak di-commit ulang.

---

## 3. RangkaBawah

Folder ini berisi program kendali robot 4 roda dengan dua model input: **analog stick PS2** dan **keypad/D-pad**. Motor dikendalikan melalui pin PWM dan pin selector/demux untuk arah putaran.

### 3.1 AnalogStick

Folder: `RangkaBawah/AnalogStick`

Alur: **PS2 → ESP32 pengirim → ESP-NOW → ESP32-S3 penerima → UART → STM32 → motor**.

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `esp32_joystick.cpp` | `onSent()`, `setup()`, `loop()` | Pengirim ESP-NOW. Membaca PS2 (LX, LY, RX, RY, D-pad) lalu mengirim struct ke receiver. |
| `esp32s3.cpp` | `onReceive()`, `setup()`, `loop()` | Penerima ESP-NOW. Menyimpan data masuk lalu meneruskannya ke STM32 lewat `Serial1` (RX 44, TX 43). |
| `stm32/src/main.cpp` | `setup()`, `loop()` | Menerima data, memetakan joystick, menghitung inverse kinematics, lalu menggerakkan 4 motor. |
| `stm32/src/inverseKinematik.h` | `inverseKinematik()` | Menghitung kecepatan roda berdasarkan `x`, `y`, rotasi, dan sudut roda. |
| `stm32/src/Moving.h` | `move()` | Mengatur arah (CW/CCW/stop) dan PWM tiap motor berdasarkan tanda nilai kecepatan. |
| `stm32/src/Normalize.h` | `deadzone()`, `mapJoystick()` | Normalisasi nilai joystick dan menghilangkan noise di sekitar titik tengah. |
| `stm32/src/Variable.h` | — | Definisi pin, konstanta `SPEED`, struct data, dan `extern` objek global. |
| `stm32/platformio.ini` | — | Konfigurasi build/upload PlatformIO untuk Blackpill F411CE. |

**Detail `esp32_joystick.cpp`:**

- Pin PS2: `CLK=18`, `CMD=23`, `ATT=5`, `DAT=19`.
- Receiver MAC: `98:88:E0:03:F8:AC`.
- Data diambil hanya saat `L1` atau `R1` ditekan.
- `esp_now_send(...)` saat ini **dikomentari**, jadi program hanya menampilkan data ke Serial (mode debug).
- Data yang disiapkan: `LX, LY, rX, rY`, `arUp, arDw, arRt, arLt`.

**Detail `esp32s3.cpp`:**

- `Serial1.begin(115200, SERIAL_8N1, 44, 43)` → RX = 44, TX = 43.
- Mencetak MAC address sendiri di `setup()`.
- Callback `onReceive()` menyalin data masuk dengan `memcpy`.
- `loop()` mengirim `receivedData` ke STM32 memakai SerialTransfer setiap 50 ms.

**Detail `main.cpp` (STM32):**

1. `setup()` menginisialisasi Serial, Serial1, pin PWM, pin mux, lalu:
   - `analogWriteFrequency(20000)` → PWM 20 kHz.
   - `analogWriteResolution(12)` → resolusi PWM 0–4095.
2. `loop()` menunggu paket SerialTransfer, lalu:
   - `VxL = deadzone(mapJoystick(LX))`
   - `VyL = deadzone(-mapJoystick(LY))`
   - `R   = deadzone(mapJoystick(rX))`
3. Jika semua nol → `move(0, 0, 0, 0)` (berhenti).
4. Jika ada input:
   - `theta = atan2(VyL, VxL)`
   - `Vx = SPEED * cos(theta)`, `Vy = SPEED * sin(theta)`
   - Hitung kecepatan 4 roda dengan sudut:
     - Roda 1: `46.5515556°`
     - Roda 2: `135.77075°`
     - Roda 3: `226.83074°`
     - Roda 4: `316.50383°`
   - Panggil `move(W1, W2, W3, W4)`.

**Rumus `inverseKinematik.h`:**

```cpp
float inverseKinematik(int x, int y, int r, int sudut)
{
    return ((-x * sin(sudut * DEG_TO_RAD)) + (y * cos(sudut * DEG_TO_RAD)) + (r * SPEED));
}
```

**Mapping roda dan pin:**

| Roda | PWM | Pin mux/arah | Sudut IK |
| --- | --- | --- | --- |
| 1 | `PB9` | `PA5` | 46.5515556° |
| 2 | `PB8` | `PA2` | 135.77075° |
| 3 | `PB7` | `PA3` | 226.83074° |
| 4 | `PB6` | `PA4` | 316.50383° |

**Parameter `Normalize.h`:**

- `deadzone(val, threshold = 10)` → nilai dengan magnitudo < 10 dianggap 0.
- `mapJoystick(raw, center = 132)` → memetakan 0–255 menjadi -127…127, dengan 132 sebagai titik tengah.

**Perilaku `move()`:**

- Nilai `w > 0` → motor **CW**, mux `HIGH`.
- Nilai `w < 0` → motor **CCW**, mux `LOW`.
- Nilai `w == 0` → motor berhenti (PWM 0).
- PWM yang ditulis selalu `abs(w)` agar nilai negatif menjadi besaran duty cycle.

**Konfigurasi PlatformIO**

```ini
[env:blackpill_f411ce]
platform = ststm32
board = blackpill_f411ce
framework = arduino
lib_deps = powerbroker2/SerialTransfer@^3.1.5
monitor_speed = 115200
build_flags =
    -DUSBCON
    -DUSBD_USE_CDC
```

### 3.2 Controller ESP-32

Folder: `RangkaBawah/Controller/ESP-32`

Program pengirim/penerima ESP-NOW berbasis PS2.

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `tx_analog.cpp` | `onSent()`, `setup()`, `loop()` | Membaca PS2 lalu mengirim data ke receiver `68:EE:8F:4F:04:1C`. Pengiriman hanya saat `L1`/`R1` ditekan. |
| `rx_analog.cpp` | `onReceive()`, `setup()`, `loop()` | Menerima struct ESP-NOW dan mencetak `LX, LY, rX, rY, arUp, arDw, arRt, arLt` ke Serial. |

**Detail:**

- `tx_analog.cpp` memakai pin PS2 yang sama: `18, 23, 5, 19`.
- Data yang dikirim: 4 nilai analog + 4 tombol D-pad.
- `rx_analog.cpp` hanya mencetak data; `loop()` kosong karena pemrosesan terjadi di callback.

### 3.3 Keyboard

Folder: `RangkaBawah/Keyboard`

Kendali motor melalui perintah teks dari Serial Monitor/terminal (115200 baud).

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `pwm_motor.cpp` | `setup()`, `loop()` | Kontrol 2 motor (`PB8` kiri, `PB9` kanan) dengan PWM. |
| `demux_motor.cpp` | `setup()`, `loop()` | Kontrol 1 motor (`PB9`) + pin selector arah (`PA2`). |
| `motor_4.cpp` | `setMotors()`, `setup()`, `loop()` | Kontrol 4 motor dengan pin PWM `PB6–PB9` dan mux `PA2–PA5`. |
| `moto_serong.cpp` | `setup()`, `loop()` | Kontrol 4 motor termasuk gerakan diagonal (Q/E/Z/C). |

**Perintah Serial:**

| Perintah | `pwm_motor.cpp` | `motor_4.cpp` | `moto_serong.cpp` |
| --- | --- | --- | --- |
| `W` | Stop | Maju | Maju |
| `S` | Kanan | Mundur | Mundur |
| `A` | Kiri | Kiri | Kiri |
| `D` | — | Kanan | Kanan |
| `X` | — | Berhenti | Berhenti |
| `Q` | — | — | Kiri atas |
| `E` | — | — | Kanan atas |
| `Z` | — | — | Kiri bawah |
| `C` | — | — | Kanan bawah |

**Detail:**

- `pwm_motor.cpp`
  - `A`: motor kanan dimatikan, tunggu 1000 ms, motor kiri PWM 200.
  - `S`: motor kiri dimatikan, tunggu 1000 ms, motor kanan PWM 200.
  - `W`: kedua motor PWM 0.
  - `delay(1000)` membuat `loop()` blocking saat pergantian arah.
- `demux_motor.cpp`
  - `A` → `_sel = HIGH`, status "kiri", `running = true`.
  - `S` → `_sel = LOW`, status "kanan", `running = true`.
  - `W` → `running = false`, PWM 0, status "stop".
  - Selama `running`, `loop()` terus menulis `analogWrite(pin_r, 200)`.
- `motor_4.cpp`
  - `setMotors(m1, m2, m3, m4, speed)` menulis 4 pin mux dan 4 pin PWM sekaligus.
  - Kecepatan tetap `SPEED = 200`.
  - Kombinasi arah:
    - Maju: `HIGH, LOW, LOW, HIGH`
    - Mundur: `LOW, HIGH, HIGH, LOW`
    - Kanan: `LOW, LOW, HIGH, HIGH`
    - Kiri: `HIGH, HIGH, LOW, LOW`
- `moto_serong.cpp`
  - Memakai pola mux yang sama untuk maju/mundur/kiri/kanan.
  - Gerakan diagonal dilakukan dengan mematikan dua motor dan menjalankan dua motor lainnya.

### 3.4 KeyPad

Folder: `RangkaBawah/KeyPad`

Alur: **PS2 D-pad → ESP32 → ESP-NOW → ESP32-S3 → UART → STM32 → motor**.

| File | Fungsi | Ringkasan |
| --- | --- | --- |
| `esp32_keypad.cpp` | `onSent()`, `setup()`, `loop()` | Pengirim ESP-NOW; membaca PS2 dan menyiapkan data stick + D-pad. |
| `esp32s3.cpp` | `onReceive()`, `setup()`, `loop()` | Penerima ESP-NOW dan jembatan UART ke STM32 (sama seperti versi AnalogStick). |
| `stm32_wheel.cpp` | `setup()`, `loop()` | Menerima data dan menggerakkan 4 motor berdasarkan tombol D-pad (`arUp`, `arDw`, `arRt`, `arLt`). |

**Detail `stm32_wheel.cpp`:**

- Pin PWM: `PB6`, `PB7`, `PB8`, `PB9`.
- Pin mux: `PA2`, `PA3`, `PA4`, `PA5`.
- `SPEED = 2048`, PWM 20 kHz, resolusi 12-bit.
- Logika gerakan:
  - `arUp` → maju
  - `arDw` → mundur
  - `arRt` → kanan
  - `arLt` → kiri
  - Selain itu → berhenti
- Memanggil `setMotors(...)`; fungsi tersebut tidak didefinisikan di file ini (kemungkinan dipakai bersama dari `Keyboard/motor_4.cpp`).

---

## 4. ROS2

Folder: `ROS2` — catatan belajar ROS 2 Jazzy dalam bahasa Indonesia.

| File | Topik | Ringkasan |
| --- | --- | --- |
| `01 - Setup Workspace and Packages.md` | Workspace & packages | `source` environment, membuat `~/ros2_ws/src`, clone `ros_tutorials`, `rosdep install`, `colcon build`, menjalankan `turtlesim`, membuat paket `jajal` dan node `tes_lur`. |
| `02 - Publisher and Subscriber.md` | Topic | Membuat `talker.py` (publisher) dan `listener.py` (subscriber) pada topik `/obrolan` dengan `std_msgs/String`, mendaftarkan entry point di `setup.py`, lalu build dan run. |
| `03 - Service and Client.md` | Service | Membuat `server.py` dan `client.py` untuk service `add_two_ints` bertipe `example_interfaces/srv/AddTwoInts`, termasuk cara memanggil service lewat CLI. |

**Prasyarat:**

- ROS 2 Jazzy terpasang di `/opt/ros/jazzy`
- `colcon`, `rosdep`, dan `git`
- Setiap terminal baru harus menjalankan:

```bash
source /opt/ros/jazzy/setup.bash
```

**Catatan format:** dokumen memakai frontmatter YAML dan wikilink Obsidian (`[[...]]`). Wikilink tersebut mungkin tidak dapat diklik langsung saat dilihat di GitHub.

---

## Peta Pin

### STM32 Blackpill F411CE

| Fungsi | Pin | Digunakan di |
| --- | --- | --- |
| PWM motor 1 | `PB9` | `AnalogStick/stm32/src/Variable.h` |
| PWM motor 2 | `PB8` | `AnalogStick/stm32/src/Variable.h` |
| PWM motor 3 | `PB7` | `AnalogStick/stm32/src/Variable.h` |
| PWM motor 4 | `PB6` | `AnalogStick/stm32/src/Variable.h` |
| Mux/arah motor 1 | `PA5` | `AnalogStick/stm32/src/Variable.h` |
| Mux/arah motor 2 | `PA2` | `AnalogStick/stm32/src/Variable.h` |
| Mux/arah motor 3 | `PA3` | `AnalogStick/stm32/src/Variable.h` |
| Mux/arah motor 4 | `PA4` | `AnalogStick/stm32/src/Variable.h` |
| LED onboard | `PC13` | `Microcontroller/esp32/blink.cpp`, `Moving.h` |
| UART ke ESP32-S3 | `PA9` (TX), `PA10` (RX) | `Serial1` (default USART1) |

> Urutan PWM di folder `Keyboard` berbeda: `pwm_1 = PB6`, `pwm_2 = PB7`, `pwm_3 = PB8`, `pwm_4 = PB9`.

### ESP32 / ESP32-S3

| Fungsi | Pin | Digunakan di |
| --- | --- | --- |
| PS2 CLK | `18` | `joy_stick.cpp`, `esp32_joystick.cpp`, `esp32_keypad.cpp`, `tx_analog.cpp` |
| PS2 CMD | `23` | file PS2 di atas |
| PS2 ATT/SEL | `5` | file PS2 di atas |
| PS2 DAT | `19` | file PS2 di atas |
| UART TX ke STM32 | `43` | `esp32s3.cpp` (penerima) |
| UART RX dari STM32 | `44` | `esp32s3.cpp` (penerima) |
| LED RGB built-in | `RGB_BUILTIN` | `rgb.cpp` |

### Arduino

| Fungsi | Pin | Digunakan di |
| --- | --- | --- |
| LED | `7`, `8`, `13` | `blink.ino`, `push_button.ino` |
| LED tambahan | `5`, `6`, `3`, `2` | `5_lampu.ino` |
| Tombol | `12` | `push_button.ino` |
| Potensiometer | `A0` | `5_lampu.ino` |

---

## Catatan Teknis

Bagian ini merangkum hal-hal yang perlu diperhatikan saat membaca atau menjalankan program. Tidak ada file source yang diubah oleh dokumentasi ini.

### Batas array dan tipe data

- `Microcontroller/arduino/blink.ino`: array `pin[3]` tetapi loop memakai `i <= 3`, sehingga indeks ke-3 berada di luar array.
- `Microcontroller/arduino/5_lampu.ino`: array `led[6]` hanya diisi 5 nilai, dan loop `i <= 5` mengakses indeks ke-5 yang tidak diinisialisasi.
- `5_lampu.ino`: rentang terakhir tertulis `105–255`; kemungkinan maksudnya `205–255` (karena 103–204 sudah ditangani cabang sebelumnya).
- `5_lampu.ino`: fungsi `int map()` dideklarasikan tanpa isi dan tanpa `return`, serta namanya bentrok dengan `map()` bawaan Arduino.

### String dan constructor

- `oop/class.cpp`: `ras.nama = 'Manusia';` memakai character literal multi-karakter, bukan string literal (`"Manusia"`).
- `Microcontroller/stm32/tx_stm32.cpp`: `testStruct.z = 'hello bung';` juga character literal multi-karakter; nilainya bergantung implementasi compiler.
- `oop/kontruktor.cpp`: `Ras ras;` dan `Ras ras("Manusia", 18);` dideklarasikan dengan nama yang sama dalam satu scope, sehingga menimbulkan redeclaration error.

### Duplikasi dan kelengkapan program

- `Microcontroller/esp32/rx_wifi.cpp` identik dengan `tx_wifi.cpp`; keduanya berperan sebagai pengirim, belum ada callback penerima.
- `RangkaBawah/AnalogStick/esp32_joystick.cpp` dan `RangkaBawah/KeyPad/esp32_keypad.cpp`: pemanggilan `esp_now_send(...)` masih dikomentari, sehingga data hanya dicetak ke Serial.
- `RangkaBawah/KeyPad/stm32_wheel.cpp`: memanggil `setMotors()` yang tidak didefinisikan di file tersebut, dan memiliki kelebihan koma pada argumen `Serial.printf`.
- `RangkaBawah/Keyboard/moto_serong.cpp`: pin mux (`PA2–PA5`) ditulis dengan `analogWrite`, padahal seharusnya `digitalWrite`.
- `RangkaBawah/AnalogStick/stm32/src/main.cpp`: `Serial.println(receivedData.LX)` dipanggil sebelum `rxObj()`, sehingga nilai yang tercetak masih data lama.
- `inverseKinematik()` memiliki parameter `int`, sedangkan `Rnorm` dan hasil perhitungan berupa `float`; konversi implisit dapat memotong nilai desimal.
- `Moving.h`: pin `PC13` hanya ditulis pada cabang motor 1 (CCW/stop), bukan sebagai indikator umum.

### Binary hasil kompilasi

- File `oop/class/encapsulation`, `oop/class/object`, `oop/inheretence`, `oop/inh_protected`, `oop/kontruktor`, dan `oop/polymorph` adalah executable ELF x86-64. Sebaiknya binary tidak disimpan di repositori; gunakan `.gitignore`.
- Folder `RangkaBawah/AnalogStick/stm32/.pio/` juga merupakan output build dan dapat dibuat ulang dengan `pio run`.

### Lisensi

Repository ini belum memiliki file lisensi. Tambahkan `LICENSE` jika kode akan dibagikan atau digunakan ulang.
