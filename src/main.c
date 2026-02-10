#include "primitives.h"
#include "ui/window.h"
#include "engine/engine.h"
#include "utils/utils.h"
#include <stdio.h>

int main(int argc, char **argv) {
  int rate = 20;
  
  Engine engine = new_engine(rate);

  start_engine(&engine);
  
  while(engine_running(&engine)) {
    if(can_engine_tick(&engine)) {
      tick_engine(&engine);
    }
    if(engine.tick >= 80)
      kill_engine(&engine);
  }

  uint64_t end_time = current_time_ms();
  printf("Time ellipsed: %.02f ms.\n", (float)(end_time - engine.start_time)/1000);
  
  printf("Engine shutting down after %d ticks.\n", engine.tick);
  
  return 0;
}
