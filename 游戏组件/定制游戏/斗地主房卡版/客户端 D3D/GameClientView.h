#ifndef GAME_CLIENT_HEAD_FILE
#define GAME_CLIENT_HEAD_FILE

#pragma once

#include "Stdafx.h"
#include "GameLogic.h"
#include "CardControl.h"
#include "ScoreControl.h"
#include "HistoryRecord.h"
#include "ChatEdit.h"
#include "ChatMessage.h"
//////////////////////////////////////////////////////////////////////////////////

//视图位置
#define MYSELF_VIEW_ID				1									//视图位置

//控制消息
#define IDM_START					(WM_USER+200)						//开始消息
#define IDM_OUT_CARD				(WM_USER+201)						//出牌消息
#define IDM_PASS_CARD				(WM_USER+202)						//PASS消息
#define IDM_OUT_PROMPT				(WM_USER+203)						//提示消息
#define IDM_CALL_SCORE				(WM_USER+204)						//叫分消息
#define	IDM_LEFT_HIT_CARD			(WM_USER+205)						//左击扑克
#define IDM_SORT_HAND_CARD			(WM_USER+206)						//排列扑克
#define IDM_LAST_TURN_CARD			(WM_USER+207)						//上轮扑克
#define IDM_TRUSTEE_CONTROL			(WM_USER+208)						//托管控制
#define IDM_GAME_SOUND				(WM_USER+209)						//游戏设置
#define IDM_GAME_CLOSE				(WM_USER+210)						//游戏关闭

//辅助消息
#define IDM_DISPATCH_FINISH			(WM_USER+300)						//发牌完成
#define IDM_REVERSAL_FINISH			(WM_USER+301)						//翻牌完成

#define IDM_SEARCH_CARD				(WM_USER+320)						//牌型搜索

#define SEARCH_MISSILE				0									//搜索火箭
#define SEARCH_BOMB					1									//搜索炸弹
#define SEARCH_THREE_TOW_LINE		2									//搜索飞机
#define SEARCH_DOUBLE_LINE			3									//搜索双顺
#define SEARCH_SINGLE_LINE			4									//搜索单顺
#define SEARCH_THREE_TWO_ONE		5									//搜索三带N

//////////////////////////////////////////////////////////////////////////////////

//游戏视图
class CGameClientView : public CGameFrameViewD3D
{
	//状态变量
public:
	bool							m_bCellScoreEnd;					//头像状态
	bool							m_bGameEnd;							//游戏结束
	bool							m_bShowScore;						//积分状态
	bool							m_bLastTurnState;					//上轮标志
	bool							m_bWaitCallScore;					//等待叫分
	bool							m_bUserPass[GAME_PLAYER];			//放弃标志
	bool							m_bUserCheat[GAME_PLAYER];			//作弊标志
	tagHistoryScore	*				m_pHistoryScore[GAME_PLAYER];		//积分信息
	double							m_dTimeScale;						//时间帧数比例
	BYTE							m_cbSenceIndex;						//场景索引
	bool							m_bPlaySound;						//游戏声音
	bool							m_bUserTrustee[GAME_PLAYER];		//托管标志
	bool							m_bChangeTimePos;
	WORD							m_wMessageLen;						//消息长度
	bool							m_bShowChatMessage;					//查看消息


	//游戏变量
protected:
	LONG							m_lCellScore;						//单元分数
	BYTE							m_cbBombCount;						//炸弹个数
	BYTE							m_cbCallScore[GAME_PLAYER];			//叫分信息
	tagScoreInfo					m_ScoreInfo;						//积分信息

	//庄家变量
protected:
	WORD							m_wBankerUser;						//庄家用户
	BYTE							m_cbBankerScore;					//庄家叫分

	//移动变量
protected:
	bool							m_bMoveMouse;						//移动标志
	bool							m_bSwitchCard;						//交换标志
	bool							m_bSelectCard;						//选择标志
	BYTE							m_cbHoverCardItem;					//盘旋索引
	BYTE							m_cbMouseDownItem;					//点击索引
	BYTE							m_cbSwitchCardItem;					//交换索引

	//位置变量
protected:
	CPoint							m_ptPass[GAME_PLAYER];				//放弃位置
	CPoint							m_ptBanker[GAME_PLAYER];			//庄家位置
	CPoint							m_ptCountWarn[GAME_PLAYER];			//报警位置
	CPoint							m_ptCallScore[GAME_PLAYER];			//叫分位置
	CPoint							m_ptOrderFlag[GAME_PLAYER];			//等级位置
	CPoint							m_ptChatBubble[GAME_PLAYER];		//聊天位置
	CPoint							m_ptMachine[GAME_PLAYER];			//托管位置

	//爆炸动画
protected:
	bool							m_bCartoonBomb;						//动画标志
	WORD							m_wCartoonBombIndex;				//帧数索引
	CLapseCount						m_CartoonBombLapseCount;			//流逝计数

	//飞机动画
protected:
	bool							m_bCartoonPlan;						//动画标志
	WORD							m_wCartoonPlanIndex;				//帧数索引
	CPoint							m_ptCartoonPlan;					//飞机位置
	CLapseCount						m_CartoonPlanLapseCount;			//流逝计数

	//火箭动画
protected:
	bool							m_bCartoonRocket;					//动画标志
	WORD							m_wCartoonRocketIndex;				//帧数索引
	CPoint							m_ptCartoonRocket;					//火箭位置
	CLapseCount						m_CartoonRocketLapseCount;			//流逝计数

	//顺子动画
protected:
	bool							m_bCartoonLine;						//动画标志
	WORD							m_wCartoonLineIndex;				//帧数索引
	CLapseCount						m_CartoonLineLapseCount;			//流逝计数

	//翻牌动画
protected:
	bool							m_bReversalCard;					//动画标志
	WORD							m_wReversalCardIndex;				//帧数索引
	CLapseCount						m_ReversalCardLapseCount;			//流逝计数

	//庄家动画
protected:
	WORD							m_wBankerMovieIndex;				//帧数索引
	CLapseCount						m_BankerMovieLapseCount;			//流逝计数

	//发牌动画
protected:
	bool							m_bRiffleCard;						//动画标志
	bool							m_bDispatchCard;					//动画标志
	WORD							m_wDispatchCardIndex;				//帧数索引
	CLapseCount						m_DispatchCardLapseCount;			//流逝计数

	//发牌数据
protected:
	WORD							m_wStartUser;						//起始用户
	BYTE							m_cbHandCardData[GAME_PLAYER][NORMAL_COUNT];	//发牌数据

	//报警动画
protected:
	bool							m_bCountWarn[GAME_PLAYER];			//动画标志
	WORD							m_wCountWarnIndex[GAME_PLAYER];		//帧数索引
	CLapseCount						m_CountWarnLapseCount[GAME_PLAYER];	//流逝计数

	//游戏按钮
public:
	CVirtualButton					m_btScore;							//看分按钮
	CVirtualButton					m_btStart;							//开始按钮
	CVirtualButton					m_btOutCard;						//出牌按钮
	CVirtualButton					m_btPassCard;						//PASS按钮
	CVirtualButton					m_btOutPrompt;						//提示按钮
	CVirtualButton					m_btPlayAgain;						//再来一局
	CVirtualButton					m_btReturn;							//返回大厅
	CVirtualButton					m_btClose;							//关闭按钮
	CVirtualButton					m_btMin;							//最小按钮
	CVirtualButton					m_btSound;							//声音按钮
	CVirtualButton					m_btHistoryChat;					//聊天记录

	//功能按钮
public:
	CVirtualButton					m_btCancelTrustee;					//取消托管
	CVirtualButton					m_btTrustee;						//托管按钮
	CVirtualButton					m_btLastTurn;						//上轮按钮
	CVirtualButton					m_btSortCard;						//排序按钮
//	CVirtualButton					m_btExpression;						//表情按钮
//	CVirtualButton					m_btVoice;							//语音按钮
	CVirtualButton					m_btEnter;							//回车按钮
//	CVirtualButton					m_btSwitchSence;					//切换场景

	//叫分按钮
public:
	CVirtualButton					m_btCallScore1;						//叫分按钮
	CVirtualButton					m_btCallScore2;						//叫分按钮
	CVirtualButton					m_btCallScore3;						//叫分按钮
	CVirtualButton					m_btCallScoreNone;					//叫分按钮

	//背景资源
protected:
	CD3DTexture						m_TextureBack;						//背景资源
	CD3DTexture						m_TextureBackButtom;				//背景资源
	CD3DTexture						m_TextureUserPlayer;				//用户框架
	CD3DTexture						m_TextureUserPlayerGame;			//用户框架
	CD3DTexture						m_TextureUserMySelf;				//用户框架
	CD3DTexture						m_TextureGameScoreBack;				//结算背景
	CD3DTexture						m_TextureChatBubble;				//泡泡聊天

	//资源变量
protected:
	CD3DSprite						m_TextureBankerFlag[GAME_PLAYER];	//庄家标志
	CD3DTexture						m_TextureCellNumber;				//信息数字
	CD3DTexture						m_TextureBankerCardBack;			//资源变量
	CD3DTexture						m_TextureRemnantCardNumber;			//资源变量
	CD3DTexture						m_TextureTimeBack;					//时间背景
	CD3DTexture						m_TextureTimeNumber;				//时间数字
	CD3DFontEx						m_FontChat;							//聊天字体
	CD3DTexture						m_TextureCardCountFrame1;			//余牌框架
	CD3DTexture						m_TextureCardCountFrame2;			//余牌框架
	CD3DTexture						m_TextureChatBack;					//聊天背景	
	CFont							m_MyFont;

	//动态资源
protected:
	CD3DTexture						m_TextureUserPass;					//放弃标志
	CD3DTexture						m_TextureLastTurn;					//上轮标志
	CD3DTexture						m_TextureCallScore;					//用户叫分
	CD3DTexture						m_TextureCartoonBomb;				//状态信息
	CD3DTexture						m_TextureCartoonPlan;				//飞机动画
	CD3DTexture						m_TextureMemberOrder;				//飞机动画
	CD3DTexture						m_TextureCartoonRocket;				//火箭动画
	CD3DTexture						m_TextureRocket;					//火箭动画
	CD3DTexture						m_TextureRocketLight;				//火箭动画
	CD3DTexture						m_TextureDispatchCard;				//资源变量
	CD3DTexture						m_TextureHistoryScore;				//资源变量
	CD3DTexture						m_TextureReversalCard;				//资源变量
	CD3DTexture						m_TextureWaitCallScore;				//等待叫分
	CD3DTexture						m_TextureCartoonTime;				//时间动画
	CD3DTexture						m_TextureCartoonLine;				//顺子动画
	CD3DTexture						m_TextureLine;						//顺子动画
	CD3DTexture						m_TextureWarn[5];					//警报动画
	CD3DTexture						m_TextureTimeLight;					//时间背景
	CD3DTexture						m_TextureMachine;					//托管标志

	

	//控件变量
public:
	CGameLogic						m_GameLogic;						//游戏逻辑
	CScoreControl					m_ScoreControl;						//积分控件

	//聊天变量
public:
	CEdit							m_ChatInput;							//聊天输入
	CString							m_strChat[GAME_PLAYER];					//聊天内容
	WORD							m_ChatChair[GAME_PLAYER];				//聊天用户
	INT								m_nChatStrlen[GAME_PLAYER];
	DWORD							m_dwChatTime;
	CChatMessage					m_ChatMessage;

	//扑克控件
public:
	CCardControl					m_BackCardControl;					//底牌扑克
	CCardControl					m_HandCardControl[GAME_PLAYER];		//用户扑克
	CCardControl					m_UserCardControl[GAME_PLAYER];		//扑克视图
	CCardControl					m_ChetCardContol[GAME_PLAYER];
protected:
	CBrush							m_brush;							//背景画刷

	//函数定义
public:
	//构造函数
	CGameClientView();
	//析构函数
	virtual ~CGameClientView();

public:
	//消息解释
	virtual BOOL PreTranslateMessage(MSG * pMsg);

	//重载函数
private:
	//重置界面
	virtual VOID ResetGameView();
	//调整控件
	virtual VOID RectifyControl(INT nWidth, INT nHeight);

	//设备事件
public:
	//丢失设备
	virtual VOID OnLostDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//重置设备
	virtual VOID OnResetDevice(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//界面函数
protected:
	//动画驱动
	virtual VOID CartoonMovie();
	//配置设备
	virtual VOID InitGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);
	//绘画界面
	virtual VOID DrawGameView(CD3DDevice * pD3DDevice, INT nWidth, INT nHeight);

	//庄家设置
public:
	//设置庄家
	VOID SetBankerUser(WORD wBankerUser);
	//设置倍数
	VOID SetBankerScore(BYTE cbBankerScore);
	//显示底牌
	VOID ShowBankerCard(BYTE cbCardData[3]);

	//功能函数
public:
	//单元积分
	VOID SetCellScore(LONG lCellScore);
	//炸弹次数
	VOID SetBombCount(BYTE cbBombCount);
	//设置结束
	VOID ShowGameScoreInfo(tagScoreInfo & ScoreInfo,bool bGameEnd);
	// 绘画数字
	void DrawNumber(CD3DDevice * pD3DDevice, CD3DTexture* ImageNumber, TCHAR * szImageNum, SCORE lOutNum, INT nXPos, INT nYPos, UINT uFormat = DT_LEFT);
	// 绘画数字
	void DrawNumber(CD3DDevice * pD3DDevice, CD3DTexture* ImageNumber, TCHAR * szImageNum, CString szOutNum, INT nXPos, INT nYPos, UINT uFormat = DT_LEFT);
	// 绘画数字
	void DrawNumber(CD3DDevice * pD3DDevice, CD3DTexture* ImageNumber, TCHAR * szImageNum, TCHAR* szOutNum ,INT nXPos, INT nYPos,  UINT uFormat = DT_LEFT);
	//绘画时间
	void DrawUserTimerEx(CD3DDevice * pD3DDevice, INT nXPos, INT nYPos, WORD wUserClock);
	//显示聊天
	void ShowChatMessage(LPCTSTR strMessage,LPCTSTR UserName);
	//设置结束框位置
	void SetScoreControlPos(INT nXOffset,INT nYOffset);
	//聊天效验
	bool EfficacyUserChat(LPCTSTR pszChatString, WORD wExpressionIndex);
	//查看聊天
	void OnHideChatMessage();
	// 添加逗号
	CString AddComma( LONGLONG lScore , bool bPlus = false);


	//牌型动画
public:
	//飞机动画
	VOID ShowCartoonPlan(bool bCartoon);
	//爆炸动画
	VOID ShowCartoonBomb(bool bCartoon);
	//火箭动画
	VOID ShowCartoonRocket(bool bCartoon);
	//顺子动画
	VOID ShowCartoonLine(bool bCartoon,BYTE cbCardType);

	//明牌函数
public:
	//用户明牌
	VOID UserValidCard(WORD wChairID, BYTE cbCardData[MAX_COUNT], BYTE cbCardCount = 17);

	//状态函数
public:
	//设置上轮
	VOID SetLastTurnState(bool bLastTurnState);
	//等待叫分
	VOID SetWaitCallScore(bool bWaitCallScore);
	//设置放弃
	VOID SetUserPassState(WORD wChairID, bool bUserPass);
	//设置警告
	VOID SetUserCountWarn(WORD wChairID, bool bCountWarn);
	//设置叫分
	VOID SetUserCallScore(WORD wChairID, BYTE cbCallScore);
	//设置积分
	VOID SetHistoryScore(WORD wChairID, tagHistoryScore * pHistoryScore);
	//设置场景
	VOID SetUserAvatar(bool bCellScoreEnd);
	//设置比例
	VOID SetTimeScale(WORD wTime);
	//托管状态
	VOID SetUserTrustee(WORD wChairID,bool bTrustee){m_bUserTrustee[wChairID] = bTrustee;}
	//重新开始
	VOID SetChangeTimePos(bool bChange){m_bChangeTimePos = bChange;}

	//发牌函数
public:
	//发牌动画
	VOID StopDispatchCard();
	//发牌动画
	VOID ShowDispatchCard(BYTE cbCardData[NORMAL_COUNT], WORD wStartUser);

	//按钮消息
public:
	//开始按钮
	VOID OnBnClickedStart();
	//积分按钮
	VOID OnBnClickedScore();
	//出牌按钮
	VOID OnBnClickedOutCard();
	//排序按钮
	VOID OnBnClickedSortCard();
	//上轮按钮
	VOID OnBnClickedLastTurn();
	//托管按钮
	VOID OnBnClickedTrustee();
	//托管按钮
	VOID OnBnClickedCancelTrustee();
	//PASS按钮
	VOID OnBnClickedPassCard();
	//提示按钮
	VOID OnBnClickedOutPrompt();
	//一分按钮
	VOID OnBnClickedCallScore1();
	//二分按钮
	VOID OnBnClickedCallScore2();
	//三分按钮
	VOID OnBnClickedCallScore3();
	//放弃按钮
	VOID OnBnClickedCallScoreNone();
	//表情按钮
	VOID OnBnClickedExpression();
	//回车按钮
	VOID OnBnClickedEnter();
	//语音按钮
	VOID OnBnClickedVoice();
	//切换场景按钮
	VOID OnBnClickedSwitchSence();

	//重载函数
public:
	//消息命令
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	//消息函数
public:
	//鼠标消息
	VOID OnRButtonUp(UINT nFlags, CPoint MousePoint);
	//鼠标消息
	VOID OnLButtonUp(UINT nFlags, CPoint MousePoint);
	//鼠标消息
	VOID OnMouseMove(UINT nFlags, CPoint MousePoint);
	//鼠标消息
	VOID OnLButtonDown(UINT nFlags, CPoint MousePoint);
	//鼠标消息
	VOID OnLButtonDblClk(UINT nFlags, CPoint MousePoint);
	//光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMessage);
	//控件颜色
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnDestroy();


	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif