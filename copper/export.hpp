#if __GNUC__ >= 4
	#define EXPORT __attribute__((visibility ("default")))
#else
	#define EXPORT
#endif
