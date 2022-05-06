#include "slros_initialize.h"

ros::NodeHandle * SLROSNodePtr;
const std::string SLROSNodeName = "accel_to_vel_no_dynamics";

// For Block accel_to_vel_no_dynamics/Subscribe
SimulinkSubscriber<std_msgs::Float64, SL_Bus_accel_to_vel_no_dynamics_std_msgs_Float64> Sub_accel_to_vel_no_dynamics_27;

// For Block accel_to_vel_no_dynamics/Publish
SimulinkPublisher<geometry_msgs::Twist, SL_Bus_accel_to_vel_no_dynamics_geometry_msgs_Twist> Pub_accel_to_vel_no_dynamics_33;

void slros_node_init(int argc, char** argv)
{
  ros::init(argc, argv, SLROSNodeName);
  SLROSNodePtr = new ros::NodeHandle();
}

