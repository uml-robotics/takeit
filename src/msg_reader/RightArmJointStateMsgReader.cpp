#include "msg_reader/RightArmJointStateMsgReader.h"

void RightArmJointStateMsgReader::read_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out) {
    read_single_joint_state(bag_filename, out);
}

void RightArmJointStateMsgReader::read_single_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out) {
    sensor_msgs::JointState read;
    JointStateMsgReader::read_single_joint_state(bag_filename, read);

    for (std::size_t i = 0; i < read.name.size(); ++i) {
        bool is_right_arm_joint = (read.name[i].find("right_", 0) == 0);
        if (is_right_arm_joint) {
            out.name.push_back(read.name[i]);
            out.position.push_back(read.position[i]);
        }
    }
}
