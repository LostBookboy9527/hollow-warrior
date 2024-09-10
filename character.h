#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "vector2.h"
#include "animation.h"
#include "collision_box.h"
#include "state_machine.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class Character
{
public:
    Character();
    ~Character();

    void decrease_hp();
    int get_hp()const
    {
        return hp;
    }
    void set_position(const Vector2& posistion)
    {
        this->position = posistion;
    }
    const Vector2& get_position()const
    {
        return position;
    }
    void set_velocity(const Vector2& velocity)
    {
        this->velocity = velocity;
    }
    const Vector2& get_velocity()const
    {
        return velocity;
    }
    Vector2 get_logic_center()const
    {
        return Vector2(position.x, position.y - logic_height / 2);
    }
    void set_gravity_enabled(bool flag)
    {
        enable_gravity = flag;
    }
    CollisionBox* get_hit_box()
    {
        return hit_box;
    }
    CollisionBox* get_hurt_box()
    {
        return hurt_box;
    }
    bool is_on_floor()const
    {
        return position.y >= FLOOR_Y;
    }
    float get_floor_y()const
    {
        return FLOOR_Y;
    }
    void make_invulnerable()
    {
        is_invulnerable = true;
        timer_invulnerable_status.restart();
    }

    virtual void on_input(const ExMessage& msg);
    virtual void on_update(float delta);
    virtual void on_render();

    virtual void on_hurt();

    void switch_state(const std::string& id);
    void set_animation(const std::string& id);

protected:
    struct AnimationGroup
    {
        Animation left;
        Animation right;
    };

protected:
    const float FLOOR_Y = 620;//�ذ����ֱ��������
    const float GRAVITY = 980 * 2;//������С

    int hp = 10;//��ɫѪ��
    Vector2 position;//��ɫ�ŵ�λ��
    Vector2 velocity;//��ɫ�ٶ�
    float logic_height = 0;//��ɫ�߼��߶�
    bool is_facing_left = true;//��ɫ����
    StateMachine state_machine;//��ɫ�߼�״̬��
    bool enable_gravity = true;//�Ƿ���������ģ��
    bool is_invulnerable = false;//��ǰ�Ƿ��޵�
    Timer timer_invulnerable_blink;//�޵���˸��Ч��ʱ��
    Timer timer_invulnerable_status;//�޵�״̬��ʱ��
    bool is_blink_invisible = false;//��ǰ�Ƿ�����˸�Ĳ��ɼ�֡
    CollisionBox* hit_box = nullptr;//��ɫ������ײ��
    CollisionBox* hurt_box = nullptr;//��ɫ�ܻ���ײ��
    AnimationGroup* current_animation = nullptr;//��ǰ��ɫ����
    std::unordered_map<std::string, AnimationGroup> animation_pool;//��ɫ������
};


#endif // !_CHARACTER_H_

