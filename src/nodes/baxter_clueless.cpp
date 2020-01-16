#include <ros/ros.h>
#include <geometry_msgs/Point.h>

#include "HandoverController.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_clueless");

    HandoverController().put_object_down();
}