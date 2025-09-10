
#pragma once

#include <iostream>
#include <cstring>


#define MYLIB_API_PUB __attribute__((__visibility__("default"))) // "hidden", "internal", "default"
#define MYLIB_API_PRIV __attribute__((__visibility__("internal"))) // "hidden", "internal", "default"

struct SStreamAccessor;

class MYLIB_API_PRIV StreamIterator {
public:
    using ValueType = char;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    StreamIterator(PointerType ptr);

    // PreFix operator
    StreamIterator operator++() const;

    // PostFix operator
    StreamIterator operator++(int) const;

    StreamIterator operator--();

    StreamIterator operator--(int);

    ReferenceType operator[](int n) const;

    PointerType operator->() const;

    ReferenceType operator*() const;

    bool operator==(const StreamIterator& other) const;

    bool operator!=(const StreamIterator& other) const;

private:
    mutable PointerType m_Ptr;
};

class MYLIB_API_PUB SStream {
private:
    using Iterator = StreamIterator;
    using constIterator = const StreamIterator;

public:
    SStream();

    SStream(const char* string);

    SStream(SStream&& other);

    SStream& operator=(SStream&& other);
    
    SStream& operator<<(SStream&& other);

    SStream& operator<<(const char* data);

    SStream(const SStream&) = delete;
    SStream& operator=(const SStream&) = delete;

    ~SStream();

    Iterator begin();
    Iterator end();
    constIterator begin() const;
    constIterator end() const;

private:
    char* str;
    size_t N;
    friend struct SStreamAccessor;
};

std::ostream& operator<<(std::ostream& stream, const SStream& string);

std::ostream& operator<<(std::ostream& stream, SStream&& string);

struct SStreamAccessor {
private:
    SStreamAccessor() = default;
public:
    static int getsize(const SStream& sstream);
    static void print_contents(const SStream& sstream);
};