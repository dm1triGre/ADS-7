// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <cstdint>
#include "train.h"

using std::cout;
using std::vector;
using std::string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::duration_cast;

void fillTrain(Train& train, int32_t n, const string& mode) {
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> dist(0, 1);

  for (int32_t i = 0; i < n; ++i) {
    if (mode == "off") {
      train.addCar(false);
    } else if (mode == "on") {
      train.addCar(true);
    } else {
      train.addCar(dist(gen));
    }
  }
}

int main() {
  vector<int32_t> sizes = { 2000, 4000, 6000, 8000, 10000 };

  cout << "mode,n,ops,time_us\n";

  for (const string& mode : { "off", "on", "random" }) {
    for (int32_t n : sizes) {
      Train train;
      fillTrain(train, n, mode);

      auto start = high_resolution_clock::now();
      train.getLength();
      auto end = high_resolution_clock::now();

      int64_t duration = duration_cast<microseconds>(end - start).count();
      int32_t ops = train.getOpCount();

      cout << mode << "," << n << "," << ops << "," << duration << "\n";
    }
  }

  return 0;
}
