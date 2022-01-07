#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include <io.h>
#include<time.h>
#include<windows.h>
#include<math.h>
#include"head.h"
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib, "Msimg32.lib")
using namespace std;




IMAGE enemy[200];
IMAGE Role[200];


int enemy_float = 30;
int cat_state = 0;//猫猫状态
int enemy_state = 0;//蓝龙状态
int boss_state = 0;//boss状态

//中心
int enemy_center1;//蓝龙中心
int enemy_center2;//猫猫中心
int enemy_center3;//boss中心


//初始站立
int action = stand;
//是否放技能
int skilling = 0;
int move_D = 0;//是否右移
int move_A = 0;//是否左移
//人物朝向判断
bool right = true;
bool enemy_right = true;//蓝龙朝向
bool cat_right = true;//猫猫朝向
bool boss_right = true;//boss朝向
//人物坐标相应贴图更新速度
int update = 100 * clock();
int fx = 0;//是否有技能特效
int big_skill = 0;//是否大招
int effect = -1;
int cat_effect = -1;
int boss_effect = -1;
//第一关是否结束
int one_over = 0;//1为野怪被打死,2为进入下一关
//第二关是否结束
int two_over = 0;
//怪物死亡
int enemy_die = 0;
int enemy_1_die = 0;
int enemy_cat_die = 0;
int enemy_boss_die = 0;
int hurting = 0;



//锁定地图
int map_move = 0;
int map_stop = 0;//等于1锁定
//移动速度
int move_speed = 15;
int judge_benten = 0;
int judge_benten_boss = 0;
int judge_benten_cat = 0;
int blood_change = 250;
int enemy_hurt = 0;
int boss_judge_benten = 0;
int wushuang = 0;
int shadow[100][5] = { 0 };

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图 
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
//实现可自设透明度
void transparentimage_t(IMAGE* dstimg, int x, int y, IMAGE* srcimg, int i) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, i, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图 
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
IMAGE img_princess, img_boss, img_boss2, img_renwu2, img_renwu3, img_background, img_speak, img_bigboss,img_renwu1, img_begin, img_introduce, img_choose, img_back, img_pointer, img_finish, img_round1, img_round2, img_round3;
void word(int count)
{
	loadimage(&img_princess, L"./imgs/交互/公主.png", 395, 260, true);
	loadimage(&img_renwu1, L"./imgs/交互/人物1.png", 395, 260, true);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("楷体"));
	if (count == 1)
	{
		outtextxy(360, 490, _T("悟空：可恶啊。。。我的公主")); Sleep(2000);
		outtextxy(360, 520, _T("白骨精：嘿嘿，小悟空，你的公主在这呢"));
		transparentimage(NULL, 650, 100, &img_princess); Sleep(2000);
		outtextxy(360, 550, _T("悟空：快放开我的公主")); Sleep(2000);
		outtextxy(360, 580, _T("白骨精：想救回你的小公主就来盘丝洞找我吧")); Sleep(2000);
	}
	if (count == 2)
	{
		outtextxy(360, 490, _T("某公主：我的悟空王子 快来救我")); Sleep(2000);
		outtextxy(360, 520, _T("某公主：come on!!!here!!!")); Sleep(2000);
		outtextxy(360, 550, _T("悟空：我来也!!")); Sleep(2000);
	}
}
//对话
void orign_cartoon()
{
	int x = 0, y = 0;
	loadimage(&img_background, L"./imgs/交互/背景.jpg", window_wide, window_height, true);

	loadimage(&img_renwu1, L"./imgs/交互/人物1.png", 210, 140, true);
	loadimage(&img_boss2, L"./imgs/交互/boss2.png", 202, 240, true);
	loadimage(&img_princess, L"./imgs/交互/公主.png", 395, 260, true);
	loadimage(&img_renwu2, L"./imgs/交互/人物2.png", 167, 260, true);
	for (x = 0; x < 500; x += 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //初始背景
		transparentimage(NULL, 650 + x, 100, &img_princess);
		transparentimage(NULL, 100, 300, &img_renwu2);
		transparentimage(NULL, 900 + x, 310, &img_boss2);
		EndBatchDraw();
		Sleep(40);
	}
	for (x = 0; x < 1300; x += 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //初始背景
		transparentimage(NULL, 100 + x, 300, &img_renwu1);
		EndBatchDraw();
		Sleep(10);
	}
}
//初始动画
void plot()
{
	int count = 0;
	char  W, S, Q, E, M, J;
	loadimage(&img_renwu1, L"./imgs/交互/人物1.png", 395, 260, true);
	loadimage(&img_speak, L"./imgs/交互/对话框.png", 580, 170, true);
	loadimage(&img_background, L"./imgs/交互/背景.jpg", window_wide, window_height, true);
	loadimage(&img_boss2, L"./imgs/交互/boss2.png", 202, 240, true);
	loadimage(&img_renwu3, L"./imgs/交互/人物3.png", 193, 280, true);
	loadimage(&img_renwu2, L"./imgs/交互/人物2.png", 167, 260, true);
	BeginBatchDraw();
	transparentimage(NULL, 0, 0, &img_background); //初始背景
	transparentimage(NULL, 900, 310, &img_boss2);
	transparentimage(NULL, 100, 300, &img_renwu2);
	EndBatchDraw();
	while (1)
	{
		static int n = 0;
		if (n == 0)
		{
			BeginBatchDraw();
			transparentimage(NULL, 300, 480, &img_speak);
			settextcolor(RGB(255, 255, 255));
			settextstyle(23, 0, _T("楷体"));
			setbkmode(TRANSPARENT);
			outtextxy(360, 490, _T("请按下J键"));
			EndBatchDraw();
		}
		if (J = GetKeyState('J') && n < 2)
		{
			transparentimage(NULL, 300, 480, &img_speak);
			count++;
			word(count);
			n++;
		}
		if (n == 2)
		{
			orign_cartoon();
			return;
		}
	}

}
//剧情
void backmusic()
{
	mciSendString(L"open 音效/进场.mp3 alias bk", NULL, 0, NULL);
	mciSendString(L"play bk repeat", NULL, 0, NULL);
}
//背景音乐
void origin()
{
	char  W, S, Q, E;
	int x = -1, count = 1, t = 1;
	int time = clock();
	static int update = clock();
	loadimage(&img_pointer, L"./imgs/交互/指针.png", 43, 25, true);
	loadimage(&img_begin, L"./imgs/交互/开始游戏.png", 242, 69, true);
	loadimage(&img_finish, L"./imgs/交互/退出游戏.png", 242, 69, true);
	loadimage(&img_choose, L"./imgs/交互/选择关卡.png", 242, 69, true);
	loadimage(&img_introduce, L"./imgs/交互/操作说明.png", 242, 69, true);
	loadimage(&img_back, L"./imgs/交互/返回.png", 242, 69, true);
	loadimage(&img_background, L"./imgs/交互/背景.jpg", window_wide, window_height, true);
	loadimage(&img_round1, L"./imgs/交互/1.png", 242, 69, true);
	loadimage(&img_round2, L"./imgs/交互/2.png", 242, 69, true);
	loadimage(&img_round3, L"./imgs/交互/3.png", 242, 69, true);
	loadimage(&img_speak, L"./imgs/交互/对话框.png", 580, 170, true);

	while (1)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //初始背景

		if ((W = GetKeyState('W')) < 0)
		{
			count -= 1;
		}
		if ((S = GetKeyState('S')) < 0)
		{
			count += 1;
		}
		if (count > 4)
		{
			count = 1;
		}
		if (count == 0)
		{
			count = 4;
		}
		if (x >= -15)
		{
			x -= 10;
		}
		else
		{
			x += 5;
		}
		if ((Q = GetKeyState('Q')) < 0)
		{
			if ((count == 1 && t == 1) || (count == 1 && t == 3))
			{
				BeginBatchDraw();
				transparentimage(NULL, 0, 0, &img_background); //初始背景
				transparentimage(NULL, 300, 480, &img_speak);
				EndBatchDraw();
				plot();
				return;
			}
			if (count == 2)
			{

				t = 2;
			}
			if (count == 3 && t == 1)
			{
				t = 3;
				count = 1;
			}//操作说明
			if (count == 4 && t == 1)
			{
				closegraph();
			}
			if (count == 4 && t == 3)
			{
				t = 1;
				count = 1;
			}

		}
		if (t == 1)
		{
			transparentimage(NULL, 500, 100, &img_begin);
			transparentimage(NULL, 500, 200, &img_introduce);
			transparentimage(NULL, 500, 300, &img_choose);
			transparentimage(NULL, 500, 400, &img_finish);
			transparentimage(NULL, 460 + x, 122 + (count - 1) * 100, &img_pointer);
		}
		if (t == 2)
		{

			int i = 0;
			wchar_t temp[100];
			setbkmode(TRANSPARENT);
			// 1.设置文字背景模式为 TRANSPARENT 实现输出文字无背景色
			settextcolor(RGB(255, 0, 0));
			// 2.设置文字颜色为 红色
			settextstyle(25, 0, _T("楷体"));

			// 3.设置文字大小和字体，参数依次为：高、宽、字体。若宽度为 0 表示自适应,
			// 字体_T(“*”)中*可自行替换，建议使用常见的字体，如：宋体、楷体、隶书等



			outtextxy(20, 30, _T("AD用来左右移动"));
			outtextxy(20, 80, _T("j是普通攻击"));
			outtextxy(20, 400, _T("E键返回"));
			transparentimage(NULL, 1000, 600, &img_back);
			if (E = GetKeyState('E') < 0)
			{
				t = 1;
			}
		}
		//待优化
		if (t == 3)
		{
			transparentimage(NULL, 500, 100, &img_round1);
			transparentimage(NULL, 500, 200, &img_round2);
			transparentimage(NULL, 500, 300, &img_round3);
			transparentimage(NULL, 500, 400, &img_back);
			transparentimage(NULL, 460 + x, 122 + (count - 1) * 100, &img_pointer);
		}

		EndBatchDraw();
		Sleep(120);
	}

}
//原始
/*void loading_music()
{
	TCHAR tmpmp3[_MAX_PATH];
	GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat_s(tmpmp3, _T("雷电.mp3")); // 所加载的音频名称

	HANDLE hFile = CreateFile(tmpmp3, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_TEMPORARY, NULL);
	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC hRes = FindResource(NULL, _T("雷电.mp3"), _T("MP3"));
	// 资源 ID、类型名称
	HGLOBAL hMem = LoadResource(NULL, hRes);
	DWORD dwSize = SizeofResource(NULL, hRes);
	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);


}*/
//音频的预加载
//贴背景图,实现地图移动
void transparentimage_BK(IMAGE* dstimg, int x, int y, IMAGE* srcimg) {

	
	if (map_stop != 1) {
		if (role.x >= window_wide - 300 && (action == run || action == jump) && map_move <= 2800 - window_wide) {
			map_move += move_speed;
		}
		if (role.x <= 200 && (action == run || action == jump) && map_move > 10) {
			map_move -= move_speed;
		}
	}
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// 结构体的第三个成员表示额外的透明度，0 表示全透明，255 表示不透明。  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// 使用 Windows GDI 函数实现半透明位图 
	AlphaBlend(dstDC, x, y, w - map_move, h, srcDC, map_move, 0, w - map_move, h, bf);
}

//地图初始化/血条
void initializtion()
{
	IMAGE img_bk1, img_blood, img_HP, img_MP, enemy_blood, act_blood, enemy_HP,boss_HP,boss_blood;
	if (one_over == 2) {
		move_speed = 35;
		loadimage(&img_bk1, L"./imgs/背景2.png", 2800, 700, true);
		transparentimage_BK(NULL, 0, 0, &img_bk1);
	}
	if (one_over < 2) {
		move_speed = 40;
		loadimage(&img_bk1, L"./imgs/背景.jpg", 2800, 700, true);
		transparentimage_BK(NULL, 0, 0, &img_bk1);
	}
	if (enemy_1_die == 1) {
		enemy_1.y = 1200;
		enemy_state = 0;
	}
	if (enemy_cat_die == 1) {
		enemy_cat.y = 1200;
		cat_state = 0;
	}
	if (enemy_boss_die == 1) {
		enemy_boss.y = 1200;
		boss_state = 0;
	}
	if (one_over != 2) {
		if (enemy_1_die == 1 && enemy_cat_die == 1) {
			one_over = 1;
		}
	}
	IMAGE door;
	if (one_over == 1) {
		Door.x = 400;
		Door.y = 300;
		loadimage(&door, L"./imgs/传送门.png", 256, 278, true);
		transparentimage(NULL, Door.x, Door.y, &door);
	}
	if (abs((role.x + 54) - (Door.x + 128)) <= 70 && GetKeyState('W')) {
		one_over = 2;
		enemy_boss_die = 2;
	}






	loadimage(&img_blood, L"./imgs/血量/血条.png", 420, 101, true);
	transparentimage(NULL, 20, 20, &img_blood);


	loadimage(&img_HP, L"./imgs/血量/血条1.png", 3, 19, true);
	loadimage(&img_MP, L"./imgs/血量/蓝条.png", 3, 19, true);
	for (int i = 0; i <= (role.HP / 10); i++) {
		transparentimage(NULL, 123 + i * 3, 67, &img_HP);
	}
	for (int i = 0; (i <= role.MP / 10); i++) {
		transparentimage(NULL, 123 + i * 3, 90, &img_MP);
	}



	loadimage(&enemy_blood, L"./imgs/血量/野怪血条框.png", 100, 101, true);
	loadimage(&enemy_HP, L"./imgs/血量/怪物血条.png", 3, 10, true);
	if (map_move >= 1500) {
		if (enemy_1_die == 0) {
			transparentimage_t(NULL, enemy_1.x + 20, enemy_1.y - 100, &enemy_blood, 150);
			for (int i = 0; i <= (enemy_1.HP / 6); i++) {
				transparentimage_t(NULL, enemy_1.x + 20 + i * 1, enemy_1.y - 10, &enemy_HP, 200);
			}
		}
		if (enemy_cat_die == 0) {
			transparentimage_t(NULL, enemy_cat.x - 10, enemy_cat.y - 100, &enemy_blood, 150);
			for (int i = 0; i <= (enemy_cat.HP / 5); i++) {
				transparentimage_t(NULL, enemy_cat.x - 10 + i * 1, enemy_cat.y - 10, &enemy_HP, 200);
			}
		}
		loadimage(&boss_blood, L"./imgs/血量/boss血条框.png", 300, 50, true);
		loadimage(&boss_HP, L"./imgs/血量/血条1.png", 3, 18, true);

		if (enemy_boss_die == 2) {
			transparentimage(NULL, 700, 20, &boss_blood);
			for (int i = 0; i <= (enemy_boss.HP / 10); i++) {
				transparentimage_t(NULL, 703 + i * 3, 23, &boss_HP, blood_change);
			}
		}
	}
}
//关卡切换

void  change()
{
	IMAGE door;
	if (one_over == 1) {
		Door.x = 900;
		Door.y = 400;

		loadimage(&door, L"./imgs/传送门.png", 256, 278, true);
		transparentimage(NULL, Door.x, Door.y, &door);
	}
	if (abs((role.x + 54) - (Door.x + 128)) <= 70) {
		one_over = 2;
	}

}
//出场动画
void role_arise()
{
	IMAGE img;
	loadimage(&img, L"./imgs/移动/移动右2.png", 138, 128, true);
	while (1) {
		BeginBatchDraw();
		initializtion();
		Sleep(10);
		role.x += 40;
		if (role.x >= 550)
			return;
		transparentimage(NULL, role.x, role.y, &img);
		EndBatchDraw();
	}
}


//大招动画
void trump_card() {
	IMAGE img[100], img_bk;
	mciSendString(TEXT("play ./大招.mp3"), NULL, 0, NULL);
	loadimage(&img_bk, L"./imgs/大招动画/背景.png", window_wide, window_height, true);
	loadimage(&img[0], L"./imgs/大招动画/1000.bmp", 300, 300, true);
	loadimage(&img[1], L"./imgs/大招动画/1001.bmp", 300, 300, true);
	loadimage(&img[2], L"./imgs/大招动画/1002.bmp", 300, 300, true);
	loadimage(&img[3], L"./imgs/大招动画/1003.bmp", 300, 300, true);
	loadimage(&img[4], L"./imgs/大招动画/1004.bmp", 300, 300, true);
	loadimage(&img[5], L"./imgs/大招动画/1005.bmp", 300, 300, true);
	loadimage(&img[6], L"./imgs/大招动画/1006.bmp", 300, 300, true);
	loadimage(&img[7], L"./imgs/大招动画/1007.bmp", 300, 300, true);
	loadimage(&img[8], L"./imgs/大招动画/1008.bmp", 300, 300, true);
	loadimage(&img[9], L"./imgs/大招动画/1009.bmp", 300, 300, true);
	loadimage(&img[10], L"./imgs/大招动画/1010.bmp", 300, 300, true);
	loadimage(&img[11], L"./imgs/大招动画/1011.bmp", 300, 300, true);
	loadimage(&img[12], L"./imgs/大招动画/1012.bmp", 300, 300, true);
	loadimage(&img[13], L"./imgs/大招动画/1013.bmp", 300, 300, true);
	loadimage(&img[14], L"./imgs/大招动画/1014.bmp", 300, 300, true);
	loadimage(&img[15], L"./imgs/大招动画/1015.bmp", 300, 300, true);
	loadimage(&img[16], L"./imgs/大招动画/1015.bmp", 300, 300, true);
	loadimage(&img[17], L"./imgs/大招动画/1015.bmp", 300, 300, true);


	loadimage(&img[18], L"./imgs/大招动画/70003.png", 300, 300, true);
	loadimage(&img[19], L"./imgs/大招动画/70004.png", 300, 300, true);
	loadimage(&img[20], L"./imgs/大招动画/70005.png", 300, 300, true);
	loadimage(&img[21], L"./imgs/大招动画/70006.png", 300, 300, true);
	loadimage(&img[22], L"./imgs/大招动画/70007.png", 300, 300, true);
	loadimage(&img[23], L"./imgs/大招动画/70008.png", 300, 300, true);
	loadimage(&img[24], L"./imgs/大招动画/70009.png", 300, 300, true);
	loadimage(&img[25], L"./imgs/大招动画/70010.png", 300, 300, true);
	loadimage(&img[26], L"./imgs/大招动画/70011.png", 300, 300, true);
	loadimage(&img[27], L"./imgs/大招动画/70012.png", 300, 300, true);
	loadimage(&img[28], L"./imgs/大招动画/70013.png", 300, 300, true);
	loadimage(&img[29], L"./imgs/大招动画/70014.png", 300, 300, true);
	loadimage(&img[30], L"./imgs/大招动画/70015.png", 300, 300, true);
	loadimage(&img[31], L"./imgs/大招动画/70016.png", 300, 300, true);
	loadimage(&img[32], L"./imgs/大招动画/70017.png", 300, 300, true);
	loadimage(&img[33], L"./imgs/大招动画/70018.png", 300, 300, true);
	loadimage(&img[34], L"./imgs/大招动画/70019.png", 300, 300, true);
	loadimage(&img[35], L"./imgs/大招动画/70020.png", 300, 300, true);
	loadimage(&img[36], L"./imgs/大招动画/70021.png", 300, 300, true);
	loadimage(&img[37], L"./imgs/大招动画/70022.png", 300, 300, true);
	loadimage(&img[38], L"./imgs/大招动画/70023.png", 300, 300, true);
	loadimage(&img[39], L"./imgs/大招动画/70024.png", 300, 300, true);
	loadimage(&img[40], L"./imgs/大招动画/70025.png", 300, 300, true);
	loadimage(&img[41], L"./imgs/大招动画/70026.png", 300, 300, true);
	loadimage(&img[42], L"./imgs/大招动画/70027.png", 300, 300, true);
	loadimage(&img[43], L"./imgs/大招动画/70028.png", 300, 300, true);
	loadimage(&img[44], L"./imgs/大招动画/70029.png", 300, 300, true);
	loadimage(&img[45], L"./imgs/大招动画/70030.png", 300, 300, true);
	loadimage(&img[46], L"./imgs/大招动画/70031.png", 300, 300, true);
	loadimage(&img[47], L"./imgs/大招动画/70032.png", 300, 300, true);
	loadimage(&img[48], L"./imgs/大招动画/70032.png", 300, 300, true);
	loadimage(&img[49], L"./imgs/大招动画/70032.png", 300, 300, true);
	loadimage(&img[50], L"./imgs/大招动画/70032.png", 300, 300, true);

	loadimage(&img[51], L"./imgs/大招动画/大招右1.png", 121, 200, true);
	loadimage(&img[52], L"./imgs/大招动画/大招右2.png", 131, 200, true);
	loadimage(&img[53], L"./imgs/大招动画/大招右3.png", 138, 200, true);
	loadimage(&img[54], L"./imgs/大招动画/大招右3.png", 138, 200, true);
	loadimage(&img[55], L"./imgs/大招动画/大招右3.png", 138, 200, true);

	loadimage(&img[80], L"./imgs/野怪/蓝龙移动1.png", 163, 159, true);
	loadimage(&img[81], L"./imgs/野怪/蓝龙移动2.png", 163, 159, true);
	loadimage(&img[82], L"./imgs/野怪/蓝龙移动3.png", 163, 159, true);
	loadimage(&img[83], L"./imgs/野怪/蓝龙移动4.png", 163, 159, true);
	loadimage(&img[84], L"./imgs/野怪/蓝龙移动5.png", 163, 159, true);

	loadimage(&img[85], L"./imgs/猫攻击/猫攻击14.png", 184, 150, true);
	loadimage(&img[86], L"./imgs/boss/boss技能1.png", 222, 250, true);

	while (1) {
		BeginBatchDraw();

		transparentimage(NULL, 0, 0, &img_bk);
		Sleep(150);
		static int i = 0, j = 18, m = 51, n = 80, t = 0;
		if (t == 0) {
			transparentimage(NULL, 450, 300, &img[i]);
			i++;
			if (i == 17) {
				i = 0;
				t = 1;;
			}
		}
	
		if (t == 1) {
			
			transparentimage(NULL, 700, 250, &img[j]);
			
				if (enemy_1_die == 0)
					transparentimage_t(NULL, 760, 360, &img[82], 150);
				if (enemy_cat_die == 0)
					transparentimage_t(NULL, 760, 360, &img[85], 150);
				if (enemy_boss_die == 2) {
					transparentimage_t(NULL, 760, 270, &img[86], 150);

				}
			transparentimage(NULL, 150, 250, &img[53]);
			j++;
			if (j == 50) {
				transparentimage(NULL, 0, 0, &img_bk);
				j = 0;
	
				big_skill = 0;
				skilling = 0;
				action = stand;
				t = 0;
				return;
			}
		}

		EndBatchDraw();
	}
}

//角色加载
void role_load()
{
	loadimage(&Role[0], L"./imgs/站立/静态右1.png", 118, 126, true);
	loadimage(&Role[1], L"./imgs/站立/静态右2.png", 118, 126, true);
	loadimage(&Role[2], L"./imgs/站立/静态右3.png", 118, 126, true);
	loadimage(&Role[3], L"./imgs/站立/静态右2.png", 118, 126, true);
	loadimage(&Role[6], L"./imgs/站立/静态1.png", 118, 126, true);
	loadimage(&Role[7], L"./imgs/站立/静态2.png", 118, 126, true);
	loadimage(&Role[8], L"./imgs/站立/静态3.png", 118, 126, true);
	loadimage(&Role[9], L"./imgs/站立/静态2.png", 118, 126, true);

	loadimage(&Role[10], L"./imgs/移动/移动右7.png", 167, 105, true);
	loadimage(&Role[11], L"./imgs/移动/移动右1.png", 138, 128, true);
	loadimage(&Role[12], L"./imgs/移动/移动右2.png", 138, 128, true);
	loadimage(&Role[13], L"./imgs/移动/移动7.png", 167, 105, true);
	loadimage(&Role[14], L"./imgs/移动/移动1.png", 138, 128, true);
	loadimage(&Role[15], L"./imgs/移动/移动2.png", 138, 128, true);


	loadimage(&Role[16], L"./imgs/移动/跳跃右8.png", 106, 165, true);
	loadimage(&Role[17], L"./imgs/移动/跳跃右3.png", 106, 165, true);
	loadimage(&Role[18], L"./imgs/移动/跳跃右3.png", 106, 165, true);
	loadimage(&Role[19], L"./imgs/移动/跳跃右4.png", 106, 165, true);
	loadimage(&Role[20], L"./imgs/移动/跳跃右5.png", 106, 165, true);
	loadimage(&Role[21], L"./imgs/移动/跳跃右5.png", 106, 165, true);
	loadimage(&Role[22], L"./imgs/移动/跳跃右8.png", 106, 165, true);
	loadimage(&Role[23], L"./imgs/移动/跳跃右8.png", 106, 165, true);
	loadimage(&Role[24], L"./imgs/移动/跳跃8.png", 106, 165, true);
	loadimage(&Role[25], L"./imgs/移动/跳跃3.png", 106, 165, true);
	loadimage(&Role[26], L"./imgs/移动/跳跃3.png", 106, 165, true);
	loadimage(&Role[27], L"./imgs/移动/跳跃4.png", 106, 165, true);
	loadimage(&Role[28], L"./imgs/移动/跳跃5.png", 106, 165, true);
	loadimage(&Role[29], L"./imgs/移动/跳跃5.png", 106, 165, true);
	loadimage(&Role[30], L"./imgs/移动/跳跃8.png", 106, 165, true);
	loadimage(&Role[31], L"./imgs/移动/跳跃8.png", 106, 165, true);
}

//人物移动
void  role_move()
{


	int time = clock();
	int role_center = role.x + 54;

	if ((abs(enemy_center1-role_center)<=170&&enemy_state==1)&&action!=skill_S ||

		(abs(enemy_center2-role_center)<=175&&cat_state==1) && action != skill_S ||

		(abs(enemy_center3-role_center)<350) && boss_judge_benten == 1 && action != skill_S) {
		if (action != jump) {
			action = hurt;
			if (enemy_state == 1)
			{
				if (role.x < enemy_1.x)
					right = true;
				else
					right = false;
			}
			else if (cat_state == 1)
			{
				if (role.x < enemy_cat.x)
					right = true;
				else
					right = false;
			}
			else if (boss_state == 1)
			{
				if (role.x < enemy_boss.x)
					right = true;
				else
					right = false;
			}
		}
		return;
	}
	else if (action != hurt) {
		if (GetKeyState('O') < 0 && action == stand&&role.MP>=300) {//大招
			skilling = 4;
			big_skill = 1;
			action = skill_O;
			role.MP -= 300;
			return;
		}

		else if (GetKeyState('I') < 0 && skilling == 0 && role.MP >= 80) {
			if (action != jump) {
				skilling = 2;
				action = skill_I;
				return;
			}
		}

		else if (GetKeyState('U') < 0 && skilling == 0 && role.MP >= 150) {
			if (action != jump) {
				skilling = 3;
				action = skill_U;
				return;
			}
		}
		else if (GetKeyState('J') < 0 && skilling == 0) {
			if (action != jump) {
				skilling = 1;
				action = skill_J;
				return;
			}
		}
		else if (GetKeyState('L') < 0 && skilling == 0&&role.MP >= 50) {
			if (action != jump) {
				skilling = 4;
				action = skill_L;
				return;
			}
		}
		else if (GetKeyState('H') < 0) {//无双
			if (wushuang == 1) {
				wushuang = 0;
				return;
			}
			wushuang = 1;

			return;

		}
		else if (GetKeyState('S') < 0 && skilling < 1)
		{
			if (action != jump) {
				action = skill_S;
			}
		}
		else if (skilling == 0)//没在放技能
		{

			if (action != hurt) {
				if (GetKeyState('D') < 0)
				{
					if (role.x < window_wide - 150) {
						role.x += move_speed;
					}
					if (action == stand)
						action = run;
					right = true;
				}
				else if (GetKeyState('A') < 0)
				{
					if (role.x > 50) {
						role.x -= move_speed;
					}
					if (action == stand)
						action = run;
					right = false;
				}
				else if (action != jump && action != hurt)
					action = stand;
				if (GetKeyState('K') < 0)
				{
					action = jump;
				}
			}
		}
	}

}
//人物展示
void role_show()
{
	static IMAGE img;
	static IMAGE img_skill;
	int time = clock();
	static int count0 = 0, count = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0;

	//角色向右
	if (right) {
		if (action == stand)
		{
			count1 = 0;
			if ((time - update) >= 100)
			{
				update = time;
				if (role.HP < 1000)
					role.HP += 6;
				if (role.MP < 1000)
					role.MP += 6;
				count++;
			}
			if (count < 0 || count>3)
			{
				count = 0;
			}
			count0 = count;
		}
		else if (action == run)
		{
			count = 0;
			if ((time - update) >= 100)
			{
				update = time;
				if (count1 != 12)
				{
					count1++;
					action = stand;
				}
				else
				{
					count1 = 12;
				}
			}
			if (count1 < 10 || count1>12)
			{
				count1 = 10;
			}
			count0 = count1;
		}
		else if (action == jump)
		{
			count = 0;
			if ((time - update) >= 60)
			{
				update = time;
				count2++;
				if (count2 < 16 || count2>23)
				{
					count2 = 16;
				}
				if (count2 % 4 == 0)
				{
					role.y += 80 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 1)
				{
					role.y += 45 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 2)
				{
					role.y += 20 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 3)
				{
					role.y += 5 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
					if (count2 == 23)
					{
						action = stand;
					}
				}
				count0 = count2;
			}
		}
		else if (action == hurt)
		{
			count = 0;
			if (count3 == 0)
			{
				fx = 0;
				loadimage(&img, L"./imgs/挨打/挨打右1.png", 161, 135, true);
				count3 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count3 == 1)
				{
					if (enemy_boss_die == 2)
						role.HP -= 170;
					else
						role.HP -= 70;
					role.x -= 60;
					loadimage(&img, L"./imgs/挨打/挨打右1.png", 161, 135, true);
					count3 = 2;
				}
				else if (count3 == 2)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/挨打/挨打右2.png", 161, 135, true);
					count3 = 3;
				}
				else if (count3 == 3)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/挨打/挨打右3.png", 161, 135, true);
					count3 = 4;
				}
				else if (count3 == 4)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/挨打/挨打右4.png", 161, 135, true);
					count3 = 5;
				}
				else if (count3 == 5)
				{
					loadimage(&img, L"./imgs/挨打/挨打右5.png", 161, 135, true);
					count3 = 6;
				}
				else if (count3 == 6)
				{
					loadimage(&img, L"./imgs/挨打/挨打右6.png", 161, 135, true);
					count3 = 7;
				}
				else if (count3 == 7)
				{
					loadimage(&img, L"./imgs/挨打/挨打右7.png", 161, 135, true);
					count3 = 8;
				}
				else if (count3 == 8)
				{
					loadimage(&img, L"./imgs/挨打/挨打右8.png", 161, 135, true);
					count3 = 9;
				}
				else if (count3 == 9)
				{
					loadimage(&img, L"./imgs/挨打/挨打右9.png", 161, 135, true);
					count3 = 1;
					fx = 0;
					skilling = 0;
					action = stand;
				}
			}
		}
		else if (action == skill_S)
		{
			FX_S.x = role.x - 125;
			FX_S.y = role.y - 140;
			count = 0;
			if (count4 == 0)
			{
				fx = 2;
				loadimage(&img, L"./imgs/移动/站立格挡右3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/技能特效/1005-7.png", 350, 350, true);
				count4 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				fx = 2;
				loadimage(&img, L"./imgs/移动/站立格挡右3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/技能特效/1005-7.png", 350, 350, true);
			}
		}
		else if (action == skill_J)
		{
			//mciSendString(L"open 音效/.mp3 alias bk", NULL, 0, NULL);
			//mciSendString(L"play bk repeat", NULL, 0, NULL);
			static int seriate_J = 1;
			count = 0;
			if (seriate_J == 1) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/攻击/右掌右4.png", 120, 124, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/攻击/右掌右4.png", 120, 124, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/攻击/右掌右1.png", 120, 124, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/攻击/右掌右5.png", 120, 124, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/攻击/右掌右6.png", 120, 124, true);
						count5 = 5;
					}
					else if (count5 == 5)
					{
						loadimage(&img, L"./imgs/攻击/右掌右1.png", 120, 124, true);
						count5 = 6;
					}
					else if (count5 == 6)
					{
						loadimage(&img, L"./imgs/攻击/右掌右4.png", 120, 124, true);
						count5 = 1;
						action = stand;
						skilling = 0;
						seriate_J = 2;
					}
				}
			}
			if (seriate_J == 2) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/攻击/左拳右4.png", 145, 127, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/攻击/左拳右4.png", 145, 127, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/攻击/左拳右3.png", 145, 127, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/攻击/左拳右2.png", 145, 127, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/攻击/左拳右4.png", 145, 127, true);
						count5 = 1;
						action = stand;
						skilling = 0;
						seriate_J = 1;
					}
				}
			}
		}
		else if (action == skill_I)
		{
			FX_I.y = role.y + 20;

			count = 0;

			if (count6 == 0)
			{
				loadimage(&img, L"./imgs/技能I/远程右2.png", 117, 163, true);
				count6 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count6 == 1)
				{
					role.MP -= 80;
					loadimage(&img, L"./imgs/技能I/远程右2.png", 117, 163, true);
					count6 = 2;
				}
				else if (count6 == 2)
				{
					loadimage(&img, L"./imgs/技能I/远程右1.png", 117, 163, true);
					count6 = 3;
				}
				else if (count6 == 3)
				{
					loadimage(&img, L"./imgs/技能I/远程右1.png", 117, 163, true);
					count6 = 4;
				}
				else if (count6 == 4)
				{
					loadimage(&img, L"./imgs/技能I/远程右5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右1.png", 22, 17, true);
					fx = 1;
					FX_I.x = role.x + 130;
					count6 = 5;
				}
				else if (count6 == 5)
				{
					loadimage(&img, L"./imgs/技能I/远程右5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右1.png", 33, 25, true);
					FX_I.x = role.x + 160;
					count6 = 6;
				}
				else if (count6 == 6)
				{
					loadimage(&img, L"./imgs/技能I/远程右5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右1.png", 44, 34, true);
					FX_I.x = role.x + 200;
					count6 = 7;
				}
				else if (count6 == 7)
				{
					loadimage(&img, L"./imgs/技能I/远程右5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右2.png", 50, 49, true);
					FX_I.x = role.x + 230;
					count6 = 8;
				}
				else if (count6 == 8)
				{
					loadimage(&img, L"./imgs/技能I/远程右5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右2.png", 60, 59, true);
					FX_I.x = role.x + 260;

					count6 = 9;
				}
				else if (count6 == 9)
				{
					loadimage(&img, L"./imgs/技能I/远程右4.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰右3.png", 73, 60, true);
					FX_I.x = role.x + 290;
					count6 = 10;
				}
				else if (count6 == 10) {
					skilling = 0;
					action = stand;
					count6 = 1;
					fx = 0;
				}

			}

		}
		else if (action == skill_U)
		{
			count = 0;
			if (count7 == 0)
			{
				loadimage(&img, L"./imgs/升龙拳/升龙拳右2.png", 148, 133, true);

				count7 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count7 == 1)
				{
					role.MP -= 150;
					FX_U.x = role.x + 80;
					FX_U.y = role.y - 100;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右3.png", 148, 133, true);
					count7 = 2;
				}
				else if (count7 == 2)
				{
					fx = 3;
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右6.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-5.png", 250, 250, true);
					count7 = 3;
				}
				else if (count7 == 3)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右5.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-4.png", 250, 250, true);
					count7 = 4;
				}
				else if (count7 == 4)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-1.png", 250, 250, true);
					count7 = 5;
				}
				else if (count7 == 5)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-2.png", 250, 250, true);
					count7 = 6;
				}
				else if (count7 == 6)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-6.png", 250, 250, true);
					count7 = 7;
				}
				else if (count7 == 7)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳右4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-3.png", 250, 250, true);
					count7 = 8;
				}

				else if (count7 == 8) {
					skilling = 0;
					action = stand;
					count7 = 1;
					fx = 0;
				}

			}

		}
		else if (action == skill_L)
		{

			count = 0;
			FX_L.x = role.x;
			if (count8 == 0)
			{

				FX_L.y = role.y - 60;
				loadimage(&img, L"./imgs/闪现/图像5.png", 150, 200, true);
				role.MP -= 50;
				count8 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				
				if (count8 == 1)
					loadimage(&img, L"./imgs/闪现/图像4.png", 150, 200, true);
				if (count8 == 2)
					loadimage(&img, L"./imgs/闪现/图像3.png", 150, 200, true);
				if (count8 == 3)
					loadimage(&img, L"./imgs/闪现/图像9.png", 150, 200, true);
				if (count8 == 4)
					loadimage(&img, L"./imgs/闪现/图像2.png", 150, 200, true);
				if (count8 == 5) {
					loadimage(&img, L"./imgs/闪现/图像1.png", 150, 200, true);
					role.x += 300;
					FX_L.x += 300;
				}
				if (count8 == 6)
					loadimage(&img, L"./imgs/闪现/图像2.png", 150, 200, true);
				if (count8 == 7)
					loadimage(&img, L"./imgs/闪现/图像9.png", 150, 200, true);
				if (count8 == 8)
					loadimage(&img, L"./imgs/闪现/图像3.png", 150, 200, true);
				if (count8 == 9)
					loadimage(&img, L"./imgs/闪现/图像4.png", 150, 200, true);
				if (count8 == 10) {
					loadimage(&img, L"./imgs/闪现/图像5.png", 150, 200, true);
				}
				if (count8 == 11) {
					count8 = 0;
					action = stand;
					skilling = 0;
				}
				count8++;
			}
		}
	}
	//角色向左
	else
	{
		if (action == stand)
		{
			count1 = 1;
			if ((time - update) >= 150)
			{
				update = time;
				if (role.HP < 1000)
					role.HP += 6;
				if (role.MP < 1000)
					role.MP += 6;
				count++;

			}
			if (count < 6 || count>9)
			{
				count = 6;
			}
			count0 = count;
		}
		else if (action == run)
		{
			count = 0;
			if ((time - update) >= 100)
			{
				update = time;
				if (count1 != 15)
				{
					count1++;
					action = stand;
				}
				else
				{
					count1 = 15;

				}
			}
			if (count1 < 13 || count1>15)
			{
				count1 = 13;
			}
			count0 = count1;
		}
		else if (action == jump)
		{
			count = 0;
			if ((time - update) >= 60)
			{
				update = time;
				count2++;
				if (count2 < 16 || count2>23)
				{
					count2 = 16;
				}
				if (count2 % 4 == 0)
				{
					role.y += 80 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 1)
				{
					role.y += 45 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 2)
				{
					role.y += 20 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
				}
				else if (count2 % 4 == 3)
				{
					role.y += 5 * (((double)count2 - 19.5) / fabs((double)count2 - 19.5));
					if (count2 == 23)
					{
						action = stand;
					}
				}
				count0 = count2 + 8;
			}

		}
		else if (action == hurt)
		{
			count = 0;
			if (count3 == 0)
			{
				fx = 0;
				loadimage(&img, L"./imgs/挨打/挨打1.png", 161, 135, true);
				count3 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count3 == 1)
				{
					if(enemy_boss_die==2)
						role.HP -= 170;
					else
					role.HP -= 70;
					role.x += 60;
					loadimage(&img, L"./imgs/挨打/挨打1.png", 161, 135, true);
					count3 = 2;
				}
				else if (count3 == 2)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/挨打/挨打2.png", 161, 135, true);
					count3 = 3;
				}
				else if (count3 == 3)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/挨打/挨打3.png", 161, 135, true);
					count3 = 4;
				}
				else if (count3 == 4)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/挨打/挨打4.png", 161, 135, true);
					count3 = 5;
				}
				else if (count3 == 5)
				{
					loadimage(&img, L"./imgs/挨打/挨打5.png", 161, 135, true);
					count3 = 6;
				}
				else if (count3 == 6)
				{
					loadimage(&img, L"./imgs/挨打/挨打6.png", 161, 135, true);
					count3 = 7;
				}
				else if (count3 == 7)
				{
					loadimage(&img, L"./imgs/挨打/挨打7.png", 161, 135, true);
					count3 = 8;
				}
				else if (count3 == 8)
				{
					loadimage(&img, L"./imgs/挨打/挨打8.png", 161, 135, true);
					count3 = 9;
				}
				else if (count3 == 9)
				{
					loadimage(&img, L"./imgs/挨打/挨打9.png", 161, 135, true);
					count3 = 1;
					fx = 0;
					skilling = 0;
					action = stand;
				}
			}


		}
		else if (action == skill_S)
		{
			FX_S.x = role.x - 125;
			FX_S.y = role.y - 140;
			count = 0;
			if (count4 == 0)
			{
				fx = 2;
				loadimage(&img, L"./imgs/移动/站立格挡3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/技能特效/1005-7.png", 350, 350, true);
				count4 = 1;
			}
			if ((time - update) >= 200)
			{
				update = time;
				fx = 2;
				loadimage(&img, L"./imgs/移动/站立格挡3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/技能特效/1005-7.png", 350, 350, true);
			}
		}
		else if (action == skill_J)
		{
			static int seriate_J = 1;
			count = 0;
			if (seriate_J == 1) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/攻击/右掌4.png", 120, 124, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/攻击/右掌4.png", 120, 124, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/攻击/右掌1.png", 120, 124, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/攻击/右掌5.png", 120, 124, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/攻击/右掌6.png", 120, 124, true);
						count5 = 5;
					}
					else if (count5 == 5)
					{
						loadimage(&img, L"./imgs/攻击/右掌1.png", 120, 124, true);
						count5 = 6;
					}
					else if (count5 == 6)
					{
						loadimage(&img, L"./imgs/攻击/右掌4.png", 120, 124, true);
						count5 = 1;
						action = stand;
						skilling = 0;
						seriate_J = 2;
					}
				}
			}
			if (seriate_J == 2) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/攻击/左拳4.png", 145, 127, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/攻击/左拳4.png", 145, 127, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/攻击/左拳3.png", 145, 127, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/攻击/左拳2.png", 145, 127, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/攻击/左拳4.png", 145, 127, true);
						count5 = 1;
						action = stand;
						skilling = 0;
						seriate_J = 1;
					}
				}
			}
		}
		else if (action == skill_I)
		{
			FX_I.y = role.y + 20;
			count = 0;
			if (count6 == 0)
			{
				loadimage(&img, L"./imgs/技能I/远程2.png", 117, 163, true);
				count6 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count6 == 1)
				{
					role.MP -= 80;
					loadimage(&img, L"./imgs/技能I/远程2.png", 117, 163, true);
					count6 = 2;
				}
				else if (count6 == 2)
				{
					loadimage(&img, L"./imgs/技能I/远程1.png", 117, 163, true);
					count6 = 3;
				}
				else if (count6 == 3)
				{
					loadimage(&img, L"./imgs/技能I/远程1.png", 117, 163, true);
					count6 = 4;
				}
				else if (count6 == 4)
				{
					loadimage(&img, L"./imgs/技能I/远程5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰1.png", 22, 17, true);
					fx = 1;
					FX_I.x = role.x - 20;
					count6 = 5;
				}
				else if (count6 == 5)
				{
					loadimage(&img, L"./imgs/技能I/远程5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰1.png", 33, 25, true);
					FX_I.x = role.x - 50;
					count6 = 6;
				}
				else if (count6 == 6)
				{
					loadimage(&img, L"./imgs/技能I/远程5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰1.png", 44, 34, true);
					FX_I.x = role.x - 80;
					count6 = 7;
				}
				else if (count6 == 7)
				{
					loadimage(&img, L"./imgs/技能I/远程5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰2.png", 50, 49, true);
					FX_I.x = role.x - 110;
					count6 = 8;
				}
				else if (count6 == 8)
				{
					loadimage(&img, L"./imgs/技能I/远程5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰2.png", 60, 59, true);
					FX_I.x = role.x - 150;

					count6 = 9;
				}
				else if (count6 == 9)
				{
					loadimage(&img, L"./imgs/技能I/远程4.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/技能I/火焰3.png", 73, 60, true);
					FX_I.x = role.x - 190;
					count6 = 10;
				}
				else if (count6 == 10) {
					skilling = 0;
					action = stand;
					count6 = 1;
					fx = 0;
				}
			}
		}
		else if (action == skill_U)
		{


			count = 0;
			if (count7 == 0)
			{
				loadimage(&img, L"./imgs/升龙拳/升龙拳2.png", 148, 133, true);

				count7 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count7 == 1)
				{
					role.MP -= 150;
					FX_U.x = role.x - 160;
					FX_U.y = role.y - 100;
					loadimage(&img, L"./imgs/升龙拳/升龙拳3.png", 148, 133, true);
					count7 = 2;
				}
				else if (count7 == 2)
				{
					fx = 3;
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳6.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-5.png", 250, 250, true);
					count7 = 3;
				}
				else if (count7 == 3)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳5.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-4.png", 250, 250, true);
					count7 = 4;
				}
				else if (count7 == 4)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-1.png", 250, 250, true);
					count7 = 5;
				}
				else if (count7 == 5)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-2.png", 250, 250, true);
					count7 = 6;
				}
				else if (count7 == 6)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-6.png", 250, 250, true);
					count7 = 7;
				}
				else if (count7 == 7)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/升龙拳/升龙拳4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/升龙拳/1572-3.png", 250, 250, true);
					count7 = 8;
				}

				else if (count7 == 8) {
					skilling = 0;
					action = stand;
					count7 = 1;
					fx = 0;
				}

			}

		}
		else if (action == skill_L)
		{

			count = 0;
			FX_L.x = role.x;
			if (count8 == 0)
			{
				FX_L.y = role.y - 60;
				loadimage(&img, L"./imgs/闪现/图像5.png", 150, 200, true);
				count8 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;

				if (count8 == 1)
					role.MP -= 50;
					loadimage(&img, L"./imgs/闪现/图像4.png", 150, 200, true);
				if (count8 == 2)
					loadimage(&img, L"./imgs/闪现/图像3.png", 150, 200, true);
				if (count8 == 3)
					loadimage(&img, L"./imgs/闪现/图像9.png", 150, 200, true);
				if (count8 == 4)
					loadimage(&img, L"./imgs/闪现/图像2.png", 150, 200, true);
				if (count8 == 5) {
					loadimage(&img, L"./imgs/闪现/图像1.png", 150, 200, true);
					role.x -= 300;
					FX_L.x -= 300;
				}
				if (count8 == 6)
					loadimage(&img, L"./imgs/闪现/图像2.png", 150, 200, true);
				if (count8 == 7)
					loadimage(&img, L"./imgs/闪现/图像9.png", 150, 200, true);
				if (count8 == 8)
					loadimage(&img, L"./imgs/闪现/图像3.png", 150, 200, true);
				if (count8 == 9)
					loadimage(&img, L"./imgs/闪现/图像4.png", 150, 200, true);
				if (count8 == 10) {
					loadimage(&img, L"./imgs/闪现/图像5.png", 150, 200, true);
				}
				if (count8 == 11) {
					count8 = 0;
					action = stand;
					skilling = 0;
				}
				count8++;
			}
		}
	}
	if (role.x <= 50)role.x = 50;//1不超出边界
	if (role.x >= 1000)role.x = 1000;

	//是否开启无双
	if (wushuang == 1) {
		if (action == run || action == jump) {
			for (int i = 1; i < 5; i++) {
				if (abs(shadow[i][2] - shadow[i - 1][2]) > 60 || abs(shadow[i][3] - shadow[i - 1][3]) > 60)
				{
					shadow[i][1] = shadow[i - 1][1];
					shadow[i][2] = shadow[i - 1][2];
					shadow[i][3] = shadow[i - 1][3];
				}
			}
			shadow[0][1] = count0;
			shadow[0][2] = role.x;
			shadow[0][3] = role.y;
			for (int j = 1; j < 5; j++) {
				transparentimage_t(NULL, shadow[j][2], shadow[j][3], &Role[shadow[j][1]], 100);
			}
		}
	}


	if (action == stand || action == run || action == jump)
		transparentimage(NULL, role.x, role.y, &Role[count0]);
	else if (action == skill_L)
		transparentimage(NULL, FX_L.x, FX_L.y, &img);
	else
		transparentimage(NULL, role.x, role.y, &img);
	if (skilling > 1 && fx == 1) {
		transparentimage(NULL, FX_I.x, FX_I.y, &img_skill);
	}
	if (action == skill_S && fx == 2) {
		transparentimage_t(NULL, FX_S.x, FX_S.y, &img_skill, 200);
	}
	if (skilling > 1 && fx == 3) {
		transparentimage(NULL, FX_U.x, FX_U.y, &img_skill);
	}



}

//*****************************************************************
//蓝龙**************************************************************
//敌人加载
void enemy_load()
{
	loadimage(&enemy[0], L"./imgs/野怪/蓝龙移动右1.png", 163, 159, true);
	loadimage(&enemy[1], L"./imgs/野怪/蓝龙移动右2.png", 163, 159, true);
	loadimage(&enemy[2], L"./imgs/野怪/蓝龙移动右3.png", 163, 159, true);
	loadimage(&enemy[3], L"./imgs/野怪/蓝龙移动右4.png", 163, 159, true);
	loadimage(&enemy[4], L"./imgs/野怪/蓝龙移动右5.png", 163, 159, true);
	loadimage(&enemy[5], L"./imgs/野怪/蓝龙移动1.png", 163, 159, true);
	loadimage(&enemy[6], L"./imgs/野怪/蓝龙移动2.png", 163, 159, true);
	loadimage(&enemy[7], L"./imgs/野怪/蓝龙移动3.png", 163, 159, true);
	loadimage(&enemy[8], L"./imgs/野怪/蓝龙移动4.png", 163, 159, true);
	loadimage(&enemy[9], L"./imgs/野怪/蓝龙移动5.png", 163, 159, true);
	loadimage(&enemy[10], L"./imgs/蓝龙攻击/蓝龙攻击1.png", 303, 193, true);
	loadimage(&enemy[11], L"./imgs/蓝龙攻击/蓝龙攻击2.png", 303, 193, true);
	loadimage(&enemy[12], L"./imgs/蓝龙攻击/蓝龙攻击3.png", 303, 193, true);
	loadimage(&enemy[13], L"./imgs/蓝龙攻击/蓝龙攻击4.png", 303, 193, true);
	loadimage(&enemy[14], L"./imgs/蓝龙攻击/蓝龙攻击5.png", 303, 193, true);
	loadimage(&enemy[15], L"./imgs/蓝龙攻击/蓝龙攻击6.png", 303, 193, true);
	loadimage(&enemy[16], L"./imgs/蓝龙攻击/蓝龙攻击7.png", 303, 193, true);
	loadimage(&enemy[17], L"./imgs/蓝龙攻击/蓝龙攻击8.png", 303, 193, true);
	loadimage(&enemy[18], L"./imgs/蓝龙攻击/蓝龙攻击9.png", 303, 193, true);
	loadimage(&enemy[19], L"./imgs/蓝龙攻击/蓝龙攻击10.png", 303, 193, true);
	loadimage(&enemy[20], L"./imgs/蓝龙攻击/蓝龙攻击右1.png", 303, 193, true);
	loadimage(&enemy[21], L"./imgs/蓝龙攻击/蓝龙攻击右2.png", 303, 193, true);
	loadimage(&enemy[22], L"./imgs/蓝龙攻击/蓝龙攻击右3.png", 303, 193, true);
	loadimage(&enemy[23], L"./imgs/蓝龙攻击/蓝龙攻击右4.png", 303, 193, true);
	loadimage(&enemy[24], L"./imgs/蓝龙攻击/蓝龙攻击右5.png", 303, 193, true);
	loadimage(&enemy[25], L"./imgs/蓝龙攻击/蓝龙攻击右6.png", 303, 193, true);
	loadimage(&enemy[26], L"./imgs/蓝龙攻击/蓝龙攻击右7.png", 303, 193, true);
	loadimage(&enemy[27], L"./imgs/蓝龙攻击/蓝龙攻击右8.png", 303, 193, true);
	loadimage(&enemy[28], L"./imgs/蓝龙攻击/蓝龙攻击右9.png", 303, 193, true);
	loadimage(&enemy[29], L"./imgs/蓝龙攻击/蓝龙攻击右10.png", 303, 193, true);
	loadimage(&enemy[30], L"./imgs/蓝龙旋转升空/蓝龙旋转1.png", 163, 159, true);
	loadimage(&enemy[31], L"./imgs/蓝龙旋转升空/蓝龙旋转2.png", 163, 159, true);
	loadimage(&enemy[32], L"./imgs/蓝龙旋转升空/蓝龙旋转3.png", 163, 159, true);
	loadimage(&enemy[33], L"./imgs/蓝龙旋转升空/蓝龙旋转4.png", 163, 159, true);
	loadimage(&enemy[34], L"./imgs/蓝龙旋转升空/蓝龙旋转5.png", 163, 159, true);
	loadimage(&enemy[35], L"./imgs/蓝龙旋转升空/蓝龙旋转6.png", 163, 159, true);
	loadimage(&enemy[36], L"./imgs/蓝龙旋转升空/蓝龙旋转7.png", 163, 159, true);
	loadimage(&enemy[37], L"./imgs/蓝龙旋转升空/蓝龙旋转右1.png", 163, 159, true);
	loadimage(&enemy[38], L"./imgs/蓝龙旋转升空/蓝龙旋转右2.png", 163, 159, true);
	loadimage(&enemy[39], L"./imgs/蓝龙旋转升空/蓝龙旋转右3.png", 163, 159, true);
	loadimage(&enemy[40], L"./imgs/蓝龙旋转升空/蓝龙旋转右4.png", 163, 159, true);
	loadimage(&enemy[41], L"./imgs/蓝龙旋转升空/蓝龙旋转右5.png", 163, 159, true);
	loadimage(&enemy[42], L"./imgs/蓝龙旋转升空/蓝龙旋转右6.png", 163, 159, true);
	loadimage(&enemy[43], L"./imgs/蓝龙旋转升空/蓝龙旋转右7.png", 163, 159, true);
	loadimage(&enemy[44], L"./imgs/蓝龙特效/特效1.png", 100, 100, true);
	loadimage(&enemy[45], L"./imgs/蓝龙特效/特效2.png", 100, 100, true);
	loadimage(&enemy[46], L"./imgs/蓝龙特效/特效3.png", 100, 100, true);
	loadimage(&enemy[47], L"./imgs/蓝龙特效/特效4.png", 70, 70, true);
	loadimage(&enemy[48], L"./imgs/蓝龙特效/特效5.png", 70, 70, true);
	loadimage(&enemy[49], L"./imgs/蓝龙特效/特效6.png", 70, 70, true);
	loadimage(&enemy[50], L"./imgs/蓝龙特效/特效7.png", 70, 70, true);
	loadimage(&enemy[51], L"./imgs/猫猫移动/猫猫移动右1.png", 100, 100, true);
	loadimage(&enemy[52], L"./imgs/猫猫移动/猫猫移动右2.png", 100, 100, true);
	loadimage(&enemy[53], L"./imgs/猫猫移动/猫猫移动右3.png", 100, 100, true);
	loadimage(&enemy[54], L"./imgs/猫猫移动/猫猫移动右4.png", 100, 100, true);
	loadimage(&enemy[55], L"./imgs/猫猫移动/猫猫移动1.png", 100, 100, true);
	loadimage(&enemy[56], L"./imgs/猫猫移动/猫猫移动2.png", 100, 100, true);
	loadimage(&enemy[57], L"./imgs/猫猫移动/猫猫移动3.png", 100, 100, true);
	loadimage(&enemy[58], L"./imgs/猫猫移动/猫猫移动4.png", 100, 100, true);
	loadimage(&enemy[59], L"./imgs/猫攻击/猫攻击右1.png", 184, 150, true);
	loadimage(&enemy[60], L"./imgs/猫攻击/猫攻击右2.png", 184, 150, true);
	loadimage(&enemy[61], L"./imgs/猫攻击/猫攻击右3.png", 184, 150, true);
	loadimage(&enemy[62], L"./imgs/猫攻击/猫攻击右4.png", 184, 150, true);
	loadimage(&enemy[63], L"./imgs/猫攻击/猫攻击右5.png", 184, 150, true);
	loadimage(&enemy[64], L"./imgs/猫攻击/猫攻击右6.png", 184, 150, true);
	loadimage(&enemy[65], L"./imgs/猫攻击/猫攻击右7.png", 184, 150, true);
	loadimage(&enemy[66], L"./imgs/猫攻击/猫攻击右8.png", 184, 150, true);
	loadimage(&enemy[67], L"./imgs/猫攻击/猫攻击右9.png", 184, 150, true);
	loadimage(&enemy[68], L"./imgs/猫攻击/猫攻击右10.png", 184, 150, true);
	loadimage(&enemy[69], L"./imgs/猫攻击/猫攻击右11.png", 184, 150, true);
	loadimage(&enemy[70], L"./imgs/猫攻击/猫攻击右12.png", 184, 150, true);
	loadimage(&enemy[71], L"./imgs/猫攻击/猫攻击右13.png", 184, 150, true);
	loadimage(&enemy[72], L"./imgs/猫攻击/猫攻击右14.png", 184, 150, true);
	loadimage(&enemy[73], L"./imgs/猫攻击/猫攻击1.png", 184, 150, true);
	loadimage(&enemy[74], L"./imgs/猫攻击/猫攻击2.png", 184, 150, true);
	loadimage(&enemy[75], L"./imgs/猫攻击/猫攻击3.png", 184, 150, true);
	loadimage(&enemy[76], L"./imgs/猫攻击/猫攻击4.png", 184, 150, true);
	loadimage(&enemy[77], L"./imgs/猫攻击/猫攻击5.png", 184, 150, true);
	loadimage(&enemy[78], L"./imgs/猫攻击/猫攻击6.png", 184, 150, true);
	loadimage(&enemy[79], L"./imgs/猫攻击/猫攻击7.png", 184, 150, true);
	loadimage(&enemy[80], L"./imgs/猫攻击/猫攻击8.png", 184, 150, true);
	loadimage(&enemy[81], L"./imgs/猫攻击/猫攻击9.png", 184, 150, true);
	loadimage(&enemy[82], L"./imgs/猫攻击/猫攻击10.png", 184, 150, true);
	loadimage(&enemy[83], L"./imgs/猫攻击/猫攻击11.png", 184, 150, true);
	loadimage(&enemy[84], L"./imgs/猫攻击/猫攻击12.png", 184, 150, true);
	loadimage(&enemy[85], L"./imgs/猫攻击/猫攻击13.png", 184, 150, true);
	loadimage(&enemy[86], L"./imgs/猫攻击/猫攻击14.png", 184, 150, true);
	loadimage(&enemy[87], L"./imgs/猫攻击/猫特效.png", 50, 50, true);
	loadimage(&enemy[88], L"./imgs/猫攻击/猫特效.png", 60, 60, true);
	loadimage(&enemy[89], L"./imgs/猫攻击/猫特效.png", 70, 70, true);
	loadimage(&enemy[90], L"./imgs/boss/boss行走1.png", 200, 200, true);
	loadimage(&enemy[91], L"./imgs/boss/boss行走2.png", 200, 200, true);
	loadimage(&enemy[92], L"./imgs/boss/boss行走3.png", 200, 200, true);
	loadimage(&enemy[93], L"./imgs/boss/boss行走4.png", 200, 200, true);
	loadimage(&enemy[94], L"./imgs/boss/boss行走5.png", 200, 200, true);
	loadimage(&enemy[95], L"./imgs/boss/boss行走右1.png", 200, 200, true);
	loadimage(&enemy[96], L"./imgs/boss/boss行走右2.png", 200, 200, true);
	loadimage(&enemy[97], L"./imgs/boss/boss行走右3.png", 200, 200, true);
	loadimage(&enemy[98], L"./imgs/boss/boss行走右4.png", 200, 200, true);
	loadimage(&enemy[99], L"./imgs/boss/boss行走右5.png", 200, 200, true);
	loadimage(&enemy[100], L"./imgs/boss/boss冲击波1.png", 600, 300, true);
	loadimage(&enemy[101], L"./imgs/boss/boss冲击波2.png", 600, 300, true);
	loadimage(&enemy[102], L"./imgs/boss/boss冲击波3.png", 600, 300, true);
	loadimage(&enemy[103], L"./imgs/boss/boss冲击波4.png", 600, 300, true);
	loadimage(&enemy[104], L"./imgs/boss/boss冲击波5.png", 600, 300, true);
	loadimage(&enemy[105], L"./imgs/boss/boss冲击波6.png", 600, 300, true);
	loadimage(&enemy[106], L"./imgs/boss/boss冲击波7.png", 600, 300, true);
	loadimage(&enemy[107], L"./imgs/boss/boss冲击波8.png", 600, 300, true);
	loadimage(&enemy[108], L"./imgs/boss/boss冲击波9.png", 600, 300, true);
	loadimage(&enemy[109], L"./imgs/boss/boss冲击波10.png", 600, 300, true);
	loadimage(&enemy[110], L"./imgs/boss/boss冲击波右1.png", 600, 300, true);
	loadimage(&enemy[111], L"./imgs/boss/boss冲击波右2.png", 600, 300, true);
	loadimage(&enemy[112], L"./imgs/boss/boss冲击波右3.png", 600, 300, true);
	loadimage(&enemy[113], L"./imgs/boss/boss冲击波右4.png", 600, 300, true);
	loadimage(&enemy[114], L"./imgs/boss/boss冲击波右5.png", 600, 300, true);
	loadimage(&enemy[115], L"./imgs/boss/boss冲击波右6.png", 600, 300, true);
	loadimage(&enemy[116], L"./imgs/boss/boss冲击波右7.png", 600, 300, true);
	loadimage(&enemy[117], L"./imgs/boss/boss冲击波右8.png", 600, 300, true);
	loadimage(&enemy[118], L"./imgs/boss/boss冲击波右9.png", 600, 300, true);
	loadimage(&enemy[119], L"./imgs/boss/boss冲击波右10.png", 600, 300, true);
	loadimage(&enemy[120], L"./imgs/boss/boss技能1.png", 450, 500, true);
	loadimage(&enemy[121], L"./imgs/boss/boss技能2.png", 450, 500, true);
	loadimage(&enemy[122], L"./imgs/boss/boss技能3.png", 450, 500, true);
	loadimage(&enemy[123], L"./imgs/boss/boss技能4.png", 450, 500, true);
	loadimage(&enemy[124], L"./imgs/boss/boss技能5.png", 450, 500, true);
	loadimage(&enemy[125], L"./imgs/boss/boss技能6.png", 450, 500, true);
	loadimage(&enemy[126], L"./imgs/boss/boss技能7.png", 450, 500, true);
	loadimage(&enemy[127], L"./imgs/boss/boss技能8.png", 450, 500, true);
	loadimage(&enemy[128], L"./imgs/boss/boss技能9.png", 450, 500, true);
	loadimage(&enemy[129], L"./imgs/boss/boss技能10.png", 450, 500, true);
	loadimage(&enemy[130], L"./imgs/boss/boss技能11.png", 450, 500, true);
	loadimage(&enemy[131], L"./imgs/boss/boss技能12.png", 450, 500, true);
	loadimage(&enemy[132], L"./imgs/boss/boss技能右1.png", 450, 500, true);
	loadimage(&enemy[133], L"./imgs/boss/boss技能右2.png", 450, 500, true);
	loadimage(&enemy[134], L"./imgs/boss/boss技能右3.png", 450, 500, true);
	loadimage(&enemy[135], L"./imgs/boss/boss技能右4.png", 450, 500, true);
	loadimage(&enemy[136], L"./imgs/boss/boss技能右5.png", 450, 500, true);
	loadimage(&enemy[137], L"./imgs/boss/boss技能右6.png", 450, 500, true);
	loadimage(&enemy[138], L"./imgs/boss/boss技能右7.png", 450, 500, true);
	loadimage(&enemy[139], L"./imgs/boss/boss技能右8.png", 450, 500, true);
	loadimage(&enemy[140], L"./imgs/boss/boss技能右9.png", 450, 500, true);
	loadimage(&enemy[141], L"./imgs/boss/boss技能右10.png", 450, 500, true);
	loadimage(&enemy[142], L"./imgs/boss/boss技能右11.png", 450, 500, true);
	loadimage(&enemy[143], L"./imgs/boss/boss技能右12.png", 450, 500, true);
}
void enemy_move()
{
	static int enemy_count;
	static int update0 = clock();
	static int update1 = clock();
	int time1 = clock();
	int time = clock();
	if (enemy_right)
	{
		if (enemy_count >= 4)
		{
			enemy_count = 0;
		}
		if (time - update0 >= 80)
		{
			enemy_count++;
			update0 = time;
		}
	}
	else if (enemy_right == false)
	{
		if (enemy_count < 5)
		{
			enemy_count = 5;
		}
		else if (enemy_count == 9)
		{
			enemy_count = 5;
		}
		if (time - update0 >= 80)
		{
			enemy_count++;
			update0 = time;

		}
	}
	transparentimage(NULL, enemy_1.x, enemy_1.y, &enemy[enemy_count]);
	if (enemy_state == 2)
	{
		if (effect == -1 && action != skill_U)
		{
			effect = 44;
		}
		else if (effect == -1 && action == skill_U)
		{
			effect = 47;
		}
		transparentimage(NULL, enemy_1.x, enemy_1.y, &enemy[enemy_count]);
		if (time1 - update1 > 50)
		{
			update1 = time1;
			effect++;
		}
		if (effect < 47 && effect>43 && action != skill_U)
		{
			transparentimage(NULL, enemy_1.x + 30, enemy_1.y + 30, &enemy[effect]);
		}
		else if (effect < 50 && action == skill_U)
		{
			transparentimage(NULL, enemy_1.x + 30, enemy_1.y + 30, &enemy[effect]);
		}
		else
		{
			effect = -2;
		}
		printf("%d\n", effect);
	}

}
//蓝龙移动
void enemy_moving()
{
	int move;
	int role_center = role.x + 54;
	int enemy_center = enemy_1.x + 81;
	int distance = role_center - enemy_center;
	if (abs(distance) > 168)
	{
		if (distance > 0)
		{
			enemy_right = true;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_1.x < 1100)
				{
					enemy_1.x += 5;
				}
			}
		}
		else if (distance < 0)
		{
			enemy_right = false;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_1.x > 50)
				{
					enemy_1.x -= 5;
				}
			}
		}
	}
	//printf("%d   %d\n", distance ,enemy_1.y);
}
//蓝龙攻击
void enemy_attack()
{
	static int enemy_count;
	if (enemy_state == 1)
	{
		static int update0 = clock();
		int time = clock();
		if (enemy_right == false)
		{

			if (enemy_count >= 19 || enemy_count < 10)
			{
				enemy_count = 10;
			}
			if (time - update0 >= 80)
			{
				enemy_count++;
				update0 = time;
			}
		}
		else if (enemy_right)
		{
			if (enemy_count >= 29 || enemy_count < 20)
			{
				enemy_count = 20;
			}
			if (time - update0 >= 80)
			{
				enemy_count++;
				update0 = time;
			}
		}
		if ((enemy_count == 29 || enemy_count == 19) && enemy_state != 2)
		{
			enemy_state = 0;
		}
	}

	transparentimage(NULL, enemy_1.x - 90, enemy_1.y, &enemy[enemy_count]);

}
//蓝龙挨打1  击退
void enemy_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_1.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//掌受击距离
	int distance1 = role_center3 - enemy_center1;//拳受击距离
	int distance2 = fire_center - enemy_center1;//火焰受击距离
	if (judge_benten == 10)
	{
		if (effect == -2)
		{
			effect = -1;
		}
		judge_benten = 0;
		enemy_state = 0;
	}
	printf("%d   %d   %d\n", distance0, distance1, distance2);
	if ((fx == 1 && distance2 < 0) || distance0 < 0)
	{
		if (time - update0 >= 70 && judge_benten < 5)
		{
			update0 = time;
			enemy_1.x += 10;
			enemy_1.y -= 5;
			judge_benten++;
		}
		else if (time - update0 >= 70 && judge_benten < 10)
		{
			update0 = time;
			enemy_1.x += 10;
			enemy_1.y += 5;
			judge_benten++;
		}
	}
	else if ((fx == 1 && distance2 > 0) || distance0 > 0)
	{
		if (time - update0 >= 70 && judge_benten < 5)
		{
			update0 = time;
			enemy_1.x -= 10;
			enemy_1.y -= 5;
			judge_benten++;
		}
		else if (time - update0 >= 70 && judge_benten < 10)
		{
			update0 = time;
			enemy_1.x -= 10;
			enemy_1.y += 5;
			judge_benten++;
		}
		//printf("%d   %d\n", enemy_1.x, enemy_1.y);
	}
}

void enemy_judge()
{
	static int update = clock();
	int time = clock();
	int role_center1 = role.x + 54;
	enemy_center1 = enemy_1.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int thunder_center = FX_U.x + 125;
	int distance = role_center1 - enemy_center1;//怪攻击距离
	int distance0 = role_center2 - enemy_center1;//掌受击距离
	int distance1 = role_center3 - enemy_center1;//拳受击距离
	int distance2 = fire_center - enemy_center1;//火焰受击距离
	int distance3 = thunder_center - enemy_center1;//雷电受击距离
	if (enemy_1.HP <= 0) {
		enemy_1_die = 1;
		enemy_die += enemy_1_die;
	}
	if (action == skill_O)
		enemy_1.HP -= 1000;
	if ((action == skill_J && (abs(distance0) < 171 || abs(distance1) < 181)) || (fx == 1 && abs(distance2) < 100))
	{
		if (action == skill_J)
			enemy_1.HP -= 10;
		if (action == skill_I)
			enemy_1.HP -= 10;

		enemy_state = 2;
	}
	else if (action == skill_U && abs(distance3) < 206)
	{
		if (action == skill_U)
			enemy_1.HP -= 10;
		enemy_state = 2;
	}
	if (time - update >= 3000)
	{
		if (abs(distance) < 170)
		{
			update = time;
			enemy_state = 1;
		}
	}
	switch (enemy_state)
	{
	case 0:
		enemy_moving();
		enemy_move();
		break;
	case 1:
		enemy_attack();
		break;
	case 2:
		enemy_beaten();
		enemy_move();
		break;
	default:;
	}
}
//蓝龙**************************************************************
//猫****************************************************************
void cat_move()
{
	static int enemy_count;
	static int update0 = clock();
	static int update1 = clock();
	int time1 = clock();
	int time = clock();
	if (cat_right)
	{

		if (enemy_count >= 54||enemy_count<51)
		{
			enemy_count = 51;
		}
		if (time - update0 >= 90)
		{
			enemy_count++;
			update0 = time;
		}
	}
	else if (cat_right == false)
	{
		if (enemy_count < 55||enemy_count>58)
		{
			enemy_count = 55;
		}
		else if (enemy_count == 58)
		{
			enemy_count = 55;
		}
		if (time - update0 >= 90)
		{
			enemy_count++;
			update0 = time;

		}
	}
	transparentimage(NULL, enemy_cat.x, enemy_cat.y, &enemy[enemy_count]);
	if (cat_state == 2)
	{
		if (cat_effect == -1 && action != skill_U)
		{
			cat_effect = 87;
		}
		else if (cat_effect == -1 && action == skill_U)
		{
			cat_effect = 47;
		}
		transparentimage(NULL, enemy_cat.x, enemy_cat.y, &enemy[enemy_count]);
		if (time1 - update1 > 50)
		{
			update1 = time1;
			cat_effect++;
		}

		if (cat_effect < 90 && cat_effect>86 && action != skill_U)
		{
			transparentimage(NULL, enemy_cat.x + 30, enemy_cat.y + 30, &enemy[cat_effect]);
		}
		else if (cat_effect < 50 && action == skill_U)
		{
			transparentimage(NULL, enemy_cat.x + 30, enemy_cat.y + 30, &enemy[cat_effect]);
		}
		else
		{
			cat_effect = -2;
		}
	}

}
//猫猫移动
void cat_moving()
{
	int move;
	int role_center = role.x + 54;
	int enemy_center = enemy_cat.x + 50;
	int distance = role_center - enemy_center;
	if (abs(distance) > 168)
	{
		if (distance > 0)
		{
			cat_right = true;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_cat.x < 1100)
				{
					enemy_cat.x += 7;//移速
				}
			}
		}
		else if (distance < 0)
		{
			cat_right = false;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_cat.x > 50)
				{
					enemy_cat.x -= 7;
				}
			}
		}
	}
	//printf("%d   %d\n", distance ,enemy_1.y);
}
//猫猫攻击
void cat_attack()
{
	static int enemy_count;
	if (cat_state == 1)
	{
		static int update0 = clock();
		int time = clock();
		if (cat_right == false)
		{

			if (enemy_count >= 86 || enemy_count < 73)
			{
				enemy_count = 73;
			}
			if (time - update0 >= 80)
			{
				enemy_cat.x -= 6;
				enemy_count++;
				update0 = time;
			}
		}
		else if (enemy_right)
		{
			if (enemy_count >= 72 || enemy_count < 59)
			{
				enemy_count = 59;
			}
			if (time - update0 >= 80)
			{
				enemy_cat.x += 6;
				enemy_count++;
				update0 = time;
			}
		}
		if ((enemy_count == 86 || enemy_count == 72) && cat_state != 2)
		{
			cat_state = 0;
		}
	}
	transparentimage(NULL, enemy_cat.x - 60, enemy_cat.y - 25, &enemy[enemy_count]);

}
//猫猫挨打1  击退
void cat_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_cat.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//掌受击距离
	int distance1 = role_center3 - enemy_center1;//拳受击距离
	int distance2 = fire_center - enemy_center1;//火焰受击距离
	if (judge_benten_cat == 10)
	{
		if (cat_effect == -2)
		{
			cat_effect = -1;
		}
		judge_benten_cat = 0;
		cat_state = 0;
	}
	//printf("%d   %d   %d\n", distance0, distance1, distance2);
	if ((fx == 1 && distance2 < 0) || distance0 < 0)
	{
		if (time - update0 >= 70 && judge_benten_cat < 5)
		{
			update0 = time;
			enemy_cat.x += 10;
			enemy_cat.y -= 5;
			judge_benten_cat++;
		}
		else if (time - update0 >= 70 && judge_benten_cat < 10)
		{
			update0 = time;
			enemy_cat.x += 10;
			enemy_cat.y += 5;
			judge_benten_cat++;
		}
	}
	else if ((fx == 1 && distance2 > 0) || distance0 > 0)
	{
		if (time - update0 >= 70 && judge_benten_cat < 5)
		{
			update0 = time;
			enemy_cat.x -= 10;
			enemy_cat.y -= 5;
			judge_benten_cat++;
		}
		else if (time - update0 >= 70 && judge_benten_cat < 10)
		{
			update0 = time;
			enemy_cat.x -= 10;
			enemy_cat.y += 5;
			judge_benten_cat++;
		}
		//printf("%d   %d\n", enemy_1.x, enemy_1.y);
	}
}
//猫猫状态判断
void cat_judge()
{
	static int update = clock();
	int time = clock();
	int role_center1 = role.x + 54;
	enemy_center2 = enemy_cat.x + 50;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int thunder_center = FX_U.x + 125;
	int distance = role_center1 - enemy_center2;//怪攻击距离
	int distance0 = role_center2 - enemy_center2;//掌受击距离
	int distance1 = role_center3 - enemy_center2;//拳受击距离
	int distance2 = fire_center - enemy_center2;//火焰受击距离
	int distance3 = thunder_center - enemy_center2;//雷电受击距离
	if (enemy_cat.HP <= 0) {
		enemy_cat_die = 1;
		enemy_die += enemy_cat_die;
	}
	if (action == skill_O)
		enemy_cat.HP -= 1000;
	if ((action == skill_J && (abs(distance0) < 140 || abs(distance1) < 152)) || (fx == 1 && abs(distance2) < 72))
	{
		if (action == skill_J)
			enemy_cat.HP -= 10;
		if (action == skill_I)
			enemy_cat.HP -= 10;

		cat_state = 2;
	}
	else if (action == skill_U && abs(distance3) < 175)
	{
		if (action == skill_U)
			enemy_cat.HP -= 10;
		cat_state = 2;
	}
	//printf("%d %d  %d\n", distance, enemy_center2,role_center1);
	if (time - update >= 5000)
	{
		if (abs(distance) < 175)
		{
			update = time;
			cat_state = 1;
		}
	}
	switch (cat_state)
	{
	case 0:
		cat_moving();
		cat_move();
		break;
	case 1:
		cat_attack();
		break;
	case 2:
		cat_beaten();
		cat_move();
		break;
	default:;
	}
}
//猫****************************************************************
//boss**************************************************************
void boss_move()
{
	static int enemy_count;
	static int update0 = clock();
	static int update1 = clock();
	int time1 = clock();
	int time = clock();
	if (boss_right)
	{

		if (enemy_count >= 99)
		{
			enemy_count = 95;
		}
		if (time - update0 >= 90)
		{
			enemy_count++;
			update0 = time;
		}
	}
	else if (boss_right == false)
	{
		if (enemy_count < 90)
		{
			enemy_count = 90;
		}
		else if (enemy_count == 94)
		{
			enemy_count = 90;
		}
		if (time - update0 >= 90)
		{
			enemy_count++;
			update0 = time;

		}
	}
	transparentimage(NULL, enemy_boss.x, enemy_boss.y, &enemy[enemy_count]);
	if (boss_state == 2)
	{
		if (boss_effect == -1 && action != skill_U)
		{
			boss_effect = 87;
		}
		else if (boss_effect == -1 && action == skill_U)
		{
			boss_effect = 47;
		}
		transparentimage(NULL, enemy_boss.x, enemy_boss.y, &enemy[enemy_count]);
		if (time1 - update1 > 50)
		{
			update1 = time1;
			boss_effect++;
		}
		if (boss_effect < 90 && boss_effect>86 && action != skill_U)
		{
			transparentimage(NULL, enemy_boss.x + 10, enemy_boss.y + 30, &enemy[boss_effect]);
		}
		else if (boss_effect < 50 && action == skill_U)
		{
			transparentimage(NULL, enemy_1.x + 30, enemy_1.y + 30, &enemy[boss_effect]);
		}
		else
		{
			boss_effect = -2;
		}
		printf("%d\n", boss_effect);
	}

}
//boss移动
void boss_moving()
{
	int move;
	int role_center = role.x + 54;
	int enemy_center = enemy_boss.x + 100;
	int distance = role_center - enemy_center;
	if (abs(distance) > 150)
	{
		if (distance > 0)
		{
			boss_right = true;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_boss.x < 1100)
				{
					enemy_boss.x += 5;
				}
			}
		}
		else if (distance < 0)
		{
			boss_right = false;
			move = rand() % 2;
			if (!move)
			{

				if (enemy_boss.x > 50)
				{
					enemy_boss.x -= 5;
				}
			}
		}
	}
	//printf("%d   %d\n", distance ,enemy_1.y);
}
//boss攻击 1
void boss_attack1()
{
	static int enemy_count;
	if (boss_state == 1)
	{
		static int update0 = clock();
		int time = clock();
		if (boss_right == false)
		{
			printf("%d\n", enemy_count);

			if (enemy_count >= 109 || enemy_count < 100)
			{
				enemy_count = 100;
			}
			if (time - update0 >= 200)
			{
				if (enemy_count == 104 || enemy_count == 105)
				{
					boss_judge_benten = 1;
				}
				else if (enemy_count == 106)
				{
					boss_judge_benten = 0;
				}
				enemy_count++;
				update0 = time;
			}
		}
		else if (boss_right)
		{
			if (enemy_count >= 119 || enemy_count < 110)
			{
				if (enemy_count == 114 || enemy_count == 115)
				{
					boss_judge_benten = 1;
				}
				else if (enemy_count == 116)
				{
					boss_judge_benten = 0;
				}
				enemy_count = 110;
			}
			if (time - update0 >= 250)
			{
				enemy_count++;
				update0 = time;
			}
		}
		if ((enemy_count == 109 || enemy_count == 119) && boss_state != 2)
		{
			boss_state = 0;
		}
	}
	if (boss_right == false)
	{
		transparentimage(NULL, enemy_boss.x - 250, enemy_boss.y - 45, &enemy[enemy_count]);

	}
	else
	{
		transparentimage(NULL, enemy_boss.x - 250, enemy_boss.y - 45, &enemy[enemy_count]);
	}
}
//boss挨打1  击退
void boss_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_boss.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//掌受击距离
	int distance1 = role_center3 - enemy_center1;//拳受击距离
	int distance2 = fire_center - enemy_center1;//火焰受击距离
	if (judge_benten_boss == 10)
	{
		if (boss_effect == -2)
		{
			boss_effect = -1;
		}
		judge_benten_boss = 0;
		boss_state = 0;
	}
	//printf("%d   %d   %d\n", distance0, distance1, distance2);
	if ((fx == 1 && distance2 < 0) || distance0 < 0)
	{
		if (time - update0 >= 70 && judge_benten_boss < 5)
		{
			update0 = time;
			enemy_boss.x += 10;
			enemy_boss.y -= 5;
			judge_benten_boss++;
		}
		else if (time - update0 >= 70 && judge_benten_boss < 10)
		{
			update0 = time;
			enemy_boss.x += 10;
			enemy_boss.y += 5;
			judge_benten_boss++;
		}
	}
	else if ((fx == 1 && distance2 > 0) || distance0 > 0)
	{
		if (time - update0 >= 70 && judge_benten_boss < 5)
		{
			update0 = time;
			enemy_boss.x -= 10;
			enemy_boss.y -= 5;
			judge_benten_boss++;
		}
		else if (time - update0 >= 70 && judge_benten_boss < 10)
		{
			update0 = time;
			enemy_boss.x -= 10;
			enemy_boss.y += 5;
			judge_benten_boss++;
		}
		//printf("%d   %d\n", enemy_1.x, enemy_1.y);
	}
}
//boos 技能回血
void boss_skill()
{
	static int enemy_count;
	if (boss_state == 3)
	{
		static int update0 = clock();
		int time = clock();
		if (boss_right == false)
		{
			printf("%d\n", enemy_count);

			if (enemy_count >= 131 || enemy_count < 120)
			{
				enemy_count = 120;
			}
			if (time - update0 >= 150)
			{
				enemy_count++;
				update0 = time;
			}
		}
		else if (boss_right)
		{
			if (enemy_count >= 132 || enemy_count < 143)
			{
				enemy_count = 132;
			}
			if (time - update0 >= 150)
			{
				enemy_count++;
				update0 = time;
			}
		}
		if ((enemy_count == 143 || enemy_count == 131) && boss_state == 3)
		{
			if (enemy_boss.HP < 900)
			{
				enemy_boss.HP += 100;
			}
			boss_state = 0;
		}
	}
	transparentimage(NULL, enemy_boss.x - 145, enemy_boss.y - 165, &enemy[enemy_count]);
}
//boss状态判断
void boss_judge()
{
	static int update0 = clock();
	static int update = clock();
	int time0 = clock();
	int time = clock();
	int role_center1 = role.x + 54;
	enemy_center3 = enemy_boss.x + 100;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int thunder_center = FX_U.x + 125;
	int distance = role_center1 - enemy_center3;//怪攻击距离
	int distance0 = role_center2 - enemy_center3;//掌受击距离
	int distance1 = role_center3 - enemy_center3;//拳受击距离
	int distance2 = fire_center - enemy_center3;//火焰受击距离
	int distance3 = thunder_center - enemy_center3;//雷电受击距离
	if (enemy_boss.HP <= 0) {
		enemy_boss_die = 5;

		enemy_die += enemy_boss_die;
	}
	if (action == skill_O)
		enemy_boss.HP -= 1000;
	if ((action == skill_J && (abs(distance0) < 191 || abs(distance1) < 201)) || (fx == 1 && abs(distance2) < 122))
	{
		if (action == skill_J)
			enemy_boss.HP -=10;
		if (action == skill_I)
			enemy_boss.HP -= 10;
		boss_state = 2;
	}
	else if (fx == 3 && abs(distance3) < 206)
	{
		if (action == skill_U)
			enemy_boss.HP -= 10;
		boss_state = 2;
	}
	printf("%d   \n", enemy_boss.HP);
	if (time0 - update0 >= 10000&&boss_state!=1)
	{
		update0 = time0;
		boss_state = 3;
	}
	if (time - update >= 6000)
	{
		update = time;
		if (abs(distance) < 450)
		{
			boss_state = 1;
		}
	}
	switch (boss_state)
	{
	case 0:
		boss_moving();
		boss_move();
		break;
	case 1:
		boss_attack1();
		break;
	case 2:
		boss_beaten();
		boss_move();
		break;
	case 3:
		boss_skill();
		break;
	default:;
	}
}

void over_cartoon()//成功
{
	IMAGE img_princess, img_boss, img_boss2, img_renwu2, img_renwu3, img_background, img_speak, img_bigboss,img_renwu1, img_begin, img_introduce, img_choose, img_back, img_pointer, img_finish, img_round1, img_round2, img_round3;
	int x = 0, y = 0;
	
	loadimage(&img_background, L"./imgs/交互/背景.jpg", window_wide, window_height, true);
	loadimage(&img_renwu1, L"./imgs/交互/人物5.png", 210, 140, true);
	loadimage(&img_boss2, L"./imgs/交互/boss2.png", 202, 240, true);
	loadimage(&img_princess, L"./imgs/交互/公主.png", 395, 260, true);
	loadimage(&img_renwu2, L"./imgs/交互/人物4.png", 167, 260, true);
	loadimage(&img_bigboss, L"./imgs/交互/bigboss.png", 167, 260, true);
	loadimage(&img_speak, L"./imgs/交互/对话框.png", 600, 250, true);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("楷体"));
	transparentimage(NULL, 0, 0, &img_background); //初始背景
	transparentimage(NULL, 100, 300, &img_renwu2);
	transparentimage(NULL, 900, 310, &img_boss2);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("悟空：哈哈，白骨精你也不过如此嘛，快把我的公主放了")); Sleep(1500);
	transparentimage(NULL, 650, 100, &img_bigboss);
	outtextxy(300, 520, _T("邪恶如来：嘿嘿，你以为你赢了？（空灵）")); Sleep(1500);
	outtextxy(300, 550, _T("白骨精：主人，您来了！")); Sleep(1500);
	outtextxy(300, 580, _T("邪恶如来：没用的fw，就这点水平？")); Sleep(1500);
	outtextxy(300, 610, _T("悟空：可恶，可恶！为什么你。。为什么是你")); Sleep(1500);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("邪恶如来：哈哈哈本来不想抛头露面的")); Sleep(1500);
	outtextxy(300, 520, _T("邪恶如来：既然如此，要想就你的小公主，来天庭找我吧")); Sleep(1500);
	transparentimage(NULL, 800, 100, &img_princess);
	outtextxy(300, 550, _T("公主：悟空，不！放我走，放我走")); Sleep(1500);
	outtextxy(300, 580, _T("悟空：我的宝，别怕，俺这就来！")); Sleep(1500);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("未完待续（按enter键结束）"));
	getchar();
	for (x = 0; x > -700; x -= 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //初始背景
		transparentimage(NULL, 800, 100 + x, &img_princess);
		transparentimage(NULL, 100, 300, &img_renwu2);
		transparentimage(NULL, 650, 100 + x, &img_bigboss);
		transparentimage(NULL, 900, 310 + x, &img_boss2);
		EndBatchDraw();
		Sleep(40);
	}
	for (x = 0; x > -700; x -= 15)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //初始背景
		transparentimage(NULL, 100, 300 + x, &img_renwu1);
		EndBatchDraw();
		Sleep(10);
	}

}