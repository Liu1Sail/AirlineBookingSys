
#pragma once
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <functional>
#include <memory>
namespace Event
{
#define BIND(v,...) (std::function<void(__VA_ARGS__)>)[v](__VA_ARGS__)
#define NO_RETURN_LAMBDA(v,...) (std::function<void(__VA_ARGS__)>)[v](__VA_ARGS__)
    class BaseCallBackList {
    public:
        virtual ~BaseCallBackList() = default;
    };

    template<typename... Args>
    class CallBackList : public BaseCallBackList {
    public:
        using CallbackType = std::function<void(Args...)>;
        void push_back(CallbackType func) {
            callBackList.push_back(func);
        }
        void execute(Args... args) {
            for (auto& func : callBackList) {
                func(args...);
            }
        }
    private:
        std::vector<CallbackType> callBackList;
    };

    template<typename EventNameType>
    class Dispatcher {
    public:
        template<class Return, class ...Args>
        void subscribe(const EventNameType& index, std::function<Return(Args...)> func) {
            //std::function<Return(Args...)> func = fun;
            auto it = callBackMap.find(index);
            if (it == callBackMap.end()) {
                callBackMap[index] = std::make_unique<CallBackList<Args...>>();
            }
            auto p = dynamic_cast<CallBackList<Args...> *>(callBackMap[index].get());
            if (p) {
                p->push_back(func);
            }
            else {
                std::cout << "(" + index + ")Binding Func Type Error\n";
            }
        }
        /*template<typename T>
        void subscribe(const EventNameType& index, std::function<void(T)> func) {
            auto it = callBackMap.find(index);
            if (it == callBackMap.end()) {
                callBackMap[index] = std::make_unique<CallBackList<T>>();
            }
            auto p = dynamic_cast<CallBackList<T> *>(callBackMap[index].get());
            if (p) {
                p->push_back(func);
            }
            else {
                std::cout << "(" + index + ")Binding Func Type Error\n";
            }
        }*/

        template<class ...Args>
        void sendEvent(const EventNameType& index, Args... args) {
            auto it = callBackMap.find(index);
            if (it != callBackMap.end()) {
                auto p = dynamic_cast<CallBackList<Args...> *>(it->second.get());
                if (p) {
                    p->execute(args...);
                }
                else {
                    std::cout << "(" + index + ")Calling Func Type Error\n";
                }
            }
        }

    private:
        std::unordered_map<EventNameType, std::unique_ptr<BaseCallBackList>> callBackMap;
    };


    namespace WindowEvent
    {
        struct WindowResizeEvent {
            int width, height;
        };
        struct KeyPressedEvent {
            int keyCode;
            bool repeat;
        };
        struct KeyReleasedEvent {
            int key;
        };
        struct MousePressedEvent {
            int button;
            bool repeat;
        };
        struct MouseReleasedEvent {
            int button;
        };
        struct MouseScrolledEvent {
            float offsetX, offsetY;
        };
        struct MouseMovedEvent {
            float x, y;
        };
    }
}