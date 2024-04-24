#include <bits/stdc++.h>

using namespace std;

// Define NOC Parameters
const int memory_latency = 10;
const double max_bandwidth = 0.0005;
const double min_latency = 10;
const double buffer_occupancy_threshold = 0.9;
const double throttling_frequency_threshold = 0.05;
const double epsilon = 0.1;
int f = 0;

// Define Transaction Table
vector<vector<string>> transaction_table = {
    {"0", "Rd", "Addr1", "00000000"},
    {"2", "Wr", "Addr2", "hxxxxxxxx"},
    {"4", "Wr", "Addr3", "hyyyyyyyy"},
    {"10", "Data", "Addr1", "hzzzzzzzz"},
};

// Q-learning Parameters
const int num_states = 100;
const int num_actions = 4;
const double alpha = 0.1;
const double gamma = 0.9;
const int num_episodes = 1000;

// Q-table
vector<vector<double>> Q(num_states, vector<double>(num_actions, 0));

// Function to convert timestamp string to integer
int toInt(const string& str) {
    try {
        return stoi(str);
    } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << e.what() << endl;
        return -1; // Return an error code
    } catch (const out_of_range& e) {
        cerr << "Out of range error: " << e.what() << endl;
        return -1; // Return an error code
    }
}

// Function to simulate NOC transactions
int simulateNOC() {
    double total_latency = 0, total_bandwidth = 0, total_buffer_occupancy = 0;
    int num_transactions = 0, num_throttling_cycles = 0;

//Adressing issues related to Invalid timestamp
    for (const auto& transaction : transaction_table) {
        int timestamp = toInt(transaction[0]);
        if (timestamp == -1) {
            cerr << "Error: Invalid timestamp encountered." << endl;
            return -1;
        }
        string txn_type = transaction[1];
        
        // Process Transactions
        if (txn_type == "Rd" || txn_type == "Wr" || txn_type == "Data") {
            int memory_completion_cycle = timestamp + memory_latency;
            total_latency += memory_latency;
            total_bandwidth += 1.0 / (memory_completion_cycle - timestamp);
        }

        total_buffer_occupancy += 1.0;

        if ((rand() % 100) < 5) {
            num_throttling_cycles++;
        }

        num_transactions++;
    }

//calculating new NOC parameters
    double avg_latency = total_latency / num_transactions;
    double avg_bandwidth = total_bandwidth / num_transactions;
    double avg_buffer_occupancy = total_buffer_occupancy / num_transactions;
    double throttling_frequency = (double)num_throttling_cycles / num_transactions;

// Checking conditions for optimality are matched
    if (avg_latency <= min_latency &&
        avg_bandwidth >= 0.95 * max_bandwidth &&
        avg_buffer_occupancy >= buffer_occupancy_threshold &&
        throttling_frequency <= throttling_frequency_threshold) {
        f = 1;
    } 
    else 
        f = 0;    
  return f;
}

// Function to choose action epsilon-greedily
int chooseAction(int state) {
    if ((double)rand() / RAND_MAX < epsilon) {
        return rand() % num_actions;
    } else {
        return distance(Q[state].begin(), max_element(Q[state].begin(), Q[state].end()));
    }
}

// Function to update Q-value based on the Bellman equation
void updateQValue(int state, int action, int next_state, double reward) {
    Q[state][action] += alpha * (reward + gamma * (*max_element(Q[next_state].begin(), Q[next_state].end())) - Q[state][action]);
}

// Function to convert latency to a state index
int latencyToState(double latency) {
    return static_cast<int>(latency);
}

int main() {
    bool optimization_achieved = false;
    
    for (int episode = 0; episode < num_episodes; ++episode) {
        int result = simulateNOC();
        if (result == -1) {
            cerr << "Error occurred during simulation. Exiting." << endl;
            return -1;
        }

        double latency = 10; // Placeholder value, you need to calculate latency

        int state = latencyToState(latency);
        int action = chooseAction(state);

        double reward = 1.0 / (min_latency - latency);
        // updateQValue(state, action, next_state, reward); // You need to implement next_state calculation

        if (result == 1) {
            optimization_achieved = true;
            break;
        }
    }

    if (optimization_achieved) {
        cout << "Optimization achieved" << endl;
    } else {
        cout << "Optimization not achieved" << endl;
    }

    return 0;
}
