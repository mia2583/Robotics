#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseArray.h>
#include <std_msgs/String.h>
#include "pcl_test/OnlinePointCloud.h"
#include "pcl_test/GlobalPointCloud.h"
#include "pcl_test/received.h"
#include <pcl/kdtree/kdtree_flann.h>
#include <memory>

// global smart pointer
std::shared_ptr<OnlinePointCloud> onlinePointCloud = nullptr;
std::shared_ptr<GlobalPointCloud> globalPointCloud = nullptr;
std::vector<float> error;

void readOnlineOrigin(const nav_msgs::OccupancyGridConstPtr& map)
{
	// T_om assign
	onlinePointCloud -> SetTom(map->info.origin.position.x, map->info.origin.position.y, map->info.origin.position.z);
	ROS_INFO("tom[0]: %lf", map->info.origin.position.x);
}

void readGlobalOrigin(const nav_msgs::OccupancyGridConstPtr& map)
{
	// T_gm assign
	globalPointCloud -> SetTgm(map->info.origin.position.x, map->info.origin.position.y, map->info.origin.position.z);
}	

// 1. count occupied point
void analyze_online(const nav_msgs::OccupancyGridConstPtr& map)
{
 	int height = map->info.height;
	int width = map->info.width;
	// count for initialize
	onlinePointCloud = std::make_shared<OnlinePointCloud>(OnlinePointCloud(height, width));
	readOnlineOrigin(map);
	onlinePointCloud -> countOccupied(map);	
}
void analyze_global(const nav_msgs::OccupancyGridConstPtr& map)
{
 	int height = map->info.height;
	int width = map->info.width;
	// count for initialize
	globalPointCloud = std::make_shared<GlobalPointCloud>(GlobalPointCloud(height, width));
	readGlobalOrigin(map);
	globalPointCloud -> countOccupied(map);
}

void readTmap(const geometry_msgs::PoseArray& arr)
{
 	// T_map assign
	onlinePointCloud -> SetTmap(arr.poses[0].position.x, arr.poses[0].position.y, arr.poses[0].position.z);
	//ROS_INFO("size of tmap: %d", arr.poses.size());
	ROS_INFO("tmap[0]: %lf", arr.poses[0].position.x);
	// check the size of poses -> 1 is best
}


// 5. change each points to coordinates with online frame origin
bool changePoints(pcl_test::received::Response &req, pcl_test::received::Response &res)
{	
	ros::NodeHandle nn;
	
	while (!onlinePointCloud) ;
	onlinePointCloud -> initMap();
	while (!globalPointCloud) ;
	globalPointCloud -> initMap();
	
	//ros::Subscriber sub1 = nn.subscribe("/lidar_deloc_recovery/online_map_poses", 10, readTmap);
	
	ROS_INFO("completed:");
	
	pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree = pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr(new pcl::KdTreeFLANN<pcl::PointXYZ>);
	globalPointCloud -> assignKdtree(kdtree);
	onlinePointCloud -> findBestMatch(kdtree);
	
	ROS_INFO("continue:");
	cv::Mat im = onlinePointCloud -> drawErrorMap();
	cv::imwrite("errorMap.jpg", im);
  	ROS_INFO("done Error Map");
	
	return true;
}




int main(int argc, char **argv) {
	ros::init(argc, argv, "CalculateError");
	ros::NodeHandle n;
	
	// 1. count occupied point, read online map(new pc=T_p)
	//    subscribe origin of online map(T_om) 
	ros::Subscriber sub1 = n.subscribe("/lidar_deloc_recovery/online_map", 10, analyze_online);
	// 2. subscribe global map(new pc = T_q)
	//    subscribe origin of global map(T_gm) 
	ros::Subscriber sub2 = n.subscribe("/map", 1000, analyze_global);
	// 3. subscribe GlobalToOnline(T_map)
	ros::Subscriber sub3 = n.subscribe("/lidar_deloc_recovery/online_map_poses", 10, readTmap);
	// 4. check whether online, global map is assigned and save it as pc
	// 5. change each point coordinate with online map frame origin
	ros::ServiceServer service = n.advertiseService("result", changePoints);
	

	
	// 6. find best match
	
	// 7. draw error-color map
	//onlinePointCloud -> drawErrorMap();
	//ros::ServiceServer service = n.advertiseService("result", receive);

	ros::spin();
	return 0;
}
