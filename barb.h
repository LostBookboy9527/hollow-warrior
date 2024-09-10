#ifndef _BARB_H_
#define _BARB_H_

#include "animation.h"
#include "collision_box.h"

class Barb
{
public:
    Barb();
    ~Barb();

    void on_update(float delta);
    void on_render();

    void set_position(const Vector2& position)
    {
        this->base_position = position;
        this->current_position = position;
    }

    bool check_valid() const
    {
        return is_valid;
    }

private:
    enum class Stage
    {
        Idle,
        Aim,
        Dash,
        Break
    };

private:
    const float SPEED_DASH = 1500.0f;

    Timer timer_idle;
    Timer timer_aim;
    int diff_peeriod = 0;//����������ƴ��򸡶����˶�����ƫ��
    bool is_valid = true;
    float total_delta_time = 0.0f;//������������������ʱ��

    Vector2 velocity;
    Vector2 base_position;//�����ʼλ��
    Vector2 current_position;//����ǰλ��

    Animation animation_loose;
    Animation animation_break;
    Animation* current_animation = nullptr;

    Stage stage = Stage::Idle;
    CollisionBox* collision_box = nullptr;

private:
    void on_break();
};

#endif // !_BARB_H_
