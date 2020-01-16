#pragma once

#include <geometry_msgs/Pose.h>

// forward declaration
namespace ros { class NodeHandle; class AsyncSpinner; }
class HeadHandCoordinationEnable;
class Gripper;
class RightArm;


class HandoverController {

public:
    HandoverController(bool enable_head_coordination = true);
    ~HandoverController();

    void stop();

    void try_reach(int REPEAT_TIMES);
    void go_reach();
    void repeat_reach(int REPEAT_TIMES);

    void hold_object();

    void put_object_down();

    void back_to_natural_down() const;

    HeadHandCoordinationEnable* getHeadHandCoordinationEnable() {
        return head_hand_coordination_enable;
    }

private:
    ros::AsyncSpinner* spinner;

    Gripper* gripper;
    RightArm* right_arm;
    HeadHandCoordinationEnable* head_hand_coordination_enable;

    geometry_msgs::Pose::Ptr object_position_pose;

    std::vector<geometry_msgs::Pose> legible_traj;

    geometry_msgs::Pose::Ptr hold_pose, put_down_pose;

    geometry_msgs::Pose::Ptr natural_down_pose;

    void read_poses();
};