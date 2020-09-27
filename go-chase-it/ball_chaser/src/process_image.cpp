#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
  

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // TODO: Request a service and pass the velocities to it to drive the robot
   ROS_INFO_STREAM("Driving through the white ball");

    // Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the command_robot service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service command_robot");
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    bool white = false;

   
    int left_side = img.step / 3;
    int middle = left_side * 2;
    float a = 0.0;
    float b = 0.0;
  
    // Loop through each pixel in the image and check if it's a white pixel (255,255,255)
    for (int i = 0; i < img.height * img.step; i += 3) {
        if ((img.data[i] == white_pixel) && (img.data[i + 1] == white_pixel) && (img.data[i + 2] == white_pixel)) {
           
            white = true;
	    a = 0.9;
	    int remainder = i % img.step;
            if (remainder < left_side) {
		b = -0.3; }
            else if (remainder < middle) {
		b = 0.0; }
	    else {
		b = 0.3;}
            break;
        }
	
    }
    // If the pixel is white then drive towards it and if it is not stop 
    // if (white)
    drive_robot(a, b);
	
    //if (!white)
	//drive_robot(a, b);
	
	
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
