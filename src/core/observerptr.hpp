#ifndef OBSERVERPTR_HPP
#define OBSERVERPTR_HPP

#include <cassert>
#include <memory>

template <class Tp_>
class ObserverPtr
{
    using Type = Tp_;
    using Pointer = Type*;
    using Reference = Type&;

public:
    ObserverPtr(Pointer ptr = nullptr) noexcept : ptr_ {ptr} {}
    ~ObserverPtr() noexcept = default;

    ObserverPtr(const ObserverPtr&) noexcept = default;
    ObserverPtr& operator=(const ObserverPtr&) noexcept = default;
    ObserverPtr(ObserverPtr&&) noexcept = default;
    ObserverPtr& operator=(ObserverPtr&&) noexcept = default;

    ObserverPtr& operator=(Pointer ptr) noexcept
    {
        ptr_ = ptr;
    }

    Reference operator*() const noexcept
    {
        assert(ptr_ && "ObserverPtr invalid. Cannot be NULL");
        return *ptr_;
    }

    Pointer operator->() const noexcept
    {
        assert(ptr_ && "ObserverPtr invalid. Cannot be NULL");
        return ptr_;
    }

    Pointer get() const noexcept
    {
        return ptr_;
    }

private:
    Pointer ptr_;
};

#endif // OBSERVERPTR_HPP
