#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include "head/HeadHandCoordinationEnable.h"
#include "head/Head.h"
#include "HandoverController.h"
#include "Execution.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_legible");

    auto controller = HandoverController();
    controller.put_object_down();

    controller.go_reach();
    controller.repeat_reach(execution::N_TIMES);
}