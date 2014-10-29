#pragma once

class Trigger
{
public:
	int getType()
	{
		return m_Type;
	}
	virtual bool operator ==( Trigger& trigger ) = 0;
protected:
	int m_Type;
};