#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include "head/HeadHandCoordinationEnable.h"
#include "head/Head.h"

#include "HandoverController.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_hold_object");

    HandoverController().hold_object();
}