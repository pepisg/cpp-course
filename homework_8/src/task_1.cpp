#include <cstddef>
#include <iostream>

int main() {
  int i = 0;
  while (true) {
    i++;
    std::byte arr[102400 * i];
    std::cout << i * 100 << "[KiB] Allocated in the stack\n";
  }
  return 0;
}