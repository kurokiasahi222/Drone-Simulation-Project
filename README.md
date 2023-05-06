
# Team-010-25-homework4
Henry Zhao - zhao1057, 
Kinsey Miller - mill8744, 
Ash Kuroki - kurok011, 
Joel Nathe - nathe031

### Project Overview
This project features a frontend written in HTML and JS which communicates with lower-level algorithms written in C++. When it is run, it provides two web-pages: index.html which displays a 3D rendering, and schedule.html which provides a user interface for scheduling trips. The rendering consists of a background modeled after the UMN-TC campus, where various entities are either spawned automatically when the simulation starts or generated at the user’s request. The two main entities are drones and robots, which simulate a ride-sharing environment where drones are delivered by robots to their destinations. 

### How to run
1. Open a Terminal window
1. Enter `cd <path to the folder containing this README>`
1. Compile the code using `make -j`
1. Run  the code using `./build/bin/transit_service 8081 apps/transit_service/web/`
1. Access the simulation at the URL http://127.0.0.1:8081
1. Schedule a new trip at the URL http://127.0.0.1:8081/schedule.html

### Alternative way to run using Docker
link to docker hub: https://hub.docker.com/repository/docker/kurok011/hw4/general 
<br/>
Run following commands on terminal
1. docker pull kurok011/hw4
2. docker run --rm -it -p 80:8081 kurok011/hw4
3. Navigate to localhost

### Simulation
The main focus of this simulation is using drones to deliver robots from one location to another. Each time a trip is scheduled, a robot is spawned, and a nearby drone must fly to that robot and take it to that destination. The drone by itself can fly high above the buildings, so it travels to its passenger in a straight line (i.e. beeline strategy.) But when carrying a robot, the drone may only travel along roads, which makes for more complicated paths. These paths can be calculated using the A*, Dijkstra, or DFS strategy, according to what the user selected when they scheduled a trip. Once the drone and robot arrive at the destination, the drone drops off the robot and is now available to serve other passengers. Aside from the ride-sharing, the simulation also contains a helicopter which travels through the sky towards a random destination, and humans who travel along roads toward random destinations.

### New Feature - Notifications (Observer)
In order to give more comprehensive information to users and make debugging easier for developers, a scrollable text box on the left logs every action taken by every entity. Whenever an entity is instantiated, an observer subscribes to the entity and displays notifications from the entity onto the screen. Not only is this observer pattern a useful feature in and of itself, it also makes it easy for future developers to also route notifications to other destinations if necessary, such as to the console or through HTTP messages to another host. Although we only attach one observer to each entity in this implementation, the entities are still capable of handling multiple observers, which makes this feature open to extension. 

### New Feature - Data Collection (Singleton)
Data collection class using the Singleton design pattern collects and maintains a record of various statistics for each entity. This includes speed and location at different times, total time taken to complete each trip, and total time to reach a robot after it is scheduled. <br/>
This feature, similar to the notification system, is signitifanctly interesting because it simplifies tracking details that may not be apparent by simply observing the entities. Also, it opens the door to statistical analysis in order to research more efficient algorithms for picking up or delivering robots
<br/>
It adds to the existing work by creating a data collection class and using that data collection class inside our Drone and Robot class to collect records. <br/>
We used singleton pattern for this data collection class. This is because singleton is the best suited when we want to log information. Our application should only have a single instance of a data collection class in order to avoid conflicting request for the same resource.
<br/>
To utilize our new data collection class, the schedule.html page features a form located below the map, designed to enable users to conduct experiments within the simulation. The form allows users to select the number of drones and robots required for the simulation, as well as a search strategy. Once the user has specified the relevant parameters and clicked on the "Click to start an experiment" button, the simulation begins automatically, using the specified drones and robots. <br/>
Additionally, a "Export CSV" button is provided, which generates a Comma Separated Values (CSV) file that contains all of the collected data. This file can be downloaded by the user for further analysis and study. Also, we have a python file that analyzes the collected data. 
<br/>
<br/>
<img width="1378" alt="Screen Shot 2023-05-02 at 11 29 44 PM" src="https://media.github.umn.edu/user/18696/files/ec2f7a9e-7198-40dc-bc85-c95b99de46d3">

### Sprint Retrospective
Some parts of the sprint went well, and some could have been better. On the plus side, we worked efficiently as a team and achieved our goals ahead of schedule. There was frequent communication between team members, so that we all knew what the others were doing and did not get in one another’s way. The code that we wrote works as expected. On the other hand, our GitHub repository has not been well-organized. There is no convention for naming branches or commits, and many of them are just groups of unrelated changes without a coherent focus. This would make it difficult to go back and debug our code if we had to. For future sprints, we should aim to not only write working code, but also do it in a way that’s methodical and coherent. For example, having each branch focused on one task, rather than many branches that span many unrelated tasks.

### UML
![HW4](https://media.github.umn.edu/user/18696/files/c0dd1f36-8e32-4d15-a9e9-89dbd0c0a6f0)

### Video presentation
Link to our video presentation and demo [here](https://www.youtube.com/watch?v=SVIainaNuyE).


