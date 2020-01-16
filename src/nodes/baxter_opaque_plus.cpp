#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include "head/HeadHandCoordinationEnable.h"
#include "head/Head.h"

#include "HandoverController.h"

int main(int argc, char **argv) {

    ros::init(argc, argv, "baxter_opaque");

    {
        HandoverController().put_object_down();
    }

    /* move head - look at object position */

    HeadHandCoordinationEnable head_hand_coordination_enable;
    Head head(true, ros::NodeHandle());

    //  Retrieved by running the following command and take the position part in the pose part
    //  rostopic echo -n 1 /robot/limb/right/endpoint_state
    geometry_msgs::Point object_position;
    object_position.x = 1.0768;
    object_position.y = -0.656;
    object_position.z = -0.102;

    {
        ros::Rate r(50);
        while (ros::ok()) {
            head_hand_coordination_enable.disable();
            head.async_look_at(object_position);
            ros::spinOnce();
            if (head.is_done_movement())
                break;
            else
                r.sleep();
        }
    }

    /* shake head - the plus part */

    geometry_msgs::Point r; r.x = 0.96; r.y = -0.96; r.z = 0.05;
    geometry_msgs::Point m; m.x = 1.125; m.y = -0.65; m.z = 0;
    geometry_msgs::Point l; l.x = 1.18; l.y = -0.43; l.z = 0.017;
    head.shake_head_while_ros_ok(r, m, l, 3);
}