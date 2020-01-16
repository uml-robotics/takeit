#pragma once

#include <string>
#include <ros/publisher.h>
#include <ros/subscriber.h>
#include <ros/rate.h>
#include <baxter_core_msgs/EndEffectorState.h>

// forward declaration
namespace ros { class NodeHandle; }

class Gripper {

public:
    // calibrate if haven't
    Gripper(const std::string &which_side);

    void grip();

    void open();
    void release() { open(); };

    bool is_gripping();
    bool is_open(float tolerance=8);

    bool is_ready_for_another_command();

    bool is_executing_command();

private:
    const std::string which_side;

    ros::Publisher publisher;
    ros::Subscriber subscriber;
    baxter_core_msgs::EndEffectorState::Ptr state = nullptr;
    ros::Rate publisher_rate = ros::Rate(20);

    void wait_until_first_gripper_state_msg_arrived();
    void on_state(const baxter_core_msgs::EndEffectorState::Ptr &state);

    void calibrate();
    bool is_calibrated();
};
