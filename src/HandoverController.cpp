#include "HandoverController.h"

#include "head/HeadHandCoordinationEnable.h"
#include "Gripper.h"
#include "Scene.h"
#include "msg_reader/PoseMsgReader.h"
#include "RightArm.h"


HandoverController::HandoverController(bool enable_head_coordination) {
    head_hand_coordination_enable = new HeadHandCoordinationEnable();

    read_poses();

    spinner = new ros::AsyncSpinner(1);
    spinner->start();

    gripper = new Gripper("right");

    Scene scene;

    right_arm = new RightArm;
    right_arm->set_velocity(0.6);

    if (enable_head_coordination) {
        head_hand_coordination_enable->get_ready();
        head_hand_coordination_enable->enable();
    }
    else {
        head_hand_coordination_enable->get_ready();
        head_hand_coordination_enable->disable();
    }
}

void HandoverController::read_poses() {
    std::string path = "/home/zhao/Dropbox/muri/experiment/catkin_ws/src/takeit/pose/";

    natural_down_pose = PoseMsgReader::read(path + "natural-down.bag");

    hold_pose = PoseMsgReader::read(path + "1-hold.bag");
    put_down_pose = PoseMsgReader::read(path + "2-place.bag");

    path = "/home/zhao/Dropbox/muri/experiment/catkin_ws/src/takeit/pose/legible/";
    legible_traj.emplace_back(*(PoseMsgReader::read(path + "place-up.bag")));
    legible_traj.emplace_back(*(PoseMsgReader::read(path + "middle.bag")));
    legible_traj.emplace_back(*(PoseMsgReader::read(path + "furthest.bag")));
}

HandoverController::~HandoverController() {
    delete gripper;
    delete right_arm;
    delete spinner;
    delete head_hand_coordination_enable;
}

void HandoverController::hold_object() {
    gripper->open();
    right_arm->move_to_pose(*hold_pose);
    std::cout << "Place the object in gripper, and press to continue...";
    std::cin.ignore();
    gripper->grip();
}

void HandoverController::put_object_down() {
    right_arm->move_to_pose(*put_down_pose);
    gripper->open();
}

void HandoverController::try_reach(const int REPEAT_TIMES) {
    gripper->open();

    auto traj = std::vector<geometry_msgs::Pose>{legible_traj[0], legible_traj[2]};
    if (REPEAT_TIMES > 0) {
        for (int i = 0; i < REPEAT_TIMES; ++i) {
            traj.emplace_back(legible_traj[1]);
            traj.emplace_back(legible_traj[2]);
        }
    }
    right_arm->follow_trajectory(traj);
}

void HandoverController::go_reach() {
    gripper->open();

    auto traj_before_shaking_head = std::vector<geometry_msgs::Pose>{legible_traj[0], legible_traj[2]};
    right_arm->follow_trajectory(traj_before_shaking_head);
}

void HandoverController::repeat_reach(const int REPEAT_TIMES) {
    gripper->open();

    auto traj = std::vector<geometry_msgs::Pose>();
    if (REPEAT_TIMES > 0) {
        for (int i = 0; i < REPEAT_TIMES; ++i) {
            traj.emplace_back(legible_traj[1]);
            traj.emplace_back(legible_traj[2]);
        }
    }
    right_arm->follow_trajectory(traj);
}

void HandoverController::back_to_natural_down() const {
    right_arm->move_to_pose(*natural_down_pose);
}

void HandoverController::stop() {
    right_arm->stop();
}
