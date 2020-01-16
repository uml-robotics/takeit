#include "Scene.h"

#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

using moveit::planning_interface::MoveGroup;
using moveit::planning_interface::PlanningSceneInterface;

moveit_msgs::CollisionObject::Ptr Scene::getTable() {
    if (table)
        return table;
    else {
        // table shape
        shape_msgs::SolidPrimitive table_shape;

        // the round table in the lab
//        table_shape.type = table_shape.CYLINDER;
//        table_shape.dimensions.resize(2);
//        table_shape.dimensions[table_shape.CYLINDER_HEIGHT] = 0.03;
//        table_shape.dimensions[table_shape.CYLINDER_RADIUS] = 0.9042 / 2.0; // 35.6 inches = 90.42 cm

        table_shape.type = table_shape.BOX;
        table_shape.dimensions.resize(3);
        table_shape.dimensions[table_shape.BOX_X] = 0.75184; // width: 29.6 in
        table_shape.dimensions[table_shape.BOX_Y] = 1.81864; // length: 71.6 in
        table_shape.dimensions[table_shape.BOX_Z] = 0.76200; // height: 30 inch

        // table pose
        geometry_msgs::Pose table_pose;

        // the round table in the lab
//        table_pose.position.x = 0.7508;
//        table_pose.position.y = 0;
//        table_pose.position.z = -0.1475;

        table_pose.position.x = 0.57525 + 0.75184 / 2.0     -0.02; // 10 is the edge threshold
        table_pose.position.y = 0;
        table_pose.position.z = -0.19827 - 0.7366 / 2.0     +0.02; // 10 is the edge threshold
        table_pose.orientation.w = 1.0;

        // construct collision object
        table = moveit_msgs::CollisionObject::Ptr(new moveit_msgs::CollisionObject);
        table->header.frame_id = "world";
        table->id = "table";
        table->primitives.push_back(table_shape);
        table->primitive_poses.push_back(table_pose);

        table->operation = table->ADD;

        return table;
    }
}

void Scene::setup() {

    moveit_msgs::AttachedCollisionObject table_to_avoid;
    table_to_avoid.link_name = "world";
    table_to_avoid.object = *this->getTable();

    bool is_applied = PlanningSceneInterface().applyCollisionObject(table_to_avoid.object);
//    PlanningSceneInterface().addCollisionObjects({table_to_avoid.object});
    ROS_INFO_STREAM("applied table to planning scene: " << std::boolalpha << is_applied);
}
