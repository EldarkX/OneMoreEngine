#pragma once

class Subsystem
{
public:
					Subsystem() = default;

	virtual bool	Initialize() = 0;
	virtual void	Terminate() = 0;

	virtual			~Subsystem() {}
};