# Publisher
Publisher adalah program yang mengeluarkan/memancarkan suatu data ke topik, yang nantinya dikirimkan ke subscriber. Bagaimana cara membuatnya?

1. Buka terminal Ubuntu, cd ke workspace/src yang telah dibuat sebelumnya, lalu buka vs code
   ```
   cd ~/ros2_workspace_test/src/
   code .
   ```

2. Dalam folder source, buatlah folder yang namanya sama dengan package yang telah dibuat sebelumnya. Lalu dalam folder yang baru, buatlah 2 file python: ![[Pasted image 20261102121656.png]]
   Nama file yang kedua tidak perlu sama, bebas saja.

3. File python yang pertama dikosongi saja, hanya ada agar sistem bisa mengetahui kalau folder tersebut diisi dengan program python. Untuk file python yang kedua:
```python
#! /usr/bin/env python3
import rclpy #import ROS 2 client library for python
from rclpy.node import Node #import node class for creating nodes
from std_msgs.msg import String #import string message type for ROS 2

class MinimalPyPublisher(Node):
    def __init__(self):
        #initialize the node with a name
        super().__init__('minimal_py_publisher')
        #create a publisher on the topic with a queue size of 10 messages
        self.publisher_1 = self.create_publisher(String, '/py_example_topic', 10)
        #create a timer with a period of 0.5 second to trigger the publish of message
        timer_period = 0.5
        self.timer = self.create_timer(timer_period, self.timer_callback)
        #initialize a counter variable for message content
        self.i = 0
    def timer_callback(self):
        #create string message object
        msg = String()
        #set the message data with a counter
        msg.data = 'Hello World: %d' % self.i
        #publish the message you created above to a topic
        self.publisher_1.publish(msg)
        #log a message indicating the message has been published
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i = self.i + 1

def main (args=None):
    rclpy.init(args=args)
    #create instance of the Minimal Publisher node
    minimal_py_publisher = MinimalPyPublisher()
    rclpy.spin(minimal_py_publisher)
    #destroy the node explicitly
    minimal_py_publisher.destroy_node()
    #shutdown ROS 2 communication
    rclpy.shutdown()

if __name__== '__main__':
    main()
```

4. Setelah itu, tweak 'package.xml' dan 'CMakeLists.txt' agar library dan package yang dibutuhkan bisa ditemukan dan dijalankan oleh sistem (mengikuti arahan dari king addison, beta belum paham apa-apa kalau bagian ini). https://www.youtube.com/watch?v=jsVEhmXSTgc&list=PLNWNEEf8BvG64FVZT4IdieI1PuYnHkUrt

5. Publisher berhasil dibuat, sekarang kita bisa melakukan beberapa testing di terminal Ubuntu:
   
   `cd ~/ros2_workspace_test/ && colcon build && source ~/.bashrc`
   
   Untuk melakukan build terhadap package yang kita punya, lalu:
   
   `ros2 run ros2_package_example py_minimal_publisher.py`
   
   Setelah menjalankan command tersebut, publisher akan dapat dijalankan dan kita bisa melihat string 'Hello World: ...' yang di print secara berkala setiap 0.5 detik.

> **Command-command untuk melihat berbagai macam informasi dari topic**
> Ada banyak macam informasi yang bisa kita cari dari topic, contoh-contohnya ada di https://docs.ros.org/en/jazzy/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Topics/Understanding-ROS2-Topics.html 


# Subscriber
Subscriber adalah program yang menerima suatu data dari publisher berdasarkan topik tertentu. Bagaimana cara membuatnya?

1. Buka terminal Ubuntu, cd ke workspace/src yang telah dibuat sebelumnya, lalu buka vs code
   ```
   cd ~/ros2_workspace_test/src/
   code .
   ```

2. Dalam folder source, folder yang tadi dibuat saat membuat publisher, tambahkan file python: ![[Pasted image 20261102161807.png]]
Nama filenya tidak perlu sama, bebas saja.

3. Isi file pythonnya:
```python
#! /usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPySubscriber(Node):
    def __init__(self):
        super().__init__('minimal_py_subscriber')
        self.subscriber_1 = self.create_subscription(String, 'py_example_topic', self.listener_callback, 10)
    def listener_callback(self, msg):
        self.get_logger().info(f'I heard: "{msg.data}"')

def main(args=None):
    rclpy.init(args=args)
    minimal_py_subscriber = MinimalPySubscriber()
    rclpy.spin(minimal_py_subscriber)
    minimal_py_subscriber.destroy_node
    rclpy.shutdown()

if __name__ == '__main__':
    main()
```

4. Setelah itu pada bagian ini di file 'CMakeLists.txt', tambahkan:
   `ros2_package_example/py_minimal_subscriber.py`
   ![[Pasted image 20261102162639.png]]
   
5. Subscriber berhasil dibuat, untuk menjalankannya, kita harus running publisher terlebih dahulu, baru subscriber:
```
cd ~/ros2_workspace_test/ && colcon build && source ~/.bashrc

ros2 run ros2_package_example py_minimal_publisher.py

ros2 run ros2_package_example py_minimal_subscriber.py
```
Pastikan untuk publisher dan subscriber dijalankan di dua terminal yang berbeda dan jangan lupa cd ke workspace.


