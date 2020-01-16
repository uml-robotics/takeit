#include "head/Head.h"
#include <angles/angles.h>
#include <std_msgs/Int32.h>

const double Head::CALIBRATED_PAN_DIFF = angles::from_degrees(-4);

Head::Head(bool enabled, ros::NodeHandle nh) : head_pan(enabled) {
    eyeball_publisher = nh.advertise<std_msgs::Int32>("/zhao/robot/head/face/eyeball/vertical_value", 1);
}

void Head::set_enable(bool enabled) {
    head_pan.enabled = enabled;
}

// asyn: see HeadPan#pan()
void Head::async_look_at(geometry_msgs::Point position) {
    if ( ! head_pan.enabled)
        return;

    // pan head
    double calibrated_pan_angle = CALIBRATED_PAN_DIFF + calculate_pan_radius(position.x, position.y);
    head_pan.pan(calibrated_pan_angle);

    /* show face with eyeballs */

    double radians_relative_to_head = this->calculate_eyeball_vertical_angle(position.x, position.z);
    double radians_relative_to_screen = radians_relative_to_head + angles::from_degrees(20);
    int vertical_value = (int)(radians_relative_to_screen * -1 / angles::from_degrees(50) * 20);
    if (vertical_value > 20)
        vertical_value = 20;
    if (vertical_value < -20)
        vertical_value = -20;

    std_msgs::Int32 vertical_value_mag;
    vertical_value_mag.data = vertical_value;
    ROS_INFO_STREAM("head published eyeball: " << vertical_value_mag);
    eyeball_publisher.publish(vertical_value_mag);
}

void Head::shake_head_while_ros_ok(geometry_msgs::Point r, geometry_msgs::Point m, geometry_msgs::Point l, int n_times) {
    ros::Rate rate(60);

    int times = 0;
    while (ros::ok() && (head_pan.enabled && times < n_times)) {
        async_look_at(r);
        while (!is_done_movement()) {
            rate.sleep();
        }
        async_look_at(l);
        while (!is_done_movement()) {
            rate.sleep();
        }

        times++;
    }

    async_look_at(m);
    while (!is_done_movement()) {
        rate.sleep();
    }

    ROS_WARN_STREAM("[shake_head] ...shake_head");
}

double Head::calculate_eyeball_vertical_angle(double x, double z) {
//    ROS_INFO_STREAM("x: " << x << ", z: " << z);

    z -= 0.686; // head height
    x -= 0.18268; // screen x translation
//    ROS_INFO_STREAM("x: " << x << ", z: " << z);

    if (z == 0) {
        return 0;
    }

    double abs_x = fabs(x);
    double abs_z = fabs(z);

    double positive_radius = atan(abs_z/abs_x);
    double negative_radius = positive_radius * -1;

    if (z > 0) {
        return positive_radius;
    }
    else {
        return negative_radius;
    }
}

// If x>0 and y=0, it will return -100;
//  because this position is not valid while we don't know and do not want to know the previous pan angle
double Head::calculate_pan_radius(const double &x, const double &y) {
    double abs_x = fabs(x);
    double abs_y = fabs(y);

    double positive_radius = atan(abs_y/abs_x);
    double negative_radius = positive_radius * -1;

    if (x > 0) {
        if (y > 0) {
            return positive_radius;
        }
        else if (y < 0) {
            return negative_radius;
        }
        else {
            return 0;
        }
    }
    else if (x < 0) {
        if (y > 0) {
            return M_PI_2;
        }
        else if ( y < 0) {
            return -M_PI_2;
        }
        else {
            return -100;
        }
    }
    else {
        if (y > 0) {
            return M_PI_2;
        }
        else if (y < 0) {
            return -M_PI_2;
        }
        else {
            throw 0;
        }
    }
}

bool Head::is_done_movement() {
    return head_pan.is_panned_angle_the_target();
}
