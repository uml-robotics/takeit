#include "head/HeadPanCommand.h"

HeadPanCommand::HeadPanCommand(ros::NodeHandle& nh) {
    publisher = nh.advertise<baxter_core_msgs::HeadPanCommand>("/robot/head/command_head_pan", 1);

    cmd.speed_ratio = 0.075;
    cmd.enable_pan_request = baxter_core_msgs::HeadPanCommand::REQUEST_PAN_ENABLE;
}

void HeadPanCommand::publish() {
    cmd.target = target;
    publisher.publish(cmd);
}
