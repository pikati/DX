#pragma once
#include "main.h"

/*キャラクター判別用*/
#define RUNA 1
#define ENEMY 2

/*アニメーション管理用変数*/
enum ANIMATION {
	RUNA_IDOL,
	RUNA_MOVE,
	RUNA_JUMP,
	RUNA_ATTACK,
	RUNA_DAMAGE,
	RUNA_NON,
	ENEMY_IDOL = 0,
	ENEMY_MOVE
};

class Animation
{
private:
	int			m_frame;
	int			m_totalFrame;
	int			m_id;
	int			m_speed;
	bool		m_loop;
	FLOAT2		m_uv;
	ANIMATION	m_state;
	
	int			m_animation[6];

	/// <summary>
	/// アニメーション管理配列の初期化
	/// </summary>
	void InitializeAnimation();

	/// <summary>
	/// アニメーションのフレーム更新
	/// </summary>
	void UpdateFrame();

	/// <summary>
	/// UV座標を計算する
	/// </summary>
	void SetUV();
public:
	/// <summary>
	/// アニメーションの初期化
	/// </summary>
	/// /// <param name="id">キャラクターのID</param>
	void Initialize(int id);

	/// <summary>
	/// アニメーションの更新作業を行う
	/// </summary>
	void Update();

	/// <summary>
	/// アニメーションの状態を変更
	/// </summary>
	/// <param name="newState">新しい状態（マクロ定義されてるやつを渡す）</param>
	void SetState(ANIMATION newState);

	/// <summary>
	/// アニメーションのループ設定
	/// </summary>
	/// <param name="isLoop">ture:OK false:NG</param>
	void SetLoop(bool isLoop);

	/// <summary>
	/// アニメーションの長さを設定 引数に2を設定すると2倍の長さになる
	/// </summary>
	/// <param name="speed">どれだけ遅くするか</param>
	void SetSpeed(int speed);

	/// <summary>
	/// 現在のアニメーションに必要なUV座標を返す
	/// </summary>
	/// <returns>UV座標</returns>
	FLOAT2 GetTexturePosition();
};

