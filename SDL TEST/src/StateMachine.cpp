#include "StateMachine.h"

StateMachine::StateMachine(const std::string& defaultState)
	: m_DefaultState(defaultState),
	m_CurrentState(defaultState)
{

}

StateMachine::~StateMachine()
{
}

void StateMachine::AddTransition(const std::string & from, const std::string & to)
{
	m_Transitions.push_back({from, to});
}

bool StateMachine::TransitionTo(const std::string & targetState)
{
	/*returns true if valid, false otherwise*/
	if (m_CurrentState == targetState) return true;
	for (StateTransition st : m_Transitions)
	{
		if (st.from == m_CurrentState && st.to == targetState)
		{
			m_CurrentState = targetState;
			return true;
		}
	}

	return false;
}

bool StateMachine::HasTransition(const std::string & fromState, const std::string & targetState) const
{
	if (fromState == targetState) true;
	for (StateTransition st : m_Transitions)
	{
		if (st.from == fromState && st.to == targetState)
		{
			return true;
		}
	}

	return false;
}
