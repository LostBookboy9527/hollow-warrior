#include "util.h"
#include "collision_manager.h"
#include "character_manager.h"
#include "resources_manager.h"
#include "bullet_time_manager.h"


#include <chrono>
#include <thread>
#include <graphics.h>

static void draw_background()
{
	static IMAGE* img_background = ResourcesManager::Instance()->find_image("background");
	static Rect rect_dst =
	{
		(getwidth() - img_background->getwidth()) / 2,
		(getheight() - img_background->getheight()) / 2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}


int main(int argc, char** argv)
{
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("�ն���ʿ"));

	//��ʼ����Դ������
	try
	{
		ResourcesManager::Instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("��Դ����ʧ��: %s"), id);
		MessageBox(hwnd, err_msg, _T("��Դ����ʧ��"), MB_OK | MB_ICONERROR);

		return -1;
	}

	const std::chrono::nanoseconds frame_duration(1000000000 / 144);
	std::chrono::steady_clock::time_point last_tick = std::chrono::steady_clock::now();


	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit)
	{
		while (peekmessage(&msg))
			CharacterManager::Instance()->on_input(msg);
		
		std::chrono::steady_clock::time_point frame_start = std::chrono::steady_clock::now();
		std::chrono::duration<float> delta = std::chrono::duration<float>(frame_start - last_tick);

		//�������
		float scaled_delta = BulletTimeManager::Instance()->on_update(delta.count());
		CharacterManager::Instance()->on_update(scaled_delta);
		CollisionManager::Instance()->process_collide();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		//�������
		draw_background();
		CharacterManager::Instance()->on_render();
		CollisionManager::Instance()->on_debug_render();

		FlushBatchDraw();

		last_tick = frame_start;
		std::chrono::nanoseconds sleep_duration = frame_duration - (std::chrono::steady_clock::now() - frame_start);
		if(sleep_duration > std::chrono::nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
	}

	EndBatchDraw();
	return 0;
}