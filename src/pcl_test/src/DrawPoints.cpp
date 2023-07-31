#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <std_msgs/String.h>
#include "pcl_test/PointCloudMap.h"
#include "pcl_test/received.h"
#include <memory>

// global smart pointer
std::shared_ptr<PointCloudMap> cloudMap = nullptr;

void chatterCallback_online(const nav_msgs::OccupancyGridConstPtr& map)
{
 	int height = map->info.height;
	int width = map->info.width;
	ROS_INFO("height! : %d, width: %d", height, width);
	cloudMap = std::make_shared<PointCloudMap>(PointCloudMap(height, width));
	// 1. count
	cloudMap -> countOccupied(map);
	//ROS_INFO("height : %d, width: %d", cloudMap->GetHeight(), cloudMap->GetWidth());
}

bool receive(pcl_test::received::Response &req, pcl_test::received::Response &res)
{
	//ROS_INFO("received : %ld", (long int)res.width);
	while (!cloudMap) ;
	ROS_INFO("filled!!%d width", cloudMap->GetWidth());
	
	cloudMap -> initMap();
	ROS_INFO("count: %d", cloudMap -> GetOccupied());
	
	pcl::visualization::PCLVisualizer::Ptr viewer = cloudMap -> DrawMap();
	ROS_INFO("point %d", cloudMap -> GetPointX(0));
	viewer -> spin();
	
	return true;
}

int main(int argc, char **argv) 
{
	ros::init(argc, argv, "DrawingPoint");
	ros::NodeHandle n;
	
	// count occupied point
	ros::Subscriber sub1 = n.subscribe("/lidar_deloc_recovery/online_map", 1000, chatterCallback_online);
	
	ros::ServiceServer service = n.advertiseService("result", receive);

	ros::spin();
	return 0;
}
