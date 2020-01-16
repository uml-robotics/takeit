#pragma once

#include <moveit/move_group_interface/move_group_interface.h>

class RightArm {

public:
    bool visualize_only = false; // plan and visualize

    moveit::planning_interface::MoveGroupInterface arm_group;

    RightArm();

    void move_to_pose(const geometry_msgs::Pose &p);

    bool follow_trajectory(const std::vector<geometry_msgs::Pose> &vector);

    void set_velocity(const double v);

    void set_acceleration(const double a);

    void stop();
};