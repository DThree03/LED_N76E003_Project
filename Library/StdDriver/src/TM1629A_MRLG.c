#include "TM1629A_MRLG.h"

#include "Function_define.h"

/*****************************************************************************
* Marco typedefs
*****************************************************************************/
#define stb P10	
#define clk P00	
#define dio P01	
			
#define	stb_output P10_PushPull_Mode
#define	clk_output P00_PushPull_Mode
#define	dio_output P01_PushPull_Mode

#define PWM1 0x80
#define PWM2 0x81
#define PWM3 0x82
#define PWM4 0x83
#define PWM5 0x84
#define PWM6 0x85
#define PWM7 0x86
#define PWM8 0x87
#define Dis_ON  0x88
#define Dis_OFF 0x80

/*****************************************************************************
* Constant and static variable
*****************************************************************************/
//const unsigned char code Code7Seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x5F, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x00, 0x40};// 0-F, off, sign(17)

const unsigned char code Code7Seg[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x40, 0x00};// 0-F(0 - 19), sign(20), off(21)

//const unsigned char code Code7SegDOT[] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0xDF, 0xFC, 0xB9, 0xDE, 0xF9, 0xF1, 0x00, 0xC0};// 0-F, off, sign(17)

const unsigned char code seg_addr[8]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};//no bit of digital segments
//                       SG0  SG1  SG2  SG3  SG4  SG5  SG6  SG7  DVD  VCD  MP3  PLY  PAU  PBC  RET  DTS  DDD  CL1  CL2   //name   -|

static unsigned char buffer[16] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

/*****************************************************************************
* Static functions prototype
*****************************************************************************/
static void update();
static void setSeg(unsigned char addr, unsigned char num);
static void send(unsigned char data1);	
static void sendData(unsigned char addr, unsigned char data1);
static void sendCommand(unsigned char data1);
static void clear();
static void setPWM(unsigned char num);
/*****************************************************************************
* Public functions
*****************************************************************************/
void TM1629_Begin(void)
{
    stb_output;
    clk_output;
    dio_output;

    stb = 1;
    clk = 1;
    dio = 1;

    sendCommand(0x40); // Write data to display register
    sendCommand(Dis_OFF); // Display is off

    setPWM(PWM8);

    //  sendCommand(Dis_ON); // Display is on

    stb = 0;
    send(0xC0);
    clear();
    stb = 1;
}

void TM1629_CLEAR_ALL(void)
{
    stb = 1;
    clk = 1;
    dio = 1;

    sendCommand(0x40); // Write data to display register

    stb = 0;
    send(0xC0);
    clear();
    stb = 1;
}

void setNshowAllSeg(unsigned char buffernum[])
{
    unsigned char i=0;
    for (i = 0; i<16; i++){
        setSeg(i, buffernum[i]);
    }
    update();
}

void blinkSegwithLine(unsigned char line)
{
    switch(line)
    {
        case 1:
        {
            setSeg(2, 21);
            break;
        }
        case 2:
        {
            setSeg(4, 21);
            setSeg(5, 21);
            setSeg(6, 21);
            break;
        }
        case 3:
        {
            setSeg(7, 21);
            setSeg(8, 21);
            setSeg(9, 21);
            setSeg(10, 21);
            break;
        }
        case 4:
        {
            setSeg(12, 21);
            setSeg(13, 21);
            break;
        }
        case 5:
        {
            setSeg(14, 21);
            setSeg(15, 21);
            break;
        }
    }
	update();
}

/*****************************************************************************
* Static functions
*****************************************************************************/
static void setPWM(unsigned char PWM)
{
    sendCommand(0x40); // Write data to display register
    sendCommand(PWM | Dis_ON);
}

static void clear()
{
	unsigned char i=0;
	for (i=0; i<16; i++){
		buffer[i]=0x00;
	}
	update();
}

static void setSeg(unsigned char addr, unsigned char num)
{
	unsigned char i=0;
	if(addr < 8){
		for(i=0; i<8; i++){
			bitWrite(buffer[i*2], seg_addr[addr], bitRead(Code7Seg[num],i));
		}
	}
    else if((addr == 8) && (num != 21)){
        for(i=0; i<8; i++){
			bitWrite(buffer[i*2 + 1], seg_addr[addr - 8], bitRead(Code7Seg[num]|0x80,i));
		}
    }
	else if(addr < 16){
		for(i=0; i<8; i++){
			bitWrite(buffer[i*2 + 1], seg_addr[addr - 8], bitRead(Code7Seg[num],i));
		}
	}
}	

static void update()
{
    unsigned char i=0;
    sendCommand(0x44);	

    for (i=0; i<16; i++)
    {
        sendData(i, buffer[i]);
    }
}

/*********** mid level  **********/
static void sendData(unsigned char addr, unsigned char data1)
{
    stb =0;
    send(0xC0 | addr);
    send(data1);
    stb =1;
}

static void sendCommand(unsigned char data1)
{
  stb =0;
  send(data1);
  stb =1;
}

/************ low level **********/
static void send(unsigned char data1)
{
    unsigned char i; 
    nop;
    nop;	

    for (i = 0; i < 8; i++) {
        clk =0;
        nop;
        nop;
        if((data1&0x01)!=0)
        {
            dio=1;
        }
        else
        {
            dio=0;
        }
        nop;
        nop;
        clk =1;
        nop;
        data1 >>= 1;
    }
}
