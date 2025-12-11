#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <unistd.h>

/*-------------- Parent Class ---------------*/

class SensorInterface {
public:
  virtual ~SensorInterface() = default;
  virtual float ReadTemperature() = 0; // pure abstraction
};

/*------------- File Descriptor Sensor-------------*/

class FileDescriptorSensor : public SensorInterface {
private:
  const std::string path;
  int fd = 0;

public:
  explicit FileDescriptorSensor(const std::string &file_path)
      : path(file_path) { // Parameterized Constructor
    fd = open(file_path.c_str(), O_RDONLY);
    if (fd < 0) {
      perror("Failed to open the file:(\n");
    } else {
    }
  }

  ~FileDescriptorSensor() { close(fd); }

  float ReadTemperature() override {
    if (fd < 0) {
      std::cout << "No temperature to read";
      return 0.0f;
    } else {
      char buff[32];
      memset(buff, 0, sizeof(buff)); // set the whole buffer with 0's
      lseek(fd, 0, SEEK_SET);        // reset file pointer
      ssize_t rd = read(fd, buff, sizeof(buff) - 1); // leave one char for '\0'
      if (rd <= 0) {
        std::cout << "Couldn't read:(\n";
        return 0.0f;
      } else {
        return (std::stof(buff)); // converts the buff string to float
      }
    }
  }
};

/*---------------- Display Class -----------------*/
class SensorDisplay {
private:
  SensorInterface &sensor;

public:
  explicit SensorDisplay(SensorInterface &s) : sensor(s) {}

  void DisplaySensorReading() {
    std::cout << "Temperature: " << sensor.ReadTemperature() << std::endl;
  }
};

/*--------------- Logger Class ----------------*/
class SensorLogger {
private:
  SensorInterface &sensor;
  int fd;

public:
  SensorLogger(SensorInterface &s, const std::string &file_path) : sensor(s) {
    fd = open(file_path.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0) {
      perror("Couldn't open log file:(\n");
    } else {
    }
  }

  ~SensorLogger() {
    if (fd >= 0) {
      close(fd);
    }
  }

  void LogData() {
    if (fd < 0) {
      perror("Couldn't log data:(\n");
      return;
    } else {
      float temp = sensor.ReadTemperature();
      char buff[32];
      int len = snprintf(buff, sizeof(buff), "%.2f\n", temp);
      ssize_t wt = write(fd, buff, len);
      if (wt < 0) {
        std::cout << "Couldn't write data in logger file:(\n";
      } else {
      }
    }
  }
};

/*----------------- Main -------------------*/

int main() {
  auto sensor = std::make_unique<FileDescriptorSensor>("/tmp/Sensor_Data.txt");
  SensorDisplay display(*sensor);
  SensorLogger logger(*sensor, "/home/Log_data.txt");

  int maxReadings = 10; // stop after 10 readings
  int counter = 0;

  while (counter < maxReadings) {
    display.DisplaySensorReading();
    logger.LogData();
    counter++;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "Finished reading sensor." << std::endl;
  return 0;
}
