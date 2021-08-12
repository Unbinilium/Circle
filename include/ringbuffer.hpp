/*
 * @name: ringbuffer.hpp
 * @namespace: ubn
 * @class: ringbuffer
 * @brief: Simple FIFO ringbuffer implementation
 * @author Unbinilium
 * @version 1.0.0
 * @date 2021-05-12
 */

#pragma once

#include <utility>
#include <type_traits>

namespace ubn {
    template<typename T, const std::size_t capacity>
    class ringbuffer {
    public:
        /*
         * @brief: Initialize ringbuffer class
         * @param: typename, the typename of item(s) for ringbuffer to store
         * @param: const std::size_t, the capacity of ringbuffer, overwrites the old item(s) when pushing if ringbuffer is full
         */
        constexpr ringbuffer() noexcept {
            static_assert(capacity >= 1UL, "ringbuffer capacity < 1");
        }
        
        /* @brief: Destrutor of ringbuffer */
        ~ringbuffer() noexcept {
            delete[] m_buffer;
        }
        
        /*
         * @brief: Let ringbuffer non-copyable and non-movable
         * @param: const ringbuffer&
         */
        constexpr ringbuffer &operator=(const ringbuffer&) = delete;
        
        /*
         * @brief:  Pushing an new item to ringbuffer, return if it overwrites an item
         * @param:  const T&, const lvalue reference of typename T
         * @return: bool, whether you're pushing on a full ringbuffer which performs the overwrite action on an old item
         */
        constexpr bool emplace(const T& __v) noexcept {
            m_buffer[m_position++ % capacity] = __v;
            return is_overwrite();
        }
        
        /*
         * @brief:  Pushing an new item to ringbuffer, return if it overwrites an item
         * @param:  T&&, rvalue reference of typename T
         * @return: bool, whether you're pushing on a full ringbuffer which performs the overwrite action on an old item
         */
        template<typename T_ = T>
        constexpr bool emplace(T&& __v, typename std::enable_if_t<!std::is_reference_v<T_>, std::nullptr_t> = nullptr) noexcept {
            m_buffer[m_position++ % capacity] = std::forward<T>(__v);
            return is_overwrite();
        }
        
        /*
         * @brief:  Get an item from ringbuffer, return the default initialized type T if ringbuffer is empty, and keeps the buffer in the ringbuffer if there had no overwrite action has been performed
         * @return: T, the item from ringbuffer tail or the default initialed type T if ringbuffer is empty
         */
        constexpr T pull() noexcept {
            return m_buffer[is_empty() ? capacity : (m_position + m_capacity++ - capacity) % capacity];
        }
        
        /*
         * @brief:  Get current catchable item counts from ringbuffer
         * @return: std::size_t, the current catchable item counts from ringbuffer
         */
        constexpr std::size_t size() noexcept {
            return capacity - m_capacity;
        }
        
        /*
         * @brief:  Check if ringbuffer is empty, empty for true, otherwise for false
         * @return: bool
         */
        constexpr bool is_empty() noexcept {
            return !(m_capacity != capacity);
        }
        
        /*
         * @brief:  Check if ringbuffer is full, full for true, otherwise for false
         * @return: bool
         */
        constexpr bool is_full() noexcept {
            return m_capacity ? false : true;
        }
        
        /*
         * @brief: Reset all buffer(s) inside ringbuffer, not free the memory, only reset the ringbuffers pointer position
         */
        constexpr void reset() noexcept {
            m_capacity = capacity;
            m_position = 0;
        }
        
    protected:
        constexpr bool is_overwrite() noexcept {
            return (m_capacity ? --m_capacity : false) ? false : true;
        }
        
    private:
        T*          m_buffer   { new T[capacity + 1]{} };
        std::size_t m_capacity { capacity };
        std::size_t m_position { 0 };
    };
}
