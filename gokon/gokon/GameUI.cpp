#include "GameUI.h"
#include "ObjectManager.h"
#include "Player.h"

void GameUI::Initialize() {
	m_gaugeHP.Initialize(100.0f, 22.0f, 100.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.25f, OBJECT, NON);
	m_gaugeMP.Initialize(100.0f, 88.0f, 100.0f, 50.0f, 0.0f, 0.0f, 1.0f, 0.25f, OBJECT, NON);
	m_gaugeHP.SetAttr(HP);
	m_gaugeMP.SetAttr(MP);
	m_gaugeFrameHP.Initialize(100.0f, 20.0f, 100.0f, 55.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_gaugeFrameMP.Initialize(100.0f, 85.0f, 100.0f, 55.0f, 0.0f, 0.0f, 1.0f, 1.0f, OBJECT, NON);
	m_gaugeFrameHP.SetAttr(HP);
	m_gaugeFrameMP.SetAttr(MP);
	m_texture.LoadTexture("Gauge.png");
	m_texture.LoadTexture("GaugeFill.png");
}

void GameUI::Update() {
	Player* player = ObjectManager::SetPlayer();
	m_gaugeHP.SetValue(player->GetMaxHP(), player->GetHP());
	m_gaugeMP.SetValue(player->GetMaxMP(), player->GetMP());
	m_gaugeHP.Update();
	m_gaugeMP.Update();
	m_gaugeFrameHP.SetValue(player->GetMaxHP());
	m_gaugeFrameMP.SetValue(player->GetMaxMP());
	m_gaugeFrameHP.Update();
	m_gaugeFrameMP.Update();
}

void GameUI::Draw() {
	m_gaugeHP.Draw(m_texture.SetTexture(1));
	m_gaugeMP.Draw(m_texture.SetTexture(1));
	m_gaugeFrameHP.Draw(m_texture.SetTexture(0));
	m_gaugeFrameMP.Draw(m_texture.SetTexture(0));
}

void GameUI::Fianlize() {
	m_texture.Finalize();
}