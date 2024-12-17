#pragma once
#include<graphics.h>
bool gameend = false, gamestart = false, rank = false, rule = false, Exit = false,
			INIT_MENU_RUNNING = true, CLEAR_MENU_RUNNING = false, PROGRAM_RUNNING = true, this_game = false;

int DIFFICULTY_TIME, DFFICULTY_HP, GAMEMODE;

//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
enum GameMode {
	race,survival,limit,hell
};

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

//���س�ʼ�˵���ť
class ReturnMenuButton :public MBUTTON {
public:
	ReturnMenuButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}
protected:
	//���س�ʼ�˵�
	void onclick() {
		INIT_MENU_RUNNING = true;
		rank = false, rule = false, CLEAR_MENU_RUNNING = false, this_game = false, gamestart = false;
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

//ѡ����Ϸģʽ��ť
//��Ϸģʽ��race���涨ʱ���ڱ�ƴ��ȷ���� survival��������������һ���������� limit�����Ƶ�����Ŀ��ʱ�䣻 hell���������������Ƶ�����Ŀʱ��
class GameModeButton :public MBUTTON {
private:
	int the_gamemode;
public:
	GameModeButton(LPCTSTR bkwait, LPCTSTR bkhold, LPCTSTR bkpushed, RECT re, int x_, int y_) :MBUTTON(bkwait, bkhold, bkpushed, re, x_, y_) {}

	//������Ϸģʽ
	void setGamemode(int gmode) {
		the_gamemode = gmode;
	}
protected:
	//�ı���Ϸģʽ
	void onclick() {
		GAMEMODE = the_gamemode;
	}
};