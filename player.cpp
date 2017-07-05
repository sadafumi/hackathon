#include "player.h"

Player player;

void Player::Init(void)
{
	this->SetTexture(TEXTURE_PLAYER);
}

void Player::Update(void)
{
	if (Input::uKeys['W'])
		this->Move(Vector3(0.0f, -1.0f, 0.0f));
	if (Input::uKeys['S'])
		this->Move(Vector3(0.0f, 1.0f, 0.0f));
	if (Input::uKeys['A'])
		this->UpdateAngle(-1.0f);
	if (Input::uKeys['D'])
		this->UpdateAngle(1.0f);
}