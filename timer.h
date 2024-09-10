#ifndef TIMER_H
#define TIMER_H

#include <functional>

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    void restart()
    {
        pass_time = 0.0f;
        shotted = false;
    }
    void set_wait_time(float val)
    {
        wait_time = val;
    }
    void set_one_shot(bool flag)
    {
        one_shot = flag;
    }
    void set_on_timeout(std::function<void()> on_timeout)
    {
        this->on_timeout = on_timeout;
    }
    void pause()
    {
        paused = true;
    }
    void resume()
    {
        paused = false;
    }
    void on_update(float delta_time)
    {
        if (paused)
            return;

        pass_time += delta_time;
        if (pass_time >= wait_time)
        {
            bool can_shot = (!one_shot || (one_shot && !shotted));
            shotted = true;
            if (can_shot && on_timeout)
                on_timeout();
            pass_time -= wait_time;// 修正计时器时间
        }
    }

private:
    float pass_time = 0.0f;
    float wait_time = 0.0f;
    bool paused = false;//是否暂停
    bool shotted = false;//是否已经触发过
    bool one_shot = false;//是否是一次性触发
    std::function<void()> on_timeout;

};

#endif // TIMER_H  
