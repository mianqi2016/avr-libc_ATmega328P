#include "ringBuffer.h"

int add(char c) {
  ring_pos_t next_head = (ring_head + 1) % RING_SIZE;
  if (next_head != ring_tail) {
    /* there is room */
    ring_data[ring_head] = c;
    ring_head = next_head;
    return 0;
    } else {
    /* no room left in the buffer */
    return -1;
  }
}

int remove(void) {
  if (ring_head != ring_tail) {
    int c = ring_data[ring_tail];
    ring_tail = (ring_tail + 1) % RING_SIZE;
    return c;
    } else {
    return -1;
  }
}
