#if __GNUC__ >= 4
  #define EXPORT __attribute__((visibility("default")))
#elif WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT
#endif
