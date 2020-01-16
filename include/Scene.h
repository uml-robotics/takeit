#pragma once

#include <moveit_msgs/CollisionObject.h>

class Scene {

public:
    Scene() { setup(); }

    moveit_msgs::CollisionObject::Ptr getTable();

private:
    void setup();

    moveit_msgs::CollisionObject::Ptr table;
};