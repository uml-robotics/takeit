#pragma once

#include <ros/node_handle.h>
#include <ros/subscriber.h>
#include <std_msgs/Bool.h>
#include <baxter_core_msgs/EndpointState.h>

#include "Head.h"

class HeadHandCoordination {

public:

    // disabled by default
    // to enable:
    //   rostopic pub /zhao/head_hand_coordination/enable std_msgs/Bool "true" -1
    // to disable
    //   rostopic pub /zhao/head_hand_coordination/enable std_msgs/Bool "false" -1
    //
    explicit HeadHandCoordination(std::string which_side, ros::NodeHandle nh, bool enabled);

    void spin();

private:

    using EndpointState = baxter_core_msgs::EndpointState;

    ros::Subscriber enable_subscriber;
    void on_enable(const std_msgs::Bool::ConstPtr& state);
    bool enabled;

    ros::Subscriber hand_state_subscriber;
    void on_hand_state(const EndpointState::ConstPtr& state);

    Head head;
};