#include "ros/ros.h"
#include "std_msgs/String.h"
#include <nav_msgs/OccupancyGrid.h>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>

cv::Mat mapToMat(const nav_msgs::OccupancyGridConstPtr& map)
{
  cv::Mat im(map->info.height, map->info.width, CV_8UC1);
  for (size_t i=0; i < map->info.height*map->info.width; i++)
    {
        if (map->data.at(i) == 0)
        {
            im.data[i] = 0;
        }
        else
        {
            if(map->data.at(i) == 100)
            {
                im.data[i] = 255;
            }
            else
            {
                im.data[i] = 100;
            }
        }
    }
    return im;
}

/*void chatterCallback_test(const nav_msgs::OccupancyGridConstPtr& msg)
{
   ROS_INFO("Received a %d X %d map @ %.3f m/pix\n", msg->info.width, msg->info.height, msg->info.resolution);
   ROS_INFO("[%d, %d] in map[0][1]", msg->data[1]);
}*/

void chatterCallback_online(const nav_msgs::OccupancyGridConstPtr& map)
{
  cv::Mat im = mapToMat(map);
  cv::imwrite("online_map.jpg", im);
  ROS_INFO("done online");
}

void chatterCallback_global(const nav_msgs::OccupancyGridConstPtr& map)
{
  cv::Mat im = mapToMat(map);
  cv::imwrite("global_map.jpg", im);
  ROS_INFO("done global");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;

  ros::Subscriber sub1 = n.subscribe("/lidar_deloc_recovery/online_map", 1000, chatterCallback_online);
  ros::Subscriber sub2 = n.subscribe("/map", 1000, chatterCallback_global);
  
  ros::spin();

  return 0;
}

