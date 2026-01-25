#include <chrono>
#include <condition_variable>
#include <cstring>
#include <fcntl.h> // For open flags like O_WRONLY, O_CREAT, O_TRUNC
#include <iostream>
#include <mutex>
#include <sys/types.h> // for ssize_t
#include <thread>
#include <unistd.h> // For write(), close()

std::mutex mx;
std::condition_variable cv;

void capslockLoop(void) {
  std::unique_lock uL(mx);
  int fd = open("/sys/class/leds/input7::capslock/brightness", O_RDONLY);
  if (fd < 0) {
    return;
  }
  char prev[1] = {0};
  char curr[1] = {0};

  ssize_t n = read(fd, prev, 1);
  if (n <= 0) {
    return;
  }

  close(fd);

  while (true) {
    int fd = open("/sys/class/leds/input7::capslock/brightness", O_RDONLY);
    if (fd < 0) {
      return;
    }
    n = read(fd, curr, 1);

    if (n <= 0) {
      return;
    }

    if ((prev[0] != curr[0]) && (curr[0] != '\n')) {
      prev[0] = curr[0];
      change = true;
      uL.unlock();
      close(fd);
      std::this_thread::sleep_for(std::chrono::seconds(1));
      cv.notify_one();
      std::cout << "notification sent\n";

      break;
    }
    close(fd);
  }
}

void fileWrite(void) {
  std::unique_lock uL(mx);
  cv.wait(uL);
  std::cout << "received notification (:\n";
  int fd = open("/home/yasmine/Desktop/threads.txt",
                O_WRONLY | O_APPEND | O_CREAT, 0644);
  if (fd < 0) {
    return;
  }
  char buff[] = "capslock state changed!! (:\n";
  ssize_t n = write(fd, buff, sizeof(buff) - 1);
  if (n <= 0) {
    return;
  }
  close(fd);
}

int main() {

  std::thread setter(capslockLoop);
  std::thread getter(fileWrite);

  setter.join();
  getter.join();
  return 0;
}
