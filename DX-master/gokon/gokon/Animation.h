#pragma once
#include "main.h"

/*�L�����N�^�[���ʗp*/
#define RUNA 1
#define ENEMY 2

/*�A�j���[�V�����Ǘ��p�ϐ�*/
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
	/// �A�j���[�V�����Ǘ��z��̏�����
	/// </summary>
	void InitializeAnimation();

	/// <summary>
	/// �A�j���[�V�����̃t���[���X�V
	/// </summary>
	void UpdateFrame();

	/// <summary>
	/// UV���W���v�Z����
	/// </summary>
	void SetUV();
public:
	/// <summary>
	/// �A�j���[�V�����̏�����
	/// </summary>
	/// /// <param name="id">�L�����N�^�[��ID</param>
	void Initialize(int id);

	/// <summary>
	/// �A�j���[�V�����̍X�V��Ƃ��s��
	/// </summary>
	void Update();

	/// <summary>
	/// �A�j���[�V�����̏�Ԃ�ύX
	/// </summary>
	/// <param name="newState">�V������ԁi�}�N����`����Ă���n���j</param>
	void SetState(ANIMATION newState);

	/// <summary>
	/// �A�j���[�V�����̃��[�v�ݒ�
	/// </summary>
	/// <param name="isLoop">ture:OK false:NG</param>
	void SetLoop(bool isLoop);

	/// <summary>
	/// �A�j���[�V�����̒�����ݒ� ������2��ݒ肷���2�{�̒����ɂȂ�
	/// </summary>
	/// <param name="speed">�ǂꂾ���x�����邩</param>
	void SetSpeed(int speed);

	/// <summary>
	/// ���݂̃A�j���[�V�����ɕK�v��UV���W��Ԃ�
	/// </summary>
	/// <returns>UV���W</returns>
	FLOAT2 GetTexturePosition();
};

