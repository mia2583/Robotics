#include "pcl_test/OnlinePointCloud.h"
#include <geometry_msgs/Pose.h>
#include <std_msgs/String.h>
#include <ros/ros.h>
#define size_of_cell 1

// 0. Constructor
OnlinePointCloud::OnlinePointCloud(int map_height_, int map_width_)
{
	this -> map_height = map_height_;
	this -> map_width = map_width_;
}

// 1. count Occupied and add points to buffer that is occupied.
void OnlinePointCloud::countOccupied(const nav_msgs::OccupancyGridConstPtr& map)
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

void OnlinePointCloud::addToBuffer(int i, int j)
{
	buffer.push_back(std::make_pair(i, j));
}

// 2. resize pcl with count of occupied and add each point to Cloud
void OnlinePointCloud::initMap()
{
	cloud -> height = map_height;
	cloud -> width = map_width;
	cloud -> points.resize(occupied_cnt);
	addToPCL();
}

void OnlinePointCloud::addToPCL()
{
	for (size_t i=0; i<cloud->points.size(); i++)
	{
		cloud -> points[i].x = buffer[i].second * size_of_cell + size_of_cell / 2;
		cloud -> points[i].y = buffer[i].first * size_of_cell + size_of_cell / 2;
		cloud -> points[i].z = 0.0;
		if(i==0) ROS_INFO("before : %lf", cloud->points[i].x);
		tf::Vector3 result = tf::Vector3(cloud -> points[i].x, cloud -> points[i].y, cloud -> points[i].z);
		result = T_map * T_om * result;
		// online_map_poses * origin in online coordinate * onlineMap point
		cloud -> points[i].x = result.x();
		cloud -> points[i].y = result.y();
		cloud -> points[i].z = result.z();
		/*cloud -> points[i].x = T_map.x() * T_om.x() * cloud -> points[i].x;
		cloud -> points[i].y = T_map.y() * T_om.y() * cloud -> points[i].y;
		cloud -> points[i].z = T_map.z() * T_om.z() * cloud -> points[i].z;*/
		// tf.vector3 ... something structure
		if(i==0) ROS_INFO("after : %lf", cloud->points[i].x);
	}
	//ROS_INFO("tmap : %lf", T_map.x());
	 
}

void OnlinePointCloud::findBestMatch(pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree)
{
	for (size_t i = 0; i < cloud->size(); ++i)
  	{
    		std::vector<int> nn_indices;
    		std::vector<float> nn_dists;
  
    		if ( kdtree -> nearestKSearch(cloud->points[i], 1, nn_indices, nn_dists) > 0)
    		{
    			//error.push_back(cloud->points[i]);
    			error.push_back(cloud->points[i].y*map_width + cloud->points[i].x);
    			color.push_back(nn_dists[0]);
      			//error.push_back(std::make_pair(cloud->points[i], nn_dists[0]));
      			if (nn_dists[0] > colorRange[1]) colorRange[1] = nn_dists[0];
      			else if (nn_dists[0] < colorRange[0]) colorRange[0] = nn_dists[0];
		}
	}
	ROS_INFO("error: %lf", color[0]);

	
}

cv::Mat OnlinePointCloud::drawErrorMap()
{
	cv::Mat im(map_height, map_width, CV_8UC1); 
	for (size_t i=0; i < map_height*map_width; i++)
	{
    		if (std::find(error.begin(), error.end(), i) != error.end() )
        	{
            		im.data[i] = 255;
        	} else {
        		im.data[i] = 0;
      		}
	}
	return im;
}
