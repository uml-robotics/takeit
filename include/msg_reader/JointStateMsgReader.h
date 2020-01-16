#pragma once

#include <sensor_msgs/JointState.h>

class JointStateMsgReader {

public:
    std::vector<sensor_msgs::JointState> msgs;

    void read(const std::string &relative_path, const std::vector<std::string> &file_names_without_extension);
/*
rosbag record --limit=1 /robot/joint_states --output-name=-.bag
 */
    static void read_single_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out);

protected:
    virtual void read_joint_state(const std::string &bag_filename, sensor_msgs::JointState &out);

};