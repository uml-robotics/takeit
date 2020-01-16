#include "msg_reader/JointStateMsgReader.h"

#include <ros/console.h>

#include <rosbag/bag.h>
#include <rosbag/view.h>

void JointStateMsgReader::read(const std::string &relative_path, const std::vector<std::string> &file_names_without_extension) {
    msgs.resize(file_names_without_extension.size());
    ROS_INFO_STREAM_NAMED("JointStateMsgReader", "reading " << file_names_without_extension.size() << " messages...");
    for (std::size_t i = 0; i < file_names_without_extension.size(); ++i) {
        std::ostringstream path; path << relative_path << file_names_without_extension[i] << ".bag";
        read_joint_state(path.str(), msgs.at(i));
        ROS_DEBUG_STREAM(msgs.at(i));
    }
    ROS_INFO_STREAM_NAMED("JointStateMsgReader", "done reading " << file_names_without_extension.size() << " messages.");
}

void JointStateMsgReader::read_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out) {
    read_single_joint_state(bag_filename, out);
}

void JointStateMsgReader::read_single_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out) {
    std::string topic = "/robot/joint_states";

    rosbag::Bag bag;
    bag.open(bag_filename, rosbag::bagmode::Read);

    std::vector<std::string> topics = {topic};
    rosbag::View view(bag, rosbag::TopicQuery(topics));

    bool has_msg = (view.size() != 0);
    if (has_msg) {
        sensor_msgs::JointState::ConstPtr msg = view.begin()->instantiate<sensor_msgs::JointState>();
        out = *msg;
    }
    else {
        ROS_WARN_STREAM_NAMED("JointStateMsgReader", "No message found in" + bag_filename);
    }

    bag.close();
}