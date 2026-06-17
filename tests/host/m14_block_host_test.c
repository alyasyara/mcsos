#include "mcsos/block.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    uint8_t storage[1024 * MCS_BLOCK_SECTOR_SIZE];
} ram_storage_t;

extern int mcs_ram_block_read(
    mcs_block_device_t *dev,
    uint64_t sector,
    void *buffer,
    size_t count);

extern int mcs_ram_block_write(
    mcs_block_device_t *dev,
    uint64_t sector,
    const void *buffer,
    size_t count);

extern void mcs_ram_block_setup(
    mcs_block_device_t *dev,
    void *storage,
    uint64_t sectors);

static void test_device_rw(void)
{
    mcs_block_device_t dev;
    ram_storage_t storage;

    uint8_t write_buf[MCS_BLOCK_SECTOR_SIZE];
    uint8_t read_buf[MCS_BLOCK_SECTOR_SIZE];

    memset(write_buf, 0xAB, sizeof(write_buf));
    memset(read_buf, 0, sizeof(read_buf));

    mcs_ram_block_setup(&dev, &storage, 1024);

    assert(
        mcs_ram_block_write(
            &dev,
            0,
            write_buf,
            1) == MCS_BLOCK_OK);

    assert(
        mcs_ram_block_read(
            &dev,
            0,
            read_buf,
            1) == MCS_BLOCK_OK);

    assert(memcmp(
        write_buf,
        read_buf,
        sizeof(write_buf)) == 0);

    printf("[PASS] block read/write\n");
}

static void test_buffer_cache(void)
{
    mcs_block_device_t dev;
    ram_storage_t storage;
    mcs_buffer_cache_t cache;

    uint8_t write_buf[MCS_BLOCK_SECTOR_SIZE];
    uint8_t read_buf[MCS_BLOCK_SECTOR_SIZE];

    memset(write_buf, 0x55, sizeof(write_buf));
    memset(read_buf, 0, sizeof(read_buf));

    mcs_ram_block_setup(&dev, &storage, 1024);

    mcs_buffer_cache_init(
        &cache,
        &dev);

    assert(
        mcs_buffer_cache_write(
            &cache,
            5,
            write_buf) == MCS_BLOCK_OK);

    assert(
        mcs_buffer_cache_flush(
            &cache) == MCS_BLOCK_OK);

    assert(
        mcs_buffer_cache_read(
            &cache,
            5,
            read_buf) == MCS_BLOCK_OK);

    assert(memcmp(
        write_buf,
        read_buf,
        sizeof(write_buf)) == 0);

    printf("[PASS] buffer cache\n");
}

int main(void)
{
    test_device_rw();
    test_buffer_cache();

    printf(
        "[PASS] M14 block layer host tests passed\n");

    return 0;
}
