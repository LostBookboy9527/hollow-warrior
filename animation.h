#include "util.h"
#include "timer.h"
#include "atlas.h"
#include "vector2.h"

#include <vector>
#include <functional>

class Animation 
{
public:
	enum class AnchorMode
	{
		Centered,
		BottomCentered
	};
	Animation()
	{
		timer.set_one_shot(false);
		timer.set_on_timeout(
			[&]()
			{
				idx_frame++;
				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;//如果是循环播放，则回到第一帧，否则停在最后一帧
					if (!is_loop && on_finished)//如果不是循环播放，并且已定义on_finished，则调用on_finished
						on_finished();
				}
			}
		);
	}
	~Animation()
	{

	}

	void reset()
	{
		timer.restart();
		idx_frame = 0;
	}

	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	void set_position(const Vector2& position)
	{
		this->position = position;
	}

	void set_loop(bool is_loop)
	{
		this->is_loop = is_loop;
	}

	void set_inerval(float interval)
	{
		timer.set_wait_time(interval);
	}

	void set_on_finished(const std::function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}

	void add_frame(IMAGE* image, int num_h)//添加一帧，参数image为当前帧使用的IMAGE对象，num_h为当前帧的行数
	{
		int width = image->getwidth();
		int height = image->getheight();
		int width_frame = width / num_h;

		for (int i = 0; i < num_h; ++i)
		{
			Rect rect_src;
			rect_src.x = i * width_frame,rect_src.y = 0, rect_src.w = width_frame, rect_src.h = height;
			frame_list.emplace_back(image, rect_src);
		}
	}
	void add_frame(Atlas* atlas)//添加一帧，参数atlas为当前帧使用的Atlas对象
	{
		for (int i = 0; i < atlas->get_size(); ++i)
		{
			IMAGE* image = atlas->get_image(i);
			int width = image->getwidth();
			int height = image->getheight();
			
			Rect rect_src;
			rect_src.x = 0, rect_src.y = 0;
			rect_src.w = width, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}
	}

	void on_update(float delta)
	{
		timer.on_update(delta);
	}

	void on_render()
	{
		const Frame& frame = frame_list[idx_frame];

		Rect rect_dst;
		rect_dst.x = (int)position.x - frame.rect_src.w / 2;
		rect_dst.y = (anchor_mode == AnchorMode::Centered ? (int)position.y - frame.rect_src.h / 2 : (int)position.y - frame.rect_src.h);
		rect_dst.w = frame.rect_src.w;
		rect_dst.h = frame.rect_src.h;

		//printf("animation on_render\n");
		putimage_ex(frame.image, &rect_dst, &frame.rect_src);
	}

private:
	struct Frame//Frame对象记录当前帧使用的IMAGE对象以及从该对象上裁剪的区域信息
	{
		Rect rect_src;
		IMAGE* image = nullptr;

		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src):image(image), rect_src(rect_src)
		{

		}
		~Frame() = default;
	};
private:
	Timer timer;//控制动画播放
	Vector2 position;//标记动画在窗口中的渲染位置
	bool is_loop = true;//是否循环播放
	size_t idx_frame = 0;//当前播放的帧索引
	std::vector<Frame> frame_list;//所有帧信息
	std::function<void()> on_finished;//动画播放完毕后处理逻辑的回调函数
	AnchorMode anchor_mode = AnchorMode::Centered;

};