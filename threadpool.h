#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <list>
#include <vector>

namespace PennCloud::Utils {

// To use this thread pool, create a thread function that suits your need.
// Then, create a subclass that inherits from Task
// The subclass can contain the arguments needed for your thread function.
// Finally, call Dispatch()
// e.g. I want to call the function: int Foo(int a, const string& b)
// Define FooTask : public Task with fields that include return value and arguments
// Create FooTask with parameters.
// Call ThreadPool::Dispatch(&FooTask)

class ThreadPool {
  public:
    ThreadPool(int max_threads);
    ~ThreadPool();
    class Task;
    typedef void (*thread_task_fn)(Task* arg);
    class Task {
      public:
        Task(thread_task_fn func) : func_(func) {}
        thread_task_fn func_;
    };
    void Dispatch(Task* task);
    void KillThreads();
    pthread_mutex_t q_lock_;
    pthread_cond_t  q_cond_;
    std::list<Task*> work_queue_;
    bool killthreads_;
    int num_threads_running_;

  private:
    std::vector<pthread_t> thread_array_;
};

} // namespace PennCloud::Utils

#endif
