#include <iostream>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

int main() {
    const char* filename = "/tmp/Sensor_Data.txt";

    // Random number generator for temperature between 20.0 and 30.0
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(20.0f, 30.0f);

    while (true) {
        float temp = dist(gen);

        // Open file descriptor for writing
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd >= 0) {
            char buff[32];
            int len = snprintf(buff, sizeof(buff), "%.2f", temp);
            ssize_t wt = write(fd, buff, len);
            if (wt < 0) {
                std::cerr << "Failed to write to file\n";
            }
            close(fd);
        } else {
            perror("Failed to open file");
        }

        std::cout << "[SIM] Wrote temperature: " << temp << " °C\n";

        // Wait 1 second before writing the next value
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
