#define OVERRIDE virtual
#define ABSTRACT virtual
#define OUT
#define BUF_SIZE 1024
#define BEGIN_NS_AT namespace Arthas{
#define END_NS_AT }
#define SAFE_DELETE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		delete PTR; \
		PTR = nullptr; \
	}\
}

#define SAFE_RELEASE(PTR)\
{\
	if (PTR != nullptr)\
	{\
		PTR->release(); \
		PTR = nullptr; \
	}\
}