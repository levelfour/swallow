#include "memory.h"
#include "string.h"
#include "stdlib.h"

PHYSICAL_MEMORY_INFO pm_info;

inline uint get_kernel_size() {
	return (&_bss_end - &_text_start);
}

// get the number of memory blocks
inline uint get_system_memory_blocks() {
	return pm_info.system_memory_blocks;
}

// get the size of one memory block
inline uint get_system_memory_size() {
	return pm_info.system_memory_size;
}

#define KERNEL_BASE 0x00100000
void init_physical_memory(uint memory_size) {
	pm_info.system_memory_size		= memory_size;
	pm_info.system_memory_blocks 	= get_system_memory_size() / MEMORY_BLOCK_SIZE;
	pm_info.allocated_blocks		= get_system_memory_blocks();
	pm_info.free_blocks				= 0;
	pm_info.memory_map				= (uint*)(KERNEL_BASE + get_kernel_size);

	memset((void*)pm_info.memory_map, 0xff, pm_info.memory_map_size);
}

// set memory block (allocate)
inline void setbit(int bit) {
	pm_info.memory_map[bit / 32] = (1 << (bit % 32));
}

// clear memory block (free)
inline void clearbit(int bit) {
	pm_info.memory_map[bit / 32] &= ~(1 << (bit % 32));
}

// check memory block allocated or not
inline bool testbit(int bit) {
	unsigned int test;
	test = pm_info.memory_map[bit / 32] & (1 << (bit % 32));
	return (test > 0);
}

// set `block_number` the first free memory block
bool memory_find_front(uint *block_number) {
	uint bitmap_index;	// search memory blocks by 8-units
	uint bit_count;		// counter

	for(bitmap_index = 0;
		bitmap_index < pm_info.memory_map_size;
		bitmap_index++) {
		// 0xffffffff means this memory block index is all using
		if(pm_info.memory_map[bitmap_index] != 0xffffffff) {
			for(bit_count = 0; bit_count < sizeof(uint); bit_count++) {
				if(testbit(bit_count) == false) {
					*block_number = bitmap_index * sizeof(uint) * 8 + bit_count;
					return true;
				}
			}
		}
	}		

	return false;
}

// set bit `0` to already freed memory blocks
void init_freedmemory(void *base, uint size) {
	uint block_number = (uint)base / MEMORY_BLOCK_SIZE;
	int block_size = size / MEMORY_BLOCK_SIZE;
	int i;

	for(i = block_size; i > 0; i--) {
		clearbit(block_number);
		block_number--;
		pm_info.allocated_blocks--;
		pm_info.free_blocks++;
	}
}

// set bit `1` to already allocated memory blocks
void init_allocedmemory(void *base, uint size) {
	uint block_number = (uint)base / MEMORY_BLOCK_SIZE;
	int block_size = size / MEMORY_BLOCK_SIZE;
	int i;

	for(i = block_size; i > 0; i--) {
		setbit(block_number);
		block_number--;
		pm_info.allocated_blocks++;
		pm_info.free_blocks--;
	}
}

// allocate one memory block
void *alloc_memblock() {
	uint block_number;
	void *phys_addr;
	bool status;

	if(pm_info.free_blocks <= 0) return NULL;

	status = memory_find_front(&block_number);
	if(!status) return NULL;

	setbit(block_number);
	phys_addr = (void *)(block_number * MEMORY_BLOCK_SIZE);
	pm_info.allocated_blocks++;
	pm_info.free_blocks--;

	return phys_addr;
	
}

// free one memory block
void free_memblock(void *phys_addr) {
	uint block_number = (uint)phys_addr / MEMORY_BLOCK_SIZE;
	clearbit(block_number);
	pm_info.allocated_blocks--;
	pm_info.free_blocks++;
}
