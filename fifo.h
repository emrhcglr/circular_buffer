// Online C compiler to run C program online



#define BUFFER_SIZE 8  // Adjust as needed
#define FIFO_MASK BUFFER_SIZE-1

//#define CIRC_BBUF_DEF(x,y)                \
//    uint8_t x##_data_space[y];            \
//    circ_bbuf_t x = {                     \
//        .buffer = x##_data_space,         \
//        .head = 0,                        \
//        .tail = 0,                        \
//        .maxlen = y                       \
//    }


typedef struct {
    unsigned char buffer[BUFFER_SIZE];
    unsigned char head;
    unsigned char tail;
    unsigned int count;
    unsigned int byte_read;
} FIFOQueue;
void FIFO_print_buffer(FIFOQueue *fifo);
void FIFO_getStats_debug(FIFOQueue * fifo);
void FIFO_push(FIFOQueue *fifo, unsigned char byte);
void FIFO_pop(FIFOQueue *fifo);
void test_buffer(void);
void FIFO_init(FIFOQueue *fifo);
unsigned char * fifo_stats(FIFOQueue * fifo);