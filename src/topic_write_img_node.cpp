#include <ros/ros.h>
#include <mmap_py2cpp/shared_memory_pool.h>
#include <vector>
#include "std_msgs/String.h"
#include "sensor_msgs/Image.h"
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
int main(int argc, char **argv)
{
    ros::init(argc, argv, "img_writer");
    ros::NodeHandle n;
    ros::Rate loop_rate(1);
    ros::Publisher pub = n.advertise<sensor_msgs::Image>("image", 10);
    const char *file_name = "/root/catkin_ws/src/mmap_py2cpp/img/DSC_0568.JPG";

    sensor_msgs::Image img_msg_;

    try
    {
        std_msgs::Header header;
        header.stamp = ros::Time::now();
        cv::Mat image = cv::imread(file_name, cv::IMREAD_COLOR);
        img_msg_ = *cv_bridge::CvImage(header, "bgr8", image).toImageMsg();

        if (image.data == NULL)
        {
            ROS_ERROR("Image read error! The reasons for this may include missing files, incorrect permissions, unsupported or invalid formatting, etc.");
        }
    }
    catch (cv::Exception &e)
    {
        ROS_ERROR("OpenCV exception: %s", e.what());
    }
    ROS_INFO("try to pub");
    while (ros::ok())
    {
        pub.publish(img_msg_);
        loop_rate.sleep();
    }

    return 0;
}