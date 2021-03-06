## Circle

An simple FIFO ringbuffer written using C++, initial by a typename  `T` and unsigned integer `capacity` of ringbuffer, it will overwrites the old item(s) that pushing while ringbuffer is full.

```cpp
template<typename T, std::size_t capacity> class ringbuffer
```

- `bool emplace(const T& item)` - Pushing an new item to ringbuffer by lvalue reference, return if it overwrites an item.

- `bool emplace(T&& item)` - Pushing an new item to ringbuffer by copy construction, return if it overwrites an item.

- `T pull(void)` - Get an item from ringbuffer, return the default initialized type T if ringbuffer is empty, keeps the buffer in the ringbuffer if there had no overwrite action has been performed.

- `std::size_t size(void)` - Get current catchable item counts from ringbuffer.

- `bool is_empty(void)` - Check if ringbuffer is empty, empty for true, otherwise for false.

- `bool is_full(void)` - Check if ringbuffer is full, full for true, otherwise for false.

- `void reset(void)` - Reset all buffer(s) inside ringbuffer, not free the memory, only reset the ringbuffers pointer position.


<details>
    <summary>Click to view examples 👇</summary>

```cpp
#include <iostream>

#include "ringbuffer.hpp"

int main() {
    ubn::ringbuffer<int, 3> rb;

    for(std::size_t i = 1; i != 10; ++i) {
        if (rb.emplace(i)) {
            std::cout << "get tail from filled ringbuffer " << rb.pull() << " while pusing -> " << i << std::endl;
        } else {
            std::cout << "waiting ringbuffer to be filled -> " << i << std::endl;
        }
    }
}
```
</details>
