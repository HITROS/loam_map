# LoamMap  
    功能描述:将loam运行时输出的地图消息转化为二维占据栅格地图并加以保存  

    工作流程：
    <div align=center><img src="https://github.com/HITROS/LoamMap/tree/master/src/Loam使用流程图.png" width="300" height="450" /></div>
## 准备工作
   1、安装ocotomap
```
   sudo apt-get install ros-kinetic-octomap-ros  
   sudo apt-get install ros-kinetic-octomap-msgs  
   sudo apt-get install ros-kinetic-octomap-server  
   sudo apt-get install ros-kinetic-octomap-rviz-plugins   
```  
   2、安装loam  
```
   cd catkin_ws/src  
   git clone https://github.com/daobilige-su/loam_velodyne.git  
   cd ..  
   catkin_make  
```  
   注意：这里直接编译可能会提示缺少loam.test.in文件，所以在编译之前/loam_velodyne目录下建立tests文件夹，在/tests文件夹下新建一个loam.test.in空白文件  

   3、确保你下载并安装了omtb，或下载相关数据集
## 下载安装
```
   cd catkin_ws/src  
   git clone https://github.com/HITROS/loam_map.git  
   cd ..  
   catkin_make  
```
## 启动
   可以运行数据集或在omtb中实验  
   1、运行数据集    
```
    roslaunch LoamMap octo_loam_dataset.launch  
```
    注意将launch文件中包含的文件路径改为你计算机上的路径
   2、运行omtb  
```
    roslaunch LoamMap octo_loam_omtb.launch  
```
    注意将launch文件中包含的文件路径改为你计算机上的路径  
## 地图保存
```
    mkdir ~/map  
    rosrun map_server map_saver map:=/projected_map -f ~/map/mymap
```
    

