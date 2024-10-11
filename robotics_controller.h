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

// Get torque function
double get_torque(double theta, double dtheta, double t, double num_e, double w)
{
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

// Function to simulate and record data
void simulate_and_save(double num_e, const std::string &weight_label)
{
    double t = 0.0;
    double theta = 0.0;
    double dtheta = 0.0;
    double w = 13; // Frequency parameter

    // Prepare filename
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
        double torque = get_torque(theta, dtheta, t, num_e, w);
        double theta_d = desiredTrajectory(t);

        // Record data to file
        outfile << t << "\t" << torque << "\t" << theta_d << std::endl;

        // Update time
        t += TIME_STEP;
    }

    outfile.close();
}
