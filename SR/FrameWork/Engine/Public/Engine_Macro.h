#pragma once


#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define NO_COPY(ClassName)								\
ClassName(const ClassName&) = delete;					\
ClassName& operator=(const ClassName&) = delete;

#define DECLARE_SINGLETON(ClassName)					\
		NO_COPY(ClassName)								\
public :												\
	static ClassName*		GetInstance();				\
	static unsigned long	DestroyInstance();			\
private:												\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)					\
ClassName* ClassName::m_pInstance = nullptr;			\
ClassName* ClassName::GetInstance()						\
{														\
	if (nullptr == m_pInstance)							\
		m_pInstance = new ClassName;					\
	return m_pInstance;									\
}														\
unsigned long ClassName::DestroyInstance()				\
{														\
	return Safe_Release(m_pInstance);					\
}

#define MSG_BOX(MESSAGE)		MessageBox(0, TEXT(MESSAGE), TEXT("System Error"), MB_OK)

#define BEGIN(NAME)		namespace NAME{

#define END				}

#define VK_MAX 0xff