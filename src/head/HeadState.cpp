#include <ros/console.h>
#include "head/HeadState.h"

void HeadState::set_pan(float p) {
    pan = p;
}

bool HeadState::is_pan_angle(float target) {
    double min = pan - 0.09;
    double max = pan + 0.09;
//    ROS_INFO_STREAM("pan diff: " << target - pan << " (" << target << " - " << pan << ")");
    bool result = target >= min && target <= max;
    return result;
}