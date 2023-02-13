#ifndef NOTCOPYABLE_HPP
#define NOTCOPYABLE_HPP

struct NotCopyable
{
public:
    NotCopyable() = default;
    NotCopyable(const NotCopyable&) = delete;
    NotCopyable& operator=(const NotCopyable&) = delete;

    virtual ~NotCopyable() = default;
};

#endif
