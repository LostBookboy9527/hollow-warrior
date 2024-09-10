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
    int diff_peeriod = 0;//随机数，控制刺球浮动的运动周期偏移
    bool is_valid = true;
    float total_delta_time = 0.0f;//刺球生成以来经过的时间

    Vector2 velocity;
    Vector2 base_position;//刺球初始位置
    Vector2 current_position;//刺球当前位置

    Animation animation_loose;
    Animation animation_break;
    Animation* current_animation = nullptr;

    Stage stage = Stage::Idle;
    CollisionBox* collision_box = nullptr;

private:
    void on_break();
};

#endif // !_BARB_H_
