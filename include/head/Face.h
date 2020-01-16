#pragma once

#include <ros/subscriber.h>
#include <std_msgs/Int32.h>
#include "Screen.h"
#include "FaceImage.h"

class Face {

public:
    Face(ros::NodeHandle& nh, std::string face_dir);

    void spin();

private:
    Screen::Ptr screen = Screen::create();
    FaceImage::Ptr face;

    ros::Subscriber eyeball_vertical_subscriber;
    int last_eyeball_value;
    void on_vertical_value(const std_msgs::Int32::ConstPtr& msg);

    int target_eyeball_value;

    void move_to_target_value(int eyeball_value);

};