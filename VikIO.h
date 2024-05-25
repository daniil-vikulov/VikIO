#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
#pragma clang diagnostic ignored "-Wimplicit-exception-spec-mismatch"
#define FAST_MEMORY
///////////////////////////////////////////////////////////
#include <iostream>
#include <concepts>

#ifdef FAST_MEMORY
const size_t kMaxAllocatedBytes = 1'000'000'000;
static constexpr char kContainerSep = ' ';
size_t m_pos = 0;
std::byte* mem = static_cast<std::byte*>(malloc(kMaxAllocatedBytes));

struct Deleter {
  ~Deleter() {
    free(mem);
  }
};

namespace UtilConcepts {
  template <typename T>
  concept IndexedContainer = requires(T t, size_t index) {
    { t.size() } -> std::same_as<size_t>;
    { t.size() } noexcept;
    { t[index] } -> std::same_as<typename T::value_type&>;
  };

  template <typename T>
  concept Numeric = std::is_arithmetic_v<T>;
}

// free all memory after program ends
[[maybe_unused]] Deleter static_deleter;

constexpr size_t alignUp(size_t n, size_t align) {
  return (n + (align - 1)) & ~(align - 1);
}

void* operator new(size_t n) {
  size_t pos = alignUp(m_pos, alignof(std::max_align_t));
  if (pos + n > kMaxAllocatedBytes) {
    throw std::bad_alloc();
  }
  m_pos = pos + n;
  return mem + pos;
}

void operator delete(void*) {}
void operator delete(void*, size_t) {}

#endif
namespace vik_io {
#ifdef __linux__
#define GET_CHAR() getchar_unlocked()
#define PUT_CHAR(c) putchar_unlocked(c)
#else
#define GET_CHAR() _getchar_nolock()
#define PUT_CHAR(c) _putchar_nolock(c)
#endif
  namespace in {
#define buff 1000
    int prevChar = 1 << 30;

    inline char getChar();

    template<UtilConcepts::Numeric T>
    [[maybe_unused]] inline void read(T& num);

    [[maybe_unused]] inline void read(std::string& s);

    template<UtilConcepts::IndexedContainer T>
    [[maybe_unused]] inline void read(T& v);

    [[maybe_unused]] inline void read(char& c);

    inline char getChar() {
      if (prevChar == 1 << 30) {
        return static_cast<char>(GET_CHAR());
      }
      char ans = static_cast<char>(prevChar);
      prevChar = 1 << 30;
      return ans;
    }

    template<UtilConcepts::IndexedContainer T>
    [[maybe_unused]] inline void read(T& v) {
      for (int i = 0; i < v.size(); ++i) {
        read(v[i]);
      }
    }

    [[maybe_unused]] inline void read(char& c) {
      c = getChar();
    }

    template<UtilConcepts::Numeric T>
    [[maybe_unused]] inline void read(T& num) {
      char c = getChar();
      T x = 0;
      bool isNeg = false;
      for (; !('0' <= c && c <= '9') && c != '-'; c = getChar());
      if (c == '-') {
        isNeg = true;
        c = getChar();
      }
      for (; '0' <= c && c <= '9'; c = getChar()) {
        x = x * 10 + c - '0';
      }
      //prevChar = static_cast<unsigned char>(c);
      if (isNeg) {
        x *= -1;
      }
      num = x;
    }

    [[maybe_unused]] inline void read(std::string& s) {
      char buf[buff];
      char c = getChar();
      int i = 0;
      while ('\n' != c || i == 0) {
        buf[i++] = c;
        c = getChar();
      }

      s.resize(i);
      for (int j = 0; j < i; ++j) {
        s[j] = buf[j];
      }
    }
  }

  namespace out {
    template<UtilConcepts::Numeric T>
    [[maybe_unused]] inline void write(T num);

    template<UtilConcepts::IndexedContainer T>
    [[maybe_unused]] inline void write(const T& container);

    [[maybe_unused]] inline void write(char c);

    [[maybe_unused]] inline void write(const char*);

    [[maybe_unused]] inline void write(const char* c) {
      int i = 0;
      while (c[i] != '\0') {
        vik_io::out::write(c[i++]);
      }
    }

    [[maybe_unused]] inline void write(char c) {
      PUT_CHAR(c);
    }

    template<UtilConcepts::IndexedContainer T>
    [[maybe_unused]]void write(const T& container) {
      for (int i = 0; i < container.size(); ++i) {
        write(container[i]);
        if constexpr (!std::is_same_v<T, std::string>) {
          if (i < container.size() - 1) {
            write(kContainerSep);
          }
        }
      }
    }

    template<UtilConcepts::Numeric T>
    [[maybe_unused]]void write(T num) {

      if (num < 0) {
        PUT_CHAR('-');
        num *= -1;
      }
      char buf[50];
      int i = 0;
      if (num == 0) {
        PUT_CHAR('0');
        return;
      }
      while (num > 0) {
        buf[i] = '0' + (num % 10);
        num /= 10;
        i++;
      }
      for (int j = i - 1; j >= 0; --j) {
        PUT_CHAR(buf[j]);
      }
    }
  }
#undef buff
#undef GET_CHAR
#undef PUT_CHAR
#ifdef FAST_MEMORY
#undef FAST_MEMORY
#endif
}
///////////////////////////////////////////////////////////

char sep = '\n';

template<typename T>
[[maybe_unused]]inline void read(T& a) {
  vik_io::in::read(a);
}

template<typename T, typename ... Ts>
[[maybe_unused]]inline void read(T& a, Ts& ... args) {
  vik_io::in::read(a);
  read(args ...);
}

template<typename T>
[[maybe_unused]]inline void print(const T& a) {
  vik_io::out::write(a);
  if (sep != '\0') {
    vik_io::out::write(sep);
  }
}

template<typename T, typename ... Ts>
[[maybe_unused]]inline void print(T a, Ts ... args) {
  print(a);
  print(args ...);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma clang diagnostic pop