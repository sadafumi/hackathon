#pragma once
#include "Lib\core.h"

typedef class Player : public Object
{
public:
	void Init(void);
	void Update(void);
private:
	float Speed;
} *pPlayer;