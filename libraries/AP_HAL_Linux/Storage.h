

#ifndef __AP_HAL_LINUX_STORAGE_H__
#define __AP_HAL_LINUX_STORAGE_H__

#include <AP_HAL.h>
#include "AP_HAL_Linux_Namespace.h"

#define LINUX_STORAGE_SIZE 4096
#define LINUX_STORAGE_MAX_WRITE 512
#define LINUX_STORAGE_LINE_SHIFT 9
#define LINUX_STORAGE_LINE_SIZE (1<<LINUX_STORAGE_LINE_SHIFT)
#define LINUX_STORAGE_NUM_LINES (LINUX_STORAGE_SIZE/LINUX_STORAGE_LINE_SIZE)

class Linux::LinuxStorage : public AP_HAL::Storage 
{
public:
    LinuxStorage() :
	_fd(-1),
	_dirty_mask(0)
	{}
    void init(void* machtnichts) {}
    void read_block(void *dst, uint16_t src, size_t n);
    void write_block(uint16_t dst, const void* src, size_t n);

    void _timer_tick(void);

private:
    uint32_t fptr;
    uint32_t write(uint16_t fd, uint8_t *Buff, uint16_t NumBytes);
    uint32_t read(uint16_t fd, uint8_t *Buff, uint16_t NumBytes);
    uint32_t lseek(uint16_t fd,uint32_t offset,uint16_t whence);
    uint32_t open(const char *Path, uint16_t Flags, uint16_t perm);
    uint32_t open(const char *Path, uint16_t Flags);
    void close(uint16_t fd);
    uint32_t fsync(uint16_t fd);
    int _fd;
    volatile bool _initialised;
    void _storage_create(void);
    void _storage_open(void);
    void _mark_dirty(uint16_t loc, uint16_t length);
    uint8_t _buffer[LINUX_STORAGE_SIZE];
    volatile uint32_t _dirty_mask;
};

#endif // __AP_HAL_LINUX_STORAGE_H__
