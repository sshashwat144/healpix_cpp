#include <fstream>
#include <iostream>
#include <cmath>
#include "src/Healpix_2.15a/healpix_base.h"
#include "src/Healpix_2.15a/pointing.h"

void write_healpix_data(int nside, const std::string& filename) {
    long npix = 12 * nside * nside;  // Calculate npix from nside
    Healpix_Base healpix_base(nside, RING, SET_NSIDE);  // Initialize Healpix_Base with RING scheme

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    file << "Theta[Degrees],Phi[Degrees]" << std::endl;  // Header for the file

    for (long pix = 0; pix < npix; ++pix) {
        pointing ptg = healpix_base.pix2ang(pix);  // Get theta and phi in radians
        double theta_deg = ptg.theta * (180.0 / M_PI);  // Convert theta to degrees
        double phi_deg = ptg.phi * (180.0 / M_PI);  // Convert phi to degrees
        file << theta_deg << "," << phi_deg << std::endl;  // Write to file
    }

    file.close();  // Close the file after writing
}

int main() {
    int nside = 1;  // Example nside
    write_healpix_data(nside, "healpix_data.txt");
    return 0;
}
