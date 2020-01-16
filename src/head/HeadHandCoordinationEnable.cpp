#include "head/HeadHandCoordinationEnable.h"
#include <ros/node_handle.h>

using std::string;

HeadHandCoordinationEnable::HeadHandCoordinationEnable() {
    ros::NodeHandle nh;
    publisher = nh.advertise<std_msgs::Bool>("/zhao/head_hand_coordination/enable", 10);

}

void HeadHandCoordinationEnable::get_ready() {
    // wait for subscriber
    ros::Rate r(100);
    while(publisher.getNumSubscribers() == 0) {
        ROS_INFO_STREAM("getting publishers...");
        r.sleep();
    }
}

void HeadHandCoordinationEnable::enable() {
    ROS_INFO_STREAM("enabling head_hand_coordination_enable...");
    msg.data = true;
    publisher.publish(msg);
}

void HeadHandCoordinationEnable::disable() {
    ROS_INFO_STREAM("disabling head_hand_coordination_enable...");
    msg.data = false;
    publisher.publish(msg);
}
