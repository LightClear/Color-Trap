#pragma once
#include<graphics.h>
bool gameend = false, gamestart = false, rank = false, rule = false, Exit = false,
			INIT_MENU_RUNNING = true, CLEAR_MENU_RUNNING = false, PROGRAM_RUNNING = true, this_game = false;
bool CHOOSE_GAMEMODE = false;

int DIFFICULTY_TIME, DFFICULTY_HP;

//游戏模式，race：规定时间内比拼正确数； survival：有生命数，错一个扣生命； limit：限制单次题目的时间； hell：有生命数，限制单次题目时间
enum GameMode {
	race,survival,limit,hell,nullmode
};

GameMode GAMEMODE=nullmode;

//绘制包含透明度信息的图片
#pragma comment(lib, "MSIMG32.LIB")
inline void Putimage(int x,int y,IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


//菜单按钮父类
class MBUTTON {
private:

	enum Status {
		Hold, Pushed, Wait
	};
	IMAGE bk_hold;
	IMAGE bk_pushed;
	IMAGE bk_wait;
	Status status = Wait;
	int x, y;	//左上角坐标
	RECT rect;

protected:
	virtual void onclick() = 0;

public:
	//构造函数
	MBUTTON(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) {
		x = x_;
		y = y_;
		rect = re;
		loadimage(&bk_wait, bkwait);
		loadimage(&bk_hold, bkhold);
		loadimage(&bk_pushed, bkpushed);
	}

	//放置菜单按钮
	void putmenu() {
		switch (status) {
		case Status::Wait:
			Putimage(x, y, &bk_wait);
			break;
		case Status::Hold:
			Putimage(x, y, &bk_hold);
			break;
		case Status::Pushed:
			Putimage(x, y, &bk_pushed);
			break;
		defalut:
			break;
		}
	}

	//改变按钮状态
	void checkstatus(const ExMessage& msg) {

		switch (msg.message) {
		case WM_MOUSEMOVE:	//若鼠标在移动
			if (status == Wait && inbutton(msg.x, msg.y))status = Hold;			//移到按钮内部
			else if (status == Hold && !inbutton(msg.x, msg.y))status = Wait;	//移到按钮外部
			break;
		case WM_LBUTTONDOWN:	//按下左键
			if (inbutton(msg.x, msg.y))		//在按钮内部
				status = Pushed;
			break;
		case WM_LBUTTONUP:		//左键抬起
			if (status == Pushed && inbutton(msg.x, msg.y)) {
				status = Hold;
				onclick();		//进行内部函数处理
			}
			else if (status == Pushed)status = Wait;
			break;
		defalut:
			break;
		}
	}

	//检测是否在按钮范围内
	bool inbutton(int cx, int cy) {
		if (cx >= x && cx <= rect.right && cy >= y && cy <= rect.bottom)return true;
		return false;
	}

};

//结束本局游戏按钮
class EndButton :public MBUTTON {
public:
	EndButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//游戏结束
	void onclick() {
		gameend = true;
	}
};

//开始一局游戏按钮
class StartButton :public MBUTTON {
public:
	StartButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//游戏开始
	void onclick() {
		gamestart = true;
		this_game = true;
		INIT_MENU_RUNNING = false;
		CLEAR_MENU_RUNNING = false;
	}
};

//打开排行榜按钮
class RankButton :public MBUTTON {
public:
	RankButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//打开或关闭排行榜
	void onclick() {
		rank = true;
		INIT_MENU_RUNNING = false;
	}
};

//游戏规则介绍按钮
class RuleButton :public MBUTTON {
public:
	RuleButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//打开游戏介绍
	void onclick() {
		rule = true;
		INIT_MENU_RUNNING = false;
	}
};

//退出程序按钮
class ExitButton :public MBUTTON {
public:
	ExitButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//关闭程序
	void onclick() {
		PROGRAM_RUNNING = false;
		INIT_MENU_RUNNING = false;
	}
};

//选择游戏模式按钮——主菜单界面
class ChooseModeButton :public MBUTTON {
public:
	ChooseModeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//返回初始菜单
	void onclick() {
		CHOOSE_GAMEMODE = true;
		INIT_MENU_RUNNING = false;
	}
};

//返回初始菜单按钮
class ReturnMenuButton :public MBUTTON {
public:
	ReturnMenuButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//返回初始菜单
	void onclick() {
		INIT_MENU_RUNNING = true;
		rank = false, rule = false, CLEAR_MENU_RUNNING = false, this_game = false, gamestart = false;
		CHOOSE_GAMEMODE = false;
	}
};

//选择时间难度按钮，主要用于race与hell和survival模式中的难度数值设置
class DifficultyTimeButton :public MBUTTON {
private:
	int the_difficulty_time;
public:
	DifficultyTimeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//设置difficulty值
	void setdifficulty(int dif){
		the_difficulty_time = dif;
	}

protected:
	//改变游戏时间难度难度
	void onclick() {
		DIFFICULTY_TIME = the_difficulty_time;
	}
};

//选择生命难度按钮，主要用于race与hell和survival模式中的难度数值设置
class DifficultyHpButton :public MBUTTON {
private:
	int the_difficulty_hp;
public:
	DifficultyHpButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//设置difficulty值
	void setdifficulty(int dif) {
		the_difficulty_hp = dif;
	}

protected:
	//改变游戏生命难度难度
	void onclick() {
		DIFFICULTY_TIME = the_difficulty_hp;
	}
};


//更改游戏模式按钮
//游戏模式，race：规定时间内比拼正确数； survival：有生命数，错一个扣生命； limit：限制单次题目的时间； hell：有生命数，限制单次题目时间
class GameModeButton :public MBUTTON {
private:
	GameMode the_gamemode;
	IMAGE successset;
	int suc_x, suc_y;
public:
	GameModeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//设置游戏模式和成功设置后的消息图及其左上角坐标
	void setGamemode(GameMode gmode, IMAGE suc, int sx, int sy) {
		successset = suc;
		the_gamemode = gmode;
		suc_x = sx;
		suc_y = sy;
	}
protected:
	//改变游戏模式
	void onclick() {
		putimage(suc_x, suc_y, &successset);
		GAMEMODE = the_gamemode;
	}
};

//返回上一级按钮
class ReturnButton :public MBUTTON {
private:
	bool* upperlevel;	//上一级
	bool* thislevel;	//这一级
public:
	ReturnButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//设置这一级，上一级
	void setlevel(bool* up, bool* this_) {
		upperlevel = up;
		thislevel = this_;
	}
protected:
	//打开或关闭排行榜
	void onclick() {
		*upperlevel = true;
		*thislevel = false;
	}
};
