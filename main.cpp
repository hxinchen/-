#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include <io.h>
#include<windows.h>
#include"head.h"
using namespace std;











int main()
{
	initgraph(window_wide, window_height);
	HWND hWnd = GetHWnd();            // »ñÈ¡´°¿ÚÃû³Æ¾ä±ú
	SetWindowText(hWnd, L"ºÚÎò¿Õ");
	Sleep(5000);
	backmusic();
	over_cartoon();
	origin();
	role_load();
	enemy_load();
	role_arise();
	while (1) {
		BeginBatchDraw();

		initializtion();
		if (big_skill == 1) {
			trump_card();
		}
		role_move();
		role_show();

		if (map_move >= 1500) {
			action = stand;
			
			map_stop = 1;
			break;		
		}
		EndBatchDraw();
	}

	while(1){
		BeginBatchDraw();

		initializtion();
		if (big_skill == 1) {
			trump_card();
		}
		role_move();		
		role_show();
	
			if (enemy_1_die == 0) {
				enemy_judge();
			}
			if (enemy_cat_die == 0)
				cat_judge();
			if (enemy_boss_die == 2)
				boss_judge();
			
		
		EndBatchDraw();
	}

	getchar();
	closegraph();
}