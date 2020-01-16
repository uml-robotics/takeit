#include <ros/init.h>
#include <ros/node_handle.h>
#include "head/Face.h"

int main(int argc, char **argv) {
    ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug);

    std::string face_dir = argv[1];
    if (argc == 0) {
        ROS_ERROR_STREAM("Please specify face_dir");
        return 1;
    }
    else
        ROS_INFO_STREAM("face_dir: " << argv[1]);

    ros::init(argc, argv, "zhao_baxter_head_face_node");

    ros::NodeHandle nh;

    Face face(nh, face_dir);

    face.spin();

    return 0;
}