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

//人物状态
extern int action;
extern int map_move;
//人物朝向判断
extern bool right;
extern bool enemy_right;//蓝龙朝向
extern bool cat_right;//猫猫朝向
//地图更新速度
extern int map_move;
extern int map_stop;
//人物坐标相应贴图更新速度
extern int update;
//角色是否在放技能
extern int skilling;
extern int big_skill;
//跳跃贴图更新速度
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

//中心
extern int enemy_center1;//蓝龙中心
extern int enemy_center2;//猫猫中心
extern int enemy_center3;//boss中心


//敌人状态
extern int enemy_state;//蓝龙状态
extern int cat_state;//猫猫状态
extern int boos_state;//猫猫状态
//蓝龙属性
struct
{
	int  x = 100;
	int  y = 370;
	int HP = 600;
}enemy_1;
//猫猫属性
struct
{
	int  x = 400;
	int y = 420;
	int HP = 500;
}enemy_cat;
//boos属性
struct
{
	double x = 900;
	double y = 330;
	int HP = 900;
}enemy_boss;
//受击位移
extern int judge_benten_boos;
extern int judge_benten_cat;
extern int judge_benten;
extern int boss_judge_benten ;

//受击特效
extern int cat_effect;//猫猫
extern int effect;//蓝龙
extern int boos_effect;//蓝龙
//受击升天
extern int enemy_float;
//extern int judge_1;


//函数声明
//*************************************************************************
//输出无黑框透明的图片
void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//实现改透明度
void transparentimage_t(IMAGE* dstimg, int x, int y, IMAGE* srcimg, int i);
//贴背景图
void transparentimage_BK(IMAGE* dstimg, int x, int y, IMAGE* srcimg);
//地图初始化
void origin();
//初始界面
void backmusic();
//背景音乐
void over_cartoon();
void loading_music();
void initializtion();
//出厂动画
void role_arise();
////第二关
//void next_level();
//人物展示
void role_show();
//人物移动
void role_move();
//大招
void trump_card();
//角色加载
void role_load();
//关卡切换
void  change();


//蓝龙移动
void enemy_moving();
//蓝龙展示
void enemy_move();
//图片加载
void enemy_load();
//蓝龙攻击
void enemy_attack();
//蓝龙状态判断
void enemy_judge();
//蓝龙挨打
void enemy_beaten();
//蓝龙挨打2
//void enemy_btfloat();
//猫猫移动
void cat_moving();
void cat_move();
//猫猫攻击
void cat_attack();
//猫猫挨打1  击退
void cat_beaten();
//猫猫状态判断
void cat_judge();
//boos移动
void boss_move();
void boss_moving();
//boos攻击
void boss_attack1();
//boos挨打1  击退
void boss_beaten();
//boos状态判断
void boss_judge();
//boos技能回血
void boss_skill();
//***********************************************************************
