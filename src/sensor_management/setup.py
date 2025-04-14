from setuptools import find_packages, setup

package_name = 'sensor_management'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='kvothe',
    maintainer_email='kvothe@todo.todo',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "fusion=sensor_management.fusion:main", 
            "sparsesampler=sensor_management.sparsesampler:main",
            "linesegmentvisualizer=sensor_management.linesegmentvisualizer:main", 
            "PoseGraphViz = sensor_management.PoseGraphViz:main",
            "LandmarkLandmarkVisualizationNode = sensor_management.LandmarkLandmarkVisualizationNode:main",
            "Linesegviz = sensor_management.linesegviz:main",
            "PostPoseGraphViz = sensor_management.PostPoseGraphViz:main"

        ],
    },
)
