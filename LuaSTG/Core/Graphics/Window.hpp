﻿#pragma once
#include "Core/Type.hpp"

namespace Core::Graphics
{
	struct IWindowEventListener
	{
		virtual void onWindowCreate() {};
		virtual void onWindowDestroy() {};

		virtual void onWindowActive() {};
		virtual void onWindowInactive() {};

		virtual void onWindowSize(Vector2U size) { (void)size; };
		virtual void onWindowFullscreenStateChange(bool state) { (void)state; }
		virtual void onWindowDpiChange() {};

		virtual void onWindowClose() {};

		virtual void onDeviceChange() {};

		struct NativeWindowMessageResult
		{
			intptr_t result;
			bool should_return;

			NativeWindowMessageResult() : result(0), should_return(false) {}
			NativeWindowMessageResult(intptr_t v, bool b) : result(v), should_return(b) {}
		};

		virtual NativeWindowMessageResult onNativeWindowMessage(void*, uint32_t, uintptr_t, intptr_t) { return {}; };
	};

	enum class WindowFrameStyle
	{
		None,
		Fixed,
		Normal,
	};

	enum class WindowLayer
	{
		Unknown,
		Invisible,
		Bottom,
		Normal,
		Top,
		TopMost,
	};

	enum class WindowCursor
	{
		None,

		Arrow,
		Hand,

		Cross,
		TextInput,

		Resize,
		ResizeEW,
		ResizeNS,
		ResizeNESW,
		ResizeNWSE,

		NotAllowed,
		Wait,
	};

	struct IWindow : public IObject
	{
		virtual void addEventListener(IWindowEventListener* e) = 0;
		virtual void removeEventListener(IWindowEventListener* e) = 0;

		virtual void* getNativeHandle() = 0;
		virtual void setNativeIcon(void* id) = 0;

		virtual void setIMEState(bool enable) = 0;
		virtual bool getIMEState() = 0;

		virtual void setTitleText(StringView str) = 0;
		virtual StringView getTitleText() = 0;

		virtual bool setFrameStyle(WindowFrameStyle style) = 0;
		virtual WindowFrameStyle getFrameStyle() = 0;

		virtual Vector2U getSize() = 0;
		virtual bool setSize(Vector2U v) = 0;

		virtual WindowLayer getLayer() = 0;
		virtual bool setLayer(WindowLayer layer) = 0;

		virtual uint32_t getDPI() = 0;
		virtual float getDPIScaling() = 0;

		virtual void setWindowMode(Vector2U size) = 0;
		virtual void setExclusiveFullScreenMode() = 0;
		virtual void setBorderlessFullScreenMode() = 0;

		virtual uint32_t getMonitorCount() = 0;
		virtual RectI getMonitorRect(uint32_t index) = 0;
		virtual void setMonitorCentered(uint32_t index) = 0;
		virtual void setMonitorFullScreen(uint32_t index) = 0;

		virtual void setCustomSizeMoveEnable(bool v) = 0;
		virtual void setCustomMinimizeButtonRect(RectI v) = 0;
		virtual void setCustomCloseButtonRect(RectI v) = 0;
		virtual void setCustomMoveButtonRect(RectI v) = 0;

		virtual bool setCursor(WindowCursor type) = 0;
		virtual WindowCursor getCursor() = 0;

		// Windows 11
		virtual void setWindowCornerPreference(bool allow) = 0;

		static bool create(IWindow** pp_window);
		static bool create(Vector2U size, StringView title_text, WindowFrameStyle style, bool show, IWindow** pp_window);
	};
}
