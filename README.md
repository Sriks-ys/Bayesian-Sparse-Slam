# Bayesian-Sparse-Slam
This is Sparse SLAM project using Naive Bayes assumption for landmark-landmark constraint. 
> Note This Branch uses Naive Bayes Approach to Construct landmark-landmark constraints. To run the benchmark Soft Manhattan World assumption swap Bayes (Line 345) in the LaunchDescription of the [Crawler.launch.py](https://github.com/Sriks-ys/Bayesian-Sparse-Slam/blob/main/src/ros_bringup/launch/Crawler.launch.py) with the node variable SWMA_landmark_landmark_graph
## Abstract
This literature identifies a research gap in the domain of Sparse SLAM. Sparsity referrers to lack of abundant ranging data that traditional SLAM algorithms rely on, this literature proposes and SLAM framework that utilizes only four range sensing data for map construction. This work aims to identify this research gap. We propose a novel Pose-Graph-Optimization (PGO) algorithm, benefitted by a naïve bayes approach to construct landmark-landmark constraints, which has been found to boost the stability of the optimization process. The basis for the computation of the said landmark-landmark constraints exists in the monotonously increasing certainty in the relative positions of the landmarks as they are progressively observed from multiple pose locations. This behaviour arises from the common error sources that disrupts the pose-pose and pose-landmark constraints. The proposed algorithm was tested in Gazebo Ignition Physics simulation environment within ROS2 humble framework. The performance of the algorithm was evaluated in Intersection Over Union (IoU) and Accuracy. To highlight the efficiency of this method of constructing landmark-landmark constraints it was tested against SoMaSLAM, the results suggest superior performance by the proposed Approach. This works aims to reduce costs invested in high-tech range sensing, while promising the same level of performance as the Non-sparse SLAM algorithms.

## System Setup
The proposed system was developed in Ubuntu 22.04 operating system, using ROS2 humble and gazebo ignition fortress. Ros2 humble was installed using debian package. 

Ros humble desktop version for Ubunut 20.04 installation: 
[ROS installation](https://docs.ros.org/en/humble/Installation/Ubuntu-Install-Debs.html)

Ignition fortress was installation: 
[Ignition installation](https://gazebosim.org/docs/fortress/install_ubuntu/)

> Note: Fortress was chosen for its compatiblity with Humble. [Refer here](https://gazebosim.org/docs/fortress/ros_installation/) for chosing appropriate version of Ignition for a different Ros distribution. 

## Packages Installation

Most of the packages used for simulation are by default installed along with ROS, some of the packages have been additionally installed to aid the development process. 

Addition Ros packages can be installed with this command. 
```
sudo apt install ros-humble-gazebo-ros-pkgs ros-humble-ros-ign-bridge ros-humble-slam-toolbox 
sudo apt install ros-humble-nav2-bringup ros-humble-sdformat-urdf ros-humble-tf-transformations ros-humble-tf-tools
```

Additional python packages can installed with the following commands.
```
sudo apt install python3-colcon-common-extensions python3-pip
pip install filterpy scikit-learn scipy
```

[GTSAM](https://github.com/borglab/gtsam) has been used for optimization process. Note install this package from source, the link attached has the necessary guide for installation. 

## To run the program
Clone the directory into your local system after making the necessary installation. Source the ros global and workspace installation. 

After installation modify the [CMAKEList.txt](https://github.com/Sriks-ys/Bayesian-Sparse-Slam/blob/main/src/cppp/CMakeLists.txt) to point to the directory the gtsam installation. 

Build the workspace in the workspace directory using 
```
colcon build
```
Run the launch file 
```
ros2 launch ros_bringup Crawler.launch.py
```

Run the commands ```rviz2``` and ```rqt``` for debugging processes. 
Configure Rviz with necessary displays. recommend using ```filter by topics```
Custom message were created in the [messages](https://github.com/Sriks-ys/Bayesian-Sparse-Slam/blob/main/src/messages/msg), these messages types do not have an Rviz display. To view these message types, nodes have been created which publish these types of messages as Marker array for visualization in Rviz 

Kindly refer to this [Crawler.launch.py](https://github.com/Sriks-ys/Bayesian-Sparse-Slam/blob/main/src/ros_bringup/launch/Crawler.launch.py)for details about all the nodes being used simulation. Many nodes have been created during the development but are not used in the final implementation, these nodes were created on an experimental basis. These nodes were dropped out implementation due to reasons such as incompatibility with pipeline and insufficient. 
> Kindly cite the source before usage. 

