#include "msg_reader/PoseMsgReader.h"

#include <vector>
#include <ros/console.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <baxter_core_msgs/EndpointState.h>

using boost::shared_ptr;
using geometry_msgs::Pose;

shared_ptr<Pose> PoseMsgReader::read(const std::string &bag_filename) {
    rosbag::Bag bag;
    bag.open(bag_filename, rosbag::bagmode::Read);

    std::vector<std::string> topics = {"/robot/limb/right/endpoint_state"};
    rosbag::View view(bag, rosbag::TopicQuery(topics));

    bool has_msg = (view.size() != 0);
    if (has_msg) {
        baxter_core_msgs::EndpointState::Ptr endpoint_state_msg
                = view.begin()->instantiate<baxter_core_msgs::EndpointState>();
        bag.close();
        return boost::make_shared<Pose>(endpoint_state_msg->pose);
    }
    else {
        ROS_WARN_STREAM("No message found in" << bag_filename);
    }
}