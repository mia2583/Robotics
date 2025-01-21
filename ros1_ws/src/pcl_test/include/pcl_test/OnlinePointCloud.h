#include <nav_msgs/OccupancyGrid.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <vector>
#include <tf/tf.h>

#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>


class OnlinePointCloud
{
	private:
		int map_height;
		int map_width;
		int occupied_cnt = 0;
		std::vector<std::pair<int, int>> buffer;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
		// this should be form of vector3
		tf::Vector3 T_om;
		tf::Vector3 T_map;
		std::vector<int> error;
		std::vector<float> color;
		float colorRange[2] = {1000, 0};
		
	public:
		OnlinePointCloud(int map_height_, int map_width_);
		void countOccupied(const nav_msgs::OccupancyGridConstPtr& map);
		void addToBuffer(int i, int j);
		void initMap();
		void addToPCL();
		void findBestMatch(pcl::KdTreeFLANN<pcl::PointXYZ>::Ptr kdtree);
		cv::Mat drawErrorMap();
		
		
		int GetHeight() { return map_height; }
		int GetWidth() { return map_width; }
		int GetSize() { return cloud -> size(); }
		int GetOccupied() { return occupied_cnt; }
		void increaseOccupied() { occupied_cnt += 1; }
		void SetOccupied(int i) { occupied_cnt = i; }
		int GetPointX(float x) { return cloud->points[x].x; }
		int GetPointY(float y) { return cloud->points[y].y; }
		void SetTom(float x, float y, float z) { T_om = tf::Vector3(x, y, z); }
		void SetTmap(float x, float y, float z) { T_map = tf::Vector3(x, y, z); }
};


