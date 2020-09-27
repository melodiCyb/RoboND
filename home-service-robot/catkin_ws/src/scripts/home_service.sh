export ROBOT_INITIAL_POSE='-x 3.56 -y 0.04 -z 0.1 -R 0 -P 0 -Y 0';

xterm -e "roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/worlds/livingroom.world " &

sleep 5

xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/map/map.yaml" &

sleep 5

xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" & 

sleep 5
xterm  -e  "rosrun pick_objects pick_objects" &

sleep 5
xterm  -e  "rosrun add_markers add_markers" 
