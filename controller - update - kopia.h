#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

// Constants for simulation
double theta0 = 0;
const double TIME_LIMIT = 70.0; // in seconds
const double TIME_STEP = 0.01;  // time step for recording data (e.g., 100 Hz)

// Function prototypes
double get_torque(double theta, double dtheta, double t, double num_e, double w);
double desiredTrajectory(double t);
void simulate_and_save(double num_e, const std::string &weight_label);
void run_simulation(const std::string &weight_label);

// Get torque function, used in your main logic
double get_torque(double theta, double dtheta, double t, double num_e, double w)
{
    if (theta0 == 0)
    {
        theta0 = theta;
    }

    double tau = num_e * sin(w * t);  // Using num_e in the torque calculation
    return tau;
}

// Desired trajectory function
double desiredTrajectory(double t)
{
    double theta_d = 2 * sin(3.6 * t) + 1 * sin(5 * t) + theta0;
    return theta_d;
}

// Function to simulate and record data for a single num_e value
void simulate_and_save(double num_e, const std::string &weight_label)
{
    double t = 0.0;
    double theta = 0.0;
    double dtheta = 0.0;
    double w = 13; // Frequency parameter

    // Prepare filename based on num_e and weight_label
    std::string filename = "data_" + weight_label + "_num_e_" + std::to_string(num_e) + ".txt";
    std::ofstream outfile(filename);

    // Check if the file was opened successfully
    if (!outfile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::cout << "Saving data for num_e = " << num_e << " to: " << filename << std::endl; // Confirmation of file saving

    // Run simulation for 70 seconds
    while (t <= TIME_LIMIT)
    {
        // Calculate torque and desired trajectory
        double torque = get_torque(theta, dtheta, t, num_e, w);  // Pass num_e explicitly here
        double theta_d = desiredTrajectory(t);

        // Record data to file
        outfile << t << "\t" << torque << "\t" << theta_d << std::endl;

        // Update time
        t += TIME_STEP;
    }

    outfile.close();
}

// Function to run the simulation for multiple num_e values, saving after each 70-second run
void run_simulation(const std::string &weight_label)
{
    // Loop over num_e values from 3 to 15
    for (double num_e = 3.0; num_e <= 15.0; )
    {
        std::cout << "Running simulation for num_e = " << num_e << std::endl;

        // Simulate and save data for the current num_e value
        simulate_and_save(num_e, weight_label);  // Save results for this num_e

        // Increment num_e according to the intervals
        if (num_e < 8.0)
        {
            num_e += 0.5; // Increment by 0.5 until 8
        }
        else
        {
            num_e += 1.0; // Increment by 1.0 after 8
        }

        std::cout << "Completed simulation for num_e = " << num_e << std::endl;
    }

    std::cout << "All simulations completed and data saved." << std::endl;
}
