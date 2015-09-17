// Mutex
// 将来的には boost::thread などに置換する方針

#include <pthread.h>

#ifndef MY_MUTEX_H
#define MY_MUTEX_H

template<typename T>
class myMutex{
 public:
  myMutex(){
    pthread_mutex_init(&mutex, NULL);
    value = 0;
  }
  myMutex(T n){
    pthread_mutex_init(&mutex, NULL);
    value = n;
  }
  
  //
  void lock(){pthread_mutex_lock(&mutex);};
  void unlock(){pthread_mutex_unlock(&mutex);};
  
  // こんなものは不要
  T get(){
    pthread_mutex_lock(&mutex);
    T tmp = value;
    pthread_mutex_unlock(&mutex); 
    return tmp;
  }
  void set(T n){
    pthread_mutex_lock(&mutex);
    value = n;
    pthread_mutex_unlock(&mutex);
  }
  
  //コピー禁止にした方がいい。
  //デストラクタとかにアンロックが。
  
  //	pthread_mutex_t mutex; //privateの方がいい
 private:
  T value;
  pthread_mutex_t mutex; //とりあえず外から勝手にロックされないようにprivateにしておく
};

#endif
