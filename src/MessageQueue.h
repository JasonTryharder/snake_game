#include <mutex>
#include <deque>
#include <iostream>
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
// for template class, you need to implement definition in header file instead of cpp file. 
// more info: https://stackoverflow.com/questions/1111440/undefined-reference-error-for-template-method
template <typename T>
T MessageQueue<T>::receive()
{
  std::unique_lock<std::mutex>uLock(_mutex); // modify the speed info under the lock
  _cond.wait(uLock,[this]{return !_queue.empty();}); // lambda function pass to conditional variable to wait for notification
  T msg = std::move(_queue.front());
  _queue.pop_front();
  return std::move(msg);
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
  std::lock_guard<std::mutex> uLock(_mutex);
  _queue.emplace_back(msg);
  std::cout<<"count down to increase speed -3 Seconds"<<std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  _cond.notify_one();
}