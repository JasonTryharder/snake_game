#include <mutex>
#include <deque>
#include <condition_variable>
#include <thread>

template <class T>
class MessageQueue
{
public:
    // MessageQueue<T>();
    T receive();
    void send(T &&msg);
private:
    std::deque<T> _queue; // currently only one element in the queue
    std::condition_variable _cond;
    std::mutex _mutex;
};