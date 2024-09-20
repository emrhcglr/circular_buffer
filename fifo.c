// FIFO ADD
#include "fifo.h"


void FIFO_init(FIFOQueue *fifo) {
    
    for(int i = 0; i<BUFFER_SIZE-1; i++)
        fifo->buffer[i] =0;
    fifo->head = 0;         // Point head to the start of the buffer
    fifo->tail = 0;         // Point tail to the start of the buffer
    fifo->count = 0;                    // Initialize count to 0
}

unsigned char FIFO_push(FIFOQueue *fifo, unsigned char byte){
  while(fifo->count == BUFFER_SIZE){
        // Queue is full, wait for space to open up
        // Implement your own waiting mechanism or block here
        printf("buffer is full\n");
        
        
    return 1;
  }
   
    fifo->buffer[fifo->head] = byte;
  
    fifo->head =(fifo->head+1) & FIFO_MASK; // it wraps around the buffer turns to zero again 
    //This is because 128 in binary is 10000000, and when ANDed with 01111111 (which is 0x7F), it results in 00000000 (i.e., 0).
    
    fifo->count++;
    FIFO_getStats_debug(fifo);
    return 0;
   }

unsigned char FIFO_pop(FIFOQueue *fifo){
    
  if (fifo->count==0){
    // fifo is empty  nothing to send.
    printf("buffer is empty");
    return 1;
  }

  unsigned char byte = fifo->buffer[fifo->tail];
  fifo->buffer[fifo->tail] = 0;
  fifo->tail = (fifo->tail+1) & FIFO_MASK;
  
  fifo->count--;
  FIFO_getStats_debug(fifo);
  return byte;
  
}

void test_buffer(void){
  FIFOQueue test_fifo;
  
  FIFO_init(&test_fifo);
  int byte;

  for(int i = 0; i<BUFFER_SIZE; i++){
    FIFO_push(&test_fifo, i);
      }
  
  for(int i = 0; i<BUFFER_SIZE; i++){
     byte = FIFO_pop(&test_fifo);
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
    
/*void test_pop(FIFOQueue *fifo){
    unsigned byte = FIFO_pop(&fifoo);
     
     for(int i = 0; i<BUFFER_SIZE; i++)
       printf(" %d\n ", fifo->buffer[i]);
        printf("\n ");
}
  */  