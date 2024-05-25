#pragma clang diagnostic push
#pragma ide diagnostic ignored "ConstantParameter"
#pragma clang diagnostic ignored "-Wimplicit-exception-spec-mismatch"
#define FAST_MEMORY
///////////////////////////////////////////////////////////
#include <vector>
#include <iostream>

template<typename T, typename ... Ts>
[[maybe_unused]]inline void print(T a, Ts ... args);

template<typename T>
[[maybe_unused]]inline void print(T a);

#ifdef FAST_MEMORY
const size_t kMaxAllocatedBytes = 1'000'000'000;
size_t m_pos = 0;
std::byte* mem = static_cast<std::byte*>(malloc(kMaxAllocatedBytes));

struct Deleter {
  ~Deleter() {
    free(mem);
  }
};

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

    template<typename T>
    [[maybe_unused]] inline void read(T& num);

    [[maybe_unused]] inline void read(std::string& s);

    template<typename T>
    [[maybe_unused]] inline void read(std::vector<T>& v);

    [[maybe_unused]] inline void read(char& c);

    inline char getChar() {
      if (prevChar == 1 << 30) {
        return static_cast<char>(GET_CHAR());
      }
      char ans = static_cast<char>(prevChar);
      prevChar = 1 << 30;
      return ans;
    }

    template<typename T>
    [[maybe_unused]] inline void read(std::vector<T>& v) {
      for (int i = 0; i < v.size(); ++i) {
        read(v[i]);
      }
    }

    [[maybe_unused]] inline void read(char& c) {
      c = getChar();
    }

    template<typename T>
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
    template<typename T>
    [[maybe_unused]] inline void write(T& num);

    [[maybe_unused]] inline void write(std::string& s);

    template<typename T>
    [[maybe_unused]] inline void write(std::vector<T>& v);

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

    template<typename T>
    [[maybe_unused]]void write(std::vector<T>& v) {
      for (int i = 0; i < v.size(); ++i) {
        ::print(v[i]);
      }
    }

    template<typename T>
    [[maybe_unused]] inline void write(T& num) {
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

    [[maybe_unused]] inline void write(std::string& s) {
      for (char i: s) {
        PUT_CHAR(i);
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
[[maybe_unused]]inline void print(T a) {
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