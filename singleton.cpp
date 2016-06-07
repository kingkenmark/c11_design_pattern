#include <utility>
#include <stdexcept>
#include <string>
#include <iostream>

template<typename T>
class Singleton
{
public:
	template<typename... Args>
	static void createInstance(Args&&... args)
	{
		if(instance == nullptr)
			instance = new T(std::forward<Args>(args)...);
	}
	
	static void deleteInstance()
	{
		if(instance != nullptr)
			delete instance;
		instance = nullptr;
	}

	static T* getInstance()
	{
		if(instance == nullptr)
		 throw std::logic_error("Singleton has not been initialized");
		return instance;
	}
private:
	Singleton() = delete;
	~Singleton() = delete;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	static T* instance; 
};

template<typename T> T* Singleton<T>::instance = nullptr;

//test code
struct A
{
    template<typename T> friend class Singleton;
private:
	A(const std::string& str) { std::cout << "lvalue:" << str << std::endl;}
	A(std::string&& str) { std::cout << "rvalue:" << str << std::endl;}   
};

int main()
{
	Singleton<A>::createInstance(std::string("rrrrr"));
	Singleton<A>::deleteInstance();
	std::string lstring = "llllll";
	Singleton<A>::createInstance(lstring);
	Singleton<A>::deleteInstance();
	return 0;
}