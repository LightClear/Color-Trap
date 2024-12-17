#pragma once
#include<graphics.h>
#include<cstdio>
#include<string>
using std::wstring;

enum COLOR {
	black, green, yellow, red, brown, blue, purple, cyan, null
};

class GameButton {
private:
	RECT rect;
	COLOR color;
	wstring text;
	IMAGE bk;
	int textsize;

public:
	//��ʼ���캯��
	GameButton(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size) {
		rect = rec;
		color = col;
		text = tex;
		loadimage(&bk, bkname);
		textsize = size;
	}

	//���������������ݵĹ��캯��
	void reset(COLOR col, wstring tex) {
		color = col;
		text = tex;
	}

	//���ñ������ı�
	//black,green,yellow,red,brown,blue,purple,cyan
	void putthings() {
		putimage(rect.left, rect.top, &bk);
		int wd = 0, he = 0;
		switch (color) {
		case black: {
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case green: {
			settextcolor(GREEN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case yellow: {
			settextcolor(YELLOW);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case red: {
			settextcolor(RED);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case brown: {
			settextcolor(BROWN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case blue: {
			settextcolor(BLUE);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case purple: {
			settextcolor(MAGENTA);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		case cyan: {
			settextcolor(CYAN);
			setbkmode(TRANSPARENT);
			settextstyle(textsize, 0, _T("΢���ź�"));
			drawtext(text.c_str(), &rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			break;
		}
		}
	}

	//����������Χ
	bool checkclick(const ExMessage& msg) {
		if (msg.message==WM_LBUTTONDOWN && msg.x >= rect.left && msg.x <= rect.right && msg.y >= rect.top && msg.y <= rect.bottom)return true;
		return false;
	}

	//���ƶ�����ı�
	void gettext(wstring& s) {
		s = text;
	}

	//���colorֵ
	COLOR getcolor() {
		return color;
	}

};


//��Ұ��İ�ť
class Ken :public GameButton {		//ΪʲôҪ��Ken������֣���Ϊ�Ҹ�����ġ����۶�������ȡ��
public:
	Ken(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size) :GameButton(rec, col, tex, bkname, size) {}
	

};


//��Ŀ�İ�ť
class Title :public GameButton {
public:
	Title(RECT rec, COLOR col, wstring tex, LPCTSTR bkname, int size):GameButton(rec, col, tex, bkname, size){}

	//����Ƿ�÷�
	//black,green,yellow,red,brown,blue,purple,cyan
	bool checkscore(Ken& but) {
		wstring s;
		but.gettext(s);
		COLOR check = null;
		int i = 0;
		wstring sc1 = { _T("��ɫ") };
		wstring sc2 = { _T("��ɫ") };
		wstring sc3 = { _T("��ɫ") };
		wstring sc4 = { _T("��ɫ") };
		wstring sc5 = { _T("��ɫ") };
		wstring sc6 = { _T("��ɫ") };
		wstring sc7 = { _T("��ɫ") };
		wstring sc8 = { _T("��ɫ") };
		COLOR assign[8] = { black,green,yellow,red,brown,blue,purple,cyan };
		if (s == sc1) { check = assign[0]; }
		if (s == sc2) { check = assign[1]; }
		if (s == sc3) { check = assign[2]; }
		if (s == sc4) { check = assign[3]; }
		if (s == sc5) { check = assign[4]; }
		if (s == sc6) { check = assign[5]; }
		if (s == sc7) { check = assign[6]; }
		if (s == sc8) { check = assign[7]; }
		return check == getcolor();
	}
};