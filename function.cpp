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
int cat_state = 0;//èè״̬
int enemy_state = 0;//����״̬
int boss_state = 0;//boss״̬

//����
int enemy_center1;//��������
int enemy_center2;//èè����
int enemy_center3;//boss����


//��ʼվ��
int action = stand;
//�Ƿ�ż���
int skilling = 0;
int move_D = 0;//�Ƿ�����
int move_A = 0;//�Ƿ�����
//���ﳯ���ж�
bool right = true;
bool enemy_right = true;//��������
bool cat_right = true;//èè����
bool boss_right = true;//boss����
//����������Ӧ��ͼ�����ٶ�
int update = 100 * clock();
int fx = 0;//�Ƿ��м�����Ч
int big_skill = 0;//�Ƿ����
int effect = -1;
int cat_effect = -1;
int boss_effect = -1;
//��һ���Ƿ����
int one_over = 0;//1ΪҰ�ֱ�����,2Ϊ������һ��
//�ڶ����Ƿ����
int two_over = 0;
//��������
int enemy_die = 0;
int enemy_1_die = 0;
int enemy_cat_die = 0;
int enemy_boss_die = 0;
int hurting = 0;



//������ͼ
int map_move = 0;
int map_stop = 0;//����1����
//�ƶ��ٶ�
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
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ 
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
//ʵ�ֿ�����͸����
void transparentimage_t(IMAGE* dstimg, int x, int y, IMAGE* srcimg, int i) {
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, i, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ 
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}
IMAGE img_princess, img_boss, img_boss2, img_renwu2, img_renwu3, img_background, img_speak, img_bigboss,img_renwu1, img_begin, img_introduce, img_choose, img_back, img_pointer, img_finish, img_round1, img_round2, img_round3;
void word(int count)
{
	loadimage(&img_princess, L"./imgs/����/����.png", 395, 260, true);
	loadimage(&img_renwu1, L"./imgs/����/����1.png", 395, 260, true);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("����"));
	if (count == 1)
	{
		outtextxy(360, 490, _T("��գ��ɶ񰡡������ҵĹ���")); Sleep(2000);
		outtextxy(360, 520, _T("�׹Ǿ����ٺ٣�С��գ���Ĺ���������"));
		transparentimage(NULL, 650, 100, &img_princess); Sleep(2000);
		outtextxy(360, 550, _T("��գ���ſ��ҵĹ���")); Sleep(2000);
		outtextxy(360, 580, _T("�׹Ǿ�����Ȼ����С����������˿�����Ұ�")); Sleep(2000);
	}
	if (count == 2)
	{
		outtextxy(360, 490, _T("ĳ�������ҵ�������� ��������")); Sleep(2000);
		outtextxy(360, 520, _T("ĳ������come on!!!here!!!")); Sleep(2000);
		outtextxy(360, 550, _T("��գ�����Ҳ!!")); Sleep(2000);
	}
}
//�Ի�
void orign_cartoon()
{
	int x = 0, y = 0;
	loadimage(&img_background, L"./imgs/����/����.jpg", window_wide, window_height, true);

	loadimage(&img_renwu1, L"./imgs/����/����1.png", 210, 140, true);
	loadimage(&img_boss2, L"./imgs/����/boss2.png", 202, 240, true);
	loadimage(&img_princess, L"./imgs/����/����.png", 395, 260, true);
	loadimage(&img_renwu2, L"./imgs/����/����2.png", 167, 260, true);
	for (x = 0; x < 500; x += 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //��ʼ����
		transparentimage(NULL, 650 + x, 100, &img_princess);
		transparentimage(NULL, 100, 300, &img_renwu2);
		transparentimage(NULL, 900 + x, 310, &img_boss2);
		EndBatchDraw();
		Sleep(40);
	}
	for (x = 0; x < 1300; x += 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //��ʼ����
		transparentimage(NULL, 100 + x, 300, &img_renwu1);
		EndBatchDraw();
		Sleep(10);
	}
}
//��ʼ����
void plot()
{
	int count = 0;
	char  W, S, Q, E, M, J;
	loadimage(&img_renwu1, L"./imgs/����/����1.png", 395, 260, true);
	loadimage(&img_speak, L"./imgs/����/�Ի���.png", 580, 170, true);
	loadimage(&img_background, L"./imgs/����/����.jpg", window_wide, window_height, true);
	loadimage(&img_boss2, L"./imgs/����/boss2.png", 202, 240, true);
	loadimage(&img_renwu3, L"./imgs/����/����3.png", 193, 280, true);
	loadimage(&img_renwu2, L"./imgs/����/����2.png", 167, 260, true);
	BeginBatchDraw();
	transparentimage(NULL, 0, 0, &img_background); //��ʼ����
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
			settextstyle(23, 0, _T("����"));
			setbkmode(TRANSPARENT);
			outtextxy(360, 490, _T("�밴��J��"));
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
//����
void backmusic()
{
	mciSendString(L"open ��Ч/����.mp3 alias bk", NULL, 0, NULL);
	mciSendString(L"play bk repeat", NULL, 0, NULL);
}
//��������
void origin()
{
	char  W, S, Q, E;
	int x = -1, count = 1, t = 1;
	int time = clock();
	static int update = clock();
	loadimage(&img_pointer, L"./imgs/����/ָ��.png", 43, 25, true);
	loadimage(&img_begin, L"./imgs/����/��ʼ��Ϸ.png", 242, 69, true);
	loadimage(&img_finish, L"./imgs/����/�˳���Ϸ.png", 242, 69, true);
	loadimage(&img_choose, L"./imgs/����/ѡ��ؿ�.png", 242, 69, true);
	loadimage(&img_introduce, L"./imgs/����/����˵��.png", 242, 69, true);
	loadimage(&img_back, L"./imgs/����/����.png", 242, 69, true);
	loadimage(&img_background, L"./imgs/����/����.jpg", window_wide, window_height, true);
	loadimage(&img_round1, L"./imgs/����/1.png", 242, 69, true);
	loadimage(&img_round2, L"./imgs/����/2.png", 242, 69, true);
	loadimage(&img_round3, L"./imgs/����/3.png", 242, 69, true);
	loadimage(&img_speak, L"./imgs/����/�Ի���.png", 580, 170, true);

	while (1)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //��ʼ����

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
				transparentimage(NULL, 0, 0, &img_background); //��ʼ����
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
			}//����˵��
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
			// 1.�������ֱ���ģʽΪ TRANSPARENT ʵ����������ޱ���ɫ
			settextcolor(RGB(255, 0, 0));
			// 2.����������ɫΪ ��ɫ
			settextstyle(25, 0, _T("����"));

			// 3.�������ִ�С�����壬��������Ϊ���ߡ������塣�����Ϊ 0 ��ʾ����Ӧ,
			// ����_T(��*��)��*�������滻������ʹ�ó��������壬�磺���塢���塢�����



			outtextxy(20, 30, _T("AD���������ƶ�"));
			outtextxy(20, 80, _T("j����ͨ����"));
			outtextxy(20, 400, _T("E������"));
			transparentimage(NULL, 1000, 600, &img_back);
			if (E = GetKeyState('E') < 0)
			{
				t = 1;
			}
		}
		//���Ż�
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
//ԭʼ
/*void loading_music()
{
	TCHAR tmpmp3[_MAX_PATH];
	GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat_s(tmpmp3, _T("�׵�.mp3")); // �����ص���Ƶ����

	HANDLE hFile = CreateFile(tmpmp3, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_TEMPORARY, NULL);
	// ������Դ�ļ��С�������Դ���ڴ桢�õ���Դ��С
	HRSRC hRes = FindResource(NULL, _T("�׵�.mp3"), _T("MP3"));
	// ��Դ ID����������
	HGLOBAL hMem = LoadResource(NULL, hRes);
	DWORD dwSize = SizeofResource(NULL, hRes);
	// д���ļ�
	DWORD dwWrite = 0; // ����д���ֽ�
	WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);


}*/
//��Ƶ��Ԥ����
//������ͼ,ʵ�ֵ�ͼ�ƶ�
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
	// �ṹ��ĵ�������Ա��ʾ�����͸���ȣ�0 ��ʾȫ͸����255 ��ʾ��͸����  
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	// ʹ�� Windows GDI ����ʵ�ְ�͸��λͼ 
	AlphaBlend(dstDC, x, y, w - map_move, h, srcDC, map_move, 0, w - map_move, h, bf);
}

//��ͼ��ʼ��/Ѫ��
void initializtion()
{
	IMAGE img_bk1, img_blood, img_HP, img_MP, enemy_blood, act_blood, enemy_HP,boss_HP,boss_blood;
	if (one_over == 2) {
		move_speed = 35;
		loadimage(&img_bk1, L"./imgs/����2.png", 2800, 700, true);
		transparentimage_BK(NULL, 0, 0, &img_bk1);
	}
	if (one_over < 2) {
		move_speed = 40;
		loadimage(&img_bk1, L"./imgs/����.jpg", 2800, 700, true);
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
		loadimage(&door, L"./imgs/������.png", 256, 278, true);
		transparentimage(NULL, Door.x, Door.y, &door);
	}
	if (abs((role.x + 54) - (Door.x + 128)) <= 70 && GetKeyState('W')) {
		one_over = 2;
		enemy_boss_die = 2;
	}






	loadimage(&img_blood, L"./imgs/Ѫ��/Ѫ��.png", 420, 101, true);
	transparentimage(NULL, 20, 20, &img_blood);


	loadimage(&img_HP, L"./imgs/Ѫ��/Ѫ��1.png", 3, 19, true);
	loadimage(&img_MP, L"./imgs/Ѫ��/����.png", 3, 19, true);
	for (int i = 0; i <= (role.HP / 10); i++) {
		transparentimage(NULL, 123 + i * 3, 67, &img_HP);
	}
	for (int i = 0; (i <= role.MP / 10); i++) {
		transparentimage(NULL, 123 + i * 3, 90, &img_MP);
	}



	loadimage(&enemy_blood, L"./imgs/Ѫ��/Ұ��Ѫ����.png", 100, 101, true);
	loadimage(&enemy_HP, L"./imgs/Ѫ��/����Ѫ��.png", 3, 10, true);
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
		loadimage(&boss_blood, L"./imgs/Ѫ��/bossѪ����.png", 300, 50, true);
		loadimage(&boss_HP, L"./imgs/Ѫ��/Ѫ��1.png", 3, 18, true);

		if (enemy_boss_die == 2) {
			transparentimage(NULL, 700, 20, &boss_blood);
			for (int i = 0; i <= (enemy_boss.HP / 10); i++) {
				transparentimage_t(NULL, 703 + i * 3, 23, &boss_HP, blood_change);
			}
		}
	}
}
//�ؿ��л�

void  change()
{
	IMAGE door;
	if (one_over == 1) {
		Door.x = 900;
		Door.y = 400;

		loadimage(&door, L"./imgs/������.png", 256, 278, true);
		transparentimage(NULL, Door.x, Door.y, &door);
	}
	if (abs((role.x + 54) - (Door.x + 128)) <= 70) {
		one_over = 2;
	}

}
//��������
void role_arise()
{
	IMAGE img;
	loadimage(&img, L"./imgs/�ƶ�/�ƶ���2.png", 138, 128, true);
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


//���ж���
void trump_card() {
	IMAGE img[100], img_bk;
	mciSendString(TEXT("play ./����.mp3"), NULL, 0, NULL);
	loadimage(&img_bk, L"./imgs/���ж���/����.png", window_wide, window_height, true);
	loadimage(&img[0], L"./imgs/���ж���/1000.bmp", 300, 300, true);
	loadimage(&img[1], L"./imgs/���ж���/1001.bmp", 300, 300, true);
	loadimage(&img[2], L"./imgs/���ж���/1002.bmp", 300, 300, true);
	loadimage(&img[3], L"./imgs/���ж���/1003.bmp", 300, 300, true);
	loadimage(&img[4], L"./imgs/���ж���/1004.bmp", 300, 300, true);
	loadimage(&img[5], L"./imgs/���ж���/1005.bmp", 300, 300, true);
	loadimage(&img[6], L"./imgs/���ж���/1006.bmp", 300, 300, true);
	loadimage(&img[7], L"./imgs/���ж���/1007.bmp", 300, 300, true);
	loadimage(&img[8], L"./imgs/���ж���/1008.bmp", 300, 300, true);
	loadimage(&img[9], L"./imgs/���ж���/1009.bmp", 300, 300, true);
	loadimage(&img[10], L"./imgs/���ж���/1010.bmp", 300, 300, true);
	loadimage(&img[11], L"./imgs/���ж���/1011.bmp", 300, 300, true);
	loadimage(&img[12], L"./imgs/���ж���/1012.bmp", 300, 300, true);
	loadimage(&img[13], L"./imgs/���ж���/1013.bmp", 300, 300, true);
	loadimage(&img[14], L"./imgs/���ж���/1014.bmp", 300, 300, true);
	loadimage(&img[15], L"./imgs/���ж���/1015.bmp", 300, 300, true);
	loadimage(&img[16], L"./imgs/���ж���/1015.bmp", 300, 300, true);
	loadimage(&img[17], L"./imgs/���ж���/1015.bmp", 300, 300, true);


	loadimage(&img[18], L"./imgs/���ж���/70003.png", 300, 300, true);
	loadimage(&img[19], L"./imgs/���ж���/70004.png", 300, 300, true);
	loadimage(&img[20], L"./imgs/���ж���/70005.png", 300, 300, true);
	loadimage(&img[21], L"./imgs/���ж���/70006.png", 300, 300, true);
	loadimage(&img[22], L"./imgs/���ж���/70007.png", 300, 300, true);
	loadimage(&img[23], L"./imgs/���ж���/70008.png", 300, 300, true);
	loadimage(&img[24], L"./imgs/���ж���/70009.png", 300, 300, true);
	loadimage(&img[25], L"./imgs/���ж���/70010.png", 300, 300, true);
	loadimage(&img[26], L"./imgs/���ж���/70011.png", 300, 300, true);
	loadimage(&img[27], L"./imgs/���ж���/70012.png", 300, 300, true);
	loadimage(&img[28], L"./imgs/���ж���/70013.png", 300, 300, true);
	loadimage(&img[29], L"./imgs/���ж���/70014.png", 300, 300, true);
	loadimage(&img[30], L"./imgs/���ж���/70015.png", 300, 300, true);
	loadimage(&img[31], L"./imgs/���ж���/70016.png", 300, 300, true);
	loadimage(&img[32], L"./imgs/���ж���/70017.png", 300, 300, true);
	loadimage(&img[33], L"./imgs/���ж���/70018.png", 300, 300, true);
	loadimage(&img[34], L"./imgs/���ж���/70019.png", 300, 300, true);
	loadimage(&img[35], L"./imgs/���ж���/70020.png", 300, 300, true);
	loadimage(&img[36], L"./imgs/���ж���/70021.png", 300, 300, true);
	loadimage(&img[37], L"./imgs/���ж���/70022.png", 300, 300, true);
	loadimage(&img[38], L"./imgs/���ж���/70023.png", 300, 300, true);
	loadimage(&img[39], L"./imgs/���ж���/70024.png", 300, 300, true);
	loadimage(&img[40], L"./imgs/���ж���/70025.png", 300, 300, true);
	loadimage(&img[41], L"./imgs/���ж���/70026.png", 300, 300, true);
	loadimage(&img[42], L"./imgs/���ж���/70027.png", 300, 300, true);
	loadimage(&img[43], L"./imgs/���ж���/70028.png", 300, 300, true);
	loadimage(&img[44], L"./imgs/���ж���/70029.png", 300, 300, true);
	loadimage(&img[45], L"./imgs/���ж���/70030.png", 300, 300, true);
	loadimage(&img[46], L"./imgs/���ж���/70031.png", 300, 300, true);
	loadimage(&img[47], L"./imgs/���ж���/70032.png", 300, 300, true);
	loadimage(&img[48], L"./imgs/���ж���/70032.png", 300, 300, true);
	loadimage(&img[49], L"./imgs/���ж���/70032.png", 300, 300, true);
	loadimage(&img[50], L"./imgs/���ж���/70032.png", 300, 300, true);

	loadimage(&img[51], L"./imgs/���ж���/������1.png", 121, 200, true);
	loadimage(&img[52], L"./imgs/���ж���/������2.png", 131, 200, true);
	loadimage(&img[53], L"./imgs/���ж���/������3.png", 138, 200, true);
	loadimage(&img[54], L"./imgs/���ж���/������3.png", 138, 200, true);
	loadimage(&img[55], L"./imgs/���ж���/������3.png", 138, 200, true);

	loadimage(&img[80], L"./imgs/Ұ��/�����ƶ�1.png", 163, 159, true);
	loadimage(&img[81], L"./imgs/Ұ��/�����ƶ�2.png", 163, 159, true);
	loadimage(&img[82], L"./imgs/Ұ��/�����ƶ�3.png", 163, 159, true);
	loadimage(&img[83], L"./imgs/Ұ��/�����ƶ�4.png", 163, 159, true);
	loadimage(&img[84], L"./imgs/Ұ��/�����ƶ�5.png", 163, 159, true);

	loadimage(&img[85], L"./imgs/è����/è����14.png", 184, 150, true);
	loadimage(&img[86], L"./imgs/boss/boss����1.png", 222, 250, true);

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

//��ɫ����
void role_load()
{
	loadimage(&Role[0], L"./imgs/վ��/��̬��1.png", 118, 126, true);
	loadimage(&Role[1], L"./imgs/վ��/��̬��2.png", 118, 126, true);
	loadimage(&Role[2], L"./imgs/վ��/��̬��3.png", 118, 126, true);
	loadimage(&Role[3], L"./imgs/վ��/��̬��2.png", 118, 126, true);
	loadimage(&Role[6], L"./imgs/վ��/��̬1.png", 118, 126, true);
	loadimage(&Role[7], L"./imgs/վ��/��̬2.png", 118, 126, true);
	loadimage(&Role[8], L"./imgs/վ��/��̬3.png", 118, 126, true);
	loadimage(&Role[9], L"./imgs/վ��/��̬2.png", 118, 126, true);

	loadimage(&Role[10], L"./imgs/�ƶ�/�ƶ���7.png", 167, 105, true);
	loadimage(&Role[11], L"./imgs/�ƶ�/�ƶ���1.png", 138, 128, true);
	loadimage(&Role[12], L"./imgs/�ƶ�/�ƶ���2.png", 138, 128, true);
	loadimage(&Role[13], L"./imgs/�ƶ�/�ƶ�7.png", 167, 105, true);
	loadimage(&Role[14], L"./imgs/�ƶ�/�ƶ�1.png", 138, 128, true);
	loadimage(&Role[15], L"./imgs/�ƶ�/�ƶ�2.png", 138, 128, true);


	loadimage(&Role[16], L"./imgs/�ƶ�/��Ծ��8.png", 106, 165, true);
	loadimage(&Role[17], L"./imgs/�ƶ�/��Ծ��3.png", 106, 165, true);
	loadimage(&Role[18], L"./imgs/�ƶ�/��Ծ��3.png", 106, 165, true);
	loadimage(&Role[19], L"./imgs/�ƶ�/��Ծ��4.png", 106, 165, true);
	loadimage(&Role[20], L"./imgs/�ƶ�/��Ծ��5.png", 106, 165, true);
	loadimage(&Role[21], L"./imgs/�ƶ�/��Ծ��5.png", 106, 165, true);
	loadimage(&Role[22], L"./imgs/�ƶ�/��Ծ��8.png", 106, 165, true);
	loadimage(&Role[23], L"./imgs/�ƶ�/��Ծ��8.png", 106, 165, true);
	loadimage(&Role[24], L"./imgs/�ƶ�/��Ծ8.png", 106, 165, true);
	loadimage(&Role[25], L"./imgs/�ƶ�/��Ծ3.png", 106, 165, true);
	loadimage(&Role[26], L"./imgs/�ƶ�/��Ծ3.png", 106, 165, true);
	loadimage(&Role[27], L"./imgs/�ƶ�/��Ծ4.png", 106, 165, true);
	loadimage(&Role[28], L"./imgs/�ƶ�/��Ծ5.png", 106, 165, true);
	loadimage(&Role[29], L"./imgs/�ƶ�/��Ծ5.png", 106, 165, true);
	loadimage(&Role[30], L"./imgs/�ƶ�/��Ծ8.png", 106, 165, true);
	loadimage(&Role[31], L"./imgs/�ƶ�/��Ծ8.png", 106, 165, true);
}

//�����ƶ�
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
		if (GetKeyState('O') < 0 && action == stand&&role.MP>=300) {//����
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
		else if (GetKeyState('H') < 0) {//��˫
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
		else if (skilling == 0)//û�ڷż���
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
//����չʾ
void role_show()
{
	static IMAGE img;
	static IMAGE img_skill;
	int time = clock();
	static int count0 = 0, count = 0, count1 = 0, count2 = 0, count3 = 0, count4 = 0, count5 = 0, count6 = 0, count7 = 0, count8 = 0;

	//��ɫ����
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
				loadimage(&img, L"./imgs/����/������1.png", 161, 135, true);
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
					loadimage(&img, L"./imgs/����/������1.png", 161, 135, true);
					count3 = 2;
				}
				else if (count3 == 2)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/����/������2.png", 161, 135, true);
					count3 = 3;
				}
				else if (count3 == 3)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/����/������3.png", 161, 135, true);
					count3 = 4;
				}
				else if (count3 == 4)
				{
					role.x -= 60;
					loadimage(&img, L"./imgs/����/������4.png", 161, 135, true);
					count3 = 5;
				}
				else if (count3 == 5)
				{
					loadimage(&img, L"./imgs/����/������5.png", 161, 135, true);
					count3 = 6;
				}
				else if (count3 == 6)
				{
					loadimage(&img, L"./imgs/����/������6.png", 161, 135, true);
					count3 = 7;
				}
				else if (count3 == 7)
				{
					loadimage(&img, L"./imgs/����/������7.png", 161, 135, true);
					count3 = 8;
				}
				else if (count3 == 8)
				{
					loadimage(&img, L"./imgs/����/������8.png", 161, 135, true);
					count3 = 9;
				}
				else if (count3 == 9)
				{
					loadimage(&img, L"./imgs/����/������9.png", 161, 135, true);
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
				loadimage(&img, L"./imgs/�ƶ�/վ������3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/������Ч/1005-7.png", 350, 350, true);
				count4 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				fx = 2;
				loadimage(&img, L"./imgs/�ƶ�/վ������3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/������Ч/1005-7.png", 350, 350, true);
			}
		}
		else if (action == skill_J)
		{
			//mciSendString(L"open ��Ч/.mp3 alias bk", NULL, 0, NULL);
			//mciSendString(L"play bk repeat", NULL, 0, NULL);
			static int seriate_J = 1;
			count = 0;
			if (seriate_J == 1) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/����/������4.png", 120, 124, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/����/������4.png", 120, 124, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/����/������1.png", 120, 124, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/����/������5.png", 120, 124, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/����/������6.png", 120, 124, true);
						count5 = 5;
					}
					else if (count5 == 5)
					{
						loadimage(&img, L"./imgs/����/������1.png", 120, 124, true);
						count5 = 6;
					}
					else if (count5 == 6)
					{
						loadimage(&img, L"./imgs/����/������4.png", 120, 124, true);
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
					loadimage(&img, L"./imgs/����/��ȭ��4.png", 145, 127, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/����/��ȭ��4.png", 145, 127, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/����/��ȭ��3.png", 145, 127, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/����/��ȭ��2.png", 145, 127, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/����/��ȭ��4.png", 145, 127, true);
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
				loadimage(&img, L"./imgs/����I/Զ����2.png", 117, 163, true);
				count6 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count6 == 1)
				{
					role.MP -= 80;
					loadimage(&img, L"./imgs/����I/Զ����2.png", 117, 163, true);
					count6 = 2;
				}
				else if (count6 == 2)
				{
					loadimage(&img, L"./imgs/����I/Զ����1.png", 117, 163, true);
					count6 = 3;
				}
				else if (count6 == 3)
				{
					loadimage(&img, L"./imgs/����I/Զ����1.png", 117, 163, true);
					count6 = 4;
				}
				else if (count6 == 4)
				{
					loadimage(&img, L"./imgs/����I/Զ����5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������1.png", 22, 17, true);
					fx = 1;
					FX_I.x = role.x + 130;
					count6 = 5;
				}
				else if (count6 == 5)
				{
					loadimage(&img, L"./imgs/����I/Զ����5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������1.png", 33, 25, true);
					FX_I.x = role.x + 160;
					count6 = 6;
				}
				else if (count6 == 6)
				{
					loadimage(&img, L"./imgs/����I/Զ����5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������1.png", 44, 34, true);
					FX_I.x = role.x + 200;
					count6 = 7;
				}
				else if (count6 == 7)
				{
					loadimage(&img, L"./imgs/����I/Զ����5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������2.png", 50, 49, true);
					FX_I.x = role.x + 230;
					count6 = 8;
				}
				else if (count6 == 8)
				{
					loadimage(&img, L"./imgs/����I/Զ����5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������2.png", 60, 59, true);
					FX_I.x = role.x + 260;

					count6 = 9;
				}
				else if (count6 == 9)
				{
					loadimage(&img, L"./imgs/����I/Զ����4.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/������3.png", 73, 60, true);
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
				loadimage(&img, L"./imgs/����ȭ/����ȭ��2.png", 148, 133, true);

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
					loadimage(&img, L"./imgs/����ȭ/����ȭ��3.png", 148, 133, true);
					count7 = 2;
				}
				else if (count7 == 2)
				{
					fx = 3;
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��6.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-5.png", 250, 250, true);
					count7 = 3;
				}
				else if (count7 == 3)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��5.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-4.png", 250, 250, true);
					count7 = 4;
				}
				else if (count7 == 4)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-1.png", 250, 250, true);
					count7 = 5;
				}
				else if (count7 == 5)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-2.png", 250, 250, true);
					count7 = 6;
				}
				else if (count7 == 6)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-6.png", 250, 250, true);
					count7 = 7;
				}
				else if (count7 == 7)
				{
					FX_U.x += 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ��4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-3.png", 250, 250, true);
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
				loadimage(&img, L"./imgs/����/ͼ��5.png", 150, 200, true);
				role.MP -= 50;
				count8 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				
				if (count8 == 1)
					loadimage(&img, L"./imgs/����/ͼ��4.png", 150, 200, true);
				if (count8 == 2)
					loadimage(&img, L"./imgs/����/ͼ��3.png", 150, 200, true);
				if (count8 == 3)
					loadimage(&img, L"./imgs/����/ͼ��9.png", 150, 200, true);
				if (count8 == 4)
					loadimage(&img, L"./imgs/����/ͼ��2.png", 150, 200, true);
				if (count8 == 5) {
					loadimage(&img, L"./imgs/����/ͼ��1.png", 150, 200, true);
					role.x += 300;
					FX_L.x += 300;
				}
				if (count8 == 6)
					loadimage(&img, L"./imgs/����/ͼ��2.png", 150, 200, true);
				if (count8 == 7)
					loadimage(&img, L"./imgs/����/ͼ��9.png", 150, 200, true);
				if (count8 == 8)
					loadimage(&img, L"./imgs/����/ͼ��3.png", 150, 200, true);
				if (count8 == 9)
					loadimage(&img, L"./imgs/����/ͼ��4.png", 150, 200, true);
				if (count8 == 10) {
					loadimage(&img, L"./imgs/����/ͼ��5.png", 150, 200, true);
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
	//��ɫ����
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
				loadimage(&img, L"./imgs/����/����1.png", 161, 135, true);
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
					loadimage(&img, L"./imgs/����/����1.png", 161, 135, true);
					count3 = 2;
				}
				else if (count3 == 2)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/����/����2.png", 161, 135, true);
					count3 = 3;
				}
				else if (count3 == 3)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/����/����3.png", 161, 135, true);
					count3 = 4;
				}
				else if (count3 == 4)
				{
					role.x += 60;
					loadimage(&img, L"./imgs/����/����4.png", 161, 135, true);
					count3 = 5;
				}
				else if (count3 == 5)
				{
					loadimage(&img, L"./imgs/����/����5.png", 161, 135, true);
					count3 = 6;
				}
				else if (count3 == 6)
				{
					loadimage(&img, L"./imgs/����/����6.png", 161, 135, true);
					count3 = 7;
				}
				else if (count3 == 7)
				{
					loadimage(&img, L"./imgs/����/����7.png", 161, 135, true);
					count3 = 8;
				}
				else if (count3 == 8)
				{
					loadimage(&img, L"./imgs/����/����8.png", 161, 135, true);
					count3 = 9;
				}
				else if (count3 == 9)
				{
					loadimage(&img, L"./imgs/����/����9.png", 161, 135, true);
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
				loadimage(&img, L"./imgs/�ƶ�/վ����3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/������Ч/1005-7.png", 350, 350, true);
				count4 = 1;
			}
			if ((time - update) >= 200)
			{
				update = time;
				fx = 2;
				loadimage(&img, L"./imgs/�ƶ�/վ����3.png", 120, 124, true);
				loadimage(&img_skill, L"./imgs/������Ч/1005-7.png", 350, 350, true);
			}
		}
		else if (action == skill_J)
		{
			static int seriate_J = 1;
			count = 0;
			if (seriate_J == 1) {
				if (count5 == 0)
				{
					loadimage(&img, L"./imgs/����/����4.png", 120, 124, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/����/����4.png", 120, 124, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/����/����1.png", 120, 124, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/����/����5.png", 120, 124, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/����/����6.png", 120, 124, true);
						count5 = 5;
					}
					else if (count5 == 5)
					{
						loadimage(&img, L"./imgs/����/����1.png", 120, 124, true);
						count5 = 6;
					}
					else if (count5 == 6)
					{
						loadimage(&img, L"./imgs/����/����4.png", 120, 124, true);
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
					loadimage(&img, L"./imgs/����/��ȭ4.png", 145, 127, true);
					count5 = 1;
				}
				if ((time - update) >= 100)
				{
					update = time;
					if (count5 == 1)
					{
						loadimage(&img, L"./imgs/����/��ȭ4.png", 145, 127, true);
						count5 = 2;
					}
					else if (count5 == 2)
					{
						loadimage(&img, L"./imgs/����/��ȭ3.png", 145, 127, true);
						count5 = 3;
					}
					else if (count5 == 3)
					{
						loadimage(&img, L"./imgs/����/��ȭ2.png", 145, 127, true);
						count5 = 4;
					}
					else if (count5 == 4)
					{
						loadimage(&img, L"./imgs/����/��ȭ4.png", 145, 127, true);
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
				loadimage(&img, L"./imgs/����I/Զ��2.png", 117, 163, true);
				count6 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;
				if (count6 == 1)
				{
					role.MP -= 80;
					loadimage(&img, L"./imgs/����I/Զ��2.png", 117, 163, true);
					count6 = 2;
				}
				else if (count6 == 2)
				{
					loadimage(&img, L"./imgs/����I/Զ��1.png", 117, 163, true);
					count6 = 3;
				}
				else if (count6 == 3)
				{
					loadimage(&img, L"./imgs/����I/Զ��1.png", 117, 163, true);
					count6 = 4;
				}
				else if (count6 == 4)
				{
					loadimage(&img, L"./imgs/����I/Զ��5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����1.png", 22, 17, true);
					fx = 1;
					FX_I.x = role.x - 20;
					count6 = 5;
				}
				else if (count6 == 5)
				{
					loadimage(&img, L"./imgs/����I/Զ��5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����1.png", 33, 25, true);
					FX_I.x = role.x - 50;
					count6 = 6;
				}
				else if (count6 == 6)
				{
					loadimage(&img, L"./imgs/����I/Զ��5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����1.png", 44, 34, true);
					FX_I.x = role.x - 80;
					count6 = 7;
				}
				else if (count6 == 7)
				{
					loadimage(&img, L"./imgs/����I/Զ��5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����2.png", 50, 49, true);
					FX_I.x = role.x - 110;
					count6 = 8;
				}
				else if (count6 == 8)
				{
					loadimage(&img, L"./imgs/����I/Զ��5.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����2.png", 60, 59, true);
					FX_I.x = role.x - 150;

					count6 = 9;
				}
				else if (count6 == 9)
				{
					loadimage(&img, L"./imgs/����I/Զ��4.png", 117, 163, true);
					loadimage(&img_skill, L"./imgs/����I/����3.png", 73, 60, true);
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
				loadimage(&img, L"./imgs/����ȭ/����ȭ2.png", 148, 133, true);

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
					loadimage(&img, L"./imgs/����ȭ/����ȭ3.png", 148, 133, true);
					count7 = 2;
				}
				else if (count7 == 2)
				{
					fx = 3;
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ6.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-5.png", 250, 250, true);
					count7 = 3;
				}
				else if (count7 == 3)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ5.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-4.png", 250, 250, true);
					count7 = 4;
				}
				else if (count7 == 4)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-1.png", 250, 250, true);
					count7 = 5;
				}
				else if (count7 == 5)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-2.png", 250, 250, true);
					count7 = 6;
				}
				else if (count7 == 6)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-6.png", 250, 250, true);
					count7 = 7;
				}
				else if (count7 == 7)
				{
					FX_U.x -= 60;
					loadimage(&img, L"./imgs/����ȭ/����ȭ4.png", 148, 133, true);
					loadimage(&img_skill, L"./imgs/����ȭ/1572-3.png", 250, 250, true);
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
				loadimage(&img, L"./imgs/����/ͼ��5.png", 150, 200, true);
				count8 = 1;
			}
			if ((time - update) >= 100)
			{
				update = time;

				if (count8 == 1)
					role.MP -= 50;
					loadimage(&img, L"./imgs/����/ͼ��4.png", 150, 200, true);
				if (count8 == 2)
					loadimage(&img, L"./imgs/����/ͼ��3.png", 150, 200, true);
				if (count8 == 3)
					loadimage(&img, L"./imgs/����/ͼ��9.png", 150, 200, true);
				if (count8 == 4)
					loadimage(&img, L"./imgs/����/ͼ��2.png", 150, 200, true);
				if (count8 == 5) {
					loadimage(&img, L"./imgs/����/ͼ��1.png", 150, 200, true);
					role.x -= 300;
					FX_L.x -= 300;
				}
				if (count8 == 6)
					loadimage(&img, L"./imgs/����/ͼ��2.png", 150, 200, true);
				if (count8 == 7)
					loadimage(&img, L"./imgs/����/ͼ��9.png", 150, 200, true);
				if (count8 == 8)
					loadimage(&img, L"./imgs/����/ͼ��3.png", 150, 200, true);
				if (count8 == 9)
					loadimage(&img, L"./imgs/����/ͼ��4.png", 150, 200, true);
				if (count8 == 10) {
					loadimage(&img, L"./imgs/����/ͼ��5.png", 150, 200, true);
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
	if (role.x <= 50)role.x = 50;//1�������߽�
	if (role.x >= 1000)role.x = 1000;

	//�Ƿ�����˫
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
//����**************************************************************
//���˼���
void enemy_load()
{
	loadimage(&enemy[0], L"./imgs/Ұ��/�����ƶ���1.png", 163, 159, true);
	loadimage(&enemy[1], L"./imgs/Ұ��/�����ƶ���2.png", 163, 159, true);
	loadimage(&enemy[2], L"./imgs/Ұ��/�����ƶ���3.png", 163, 159, true);
	loadimage(&enemy[3], L"./imgs/Ұ��/�����ƶ���4.png", 163, 159, true);
	loadimage(&enemy[4], L"./imgs/Ұ��/�����ƶ���5.png", 163, 159, true);
	loadimage(&enemy[5], L"./imgs/Ұ��/�����ƶ�1.png", 163, 159, true);
	loadimage(&enemy[6], L"./imgs/Ұ��/�����ƶ�2.png", 163, 159, true);
	loadimage(&enemy[7], L"./imgs/Ұ��/�����ƶ�3.png", 163, 159, true);
	loadimage(&enemy[8], L"./imgs/Ұ��/�����ƶ�4.png", 163, 159, true);
	loadimage(&enemy[9], L"./imgs/Ұ��/�����ƶ�5.png", 163, 159, true);
	loadimage(&enemy[10], L"./imgs/��������/��������1.png", 303, 193, true);
	loadimage(&enemy[11], L"./imgs/��������/��������2.png", 303, 193, true);
	loadimage(&enemy[12], L"./imgs/��������/��������3.png", 303, 193, true);
	loadimage(&enemy[13], L"./imgs/��������/��������4.png", 303, 193, true);
	loadimage(&enemy[14], L"./imgs/��������/��������5.png", 303, 193, true);
	loadimage(&enemy[15], L"./imgs/��������/��������6.png", 303, 193, true);
	loadimage(&enemy[16], L"./imgs/��������/��������7.png", 303, 193, true);
	loadimage(&enemy[17], L"./imgs/��������/��������8.png", 303, 193, true);
	loadimage(&enemy[18], L"./imgs/��������/��������9.png", 303, 193, true);
	loadimage(&enemy[19], L"./imgs/��������/��������10.png", 303, 193, true);
	loadimage(&enemy[20], L"./imgs/��������/����������1.png", 303, 193, true);
	loadimage(&enemy[21], L"./imgs/��������/����������2.png", 303, 193, true);
	loadimage(&enemy[22], L"./imgs/��������/����������3.png", 303, 193, true);
	loadimage(&enemy[23], L"./imgs/��������/����������4.png", 303, 193, true);
	loadimage(&enemy[24], L"./imgs/��������/����������5.png", 303, 193, true);
	loadimage(&enemy[25], L"./imgs/��������/����������6.png", 303, 193, true);
	loadimage(&enemy[26], L"./imgs/��������/����������7.png", 303, 193, true);
	loadimage(&enemy[27], L"./imgs/��������/����������8.png", 303, 193, true);
	loadimage(&enemy[28], L"./imgs/��������/����������9.png", 303, 193, true);
	loadimage(&enemy[29], L"./imgs/��������/����������10.png", 303, 193, true);
	loadimage(&enemy[30], L"./imgs/������ת����/������ת1.png", 163, 159, true);
	loadimage(&enemy[31], L"./imgs/������ת����/������ת2.png", 163, 159, true);
	loadimage(&enemy[32], L"./imgs/������ת����/������ת3.png", 163, 159, true);
	loadimage(&enemy[33], L"./imgs/������ת����/������ת4.png", 163, 159, true);
	loadimage(&enemy[34], L"./imgs/������ת����/������ת5.png", 163, 159, true);
	loadimage(&enemy[35], L"./imgs/������ת����/������ת6.png", 163, 159, true);
	loadimage(&enemy[36], L"./imgs/������ת����/������ת7.png", 163, 159, true);
	loadimage(&enemy[37], L"./imgs/������ת����/������ת��1.png", 163, 159, true);
	loadimage(&enemy[38], L"./imgs/������ת����/������ת��2.png", 163, 159, true);
	loadimage(&enemy[39], L"./imgs/������ת����/������ת��3.png", 163, 159, true);
	loadimage(&enemy[40], L"./imgs/������ת����/������ת��4.png", 163, 159, true);
	loadimage(&enemy[41], L"./imgs/������ת����/������ת��5.png", 163, 159, true);
	loadimage(&enemy[42], L"./imgs/������ת����/������ת��6.png", 163, 159, true);
	loadimage(&enemy[43], L"./imgs/������ת����/������ת��7.png", 163, 159, true);
	loadimage(&enemy[44], L"./imgs/������Ч/��Ч1.png", 100, 100, true);
	loadimage(&enemy[45], L"./imgs/������Ч/��Ч2.png", 100, 100, true);
	loadimage(&enemy[46], L"./imgs/������Ч/��Ч3.png", 100, 100, true);
	loadimage(&enemy[47], L"./imgs/������Ч/��Ч4.png", 70, 70, true);
	loadimage(&enemy[48], L"./imgs/������Ч/��Ч5.png", 70, 70, true);
	loadimage(&enemy[49], L"./imgs/������Ч/��Ч6.png", 70, 70, true);
	loadimage(&enemy[50], L"./imgs/������Ч/��Ч7.png", 70, 70, true);
	loadimage(&enemy[51], L"./imgs/èè�ƶ�/èè�ƶ���1.png", 100, 100, true);
	loadimage(&enemy[52], L"./imgs/èè�ƶ�/èè�ƶ���2.png", 100, 100, true);
	loadimage(&enemy[53], L"./imgs/èè�ƶ�/èè�ƶ���3.png", 100, 100, true);
	loadimage(&enemy[54], L"./imgs/èè�ƶ�/èè�ƶ���4.png", 100, 100, true);
	loadimage(&enemy[55], L"./imgs/èè�ƶ�/èè�ƶ�1.png", 100, 100, true);
	loadimage(&enemy[56], L"./imgs/èè�ƶ�/èè�ƶ�2.png", 100, 100, true);
	loadimage(&enemy[57], L"./imgs/èè�ƶ�/èè�ƶ�3.png", 100, 100, true);
	loadimage(&enemy[58], L"./imgs/èè�ƶ�/èè�ƶ�4.png", 100, 100, true);
	loadimage(&enemy[59], L"./imgs/è����/è������1.png", 184, 150, true);
	loadimage(&enemy[60], L"./imgs/è����/è������2.png", 184, 150, true);
	loadimage(&enemy[61], L"./imgs/è����/è������3.png", 184, 150, true);
	loadimage(&enemy[62], L"./imgs/è����/è������4.png", 184, 150, true);
	loadimage(&enemy[63], L"./imgs/è����/è������5.png", 184, 150, true);
	loadimage(&enemy[64], L"./imgs/è����/è������6.png", 184, 150, true);
	loadimage(&enemy[65], L"./imgs/è����/è������7.png", 184, 150, true);
	loadimage(&enemy[66], L"./imgs/è����/è������8.png", 184, 150, true);
	loadimage(&enemy[67], L"./imgs/è����/è������9.png", 184, 150, true);
	loadimage(&enemy[68], L"./imgs/è����/è������10.png", 184, 150, true);
	loadimage(&enemy[69], L"./imgs/è����/è������11.png", 184, 150, true);
	loadimage(&enemy[70], L"./imgs/è����/è������12.png", 184, 150, true);
	loadimage(&enemy[71], L"./imgs/è����/è������13.png", 184, 150, true);
	loadimage(&enemy[72], L"./imgs/è����/è������14.png", 184, 150, true);
	loadimage(&enemy[73], L"./imgs/è����/è����1.png", 184, 150, true);
	loadimage(&enemy[74], L"./imgs/è����/è����2.png", 184, 150, true);
	loadimage(&enemy[75], L"./imgs/è����/è����3.png", 184, 150, true);
	loadimage(&enemy[76], L"./imgs/è����/è����4.png", 184, 150, true);
	loadimage(&enemy[77], L"./imgs/è����/è����5.png", 184, 150, true);
	loadimage(&enemy[78], L"./imgs/è����/è����6.png", 184, 150, true);
	loadimage(&enemy[79], L"./imgs/è����/è����7.png", 184, 150, true);
	loadimage(&enemy[80], L"./imgs/è����/è����8.png", 184, 150, true);
	loadimage(&enemy[81], L"./imgs/è����/è����9.png", 184, 150, true);
	loadimage(&enemy[82], L"./imgs/è����/è����10.png", 184, 150, true);
	loadimage(&enemy[83], L"./imgs/è����/è����11.png", 184, 150, true);
	loadimage(&enemy[84], L"./imgs/è����/è����12.png", 184, 150, true);
	loadimage(&enemy[85], L"./imgs/è����/è����13.png", 184, 150, true);
	loadimage(&enemy[86], L"./imgs/è����/è����14.png", 184, 150, true);
	loadimage(&enemy[87], L"./imgs/è����/è��Ч.png", 50, 50, true);
	loadimage(&enemy[88], L"./imgs/è����/è��Ч.png", 60, 60, true);
	loadimage(&enemy[89], L"./imgs/è����/è��Ч.png", 70, 70, true);
	loadimage(&enemy[90], L"./imgs/boss/boss����1.png", 200, 200, true);
	loadimage(&enemy[91], L"./imgs/boss/boss����2.png", 200, 200, true);
	loadimage(&enemy[92], L"./imgs/boss/boss����3.png", 200, 200, true);
	loadimage(&enemy[93], L"./imgs/boss/boss����4.png", 200, 200, true);
	loadimage(&enemy[94], L"./imgs/boss/boss����5.png", 200, 200, true);
	loadimage(&enemy[95], L"./imgs/boss/boss������1.png", 200, 200, true);
	loadimage(&enemy[96], L"./imgs/boss/boss������2.png", 200, 200, true);
	loadimage(&enemy[97], L"./imgs/boss/boss������3.png", 200, 200, true);
	loadimage(&enemy[98], L"./imgs/boss/boss������4.png", 200, 200, true);
	loadimage(&enemy[99], L"./imgs/boss/boss������5.png", 200, 200, true);
	loadimage(&enemy[100], L"./imgs/boss/boss�����1.png", 600, 300, true);
	loadimage(&enemy[101], L"./imgs/boss/boss�����2.png", 600, 300, true);
	loadimage(&enemy[102], L"./imgs/boss/boss�����3.png", 600, 300, true);
	loadimage(&enemy[103], L"./imgs/boss/boss�����4.png", 600, 300, true);
	loadimage(&enemy[104], L"./imgs/boss/boss�����5.png", 600, 300, true);
	loadimage(&enemy[105], L"./imgs/boss/boss�����6.png", 600, 300, true);
	loadimage(&enemy[106], L"./imgs/boss/boss�����7.png", 600, 300, true);
	loadimage(&enemy[107], L"./imgs/boss/boss�����8.png", 600, 300, true);
	loadimage(&enemy[108], L"./imgs/boss/boss�����9.png", 600, 300, true);
	loadimage(&enemy[109], L"./imgs/boss/boss�����10.png", 600, 300, true);
	loadimage(&enemy[110], L"./imgs/boss/boss�������1.png", 600, 300, true);
	loadimage(&enemy[111], L"./imgs/boss/boss�������2.png", 600, 300, true);
	loadimage(&enemy[112], L"./imgs/boss/boss�������3.png", 600, 300, true);
	loadimage(&enemy[113], L"./imgs/boss/boss�������4.png", 600, 300, true);
	loadimage(&enemy[114], L"./imgs/boss/boss�������5.png", 600, 300, true);
	loadimage(&enemy[115], L"./imgs/boss/boss�������6.png", 600, 300, true);
	loadimage(&enemy[116], L"./imgs/boss/boss�������7.png", 600, 300, true);
	loadimage(&enemy[117], L"./imgs/boss/boss�������8.png", 600, 300, true);
	loadimage(&enemy[118], L"./imgs/boss/boss�������9.png", 600, 300, true);
	loadimage(&enemy[119], L"./imgs/boss/boss�������10.png", 600, 300, true);
	loadimage(&enemy[120], L"./imgs/boss/boss����1.png", 450, 500, true);
	loadimage(&enemy[121], L"./imgs/boss/boss����2.png", 450, 500, true);
	loadimage(&enemy[122], L"./imgs/boss/boss����3.png", 450, 500, true);
	loadimage(&enemy[123], L"./imgs/boss/boss����4.png", 450, 500, true);
	loadimage(&enemy[124], L"./imgs/boss/boss����5.png", 450, 500, true);
	loadimage(&enemy[125], L"./imgs/boss/boss����6.png", 450, 500, true);
	loadimage(&enemy[126], L"./imgs/boss/boss����7.png", 450, 500, true);
	loadimage(&enemy[127], L"./imgs/boss/boss����8.png", 450, 500, true);
	loadimage(&enemy[128], L"./imgs/boss/boss����9.png", 450, 500, true);
	loadimage(&enemy[129], L"./imgs/boss/boss����10.png", 450, 500, true);
	loadimage(&enemy[130], L"./imgs/boss/boss����11.png", 450, 500, true);
	loadimage(&enemy[131], L"./imgs/boss/boss����12.png", 450, 500, true);
	loadimage(&enemy[132], L"./imgs/boss/boss������1.png", 450, 500, true);
	loadimage(&enemy[133], L"./imgs/boss/boss������2.png", 450, 500, true);
	loadimage(&enemy[134], L"./imgs/boss/boss������3.png", 450, 500, true);
	loadimage(&enemy[135], L"./imgs/boss/boss������4.png", 450, 500, true);
	loadimage(&enemy[136], L"./imgs/boss/boss������5.png", 450, 500, true);
	loadimage(&enemy[137], L"./imgs/boss/boss������6.png", 450, 500, true);
	loadimage(&enemy[138], L"./imgs/boss/boss������7.png", 450, 500, true);
	loadimage(&enemy[139], L"./imgs/boss/boss������8.png", 450, 500, true);
	loadimage(&enemy[140], L"./imgs/boss/boss������9.png", 450, 500, true);
	loadimage(&enemy[141], L"./imgs/boss/boss������10.png", 450, 500, true);
	loadimage(&enemy[142], L"./imgs/boss/boss������11.png", 450, 500, true);
	loadimage(&enemy[143], L"./imgs/boss/boss������12.png", 450, 500, true);
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
//�����ƶ�
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
//��������
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
//��������1  ����
void enemy_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_1.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//���ܻ�����
	int distance1 = role_center3 - enemy_center1;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center1;//�����ܻ�����
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
	int distance = role_center1 - enemy_center1;//�ֹ�������
	int distance0 = role_center2 - enemy_center1;//���ܻ�����
	int distance1 = role_center3 - enemy_center1;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center1;//�����ܻ�����
	int distance3 = thunder_center - enemy_center1;//�׵��ܻ�����
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
//����**************************************************************
//è****************************************************************
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
//èè�ƶ�
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
					enemy_cat.x += 7;//����
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
//èè����
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
//èè����1  ����
void cat_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_cat.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//���ܻ�����
	int distance1 = role_center3 - enemy_center1;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center1;//�����ܻ�����
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
//èè״̬�ж�
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
	int distance = role_center1 - enemy_center2;//�ֹ�������
	int distance0 = role_center2 - enemy_center2;//���ܻ�����
	int distance1 = role_center3 - enemy_center2;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center2;//�����ܻ�����
	int distance3 = thunder_center - enemy_center2;//�׵��ܻ�����
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
//è****************************************************************
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
//boss�ƶ�
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
//boss���� 1
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
//boss����1  ����
void boss_beaten()
{
	static int update0 = clock();
	int time = clock();
	int enemy_center1 = enemy_boss.x + 81;
	int role_center2 = role.x + 60;
	int role_center3 = role.x + 72;
	int fire_center = FX_I.x + 22;
	int distance0 = role_center2 - enemy_center1;//���ܻ�����
	int distance1 = role_center3 - enemy_center1;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center1;//�����ܻ�����
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
//boos ���ܻ�Ѫ
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
//boss״̬�ж�
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
	int distance = role_center1 - enemy_center3;//�ֹ�������
	int distance0 = role_center2 - enemy_center3;//���ܻ�����
	int distance1 = role_center3 - enemy_center3;//ȭ�ܻ�����
	int distance2 = fire_center - enemy_center3;//�����ܻ�����
	int distance3 = thunder_center - enemy_center3;//�׵��ܻ�����
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

void over_cartoon()//�ɹ�
{
	IMAGE img_princess, img_boss, img_boss2, img_renwu2, img_renwu3, img_background, img_speak, img_bigboss,img_renwu1, img_begin, img_introduce, img_choose, img_back, img_pointer, img_finish, img_round1, img_round2, img_round3;
	int x = 0, y = 0;
	
	loadimage(&img_background, L"./imgs/����/����.jpg", window_wide, window_height, true);
	loadimage(&img_renwu1, L"./imgs/����/����5.png", 210, 140, true);
	loadimage(&img_boss2, L"./imgs/����/boss2.png", 202, 240, true);
	loadimage(&img_princess, L"./imgs/����/����.png", 395, 260, true);
	loadimage(&img_renwu2, L"./imgs/����/����4.png", 167, 260, true);
	loadimage(&img_bigboss, L"./imgs/����/bigboss.png", 167, 260, true);
	loadimage(&img_speak, L"./imgs/����/�Ի���.png", 600, 250, true);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(255, 255, 255));
	settextstyle(23, 0, _T("����"));
	transparentimage(NULL, 0, 0, &img_background); //��ʼ����
	transparentimage(NULL, 100, 300, &img_renwu2);
	transparentimage(NULL, 900, 310, &img_boss2);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("��գ��������׹Ǿ���Ҳ������������ҵĹ�������")); Sleep(1500);
	transparentimage(NULL, 650, 100, &img_bigboss);
	outtextxy(300, 520, _T("а���������ٺ٣�����Ϊ��Ӯ�ˣ������飩")); Sleep(1500);
	outtextxy(300, 550, _T("�׹Ǿ������ˣ������ˣ�")); Sleep(1500);
	outtextxy(300, 580, _T("а��������û�õ�fw�������ˮƽ��")); Sleep(1500);
	outtextxy(300, 610, _T("��գ��ɶ񣬿ɶ�Ϊʲô�㡣��Ϊʲô����")); Sleep(1500);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("а������������������������ͷ¶���")); Sleep(1500);
	outtextxy(300, 520, _T("а����������Ȼ��ˣ�Ҫ������С����������ͥ���Ұ�")); Sleep(1500);
	transparentimage(NULL, 800, 100, &img_princess);
	outtextxy(300, 550, _T("��������գ����������ߣ�������")); Sleep(1500);
	outtextxy(300, 580, _T("��գ��ҵı������£����������")); Sleep(1500);
	transparentimage(NULL, 300, 480, &img_speak);
	outtextxy(300, 490, _T("δ���������enter��������"));
	getchar();
	for (x = 0; x > -700; x -= 20)
	{
		BeginBatchDraw();
		transparentimage(NULL, 0, 0, &img_background); //��ʼ����
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
		transparentimage(NULL, 0, 0, &img_background); //��ʼ����
		transparentimage(NULL, 100, 300 + x, &img_renwu1);
		EndBatchDraw();
		Sleep(10);
	}

}