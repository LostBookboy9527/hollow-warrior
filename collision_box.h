#ifndef _COLLISION_BOX_H_
#define _COLLISION_BOX_H_

#include "vector2.h"
#include "collision_layer.h"

#include <functional>

class CollisionManager;

class CollisionBox
{
	friend class CollisionManager;


public:
	void set_enabled(bool flag)
	{
		enabled = flag;
	}

	void set_layer_src(CollisionLayer layer)
	{
		layer_src = layer;
	}
	void set_layer_dst(CollisionLayer layer)
	{
		layer_dst = layer;
	}
	void set_on_collide(std::function<void()> func)
	{
		this->on_Collide = func;
	}
	//void set_size(Vector2& size)
	void set_size(const Vector2& size)
	{
		this->size = size;
	}
	const Vector2& get_size() const
	{
		return size;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

private:
	Vector2 size;//Åö×²Ïä³ß´ç
    Vector2 position;//Åö×²ÏäÖĞĞÄÎ»ÖÃ
	bool enabled= true;//ÊÇ·ñÆôÓÃÅö×²¼ì²â
	std::function<void()> on_Collide;
	CollisionLayer layer_src = CollisionLayer::None;//Åö×²ÏäËùÊô²ã
    CollisionLayer layer_dst = CollisionLayer::None;//Åö×²¼ì²âÄ¿±ê²ã

private:
	CollisionBox() = default;
	~CollisionBox() = default;

};



#endif // !_COLLISION_BOX_H_

