#include <iostream>
#include <string>
template<typename T>
class SinglePatternQ
{
public:
    static T* GetInit()
    {
        return &sit;
    }
private:
    static T sit;
};
std::string* result = SinglePatternQ<std::string>::GetInit();

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
template<typename T>
class SinglePatternS
{
public:
    static T* GetInit()
    {
        if (sit == NULL)
        {
            pthread_mutex_lock(&mutex);
            if (sit == NULL)
            {
                sit = new T;
            }
            pthread_mutex_unlock(&mutex);
        }
        return sit;
    }
private:
    static volatile T* sit;
};
