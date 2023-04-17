#!/usr/bin/env python3
import rospy
from sensor_msgs.msg import Image
from impl.shared_memory_pool import *
import cv2
import numpy as np
import ros_numpy


def callback(msg: Image):
    img_rgb = ros_numpy.numpify(msg)
    # OpenCV形式のチャンネルに変換
    img_rgb = cv2.cvtColor(img_rgb, cv2.COLOR_RGB2BGR)
    cv2.imwrite(
        "/root/catkin_ws/src/mmap_py2cpp/img/receive_by_topic.jpg", img_rgb)
    # 最初の1回のみ読む
    print("time[s] = ", (rospy.Time.now() - msg.header.stamp).to_sec())


def listener():
    rospy.init_node('img_reader', anonymous=True)
    rospy.Subscriber("image", Image, callback=callback)
    w = 5504
    h = 3096
    BUF_CAPACITY = w * h * 3
    rospy.spin()


if __name__ == '__main__':
    listener()
