#ifndef TM_ALLOC_H
#define TM_ALLOC_H

#include <new>      // placement new
#include <cstddef>  // ptrdiff_t, size_t
#include <cstdlib>  // exit()
#include <climits>  // UINT_MAX
#include <iostream> // cerr
// 一个简单的空间配置器

#define ALLOC_VECTOR   //new vector mm
#define ALLOC_VECTOR_TEST //for test

namespace TmAllocator
{
    // 提供外部使用 allocator
    template <typename T>
    class tm_allocator {
    public:
        // 对象的类型
        typedef T value_type;
        typedef T* pointer;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef T& reference;
        typedef const T& const_reference;
        typedef const T* const_pointer;
        template <typename U>
        struct rebind {
        typedef tm_allocator<U> other;
        };

        tm_allocator() {}

    template <typename U>
    tm_allocator(const tm_allocator<U>&) {}

    const_pointer address(const_reference value) const {
        return std::addressof(value);
    }

    pointer address(reference value) const {
        return std::addressof(value);
    }

    pointer allocate(size_type size, const void* = nullptr) {
        void* p = aligned_alloc(sizeof(T) * size);
        if (!p && size > 0)
            throw printf("failed to allocate");
        return static_cast<pointer>(p);
    }
    
    size_type max_size() const {
        return ~static_cast<std::size_t>(0) / sizeof(T);
    }

    void deallocate(pointer ptr, size_type) {
        aligned_free(ptr);
    }

    template<class U, class V>
    void construct(U* ptr, const V& value) {
        void* p = ptr;
        ::new(p) U(value);
    }
    template<class U, class... Args>
    void construct(U* ptr, Args&&... args) {
        void* p = ptr;
        ::new(p) U(std::forward<Args>(args)...);
    }


    template<class U>
    void construct(U* ptr) {
        void* p = ptr;
        ::new(p) U();
    }

    template<class U>
    void destroy(U* ptr) {
        ptr->~U();
    }

private:
    void* aligned_alloc(size_type size) const {
       
        void* p;
        p=::malloc(size);
        return p;
    }

    void aligned_free(pointer ptr) {
      
        ::free(ptr);
    }


    };
}
#endif