#pragma once

#define window_wide  1200
#define window_height  700


#define stand       0
#define run         1
#define jump        2 
#define hurt        3
#define skill_J     4
#define skill_U     5
#define skill_I     6
#define skill_O     7
#define skill_S     8
#define skill_L     9
#define skill_wu    10


extern IMAGE enemy[200];
extern IMAGE Role[200];

//����״̬
extern int action;
extern int map_move;
//���ﳯ���ж�
extern bool right;
extern bool enemy_right;//��������
extern bool cat_right;//èè����
//��ͼ�����ٶ�
extern int map_move;
extern int map_stop;
//����������Ӧ��ͼ�����ٶ�
extern int update;
//��ɫ�Ƿ��ڷż���
extern int skilling;
extern int big_skill;
//��Ծ��ͼ�����ٶ�
extern int jumping;

extern int fx;
extern int enemy_die;
extern int enemy_1_die;
extern int enemy_cat_die;
extern int enemy_boss_die;

extern int one_over;


struct
{
	int x=0;
	int y=400;
	int HP = 1000;
	int MP = 1000;
}role;
struct
{
	int x=0;
	int y=400;
}FX_I,FX_S,FX_U,FX_O,FX_L,Door;
//***************************************************

//����
extern int enemy_center1;//��������
extern int enemy_center2;//èè����
extern int enemy_center3;//boss����


//����״̬
extern int enemy_state;//����״̬
extern int cat_state;//èè״̬
extern int boos_state;//èè״̬
//��������
struct
{
	int  x = 100;
	int  y = 370;
	int HP = 600;
}enemy_1;
//èè����
struct
{
	int  x = 400;
	int y = 420;
	int HP = 500;
}enemy_cat;
//boos����
struct
{
	double x = 900;
	double y = 330;
	int HP = 900;
}enemy_boss;
//�ܻ�λ��
extern int judge_benten_boos;
extern int judge_benten_cat;
extern int judge_benten;
extern int boss_judge_benten ;

//�ܻ���Ч
extern int cat_effect;//èè
extern int effect;//����
extern int boos_effect;//����
//�ܻ�����
extern int enemy_float;
//extern int judge_1;


//��������
//*************************************************************************
//����޺ڿ�͸����ͼƬ
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//ʵ�ָ�͸����
void transparentimage_t(IMAGE* dstimg, int x, int y, IMAGE* srcimg, int i);
//������ͼ
void transparentimage_BK(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//��ͼ��ʼ��
void origin();
//��ʼ����
void backmusic();
//��������
void over_cartoon();
void loading_music();
void initializtion();
//��������
void role_arise();
////�ڶ���
//void next_level();
//����չʾ
void role_show();
//�����ƶ�
void role_move();
//����
void trump_card();
//��ɫ����
void role_load();
//�ؿ��л�
void  change();


//�����ƶ�
void enemy_moving();
//����չʾ
void enemy_move();
//ͼƬ����
void enemy_load();
//��������
void enemy_attack();
//����״̬�ж�
void enemy_judge();
//��������
void enemy_beaten();
//��������2
//void enemy_btfloat();
//èè�ƶ�
void cat_moving();
void cat_move();
//èè����
void cat_attack();
//èè����1  ����
void cat_beaten();
//èè״̬�ж�
void cat_judge();
//boos�ƶ�
void boss_move();
void boss_moving();
//boos����
void boss_attack1();
//boos����1  ����
void boss_beaten();
//boos״̬�ж�
void boss_judge();
//boos���ܻ�Ѫ
void boss_skill();
//***********************************************************************
