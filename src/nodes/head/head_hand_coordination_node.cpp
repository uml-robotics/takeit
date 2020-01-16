#include <ros/init.h>
#include <ros/node_handle.h>
#include "head/HeadHandCoordination.h"

int main(int argc, char **argv) {
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

    ros::init(argc, argv, "head_hand_coordination_node");

    ros::NodeHandle nh;

    HeadHandCoordination("right", nh, false).spin();

    return 0;
}