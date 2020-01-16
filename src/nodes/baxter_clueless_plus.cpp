#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <head/HeadHandCoordinationEnable.h>
#include "head/Head.h"

#include "HandoverController.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_clueless_plus");

    HandoverController().put_object_down();

    HeadHandCoordinationEnable head_hand_coordination_enable;
    head_hand_coordination_enable.disable();

    /* shake head - the plus part */
    Head head(true, ros::NodeHandle());

//    geometry_msgs::Point r; r.x = 0.96; r.y = -0.96; r.z = -0.13;
    geometry_msgs::Point r; r.x = 0.8; r.y = -0.3; r.z = -0.13;

//    geometry_msgs::Point m; m.x = 1.125; m.y = -0.65; m.z = 0;
    geometry_msgs::Point m; m.x = 0.8; m.y = -0.1; m.z = -0.13;

//    geometry_msgs::Point l; l.x = 1.18; l.y = -0.43; l.z = -0.13;
    geometry_msgs::Point l; l.x = 0.8; l.y = 0.1; l.z = -0.13;

    head.shake_head_while_ros_ok(r, m, l, 3);
}