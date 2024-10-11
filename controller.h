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
double get_torque(double theta, double dtheta, double t);
double desiredTrajectory(double t);
void simulate_and_save(double num_e, const std::string &weight_label);
void run_simulation(const std::string &weight_label);

// Get torque function, used in your main logic
double get_torque(double theta, double dtheta, double t)
{
    double num_e = 4; // default value (you can change this if needed)
    double w = 13;    // default frequency (adjustable)

    if (theta0 == 0)
    {
        theta0 = theta;
    }

    double tau = num_e * sin(w * t);
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

    // Run simulation for 70 seconds
    while (t <= TIME_LIMIT)
    {
        // Calculate torque and desired trajectory
        double torque = get_torque(theta, dtheta, t);
        double theta_d = desiredTrajectory(t);

        // Record data to file
        outfile << t << "\t" << torque << "\t" << theta_d << std::endl;

        // Update time
        t += TIME_STEP;
    }

    outfile.close();
}

// Function to run the simulation for multiple num_e values
void run_simulation(const std::string &weight_label)
{
    // Loop over num_e values from 3 to 15
    for (double num_e = 3.0; num_e <= 15.0; )
    {
        // Call simulation and save function for each num_e value
        simulate_and_save(num_e, weight_label);

        // Increment num_e according to the intervals
        if (num_e < 8.0)
        {
            num_e += 0.5; // Increment by 0.5 until 8
        }
        else
        {
            num_e += 1.0; // Increment by 1.0 after 8
        }
    }

    std::cout << "Simulation completed and data saved." << std::endl;
}