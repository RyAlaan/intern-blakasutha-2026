---
module: Workspace & Packages
framework: ROS 2 Jazzy
language: bash
updated: 2026-10-29
tags:
  - ROS2
  - ROS2-Jazzy
  - workspace
---

# Setup Workspace & Packages

> **Tujuan**
> Menyiapkan workspace ROS 2 Jazzy, memverifikasi instalasi dengan `turtlesim`, lalu membuat paket Python sendiri.

> **Prasyarat**
> - ROS 2 Jazzy terpasang di `/opt/ros/jazzy`
> - `colcon`, `rosdep`, dan `git` tersedia

---

## 1. Muat environment ROS 2

ROS 2 mendukung beberapa distro sekaligus. `source` menentukan distro mana yang aktif di terminal ini.

```bash
source /opt/ros/jazzy/setup.bash
```

Cek distro yang sedang aktif:

```bash
echo $ROS_DISTRO
# jazzy
```

> [!note]
> `setup.bash` harus di-`source` di **setiap terminal baru**. Tanpa ini, perintah `ros2` dan library ROS tidak akan ditemukan.

## 2. Buat folder workspace

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
```

## 3. Clone paket uji coba

```bash
git clone https://github.com/ros/ros_tutorials.git -b jazzy
```

## 4. Install dependencies

Kembali ke root workspace, lalu install dependency dari semua paket di `src`:

```bash
cd ~/ros2_ws
rosdep install -i --from-path src --rosdistro jazzy -y
```

## 5. Build workspace

```bash
colcon build
```

Output jika berhasil:

```text
Starting >>> turtlesim
Finished <<< turtlesim [5.49s]

Summary: 1 package finished [5.58s]
```

## 6. Jalankan hasil build

```bash
ros2 run turtlesim turtlesim_node
```

`turtlesim` adalah nama paket, `turtlesim_node` adalah nama node.

## 7. Buat paket sendiri

Masuk ke `src`, lalu buat paket (contoh nama paket: `jajal`):

```bash
cd ~/ros2_ws/src
ros2 pkg create --build-type ament_python --license Apache-2.0 jajal
```

Pilihan `--build-type` menentukan bahasa paket:

| Build type | Bahasa |
| --- | --- |
| `ament_python` | Python |
| `ament_cmake` | C++ |

## 8. Buat node pertama di dalam paket

```bash
ros2 pkg create --build-type ament_python --license Apache-2.0 --node-name tes_lur jajal
```

`tes_lur` adalah nama node, `jajal` adalah nama paket yang sudah dibuat.

## 9. Build dan jalankan paket

```bash
cd ~/ros2_ws
colcon build --packages-select jajal
source install/setup.bash
ros2 run jajal tes_lur
```

---

## Selanjutnya

- [[02 - Publisher and Subscriber]]
- [[03 - Service and Client]]
