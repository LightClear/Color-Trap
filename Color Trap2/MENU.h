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
	int order;		//ָ���ʼ��ϷΪ1�����а�Ϊ2���˳���ϷΪ3
	void setbk() {
		loadimage(&bk_hold, _T("images/bk_hold.png"));
		loadimage(&bk_pushed, _T("images/bk_pushed.png"));
		loadimage(&bk_wait, _T("images/bk_wait.png"));
		status = Wait;
	}
public:
	

	//���ò˵���ť
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
		//if (cx >= x && cx <= x + length && cy >= y && cy <= y + height)putimage(x, y, &graybk);	//�����ڰ�ť�ھ���ʾ��ɫ����
		//else putimage(x, y, &lightbk);
		//RECT rect = { x,y,x + length,y + length };
		//settextcolor(BLACK);
		//setbkmode(TRANSPARENT);
		//settextstyle(50, 0, _T("΢���ź�"));
		//drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
	}

	//����Ƿ��ڰ�ť��Χ��,��������ָ��
	bool checkclick(int& cx, int& cy) {
		if (cx >= x && cx <= cx + length && cy >= y && cy <= cy + height)return order;
		return 0;
	}

	//��ʼ��ָ��ı����ݡ����ꡢ����
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