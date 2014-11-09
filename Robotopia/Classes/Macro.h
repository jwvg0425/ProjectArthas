#define OVERRIDE virtual
#define ABSTRACT virtual
#define OUT
#define BUF_SIZE 1024
#define MAX_LEN 256
#define MAX_KEY_NUM	255
#define MAX_FRAME 50
#define GAME_SCENE_TAG 1
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