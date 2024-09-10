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
	float progress = 0;//0.0f - 1.0f, 0����û���ӵ�ʱ��Ч��, 1������ȫ�����ӵ�ʱ��
	Status status = Status::Exiting;
	const float SPEED_PROGRESS = 2.0f;//������˳��ӵ�ʱ��ʱ��ÿ���ٶ�
	const float DST_DELTA_FACTOR = 0.3f;//�����ӵ�ʱ���֡����ʱ������ű���
	const float DST_COLOR_FACTOR = 0.5f;//�����ӵ�ʱ��󣬻���ɫ�ʱ仯�����ű���

private:
	BulletTimeManager();
	~BulletTimeManager();

	float lerp(float start, float end, float t)//���Բ�ֵ
	{
		return (1 - t) * start + t * end;
	}
};


#endif // !_BULLET_TIME_MANAGER_H_
