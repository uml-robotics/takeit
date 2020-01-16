#pragma once

#include <ros/publisher.h>
#include <std_msgs/Bool.h>

class HeadHandCoordinationEnable {

public:
    HeadHandCoordinationEnable();

    // rostopic pub /zhao/head_hand_coordination/enable std_msgs/Bool "true" -1
    void enable();

    // rostopic pub /zhao/head_hand_coordination/enable std_msgs/Bool "false" -1
    void disable();

    void get_ready();

private:
    ros::Publisher publisher;
    std_msgs::Bool msg;
};