#include "robotics_controller.h"

int main()
{
    // Loop over num_e values
    for (double num_e = 3.0; num_e <= 15.0; )
    {
        // Specify the external weight label (e.g., "55g")
        std::string weight_label = "55g";  // Adjust accordingly for other weights

        // Call simulation and save function
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
    return 0;
}
