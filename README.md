# Autonomous NOC
# Optimization using the Deep Q-Learning Algorithm

**Pseudo code for Table 1.O:**

The first requirement of the problem statement was to write a pseudocode to calculate average latency and bandwidth using the simulator-provided output.The provided pseudocode calculates the average latency and average bandwidth based on user input values for CPU arbitration rate and IO arbitration rate. It first reads these input values and then fetches the corresponding arbitration rates using an API call. If either of the input values is zero, it outputs "Invalid Input." Otherwise, it calculates the read and write latencies, average latency, CPU and IO bandwidths, and finally outputs the average latency and average bandwidth. The code effectively handles the calculation and validation of input values to derive meaningful metrics for latency and bandwidth.

**How did I arrive at this model?**

Firstly, I have started with the basic Q-learning optimization model. This model is a simple implementation of how AI/ML can be used to optimize Network-On-Chip architectures. This model assumes the required parameters for optimality and does not use any of the APIs.

**The details of the model are listed below:**

NOC Parameters and Transaction Table: The code defines parameters such as memory latency, maximum bandwidth, and a transaction table containing timestamped transactions.

**Q-learning Parameters:** It sets up parameters for Q-learning, including the number of states and actions, learning rate (alpha), discount factor (gamma), and the number of training episodes.

**Simulation of NOC Transactions:** The simulateNOC() function iterates over transactions in the transaction table, simulating memory access and updating metrics such as latency, bandwidth, buffer occupancy, and throttling frequency.

**Calculation of Average Metrics:** After simulating transactions, the code calculates the average latency, bandwidth, buffer occupancy, and throttling frequency.

**Optimization Check:** It checks whether the calculated metrics meet the optimization criteria defined by minimum latency, bandwidth, buffer occupancy, and throttling frequency thresholds.

**Action Selection:** In the main loop, the code selects actions using an epsilon-greedy policy based on Q-values.

**Q-value Update:** It updates Q-values using the Bellman equation, which requires implementing the calculation of the next state.

**Optimization Status:** Finally, the code outputs whether optimization is achieved based on the defined criteria.

**Testing: The code has been tested on Example Table 1.0 and some arbitrary inputs to see its coverage.**

Moving forward, This basic Q-learning model is a good solution for smaller action spaces, but as the complexity increases, this model is not scalable. Upon research, I learned that DQN utilizes a separate target network to stabilize training by decoupling target Q-value estimation from the online Q-network updates. This helps prevent overestimation bias and improves training stability, which is absent in this code. Q-learning with a Q-table can struggle to generalize across similar states, resulting in inefficient learning. DQN leverages neural networks to generalize Q-values across states, enabling more effective learning from similar experiences.

And in today's scenario, autonomy has become the basic requirement of every system, so an idea popped up to make an autonomous NOC. This NOC will be able to handle dynamic workloads. Autonomous NOC management can scale efficiently to handle the increasing complexity and workload demands without requiring constant human intervention. Autonomous management techniques can dynamically adjust power and performance settings based on workload characteristics, leading to improved energy efficiency. With the rapid growth of real-time and mission-critical applications, autonomous NOC management can dynamically optimize network configurations to meet stringent latency and throughput requirements.

Seeing all the advantages of making autonomous NOC, as we know, DQN is superior to Q-learning for autonomous NOC management due to its ability to handle large state spaces efficiently, generalize across similar states, leverage neural networks for function approximation, and incorporate experience replay and target networks for stable learning and improved performance. 

This way, I arrived at my solution for an autonomous NOC.

You can simulate this code with any C++ compiler.

**DQN pseudocode :**

This pseudocode has a basic implementation of how the DQN algorithm can be used to get an autonomous NOC.This code outlines a typical training loop for a deep Q-network (DQN) used in autonomous network-on-chip (NoC) control. It iterates through episodes, interacting with the environment, collecting experiences, updating the Q-network, and adjusting the exploration rate. The training loop terminates upon meeting certain conditions, after which the final trained Q-network is used for autonomous control.

**Future possibilities:**

This code can be converted to actual code for model generation by generating an environment in GEM5 and by using proper data fetching through the API. 

Download Gem5 from the official site using: git clone https://github.com/gem5/gem5.git

Build the gem5 according to the official gem5 documentation.

Now copy the env folder inside the gem5 folder and the user folder inside the gem5 configs folder.

How to use it?

You can use this simulator by importing the simulator.py file, which includes functions for apis, and running the Gem5 environment contained in the Gem5 folder.

add soc.py to config/user/and add simulator.py to env/

**Thank you!!**
 
 


