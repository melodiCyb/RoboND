#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 8 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(8.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // set up the frame parameters
  goal.target_pose.header.frame_id = "odom"; //"map";
  goal.target_pose.header.stamp = ros::Time::now();
  //ros::Duration(8.0).sleep(); 
  // Define a position and orientation for the robot to reach
  goal.target_pose.pose.position.x = 1.29;  
  goal.target_pose.pose.position.y = 0.4; 
  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, robot reached to pick up point!");
  else
    ROS_INFO("The base failed to reach to pick up point for some reason");
  // Wait an infinite time for the results
 // ac.waitForResult();
  ros::Duration(5.0).sleep(); 
 
  // Drop zone - bring back
  goal.target_pose.pose.position.x = -0.73; 
  goal.target_pose.pose.position.y = -1.57; 

  goal.target_pose.pose.orientation.w = 1.0;

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, robot has arrived to the target destination!");
  else
    ROS_INFO("The base failed to go to the target destination for some reason");

  return 0;
}
