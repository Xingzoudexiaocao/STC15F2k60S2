//1、用导线将MCU的MCU_IO1---MCU_IO4分别连接到16*16LED的A0、A1、A2、A3。
//2、用导线将MCU的SDA、SCL、PWM0分别连接到16*16LED的SHCR、STCP、DS。
#include	<reg51.h>
unsigned char code  table0[] = {
//--  文字:  刘  --
//--  宋体12;  此字体下对应的点阵为：宽x高=16x16   -- 
0x00,0x00,0x04,0x40,0x08,0x41,0x90,0x49,0xF0,0x48,0x60,0x48,0x50,0x48,0x48,0x48,
0x84,0x48,0x80,0x48,0xFC,0x48,0x00,0x49,0x20,0x40,0x30,0x40,0x00,0x40,0x00,0x00
};

sbit	SHCP = P1^1;
sbit	STCP = P1^2;
sbit	DS   = P1^3;


void WriteByte(char dat)          //写一个字节的数据 
{
	char i;	
	for(i=0;i<8;i++)          //循环8次把编码传给锁存器 	
	{
		dat=dat>>1;       //右移一位，取出该字节的最低位 
		DS=CY;            //将该字节的最低位传给R
		SHCP=0;          //将数据移入595，上升沿 
		SHCP=1;                    
	}     
}
void display(unsigned char *p)
{
  int x,num,i;
  for(num=0;num<16;num++)
  { 
     P0=num;          //选择对应的行
     WriteByte(*(p+2*num+1)); 
	 WriteByte(*(p+2*num));   	 	
     STCP=1;         					
          						
	 STCP=0; 
	 for(x=0;x<40;x++);
  }

}

int main(void)
{	
	while(1)
	{	
	  
	    display(table0);
        
	}           
}

