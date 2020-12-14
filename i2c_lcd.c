#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#define I2C_BUS "/dev/i2c-1"
#define I2C_ADDR 0x27

int i2cFile;

void i2c_start()
{
    if ((i2cFile = open(I2C_BUS, O_RDWR)) < 0)
    {
        printf("Error failed to open I2C bus [%s].\n", I2C_BUS);
        exit(-1);
    }
    // set the I2C slave address for all subsequent I2C device transfers
    if (ioctl(i2cFile, I2C_SLAVE, I2C_ADDR) < 0)
    {
        printf("Error failed to set I2C address [%s].\n", I2C_ADDR);
        exit(-1);
    }
}

void i2c_stop() { close(i2cFile); }

void i2c_send_byte(unsigned char data)
{
    unsigned char byte[1];
    byte[0] = data;
    write(i2cFile, byte, sizeof(byte));
    usleep(1000);
}

void i2c_init()
{
    usleep(15000);            
    i2c_send_byte(0b00110100); // D7=0, D6=0, D5=1, D4=1, RS,RW=0 EN=1
    i2c_send_byte(0b00110000); // D7=0, D6=0, D5=1, D4=1, RS,RW=0 EN=0
    usleep(4100);             
    i2c_send_byte(0b00110100); 
    i2c_send_byte(0b00110000); 
    usleep(100);               
    i2c_send_byte(0b00110100);
    i2c_send_byte(0b00110000); // 8-bit mode init complete
    usleep(4100);              
    i2c_send_byte(0b00100100);
    i2c_send_byte(0b00100000); // switched now to 4-bit mode

    // 4-bit mode initialization complete. Now configuring the function set 
    usleep(40);                
    i2c_send_byte(0b00100100); 
    i2c_send_byte(0b00100000); 
    i2c_send_byte(0b10000100); 
    i2c_send_byte(0b10000000); // D3=2lines, D2=char5x8

    
    // Next turn display off                                                
    usleep(40);                
    i2c_send_byte(0b00000100); 
    i2c_send_byte(0b00000000); 
    i2c_send_byte(0b10000100); 
    i2c_send_byte(0b10000000); // D3=1 D2=display_off, D1=cursor_off, D0=cursor_blink


    // Display clear, cursor home 
    usleep(40);                
    i2c_send_byte(0b00000100); 
    i2c_send_byte(0b00000000);
    i2c_send_byte(0b00010100); 
    i2c_send_byte(0b00010000); // D0=display_clear

   
    // Set cursor direction      
    usleep(40);             
    i2c_send_byte(0b00000100); 
    i2c_send_byte(0b00000000);
    i2c_send_byte(0b01100100); 
    i2c_send_byte(0b01100000); // print left to right

  
    // Turn on the display
    usleep(40);                
    i2c_send_byte(0b00000100); 
    i2c_send_byte(0b00000000); 
    i2c_send_byte(0b11100100); 
    i2c_send_byte(0b11100000); // D3=1 D2=display_on, D1=cursor_on, D0=cursor_blink

    sleep(1);
}

void *main_lcd()
{
    i2c_start();

    // Print Start  
    i2c_send_byte(0b01001101);
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); // send 0101=5 = 0x45 = 'E'

    i2c_send_byte(0b01001101); 
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b00011101); 
    i2c_send_byte(0b00011001); // send 0001=1 = 0x41 ='A'

    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); 
    i2c_send_byte(0b00101101); 
    i2c_send_byte(0b00101001); // send 0010=2 = 0x52 ='R'

    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); 
    i2c_send_byte(0b01001101); 
    i2c_send_byte(0b01001001); // send 0100=4 = 0x54 ='T'

    i2c_send_byte(0b01001101); 
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b10001101); 
    i2c_send_byte(0b10001001); // send 1000=8 = 0x48 ='H'

    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); 
    i2c_send_byte(0b00011101); 
    i2c_send_byte(0b00011001); // send 0001=1 = 0x51 ='Q'

    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); 
    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); // send 0101=5 = 0x55 ='U'

    i2c_send_byte(0b01001101); 
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b00011101); 
    i2c_send_byte(0b00011001); // send 0001=1 = 0x41 ='A'

    i2c_send_byte(0b01001101); 
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b10111101); 
    i2c_send_byte(0b10111001); // send 1011=11 = 0x4B ='K'

    i2c_send_byte(0b01001101);
    i2c_send_byte(0b01001001); 
    i2c_send_byte(0b01011101); 
    i2c_send_byte(0b01011001); // send 0101=5 = 0x45 ='E'

    i2c_stop();
}