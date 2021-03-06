#ifndef __UTI_H__
#define __UTI_H__

#include <time.h>
#include <stdio.h>
#include <stdlib.h>


////////////////////////////////////////////////////////////////////////////////
/// STAŁE
////////////////////////////////////////////////////////////////////////////////
#define INF 2147483647
#define MINF -2147483647
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
/// POMIAR CZASU
////////////////////////////////////////////////////////////////////////////////
typedef struct Timer
{
    clock_t start_time, stop_time;
    double passed_time;
} Timer;
////////////////////////////////////////////////////////////////////////////////
void timer_start(Timer * timer);
////////////////////////////////////////////////////////////////////////////////
void timer_stop(Timer * timer);
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
/// FUNKCJE POMOCNICZE
////////////////////////////////////////////////////////////////////////////////
int getlevel(const int max);
////////////////////////////////////////////////////////////////////////////////
int * int_get_rand_arr(const int size, const int max);
////////////////////////////////////////////////////////////////////////////////
void int_print_arr(int * arr, const int size);
////////////////////////////////////////////////////////////////////////////////
#endif