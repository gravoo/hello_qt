#include <boost/process.hpp>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

namespace bp = boost::process;
std::mutex mtx;
std::condition_variable cv;
bool ready_to_read = false;
bool ready_to_write = true;

int main()
{
    std::stringstream processes;
    std::thread processes_list_producer = std::thread(
      [&processes]()
      {
          while (true)
          {

              std::unique_lock<std::mutex> lock(mtx);
              cv.wait(lock, [] { return ready_to_write; });
              processes.str("");
              processes.clear();
              bp::ipstream pipe_stream;
              bp::child c("ps -e", bp::std_out > pipe_stream);

              std::string line;
              while (pipe_stream && std::getline(pipe_stream, line))
              {
                  processes << line << "\n";
              }

              c.wait();
              ready_to_read = true;
              ready_to_write = false;
              cv.notify_one();
          }
      });

    std::thread processes_list_consumer = std::thread(
      [&processes]()
      {
          while (true)
          {

              std::string line;
              std::unique_lock<std::mutex> lock(mtx);
              cv.wait(lock, [] { return ready_to_read; });
              while (std::getline(processes, line))
              {
                  std::cout << line << "\n";
              }

              std::this_thread::sleep_for(std::chrono::seconds(2));
              ready_to_read = false;
              ready_to_write = true;
              cv.notify_one();
          }
      });

    processes_list_producer.join();
    processes_list_consumer.join();

    return 0;
}