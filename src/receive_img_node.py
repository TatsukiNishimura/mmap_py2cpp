#!/usr/bin/env python3
import rospy
from std_msgs.msg import Header
from impl.shared_memory_pool import *
import cv2
import numpy as np
# path = os.path.join(os.path.dirname(__file__), "shared.pool")
path = "/root/catkin_ws/src/mmap_py2cpp/share/shared.pool"


def listener():

    rospy.init_node('img_reader', anonymous=True)
    pub = rospy.Publisher("header", Header, queue_size=10)
    w = 5504
    h = 3096
    BUF_CAPACITY = w * h * 3
    print(BUF_CAPACITY)
    with SharedMemoryPool(path, BUF_CAPACITY, 2) as memory:
        # memory.flush()
        while not rospy.is_shutdown():
            ret, bin = memory.try_read()
            if ret:
                image = np.frombuffer(bin, dtype=np.uint8).reshape(h, w, 3)
                print(type(image))
                cv2.imwrite(
                    "/root/catkin_ws/src/mmap_py2cpp/img/receive.jpg", image)
                # rospy.loginfo("now: %f", rospy.get_time())
                break
    header: Header = Header()
    header.stamp = rospy.Time.now()
    pub.publish(header)


if __name__ == '__main__':
    listener()
