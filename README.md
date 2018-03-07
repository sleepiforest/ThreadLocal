# ThreadLocal
c++11 code style. Gracefully wrap pthread functions to manipulate thread locals or thread singleton.

Examples:
```
int & i = ThreadData<int>::Instance(5);
std::string & b = ThreadData<std::string>::Instance(i, 'b');
```

You can see more sample code in test.cpp.

In addition, new c++ standard has involve keyword thread_local
You can simplily define variables like this:
static thread_local int i(5);
static thread_local std::string s(i, 'b');

However, thread_local only support trivial type and some platform do not support this keyword, in which case you can use this library instead.


