#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_interface/planning_interface.h>
#include <moveit/move_group_interface/move_group.h>
#include "Execution.h"

using namespace moveit::planning_interface;
using moveit::planning_interface::MoveGroup;

/**
 * TODO move to a specific
 */

int main(int argc, char **argv) {

    ros::init(argc, argv, "replay_node");

    // must-have for moveit to work
    ros::AsyncSpinner spinner(1);
    spinner.start();

    MoveGroupInterface ur5("manipulator");

    // target pose
    // TODO
    //  record on the real robot
    //    check rostopic for the physical robot
    //  or follow trajectory (see the next block)
    geometry_msgs::Pose target_pose1;
    target_pose1.position.x = 0;
    target_pose1.position.y = 0.19;
    target_pose1.position.z = 1;
    target_pose1.orientation.x = 0;
    target_pose1.orientation.y = 0;
    target_pose1.orientation.z = 0.707;
    target_pose1.orientation.w = 0.707;
    ur5.setPoseTarget(target_pose1);


//    moveit::planning_interface::MoveGroupInterface::Plan my_plan;

//    bool success = (bool)ur5.plan(my_plan);

//    ROS_INFO("Visualizing plan 1 (pose goal) %s", success ? "" : "FAILED");


    bool success = (bool)ur5.move();

    ROS_INFO("move result (pose goal) %s", success ? "" : "FAILED");



    // copied from RightArm.cpp


    // compute trajectory
    double one_cm_step = 0.01;
    double disable_jump = 0.0;
    moveit_msgs::RobotTrajectory trajectory;
    double fraction = ur5.computeCartesianPath(waypoints, one_cm_step, disable_jump, trajectory);
    ROS_INFO("follow_trajectory computeCartesianPath: %.2f%% achieved", fraction * 100.0);

    // construct plan
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    plan.trajectory_ = trajectory;

//    if (visualize_only) {
//        const MoveItErrorCode &result = arm_group.plan(plan);
//        ROS_INFO("follow_trajectory plan %s", result ? "SUCCESS" : "FAILED");
//        return (bool)result;
//    }
//    else {
        const MoveItErrorCode &result = ur5.execute(plan);
        ROS_INFO_STREAM("follow_trajectory result:" << result);
        return (bool)result;
//    }




    for (int i = 0; i < execution::N_TIMES; ++i) {
        // run the same times as Baxter
    }










    // reset arm
    // similar to baxter
    // 1. record pose: rostopic echo -n 1 TOPIC
    // 2. move there w/ moveit
}