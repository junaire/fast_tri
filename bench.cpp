#include "fast_tri.h"
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>

const int NUM_TESTS = 10000;
const double MAX_ERROR = 0.001;

double generate_random_angle() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_real_distribution<> dis(0, 2 * M_PI);
  return dis(gen);
}

bool test_accuracy() {
  bool failed = false;

  for (int i = 0; i < NUM_TESTS; ++i) {
    double angle = generate_random_angle();

    double glibc_sin = std::sin(angle);
    double fast_tri_sin = fast_sin(angle);

    double sin_error = std::abs(glibc_sin - fast_tri_sin);
    if (sin_error >= MAX_ERROR) {
      failed = true;
      std::cout << "sin(" << angle << ") failed, expected = " << glibc_sin
                << ", actual = " << fast_tri_sin << "\n";
    } else {
      std::cout << "sin(" << angle << ") OK!\n";
    }

    double glibc_cos = std::cos(angle);
    double fast_tri_cos = fast_cos(angle);

    double cos_error = std::abs(glibc_cos - fast_tri_cos);
    if (cos_error >= MAX_ERROR) {
      failed = true;
      std::cout << "cos(" << angle << ") failed, expected = " << glibc_cos
                << ", actual = " << fast_tri_cos << "\n";
    } else {
      std::cout << "cos(" << angle << ") OK!\n";
    }
  }
  return failed;
}

template <typename Func> double benchmark_impl(Func f, const char *name) {
  auto start = std::chrono::high_resolution_clock::now();

  volatile double result = 0.0; // volatile to prevent optimization
  for (int i = 0; i < NUM_TESTS; ++i) {
    double angle = generate_random_angle();
    result += f(angle);
  }

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;

  std::cout << std::setw(10) << name << ": " << diff.count() << " seconds"
            << "\n";
  return diff.count();
}

void benchmark() {
  std::cout << "\nPerformance Benchmark:"
            << "\n";
  double std_sin_time =
      benchmark_impl(static_cast<double (*)(double)>(std::sin), "std::sin");
  double fast_sin_time = benchmark_impl(fast_sin, "fast_sin");
  std::cout << "Speedup:\nsin: " << std_sin_time / fast_sin_time << "x\n\n";

  double std_cos_time =
      benchmark_impl(static_cast<double (*)(double)>(std::cos), "std::cos");
  double fast_cos_time = benchmark_impl(fast_cos, "fast_cos");
  std::cout << "Speedup:\ncos: " << std_cos_time / fast_cos_time << "x\n\n";
}

int main() {
  if (test_accuracy()) {
    std::abort();
  }
  benchmark();

  return 0;
}
