#include <ros/ros.h>
#include <mmap_py2cpp/shared_memory_pool.h>
#include <vector>
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>

int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_writer");
    ros::NodeHandle n;
    const char *file_name = "/root/catkin_ws/src/mmap_py2cpp/img/DSC_0568.JPG";
    cv::Mat image;
    try
    {
        image = cv::imread(file_name);
        if (image.data == NULL)
        {
            ROS_ERROR("Image read error! The reasons for this may include missing files, incorrect permissions, unsupported or invalid formatting, etc.");
            ROS_ERROR("Image file: %s", file_name);
        }
    }
    catch (const std::exception &e)
    {
        ROS_ERROR("OpenCV exception: %s", e.what());
    }

    const int size = image.total() * image.elemSize();
    printf("total : %d elemsize : %d size : %d", image.total(), image.elemSize(), size);
    std::vector<uint8_t> buf;
    buf.resize(size);
    SharedMemoryPool memory("/root/catkin_ws/src/mmap_py2cpp/share/shared.pool", size, 2);
    std::memcpy(buf.data(), image.data, buf.size());
    memory.flush();
    if (memory.try_write(buf.data(), buf.size()))
    {
        ROS_INFO("wrote %d bytes", buf.size());
    }
    return 0;
}