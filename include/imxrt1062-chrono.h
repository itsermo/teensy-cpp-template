#ifndef CHRONO_H
#define CHRONO_H
#include "imxrt1062.h"

#ifndef F_CPU_ACTUAL
#define F_CPU_ACTUAL 396000000
#endif

__attribute__((always_inline, unused))
inline void init_demcr() { ARM_DEMCR |= ARM_DEMCR_TRCENA; }

__attribute__((always_inline, unused))
inline void deinit_demcr() { ARM_DEMCR &= ~ARM_DEMCR_TRCENA; }

__attribute__((always_inline, unused))
inline void start_cpu_counter() { ARM_DWT_CTRL |= ARM_DWT_CTRL_CYCCNTENA; }

__attribute__((always_inline, unused))
inline void stop_cpu_counter() { ARM_DWT_CTRL &= ~ARM_DWT_CTRL_CYCCNTENA; }

__attribute__((always_inline, unused))
inline void reset_cpu_counter() { ARM_DWT_CYCCNT = 0; }

__attribute__((always_inline, unused))
inline uint32_t get_cpu_tick_count() { return ARM_DWT_CYCCNT; }

__attribute__((always_inline, unused))
inline void delay_ticks(volatile uint32_t num_ticks)
{
	reset_cpu_counter();
	start_cpu_counter();
	uint32_t end = get_cpu_tick_count() + num_ticks;
	while (1) {
        if (get_cpu_tick_count() >= end) break;
    }
	stop_cpu_counter();
}

__attribute__((always_inline, unused))
inline void delay_ns(uint32_t nsec)
{
    delay_ticks(((F_CPU_ACTUAL>>16) * nsec) / (1000000000UL>>16));
}

__attribute__((always_inline, unused))
inline void delay_us(uint32_t usec)
{
	delay_ticks(F_CPU_ACTUAL / 1000000 * usec);
}

__attribute__((always_inline, unused))
inline void delay_ms(uint32_t msec)
{
	delay_ticks(F_CPU_ACTUAL / 1000 * msec);
}

__attribute__((always_inline, unused))
inline void delay_s(uint32_t sec)
{
	delay_ticks(F_CPU_ACTUAL * sec);
}

#endif //CHRONO_H