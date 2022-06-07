# Data Structures and Algorithms Project
## Simulating Cargo Assignment, Loading, and Delivery.

The goal of this project is to simulate the cargo delivery process in the most efficient and profitable way possible for a shipping company, and then calculate delivery statistics at the end of the simulation, using the knowledge accumulated in the Data Structures and Algorithms (CMPN102) course. 

Cargo and trucks can be categorized into 3 types: Normal, Special, and VIP. Each of which is dealt with differently during the simulation, as they have different priorities (VIP, then special, then normal). Input for the simulation is received from an input file, which contains all of the supported events (cargo preparation, cargo cancellation, promotion), as well as other parameters, such as: truck maintenance and checkup durations, maximum waiting time for cargos, number of deliveries and distance moved before checkup, and time before auto promotions. 

> Project Objectives:  

1. Learn How To Integrate VisualStudio and GitHub. 
2. Writing a complete object oriented C++ program that performs a non-trivial task.
3. Displaying the capability of choosing the most suitable data structures for different tasks.
4. Working effectively in a team.


> Simulation Steps:

1. Enter the name of the input file.
2. Enter the name of the output file (which will contain the final statistics).
3. Enter the simulation mode (Interactive, Step-by-step, Sleep).
4. The simulation will now begin, when a truck is ready to be filled with cargo, it will start being loaded.
5. When any loading truck is ready to move, it will start the delivery.
6. The truck will deliver all of the cargo it is carrying in the order of their distances from the company.
7. Delivery failures might occur in this stage. If that occurs, the truck will return to the company and empty its stored cargo.
8. Once a truck finishes its delivery, it will return to the company.
9. If the truck has finished a large number of journeys, it will move to checkup. If its calculated total distance exceeds a certain value, it will move to maintenance.
10. Trucks can be taken from maintenance if needed, but their speeds will be reduced by a factor of 2 for the rest of the simulation.
11. After all the cargo has been delivered, output statistics will be written to the output file.
12. Open the output file, and analyze the delivery statistics to see how well the company has performed the delivery process.
