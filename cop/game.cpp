#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "man.h"
#include "game.h"

using namespace std;


void game::HideCursor()
{//���ع��
    CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);    
}

void game::gotoxy(int x, int y)
{	//����һ������Ļ
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


ostream& operator<< (ostream&cout,const game& g)
{
    int i, j;
    for (i=1; i<=17; i++)
    {
        for (j=1; j<=17; j++)
        {
 			switch(g.map[i][j])
 			{
			case FREE:   cout<<"  "; break;
		    case WALL:   cout<<"��"; break;	
	    	case COP :   cout<<"��"; break; 
			case ENEMY:  cout<<"��"; break;  
			case UP_BULLET:   cout<<"��"; break;  
			case LEFT_BULLET: cout<<"��"; break; 
			case RIGHT_BULLET:cout<<"��"; break;   
			case DOWN_BULLET: cout<<"��"; break; 
			case PICKAXE: cout<<"��";break;
			case SHIELD:  cout<<"��";break;
			}
        }
        cout<<endl;
    } 	
    return cout;
}



void game::mapSign()
{
	switch(cop_ptr->face)
	{
		case 0:	map[cop_ptr->x][cop_ptr->y]= COP;break;
		case 1: map[cop_ptr->x][cop_ptr->y]= PICKAXE;break;
		case 2: map[cop_ptr->x][cop_ptr->y]= SHIELD;break;		
	}
	
	map[up_bullet_ptr->x][up_bullet_ptr->y]= UP_BULLET;
	map[left_bullet_ptr->x][left_bullet_ptr->y]= LEFT_BULLET;	
	map[right_bullet_ptr->x][right_bullet_ptr->y]= RIGHT_BULLET;	
	map[down_bullet_ptr->x][down_bullet_ptr->y]= DOWN_BULLET;	
	
	for(int i =0;i<8;i++)
	{	
		if(enemy_group[i].if_exist==1)
			{map[enemy_group[i].x][enemy_group[i].y]= ENEMY;}
	}
	
}

void game::updateWithInput()//�������йصĸ���
{
    char input;
    if (kbhit())
    {
        input = getch();

        // �����Ǿ����ƶ�   // ���ڶ���map����ʱ��[x][y],���� x Ϊ������, y Ϊ������ ! 
        if (input == 'a')                               // �����ƶ�
            if(map[cop_ptr->x][cop_ptr->y-1]==FREE)     // �������һ,�����겻��
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y--;}
        if (input == 's')                               //�����ƶ�
            if(map[cop_ptr->x+1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x++;}
        if (input == 'd')                               //�����ƶ�
            if(map[cop_ptr->x][cop_ptr->y+1]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y++;}
        if (input == 'w')                               //�����ƶ�
            if(map[cop_ptr->x-1][cop_ptr->y]==FREE)
                {map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x--;}

		// ����װ��ѡ��
		if (input=='f') {cop_ptr->face =0;}	// Яǹ״̬
		if (input=='q') {cop_ptr->face =1;} // Я��״̬
		if (input=='e') {cop_ptr->face =2;}	// Я��״̬
		
		
        // �����Ƿ����ӵ�
        
        if (input == 'i'&& cop_ptr->face == 0)                      //�������
            if(map[cop_ptr->x-1][cop_ptr->y]!=WALL)
                {up_bullet_ptr->x = cop_ptr->x-1;up_bullet_ptr->y = cop_ptr->y;}
                
        if (input == 'j'&& cop_ptr->face == 0)                      //�������
            if(map[cop_ptr->x][cop_ptr->y-1]!=WALL)
                {left_bullet_ptr->x = cop_ptr->x;left_bullet_ptr->y = cop_ptr->y-1;}
                
        if (input == 'k'&& cop_ptr->face == 0)                      //�������
            if(map[cop_ptr->x+1][cop_ptr->y]!=WALL)
                {down_bullet_ptr->x = cop_ptr->x+1;down_bullet_ptr->y = cop_ptr->y;}
                
        if (input == 'l'&& cop_ptr->face == 0)                      //�������
            if(map[cop_ptr->x][cop_ptr->y+1]!=WALL)
                {right_bullet_ptr->x = cop_ptr->x;right_bullet_ptr->y = cop_ptr->y+1;}
		
		
		// ����Ϊʹ�ø���
		
        if (input == 'i'&& cop_ptr->face == 1)
            if(map[cop_ptr->x-1][cop_ptr->y]==WALL)	
				{map[cop_ptr->x-1][cop_ptr->y]=FREE;map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x--;}
				
        if (input == 'j'&& cop_ptr->face == 1)
            if(map[cop_ptr->x][cop_ptr->y-1]==WALL)	
				{map[cop_ptr->x][cop_ptr->y-1]=FREE;map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y--;}	
					
        if (input == 'k'&& cop_ptr->face == 1)
            if(map[cop_ptr->x+1][cop_ptr->y]==WALL)	
				{map[cop_ptr->x+1][cop_ptr->y]=FREE;map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->x++;}	
									
        if (input == 'l'&& cop_ptr->face == 1)
            if(map[cop_ptr->x][cop_ptr->y+1]==WALL)	
				{map[cop_ptr->x][cop_ptr->y+1]=FREE;map[cop_ptr->x][cop_ptr->y]=FREE;cop_ptr->y++;}		
		
		
		// ����Ϊʹ�û���
		
        if (input == 'i'&& cop_ptr->face == 2)
            if(map[cop_ptr->x-1][cop_ptr->y]==FREE)	
				{map[cop_ptr->x-1][cop_ptr->y]=WALL;}
				
        if (input == 'j'&& cop_ptr->face == 2)
            if(map[cop_ptr->x][cop_ptr->y-1]==FREE)	
				{map[cop_ptr->x][cop_ptr->y-1]=WALL;}	
					
        if (input == 'k'&& cop_ptr->face == 2)
            if(map[cop_ptr->x+1][cop_ptr->y]==FREE)	
				{map[cop_ptr->x+1][cop_ptr->y]=WALL;}	
									
        if (input == 'l'&& cop_ptr->face == 2)
            if(map[cop_ptr->x][cop_ptr->y+1]==FREE)	
				{map[cop_ptr->x][cop_ptr->y+1]=WALL;}		
	}
}


void game::update_bullet()  //���ӵ����������С͵
{
    if (up_bullet_ptr->y < 18 && up_bullet_ptr->x > 0)           //�ӵ�up�Զ�����
        {
            if(map[up_bullet_ptr->x-1][up_bullet_ptr->y]!=WALL)
                {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x--;}
            else {map[up_bullet_ptr->x][up_bullet_ptr->y]=0;up_bullet_ptr->x=19;up_bullet_ptr->y=19;}
        }
    if (left_bullet_ptr->y < 18 && left_bullet_ptr->x > 0)       //�ӵ�left�Զ�����
        {
            if(map[left_bullet_ptr->x][left_bullet_ptr->y - 1]!=WALL)
                {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->y--;}
            else {map[left_bullet_ptr->x][left_bullet_ptr->y]=0;left_bullet_ptr->x=0;left_bullet_ptr->y=0;}
        }
    if (right_bullet_ptr->y < 18 && right_bullet_ptr->x > 0)     //�ӵ�right�Զ�����
        {
            if(map[right_bullet_ptr->x][right_bullet_ptr->y + 1]!=WALL)
                {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->y++;}
            else {map[right_bullet_ptr->x][right_bullet_ptr->y]=0;right_bullet_ptr->x=0;right_bullet_ptr->y=19;}
        }
    if (down_bullet_ptr->y < 18 && down_bullet_ptr->x > 0)       //�ӵ�down�Զ�����
        {
            if(map[down_bullet_ptr->x + 1][down_bullet_ptr->y]!=WALL)
                {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x++;}
            else {map[down_bullet_ptr->x][down_bullet_ptr->y]=0;down_bullet_ptr->x=0;down_bullet_ptr->y=1;}
        }
	
	for(int i=0;i<8;i++)
	{	if(enemy_group[i].if_exist==1)
		{
		// �˴������� bool������ԭ���Ǽ�������� if �ж����ĳ���
		bool condition1=(up_bullet_ptr->x == enemy_group[i].x) && (up_bullet_ptr->y == enemy_group[i].y);
		bool condition2=(left_bullet_ptr->x == enemy_group[i].x) && (left_bullet_ptr->y == enemy_group[i].y);
		bool condition3=(right_bullet_ptr->x == enemy_group[i].x) && (right_bullet_ptr->y == enemy_group[i].y);
		bool condition4=(down_bullet_ptr->x == enemy_group[i].x) && (down_bullet_ptr->y == enemy_group[i].y);
		
	
	    if (condition1||condition2||condition3||condition4)
	        //��ĳ��С͵������ʱ
	        {
	            enemy_group[i].if_exist=0;
	            map[enemy_group[i].x][enemy_group[i].y]=FREE;
	            enemy_group[i].x=0;
	            enemy_group[i].y=0;
	            enemy_num--;
	            cout<<"��";
	        }
	    if(enemy_num ==0)
	    	{win_or_die =1;} // Ӯ��
	    	
		}
	}       
        
}


		
void game::update_enemy()
{
	for(int i=0;i<8;i++)
	{
	   if(enemy_group[i].if_exist==1)
	   {
       time_t t=time(NULL);    //    ��ϵͳʱ����Ϊ��ǩ�����������
       srand(t);               //
       int p;
       Sleep(100/enemy_num); // ��֤���˵��ӳ��� 100ms
       enemy_group[i].flag =0;                // flag ����Ҫ,��ȷ��С͵ÿ�ζ�������ƶ�
       
       while (enemy_group[i].flag ==0)
       {
           p=(rand()+i*14-enemy_num*2)%4;
           switch(p)
           {
               case 0:
				if(map[enemy_group[i].x-1][enemy_group[i].y]!=WALL && map[enemy_group[i].x-1][enemy_group[i].y]!=DOWN_BULLET)
					{map[enemy_group[i].x][enemy_group[i].y]=FREE;enemy_group[i].x--;enemy_group[i].flag=1;}    
				break;  
					
               case 1:
				if(map[enemy_group[i].x][enemy_group[i].y-1]!=WALL && map[enemy_group[i].x][enemy_group[i].y-1]!=RIGHT_BULLET)
					{map[enemy_group[i].x][enemy_group[i].y]=FREE;enemy_group[i].y--;enemy_group[i].flag=1;}	  
				break;  
					
               case 2:
				if(map[enemy_group[i].x+1][enemy_group[i].y]!=WALL && map[enemy_group[i].x+1][enemy_group[i].y]!=UP_BULLET)
					{map[enemy_group[i].x][enemy_group[i].y]=FREE;enemy_group[i].x++;enemy_group[i].flag=1;}    
				break;  
					
               case 3:
				if(map[enemy_group[i].x][enemy_group[i].y+1]!=WALL && map[enemy_group[i].x][enemy_group[i].y+1]!=LEFT_BULLET)
					{map[enemy_group[i].x][enemy_group[i].y]=FREE;enemy_group[i].y++;enemy_group[i].flag=1;}    
				break;  
           }
       }
       
	    if(enemy_group[i].x == cop_ptr->x && enemy_group[i].y == cop_ptr->y)
		{
			win_or_die=2;
			break;
		} // �������
		
	   }
	}	
	
}
		
			
			
