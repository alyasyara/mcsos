#include "mcsos/block.h"

static void mcs_memcpy(void *dst, const void *src, size_t n)
{
    size_t i;
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    for (i = 0; i < n; ++i) {
        d[i] = s[i];
    }
}

static void mcs_memset(void *dst, int value, size_t n)
{
    size_t i;
    uint8_t *d = (uint8_t *)dst;

    for (i = 0; i < n; ++i) {
        d[i] = (uint8_t)value;
    }
}

void mcs_block_device_init(
    mcs_block_device_t *dev,
    const char *name,
    uint64_t sector_count,
    mcs_block_read_fn read_fn,
    mcs_block_write_fn write_fn,
    void *driver_data)
{
    size_t i = 0;

    if (dev == 0) {
        return;
    }

    mcs_memset(dev, 0, sizeof(*dev));

    if (name != 0) {
        while (name[i] != '\0' &&
               i < (MCS_BLOCK_NAME_MAX - 1u)) {
            dev->name[i] = name[i];
            ++i;
        }

        dev->name[i] = '\0';
    }

    dev->sector_count = sector_count;
    dev->sector_size = MCS_BLOCK_SECTOR_SIZE;
    dev->read = read_fn;
    dev->write = write_fn;
    dev->driver_data = driver_data;
}

void mcs_buffer_cache_init(
    mcs_buffer_cache_t *cache,
    mcs_block_device_t *device)
{
    if (cache == 0) {
        return;
    }

    mcs_memset(cache, 0, sizeof(*cache));
    cache->device = device;
}

static mcs_cache_entry_t *cache_find(
    mcs_buffer_cache_t *cache,
    uint64_t sector)
{
    uint32_t i;

    for (i = 0; i < MCS_BLOCK_CACHE_SIZE; ++i) {
        if (cache->entries[i].valid &&
            cache->entries[i].sector == sector) {
            return &cache->entries[i];
        }
    }

    return 0;
}

static mcs_cache_entry_t *cache_alloc(
    mcs_buffer_cache_t *cache)
{
    uint32_t i;

    for (i = 0; i < MCS_BLOCK_CACHE_SIZE; ++i) {
        if (!cache->entries[i].valid) {
            return &cache->entries[i];
        }
    }

    return &cache->entries[
        (cache->next_victim++) %
        MCS_BLOCK_CACHE_SIZE];
}

int mcs_buffer_cache_read(
    mcs_buffer_cache_t *cache,
    uint64_t sector,
    void *buffer)
{
    mcs_cache_entry_t *entry;

    if (cache == 0 ||
        cache->device == 0 ||
        buffer == 0) {
        return MCS_BLOCK_EINVAL;
    }

    entry = cache_find(cache, sector);

    if (entry == 0) {
        entry = cache_alloc(cache);

        if (cache->device->read(
                cache->device,
                sector,
                entry->data,
                1) != MCS_BLOCK_OK) {
            return MCS_BLOCK_EIO;
        }

        entry->valid = true;
        entry->dirty = false;
        entry->sector = sector;
    }

    mcs_memcpy(
        buffer,
        entry->data,
        MCS_BLOCK_SECTOR_SIZE);

    return MCS_BLOCK_OK;
}

int mcs_buffer_cache_write(
    mcs_buffer_cache_t *cache,
    uint64_t sector,
    const void *buffer)
{
    mcs_cache_entry_t *entry;

    if (cache == 0 || buffer == 0) {
        return MCS_BLOCK_EINVAL;
    }

    entry = cache_find(cache, sector);

    if (entry == 0) {
        entry = cache_alloc(cache);
        entry->valid = true;
        entry->sector = sector;
    }

    mcs_memcpy(
        entry->data,
        buffer,
        MCS_BLOCK_SECTOR_SIZE);

    entry->dirty = true;

    return MCS_BLOCK_OK;
}

int mcs_buffer_cache_flush(
    mcs_buffer_cache_t *cache)
{
    uint32_t i;

    if (cache == 0 ||
        cache->device == 0) {
        return MCS_BLOCK_EINVAL;
    }

    for (i = 0; i < MCS_BLOCK_CACHE_SIZE; ++i) {
        mcs_cache_entry_t *entry =
            &cache->entries[i];

        if (!entry->valid ||
            !entry->dirty) {
            continue;
        }

        if (cache->device->write(
                cache->device,
                entry->sector,
                entry->data,
                1) != MCS_BLOCK_OK) {
            return MCS_BLOCK_EIO;
        }

        entry->dirty = false;
    }

    return MCS_BLOCK_OK;
}
