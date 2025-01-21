#include <nav_msgs/OccupancyGrid.h>
#include <pcl/point_cloud.h>
#include <pcl/point_representation.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <vector>
#include <tf/tf.h>


class PointCloudMap
{
	private:
		int map_height;
		int map_width;
		int occupied_cnt = 0;
		std::vector<std::pair<int, int>> buffer;
		pcl::PointCloud<pcl::PointXYZ>::Ptr cloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
		pcl::PointCloud<pcl::PointXYZ>::Ptr globalCloud = pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
		std::vector<float> error;
		
	public:
		PointCloudMap(int map_height_, int map_width_);
		void countOccupied(const nav_msgs::OccupancyGridConstPtr& map);
		void addToBuffer(int i, int j);
		void initMap();
		void addToPCL();
		pcl::visualization::PCLVisualizer::Ptr DrawMap();
		
		
		int GetHeight() { return map_height; }
		int GetWidth() { return map_width; }
		int GetOccupied() { return occupied_cnt; }
		void increaseOccupied() { occupied_cnt += 1; }
		int GetPointX(int x) { return cloud->points[x].x; }
		int GetPointY(int y) { return cloud->points[y].y; }		
};
