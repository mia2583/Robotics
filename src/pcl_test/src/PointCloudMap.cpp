#include "pcl_test/PointCloudMap.h"
#include <geometry_msgs/Pose.h>
#include <ros/ros.h>
#define size_of_cell 1

//Constructor
PointCloudMap::PointCloudMap(int map_height_, int map_width_)
{
	this -> map_height = map_height_;
	this -> map_width = map_width_;
}

void PointCloudMap::addToBuffer(int i, int j)
{
	buffer.push_back(std::make_pair(i, j));
}

// 1. count Occupied
void PointCloudMap::countOccupied(const nav_msgs::OccupancyGridConstPtr& map)
{
	int PCLcnt = 0;
	ROS_INFO("map: %d", map->info.height);
	for (size_t i=0; i<map->info.height; i++)
	{
		for (size_t j=0; j<map->info.width; j++)
		{
			if (map->data.at(i*map->info.width + j) == 100) 
			{
				increaseOccupied();
				// 2. add Point that is occupied
				addToBuffer(i, j);
			}
		}
	}
}

// 3. resize pcl with count of occupied
void PointCloudMap::initMap()
{
	cloud -> height = map_height;
	cloud -> width = map_width;
	cloud -> points.resize(occupied_cnt);
	addToPCL();
}

// 4. add point to PCL
void PointCloudMap::addToPCL()
{
	for (size_t i=0; i<cloud->points.size(); i++)
	{
		cloud -> points[i].x = buffer[i].second * size_of_cell + size_of_cell / 2;
		cloud -> points[i].y = buffer[i].first * size_of_cell + size_of_cell / 2;
		cloud -> points[i].z = 0.0;
	}
}

// 5. Draw PCL
pcl::visualization::PCLVisualizer::Ptr PointCloudMap::DrawMap()
{
	pcl::visualization::PCLVisualizer::Ptr viewer(new pcl::visualization::PCLVisualizer ("2D Viewer"));
	viewer -> setBackgroundColor(0,0,0);
	pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> online_cloud_h(cloud, 255, 255, 255);
	viewer->addPointCloud(cloud, online_cloud_h, "online_cloud");
	return viewer;
}

