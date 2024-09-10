#ifndef _BULLET_TIME_MANAGER_H_
#define _BULLET_TIME_MANAGER_H_

class BulletTimeManager
{
public:
	enum class Status
	{
		Entering,
		Exiting
	};
public:
	static BulletTimeManager* Instance();

	void post_process();
	void set_status(Status status);

	float on_update(float delta);

private:
	static BulletTimeManager* manager;

private:
	float progress = 0;//0.0f - 1.0f, 0代表没有子弹时间效果, 1代表完全进入子弹时间
	Status status = Status::Exiting;
	const float SPEED_PROGRESS = 2.0f;//进入和退出子弹时间时，每秒速度
	const float DST_DELTA_FACTOR = 0.3f;//进入子弹时间后，帧更新时间的缩放比例
	const float DST_COLOR_FACTOR = 0.5f;//进入子弹时间后，画面色彩变化的缩放比例

private:
	BulletTimeManager();
	~BulletTimeManager();

	float lerp(float start, float end, float t)//线性插值
	{
		return (1 - t) * start + t * end;
	}
};


#endif // !_BULLET_TIME_MANAGER_H_
