# Robot Explanation Experiment

Code released for reproduction of the experiment in the **Robot Explanations: How and What a Robot Should Convey to People About Its Actions and Decisions** paper.

## Physical Environment Setup

- A Rethink Baxter robot
- A rectangular table in front of Baxter
  - The corner of the table must not be reachable by Baxter's fully extended arm
- A paper cup on the front-right corner of the table (from Baxter's view)

## Software/Dependecies

- Ubuntu 16.04
- [ROS Kinetic](http://wiki.ros.org/kinetic/Installation/Ubuntu)
- [Baxter SDK](http://sdk.rethinkrobotics.com/wiki/Home)
- [MoveIt](http://sdk.rethinkrobotics.com/wiki/MoveIt_Tutorial#Installation.2FPrerequisites) -- replace indigo with kinetic
- [Recommended] [JetBrains CLion IDE](https://www.jetbrains.com/clion/)

# Run the experiment

Make sure you've [setup the Baxter ros environment](http://sdk.rethinkrobotics.com/wiki/Hello_Baxter#Step_1:_Setup_ROS_Environment).

Clone or download this repository to the `src` folder of your catkin workspace.

Enable the robot: `rosrun baxter_tools enable_robot.py -e`

Make Baxter hold the object: `rosrun takeit baxter_hold_object`

Run each execution type created in [src/nodes/](src/nodes/).