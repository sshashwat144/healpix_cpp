#include <fstream>
#include <iostream>
#include <cmath>
#include <random>
#include <sstream>
#include "src/Healpix_2.15a/healpix_base.h"
#include "src/Healpix_2.15a/pointing.h"

std::vector<std::pair<double, double>> order_to_boundries(int order){

}

std::vector<std::pair<double, double>> boundries_to_sampling(int order){

}







int main() {
    int nside;
    int ang_step_size;
    std::cout << "Enter the order";
    std::cin >> nside;
    std::cout << "Enter the value of step size";
    std::cin >> ang_step_size;
    std::cout << "The number of regions created are (nside * 12 * 12): "<<int(nside)*int(nside)*12<<std::endl;
    write_healpix_random_samples(nside, ang_step_size, num_points);
    return 0;
}