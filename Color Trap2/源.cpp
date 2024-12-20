#include"MBUTTON.h"
#include"initspace.h"
#include<ctime>
#include <sstream> // ������׼���е��ַ�����ͷ�ļ�
#include <iomanip> // �������ø��������ȵ�ͷ�ļ�
using namespace init;

//24.12.13���賿12�㣬�����������Button�Ķ���
//24.12.14����22�㣬��Ҫ�����Ϸ�����߼��Ĵ��ͬʱҪ����endgame��clearmenu������߼���ϵ���������е��ظ��ˣ������Ƿ�Ҫ������ͣ��ť

//�������ð�ť��ֵ
inline void resetbuttons() {
	int n = 0;
	int a[8][2] = {0};
	COLOR ass[8] = { black,green,yellow,red,brown,blue,purple,cyan };
	wstring s[8]= { { _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") } ,
					{ _T("��ɫ") } ,{ _T("��ɫ") } ,{ _T("��ɫ") }, { _T("��ɫ") } };
	wstring tmps;
	srand(time(0));
	int tmp1,tmp2;
	while (n < 8) {
		tmp1 = rand() % 8, tmp2 = rand() % 8;
		if (!a[tmp1][0] && !a[tmp2][1]) {
			tmps = s[tmp2];
			switch (n) {
			case 0:player1.reset(ass[tmp1], tmps); break;
			case 1:player2.reset(ass[tmp1], tmps); break;
			case 2:player3.reset(ass[tmp1], tmps); break;
			case 3:player4.reset(ass[tmp1], tmps); break;
			case 4:player5.reset(ass[tmp1], tmps); break;
			case 5:player6.reset(ass[tmp1], tmps); break;
			case 6:player7.reset(ass[tmp1], tmps); break;
			case 7:player8.reset(ass[tmp1], tmps); break;
			}
			a[tmp1][0] = a[tmp2][1] = 1;
			n++;
		}
	}
	while (1) {
		tmp1 = rand() % 8, tmp2 = rand() % 8;
		if (tmp1 != tmp2) {
			tmps = s[tmp2];
			question.reset(ass[tmp1], tmps);
			break;
		}
	}
}

//����player�ఴť
inline void putplayers() {
	question.putthings();
	player1.putthings();
	player2.putthings();
	player3.putthings();
	player4.putthings();
	player5.putthings();
	player6.putthings();
	player7.putthings();
	player8.putthings();
}


int main() {

	//��ʼ�����ڡ���ť�Լ�����
	initgraph(1280,720);
	IMAGE INITBACKGROUND;
	loadimage(&INITBACKGROUND, _T("images/INITBACKGROUND.png"));
	putimage(0, 0, &INITBACKGROUND);
	IMAGE OTBACKGROUND;
	loadimage(&OTBACKGROUND, _T("images/OTHERBACKGROUND.png"));

	//��ʼ������ͼƬ
	IMAGE REPLACE_TIME;
	IMAGE REPLACE_SCORE;
	loadimage(&REPLACE_TIME, _T("images/REPLACE_TIME.png"));
	loadimage(&REPLACE_SCORE, _T("images/REPLACE_SCORE.png"));

	//��ʼ������ͼƬ
	IMAGE RULE_BK;
	loadimage(&RULE_BK, _T("images/RULE_BK.png"));
	resetbuttons();

	//��ʼ�����а�ͼƬ
	IMAGE RANKINGLIST_BK;
	loadimage(&RANKINGLIST_BK, _T("images/RANKINGLIST_BK.png"));

	//��ʼ������ť��ֵ
	/*race_modebtn.setGamemode(race);
	survival_modebtn.setGamemode(survival);
	limit_modebtn.setGamemode(limit);
	hell_modebtn.setGamemode(hell);*/

	
	ExMessage msg;
	while (PROGRAM_RUNNING) {
		DWORD starttime = GetTickCount();

		//�������˵�ʱ
		putimage(0, 0, &INITBACKGROUND);
		while (INIT_MENU_RUNNING) {
			DWORD starttime_initmenu = GetTickCount();

			stbtn.putmenu();
			rkbtn.putmenu();
			rlbtn.putmenu();
			exbtn.putmenu();
			chmodebtn.putmenu();

			while (peekmessage(&msg)) {

				stbtn.checkstatus(msg);
				rlbtn.checkstatus(msg);
				rkbtn.checkstatus(msg);
				exbtn.checkstatus(msg);
				chmodebtn.checkstatus(msg);
				
				stbtn.putmenu();
				rkbtn.putmenu();
				rlbtn.putmenu();
				exbtn.putmenu();
				chmodebtn.putmenu();
			}

			DWORD endtime_initmenu = GetTickCount();
			DWORD process_initmenu = endtime_initmenu - starttime_initmenu;
			if (process_initmenu < 1000 / 60) {
				Sleep(1000 / 60 - process_initmenu);
			}
		}
		
		//�������а�
		putimage(0, 0, &OTBACKGROUND);
		if (rank)putimage(0, 0, &RANKINGLIST_BK);	//�����������а������
		while (rank) {
			DWORD starttime_rank = GetTickCount();

			remenubtn.putmenu();
			while (peekmessage(&msg)) {
				remenubtn.checkstatus(msg);
				remenubtn.putmenu();
			}

			DWORD endtime_rank = GetTickCount();
			DWORD process_rank = endtime_rank - starttime_rank;
			if (process_rank < 1000 / 60) {
				Sleep(1000 / 60 - process_rank);
			}
		}

		//������Ϸ����
		putimage(0, 0, &OTBACKGROUND);
		if (rule)putimage(0, 0, &RULE_BK);	//����������Ϸ���ܵ�����
		while (rule) {
			DWORD starttime_rule = GetTickCount();

			remenubtn.putmenu();
			while (peekmessage(&msg)) {
				remenubtn.checkstatus(msg);
				remenubtn.putmenu();
			}

			DWORD endtime_rule = GetTickCount();
			DWORD process_rule = endtime_rule - starttime_rule;
			if (process_rule < 1000 / 60) {
				Sleep(1000 / 60 - process_rule);
			}
		}

		//������Ϸģʽѡ��
		while (CHOOSE_GAMEMODE) {
			putimage(0, 0, &OTBACKGROUND);
			DWORD starttime_chmode = GetTickCount();

			remenubtn.putmenu();
			race_modebtn.putmenu();
			survival_modebtn.putmenu();
			limit_modebtn.putmenu();
			hell_modebtn.putmenu();
			while (peekmessage(&msg)) {

				remenubtn.checkstatus(msg);
				race_modebtn.checkstatus(msg);
				survival_modebtn.checkstatus(msg);
				limit_modebtn.checkstatus(msg);
				hell_modebtn.checkstatus(msg);

				remenubtn.putmenu();
				race_modebtn.putmenu();
				survival_modebtn.putmenu();
				limit_modebtn.putmenu();
				hell_modebtn.putmenu();
			}

			//���ѡ�����

			DWORD endtime_chmode = GetTickCount();
			DWORD process_chmode = endtime_chmode - starttime_chmode;
			if (process_chmode < 1000 / 60) {
				Sleep(1000 / 60 - process_chmode);
			}
		}

		//��Ϸ��ʼ
		while (gamestart) {
			DWORD starttime_game = GetTickCount();

			putimage(0, 0, &OTBACKGROUND);
			int score = 0, pre_score = 1;							//��ҵ÷�
			bool have_clicked = false;				//����Ƿ������е�ĳ����ť
			DWORD this_game_start = GetTickCount();	//�˾���Ϸ�Ŀ�ʼʱ��
			wstring game_time_now;					//ʣ��ʱ���ı�
			wstring score_now;						//��ǰ�÷�
			RECT game_time_now_rect = { 950,125,1000,175 };						//ʣ��ʱ��������������
			RECT replace_time_rect = { 840,90,840+353,90+187 };					//ʣ��ʱ�串���ı�λ��
			RECT replace_score_now_rect = { 220,100,220 + 206,100 + 140 };		//��ǰ���������ı�����
			RECT score_now_rect = { 300,125,350,175 };							//��ǰ����������������
			remenubtn.putmenu();
			putplayers();

			//�˾���Ϸ��ʼ
			while (this_game) {
				DWORD starttime_thisgame = GetTickCount();

				while (peekmessage(&msg)) {

					//����Ƿ����ص����˵���ť
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					//����Ƿ�����ĳ����Ұ�ť�����Ƿ�÷�
					if (!have_clicked && player1.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player1))pre_score = score, score++;
					}
					if(!have_clicked && player2.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player2))pre_score = score, score++;
					}
					if(!have_clicked && player3.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player3))pre_score = score, score++;
					}
					if(!have_clicked && player4.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player4))pre_score = score, score++;
					}
					if(!have_clicked && player5.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player5))pre_score = score, score++;
					}
					if(!have_clicked && player6.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player6))pre_score = score, score++;
					}
					if(!have_clicked && player7.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player7))pre_score = score, score++;
					}
					if(!have_clicked && player8.checkclick(msg)) {
						have_clicked = true;
						if (question.checkscore(player8))pre_score = score, score++;
					}
				}

				//����Ƿ��Ѿ���������ĳ����ť
				if (have_clicked) {
					resetbuttons();
					putplayers();
					have_clicked = false;
				}

				//���ʱ���Ƿ��ޣ�������˾���Ϸ����
				DWORD this_game_now = GetTickCount();
				if (this_game_now - this_game_start > 60000) this_game = false, CLEAR_MENU_RUNNING = true;
				//_stprintf_s(game_time_now.c_str(), game_time_now.size() + 1, _T("ʣ��ʱ��Ϊ��%.2f"), 60.00 - (this_game_now - this_game_start) / 1000.0);
				
				//���õ÷�
				if (pre_score != score) {
					std::wstringstream wss; // ����һ�����ַ���������
					// ���þ��Ȳ������ʽ�����ַ���
					wss << L"��ǰ�÷֣�" << std::fixed << score;
					// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
					score_now = wss.str();
					settextcolor(BLACK);
					setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("Segoe UI Black"));
					putimage(replace_score_now_rect.left, replace_score_now_rect.top, &REPLACE_SCORE);
					drawtext(score_now.c_str(), &score_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
				}
				
				//����ʣ��ʱ���ı�
				std::wstringstream wss; // ����һ�����ַ���������
				double elapsedTime = 60.00 - (this_game_now - this_game_start) / 1000.0; // ���㾭����ʱ��
				// ���þ��Ȳ������ʽ�����ַ���
				if(elapsedTime>=10)wss << L"ʣ��ʱ��Ϊ��" << std::fixed << std::setprecision(2) << elapsedTime;
				else wss << L"ʣ��ʱ��Ϊ�� " << std::fixed << std::setprecision(2) << elapsedTime;
				// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
				game_time_now = wss.str();
				//����ʣ��ʱ���ı�
				//drawtext(L"                                       ", &game_time_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
				// ���������ʽΪ��ǰ����ɫ
				//setfillstyle(SOLID_FILL, getbkcolor());
				// �����ľ��θ����ı�����
				///bar(game_time_now_rect.left, game_time_now_rect.top, game_time_now_rect.right, game_time_now_rect.bottom);
				if (this_game_now - this_game_start <= 45000)settextcolor(BLACK);
				else settextcolor(RED);
				setbkmode(TRANSPARENT);
				settextstyle(40, 0, _T("΢���ź�"));
				putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
				drawtext(game_time_now.c_str(), &game_time_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);			

				DWORD endtime_thisgame = GetTickCount();
				DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
				if (process_thisgame < 1000 / 60) {
					Sleep(1000 / 60 - process_thisgame);
				}
			}

			//����˵�
			putimage(0, 0, &OTBACKGROUND);
			wstring gameover=_T("��Ϸ����"), score_final;	//��Ϸ�����ı������յ÷��ı�
			RECT gameover_rect = { 590,100,690,150 };
			RECT score_final_rect = { 590,200,690,250 };
			std::wstringstream wss; // ����һ�����ַ���������
			// ���þ��Ȳ������ʽ�����ַ���
			wss << L"���յ÷֣�" << std::fixed << score;
			// ���ַ������л�ȡ��ʽ������ַ���������ֵ�� wstring ����
			score_final = wss.str();
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("΢���ź�"));
			drawtext(gameover.c_str(), &gameover_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			drawtext(score_final.c_str(), &score_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			restartbtn.putmenu();

			while (CLEAR_MENU_RUNNING) {
				DWORD starttime_clearmenu = GetTickCount();

				while (peekmessage(&msg)) {
					//����ؿ���ť�ͷ������˵���ť
					restartbtn.checkstatus(msg);
					restartbtn.putmenu();
					remenubtn_clear.checkstatus(msg);
					remenubtn_clear.putmenu();
				}
				
			}
		}

		
		DWORD endtime = GetTickCount();
		DWORD process = endtime - starttime;
		if (process < 1000 / 60) {
			Sleep(1000 / 60 - process);
		}
	}
	EndBatchDraw();
	return 0;
}