#include "head/HeadPan.h"

HeadPan::HeadPan(bool enabled) : enabled(enabled), nh(), pan_cmd(nh), async_spinner(1, &callback_queue) {
    nh.setCallbackQueue(&callback_queue);

    set_up_subscriber(nh);

    async_spinner.start();
}

void HeadPan::set_up_subscriber(ros::NodeHandle &nh) {
    std::string topic = "/robot/head/head_state";
    auto callback = boost::bind(&HeadPan::on_state, this, _1);
    auto ops = ros::SubscribeOptions::create<baxter_core_msgs::HeadState>(topic, 1, callback, ros::VoidPtr(), &callback_queue);
    subscriber = nh.subscribe(ops);
}

void HeadPan::pan(const float target) {
    ROS_INFO_STREAM("pan_cmd.target: " << target);
    pan_cmd.target = target;
}

bool HeadPan::is_panned_angle_the_target() {
    return head_state.is_pan_angle(pan_cmd.target);
}

void HeadPan::on_state(const baxter_core_msgs::HeadState::ConstPtr &state) {
    if ( ! enabled)
        return;

    head_state.set_pan(state->pan);
    if ( ! is_panned_angle_the_target()) {
//        ROS_INFO_STREAM("pan_cmd.publish()");
        pan_cmd.publish();
    }
}
