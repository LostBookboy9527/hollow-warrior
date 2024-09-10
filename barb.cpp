#include "barb.h"
#include "collision_manager.h"
#include "resources_manager.h"
#include "character_manager.h"

Barb::Barb()
{
	diff_peeriod = range_random(0, 6);

	//�����������
	animation_loose.set_inerval(0.5f);
	animation_loose.set_loop(true);
	animation_loose.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_loose.add_frame(ResourcesManager::Instance()->find_atlas("barb_loose"));

	//�������鶯��
	animation_break.set_inerval(0.1f);
	animation_break.set_loop(false);
	animation_break.set_anchor_mode(Animation::AnchorMode::Centered);
	animation_break.add_frame(ResourcesManager::Instance()->find_atlas("barb_break"));
	animation_break.set_on_finished([&]() {is_valid = false; });

	collision_box = CollisionManager::Instance()->create_collision_box();
	collision_box->set_layer_src(CollisionLayer::Enemy);
	collision_box->set_layer_dst(CollisionLayer::Player);
	collision_box->set_size({ 20,20 });
	collision_box->set_on_collide([&]() {on_break(); });

	timer_idle.set_wait_time((float)range_random(3, 10));
	timer_idle.set_one_shot(true);
	timer_idle.set_on_timeout([&]()
		{
			if (stage == Stage::Idle)
			{
				stage = Stage::Aim;
				base_position = current_position;
			}
		});

	timer_aim.set_wait_time(0.75f);
	timer_aim.set_one_shot(true);
	timer_aim.set_on_timeout([&]()
		{
			if (stage == Stage::Aim)
			{
				stage = Stage::Dash;
				const Vector2& pos_player = CharacterManager::Instance()->get_player()->get_position();
				velocity = (pos_player - current_position).normalized() * SPEED_DASH;
			}
		});
}

Barb::~Barb()
{
	CollisionManager::Instance()->destroy_collision_box(collision_box);
}

void Barb::on_update(float delta)
{
	//���¶�ʱ���߼�
	if(stage == Stage::Idle)
		timer_idle.on_update(delta);
	if (stage == Stage::Aim)
		timer_aim.on_update(delta);

	//�����ƶ��߼�
	total_delta_time += delta;
	switch (stage)
	{
	case Barb::Stage::Idle:
		current_position.y = base_position.y + sin(total_delta_time * 2.0f + diff_peeriod) * 30;
		break;
	case Barb::Stage::Aim:
		current_position.x = base_position.x + range_random(-10, 10);
		break;
	case Barb::Stage::Dash:
		current_position += velocity * delta;
		if(current_position.y>=CharacterManager::Instance()->get_player()->get_floor_y())
			on_break();
		if(current_position.y<=0)
			is_valid = false;
		break;
	}
	collision_box->set_position(current_position);

	//���¶����߼�
	current_animation = (stage == Stage::Break ? &animation_break : &animation_loose);
	current_animation->set_position(current_position);
	current_animation->on_update(delta);
}

void Barb::on_render()
{
	current_animation->on_render();
}

void Barb::on_break()
{
	if (stage == Stage::Break)  return;

	stage = Stage::Break;
	collision_box->set_enabled(false);
	play_audio(_T("barb_break"), false);
}