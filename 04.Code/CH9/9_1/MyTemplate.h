#pragma once

// ģ�庯��-����ֵ
template<typename T>
T Abs(T val)
{
	return (val<0 ? -val : val);
}

// ģ�庯������
int Abs(int val)
{
	return (val>0 ? val : -val);
}

