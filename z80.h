/*
 *  This class abstracts the usage of the retroshield to drive a Z80.
 *
 *  The intention is that you can instantiate an instance of this class
 *  and ensure it operates but keep the details of RAM & I/O inside your
 *  main-sketch.
 *
 *  You provide a callback to be invoked when RAM is read/written, and
 *  they are missing you'll end up with a free-running system.
 *
 */

#ifndef _Z80_DRIVER
#define _Z80_DRIVER 1


/*
 * Signatures for our callback functions.
 *
 */
typedef char (*memoryRead)(int address);
typedef void (*memoryWrite)(int address, char byte);
typedef char (*ioread)(int address);
typedef void (*iowrite)(int address, char byte);




class Z80
{

public:

    // constructor & destructor
    Z80();
    ~Z80();

    // reset
    void Reset();

    // run a single cycle
    void Tick();

    // set callbacks
    void set_ram_read(memoryRead cb)
    {
        m_on_memory_read = cb;
    };
    void set_ram_write(memoryWrite cb)
    {
        m_on_memory_write = cb;
    };
    void set_io_read(ioread cb)
    {
        m_on_io_read = cb;
    };
    void set_io_write(iowrite cb)
    {
        m_on_io_write = cb;
    };


private:

    // pointers to callback functions
    memoryRead  m_on_memory_read;
    memoryWrite m_on_memory_write;
    ioread      m_on_io_read;
    iowrite     m_on_io_write;


};


#endif /* _Z80_DRIVER */
