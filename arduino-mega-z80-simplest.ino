//
// This is a very basic program which uses our abstracted Z80 class
// to execute a program.
//
// The program is hard-wired and just increments a single byte of RAM:
//
//     ld hl, output
//     xor a,a
//  loop:
//     inc a
//     ld (hl), a
//     jp loop
//  output:
//     db 00
//
// The program compiles to a few bytes, so we only pretend we have
// 16-bytes of RAM/ROM - and output the contents every ten cycles.
//
// After a few iterations, sufficient to prove it works, we stop the
// processor.
//
// Steve
//


#include "z80.h"

//
// our program.
//
unsigned char rom[16] = {  0x21, 0x09, 0x00, 0xaf, 0x3c, 0x77, 0xc3, 0x04, 0x00, 0x00 };
int rom_len = sizeof(rom)/sizeof(rom[0]);



//
// Our helper
//
Z80 cpu;

//
// RAM I/O function handler.
//
char ram_read(int address){
    if ( address >= rom_len )
        address = 0;

    return( rom[address]) ;
}

//
// RAM I/O function handler.
//
void ram_write(int address, char byte) {
    if ( address >= rom_len )
        address = 0;

    rom[address]=byte;
}

//
// I/O function handler.
//
void io_read(int address, char byte) {
    if ( address == 1 ) {
        return(Serial.read());
    }
    return 0;
}

//
// I/O function handler.
//
void io_write(int address, char byte) {
    if ( address == 1 ) {
        Serial.write(byte);
    }
}

//
// Setup routine: Called once.
//
void setup()
{
    Serial.begin(115200);

    // Setup callbacks: Memory I/O
    cpu.set_ram_read( ram_read );
    cpu.set_ram_write( ram_write );

    // Setup callbacks: I/O
    cpu.set_io_read( io_read );
    cpu.set_io_write( io_write );

    Serial.println( "Z80 configured; launching program.\n" );
}


//
// Loop function: Called forever.
//
void loop()
{
    //
    // Count the number of times we've pumped the Z80.
    //
    static int cycles = 0;

    //
    // We stop running after 1024 cycles.
    //
    // Arbitrary value.
    //
    if ( cycles > 1024 ) {

        // Log a message once we're done.
        static bool done = false;

        if ( ! done ) {
            Serial.println( "Z80 processor stopped; 1024 cycles ran.\n" );
            done = true;
        }
        return;
    }

    //
    // Step the CPU.
    //
    cpu.Tick();

    //
    // Dump the RAM every ten cycles.
    //
    if ( ( cycles % 10 ) == 0 ) {

        // Temporary buffer for a line of output.
        char tmp[64] = { '\0' };

        // Update the buffer with our RAM.
        for( int i = 0 ; i < rom_len; i++ ) {
            strcat( tmp, sprintf("%s %02X", tmp, rom[i]));
        }

        // Show to the serial console.
        Serial.println( tmp );
    }

    // We've run a tick.
    cycles++;
}
