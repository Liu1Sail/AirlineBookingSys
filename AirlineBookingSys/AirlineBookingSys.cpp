// AirlineBookingSys.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "Utils.h"

Event::Dispatcher<std::string> dispatcher;
class Example
{
private:
    std::string className = "Example";
private:
    void getClassName(std::string& ans)
    {
        ans = className;
    }
public:
    Example() {
        dispatcher.subscribe("LOG", BIND(  ,      std::string str) {//订阅LOG事件
            std::cout << str << std::endl; });

        dispatcher.subscribe("ADD",//订阅ADD事件
            BIND(     ,    int a, int b){
                std::cout << a + b<<std::endl;
            }
        );

        dispatcher.subscribe("CALL_MEM_FUNC",
            BIND(this  ,std::string & ans){
                getClassName(ans);
            }
        );


    }
};

Example ex;



int main()
{
    dispatcher.sendEvent<std::string>("LOG", "Hello dispatcher! ! !");
    dispatcher.sendEvent("ADD", 1 , 2);


    std::string exam;
    dispatcher.sendEvent<std::string&>("CALL_MEM_FUNC", exam);
    std::cout << exam<<std::endl;

}
