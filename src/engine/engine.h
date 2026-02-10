#ifndef ENGINE_H
#define ENGINE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct Engine {
    uint64_t tick;
    int tickrate; // ticks per second
    int tick_delta; // ms
    uint64_t last_tick_time;
    uint64_t start_time;
    
    uint8_t is_running;
    uint8_t paused;
    uint8_t headless;
} Engine;

Engine new_engine(int rate);
void start_engine(Engine *e);
void tick_engine(Engine *e);
bool can_engine_tick(Engine *e);
bool engine_running(Engine *e);
void stop_engine(Engine *e);
void kill_engine(Engine *e);

#endif