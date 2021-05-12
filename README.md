## Circle

An simple FIFO ringbuffer written using C++
```cpp
template<typename T, int64_t capacity> class ringbuffer
```

- `bool push_head(const T& item)` - Pushing an new item on ringbuffer head by lvalue reference, return if it overwrites an item.

- `bool push_head(T&& item)` - Pushing an new item on ringbuffer head by copy construction, return if it overwrites an item.

- `T catch_tail(void)` - Get an item from ringbuffer tail, return the default initialized type T if ringbuffer is empty, and keeps the buffer in the ringbuffer if there had no overwrite action has been performed.

- `int64_t size(void)` - Get current catchable item counts from ringbuffer.

- `bool is_empty(void)` - Check if ringbuffer is empty, empty for true, otherwise for false.

- `bool is_full(void)` - Check if ringbuffer is full, full for true, otherwise for false.

- `void empty(void)` - Empty all buffer(s) inside ringbuffer, not free the memory, only reset the ringbuffers pointer position.


<details>
    <summary>Click to view examples 👇</summary>

```cpp
#include <thread>
#include <ranges>
#include <iostream>

#include "include/queue.hpp"

int main() {
    ubn::queue<int> q;
    std::jthread t[] = {
        std::jthread([&]() {
            for (auto i : std::views::iota(0, 10))
                std::cout << "thr1: poll <- " << q.poll() << "\n";
        }),
        std::jthread([&]() {
            for (auto i : std::views::iota(0, 10))
                std::cout << "thr2: poll <- " << q.poll() << "\n";
        }),
        std::jthread([&]() {
            for (auto i : std::views::iota(0, 10)) {
                std::cout << "thr3: push -> " << i << "\n";
                q.push(i);
            }
        }),
        std::jthread([&]() {
            for (auto i : std::views::iota(0, 10)) {
                std::cout << "thr4: push -> " << i << "\n";
                q.push(i);
            }
        })
    };
}
```
</details>
