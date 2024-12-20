#pragma once
#include<graphics.h>
bool gameend = false, gamestart = false, rank = false, rule = false, Exit = false,
			INIT_MENU_RUNNING = true, CLEAR_MENU_RUNNING = false, PROGRAM_RUNNING = true, this_game = false;
bool CHOOSE_GAMEMODE = false;

int DIFFICULTY_TIME, DFFICULTY_HP;

//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
enum GameMode {
	race,survival,limit,hell,nullmode
};

GameMode GAMEMODE=nullmode;

//���ư���͸������Ϣ��ͼƬ
#pragma comment(lib, "MSIMG32.LIB")
inline void Putimage(int x,int y,IMAGE* img) {
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}


//�˵���ť����
class MBUTTON {
private:

	enum Status {
		Hold, Pushed, Wait
	};
	IMAGE bk_hold;
	IMAGE bk_pushed;
	IMAGE bk_wait;
	Status status = Wait;
	int x, y;	//���Ͻ�����
	RECT rect;

protected:
	virtual void onclick() = 0;

public:
	//���캯��
	MBUTTON(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) {
		x = x_;
		y = y_;
		rect = re;
		loadimage(&bk_wait, bkwait);
		loadimage(&bk_hold, bkhold);
		loadimage(&bk_pushed, bkpushed);
	}

	//���ò˵���ť
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

	//�ı䰴ť״̬
	void checkstatus(const ExMessage& msg) {

		switch (msg.message) {
		case WM_MOUSEMOVE:	//��������ƶ�
			if (status == Wait && inbutton(msg.x, msg.y))status = Hold;			//�Ƶ���ť�ڲ�
			else if (status == Hold && !inbutton(msg.x, msg.y))status = Wait;	//�Ƶ���ť�ⲿ
			break;
		case WM_LBUTTONDOWN:	//�������
			if (inbutton(msg.x, msg.y))		//�ڰ�ť�ڲ�
				status = Pushed;
			break;
		case WM_LBUTTONUP:		//���̧��
			if (status == Pushed && inbutton(msg.x, msg.y)) {
				status = Hold;
				onclick();		//�����ڲ���������
			}
			else if (status == Pushed)status = Wait;
			break;
		defalut:
			break;
		}
	}

	//����Ƿ��ڰ�ť��Χ��
	bool inbutton(int cx, int cy) {
		if (cx >= x && cx <= rect.right && cy >= y && cy <= rect.bottom)return true;
		return false;
	}

};

//����������Ϸ��ť
class EndButton :public MBUTTON {
public:
	EndButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//��Ϸ����
	void onclick() {
		gameend = true;
	}
};

//��ʼһ����Ϸ��ť
class StartButton :public MBUTTON {
public:
	StartButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//��Ϸ��ʼ
	void onclick() {
		gamestart = true;
		this_game = true;
		INIT_MENU_RUNNING = false;
		CLEAR_MENU_RUNNING = false;
	}
};

//�����а�ť
class RankButton :public MBUTTON {
public:
	RankButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//�򿪻�ر����а�
	void onclick() {
		rank = true;
		INIT_MENU_RUNNING = false;
	}
};

//��Ϸ������ܰ�ť
class RuleButton :public MBUTTON {
public:
	RuleButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//����Ϸ����
	void onclick() {
		rule = true;
		INIT_MENU_RUNNING = false;
	}
};

//�˳�����ť
class ExitButton :public MBUTTON {
public:
	ExitButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//�رճ���
	void onclick() {
		PROGRAM_RUNNING = false;
		INIT_MENU_RUNNING = false;
	}
};

//ѡ����Ϸģʽ��ť�������˵�����
class ChooseModeButton :public MBUTTON {
public:
	ChooseModeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//���س�ʼ�˵�
	void onclick() {
		CHOOSE_GAMEMODE = true;
		INIT_MENU_RUNNING = false;
	}
};

//���س�ʼ�˵���ť
class ReturnMenuButton :public MBUTTON {
public:
	ReturnMenuButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//���س�ʼ�˵�
	void onclick() {
		INIT_MENU_RUNNING = true;
		rank = false, rule = false, CLEAR_MENU_RUNNING = false, this_game = false, gamestart = false;
		CHOOSE_GAMEMODE = false;
	}
};

//ѡ��ʱ���ѶȰ�ť����Ҫ����race��hell��survivalģʽ�е��Ѷ���ֵ����
class DifficultyTimeButton :public MBUTTON {
private:
	int the_difficulty_time;
public:
	DifficultyTimeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//����difficultyֵ
	void setdifficulty(int dif){
		the_difficulty_time = dif;
	}

protected:
	//�ı���Ϸʱ���Ѷ��Ѷ�
	void onclick() {
		DIFFICULTY_TIME = the_difficulty_time;
	}
};

//ѡ�������ѶȰ�ť����Ҫ����race��hell��survivalģʽ�е��Ѷ���ֵ����
class DifficultyHpButton :public MBUTTON {
private:
	int the_difficulty_hp;
public:
	DifficultyHpButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//����difficultyֵ
	void setdifficulty(int dif) {
		the_difficulty_hp = dif;
	}

protected:
	//�ı���Ϸ�����Ѷ��Ѷ�
	void onclick() {
		DIFFICULTY_TIME = the_difficulty_hp;
	}
};


//������Ϸģʽ��ť
//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
class GameModeButton :public MBUTTON {
private:
	GameMode the_gamemode;
	IMAGE successset;
	int suc_x, suc_y;
public:
	GameModeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//������Ϸģʽ�ͳɹ����ú����Ϣͼ�������Ͻ�����
	void setGamemode(GameMode gmode, IMAGE suc, int sx, int sy) {
		successset = suc;
		the_gamemode = gmode;
		suc_x = sx;
		suc_y = sy;
	}
protected:
	//�ı���Ϸģʽ
	void onclick() {
		putimage(suc_x, suc_y, &successset);
		GAMEMODE = the_gamemode;
	}
};

//������һ����ť
class ReturnButton :public MBUTTON {
private:
	bool* upperlevel;	//��һ��
	bool* thislevel;	//��һ��
public:
	ReturnButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//������һ������һ��
	void setlevel(bool* up, bool* this_) {
		upperlevel = up;
		thislevel = this_;
	}
protected:
	//�򿪻�ر����а�
	void onclick() {
		*upperlevel = true;
		*thislevel = false;
	}
};
