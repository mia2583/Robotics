#include <ros/ros.h>
#include "pcl_test/received.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "send");
	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<pcl_test::received>("result");
	pcl_test::received srv;
	if (client.call(srv))
	{
		ROS_INFO("send!!");
	}
}
