---
module: Topics
framework: ROS 2 Jazzy
language: python
updated: 2026-10-29
tags:
  - ROS2
  - ROS2-Jazzy
  - topics
  - python
---

# Publisher & Subscriber

> **Tujuan**
> Membuat dua node Python yang berkomunikasi lewat satu topik (`/obrolan`): `talker` sebagai publisher dan `listener` sebagai subscriber.

> **Prasyarat**
> - Workspace `~/ros2_ws` dan paket `jajal` sudah ada — lihat [[01 - Setup Workspace and Packages]]

---

## 1. Buat file node

```bash
cd ~/ros2_ws/src/jajal/jajal
touch talker.py listener.py
```

## 2. Tulis node subscriber (`listener.py`)

```python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class Krungu(Node):
    def __init__(self):
        super().__init__('krungu')
        # Subscribe ke topik /obrolan dengan tipe data String
        self.sub = self.create_subscription(String, '/obrolan', self.callback, 10)

    def callback(self, msg):
        self.get_logger().info(f'Krungu: {msg.data}')


def main(args=None):
    rclpy.init(args=args)
    node = Krungu()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```

## 3. Tulis node publisher (`talker.py`)

```python
import rclpy
from rclpy.node import Node
from std_msgs.msg import String


class Ngomong(Node):
    def __init__(self):
        super().__init__('ngomong')
        self.pub = self.create_publisher(String, '/obrolan', 10)
        self.timer = self.create_timer(1.0, self.callback)
        self.count = 0

    def callback(self):
        msg = String()
        msg.data = f'Halo! pesan ke-{self.count}'
        self.pub.publish(msg)
        self.get_logger().info(f'Ngirim: {msg.data}')
        self.count += 1


def main(args=None):
    rclpy.init(args=args)
    node = Ngomong()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```

## 4. Daftarkan entry point di `setup.py`

```bash
cd ~/ros2_ws/src/jajal
nano setup.py
```

Tambahkan atau ubah bagian `entry_points` menjadi:

```python
entry_points={
    'console_scripts': [
        'talker = jajal.talker:main',
        'listener = jajal.listener:main',
    ],
},
```

## 5. Build paket

```bash
cd ~/ros2_ws
colcon build --packages-select jajal
source install/setup.bash
```

## 6. Jalankan node

Terminal 1 — publisher:

```bash
ros2 run jajal talker
```

Terminal 2 — subscriber:

```bash
ros2 run jajal listener
```

## 7. Cek hasil

Subscriber akan menampilkan pesan setiap detik:

```text
[INFO] [krungu]: Krungu: Halo! pesan ke-0
[INFO] [krungu]: Krungu: Halo! pesan ke-1
```

Perintah CLI untuk inspeksi topik:

```bash
ros2 topic list          # daftar topik aktif
ros2 topic echo /obrolan # lihat isi topik mentah
ros2 topic info /obrolan # tipe data dan jumlah publisher/subscriber
```

---

## Selanjutnya

- [[01 - Setup Workspace and Packages]]
- [[03 - Service and Client]]
