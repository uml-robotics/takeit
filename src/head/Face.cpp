#include "head/Face.h"
#include <ros/node_handle.h>
#include "head/FaceImage.h"

Face::Face(ros::NodeHandle& nh, std::string face_dir) : last_eyeball_value(-10000) {
    face = FaceImage::create(face_dir);
    eyeball_vertical_subscriber = nh.subscribe("/zhao/robot/head/face/eyeball/vertical_value", 1, &Face::on_vertical_value, this);
}

void Face::spin() {
    ros::Rate r(10);
    while (ros::ok()) {
        ros::spinOnce();
        if (last_eyeball_value != -10000 && last_eyeball_value != target_eyeball_value) {
            move_to_target_value(target_eyeball_value);
        }
        r.sleep();
    }
}

void Face::on_vertical_value(const std_msgs::Int32::ConstPtr &msg) {
    puts("");
    ROS_INFO_STREAM(target_eyeball_value << " - RECEIVED");
    target_eyeball_value = msg->data;

    if (target_eyeball_value > 20)
        target_eyeball_value = 20;
    else if (target_eyeball_value < -20)
        target_eyeball_value = -20;

    ROS_INFO_STREAM(target_eyeball_value << " - TARGET");

    if (last_eyeball_value == -10000) {
        // show face image directly
        screen->display(face->with_eyeballs_vertically(target_eyeball_value));
        last_eyeball_value = target_eyeball_value;
    }
    else {
        move_to_target_value(target_eyeball_value);
    }
}

// interpolate
void Face::move_to_target_value(int target_eyeball_value) {
//    ROS_INFO_STREAM(last_eyeball_value << " - LAST");
    if (target_eyeball_value == last_eyeball_value) {
        ROS_INFO_STREAM("NO MOVE");
        return;
    }

    int step = 1;
    int next_eyeball_value;

    if (target_eyeball_value > last_eyeball_value) {
        int diff = target_eyeball_value - last_eyeball_value;
        if (diff > step) {
            next_eyeball_value = last_eyeball_value + step;
        }
        else {
            next_eyeball_value = target_eyeball_value;
        }
    }
    else { // target_eyeball_value < last_eyeball_value
        int diff = last_eyeball_value - target_eyeball_value;
        if (diff > step) {
            next_eyeball_value = last_eyeball_value - step;
        }
        else {
            next_eyeball_value = target_eyeball_value;
        }
    }

    ROS_INFO_STREAM(next_eyeball_value << " - MOVING TO");
    screen->display(face->with_eyeballs_vertically(next_eyeball_value));

    last_eyeball_value = next_eyeball_value;
}
