//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|
// Item.h 2017.07.8
// Author: �@��j�� AT12A242-37 60118
//+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+|

//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �C���N���[�h�t�@�C��
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
#include "Item.h"
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �ÓI�ϐ�
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Item item[ITEM_MAX];
static int ItemCon = 0;
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// �ÓI�֐�
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
Item::Item()
{

	ItemType = (ITEMTYPE)(rand()%ITEM_TYPE_MAX);
	Object::SetTexture(JudgeItemuType(ItemType));
	Object::SetPosition(GeneratedPosition(&this->Position));
	ItemCon++;
}
void Item::Update()
{
	
}
TEXTURE_NUM JudgeItemuType(ITEMTYPE ItemType)
{
	if (ItemType == ITEM_TYPE_RED)   {return TEXTURE_BULLET;}
	if (ItemType == ITEM_TYPE_GREEN) {return TEXTURE_BULLET;}
	if (ItemType == ITEM_TYPE_BLUE)  {return TEXTURE_BULLET;}
	return TEXTURE_EMPTY;
}
VECTOR3 GeneratedPosition(VECTOR3* Vec3)
{
	static int x=0, y=0;
	Vec3->z = ITEM_Z_POS;
	Vec3->x += x * 50;
	Vec3->y += y * 50;
	if( x == y )
	{
		y++;
		x = 0;
	}
	x++;
	return *Vec3;
}
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// End.
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+