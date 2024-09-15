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

void draw_remain_hp()
{
	static IMAGE* img_ui_heart = ResourcesManager::Instance()->find_image("ui_heart");
	Rect rect_dst = { 0, 10, img_ui_heart->getwidth(), img_ui_heart->getheight() };
	for (int i = 0; i < CharacterManager::Instance()->get_player()->get_hp(); i++)
	{
		rect_dst.x = 10 + i * 40;
		putimage_ex(img_ui_heart, &rect_dst);
	}
}

int main(int argc, char** argv)
{
	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("空洞武士"));

	//初始化资源管理器
	try
	{
		ResourcesManager::Instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("资源加载失败: %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);

		return -1;
	}

	play_audio(_T("bgm"), true);

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

		//处理更新
		float scaled_delta = BulletTimeManager::Instance()->on_update(delta.count());
		CharacterManager::Instance()->on_update(scaled_delta);
		CollisionManager::Instance()->process_collide();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		//处理绘制
		draw_background();
		CharacterManager::Instance()->on_render();
		CollisionManager::Instance()->on_debug_render();
		draw_remain_hp();

		FlushBatchDraw();

		last_tick = frame_start;
		std::chrono::nanoseconds sleep_duration = frame_duration - (std::chrono::steady_clock::now() - frame_start);
		if(sleep_duration > std::chrono::nanoseconds(0))
			std::this_thread::sleep_for(sleep_duration);
	}

	EndBatchDraw();
	return 0;
}