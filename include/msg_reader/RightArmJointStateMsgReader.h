#pragma once

#include "JointStateMsgReader.h"

class RightArmJointStateMsgReader : public JointStateMsgReader {

public:
    static void read_single_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out);

protected:
    void read_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out) override;
};