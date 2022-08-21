#pragma once

namespace fbr
{
	struct InputEvent
	{
		enum class Type : unsigned int 
		{
			KEY = 0,
			MOUSE_WHEEL, MOUSE_POSITION, MOUSE_CLICK
		};

		Type type;
		
		union InputData
		{
			int position[2];
			int delta;
			int keyCode;
		};

		InputData data;
	};
}