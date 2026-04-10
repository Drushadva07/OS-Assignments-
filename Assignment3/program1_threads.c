#include <stdio.h>
#include <pthread.h>

int x=10;

void* thread_func(void* arg){
   int local=5;
   printf("Thread ID:%ld\n",pthread_self());
   printf("Address of global variable x:%p\n",&x);
   printf("Address of local variable local:%p\n\n",&local);
 
   return NULL;
}

int main(){
  pthread_t t1,t2,t3;
  
  pthread_create(&t1,NULL,thread_func,NULL);
  pthread_create(&t2,NULL,thread_func,NULL);
  pthread_create(&t3,NULL,thread_func,NULL);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  
  return 0;
}
