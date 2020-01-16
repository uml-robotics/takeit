#pragma once

#include <ros/node_handle.h>
#include <ros/callback_queue.h>
#include <ros/spinner.h>
#include <ros/subscriber.h>
#include <baxter_core_msgs/HeadState.h>

#include "HeadState.h"
#include "HeadPanCommand.h"

// operated on its own thread
class HeadPan {
public:
    HeadPan(bool enabled);

    bool enabled;

    void pan(float target);

    bool is_panned_angle_the_target();

private:
    ros::NodeHandle nh;
    ros::CallbackQueue callback_queue; // own queue so no other callbacks are called when checking if pan angle is reached.
    ros::AsyncSpinner async_spinner;

    /* pub & sub */
    HeadPanCommand pan_cmd;
    ros::Subscriber subscriber;
    void set_up_subscriber(ros::NodeHandle &nh);

    /* state ops */
    HeadState head_state;
    void on_state(const baxter_core_msgs::HeadState::ConstPtr &state);
};