#include "head/HeadHandCoordination.h"

#include <angles/angles.h>

HeadHandCoordination::HeadHandCoordination(std::string which_side, ros::NodeHandle nh, bool enabled)
        : enabled(enabled), head(enabled, nh) {

    ROS_INFO_STREAM("HeadHandCoordination::enabled: " << enabled);

    enable_subscriber = nh.subscribe("/zhao/head_hand_coordination/enable", 1, &HeadHandCoordination::on_enable, this);

    std::string topic = "/robot/limb/" + which_side + "/endpoint_state";
    hand_state_subscriber = nh.subscribe(topic, 1, &HeadHandCoordination::on_hand_state, this);
}

void HeadHandCoordination::on_enable(const std_msgs::Bool::ConstPtr& enabled_msg) {
    enabled = enabled_msg->data;
    ROS_INFO_STREAM(enabled << " (" << "HeadHandCoordination::on_enable)");
    head.set_enable(enabled);
}

void HeadHandCoordination::on_hand_state(const baxter_core_msgs::EndpointState::ConstPtr& state) {
    if ( ! enabled)
        return;

    head.async_look_at(state->pose.position);
}

void HeadHandCoordination::spin() {
    ros::Rate r(50);
    while (ros::ok()) {
        ros::spinOnce();
        r.sleep();
    }
}