#include "RightArm.h"

using moveit::planning_interface::MoveGroupInterface;
using moveit::planning_interface::MoveItErrorCode;

RightArm::RightArm() : arm_group("right_arm") {
}

void RightArm::move_to_pose(const geometry_msgs::Pose &p) {
    arm_group.setPoseTarget(p);

    if (visualize_only) {
        MoveGroupInterface::Plan plan;
        const MoveItErrorCode &success = arm_group.plan(plan);
        ROS_INFO_STREAM("visualize_only: plan " << success?"V":"X");
    }
    else {
        const MoveItErrorCode &result = arm_group.move();
        ROS_INFO_STREAM("move_to_pose result:" << result);
    }
}

bool RightArm::follow_trajectory(const std::vector<geometry_msgs::Pose> &waypoints) {
    // compute trajectory
    double one_cm_step = 0.01;
    double disable_jump = 0.0;
    moveit_msgs::RobotTrajectory trajectory;
    double fraction = arm_group.computeCartesianPath(waypoints, one_cm_step, disable_jump, trajectory);
    ROS_INFO("follow_trajectory computeCartesianPath: %.2f%% achieved", fraction * 100.0);

    // construct plan
    MoveGroupInterface::Plan plan;
    plan.trajectory_ = trajectory;

    if (visualize_only) {
        const MoveItErrorCode &result = arm_group.plan(plan);
        ROS_INFO("follow_trajectory plan %s", result ? "SUCCESS" : "FAILED");
        return (bool)result;
    }
    else {
        const MoveItErrorCode &result = arm_group.execute(plan);
        ROS_INFO_STREAM("follow_trajectory result:" << result);
        return (bool)result;
    }
}

void RightArm::set_velocity(const double v) {
    arm_group.setMaxVelocityScalingFactor(v);
}

void RightArm::set_acceleration(const double a) {
    arm_group.setMaxAccelerationScalingFactor(a);
}

void RightArm::stop() {
    arm_group.stop();
}
