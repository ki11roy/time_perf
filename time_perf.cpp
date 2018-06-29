#include <chrono>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <sys/time.h>
#include <vector>

template <class Tp> inline void DoNotOptimize(Tp const &value) {
  asm volatile("" : : "g"(value) : "memory");
}

int main() {
  auto iterations = 100000000;
  std::chrono::time_point<std::chrono::system_clock> start;
  std::chrono::time_point<std::chrono::system_clock> stop;

  // noop
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    asm volatile("nop" : : :);
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "noop" << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;

  // time()
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    DoNotOptimize(time(0));
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "time()" << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;

  // gettimeofday()
  struct timeval tv;
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    DoNotOptimize(gettimeofday(&tv, NULL));
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "gettimeofday()" << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;

  // std::chrono::steady_clock::now()
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    DoNotOptimize(std::chrono::steady_clock::now());
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "std::chrono::steady_clock::now()"
            << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;

  // std::chrono::system_clock::now()
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    DoNotOptimize(std::chrono::system_clock::now());
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50) << "std::chrono::system_clock::now()"
            << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;

  // std::chrono::high_resolution_clock::now()
  start = std::chrono::system_clock::now();
  for (auto i = 0; i < iterations; ++i) {
    DoNotOptimize(std::chrono::high_resolution_clock::now());
  }
  stop = std::chrono::system_clock::now();
  std::cout << std::left << std::setw(50)
            << "std::chrono::high_resolution_clock::now()" << std::setw(20)
            << iterations /
                   std::chrono::duration<double>(stop - start).count() / 1000000
            << std::endl;
}
