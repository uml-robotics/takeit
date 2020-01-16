#include <ros/ros.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_interface/planning_interface.h>

using namespace moveit::planning_interface;

int main(int argc, char **argv) {

    ros::init(argc, argv, "replay_node");

    // must-have for moveit to work
    ros::AsyncSpinner spinner(1);
    spinner.start();

    MoveGroupInterface ur5("manipulator");

    // target pose
    // TODO record on the real robot
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




    // reset arm
    // similar to baxter
    // 1. record pose: rostopic echo -n 1 TOPIC
    // 2. move there w/ moveit
}