#pragma once

#include <string>
#include <boost/shared_ptr.hpp>
#include <geometry_msgs/Pose.h>

class PoseMsgReader {

public:
    static boost::shared_ptr<geometry_msgs::Pose> read(const std::string &bag_filename);
};