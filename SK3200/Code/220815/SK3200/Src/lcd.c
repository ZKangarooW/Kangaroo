#include "lcd.h"


void write_addr_dat_n(unsigned char _addr, unsigned char _dat, unsigned char n);
void youhua(void);

uint8_t UP_Tab[]={0xee,0x24,0xba,0xb6,0x74,0xd6,0xde,0xa4,0xfe,0xf6};
uint8_t DOWNL_Tab[]={0x77,0X24,0x5d,0x6d,0x2e,0x6b,0x7b,0x25,0x7f,0x6f};
uint8_t DOWNR_Tab[]={0xee,0x48,0xba,0xda,0x5c,0xd6,0xf6,0x4a,0xfe,0xde};
uint8_t Tab[4]={0,0,0,0};
	
uint16_t rel_speed;//ÊµÊ±ËÙ¶È
int rel_time;//ÊµÊ±Ê±¼ä
uint16_t set_speed;//Éè¶¨ËÙ¶È
int set_time;//Éè¶¨Ê±¼ä
uint16_t dis_hour,dis_min;	//ÏÔÊ¾Ğ¡Ê±Êı£¬ÏÔÊ¾·ÖÖÓÊı
uint16_t dis_speed;	//ÏÔÊ¾ËÙ¶È
uint16_t	dis_speed_N;
uint16_t	dis_speed_F;
extern uint8_t LOCK_Status;//°²È«Ëø±êÖ¾ 1£ºËø¶¨ 0£º½âËø
extern uint8_t ADD_Mode;
extern uint8_t Run_Status;//
extern uint8_t Wise_Status;//µç»ú×ª¶¯·½Ïò 0£ºË³Ê±Õë 1£ºÄæÊ±Õë
extern uint8_t dis_flag_wise;
extern uint8_t dis_flag_time;
extern uint8_t time_disable;//¹Ø±Õ¼ÆÊ
int dis_rel_time;//ÊµÊ±Ê±¼ä±
// addr=seg*2-2
	
void LCD_Display()
{
	
	
	dis_speed=rel_speed;
		if(Run_Status==0)
		{
			dis_speed=0;
		}
		else
		{
			if(ADD_Mode==4)
				dis_speed=set_speed;
			else if(ADD_Mode==3)
				dis_speed=0;
			else
			{
				dis_speed_N=rel_speed;
				if(ADD_Mode==1)
				{
					if(dis_speed_N>dis_speed_F)
				   dis_speed=dis_speed_N;
					else
					{
						dis_speed=dis_speed_F;
						dis_speed_N=dis_speed_F;
					}
				}
				
				if(ADD_Mode==0)
				{
					if(dis_speed_N<dis_speed_F)
				   dis_speed=dis_speed_N;
					else
					{
						dis_speed=dis_speed_F;
						dis_speed_N=dis_speed_F;
					}
				}
				
				
				
				dis_speed_F=dis_speed_N;

			}
   }
		
	 
	 
	 
	 
	 
	 
	youhua();
	//ÊµÊ±ËÙ¶ÈÏÔÊ¾
	if(dis_speed>999){	
	Tab[0]=0; Tab[1]=UP_Tab[dis_speed/100%10]; Tab[2]=UP_Tab[dis_speed/10%10]; Tab[3]=UP_Tab[dis_speed%10];}
		
	else if(dis_speed >99){
	Tab[0]=0; Tab[1]=UP_Tab[dis_speed/100];Tab[2]=UP_Tab[dis_speed/10%10];Tab[3]=UP_Tab[dis_speed%10];}
	
	else if(dis_speed >9){
	Tab[0]=0; Tab[1]=UP_Tab[0];Tab[2]=UP_Tab[dis_speed/10];Tab[3]=UP_Tab[dis_speed%10];}	
	
	else if(dis_speed>=0){
	Tab[0]=0; Tab[1]=UP_Tab[0];Tab[2]=UP_Tab[0];Tab[3]=UP_Tab[dis_speed%10];}		
		
	
	
	//Õı·´×ª±êÖ¾
	  Tab[0]=Tab[0]|0x01;
		if(Wise_Status ==0)
		{
			if(dis_flag_wise==0)
			{
			Tab[1]=Tab[1]|0x01;
			Tab[0]=Tab[0]|0x01;	
			}
			else
			{
			Tab[1]=Tab[1]&0xfe;
			Tab[0]=Tab[0]&0xfe;
			}
		}
		else
		{
		  	if(dis_flag_wise==0)
				{
			   Tab[2]=Tab[2]|0x01;
					Tab[0]=Tab[0]|0x01;	
				}
			else
			{
			Tab[2]=Tab[2]&0xfe;
				Tab[0]=Tab[0]&0xfe;
			}
		}
			
	
	write_addr_dat_n(46,Tab[0], 1);
	write_addr_dat_n(44,Tab[1], 1);
	write_addr_dat_n(42,Tab[2], 1);
	write_addr_dat_n(40,Tab[3], 1);
	
	
	dis_rel_time=rel_time;
			
					if(set_time-rel_time>0)
							dis_rel_time=dis_rel_time+60;
						if(rel_time==0)
							dis_rel_time=0;
	//ÊµÊ±Ê±¼äÏÔÊ¾
	if(rel_time>3599){
				if(Run_Status ==1)
		   	{
				
					
					if(( ADD_Mode==4)||( ADD_Mode==1))
					{
						
						 dis_hour=dis_rel_time/3600;dis_min=(dis_rel_time%3600/60);
					}
				}
				else
					 dis_hour=dis_rel_time/3600;dis_min=dis_rel_time%3600/60;
					
			}
	
	else if(rel_time>59){
		if(Run_Status ==1)
		   	{
					if(( ADD_Mode==4)||( ADD_Mode==1))
					{
						
	          dis_hour=0; dis_min=(dis_rel_time/60)+1;
					}
				}
				else
					dis_hour=0; dis_min=rel_time/60+1;
				}
	
	else if(rel_time>0){
	dis_hour=0;	dis_min=1;}

	else{
	dis_hour=0;	dis_min=0;}

	if(dis_hour>9)
	{
		Tab[0]=UP_Tab[dis_hour/10];
		Tab[1]=UP_Tab[dis_hour%10];
  	if(dis_min>9)
		{
			Tab[2]=UP_Tab[dis_min/10];
		  Tab[3]=UP_Tab[dis_min%10];
	  }
		else
		{
			Tab[2]=UP_Tab[0];
		  Tab[3]=UP_Tab[dis_min];
		}
	}
	else
	{
		Tab[0]=UP_Tab[0];
		Tab[1]=UP_Tab[dis_hour];
  	if(dis_min>9)
		{
			Tab[2]=UP_Tab[dis_min/10];
		  Tab[3]=UP_Tab[dis_min%10]; 
	  }
		else
		{
			Tab[2]=UP_Tab[0];
		  Tab[3]=UP_Tab[dis_min];
		}
	}
	//²»¼ÆÊ±£¬ÏÔÊ¾----
		if(time_disable)
	{
		Tab[0]=(Tab[0]&0x01)|0x10;
		Tab[1]=(Tab[1]&0x01)|0x10;
		Tab[2]=(Tab[2]&0x01)|0x10;
		Tab[3]=(Tab[3]&0x01)|0x10;
	}
	//Ê±¼äÍ¼±ê
	Tab[3]=Tab[3]|0x01;
	
	//Êµ¼ÊÊ±¼äÃ°ºÅ£¨ÉÏÃæ£©+Ê±ÖÓÍ¼°¸
	if(dis_flag_time)
	{
		Tab[1]=Tab[1]&0xfe;
		Tab[3]=Tab[3]&0xfe;
	}
	else
	{
		Tab[1]=Tab[1]|0x01;
		Tab[3]=Tab[3]|0x01;
	}
	
	
	
	write_addr_dat_n(54,Tab[0], 1);
	write_addr_dat_n(52,Tab[1], 1);
	write_addr_dat_n(50,Tab[2], 1);
	write_addr_dat_n(48,Tab[3], 1);
	
	
	//Éè¶¨ËÙ¶È
	if(set_speed>999){	
	Tab[0]=DOWNR_Tab[set_speed/1000]; Tab[1]=DOWNR_Tab[set_speed/100%10]; Tab[2]=DOWNR_Tab[set_speed/10%10]; Tab[3]=DOWNR_Tab[set_speed%10];}
		
	else if(set_speed >99){
	Tab[0]=DOWNR_Tab[0]; Tab[1]=DOWNR_Tab[set_speed/100];Tab[2]=DOWNR_Tab[set_speed/10%10];Tab[3]=DOWNR_Tab[set_speed%10];}
	
	else if(set_speed >9){
	Tab[0]=DOWNR_Tab[0]; Tab[1]=DOWNR_Tab[0];Tab[2]=DOWNR_Tab[set_speed/10];Tab[3]=DOWNR_Tab[set_speed%10];}	
	
	else if(set_speed>=0){
	Tab[0]=DOWNR_Tab[0]; Tab[1]=DOWNR_Tab[0];Tab[2]=DOWNR_Tab[0];Tab[3]=DOWNR_Tab[set_speed%10];}		
		
	Tab[3]=Tab[3]|0x01;//rpmÎÄ±¾ÏÔÊ¾
	
	Tab[0]=0;
	write_addr_dat_n(26,Tab[0], 1);
	write_addr_dat_n(28,Tab[1], 1);
	write_addr_dat_n(30,Tab[2], 1);
	write_addr_dat_n(32,Tab[3], 1);
	
	//Éè¶¨Ê±¼äÏÔÊ¾
	if(set_time>3599){
	dis_hour=set_time/3600;dis_min=set_time%3600/60;}
	
	else if(set_time>59){
	dis_hour=0; dis_min=set_time/60; }
	else{
	dis_hour=0;	dis_min=0;}

	if(dis_hour>9)
	{
		Tab[0]=DOWNL_Tab[dis_hour/10];
		Tab[1]=DOWNL_Tab[dis_hour%10];
  	if(dis_min>9)
		{
			Tab[2]=DOWNL_Tab[dis_min/10];
		  Tab[3]=DOWNL_Tab[dis_min%10];
	  }
		else
		{
			Tab[2]=DOWNL_Tab[0];
		  Tab[3]=DOWNL_Tab[dis_min];
		}
	}
	else
	{
		Tab[0]=DOWNL_Tab[0];
		Tab[1]=DOWNL_Tab[dis_hour];
  	if(dis_min>9)
		{
			Tab[2]=DOWNL_Tab[dis_min/10];
		  Tab[3]=DOWNL_Tab[dis_min%10]; 
	  }
		else
		{
			Tab[2]=DOWNL_Tab[0];
		  Tab[3]=DOWNL_Tab[dis_min];
		}
	}
	
	if(time_disable)
	{
		Tab[0]=(Tab[0]&0x80)|0x08;
		Tab[1]=(Tab[1]&0x80)|0x08;
		Tab[2]=(Tab[2]&0x80)|0x08;
		Tab[3]=(Tab[3]&0x80)|0x08;
	}
		
	
	Tab[3]=Tab[3]|0x80;//Éè¶¨Ê±¼äminÎÄ±¾ÏÔÊ¾
	
	
	//Éè¶¨Ê±¼äÃ°ºÅ£¨ÏÂÃæ£©
	Tab[1]=Tab[1]|0x80;
	
	
	
	write_addr_dat_n(0,Tab[0], 1);
	write_addr_dat_n(2,Tab[1], 1);
	write_addr_dat_n(4,Tab[2], 1);
	write_addr_dat_n(6,Tab[3], 1);
	
	
	//Ëø¶¨Í¼°¸
	if(LOCK_Status)
	write_addr_dat_n(18,0x01, 1);
	else
	write_addr_dat_n(18,0x00, 1);	
	
	
	
}

//ÏÔÊ¾ÓÅ»¯
void youhua(void)
{
	if(rel_speed <set_speed )
	{
		if((set_speed-rel_speed)<2)
		{
		dis_speed=set_speed;
			ADD_Mode=4;
		}
		
	}
	else
	{
		if((rel_speed-set_speed)<2)
		{
			dis_speed=set_speed;
			ADD_Mode=4;
		}
	}
	
}
