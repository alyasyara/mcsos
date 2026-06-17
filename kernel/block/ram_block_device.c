#include "mcsos/block.h"

#define MCS_RAM_BLOCK_MAX_SECTORS 1024u

typedef struct {
    uint8_t storage[
        MCS_RAM_BLOCK_MAX_SECTORS *
        MCS_BLOCK_SECTOR_SIZE];
} mcs_ram_block_data_t;

static void mcs_memcpy(
    void *dst,
    const void *src,
    size_t n)
{
    size_t i;
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    for (i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

static void mcs_memset(
    void *dst,
    int value,
    size_t n)
{
    size_t i;
    uint8_t *d = (uint8_t *)dst;

    for (i = 0; i < n; ++i) {
        d[i] = (uint8_t)value;
    }
}

int mcs_ram_block_read(
    mcs_block_device_t *dev,
    uint64_t sector,
    void *buffer,
    size_t count)
{
    mcs_ram_block_data_t *ram;

    if (dev == 0 || buffer == 0) {
        return MCS_BLOCK_EINVAL;
    }

    if (sector + count > dev->sector_count) {
        return MCS_BLOCK_EIO;
    }

    ram = (mcs_ram_block_data_t *)
        dev->driver_data;

    mcs_memcpy(
        buffer,
        &ram->storage[
            sector *
            MCS_BLOCK_SECTOR_SIZE],
        count *
        MCS_BLOCK_SECTOR_SIZE);

    return MCS_BLOCK_OK;
}

int mcs_ram_block_write(
    mcs_block_device_t *dev,
    uint64_t sector,
    const void *buffer,
    size_t count)
{
    mcs_ram_block_data_t *ram;

    if (dev == 0 || buffer == 0) {
        return MCS_BLOCK_EINVAL;
    }

    if (sector + count > dev->sector_count) {
        return MCS_BLOCK_EIO;
    }

    ram = (mcs_ram_block_data_t *)
        dev->driver_data;

    mcs_memcpy(
        &ram->storage[
            sector *
            MCS_BLOCK_SECTOR_SIZE],
        buffer,
        count *
        MCS_BLOCK_SECTOR_SIZE);

    return MCS_BLOCK_OK;
}

void mcs_ram_block_setup(
    mcs_block_device_t *dev,
    mcs_ram_block_data_t *storage,
    uint64_t sectors)
{
    if (storage == 0 ||
        dev == 0) {
        return;
    }

    mcs_memset(
        storage,
        0,
        sizeof(*storage));

    mcs_block_device_init(
        dev,
        "ramblk0",
        sectors,
        mcs_ram_block_read,
        mcs_ram_block_write,
        storage);
}
