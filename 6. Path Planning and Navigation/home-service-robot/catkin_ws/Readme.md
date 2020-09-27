

Our objective is simulating a delivery robot that picks an object from the given location and delivers to the target location. We used _add_markers_ C++ script for visualizing objects in rviz environment and _pick_objects_ C++ script for navigation goal setting. For the execution of the objective, the robot maps it environment using laser scan and simultaneous localization and mapping (SLAM) ROS package. Then using Adaptive Monte Carlo localization (AMCL) ROS package, it navigates on the map.

Note: In the Udacity workspace it was necessary to "pip install rospkg".
