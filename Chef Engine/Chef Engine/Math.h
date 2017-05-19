#pragma once

namespace ce
{
	class Math
	{
	public:
		Math();
		~Math();

		static float ClampF(float value, float maxValue, float minValue);
		static int ClampI(int value, int maxValue, int minValue);
	};
}

