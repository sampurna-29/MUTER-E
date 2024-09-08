## Introduction

**MUTER - E** (Multi-Terrain Robot - Explorer) is a robotic system designed to navigate complex and challenging terrains using an advanced rocker bogie suspension mechanism. This system is widely known for its stability and ability to overcome obstacles, making it ideal for applications such as surveillance, environmental monitoring, search and rescue, industrial inspections, and agricultural tasks.

The robot is equipped with a range of sensors, including a camera for visual feedback, GPS for location tracking, Wi-Fi for data transmission, and multiple gas sensors for monitoring environmental conditions. These features enable the robot to operate autonomously and transmit critical data to a web-based dashboard for real-time monitoring and analysis.

**Related Publication:** For a detailed description of the design and development of MUTER - E, please refer to our research paper [here](https://iopscience.iop.org/article/10.1088/1757-899X/1295/1/012005/meta).


## Features

### 1. Rocker Bogie Suspension System
The core of the robot’s design is the rocker bogie mechanism, which provides excellent stability and maneuverability on uneven terrains. This design allows the robot to maintain contact with the ground at all times, reducing the risk of tipping and enabling smooth navigation over obstacles.

### 2. Visual and Environmental Sensing
The robot is fitted with an integrated camera for capturing real-time images and videos of its surroundings. This visual sensor enables the robot to perceive its environment, recognize obstacles, and gather data for analysis. In addition, the robot is equipped with various gas sensors (MQ-02, MQ-04, MQ-07) to detect carbon monoxide, methane, smoke, and air quality index (AQI), providing valuable insights into the environment.

### 3. GPS Module
With the GPS module, the robot can accurately determine its position in outdoor environments, aiding in navigation, mapping, and geolocation-based tasks. This feature is critical for applications that require precise positioning, such as search and rescue or environmental monitoring.

### 4. Wi-Fi Module and Internet Connectivity
The Wi-Fi module enables seamless wireless connectivity, allowing the robot to transmit sensor data to the cloud and receive remote commands. This feature supports real-time monitoring, remote control, and data exchange, making it possible to manage the robot's operations from any location.

### 5. Ultrasonic Sensor for Obstacle Detection
The ultrasonic sensor enhances the robot’s ability to detect obstacles by emitting high-frequency sound waves and measuring their reflection times. This data helps the robot avoid collisions and navigate through complex environments safely.

### 6. Data Display on Web-Based Dashboard
The robot’s collected data is transmitted to a user-friendly dashboard, where it is displayed in real-time. This dashboard provides access to visual feeds, sensor readings, and environmental parameters, allowing users to monitor the robot’s performance and make informed decisions.


## Overall Block Diagram

<p align="center">
<img src="https://github.com/user-attachments/assets/12a092b7-6d1f-480b-83ed-fafab729de52" width="100%" alt="block_diagram">
</p>

## Development Stages

### Prototype 1: Initial Concept and Testing
The initial prototype was developed to test the basic functionality of the rocker bogie suspension system and sensor integration. Key features included a basic chassis, initial motor setup, and preliminary testing of the obstacle navigation capabilities using Wi-Fi-based control.

- **Key Components:**
  - Basic rocker bogie suspension setup
  - Wi-Fi module for remote control using a custom-developed mobile application
  - Basic obstacle detection capabilities using ultrasonic sensors

- **Testing and Results:**
  - Successfully navigated basic obstacles and uneven terrains.
  - Conducted initial tests on data transmission and remote control functionalities.
<p align="center">
<img src="https://github.com/user-attachments/assets/731f424e-0b6e-4de4-8818-c444d2986a19" width="60%" alt="prt1.1">
<img src="https://github.com/user-attachments/assets/49fdbe76-c2cb-4bc6-bee7-4d3e8abe3ea1" width="60%" alt="prt1.2">
<img src="https://github.com/user-attachments/assets/effc1570-1e9f-4b53-b0b8-f8152541cf47" width="50%" alt="prt1.3">
</p>

### Prototype 2: Enhanced Mobility and Sensor Integration
The second prototype improved upon the initial design with upgraded components, refined suspension, and enhanced data communication capabilities. This version focused on integrating more advanced sensors, improving the robot's stability, and enhancing control through the development of a dedicated RF-based remote system.

- **Key Upgrades:**
  - Enhanced suspension for better stability and obstacle climbing.
  - Upgraded wheels with better traction for improved maneuverability.
  - Integration of gas sensors for environmental monitoring.
  - Replacement of Wi-Fi control with RF-based remote control for extended range and reliability.

- **Testing and Results:**
  - Enhanced stability on rough terrains and slopes.
  - Successful integration of environmental sensors, allowing for real-time monitoring of air quality.
  - Improved control system with RF remote, offering greater precision and reduced latency.
<p align="center">
<img src="https://github.com/user-attachments/assets/b7690131-3170-47af-9b7f-9d4b34877320" width="60%" alt="prt2.1">
<img src="https://github.com/user-attachments/assets/a659fa33-3ac2-4a4c-b118-df1632ecccfa" width="60%" alt="prt2.2">
</p>

### Final Design: Fully Integrated Multi-Terrain Robot
The final version of MUTER - E incorporates all the previous enhancements and adds a web-based dashboard for real-time monitoring and data visualization. This iteration includes a complete suite of sensors, optimized suspension, and improved data transmission capabilities, making it suitable for various real-world applications.

- **Key Features:**
  - Fully integrated rocker bogie mechanism for superior terrain adaptability.
  - Comprehensive sensor suite including camera, GPS, ultrasonic sensors, and gas detectors.
  - Web-based dashboard providing real-time access to sensor data, environmental monitoring, and robot status.
  - Robust communication system combining RF remote control and Wi-Fi connectivity for flexible operation.

- **Final Testing and Analysis:**
  - Conducted extensive field testing to validate obstacle climbing, stability, and sensor accuracy.
  - Demonstrated capabilities in surveillance, environmental monitoring, and industrial inspections.
  - Successfully transmitted real-time data to the dashboard, enabling detailed analysis and decision-making.
<p align="center">
<img src="https://github.com/user-attachments/assets/7314707c-1e97-49f1-933a-f9a1c92c2f4a" width="60%" alt="final">
<img src="https://github.com/user-attachments/assets/1afb7fc9-5a43-46d8-8dbb-82e717dcd5f1" width="60%" alt="db1">
<img src="https://github.com/user-attachments/assets/77a66c34-be5d-48df-8038-82da4dec5777" width="60%" alt="db2">
</p>


## Applications

- **Surveillance and Security**: Use the robot for patrolling areas, monitoring perimeters, and detecting intrusions in hazardous or restricted environments.
- **Environmental Monitoring**: Monitor air quality, detect gases, and assess environmental conditions in industrial or urban settings to mitigate health risks.
- **Search and Rescue**: Deploy the robot in disaster scenarios to locate survivors and navigate through debris, aiding in efficient and safe rescue missions.
- **Industrial Inspections**: Perform inspections in dangerous or hard-to-reach areas, reducing human risk while maintaining high inspection standards.
- **Agriculture**: Use the robot to monitor crops, assess soil conditions, and optimize resource management for precision farming.
- **Remote Monitoring and Telepresence**: Operate the robot remotely as a telepresence device for exploring and interacting with environments from a distance.


## Future Work

The following enhancements are planned for future development:
- **Autonomous Navigation**: Implement advanced path planning and SLAM algorithms for fully autonomous operations.
- **Enhanced Localization**: Integrate additional sensors such as LiDAR and visual odometry for improved positioning accuracy.
- **Energy Efficiency**: Optimize power management to extend operational time and reduce energy consumption.
- **Swarm Robotics**: Explore the deployment of multiple robots working collaboratively to achieve complex tasks.


Thank you for exploring MUTER - E! We welcome contributions and ideas for future enhancements.
