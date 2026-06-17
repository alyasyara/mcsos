#ifndef MCSOS_BLOCK_H
#define MCSOS_BLOCK_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define MCS_BLOCK_SECTOR_SIZE 512u
#define MCS_BLOCK_CACHE_SIZE  16u
#define MCS_BLOCK_NAME_MAX    32u

typedef enum {
    MCS_BLOCK_OK = 0,
    MCS_BLOCK_EINVAL = -1,
    MCS_BLOCK_ENOSPC = -2,
    MCS_BLOCK_EIO = -3,
    MCS_BLOCK_ENOTFOUND = -4
} mcs_block_status_t;

typedef struct mcs_block_device mcs_block_device_t;

typedef int (*mcs_block_read_fn)(
    mcs_block_device_t *dev,
    uint64_t sector,
    void *buffer,
    size_t count);

typedef int (*mcs_block_write_fn)(
    mcs_block_device_t *dev,
    uint64_t sector,
    const void *buffer,
    size_t count);

struct mcs_block_device {
    char name[MCS_BLOCK_NAME_MAX];
    uint64_t sector_count;
    uint32_t sector_size;

    mcs_block_read_fn read;
    mcs_block_write_fn write;

    void *driver_data;
};

typedef struct {
    bool valid;
    bool dirty;

    uint64_t sector;
    uint8_t data[MCS_BLOCK_SECTOR_SIZE];
} mcs_cache_entry_t;

typedef struct {
    mcs_block_device_t *device;

    mcs_cache_entry_t entries[MCS_BLOCK_CACHE_SIZE];
    uint32_t next_victim;
} mcs_buffer_cache_t;

void mcs_block_device_init(
    mcs_block_device_t *dev,
    const char *name,
    uint64_t sector_count,
    mcs_block_read_fn read_fn,
    mcs_block_write_fn write_fn,
    void *driver_data);

void mcs_buffer_cache_init(
    mcs_buffer_cache_t *cache,
    mcs_block_device_t *device);

int mcs_buffer_cache_read(
    mcs_buffer_cache_t *cache,
    uint64_t sector,
    void *buffer);

int mcs_buffer_cache_write(
    mcs_buffer_cache_t *cache,
    uint64_t sector,
    const void *buffer);

int mcs_buffer_cache_flush(
    mcs_buffer_cache_t *cache);

#endif
