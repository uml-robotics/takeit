#pragma once

#include <baxter_core_msgs/HeadState.h>

class HeadState {

public:
    HeadState() = default;
    void set_pan(float p);
    bool is_pan_angle(float target);

private:
    float pan;
};