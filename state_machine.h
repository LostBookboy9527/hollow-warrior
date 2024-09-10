#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state_node.h"

#include <string>
#include <graphics.h>
#include <unordered_map>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();

	void on_update(float delta);

	void set_entry(const std::string& id);
	void switch_to(const std::string& id);
	void register_state(const std::string& id, StateNode* state_node);

private:
	bool need_init = true;//是否需要进行初始化进入
	StateNode* current_state = nullptr;//当前激活的状态节点
	std::unordered_map<std::string, StateNode*> state_pool;
};


#endif // _STATE_MACHINE_H_
