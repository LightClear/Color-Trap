#include"MBUTTON.h"
#include"initspace.h"
#include<ctime>
#include <sstream> // 包含标准库中的字符串流头文件
#include <iomanip> // 包含设置浮点数精度的头文件
using namespace init;

//24.12.13日凌晨12点，基本上完成了Button的对象搭建
//24.12.14晚上22点，还要完成游戏主体逻辑的搭建，同时要完善endgame与clearmenu那里的逻辑关系，这两个有点重复了，考虑是否要加入暂停按钮

//重新设置按钮的值
inline void resetbuttons() {
	int n = 0;
	int a[8][2] = {0};
	COLOR ass[8] = { black,green,yellow,red,brown,blue,purple,cyan };
	wstring s[8]= { { _T("黑色") } ,{ _T("绿色") } ,{ _T("黄色") } ,{ _T("红色") } ,
					{ _T("棕色") } ,{ _T("蓝色") } ,{ _T("紫色") }, { _T("青色") } };
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

//放置player类按钮
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

	//初始化窗口、按钮以及背景
	initgraph(1280,720);
	IMAGE INITBACKGROUND;
	loadimage(&INITBACKGROUND, _T("images/INITBACKGROUND.png"));
	putimage(0, 0, &INITBACKGROUND);
	IMAGE OTBACKGROUND;
	loadimage(&OTBACKGROUND, _T("images/OTHERBACKGROUND.png"));

	//初始化覆盖图片
	IMAGE REPLACE_TIME;
	IMAGE REPLACE_SCORE;
	loadimage(&REPLACE_TIME, _T("images/REPLACE_TIME.png"));
	loadimage(&REPLACE_SCORE, _T("images/REPLACE_SCORE.png"));

	//初始化规则图片
	IMAGE RULE_BK;
	loadimage(&RULE_BK, _T("images/RULE_BK.png"));
	resetbuttons();

	//初始化排行榜图片
	IMAGE RANKINGLIST_BK;
	loadimage(&RANKINGLIST_BK, _T("images/RANKINGLIST_BK.png"));

	//初始化规则按钮的值
	/*race_modebtn.setGamemode(race);
	survival_modebtn.setGamemode(survival);
	limit_modebtn.setGamemode(limit);
	hell_modebtn.setGamemode(hell);*/

	
	ExMessage msg;
	while (PROGRAM_RUNNING) {
		DWORD starttime = GetTickCount();

		//处于主菜单时
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
		
		//处于排行榜
		putimage(0, 0, &OTBACKGROUND);
		if (rank)putimage(0, 0, &RANKINGLIST_BK);	//用来放置排行榜的内容
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

		//处于游戏介绍
		putimage(0, 0, &OTBACKGROUND);
		if (rule)putimage(0, 0, &RULE_BK);	//用来放置游戏介绍的内容
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

		//处于游戏模式选择
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

			//如果选择的是

			DWORD endtime_chmode = GetTickCount();
			DWORD process_chmode = endtime_chmode - starttime_chmode;
			if (process_chmode < 1000 / 60) {
				Sleep(1000 / 60 - process_chmode);
			}
		}

		//游戏开始
		while (gamestart) {
			DWORD starttime_game = GetTickCount();

			putimage(0, 0, &OTBACKGROUND);
			int score = 0, pre_score = 1;							//玩家得分
			bool have_clicked = false;				//检测是否按了其中的某个按钮
			DWORD this_game_start = GetTickCount();	//此局游戏的开始时间
			wstring game_time_now;					//剩余时间文本
			wstring score_now;						//当前得分
			RECT game_time_now_rect = { 950,125,1000,175 };						//剩余时间文字所在区域
			RECT replace_time_rect = { 840,90,840+353,90+187 };					//剩余时间覆盖文本位置
			RECT replace_score_now_rect = { 220,100,220 + 206,100 + 140 };		//当前分数覆盖文本区域
			RECT score_now_rect = { 300,125,350,175 };							//当前分数文字所在区域
			remenubtn.putmenu();
			putplayers();

			//此局游戏开始
			while (this_game) {
				DWORD starttime_thisgame = GetTickCount();

				while (peekmessage(&msg)) {

					//检测是否点击回到主菜单按钮
					remenubtn.checkstatus(msg);
					remenubtn.putmenu();

					//检测是否点击了某个玩家按钮，且是否得分
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

				//检测是否已经按了其中某个按钮
				if (have_clicked) {
					resetbuttons();
					putplayers();
					have_clicked = false;
				}

				//检测时间是否超限，超限则此局游戏结束
				DWORD this_game_now = GetTickCount();
				if (this_game_now - this_game_start > 60000) this_game = false, CLEAR_MENU_RUNNING = true;
				//_stprintf_s(game_time_now.c_str(), game_time_now.size() + 1, _T("剩余时间为：%.2f"), 60.00 - (this_game_now - this_game_start) / 1000.0);
				
				//放置得分
				if (pre_score != score) {
					std::wstringstream wss; // 创建一个宽字符串流对象
					// 设置精度并插入格式化的字符串
					wss << L"当前得分：" << std::fixed << score;
					// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
					score_now = wss.str();
					settextcolor(BLACK);
					setbkmode(TRANSPARENT);
					settextstyle(40, 0, _T("Segoe UI Black"));
					putimage(replace_score_now_rect.left, replace_score_now_rect.top, &REPLACE_SCORE);
					drawtext(score_now.c_str(), &score_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
				}
				
				//设置剩余时间文本
				std::wstringstream wss; // 创建一个宽字符串流对象
				double elapsedTime = 60.00 - (this_game_now - this_game_start) / 1000.0; // 计算经过的时间
				// 设置精度并插入格式化的字符串
				if(elapsedTime>=10)wss << L"剩余时间为：" << std::fixed << std::setprecision(2) << elapsedTime;
				else wss << L"剩余时间为： " << std::fixed << std::setprecision(2) << elapsedTime;
				// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
				game_time_now = wss.str();
				//放置剩余时间文本
				//drawtext(L"                                       ", &game_time_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
				// 设置填充样式为当前背景色
				//setfillstyle(SOLID_FILL, getbkcolor());
				// 用填充的矩形覆盖文本区域
				///bar(game_time_now_rect.left, game_time_now_rect.top, game_time_now_rect.right, game_time_now_rect.bottom);
				if (this_game_now - this_game_start <= 45000)settextcolor(BLACK);
				else settextcolor(RED);
				setbkmode(TRANSPARENT);
				settextstyle(40, 0, _T("微软雅黑"));
				putimage(replace_time_rect.left, replace_time_rect.top, &REPLACE_TIME);
				drawtext(game_time_now.c_str(), &game_time_now_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);			

				DWORD endtime_thisgame = GetTickCount();
				DWORD process_thisgame = endtime_thisgame - starttime_thisgame;
				if (process_thisgame < 1000 / 60) {
					Sleep(1000 / 60 - process_thisgame);
				}
			}

			//结算菜单
			putimage(0, 0, &OTBACKGROUND);
			wstring gameover=_T("游戏结束"), score_final;	//游戏结束文本，最终得分文本
			RECT gameover_rect = { 590,100,690,150 };
			RECT score_final_rect = { 590,200,690,250 };
			std::wstringstream wss; // 创建一个宽字符串流对象
			// 设置精度并插入格式化的字符串
			wss << L"最终得分：" << std::fixed << score;
			// 从字符串流中获取格式化后的字符串，并赋值给 wstring 变量
			score_final = wss.str();
			settextcolor(BLACK);
			setbkmode(TRANSPARENT);
			settextstyle(50, 0, _T("微软雅黑"));
			drawtext(gameover.c_str(), &gameover_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			drawtext(score_final.c_str(), &score_final_rect, DT_NOCLIP | DT_SINGLELINE | DT_CENTER);
			restartbtn.putmenu();

			while (CLEAR_MENU_RUNNING) {
				DWORD starttime_clearmenu = GetTickCount();

				while (peekmessage(&msg)) {
					//检测重开按钮和返回主菜单按钮
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