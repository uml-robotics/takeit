#include "Gripper.h"

#include <ros/node_handle.h>
#include <baxter_core_msgs/EndEffectorCommand.h>

using baxter_core_msgs::EndEffectorState;
using baxter_core_msgs::EndEffectorCommand;

Gripper::Gripper(const std::string &which_side) : which_side(which_side) {
    ros::NodeHandle nh;

    std::string ns = "/robot/end_effector/" + which_side + "_gripper/";

    std::string pub_name = ns + "command";
    publisher = nh.advertise<EndEffectorCommand>(pub_name, 1);

    std::string sub_name = ns + "state";
    subscriber = nh.subscribe(sub_name, 1, &Gripper::on_state, this);

    wait_until_first_gripper_state_msg_arrived();
}

void Gripper::wait_until_first_gripper_state_msg_arrived() {
    do {
        publisher_rate.sleep();
        ros::spinOnce();
    } while (ros::ok() && !state);
    ROS_DEBUG_STREAM_NAMED("gripper", "Received first gripper state msg");
}

void Gripper::on_state(const EndEffectorState::Ptr &state) {
    this->state = state;
//    ROS_DEBUG_STREAM_NAMED("gripper", "received gripper state: " << *state);
    if ( ! this->is_calibrated()) {
        calibrate();
    }
}

void Gripper::calibrate() {
    EndEffectorCommand cmd;
    cmd.id = state->id;
    cmd.command = EndEffectorCommand::CMD_CALIBRATE;
    while (ros::ok() && ! is_calibrated()) {
        publisher.publish(cmd);
        ros::spinOnce();
        publisher_rate.sleep();
    }
}

void Gripper::grip() {
    ROS_DEBUG_STREAM_NAMED("gripper", "Gripper::grip");

    EndEffectorCommand cmd;
    cmd.id = state->id;
    cmd.command = EndEffectorCommand::CMD_GRIP;

    do {
        ROS_DEBUG_STREAM_NAMED("gripper", "Gripper::grip publishing...");
        publisher.publish(cmd);
        ros::spinOnce();
        publisher_rate.sleep();
    } while (ros::ok() && this->is_gripping());
}

bool Gripper::is_calibrated() {
    if (state)
        return state->calibrated == EndEffectorState::STATE_TRUE;
    else
        return false;
}

bool Gripper::is_gripping() {
    if (state)
        return state->gripping == EndEffectorState::STATE_TRUE;
    else
        return false;
}

void Gripper::open() {
    ROS_DEBUG_STREAM_NAMED("gripper", "Gripper::open");

    EndEffectorCommand cmd;
    cmd.id = state->id;
    cmd.command = EndEffectorCommand::CMD_GO;
    cmd.args = "{\"position\": 100.0}";
    do {
        ROS_DEBUG_STREAM_NAMED("gripper", "Gripper::open publishing...");
        publisher.publish(cmd);
        ros::spinOnce();
        publisher_rate.sleep();
    } while (ros::ok() && ! is_open());
}

bool Gripper::is_open(float tolerance) {
    return this->state->position >= EndEffectorState::POSITION_OPEN - tolerance;
}

bool Gripper::is_ready_for_another_command() {
    return this->state->ready == 1;
}

bool Gripper::is_executing_command() {
    return ! is_ready_for_another_command();
}
