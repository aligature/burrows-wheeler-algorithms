#include <deque>
#include <functional>
#include <iostream>
#include <utility>

class RunThings
{
public:
   RunThings()
   {
   }

   template<typename T>
   void queue(T&& fn)
   {
      fns_.push_back(std::forward<T>(fn));
   }

   int run(int init)
   {
      for(auto const& fn: fns_)
      {
         init = fn(init);
      }
      return init;
   }


private:
   typedef std::function<int (int)> IntFn;
   typedef std::deque<IntFn> FnQueue;
   FnQueue fns_;
};

int main()
{
   RunThings r;
   r.queue([](int i){ return i * 3;});
   r.queue([](int i){ return i + 4;});
   r.queue([](int i){ return i / 5;});
   std::cout << r.run(7) << std::endl;
}
