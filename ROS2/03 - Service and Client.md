---
module: Services
framework: ROS 2 Jazzy
language: python
updated: 2026-10-29
tags:
  - ROS2
  - ROS2-Jazzy
  - services
  - python
---

# Service & Client

> **Tujuan**
> Membuat server dan client Python dengan service `add_two_ints` (tipe `example_interfaces/srv/AddTwoInts`) yang menjumlahkan dua bilangan.

> **Prasyarat**
> - ROS 2 Jazzy sudah di-`source`
> - Paket `example_interfaces` tersedia (bawaan instalasi ROS 2)

---

## 1. Buat workspace

```bash
mkdir -p ~/ros2_sc/src
cd ~/ros2_sc/src
```

## 2. Buat paket

```bash
ros2 pkg create --build-type ament_python jajal
```

## 3. Buat file node

```bash
cd ~/ros2_sc/src/jajal/jajal
touch server.py client.py
```

## 4. Tulis server (`server.py`)

```python
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class MyServiceServer(Node):
    def __init__(self):
        super().__init__('my_service_server')
        self.srv = self.create_service(
            AddTwoInts,          # tipe service
            'add_two_ints',      # nama service
            self.handle_request  # callback
        )
        self.get_logger().info('Service server siap!')

    def handle_request(self, request, response):
        response.sum = request.a + request.b
        self.get_logger().info(f'Request: {request.a} + {request.b} = {response.sum}')
        return response


def main(args=None):
    rclpy.init(args=args)
    node = MyServiceServer()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```

## 5. Tulis client (`client.py`)

```python
import rclpy
from rclpy.node import Node
from example_interfaces.srv import AddTwoInts


class MyServiceClient(Node):
    def __init__(self):
        super().__init__('my_service_client')
        self.client = self.create_client(AddTwoInts, 'add_two_ints')

        # Tunggu sampai server siap
        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('Nunggu service...')

    def send_request(self, a, b):
        request = AddTwoInts.Request()
        request.a = a
        request.b = b

        future = self.client.call_async(request)
        rclpy.spin_until_future_complete(self, future)
        return future.result()


def main(args=None):
    rclpy.init(args=args)
    client = MyServiceClient()
    result = client.send_request(5, 3)
    client.get_logger().info(f'Hasil: {result.sum}')
    client.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
```

## 6. Daftarkan entry point di `setup.py`

```bash
cd ~/ros2_sc/src/jajal
nano setup.py
```

Tambahkan atau ubah bagian `entry_points` menjadi:

```python
entry_points={
    'console_scripts': [
        'server = jajal.server:main',
        'client = jajal.client:main',
    ],
},
```

## 7. Build dan jalankan

```bash
cd ~/ros2_sc
colcon build --packages-select jajal
source install/setup.bash
```

Terminal 1 — server:

```bash
ros2 run jajal server
```

Terminal 2 — client:

```bash
ros2 run jajal client
```

## 8. Cek hasil

Client akan mencetak `Hasil: 8`, dan server mencatat request yang masuk.

Uji manual lewat CLI (server harus tetap berjalan):

```bash
ros2 service list                       # daftar service aktif
ros2 service type /add_two_ints         # tipe service
ros2 service call /add_two_ints example_interfaces/srv/AddTwoInts "{a: 5, b: 3}"
```

---

## Selanjutnya

- [[01 - Setup Workspace and Packages]]
- [[02 - Publisher and Subscriber]]
