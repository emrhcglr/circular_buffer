// FIFO ADD
#include <stdio.h>
#include "fifo.h"
#define  debug 0

int main(void) {
  
    FIFOQueue fifoo;
    FIFO_init(&fifoo);
    //FIFO_push(&fifoo,0);

    // Insert bytes into the queue
    for (int i =1; i <3; i++) 
      FIFO_push(&fifoo, i);
    

    // Retrieve bytes from the queue
    for (int i = 0; i < 3; i++) 
        FIFO_pop(&fifoo);

     for (int i =10; i <30; i++) 
  // for (int i =1; i <BUFFER_SIZE; i++) 
        FIFO_push(&fifoo, i);
    
     for (int i = 0; i <10; i++) 
    FIFO_pop(&fifoo);

    return 0;
}

void FIFO_init(FIFOQueue *fifo) {
    
    for(int i = 0; i<BUFFER_SIZE-1; i++)
        fifo->buffer[i] =0;
    fifo->head = 0;         // Point head to the start of the buffer
    fifo->tail = 0;         // Point tail to the start of the buffer
    fifo->count = 0;                    // Initialize count to 0
}

void FIFO_push(FIFOQueue *fifo, unsigned char tts){

    fifo->buffer[fifo->head] = tts;
  
    fifo->head =(fifo->head+1) & FIFO_MASK; // it wraps around the buffer turns to zero again 
    //This is because 128 in binary is 10000000, and when ANDed with 01111111 (which is 0x7F), it results in 00000000 (i.e., 0).
    if (fifo->count == BUFFER_SIZE) {

        // Buffer is full, move the tail to make space (overwrite oldest data)
        if(debug)
        printf("buffer is full\n");
        fifo->tail = (fifo->tail + 1) & FIFO_MASK;    // Efficient wrapping for tail
    } 
    else {
        fifo->count++;  // Increase count if not full
    }
    if (debug)
    FIFO_getStats_debug(fifo);
    
   }

void FIFO_pop(FIFOQueue *fifo){
    
  if (fifo->count==0){
    // fifo is empty  nothing to send.
    if (debug)
    printf("buffer is empty\n");
  }

  fifo->byte_read = fifo->buffer[fifo->tail];
  if(debug)
  fifo->buffer[fifo->tail] = 0;
  
  if (fifo->count>0){
    fifo->tail = (fifo->tail+1) & FIFO_MASK;
    fifo->count--;
  }

  if (debug)
  FIFO_getStats_debug(fifo);
  
}

void test_buffer(void){
  FIFOQueue test_fifo;
  
  FIFO_init(&test_fifo);
  int byte;

  for(int i = 0; i<BUFFER_SIZE; i++){
    FIFO_push(&test_fifo, i);
      }
  
  for(int i = 0; i<BUFFER_SIZE; i++){
     FIFO_pop(&test_fifo);
      }
  }
  

unsigned char *fifo_stats(FIFOQueue * fifo){
  static unsigned char fifo_stat[3] ={0};
  
    fifo_stat[0] = fifo->count;  // Assign count to fifo_stat[2]
    fifo_stat[1] = fifo->head;   // Assign head to fifo_stat[0]
    fifo_stat[2] = fifo->tail;   // Assign tail to fifo_stat[1]
    
    return fifo_stat;
  
}

void FIFO_getStats_debug(FIFOQueue *fifo){
    
    unsigned char *stats  = fifo_stats(fifo);
    unsigned char *b[3] = {"count,head,tail"};
    
    printf("%s \n  ", *(b));
    printf(" %d    ",*(stats));
    printf(" %d    ",*(stats+1));
    printf(" %d    ",*(stats+2));
     printf("\n ");
     FIFO_print_buffer(fifo);
}

void FIFO_print_buffer(FIFOQueue *fifo){
     for(int i = 0; i<BUFFER_SIZE; i++){
      printf(" ");
       printf(" %d  ", fifo->buffer[i]);
     }
        printf("\n ");
}