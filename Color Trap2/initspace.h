#pragma once
#include<graphics.h>
#include"MBUTTON.h"
#include"GameButton.h"

namespace init {
	int WINOWS_LENGTH = 1280, WINDOWS_HEIGHT = 720;

	//开始游戏按钮
	LPCTSTR st_bkwait = _T("images/st_bk_wait.png");
	LPCTSTR st_bkhold = _T("images/st_bk_hold.png");
	LPCTSTR st_bkpushed = _T("images/st_bk_pushed.png");
	int x_st_bkrect = 435, y_st_bkrect = 123;
	RECT st_bkrect = { x_st_bkrect,y_st_bkrect,x_st_bkrect+400,y_st_bkrect+100 };
	StartButton stbtn(st_bkwait, st_bkhold, st_bkpushed, st_bkrect, x_st_bkrect, y_st_bkrect);

	//再来一局游戏按钮
	LPCTSTR restart_bkwait = _T("images/restart_bk_wait.png");
	LPCTSTR restart_bkhold = _T("images/restart_bk_hold.png");
	LPCTSTR restart_bkpushed = _T("images/restart_bk_pushed.png");
	int x_restart_bkrect = 515, y_restart_bkrect = 300;
	RECT restart_bkrect = { x_restart_bkrect, y_restart_bkrect, x_restart_bkrect+250, y_restart_bkrect+80 };
	StartButton restartbtn(restart_bkwait, restart_bkhold, restart_bkpushed, restart_bkrect, x_restart_bkrect, y_restart_bkrect);

	//选择游戏模式按钮

	
	//排行榜按钮
	LPCTSTR rk_bkwait = _T("images/rk_bk_wait.png");
	LPCTSTR rk_bkhold = _T("images/rk_bk_hold.png");
	LPCTSTR rk_bkpushed = _T("images/rk_bk_pushed.png");
	int x_rk_bkrect = 435, y_rk_bkrect = 248+125;
	RECT rk_bkrect = { x_rk_bkrect,y_rk_bkrect,x_rk_bkrect+400,y_rk_bkrect+100 };
	RankButton rkbtn(rk_bkwait, rk_bkhold, rk_bkpushed, rk_bkrect, x_rk_bkrect, y_rk_bkrect);

	//游戏规则按钮
	LPCTSTR rl_bkwait = _T("images/rl_bk_wait.png");
	LPCTSTR rl_bkhold = _T("images/rl_bk_hold.png");
	LPCTSTR rl_bkpushed = _T("images/rl_bk_pushed.png");
	int x_rl_bkrect = 435, y_rl_bkrect = 373+125;
	RECT rl_bkrect = { x_rl_bkrect,y_rl_bkrect,x_rl_bkrect+400,y_rl_bkrect+100 };
	RuleButton rlbtn(rl_bkwait, rl_bkhold, rl_bkpushed, rl_bkrect, x_rl_bkrect, y_rl_bkrect);

	//退出游戏按钮
	LPCTSTR ex_bkwait = _T("images/ex_bk_wait.png");
	LPCTSTR ex_bkhold = _T("images/ex_bk_hold.png");
	LPCTSTR ex_bkpushed = _T("images/ex_bk_pushed.png");
	int x_ex_bkrect = 435, y_ex_bkrect = 498+125;
	RECT ex_bkrect = { x_ex_bkrect,y_ex_bkrect,x_ex_bkrect + 400,y_ex_bkrect + 100 };
	ExitButton exbtn(ex_bkwait, ex_bkhold, ex_bkpushed, ex_bkrect, x_ex_bkrect, y_ex_bkrect);

	//返回主菜单按钮——在初始界面中的
	LPCTSTR remenu_bkwait = _T("images/remenu_bk_wait.png");
	LPCTSTR remenu_bkhold = _T("images/remenu_bk_hold.png");
	LPCTSTR remenu_bkpushed = _T("images/remenu_bk_pushed.png");
	int x_remenu_bkrect = 20, y_remenu_bkrect = 20;
	RECT remenu_bkrect = { x_remenu_bkrect,y_remenu_bkrect,x_remenu_bkrect+250,y_remenu_bkrect+80 };
	ReturnMenuButton remenubtn(remenu_bkwait, remenu_bkhold, remenu_bkpushed, remenu_bkrect,x_remenu_bkrect,y_remenu_bkrect);

	//返回主菜单按钮——在结算界面中的
	/*LPCTSTR remenu_clear_bkwait = _T("images/remenu_bk_wait.png");		和上一个相同，故这里省略
	LPCTSTR remenu_clear_bkhold = _T("images/remenu_bk_hold.png");
	LPCTSTR remenu_clear_bkpushed = _T("images/remenu_bk_pushed.png");*/
	int x_remenubtn_clear_bkrect = 515, y_remenubtn_clear_bkrect = 450;
	RECT remenu_clear_bkrect = { x_remenubtn_clear_bkrect, y_remenubtn_clear_bkrect, x_remenubtn_clear_bkrect+250, y_remenubtn_clear_bkrect+80 };
	ReturnMenuButton remenubtn_clear(remenu_bkwait, remenu_bkhold, remenu_bkpushed, remenu_clear_bkrect,x_remenubtn_clear_bkrect,y_remenubtn_clear_bkrect);

	
	
	//问题按钮
	int	QUESIZE = 110;
	RECT que_bkrect = { 450,70,450 + 380,230 };
	LPCTSTR GAMEBK = _T("images/GAMEBK.png");
	wstring NULLW = _T("NULL");
	COLOR NULLC = null;
	Title question(que_bkrect, NULLC, NULLW, GAMEBK,QUESIZE);

	//玩家操控按钮
	int PLAYERSIZE = 70;
	LPCTSTR PLAYERBK = _T("images/PLAYERBK.png");
	RECT pl_rect1 = { 203,380,403,470 };
	RECT pl_rect2 = { 428,380,628,470 };
	RECT pl_rect3 = { 653,380,853,470 };
	RECT pl_rect4 = { 878,380,1078,470 };
	RECT pl_rect5 = { 203,480,403,570};
	RECT pl_rect6 = { 428,480,628,570};
	RECT pl_rect7 = { 653,480,853,570};
	RECT pl_rect8 = { 878,480,1078,570 };

	Ken player1(pl_rect1, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player2(pl_rect2, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player3(pl_rect3, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player4(pl_rect4, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player5(pl_rect5, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player6(pl_rect6, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player7(pl_rect7, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
	Ken player8(pl_rect8, NULLC, NULLW, PLAYERBK, PLAYERSIZE);
}