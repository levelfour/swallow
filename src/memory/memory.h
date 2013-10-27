#ifndef __MEMORY_H
#define __MEMORY_H

#include "types.h"

typedef struct {
	uint system_memory_size;	// システムのメモリサイズ
	uint system_memory_blocks;	// システムのメモリブロック数
	uint allocated_blocks;		// 割り当て済みブロック数
	uint free_blocks;			// 未割り当てブロック数
	uint *memory_map;			// ビットマップ(0:未割り当て 1:割り当て済み)
	uint memory_map_size;		// ビットマップのサイズ
} PHYSICAL_MEMORY_INFO;

#define MEMORY_BLOCK_SIZE	0x1000

// defined in linker script (src/script/boot.ls)
extern uint _text_start;
extern uint _text_end;
extern uint _rodata_start;
extern uint _rodata_end;
extern uint _data_start;
extern uint _data_end;
extern uint _bss_start;
extern uint _bss_end;

extern PHYSICAL_MEMORY_INFO pm_info;

uint get_kernel_size();
uint get_system_memory_blocks();
uint get_system_memory_size();
void init_physical_memory(uint memory_size);
void setbit(int bit);
void clearbit(int bit);
bool testbit(int bit);
bool memory_find_front(uint *block_number);
void init_freedmemory(void *base, uint size);
void init_allocedmemory(void *base, uint size);
void *alloc_memblock();
void free_memblock(void *phys_addr);

#endif // __MEMORY_H
