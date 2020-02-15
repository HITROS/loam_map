/**
*
* 函数功能:读取pcl点云文件并发布到topic上去
*
*
* maker: crp 
* data: 2016-6-8
*/
// 参考资料:https://blog.csdn.net/Travis_X/article/details/89374013
// 参考资料:https://blog.csdn.net/crp997576280/article/details/74605766
// 参考资料:https://blog.csdn.net/sylin211/article/details/93743724

#include<iostream>
#include<string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>

#include<ros/ros.h>  
#include<pcl/point_cloud.h>  
#include<pcl_conversions/pcl_conversions.h>  
#include<sensor_msgs/PointCloud2.h>  
#include<pcl/io/pcd_io.h>
#include <Eigen/Dense>
#include <pcl/common/transforms.h>

using namespace std;


void PointCloudModifyCallback(const sensor_msgs::PointCloud2& pt);

pcl::PointCloud<pcl::PointXYZ> received;    
pcl::PointCloud<pcl::PointXYZ> modified; 
sensor_msgs::PointCloud2 output;

int main (int argc, char **argv)  
{  
	std::string topic,path,frame_id;
    int hz=5;

	ros::init (argc, argv, "publish_pointcloud");  
	ros::NodeHandle nh;  

    //nh.param<std::string>("path", path, "/home/zs/catkin_ws/src/publish_pointcloud/data/test.pcd");
	nh.param<std::string>("frame_id", frame_id, "camera");
	nh.param<std::string>("topic", topic, "/pointcloud/output");
    nh.param<int>("hz", hz, 5);

    ros::Subscriber sub = nh.subscribe("/laser_cloud_surround", 1000, PointCloudModifyCallback);
  	ros::Publisher pointmodified_pub = nh.advertise<sensor_msgs::PointCloud2> ("/laser_cloud_surround_modify", 10);  
	ros::Rate loop_rate(10); 
	


	while (ros::ok())  
	{  
	    pointmodified_pub.publish(output); 
		ros::spinOnce();  
		loop_rate.sleep();  
	}  
	return 0;  
}  

void PointCloudModifyCallback(const sensor_msgs::PointCloud2& pt)
{
	pcl::fromROSMsg (pt, received);
    //Eigen::Affine3f transform_2 = Eigen::Affine3f::Identity();
	//transform_2.rotate(Eigen::AngleAxisf(1.570795, Eigen::Vector3f::UnitX()));
	//pcl::transformPointCloud(received, modified, transform_2);
	pcl::PointCloud<pcl::PointXYZ> modified = received;
	int number = received.points.size();
	for (int i =0;i<number;i++)
	{
		modified.points[i].x = received.points[i].x ;
		modified.points[i].z = received.points[i].y ;
		modified.points[i].y = received.points[i].z ;
	}
    
	pcl::toROSMsg(modified, output);
}