#include "stdafx.h"
#include "HWControl.h"
#include "stdio.h"
#include "windows.h"
#include "mmsystem.h"

#pragma comment(lib,"winmm.lib")
BOOL isLocalSound = false;

int freq_list_basic[7]={523,575,659,698,784,880,988};
int freq_list[8]={0,523,575,659,698,784,880,988};
char tone_list[7][2] = {{'D','o'}, {'R','a'},{'M','i'},{'F','a'},{'S','o'},{'L','a'},{'X','i'}};
float flag=1;
int aliasI = 0;

float beat = 125;

int music1[][2]={
	{2,1},{3,1},{4,1},{5,1},{6,1},{6,1},{2,2},{1,2},{6,1},{2,1},{6,1},{5,1},{4,1},{3,1},
	{2,1},{3,1},{4,1},{5,1},{6,1},{5,1},{4,1},{3,1},{2,1},{3,1},{4,1},{3,1},{2,1},{2,1},{3,1},
	{2,1},{3,1},{4,1},{5,1},{6,1},{2,2},{1,2},{6,1},{2,1},{6,1},{5,1},{4,1},{3,1},
	{2,1},{3,1},{4,1},{5,1},{6,1},{5,1},{4,1},{3,1},{4,1},{5,1},{6,1},
	
	{1,2},{2,2},{6,1},{5,1},{6,1},
	
	{5,1},{6,1},{1,2},{2,2},{6,1},{5,1},{6,1},{5,1},{6,1},{5,1},{4,1},{3,1},{1,1},{2,1},
	{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{2,1},{5,1},{6,1},{1,2},{2,2},{6,1},{5,1},{6,1},
	{5,1},{6,1},{1,2},{2,2},{6,1},{5,1},{6,1},{5,1},{6,1},{5,1},{4,1},{3,1},{1,1},{2,1},
	{1,1},{2,1},{3,1},{4,1},{5,1},{6,1},{2,1},{5,1},{6,1},{1,2},{2,2},{6,1},{5,1},{6,1},
	
	{5,1},{6,1},{1,2},{2,2},{6,1},{5,1},{6,1},
	{2,2},{3,2},{4,2},{3,2},{2,2},{1,2},{6,1},{5,1},{6,1},{5,1},{4,1},{3,1},{1,1},{2,1}
};

int ttt3[]={
	1,1,1,1,2,1,1,2,2,1,1,1,1,
	1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,2,1,1,2,2,2,2,
	1,1,1,1,2,
	1,1,1,1,1,1,2,1,1,1,1,1,1,2,
	1,1,1,1,1,1,2,1,1,1,1,1,1,2,
	1,1,1,1,1,1,2,1,1,1,1,1,1,2,
	1,1,1,1,1,1,2,1,1,1,1,1,1,2,
	1,1,1,1,1,1,2,
	1,1,1,1,1,1,2,1,1,1,1,1,1,2,
	2
};

int music2[156][2]={{0,0},{0,0},{0,0},{6,1},{7,1},{1,2},{7,1},{1,2},{3,2},
{7,1},{7,1},{7,1},{3,1},{3,1},{6,1},{5,1},{6,1},{1,2},
{5,1},{5,1},{5,1},{3,1},{4,1},{3,1},{4,1},{1,2},{3,1},
{3,1},{0,0},{1,2},{1,2},{1,2},{7,1},{4,1},{4,1},{7,1},
{7,1},{7,1},{0,0},{6,1},{7,1},{1,2},{7,1},{1,2},{3,2},
{7,1},{7,1},{7,1},{3,1},{3,1},{6,1},{5,1},{6,1},{1,2},
{5,1},{5,1},{5,1},{2,1},{3,1},{4,1},{1,2},{7,1},{7,1},
{1,2},{1,2},{2,2},{2,2},{3,2},{1,2},{1,2},{1,2},{1,2},
{7,1},{6,1},{6,1},{7,1},{5,1},{6,1},{6,1},{6,1},{1,2},
{2,2},{3,2},{2,2},{3,2},{5,2},{2,2},{2,2},{2,2},{5,1},
{5,1},{1,2},{7,1},{1,2},{3,2},{3,2},{3,2},{3,2},{3,2},
{6,1},{7,1},{1,2},{7,1},{2,2},{2,2},{1,2},{5,1},{5,1},
{5,1},{4,2},{3,2},{2,2},{1,2},{3,2},{3,2},{3,2},{3,2},
{6,2},{6,2},{5,2},{5,2},{3,2},{2,2},{1,2},{1,2},{0,0},
{1,2},{2,2},{1,2},{2,2},{2,2},{5,2},{3,2},{3,2},{3,2},
{3,2},{6,2},{6,2},{5,2},{5,2},{3,2},{2,2},{1,2},{1,2},
{0,0},{1,2},{2,2},{1,2},{2,2},{2,2},{7,1},{6,1},{6,1},
{6,1},{6,1},{7,1}};

float ttt2[]={  
		1,1,1,0.5,0.5,1+0.5,0.5,1,1,1,1,1,0.5,0.5,
		1+0.5,0.5,1,1,1,1,1,1,1+0.5,0.5,1,1, 
		1,1,0.5,0.5,0.5,0.5,1+0.5,0.5,1,1,1,1,1,0.5,0.5,
		1+0.5,0.5,1,1,1,1,1,0.5,0.5,1+0.5,0.5,1,1,
		1,1,1,0.5,0.5,1,0.5,0.25,0.25,0.25,0.5,0.5,0.5,0.5,0.25,0.5,1,
		0.5,0.5,0.5,0.5,1,1,1,1,1,0.5,0.5,1+0.5,0.5,1,1,
		1,1,1,0.5,0.5,1.5,0.5,1,1,1,1,1,1,
		0.5,0.5,1,1,0.5,0.5,1.5,0.25,0.5,1,1,1,1,1,
		1,1,1,1,1,1,1,1,0.5,0.5,1,1,0.5,0.5,
		1,0.5,0.5,1,1,1,1,1,1,1,1,1,1,
		0.5,0.5,1,1,0.5,0.5,1,0.5,0.25,0.5,1,1,1,1,0.5,0.5
};

int get_div_ratio(int freqnum,float flag)
{
	if (freqnum==0){
		return 0;
	}
	float tmp;
	float real_freq=freq_list[freqnum]*flag;
	tmp=BASEFREQ/real_freq+0.5;
	return (int)tmp;
}

void play_music(int music_num)
{
	if(music_num==1){
		int n=135;
		for(int i=0;i<n;i++){
			int div_ratio=get_div_ratio(music1[i][0],music1[i][1]);
			set_freq_dividing_ratio(div_ratio,(int)(200*ttt3[i]));
		}
	}
	if(music_num==2){
		int n=156;
		for(int i=0;i<n;i++){
			int div_ratio=get_div_ratio(music2[i][0],music2[i][1]);
			set_freq_dividing_ratio(div_ratio,(int)(375*ttt2[i]));
		}
	}
}
void play_one_tone(int freqnum,float flag)
{
	//printf("\b%c%c\n",tone_list[freqnum-1][0],tone_list[freqnum-1][1]);
	int div_ratio = get_div_ratio(freqnum, flag);
	if (isLocalSound){
		if(flag < 1) flag = 0;
		play_one_toneL('a'+freqnum-1 + flag*7);
	}else{
		set_freq_dividing_ratio(div_ratio,beat);
	}
}

void play_one_toneL(char c){

	char cmd[100];
	sprintf(cmd, "open sound\\%c.mp3 alias s%d", c, aliasI);
	mciSendString(cmd,NULL,0,NULL);

	sprintf(cmd, "play s%d", aliasI);
	mciSendString(cmd,NULL,0,NULL);

	sprintf(cmd, "close s%d",(aliasI + 1)%9);
	mciSendString(cmd,NULL,0,NULL);


	aliasI = (aliasI + 1)%9;
}

BOOL init8254()
{
	return Init9054();
}

void set_freq_dividing_ratio(int ratio,int time)
{
	if(ratio!=0){
		IO8bWrite(P8254MODE,0x14);//0x03
		char input = (char)(ratio);
//		printf(" ��Ƶϵ��Ϊ: %d\n",(int)ratio);
		IO8bWrite(P8254A,input);
	}
	Sleep(time);
	IO8bWrite(P8254MODE,0x10);
}

void delay(int nms)
{
	Sleep(nms);
	return;   
}

void setBeat(float b){
	beat = b;
}

void setRhythm(bool rhythm){
	if(rhythm){
		for(int i = 1; i < 8; i++){
			freq_list[i] = freq_list_basic[i-1];
		}
	}else{
		for(int i = 0; i < 7; i++){
			freq_list[i] = freq_list_basic[i];
		}
		freq_list[7] = 1109;
	}
}