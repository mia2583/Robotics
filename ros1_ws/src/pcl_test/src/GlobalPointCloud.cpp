#include "pcl_test/GlobalPointCloud.h"
#include <geometry_msgs/Pose.h>
#include <ros/ros.h>
#define size_of_cell 1

// 0. Constructor
GlobalPointCloud::GlobalPointCloud(int map_height_, int map_width_)
{
	this -> map_height = map_height_;
	this -> map_width = map_width_;
}

// 1. count Occupied and add points to buffer that is occupied.
void GlobalPointCloud::countOccupied(const nav_msgs::OccupancyGridConstPtr& map)
{
	int PCLcnt = 0;
	SetOccupied(0);
	for (size_t i=0; i<map->info.height; i++)
	{
		for (size_t j=0; j<map->info.width; j++)
		{
			if (map->data.at(i*map->info.width + j) == 100) 
			{
				increaseOccupied();
				addToBuffer(i, j);
			}
		}
	}
}

void GlobalPointCloud::addToBuffer(int i, int j)
{
	buffer.push_back(std::make_pair(i, j));
}

// 2. resize pcl with count of occupied and add each point to Cloud
void GlobalPointCloud::initMap()
{
	cloud -> height = map_height;
	cloud -> width = map_width;
	cloud -> points.resize(occupied_cnt);
	addToPCL();
}

void GlobalPointCloud::addToPCL()
{
	for (size_t i=0; i<cloud->points.size(); i++)
	{
		cloud -> points[i].x = buffer[i].second * size_of_cell + size_of_cell / 2;
		cloud -> points[i].y = buffer[i].first * size_of_cell + size_of_cell / 2;
		cloud -> points[i].z = 0.0;
		tf::Vector3 result = tf::Vector3(cloud -> points[i].x, cloud -> points[i].y, cloud -> points[i].z);
		result = T_gm * result;
		cloud -> points[i].x = result.x();
		cloud -> points[i].y = result.y();
		cloud -> points[i].z = result.z();
		// origin in global coordinate* global point
		/*cloud -> points[i].x = T_gm.x * cloud -> points[i].x;
		cloud -> points[i].y = T_gm.y * cloud -> points[i].y;
		cloud -> points[i].z = T_gm.z * cloud -> points[i].z;*/
	}
}

void GlobalPointCloud::assignKdtree(pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree)
{
	kdtree -> setInputCloud(cloud);
}
