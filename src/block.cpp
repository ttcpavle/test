#include "../includes/block.h"

Block::Block(Vector2 position)
{
	this->position = position;
}

void Block::Draw()
{
	DrawRectangleV(position, {3, 3}, {243, 216, 63, 255});
}
