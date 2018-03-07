#pragma once

#include <pthread.h>
#include <stdint.h>
#include <assert.h>

template<typename T>
class ThreadLocal
{
public:
    ThreadLocal() {
        pthread_key_create(&data, DeleteData);
    }

    ~ThreadLocal()
    {
        pthread_key_delete(data);
    }

    template<typename... Args>
    T & GetData(const Args &... args)
    {
        T * data_ptr = (T*) pthread_getspecific(data);
        if( data_ptr == NULL ) 
        {
            data_ptr = new T(args...);
            pthread_setspecific(data, data_ptr);
        }    
        assert(data_ptr != NULL);
        return *data_ptr;
    }

    template<typename... Args>
    static T & Instance(const Args &... args)
    {
        static ThreadLocal s_obj;
        return s_obj.GetData(args...);
    }

private:
    static void DeleteData(void * ctx_ptr)
    {
        delete (T*)ctx_ptr;
    }

private:
    pthread_key_t data;
};
