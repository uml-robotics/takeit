#pragma once

#include <ros/node_handle.h>
#include <ros/publisher.h>
#include <baxter_core_msgs/HeadPanCommand.h>

class HeadPanCommand {

public:
    float target;
    explicit HeadPanCommand(ros::NodeHandle& nh);
    void publish();

private:
    ros::Publisher publisher;
    baxter_core_msgs::HeadPanCommand cmd;
};