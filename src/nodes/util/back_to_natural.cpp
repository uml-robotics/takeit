#include <ros/init.h>
#include "HandoverController.h"

int main(int argc, char **argv) {
    ros::init(argc, argv, "test_handover");
    HandoverController().back_to_natural_down();
    return EXIT_SUCCESS;
}
