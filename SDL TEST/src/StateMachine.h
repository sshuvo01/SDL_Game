#pragma once
#include <iostream>
#include <vector>

struct StateTransition
{
	/*one way*/
	std::string from;
	std::string to;
};

class StateMachine
{
public:
	StateMachine(const std::string& defaultState);
	~StateMachine();

	void AddTransition(const std::string& from, const std::string& to);
	bool TransitionTo(const std::string& targetState);
	bool HasTransition(const std::string& fromState, const std::string& targetState) const;
	inline std::string GetCurrentState() const { return m_CurrentState; }
private:
	std::vector<StateTransition>		m_Transitions;
	std::string							m_CurrentState;
	std::string							m_DefaultState;
};
