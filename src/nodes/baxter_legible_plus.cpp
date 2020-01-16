#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include "head/HeadHandCoordinationEnable.h"
#include "head/Head.h"
#include "HandoverController.h"
#include "Execution.h"
#include <thread>

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_legible_plus");

    auto controller = HandoverController();
    controller.put_object_down();


    auto head = std::make_shared<Head>(false, ros::NodeHandle());

    // go to the furthest point
    controller.go_reach();

    // shake head
    controller.getHeadHandCoordinationEnable()->disable();
    head->set_enable(true);

    geometry_msgs::Point r; r.x = 0.96; r.y = -0.96; r.z = 0.05;
    geometry_msgs::Point m; m.x = 1.125; m.y = -0.65; m.z = 0;
    geometry_msgs::Point l; l.x = 1.18; l.y = -0.43; l.z = 0.017;
//    geometry_msgs::Point l; l.x = 1.2; l.y = -0.27; l.z = 0.20;
    std::thread shake_head_thread(&Head::shake_head_while_ros_ok, head, r, m, l, std::numeric_limits<int>::max());

    // repeat reach
    controller.repeat_reach(execution::N_TIMES);

    ROS_INFO_STREAM("... repeat_reach");

    head->set_enable(false);

}