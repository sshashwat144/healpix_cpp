#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <sstream>
#include "src/Healpix_2.15a/healpix_base.h"
#include "src/Healpix_2.15a/pointing.h"

// Function to generate random points within the bounds of theta and phi
std::vector<std::pair<double, double>> generate_random_points(double theta, double phi, double step, int count) {
    std::vector<std::pair<double, double>> points;
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<> dis_theta(theta - step, theta + step);
    std::uniform_real_distribution<> dis_phi(phi - step, phi + step);

    for (int i = 0; i < count; ++i) {
        double rand_theta = dis_theta(gen);
        double rand_phi = dis_phi(gen);
        points.emplace_back(rand_theta * (180.0 / M_PI), rand_phi * (180.0 / M_PI));  // Convert to degrees
    }

    return points;
}

void write_healpix_random_samples(int nside) {
    long npix = 12 * nside * nside;
    Healpix_Base healpix_base(nside, RING, SET_NSIDE);
    double pixel_size = std::sqrt(4 * M_PI / npix);  // Approximate size of each pixel

    for (long pix = 0; pix < npix; ++pix) {
        pointing ptg = healpix_base.pix2ang(pix);
        auto samples = generate_random_points(ptg.theta, ptg.phi, pixel_size / 2.0, 500);  // Generate 100 random samples within bounds

        std::stringstream filename;
        filename << "healpix_data_" << pix << ".txt";
        std::ofstream file(filename.str());
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << filename.str() << std::endl;
            continue;
        }

        //file << "Theta[Degrees],Phi[Degrees]" << std::endl;
        for (const auto& sample : samples) {
            file << sample.first << " " << sample.second << std::endl;
        }

        file.close();
    }
}

int main() {
    int nside = 1;  // Example nside
    write_healpix_random_samples(nside);
    return 0;
}
