from setuptools import find_packages, setup

package_name = 'soma'

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
            'LineSegmentAssociation = soma.LineSegmentAssociation:main', 
            'PoseGraphNode = soma.PoseGraphNode:main', 
            'EuclidsLandmarkLandmarkGraphNode = soma.EuclidsLandmarkLandmarkGraphNode:main', 
            'SWMANode = soma.SWMANode:main',
            "GraphNode = soma.GraphNode:main", 
            "OldGraphNode = soma.OldGraphNode:main",
            "PostProcessingNode = soma.PostProcessingNode:main",
            "BayesianLandmarkConstraintNode = soma.BayesianLandmarkConstraintNode:main", 
            "LandmarkConstraintVisualizer = soma.LandmarkConstraintVisualizer:main",
            "LandmarkMapGenerator = soma.LandmarkMapGenerator:main"
        ],
    },
)
