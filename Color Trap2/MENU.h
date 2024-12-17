#pragma once
#include<graphics.h>
#include<string>
using std::wstring;

class MENU {
private:
	enum Status {
		Hold,Pushed,Wait
	};
	wstring text;
	IMAGE bk_hold;
	IMAGE bk_pushed;
	IMAGE bk_wait;
	Status status;
	int x, y;
	int length, height;
	int order;		//指令，开始游戏为1，排行榜为2，退出游戏为3
	void setbk() {
		loadimage(&bk_hold, _T("images/bk_hold.png"));
		loadimage(&bk_pushed, _T("images/bk_pushed.png"));
		loadimage(&bk_wait, _T("images/bk_wait.png"));
		status = Wait;
	}
public:
	

	//放置菜单按钮
	void putmenu() {
		switch (status) {
		case Status::Wait:
			putimage(x, y, &bk_wait);
			break;
		case Status::Hold:
			putimage(x, y, &bk_hold);
			break;
		case Status::Pushed:
			putimage(x, y, &bk_pushed);
			break;
		defalut:
			break;
		}
		//if (cx >= x && cx <= x + length && cy >= y && cy <= y + height)putimage(x, y, &graybk);	//鼠标放在按钮内就显示灰色背景
		//else putimage(x, y, &lightbk);
		//RECT rect = { x,y,x + length,y + length };
		//settextcolor(BLACK);
		//setbkmode(TRANSPARENT);
		//settextstyle(50, 0, _T("微软雅黑"));
		//drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
	}

	//检测是否在按钮范围内,并返回其指令
	bool checkclick(int& cx, int& cy) {
		if (cx >= x && cx <= cx + length && cy >= y && cy <= cy + height)return order;
		return 0;
	}

	//初始化指令、文本内容、坐标、长高
	void initmembers(int& iorder, wstring& itext, int& ix, int& iy, int& ilength, int& iheight) {
		order = iorder;
		text = itext;
		x = ix;
		y = iy;
		length = ilength;
		height = iheight;
	}

};

class StartMenu :public MENU {

};