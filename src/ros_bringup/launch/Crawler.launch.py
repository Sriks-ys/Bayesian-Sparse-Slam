# Copyright 2022 Open Source Robotics Foundation, Inc.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.actions import IncludeLaunchDescription
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution

from launch_ros.actions import Node


def generate_launch_description():
    # Configure ROS nodes for launch

    # Setup project paths
    pkg_project_bringup = get_package_share_directory('ros_bringup')
    pkg_project_gazebo = get_package_share_directory('ros_gazebo')
    pkg_project_description = get_package_share_directory('robot_description')
    pkg_ros_gz_sim = get_package_share_directory('ros_gz_sim')


    world_file_param = LaunchConfiguration('world_file')

    declare_world_file_param = DeclareLaunchArgument(
        'world_file',
        default_value='Crawler.sdf',
        description='Gazebo world file to load'
    )

    declare_tf_param = DeclareLaunchArgument(
        'tf_frame',
        default_value='odom',
        description='Choose frame to transform line segments: map or odom'
    )

    # Load the SDF file from "description" package
    sdf_file  =  os.path.join(pkg_project_description, 'models', 'Crawler', 'model.sdf')
    with open(sdf_file, 'r') as infp:
        robot_desc = infp.read()



  
    gz_sim = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(pkg_ros_gz_sim, 'launch', 'gz_sim.launch.py')),
        launch_arguments={'gz_args': PathJoinSubstitution([
            pkg_project_gazebo,
            'worlds',
            world_file_param
        ])}.items(),
    )

    
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='both',
        parameters=[
            {'use_sim_time': True},
            {'robot_description': robot_desc}
        ]
    )

    joint_state_publisher = Node(
     package='joint_state_publisher',
     executable='joint_state_publisher',
     name='joint_state_publisher',
     parameters=[{'use_sim_time': True}]
    )

    static_tf_pub_caster = Node(
    package="tf2_ros",
    executable="static_transform_publisher",
    arguments=["0.4", "0", "-0.1", "0", "0", "0", "base_link", "caster"], 
    parameters=[{'use_sim_time':True}]
    )
    
    static_tf_pub_lid = Node(
    package="tf2_ros",
    executable="static_transform_publisher",
    arguments=["0.0", "0", "0.3", "0", "0", "0", "base_link", "Crawler/base_link/LinSense"],
    parameters=[{'use_sim_time':True}]
    )
    
    static_tf_pub_map = Node(
    package="tf2_ros",
    executable="static_transform_publisher",
    arguments=["0", "0", "0", "0", "0", "0", "map", "odom"],
    parameters=[{'use_sim_time':True}]
    )
    
    rviz = Node(
       package='rviz2',
       executable='rviz2',
       condition=IfCondition(LaunchConfiguration('rviz')),
       parameters=[{
        'use_sim_time':True
       }]
    )

    bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        parameters=[{
            'config_file': os.path.join(pkg_project_bringup, 'config', 'ros_bridge.yaml'),
            'qos_overrides./tf_static.publisher.durability': 'volatile'},
            {
                'use_sim_time': True
            }],
        output='screen'
    )

    map_server = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{
            'yaml_filename': os.path.join(pkg_project_bringup, 'maps', '/home/kvothe/finalmap.yaml'),
            'use_sim_time': True
        }],
    )

    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_map',
        output='screen',
        parameters=[{
            'use_sim_time': True,
            'autostart': True,
            'node_names': ['map_server']
        }],
    )
    sparse_sampler = Node(
        package='sensor_management', 
        executable='sparsesampler', 
        parameters=[{'use_sim_time':True}]
    )
    
    sensor_fusion = Node(
        package='sensor_management', 
        executable='fusion', 
        parameters=[{'use_sim_time':True}]
    )

    accumululator = Node(
        package='cppp',
        executable='ScanAccumulator', 
        parameters=[{'use_sim_time': True}]
    )

    preprocess = Node(
        package='cppp', 
        executable='PreprocessNode', 
        parameters=[{
            'use_sim_time': True, 
            'max_range': 5.0
        }]
    )

    scantransform = Node(
        package='cppp',
        executable='ScanTransformer', 
        parameters=[{
            'use_sim_time': True
        }]
    )

    ransac_line_exac = Node(
        package='cppp',
        executable='RansacLineExtractionNode',
        parameters=[{
            'use_sim_time': True
        }]
    )

    inc_line_exac = Node(
        package='cppp',
        executable='IncrementalLineFittingNode',
        parameters=[{
            'use_sim_time': True
        }]
    )

    hough_line_exac = Node(
        package='cppp',
        executable='HoughLineFittingNode',
        parameters=[{
            'use_sim_time': True
        }]
    )

    

    LmmapTransform = Node(
        package='cppp', 
        executable='LandmarkTransformermapNode',
        parameters=[
            {'use_sim_time': True}
        ]
    )

    amcl = Node(
        package='nav2_amcl', 
        executable='amcl',
        parameters=[{
            'use_sim_time': True
        }]
    )
    landmark_graph_viz = Node(
        package='sensor_management',
        executable='linesegmentvisualizer', 
        name='Landmark_viz', 
        parameters=[
            {'use_sim_time':True, 
             'line_topic':'global_landmarks', 
             'pub_topic': "global"}
        ]
    )

    linesec_viz = Node(
        package='sensor_management',
        executable='Linesegviz', 
        name='Linesec_viz', 
        parameters=[
            {'use_sim_time':True, 
             'line_topic':'extracted_lines', 
             'pub_topic': "el"}
        ]
    )
    pose_graph_viz = Node(
        package='sensor_management',
        executable='PoseGraphViz', 
        name='posegraph_viz', 
        parameters=[
            {'use_sim_time':True, 
             'pose_topic':"pose_graph", 
             'pub_topic': "preop"}
        ]
    )
    Eu_landmark_landmark_graph = Node(
        package='soma', 
        executable='EuclidsLandmarkLandmarkGraphNode',
        parameters=[
            {'use_sim_time': True}
        ]
    )

    SWMA_landmark_landmark_graph = Node(
        package='soma', 
        executable='SWMANode',
        parameters=[
            {'use_sim_time': True}
        ]
    )
    Bayes = Node(
        package='soma',
        executable='BayesianLandmarkConstraintNode',
        name = 'Bayes',
        parameters=[{
            'use_sim_time': True
        }]
    )

    graph = Node(
        package='soma', 
        executable='GraphNode',
        parameters=[
            {'use_sim_time': True}
        ]
    ) 
    ograph = Node(
        package='soma', 
        executable='OldGraphNode',
        parameters=[
            {'use_sim_time': True}
        ]
    ) 
    lmlmconsviz = Node(
        package='soma', 
        executable='LandmarkConstraintVisualizer', 
        name= 'Lm_lm_viz',
        parameters=[{
            'use_sim_time': True
        }]
    )

    optimizer = Node(
        package='cppp',
        executable='PoseGraphOptimizer',
        name='optimizer',
        parameters=[{
           'use_sim_time': True,
        }]
     )
    
    Postposegraphviz = Node(
        package='sensor_management',
        executable='PostPoseGraphViz',
        name='postposegraph_viz',
        parameters=[{
            'pose_topic': 'optimized_posegraph',
            'use_sim_time': True,
            'pub_topic': 'postopgraph'
        }]
    )

    Postlandmarkviz = Node(
        package='sensor_management',
        executable='Linesegviz',
        name = 'postlandmarkviz',
        parameters=[{
            'use_sim_time': True,
            'line_topic': 'optimized_landmarks',
            'pub_topic': 'postoplandmarks'
        }]
    )
    return LaunchDescription([
        declare_world_file_param, declare_tf_param, gz_sim,
        DeclareLaunchArgument('rviz', default_value='true',
                              description='Open RViz.'),
        bridge, joint_state_publisher, robot_state_publisher, static_tf_pub_lid, static_tf_pub_caster, 
        static_tf_pub_map, map_server, lifecycle_manager, rviz, sensor_fusion, sparse_sampler, 
        accumululator, preprocess, scantransform, hough_line_exac, linesec_viz, ograph,
        pose_graph_viz, landmark_graph_viz, Bayes, lmlmconsviz, optimizer, Postposegraphviz, Postlandmarkviz
        ]) 
