#include "GUI.h"






// ========================================================
// |             #IMGUI #CONTROLS #KEYBINDINGS            |
// ========================================================
void ImGui::TextBool(const char* label, const bool& inBool, const char* text_true, const char* text_false, const bool& useColoring, const ImU32& color_true, const ImU32& color_false)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, inBool ? color_true : color_false);
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));
		ImGui::PopStyleColor();
	}
	else
		ImGui::TextUnformatted(inBool
			? (text_true ? text_true : "True")
			: (text_false ? text_false : "False"));

}

void ImGui::TextBool(const char* label, const bool& inBool)
{
	TextBool(label, inBool, "True", "False", false, ImU32(), ImU32());
}

void ImGui::TextBoolColored(const char* label, const bool& status)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, status, "True", "False", true, color_true, color_false);
}

void ImGui::TextBoolPresence(const char* label, const bool& presence)
{
	TextBool(label, presence, "Is Present", "Doesn't Exist!", false, ImU32(), ImU32());
}

void ImGui::TextBoolPresenceColored(const char* label, const bool& presence)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, presence, "Is Present", "Doesn't Exist!", true, color_true, color_false);
}

void ImGui::TextBoolMultiplePresence(const char* label, const bool& presence)
{
	TextBool(label, presence, "Are Present", "Are Non Existent!", false, ImU32(), ImU32());
}

void ImGui::TextBoolMultiplePresenceColored(const char* label, const bool& presence)
{
	static const ImU32 color_true = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_false = IM_COL32(204, 77, 51, 255);

	TextBool(label, presence, "Are Present", "Are Non Existent!", true, color_true, color_false);
}




void ImGui::TextFloat(const char* label, const float& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0.0f)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%f", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%f", value);
}

void ImGui::TextFloat(const char* label, const float& value)
{
	TextFloat(label, value, false, ImU32(), ImU32());
}

void ImGui::TextFloatColored(const char* label, const float& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextFloat(label, value, true, color_positive, color_negative);
}




void ImGui::TextInt(const char* label, const int32_t& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	if (useColoring && value != 0)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, value > 0.0f ? color_positive : color_negative);
		ImGui::Text("%d", value);
		ImGui::PopStyleColor();;
	}
	else
		ImGui::Text("%d", value);
}

void ImGui::TextInt(const char* label, const int32_t& value)
{
	TextInt(label, value, false, ImU32(), ImU32());
}

void ImGui::TextIntColored(const char* label, const int32_t& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextInt(label, value, true, color_positive, color_negative);
}




void ImGui::TextVector(const char* label, const SDK::FVector& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"X:",
		"Y:",
		"Z:"
	};

	const double coords[3]
	{
		value.X,
		value.Y,
		value.Z
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = coords[i] > -0.0000001 && coords[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, coords[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%f", neutralValue ? 0.0 : coords[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
}

void ImGui::TextVector(const char* label, const SDK::FVector& value)
{
	TextVector(label, value, false, ImU32(), ImU32());
}

void ImGui::TextVectorColored(const char* label, const SDK::FVector& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextVector(label, value, true, color_positive, color_negative);
}




void ImGui::TextRotator(const char* label, const SDK::FRotator& value, const bool& useColoring, const ImU32& color_positive, const ImU32& color_negative)
{
	constexpr ImU32 axis_colors[3]
	{
		IM_COL32(255, 0, 0, 255),
		IM_COL32(0, 255, 0, 255),
		IM_COL32(0, 0, 255, 255)
	};

	constexpr const char* axis_prefixes[3]
	{
		"Pitch:",
		"Yaw:",
		"Roll:"
	};

	const double angles[3]
	{
		value.Pitch,
		value.Yaw,
		value.Roll
	};

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	for (int i = 0; i < 3; i++)
	{
		if (useColoring) ImGui::PushStyleColor(ImGuiCol_Text, axis_colors[i]);
		ImGui::SetFontBig();
		ImGui::TextUnformatted(axis_prefixes[i]);
		ImGui::SetFontRegular();
		if (useColoring) ImGui::PopStyleColor();

		ImGui::SameLine();

		bool neutralValue = angles[i] > -0.0000001 && angles[i] < 0.0000001;
		if (useColoring && !neutralValue) ImGui::PushStyleColor(ImGuiCol_Text, angles[i] > 0.0 ? color_positive : color_negative);
		ImGui::Text("%f", neutralValue ? 0.0 : angles[i]);
		if (useColoring && !neutralValue) ImGui::PopStyleColor();

		if (i != 2)
		{
			ImGui::SameLine();
			ImGui::Spacing();
			ImGui::SameLine();
		}
	}
}

void ImGui::TextRotator(const char* label, const SDK::FRotator& value)
{
	TextRotator(label, value, false, ImU32(), ImU32());
}

void ImGui::TextRotatorColored(const char* label, const SDK::FRotator& value)
{
	static const ImU32 color_positive = IM_COL32(51, 204, 77, 255);
	static const ImU32 color_negative = IM_COL32(204, 77, 51, 255);

	TextRotator(label, value, true, color_positive, color_negative);
}




void ImGui::TextHint(const char* hint)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::TextUnformatted(hint);
		ImGui::EndTooltip();
	}
}




void ImGui::ReadOnlyInputText(const char* label, const char* text, const bool& showCopyButton)
{
	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : (text ? text : "ReadOnlyInputText"));
	const size_t length = text ? strlen(text) : 0;

	static std::vector<char> buffer;
	buffer.clear();

	if (text && length)
		buffer.insert(buffer.end(), text, text + length);
	buffer.push_back('\0');

	ImGui::InputText("##ReadOnlyInputText", buffer.data(), buffer.size(), ImGuiInputTextFlags_ReadOnly);
	if (showCopyButton)
	{
		ImGui::SameLine();
		if (ImGui::Button("Copy"))
		{
			Clipboard::SetClipboard(buffer.data());
			GUI::PlayActionSound(true);
		}
	}

	ImGui::PopID();
}




void ImGui::ObjectFilterModeComboBox(const char* label, E_ObjectFilterMode* v)
{
	ImGui::PushID(label);

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	static const char* items[] = { "Class Name", "Object Name", "All" };
	int index = static_cast<int>(*v);

	ImGui::SetNextItemWidth(200);
	if (ImGui::Combo("##object_filter_combo", &index, items, IM_ARRAYSIZE(items))) 
	{
		*v = static_cast<E_ObjectFilterMode>(index);
	}

	ImGui::PopID();
}




int ImGui::ImGuiKey_ToWinAPI(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab: return VK_TAB;
		case ImGuiKey_LeftArrow: return VK_LEFT;
		case ImGuiKey_RightArrow: return VK_RIGHT;
		case ImGuiKey_UpArrow: return VK_UP;
		case ImGuiKey_DownArrow: return VK_DOWN;
		case ImGuiKey_PageUp: return VK_PRIOR;
		case ImGuiKey_PageDown: return VK_NEXT;
		case ImGuiKey_Home: return VK_HOME;
		case ImGuiKey_End: return VK_END;
		case ImGuiKey_Insert: return VK_INSERT;
		case ImGuiKey_Delete: return VK_DELETE;
		case ImGuiKey_Backspace: return VK_BACK;
		case ImGuiKey_Space: return VK_SPACE;
		case ImGuiKey_Enter: return VK_RETURN;
		case ImGuiKey_Escape: return VK_ESCAPE;

		case ImGuiKey_A: return 'A'; case ImGuiKey_B: return 'B';
		case ImGuiKey_C: return 'C'; case ImGuiKey_D: return 'D';
		case ImGuiKey_E: return 'E'; case ImGuiKey_F: return 'F';
		case ImGuiKey_G: return 'G'; case ImGuiKey_H: return 'H';
		case ImGuiKey_I: return 'I'; case ImGuiKey_J: return 'J';
		case ImGuiKey_K: return 'K'; case ImGuiKey_L: return 'L';
		case ImGuiKey_M: return 'M'; case ImGuiKey_N: return 'N';
		case ImGuiKey_O: return 'O'; case ImGuiKey_P: return 'P';
		case ImGuiKey_Q: return 'Q'; case ImGuiKey_R: return 'R';
		case ImGuiKey_S: return 'S'; case ImGuiKey_T: return 'T';
		case ImGuiKey_U: return 'U'; case ImGuiKey_V: return 'V';
		case ImGuiKey_W: return 'W'; case ImGuiKey_X: return 'X';
		case ImGuiKey_Y: return 'Y'; case ImGuiKey_Z: return 'Z';

		case ImGuiKey_0: return '0'; case ImGuiKey_1: return '1';
		case ImGuiKey_2: return '2'; case ImGuiKey_3: return '3';
		case ImGuiKey_4: return '4'; case ImGuiKey_5: return '5';
		case ImGuiKey_6: return '6'; case ImGuiKey_7: return '7';
		case ImGuiKey_8: return '8'; case ImGuiKey_9: return '9';

		case ImGuiKey_Keypad0: return VK_NUMPAD0;
		case ImGuiKey_Keypad1: return VK_NUMPAD1;
		case ImGuiKey_Keypad2: return VK_NUMPAD2;
		case ImGuiKey_Keypad3: return VK_NUMPAD3;
		case ImGuiKey_Keypad4: return VK_NUMPAD4;
		case ImGuiKey_Keypad5: return VK_NUMPAD5;
		case ImGuiKey_Keypad6: return VK_NUMPAD6;
		case ImGuiKey_Keypad7: return VK_NUMPAD7;
		case ImGuiKey_Keypad8: return VK_NUMPAD8;
		case ImGuiKey_Keypad9: return VK_NUMPAD9;
		case ImGuiKey_KeypadMultiply: return VK_MULTIPLY;
		case ImGuiKey_KeypadAdd: return VK_ADD;
		case ImGuiKey_KeypadSubtract: return VK_SUBTRACT;
		case ImGuiKey_KeypadDecimal: return VK_DECIMAL;
		case ImGuiKey_KeypadDivide: return VK_DIVIDE;

		case ImGuiKey_F1: return VK_F1; case ImGuiKey_F2: return VK_F2;
		case ImGuiKey_F3: return VK_F3; case ImGuiKey_F4: return VK_F4;
		case ImGuiKey_F5: return VK_F5; case ImGuiKey_F6: return VK_F6;
		case ImGuiKey_F7: return VK_F7; case ImGuiKey_F8: return VK_F8;
		case ImGuiKey_F9: return VK_F9; case ImGuiKey_F10: return VK_F10;
		case ImGuiKey_F11: return VK_F11; case ImGuiKey_F12: return VK_F12;

		case ImGuiKey_LeftCtrl: return VK_LCONTROL;
		case ImGuiKey_RightCtrl: return VK_RCONTROL;
		case ImGuiKey_LeftShift: return VK_LSHIFT;
		case ImGuiKey_RightShift: return VK_RSHIFT;
		/* Left Alt recognition was disabled due to glitch with ALT + TABbing. */
		// case ImGuiKey_LeftAlt: return VK_LMENU;
		case ImGuiKey_RightAlt: return VK_RMENU;
		case ImGuiKey_LeftSuper: return VK_LWIN;
		case ImGuiKey_RightSuper: return VK_RWIN;

		default: return 0;
	}
}

const char* ImGui::ImGuiKey_GetName(const ImGuiKey& key)
{
	switch (key)
	{
		case ImGuiKey_Tab:            return "Tab";
		case ImGuiKey_LeftArrow:      return "Left";
		case ImGuiKey_RightArrow:     return "Right";
		case ImGuiKey_UpArrow:        return "Up";
		case ImGuiKey_DownArrow:      return "Down";
		case ImGuiKey_PageUp:         return "PgUp";
		case ImGuiKey_PageDown:       return "PgDn";
		case ImGuiKey_Home:           return "Home";
		case ImGuiKey_End:            return "End";
		case ImGuiKey_Insert:         return "Ins";
		case ImGuiKey_Delete:         return "Del";
		case ImGuiKey_Backspace:      return "Bspace";
		case ImGuiKey_Space:          return "Space";
		case ImGuiKey_Enter:          return "Enter";
		case ImGuiKey_Escape:         return "Esc";

		case ImGuiKey_A: return "A";  case ImGuiKey_B: return "B";
		case ImGuiKey_C: return "C";  case ImGuiKey_D: return "D";
		case ImGuiKey_E: return "E";  case ImGuiKey_F: return "F";
		case ImGuiKey_G: return "G";  case ImGuiKey_H: return "H";
		case ImGuiKey_I: return "I";  case ImGuiKey_J: return "J";
		case ImGuiKey_K: return "K";  case ImGuiKey_L: return "L";
		case ImGuiKey_M: return "M";  case ImGuiKey_N: return "N";
		case ImGuiKey_O: return "O";  case ImGuiKey_P: return "P";
		case ImGuiKey_Q: return "Q";  case ImGuiKey_R: return "R";
		case ImGuiKey_S: return "S";  case ImGuiKey_T: return "T";
		case ImGuiKey_U: return "U";  case ImGuiKey_V: return "V";
		case ImGuiKey_W: return "W";  case ImGuiKey_X: return "X";
		case ImGuiKey_Y: return "Y";  case ImGuiKey_Z: return "Z";

		case ImGuiKey_0: return "0";  case ImGuiKey_1: return "1";
		case ImGuiKey_2: return "2";  case ImGuiKey_3: return "3";
		case ImGuiKey_4: return "4";  case ImGuiKey_5: return "5";
		case ImGuiKey_6: return "6";  case ImGuiKey_7: return "7";
		case ImGuiKey_8: return "8";  case ImGuiKey_9: return "9";

		case ImGuiKey_Keypad0:        return "Num0";
		case ImGuiKey_Keypad1:        return "Num1";
		case ImGuiKey_Keypad2:        return "Num2";
		case ImGuiKey_Keypad3:        return "Num3";
		case ImGuiKey_Keypad4:        return "Num4";
		case ImGuiKey_Keypad5:        return "Num5";
		case ImGuiKey_Keypad6:        return "Num6";
		case ImGuiKey_Keypad7:        return "Num7";
		case ImGuiKey_Keypad8:        return "Num8";
		case ImGuiKey_Keypad9:        return "Num9";
		case ImGuiKey_KeypadMultiply: return "Num*";
		case ImGuiKey_KeypadAdd:      return "Num+";
		case ImGuiKey_KeypadSubtract: return "Num-";
		case ImGuiKey_KeypadDecimal:  return "Num.";
		case ImGuiKey_KeypadDivide:   return "Num/";

		case ImGuiKey_F1:  return "F1";   case ImGuiKey_F2:  return "F2";
		case ImGuiKey_F3:  return "F3";   case ImGuiKey_F4:  return "F4";
		case ImGuiKey_F5:  return "F5";   case ImGuiKey_F6:  return "F6";
		case ImGuiKey_F7:  return "F7";   case ImGuiKey_F8:  return "F8";
		case ImGuiKey_F9:  return "F9";   case ImGuiKey_F10: return "F10";
		case ImGuiKey_F11: return "F11";  case ImGuiKey_F12: return "F12";

		case ImGuiKey_LeftCtrl:   return "LCtrl";
		case ImGuiKey_RightCtrl:  return "RCtrl";
		case ImGuiKey_LeftShift:  return "LShift";
		case ImGuiKey_RightShift: return "RShift";
		case ImGuiKey_LeftAlt:    return "LAlt";
		case ImGuiKey_RightAlt:   return "RAlt";
		case ImGuiKey_LeftSuper:  return "LWin";
		case ImGuiKey_RightSuper: return "RWin";

		default: return "???";
	}
}




bool ImGui::KeyBindingInput(const char* label, KeyBinding* binding)
{
	if (!binding)
		return false;

	if (label)
	{
		const char* idPosition = std::strstr(label, "##");
		if (idPosition)
			ImGui::TextUnformatted(label, idPosition);
		else
			ImGui::TextUnformatted(label);

		ImGui::SameLine();
	}

	ImGui::PushID(label ? label : "KeyBindingInput");

	SameLine();

	/* 0 corresponds for default vertical size. */
	static const ImVec2 buttonSize = { 96.0f, 0.0f };

	static const ImVec4 buttonColor = { 0.20f, 0.50f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_unbound = { 0.50f, 0.20f, 0.20f, 1.00f };
	static const ImVec4 buttonColor_capturing = { 0.25f, 0.25f, 0.25f, 1.00f };

	bool hasBindingChanged = false;
	if (binding->isDetermined)
	{
		const char* bindingName;

		if (binding->key == ImGuiKey_None)
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_unbound);
			bindingName = "?";
		}
		else
		{
			ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);
			bindingName = ImGuiKey_GetName(binding->key);
		}

		if (Button(bindingName, buttonSize))
			binding->isDetermined = false;
	}
	else
	{
		ImGui::PushStyleColor(ImGuiCol_Button, buttonColor_capturing);

		Button("...", buttonSize);
		for (int keyCode = ImGuiKey_NamedKey_BEGIN; keyCode < ImGuiKey_NamedKey_END; keyCode++)
		{
			if (IsKeyPressed((ImGuiKey)keyCode))
			{
				/* Verify that keyCode is within pre-determined list of keys. */
				if (ImGuiKey_ToWinAPI((ImGuiKey)keyCode) == 0)
					continue;

				/* When user tries to assign same key that is already set, consider that as will to unbind. */
				if (keyCode == binding->key)
					binding->key = ImGuiKey_None;
				else
					binding->key = (ImGuiKey)keyCode;

				binding->isDetermined = true;
				hasBindingChanged = true;
				break;
			}
		}
	}

	ImGui::PopStyleColor();
	ImGui::PopID();

	return hasBindingChanged;
}

bool ImGui::IsKeyBindingPressed(KeyBinding* binding, const bool& waitForRelease)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (waitForRelease)
	{
		if (GetAsyncKeyState(keyCode) & 0x8000)
		{
			binding->isInUse = true;
			while (GetAsyncKeyState(keyCode) & 0x8000)
			{
				Sleep(1);
			}

			binding->isInUse = false;
			return true;
		}
	}
	else
		return (GetAsyncKeyState(keyCode) & 1);

	return false;
}

bool ImGui::IsKeyBindingDown(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse) // <-- !
		return true;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	if (GetAsyncKeyState(keyCode) & 0x8000)
		return true;

	return false;
}

bool ImGui::IsKeyBindingReleased(KeyBinding* binding)
{
	if (!binding)
		return false;

	if (binding->isDetermined == false)
		return false;

	if (binding->isInUse)
		return false;

	if (binding->key == ImGuiKey_None)
		return false;

	int keyCode = ImGuiKey_ToWinAPI(binding->key);
	return (GetAsyncKeyState(keyCode) & 0x8000) == false;
}






// ========================================================
// |                #GUI #UI #USERINTERFACE               |
// ========================================================
bool GUI::StartDirectWindowThread()
{
	if (directWindowThread)
		return false;

	directWindowThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DirectWindow::Create, 0, 0, 0);
	return directWindowThread;
}




void GUI::Init(const HMODULE& applicationModule)
{
	/* Before creating a DirectWindow, we need to make it aware of our DLL HMODULE. */
	DirectWindow::SetApplicationModule(applicationModule);
	StartDirectWindowThread();
}




void GUI::Draw()
{
	ImGuiViewport* iViewPort = ImGui::GetMainViewport();
	ImVec2 iViewPortPosition = { iViewPort->Pos.x, iViewPort->Pos.y };
	ImVec2 iViewPortSize = { iViewPort->Size.x, iViewPort->Size.y };

	ImDrawList* iDrawList = ImGui::GetBackgroundDrawList();


	if (GetIsMenuActive())
	{
		if (ImGui::BeginMainMenuBar())
		{
			ImGui::Text("UETools GUI (v2.2)");
			if (ImGui::IsItemHovered())
			{
				ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
			}
			if (ImGui::IsItemClicked())
			{
				ShellExecuteA(NULL, "open", "https://github.com/Cranch-fur/UETools-GUI", NULL, NULL, SW_SHOWNORMAL);
			}


			ImGui::Text(" | ");


			if (ImGui::BeginMenu("Debug"))
			{
				if (Features::Debug::enabled == false)
				{
					if (ImGui::Button("Start"))
					{
						if (Features::Debug::autoUpdate == false)
							Features::Debug::Update();

						Features::Debug::enabled = true;
						PlayActionSound(true);
					}
				}
				else
				{
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0 / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

					ImGui::NewLine();

					if (Features::Debug::autoUpdate)
					{
						float updatesPerSecond = 1.0f / Features::Debug::autoUpdateDelay;
						if (updatesPerSecond > 1.0f)
							ImGui::Text("Updates %d times per second", (int32_t)(updatesPerSecond));
						else
						{
							float updatesPerMinute = 60.0f / Features::Debug::autoUpdateDelay;
							if (updatesPerMinute > 1.0f)
								ImGui::Text("Updates %d times per minute", (int32_t)(updatesPerMinute));
							else
							{
								float updatesPerHour = 3600.0f / Features::Debug::autoUpdateDelay;
								if (updatesPerHour > 1.0f)
									ImGui::Text("Updates %d times per hour", (int32_t)(updatesPerHour));
								else
								{
									float updatesPerDay = 86400.0f / Features::Debug::autoUpdateDelay;
									if (updatesPerDay > 1.0f)
										ImGui::Text("Updates %d times per day", (int32_t)(updatesPerDay));
									else
										ImGui::Text("Updates periodically", (int32_t)(updatesPerDay));
								}
							}
						}
						if (ImGui::InputFloat("Auto Update Delay", &Features::Debug::autoUpdateDelay, 0.01f, 0.1f))
						{
							if (Features::Debug::autoUpdateDelay < 0.01f)
								Features::Debug::autoUpdateDelay = 0.01f;
						}

						const double now = ImGui::GetTime();
						const double elapsed = now - Features::Debug::lastUpdateTime;

						if (elapsed >= Features::Debug::autoUpdateDelay)
							Features::Debug::Update();
					}
					else
					{
						const double now = ImGui::GetTime();
						const double elapsed = now - Features::Debug::lastUpdateTime;
						if (elapsed < 60.0)
						{
							int seconds = (int)elapsed;
							ImGui::Text("Last Update: %d %s ago", seconds, (seconds == 1 ? "second" : "seconds"));
						}
						else if (elapsed < 3600.0)
						{
							int minutes = (int)(elapsed / 60.0);
							ImGui::Text("Last Update: %d %s ago", minutes, (minutes == 1 ? "minute" : "minutes"));
						}
						else if (elapsed < 86400.0)
						{
							int hours = (int)(elapsed / 3600.0);
							ImGui::Text("Last Update: %d %s ago", hours, (hours == 1 ? "hour" : "hours"));
						}
						else
						{
							int days = (int)(elapsed / 86400.0);
							ImGui::Text("Last Update: %d %s ago", days, (days == 1 ? "day" : "days"));
						}
					}


					ImGui::BeginDisabled(Features::Debug::autoUpdate);
					if (ImGui::Button("Update##DebugInformation"))
					{
						Features::Debug::Update();
						PlayActionSound(true);
					}
					ImGui::EndDisabled();
					ImGui::SameLine();
					ImGui::Checkbox("Auto", &Features::Debug::autoUpdate);
					if (ImGui::Button("Stop"))
					{
						Features::Debug::enabled = false;
						PlayActionSound(true);
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Engine:", Features::Debug::engine.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::engine.reference)
					{
						if (ImGui::CollapsingHeader("Details##Engine"))
						{
							ImGui::Text("Engine Class: %s", Features::Debug::engine.className.c_str());
							ImGui::Text("Engine Object: %s", Features::Debug::engine.objectName.c_str());

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Game Viewport Client:", Features::Debug::engine.gameViewportClient.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::engine.gameViewportClient.reference)
							{
								if (ImGui::TreeNode("Details##GameViewportClient"))
								{
									ImGui::Text("Viewport Client Class: %s", Features::Debug::engine.gameViewportClient.className.c_str());
									ImGui::Text("Viewport Client Object: %s", Features::Debug::engine.gameViewportClient.objectName.c_str());

									ImGui::NewLine();

									ImGui::SetFontTitle();
									ImGui::TextBoolPresenceColored("Console:", Features::Debug::engine.gameViewportClient.console.reference);
									ImGui::SetFontRegular();
									if (Features::Debug::engine.gameViewportClient.console.reference)
									{
										ImGui::SameLine();
										ImGui::TextHint("Press ~ (Tilde) or F10 to open. Second press will switch console to detailed mode.");

										if (ImGui::TreeNode("Details##Console"))
										{
											ImGui::Text("Console Class: %s", Features::Debug::engine.gameViewportClient.console.className.c_str());
											ImGui::Text("Console Object: %s", Features::Debug::engine.gameViewportClient.console.objectName.c_str());

											ImGui::TreePop();
										}
									}
									else
									{
										if (ImGui::Button("Construct Console"))
										{
											bool wasConstructed = Unreal::Console::Construct() && Unreal::InputSettings::AssignConsoleBindings();
											if (wasConstructed) // Only gather debug information if we're aware of changes.
												Features::Debug::Update();

											PlayActionSound(wasConstructed);
										}
									}

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::Text("High Dynamic Range");
							ImGui::SetFontRegular();
							if (ImGui::TreeNode("Details##HDR"))
							{
#ifndef UE5
								ImGui::SetFontTitle();
								ImGui::Text("[!] DirectX 12 [!]");
								ImGui::SetFontRegular();
								ImGui::Text("Unreal Engine 4.14 - 4.27 only support HDR while running under DirectX 11.");
								ImGui::NewLine();
#endif

								ImGui::SetFontSmall();
								ImGui::Text("HDR must be allowed through configuration file in order to be enabled.");

								ImGui::SetFontRegular();
								ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
								ImGui::SetFontSmall();
								static const char* HDRAllowConfigDescription = "[/Script/Engine.RendererSettings]\n"
																			   "r.AllowHDR = 1";
								static const size_t HDRAllowConfigDescriptionLength = strlen(HDRAllowConfigDescription);
								ImGui::InputTextMultiline("##HDRAllowConfigDescription", const_cast<char*>(HDRAllowConfigDescription), HDRAllowConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);

								ImGui::NewLine();

								ImGui::Text("Behavior can be adjusted through configuration file or Unreal Engine Console (Engine -> Game Viewport Client -> Console).");

								ImGui::SetFontRegular();
								ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
								ImGui::SetFontSmall();
								static const char* HDRSettingsConfigDescription = "[/Script/Engine.RendererSettings]\n"
																				  "r.HDR.EnableHDROutput = 1\n"
																				  "; 0 - LDR.\n"
																				  "; 1 - HDR.\n"
																				  "\n"
																				  "r.HDR.Display.ColorGamut = 2\n"
																				  "; Color space of the output display.\n"
																				  "; 0 - Rec709.\n"
																				  "; 1 - DCI - P3.\n"
																				  "; 2 - Rec2020.\n"
																				  "; 3 - ACES.\n"
																				  "; 4 - ACEScg.\n"
																				  "\n"
																				  "r.HDR.Display.OutputDevice = 5\n"
																				  "; Device format of the output display\n"
																				  "; 0 - sRGB (LDR).\n"
																				  "; 1 - Rec709 (LDR).\n"
																				  "; 2 - Explicit gamma mapping (LDR).\n"
																				  "; 3 - ACES 1000 nit ST-2084 (Dolby PQ) (HDR).\n"
																				  "; 4 - ACES 2000 nit ST-2084 (Dolby PQ) (HDR).\n"
																				  "; 5 - ACES 1000 nit ScRGB (HDR).\n"
																				  "; 6 - ACES 2000 nit ScRGB (HDR).\n"
																				  "; 7 - Linear EXR (HDR).\n"
																				  "; 8 - Linear final color, no tone curve (HDR).\n"
																				  "; 9 - Linear final color with tone curve (HDR).\n"
																				  "\n"
#ifdef UE5																		  										  
																				  "r.HDR.Display.MaxLuminance = 1000\n"
																				  "; Output peak nit level.\n"
																				  "\n"
																				  "r.HDR.Display.MidLuminance = 15\n"
																				  "; Output nit level for 18% gray."
																				  "\n"
#endif																			  										  
																				  "r.HDR.UI.CompositeMode = 1\n"
																				  "; Preserve LDR visuals and blending for UI elements.\n"
																				  "\n"
																				  "r.HDR.UI.Level = 0.65\n"
																				  "; Luminance level for UI elements.";
								static const size_t HDRSettingsConfigDescriptionLength = strlen(HDRSettingsConfigDescription);
								ImGui::InputTextMultiline("##HDRSettingsConfigDescription", const_cast<char*>(HDRSettingsConfigDescription), HDRSettingsConfigDescriptionLength, { 800, 600 }, ImGuiInputTextFlags_ReadOnly);

								ImGui::SetFontRegular();
								ImGui::Text("Unreal Engine Console");
								ImGui::SetFontSmall();
								static const char* HDRSettingsConsoleDescription = "r.HDR.EnableHDROutput 1 | "
																				   "r.HDR.Display.ColorGamut 2 | "
																				   "r.HDR.Display.OutputDevice 5 | "
#ifdef UE5																		   
																				   "r.HDR.Display.MaxLuminance 1000 | "
																				   "r.HDR.Display.MidLuminance 15 | "
#endif																			   
																				   "r.HDR.UI.CompositeMode 1 | "
																				   "r.HDR.UI.Level 0.65";
								static const size_t HDRSettingsConsoleDescriptionLength = strlen(HDRSettingsConsoleDescription);
								ImGui::InputTextMultiline("##HDRSettingsConsoleDescription", const_cast<char*>(HDRSettingsConsoleDescription), HDRSettingsConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);

								ImGui::NewLine();

								ImGui::Text("Autoexposure and fake HDR can cause scenes to appear overly dark.");

								ImGui::SetFontRegular();
								ImGui::Text("DefaultEngine.ini | UserEngine.ini | Engine.ini");
								ImGui::SetFontSmall();
								static const char* HDRDisturbanceConfigDescription = "[/Script/Engine.RendererSettings]\n"
																					 "r.DefaultFeature.AutoExposure = 0\n"
																					 "r.EyeAdaptationQuality = 0";
								static const size_t HDRDisturbanceConfigDescriptionLength = strlen(HDRDisturbanceConfigDescription);
								ImGui::InputTextMultiline("##HDRDisturbanceConfigDescription", const_cast<char*>(HDRDisturbanceConfigDescription), HDRDisturbanceConfigDescriptionLength, { 500, 120 }, ImGuiInputTextFlags_ReadOnly);

								ImGui::SetFontRegular();
								ImGui::Text("Unreal Engine Console");
								ImGui::SetFontSmall();
								static const char* HDRDisturbanceConsoleDescription = "r.DefaultFeature.AutoExposure 0 | "
																					  "r.EyeAdaptationQuality 0";
								static const size_t HDRDisturbanceConsoleDescriptionLength = strlen(HDRDisturbanceConsoleDescription);
								ImGui::InputTextMultiline("##HDRDisturbanceConsoleDescription", const_cast<char*>(HDRDisturbanceConsoleDescription), HDRDisturbanceConsoleDescriptionLength, { 800, 40 }, ImGuiInputTextFlags_ReadOnly);

								ImGui::NewLine();

								ImGui::Text("Certain titles may try deleting \"Engine.ini\" configuration file from the system!\nIt's recommended to set it as for read-only (RMB -> Properties).");
								
								ImGui::SetFontRegular();
								ImGui::TreePop();
							}
							

							ImGui::NewLine();

							bool fixedFrameRateEnabled = Features::Debug::engine.fixedFrameRateEnabled;
							if (ImGui::Checkbox("Fixed FrameRate Enabled", &fixedFrameRateEnabled))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.fixedFrameRateEnabled = fixedFrameRateEnabled;
									Features::Debug::engine.reference->bUseFixedFrameRate = fixedFrameRateEnabled;
								}
							}
							float fixedFrameRate = Features::Debug::engine.fixedFrameRate;
							if (ImGui::InputFloat("Fixed FrameRate", &fixedFrameRate, 1.0f, 10.0f))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.fixedFrameRate = fixedFrameRate;
									Features::Debug::engine.reference->FixedFrameRate = fixedFrameRate;
								}
							}

							ImGui::NewLine();

							bool smoothFrameRateEnabled = Features::Debug::engine.smoothFrameRateEnabled;
							if (ImGui::Checkbox("Smooth FrameRate Enabled", &smoothFrameRateEnabled))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.smoothFrameRateEnabled = smoothFrameRateEnabled;
									Features::Debug::engine.reference->bSmoothFrameRate = smoothFrameRateEnabled;
								}
							}
							float smoothFrameRateRange[2] = { Features::Debug::engine.smoothFrameRateRange.LowerBound.Value, Features::Debug::engine.smoothFrameRateRange.UpperBound.Value };
							if (ImGui::InputFloat2("Smooth FrameRate Range", smoothFrameRateRange))
							{
								if (Features::Debug::engine.reference)
								{
									SDK::FFloatRange floatRange = Features::Debug::engine.smoothFrameRateRange;
									floatRange.LowerBound.Value = smoothFrameRateRange[0];
									floatRange.UpperBound.Value = smoothFrameRateRange[1];

									Features::Debug::engine.smoothFrameRateRange = floatRange;
									Features::Debug::engine.reference->SmoothedFrameRateRange = floatRange;
								}
							}

							ImGui::NewLine();

							bool subtitlesEnabled = Features::Debug::engine.subtitlesEnabled;
							if (ImGui::Checkbox("Subtitles Enabled", &subtitlesEnabled))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.subtitlesEnabled = subtitlesEnabled;
									Features::Debug::engine.reference->bSubtitlesEnabled = subtitlesEnabled;
								}
							}
							bool subtitlesForcedOff = Features::Debug::engine.subtitlesForcedOff;
							if (ImGui::Checkbox("Subtitles Forced Off", &subtitlesForcedOff))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.subtitlesForcedOff = subtitlesForcedOff;
									Features::Debug::engine.reference->bSubtitlesForcedOff = subtitlesForcedOff;
								}
							}

							ImGui::NewLine();

							bool pauseOnLossOfFocus = Features::Debug::engine.pauseOnLossOfFocus;
							if (ImGui::Checkbox("Pause On Loss Of Focus", &pauseOnLossOfFocus))
							{
								if (Features::Debug::engine.reference)
								{
									Features::Debug::engine.pauseOnLossOfFocus = pauseOnLossOfFocus;
									Features::Debug::engine.reference->bPauseOnLossOfFocus = pauseOnLossOfFocus;
								}
							}
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Game Instance:", Features::Debug::gameInstance.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::gameInstance.reference)
					{
						if (ImGui::CollapsingHeader("Details##GameInstance"))
						{
							ImGui::Text("Game Instance Class: %s", Features::Debug::gameInstance.className.c_str());
							ImGui::Text("Game Instance Object: %s", Features::Debug::gameInstance.objectName.c_str());

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Online Session:", Features::Debug::gameInstance.onlineSession.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::gameInstance.onlineSession.reference)
							{
								if (ImGui::TreeNode("Details##OnlineSession"))
								{
									ImGui::Text("Online Session Class: %s", Features::Debug::gameInstance.onlineSession.className.c_str());
									ImGui::Text("Online Session Object: %s", Features::Debug::gameInstance.onlineSession.objectName.c_str());

									ImGui::TreePop();
								}
							}
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Game Mode:", Features::Debug::gameMode.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::gameMode.reference)
					{
						if (ImGui::CollapsingHeader("Details##GameMode"))
						{
							ImGui::Text("Game Mode Class: %s", Features::Debug::gameMode.className.c_str());
							ImGui::Text("Game Mode Object: %s", Features::Debug::gameMode.objectName.c_str());

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Game Session:", Features::Debug::gameMode.gameSession.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::gameMode.gameSession.reference)
							{
								if (ImGui::TreeNode("Details##GameSession"))
								{
									ImGui::Text("Game Session Class: %s", Features::Debug::gameMode.gameSession.className.c_str());
									ImGui::Text("Game Session Object: %s", Features::Debug::gameMode.gameSession.objectName.c_str());

									ImGui::NewLine();

									int32_t maxPlayers = Features::Debug::gameMode.gameSession.maxPlayers;
									if (ImGui::InputInt("Max Players", &maxPlayers, 1, 10))
									{
										if (Features::Debug::gameMode.gameSession.reference)
										{
											Features::Debug::gameMode.gameSession.maxPlayers = maxPlayers;
											Features::Debug::gameMode.gameSession.reference->MaxPlayers = maxPlayers;
										}
									}
									int32_t maxSpectators = Features::Debug::gameMode.gameSession.maxSpectators;
									if (ImGui::InputInt("Max Spectators", &maxSpectators, 1, 10))
									{
										if (Features::Debug::gameMode.gameSession.reference)
										{
											Features::Debug::gameMode.gameSession.maxSpectators = maxSpectators;
											Features::Debug::gameMode.gameSession.reference->MaxSpectators = maxSpectators;
										}
									}
									int32_t maxPartySize = Features::Debug::gameMode.gameSession.maxPartySize;
									if (ImGui::InputInt("Max Party Size", &maxPartySize, 1, 10))
									{
										if (Features::Debug::gameMode.gameSession.reference)
										{
											Features::Debug::gameMode.gameSession.maxPartySize = maxPartySize;
											Features::Debug::gameMode.gameSession.reference->MaxPartySize = maxPartySize;
										}
									}
									int32_t maxSplitScreensPerConnection = Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection;
									if (ImGui::InputInt("Max Split Screens Per Connection", &maxSplitScreensPerConnection, 1, 10))
									{
										if (Features::Debug::gameMode.gameSession.reference)
										{
											Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = maxSplitScreensPerConnection;
											Features::Debug::gameMode.gameSession.reference->MaxSplitscreensPerConnection = maxSplitScreensPerConnection;
										}
									}

									ImGui::NewLine();

									ImGui::ReadOnlyInputText("Session Name:", Features::Debug::gameMode.gameSession.sessionName.c_str(), true);

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::TextIntColored("Players Count:", Features::Debug::gameMode.playersCount);
							ImGui::TextIntColored("Spectators Count:", Features::Debug::gameMode.spectatorsCount);

							ImGui::NewLine();

							ImGui::TextBoolColored("Start Players As Spectator:", Features::Debug::gameMode.startPlayersAsSpectators);
							ImGui::ReadOnlyInputText("Default Player Name:", Features::Debug::gameMode.defaultPlayerName.c_str(), true);

							ImGui::NewLine();

							bool useSeamlessTravel = Features::Debug::gameMode.useSeamlessTravel;
							if (ImGui::Checkbox("Use Seamless Travel", &useSeamlessTravel))
							{
								if (Features::Debug::gameMode.reference)
								{
									Features::Debug::gameMode.useSeamlessTravel = useSeamlessTravel;
									Features::Debug::gameMode.reference->bUseSeamlessTravel = useSeamlessTravel;
								}
							}
							bool isPausable = Features::Debug::gameMode.isPausable;
							if (ImGui::Checkbox("Is Pausable", &isPausable))
							{
								if (Features::Debug::gameMode.reference)
								{
									Features::Debug::gameMode.isPausable = isPausable;
									Features::Debug::gameMode.reference->bPauseable = isPausable;
								}
							}

							ImGui::NewLine();

							ImGui::ReadOnlyInputText("Options:", Features::Debug::gameMode.options.c_str(), true);
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("Player Controller:", Features::Debug::playerController.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::playerController.reference)
					{
						if (ImGui::CollapsingHeader("Details##PlayerController"))
						{
							ImGui::Text("Player Controller Class: %s", Features::Debug::playerController.className.c_str());
							ImGui::Text("Player Controller Object: %s", Features::Debug::playerController.objectName.c_str());

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Pawn:", Features::Debug::playerController.pawn.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::playerController.pawn.reference)
							{
								if (ImGui::TreeNode("Details##Pawn"))
								{
									ImGui::Text("Pawn Class: %s", Features::Debug::playerController.pawn.className.c_str());
									ImGui::Text("Pawn Object: %s", Features::Debug::playerController.pawn.objectName.c_str());
									ImGui::TextVectorColored("Location:", Features::Debug::playerController.pawn.location);
									ImGui::TextRotatorColored("Rotation:", Features::Debug::playerController.pawn.rotation);
									ImGui::TextVectorColored("Scale:", Features::Debug::playerController.pawn.scale);

									ImGui::NewLine();

									ImGui::TextBoolColored("Is Controlled:", Features::Debug::playerController.pawn.isControlled);
									ImGui::TextBoolColored("Is Pawn Controlled:", Features::Debug::playerController.pawn.isPawnControlled);
									ImGui::TextBoolColored("Is Player Controlled:", Features::Debug::playerController.pawn.isPlayerControlled);
									ImGui::TextBoolColored("Is Locally Controlled:", Features::Debug::playerController.pawn.isLocallyControlled);
									ImGui::TextBoolColored("Is Bot Controlled:", Features::Debug::playerController.pawn.isBotControlled);

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Camera Manager:", Features::Debug::playerController.cameraManager.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::playerController.cameraManager.reference)
							{
								if (ImGui::TreeNode("Details##CameraManager"))
								{
									ImGui::Text("Camera Manager Class: %s", Features::Debug::playerController.cameraManager.className.c_str());
									ImGui::Text("Camera Manager Object: %s", Features::Debug::playerController.cameraManager.objectName.c_str());
									ImGui::TextVectorColored("Location:", Features::Debug::playerController.cameraManager.location);
									ImGui::TextRotatorColored("Rotation:", Features::Debug::playerController.cameraManager.rotation);
									ImGui::TextVectorColored("Scale:", Features::Debug::playerController.cameraManager.scale);

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Cheat Manager:", Features::Debug::playerController.cheatManager.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::playerController.cheatManager.reference)
							{
								if (ImGui::TreeNode("Details##CheatManager"))
								{
									ImGui::Text("Cheat Manager Class: %s", Features::Debug::playerController.cheatManager.className.c_str());
									ImGui::Text("Cheat Manager Object: %s", Features::Debug::playerController.cheatManager.objectName.c_str());

									ImGui::TreePop();
								}
							}
							else
							{
								if (ImGui::Button("Construct Cheat Manager"))
								{
									bool wasConstructed = Unreal::CheatManager::Construct();
									if (wasConstructed) // Only gather debug information if we're aware of changes.
										Features::Debug::Update();

									PlayActionSound(wasConstructed);
								}
							}
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::TextBoolPresenceColored("World:", Features::Debug::world.reference);
					ImGui::SetFontRegular();
					if (Features::Debug::world.reference)
					{
						if (ImGui::CollapsingHeader("Details##World"))
						{
							ImGui::Text("World Class: %s", Features::Debug::world.className.c_str());
							ImGui::Text("World Object: %s", Features::Debug::world.objectName.c_str());

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Game State:", Features::Debug::world.gameState.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::world.gameState.reference)
							{
								if (ImGui::TreeNode("Details##GameState"))
								{
									ImGui::Text("Game State Class: %s", Features::Debug::world.gameState.className.c_str());
									ImGui::Text("Game State Object: %s", Features::Debug::world.gameState.objectName.c_str());

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Net Driver:", Features::Debug::world.netDriver.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::world.netDriver.reference)
							{
								if (ImGui::TreeNode("Details##NetDriver"))
								{
									ImGui::Text("Net Driver Class: %s", Features::Debug::world.netDriver.className.c_str());
									ImGui::Text("Net Driver Object: %s", Features::Debug::world.netDriver.objectName.c_str());

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Demo Net Driver:", Features::Debug::world.demoNetDriver.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::world.demoNetDriver.reference)
							{
								if (ImGui::TreeNode("Details##DemoNetDriver"))
								{
									ImGui::Text("Demo Net Driver Class: %s", Features::Debug::world.demoNetDriver.className.c_str());
									ImGui::Text("Demo Net Driver Object: %s", Features::Debug::world.demoNetDriver.objectName.c_str());

									ImGui::TreePop();
								}
							}

							ImGui::NewLine();

							ImGui::SetFontTitle();
							ImGui::TextBoolPresenceColored("Persistent Level:", Features::Debug::world.persistentLevel.reference);
							ImGui::SetFontRegular();
							if (Features::Debug::world.persistentLevel.reference)
							{
								if (ImGui::TreeNode("Details##PersistentLevel"))
								{
									ImGui::Text("Persistent Level Class: %s", Features::Debug::world.persistentLevel.className.c_str());
									ImGui::Text("Persistent Level Object: %s", Features::Debug::world.persistentLevel.objectName.c_str());
									ImGui::TextBoolColored("Is Visible:", Features::Debug::world.persistentLevel.isVisible);

									ImGui::NewLine();

									bool worldSettingsPresent = Features::Debug::world.persistentLevel.worldSettings.reference;
									ImGui::TextBoolPresenceColored("World Settings:", worldSettingsPresent);
									if (worldSettingsPresent)
									{
										if (ImGui::TreeNode("World Settings"))
										{
											ImGui::Text("World Settings Class: %s", Features::Debug::world.persistentLevel.worldSettings.className.c_str());
											ImGui::Text("World Settings Object: %s", Features::Debug::world.persistentLevel.worldSettings.objectName.c_str());

											ImGui::NewLine();

											ImGui::TextBoolColored("High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading);
											ImGui::TextBoolColored("Local High Priority Loading:", Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading);

											ImGui::NewLine();

											ImGui::TextFloat("Unreal Units = 1m:", Features::Debug::world.persistentLevel.worldSettings.unitsToMeters);

											ImGui::TreePop();
										}
									}

									ImGui::NewLine();

									bool areStreamingLevelsPresent = Features::Debug::world.streamingLevels.size() > 0;
									ImGui::TextBoolMultiplePresenceColored("Streaming Levels:", areStreamingLevelsPresent);
									if (areStreamingLevelsPresent)
									{
										if (ImGui::TreeNode("Streaming Levels"))
										{
											ImGui::InputText("Search Filter", Features::Debug::streamingLevelsFilterBuffer, Features::Debug::streamingLevelsFilterBufferSize);
											ImGui::SameLine();
											ImGui::Spacing();
											ImGui::SameLine();
											ImGui::Checkbox("Case Sensitive", &Features::Debug::streamingLevelsFilterCaseSensitive);
											ImGui::SameLine();
											ImGui::Spacing();
											ImGui::SameLine();
											ImGui::Checkbox("Editor Colors", &Features::Debug::streamingLevelsEditorColors);

											std::vector<Unreal::LevelStreaming::DataStructure> filteredStreamingLevels = Unreal::LevelStreaming::FilterByLevelPath(Features::Debug::world.streamingLevels, Features::Debug::streamingLevelsFilterBuffer, Features::Debug::streamingLevelsFilterCaseSensitive);
											for (Unreal::LevelStreaming::DataStructure& streamingLevel : filteredStreamingLevels) // <-- Reference!
											{
												ImGui::PushID(streamingLevel.objectName.c_str());

												ImVec4 levelColor;
												if (Features::Debug::streamingLevelsEditorColors)
												{
													levelColor = { streamingLevel.levelColor.R, streamingLevel.levelColor.G, streamingLevel.levelColor.B, streamingLevel.levelColor.A };
												}
												else
												{
													static const ImVec4 color_visible = ImGui::ColorConvertU32ToFloat4(IM_COL32(51, 204, 77, 255));
													static const ImVec4 color_loaded = ImGui::ColorConvertU32ToFloat4(IM_COL32(51, 102, 204, 255));
													static const ImVec4 color_null = ImGui::ColorConvertU32ToFloat4(IM_COL32(204, 77, 51, 255));

													if (streamingLevel.level.reference)
														levelColor = streamingLevel.level.isVisible ? color_visible : color_loaded;
													else
														levelColor = color_null;
												}

												ImGui::PushStyleColor(ImGuiCol_Text, levelColor);
												bool isTreeNodeOpen = ImGui::TreeNode(streamingLevel.levelPath.c_str());
												ImGui::PopStyleColor();

												if (isTreeNodeOpen)
												{
													if (Features::Debug::autoUpdate == false)
													{
														ImGui::Text("Debug section isn't set to auto-update!");
														ImGui::SetFontSmall();
														ImGui::Text("In order to see level related changes in UI, use \"Update\" button.");
														ImGui::SetFontRegular();
														ImGui::NewLine();
													}

													bool isLevelLoaded = streamingLevel.level.reference;

													ImGui::TextBoolColored("Is Loaded:", isLevelLoaded);
													ImGui::SameLine();
													ImGui::Spacing();
													ImGui::SameLine();
													if (ImGui::Button(isLevelLoaded ? "Unload" : "Load"))
													{
														if (streamingLevel.reference != nullptr)
														{
															streamingLevel.reference->SetShouldBeLoaded(!isLevelLoaded);
															PlayActionSound(true);
														}
														else
															PlayActionSound(false);
													}

													ImGui::TextBoolColored("Is Visible:", streamingLevel.level.isVisible);
													ImGui::SameLine();
													ImGui::Spacing();
													ImGui::SameLine();
													ImGui::BeginDisabled(isLevelLoaded == false);
													if (ImGui::Button(streamingLevel.level.isVisible ? "Hide" : "Show"))
													{
														if (isLevelLoaded && streamingLevel.reference != nullptr)
														{
															streamingLevel.reference->SetShouldBeVisible(!streamingLevel.level.isVisible);
															PlayActionSound(true);
														}
														else
															PlayActionSound(false);
													}
													ImGui::EndDisabled();

													ImGui::NewLine();

													bool worldSettingsPresent = streamingLevel.level.worldSettings.reference;
													ImGui::TextBoolPresence("World Settings:", worldSettingsPresent);
													if (worldSettingsPresent)
													{
														if (ImGui::TreeNode("World Settings"))
														{
															ImGui::Text("World Settings Class: %s", streamingLevel.level.worldSettings.className.c_str());
															ImGui::Text("World Settings Object: %s", streamingLevel.level.worldSettings.objectName.c_str());

															ImGui::NewLine();

															ImGui::TextBoolColored("High Priority Loading:", streamingLevel.level.worldSettings.highPriorityLoading);
															ImGui::TextBoolColored("Local High Priority Loading:", streamingLevel.level.worldSettings.localHighPriorityLoading);

															ImGui::NewLine();

															ImGui::TextFloat("Unreal Units = 1m:", streamingLevel.level.worldSettings.unitsToMeters);

															ImGui::TreePop();
														}
													}

													ImGui::TreePop();
												}

												ImGui::PopID();
											}

											ImGui::TreePop();
										}
									}

									ImGui::NewLine();

									ImGui::TextFloatColored("Game Time (In Seconds):", Features::Debug::world.gameTimeInSeconds);

									ImGui::NewLine();

									ImGui::TextBoolColored("Is Server:", Features::Debug::world.isServer);
									ImGui::TextBoolColored("Is Dedicated Server:", Features::Debug::world.isDedicatedServer);
									ImGui::TextBoolColored("Is Split Screen:", Features::Debug::world.isSplitScreen);
									ImGui::TextBoolColored("Is Standalone:", Features::Debug::world.isStandalone);

									ImGui::TreePop();
								}
							}
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::Text("Actors");
					ImGui::SetFontRegular();
					if (ImGui::CollapsingHeader("Details##Actors"))
					{
#ifdef ACTOR_TRACE
						ImGui::SetFontTitle();
						ImGui::Text("Actor Trace");
						ImGui::SetFontSmall();
						ImGui::Text("Performs a trace starting at the camera's position and outputs the name of the Actor hit by the trace.");
						ImGui::Text("X - Location at where trace has hit an Actor.");
						ImGui::Text("@ - Location at where trace has ended without a hit.");
						ImGui::Text("O - Location at where trace has started.");
						ImGui::SetFontRegular();
						ImGui::Checkbox("Enabled##ActorTrace", &Features::ActorTrace::enabled);
						ImGui::BeginDisabled(Features::ActorTrace::enabled == false);
						if (ImGui::TreeNode("Settings##ActorTrace"))
						{
							ImGui::KeyBindingInput("Key Binding:", &Keybindings::debug_ActorTrace);

							ImGui::NewLine();

							ImGui::Checkbox("Show On Screen##ActorTrace", &Features::ActorTrace::showOnScreen);
							ImGui::Checkbox("Show Line Trace##ActorTrace", &Features::ActorTrace::showLineTrace);

							ImGui::NewLine();

							ImGui::ColorPicker4("Trace Color", Features::ActorTrace::traceColor);
							ImGui::InputFloat("Trace Thickness", &Features::ActorTrace::traceThickness, 0.1f, 1.0f);
							ImGui::InputFloat("Trace Length", &Features::ActorTrace::traceLength, 1.0f, 10.0f);

							ImGui::TreePop();
						}
						ImGui::EndDisabled();

						ImGui::NewLine();
#endif


						ImGui::SetFontTitle();
						ImGui::Text("Actor Spawn");
						ImGui::SetFontSmall();
#ifdef SOFT_PATH
						ImGui::Text("Dynamic Actor spawning from ready to go presets");
						ImGui::Text("and by soft path, for example \"/Game/Blueprints/Watermelon.Watermelon_C\".");
						ImGui::Text("Feature supports combined input using the '|' separator between paths.");
#else
						ImGui::Text("Dynamic Actor spawning from ready to go presets.");
#endif
						ImGui::SetFontRegular();

						if (ImGui::TreeNode("Details##ActorSpawn"))
						{
							ImGui::SetFontTitle();
							ImGui::Text("Quick Summon");
							ImGui::SetFontRegular();

							if (ImGui::Button("Point Light"))
							{
								SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::APointLight::StaticClass());
								PlayActionSound(actorReference);
							}
							ImGui::SameLine();
							if (ImGui::Button("Spot Light"))
							{
								SDK::AActor* actorReference = Unreal::Actor::Summon(SDK::ASpotLight::StaticClass());
								PlayActionSound(actorReference);
							}

#ifdef SOFT_PATH
							ImGui::CategorySeparator();

							ImGui::SetFontTitle();
							ImGui::Text("Soft Summon");
							ImGui::SetFontRegular();

							ImGui::Text("Actor Path:    ");
							ImGui::SameLine();
							ImGui::InputText("##ActorSpawn", Features::ActorSpawn::actorPathBuffer, Features::ActorSpawn::actorPathBufferSize);

							ImGui::Checkbox("Use Character Location##ActorSpawn", &Features::ActorSpawn::useCharacterLocation);
							ImGui::BeginDisabled(Features::ActorSpawn::useCharacterLocation);
							ImGui::Text("Actor Location:");
							ImGui::SameLine();
							ImGui::InputFloat3("##ActorSpawnLocation", Features::ActorSpawn::location);
							ImGui::EndDisabled();

							ImGui::Checkbox("Use Character Rotation##ActorSpawn", &Features::ActorSpawn::useCharacterRotation);
							ImGui::BeginDisabled(Features::ActorSpawn::useCharacterRotation);
							ImGui::Text("Actor Rotation:");
							ImGui::SameLine();
							ImGui::InputFloat3("##ActorSpawnRotation", Features::ActorSpawn::rotation);
							ImGui::EndDisabled();

							ImGui::Text("Actor Scale:   ");
							ImGui::SameLine();
							ImGui::InputFloat3("##ActorSpawnScale", Features::ActorSpawn::scale);

							if (ImGui::Button("Spawn Actor##ActorSpawn"))
							{
								SDK::UWorld* world = Unreal::World::Get();
								if (world)
								{
									Unreal::Transform spawnTransform;
									spawnTransform.location = spawnTransform.location = { Features::ActorSpawn::location[0], Features::ActorSpawn::location[1], Features::ActorSpawn::location[2] };
									spawnTransform.rotation = { Features::ActorSpawn::rotation[0], Features::ActorSpawn::rotation[1], Features::ActorSpawn::rotation[2] };
									spawnTransform.scale = { Features::ActorSpawn::scale[0], Features::ActorSpawn::scale[1], Features::ActorSpawn::scale[2] };

									if (Features::ActorSpawn::useCharacterLocation || Features::ActorSpawn::useCharacterRotation)
									{
										SDK::APlayerController* playerController = Unreal::PlayerController::Get();
										if (playerController)
										{
											Unreal::Transform playerTransform;

											if (playerController->Pawn)
												playerTransform = Unreal::Actor::GetTransform(playerController->Pawn);
											else if (playerController->PlayerCameraManager)
												playerTransform = Unreal::Actor::GetTransform(playerController->PlayerCameraManager);

											if (Features::ActorSpawn::useCharacterLocation)
												spawnTransform.location = playerTransform.location;

											if (Features::ActorSpawn::useCharacterRotation)
												spawnTransform.rotation = playerTransform.rotation;
										}
									}
									
									std::vector<SDK::FString> actorPathCollection = Unreal::String::Split(Features::ActorSpawn::actorPathBuffer, '|');
									if (actorPathCollection.size() > 0)
									{
										bool anyActorSpawned = false;
	
										for (SDK::FString& actorPath : actorPathCollection) // <-- Reference!
										{
											if (SDK::AActor* actorReference = Unreal::Actor::SoftSummon(actorPath, spawnTransform))
												anyActorSpawned = true;
										}

										PlayActionSound(anyActorSpawned);
									}
									else
										PlayActionSound(false);
								}
								else
									PlayActionSound(false);
							}
#endif

							ImGui::TreePop();
						}

						ImGui::NewLine();

						if (ImGui::Button("Update##Actors"))
						{
							Features::ActorsList::Update();
							PlayActionSound(true);
						}
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::InputText("Search Filter##Actors", Features::ActorsList::filterBuffer, Features::ActorsList::filterBufferSize);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::Checkbox("Case Sensitive##Actors", &Features::ActorsList::filterCaseSensitive);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::ObjectFilterModeComboBox("##Actors", &Features::ActorsList::filterMode);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::Checkbox("Check Validness##Actors", &Features::ActorsList::filterCheckValidness);

#ifdef COLLISION_VISUALIZER
						ImGui::Checkbox("Draw Collision##Actors", &Features::CollisionVisualizer::enabled);
						ImGui::SameLine();
						ImGui::TextHint("Draws simplified polygonal wireframe color of which depends on Actor type:\n\nStatic Mesh\n- BLUE: Collision.\n\nVolume\n- RED: Blocking (Collision).\n- ORANGE: Trigger.\n- WHITE: Unknown.\n\nPawn\n-GREEN: Capsule Collision.");
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
#endif

#ifdef ACTORS_TRACKING
						ImGui::Checkbox("Enable Tracking##Actors", &Features::ActorsTracker::enabled);
						ImGui::SameLine();
						ImGui::TextHint("Draws circle at root location alongside Actor technical name.\n\nExtremely useful when it's needed to find an specific Actor in 3D space.");
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
#endif

						ImGui::Text("In Distance:");
						ImGui::SameLine();
						if (ImGui::InputFloat("##FilterDistance##Actors", &Features::ActorsList::filterDistance, 100.0f, 1000.0f))
						{
							Features::ActorsList::filterDistance = std::clamp(Features::ActorsList::filterDistance, 0.0f, 100000.0f);
						}
						ImGui::SameLine();
						ImGui::TextHint("Maximum Actor distance from Player in centimetres. Calculations doesn't update in background!\n\nThat allows to return to the game while keeping needed Actors filtered.");
						
						ImGui::NewLine();

						if (ImGui::Button("Enable Collision (All)##Actors"))
						{
							bool anyActorCollisionEnabled = false;
							for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
							{
								if (actor.reference)
								{
									actor.reference->SetActorEnableCollision(true);
									anyActorCollisionEnabled = true;
								}
							}

							PlayActionSound(anyActorCollisionEnabled);
						}
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						if (ImGui::Button("Disable Collision (All)##Actors"))
						{
							bool anyActorCollisionDisabled = false;
							for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
							{
								if (actor.reference)
								{
									actor.reference->SetActorEnableCollision(false);
									anyActorCollisionDisabled = true;
								}
							}

							PlayActionSound(anyActorCollisionDisabled);
						}

						if (ImGui::Button("Set Visible (All)##Actors"))
						{
							bool anyActorShown = false;
							for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
							{
								if (actor.reference)
								{
									Unreal::Actor::SetVisibility(actor.reference, true);
									anyActorShown = true;
								}
							}

							PlayActionSound(anyActorShown);
						}
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						if (ImGui::Button("Set Hidden (All)##Actors"))
						{
							bool anyActorHidden = false;
							for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
							{
								if (actor.reference)
								{
									Unreal::Actor::SetVisibility(actor.reference, false);
									anyActorHidden = true;
								}
							}

							PlayActionSound(anyActorHidden);
						}

						if (ImGui::Button("Destroy (All)##Actors"))
						{
							bool anyActorDestroyed = false;
							for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
							{
								if (actor.reference)
								{
									actor.reference->K2_DestroyActor();
									anyActorDestroyed = true;
								}
							}

							PlayActionSound(anyActorDestroyed);
						}

						ImGui::NewLine();

						/* Filter Actors by "Search Filter" */
						switch (Features::ActorsList::filterMode)
						{
							case ImGui::E_ObjectFilterMode::ClassName:
								Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
								break;

							case ImGui::E_ObjectFilterMode::ObjectName:
								Features::ActorsList::filteredActors = Unreal::Actor::FilterByObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
								break;

							case ImGui::E_ObjectFilterMode::All:
								Features::ActorsList::filteredActors = Unreal::Actor::FilterByClassAndObjectName(Features::ActorsList::actors, Features::ActorsList::filterBuffer, Features::ActorsList::filterCaseSensitive, Features::ActorsList::filterDistance);
								break;
						}
						
						/* Output to user interface Actors that are matching "Search Filter" */
						for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
						{
							bool isTreeNodeOpen;
							if (Features::ActorsList::filterCheckValidness)
							{
								ImU32 color = Math::ColorFloat4_ToU32(Unreal::Actor::IsValid(actor.reference) ? Features::ActorsList::color_Valid : Features::ActorsList::color_Invalid);

								ImGui::PushStyleColor(ImGuiCol_Text, color);
								isTreeNodeOpen = ImGui::TreeNode(actor.objectName.c_str());
								ImGui::PopStyleColor();
							}
							else
								isTreeNodeOpen = ImGui::TreeNode(actor.objectName.c_str());
								
							if (isTreeNodeOpen)
							{
								ImGui::PushID(actor.objectName.c_str());

								ImGui::BeginDisabled(std::strcmp(Features::ActorsList::filterBuffer, actor.objectName.c_str()) == 0);
								if (ImGui::Button("Focus On"))
								{
									std::snprintf(Features::ActorsList::filterBuffer, sizeof(Features::ActorsList::filterBuffer), actor.objectName.c_str());
									Features::ActorsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

									PlayActionSound(true);
								}
								ImGui::EndDisabled();

								ImGui::NewLine();

								ImGui::Text("Actor Super Class: %s", actor.superClassName.c_str());
								ImGui::Text("Actor Class: %s", actor.className.c_str());
								ImGui::Text("Actor Object: %s", actor.objectName.c_str());

								ImGui::NewLine();

								ImGui::TextVectorColored("Location:", actor.location);
								static float customLocation[3];
								if (ImGui::Button("Copy##Location"))
								{
									customLocation[0] = actor.location.X;
									customLocation[1] = actor.location.Y;
									customLocation[2] = actor.location.Z;
									PlayActionSound(true);
								}
								ImGui::SameLine();
								ImGui::InputFloat3("##Location", customLocation);
								ImGui::SameLine();
								if (ImGui::Button("Set##Location"))
								{
									if (actor.reference)
									{
										actor.reference->K2_TeleportTo({ customLocation[0], customLocation[1], customLocation[2] }, actor.reference->K2_GetActorRotation());
										PlayActionSound(true);

										Features::ActorsList::Update();
									}
									else
										PlayActionSound(false);
								}

								ImGui::TextRotatorColored("Rotation:", actor.rotation);
								static float customRotation[3];
								if (ImGui::Button("Copy##Rotation"))
								{
									customRotation[0] = actor.rotation.Pitch;
									customRotation[1] = actor.rotation.Yaw;
									customRotation[2] = actor.rotation.Roll;
									PlayActionSound(true);
								}
								ImGui::SameLine();
								ImGui::InputFloat3("##Rotation", customRotation);
								ImGui::SameLine();
								if (ImGui::Button("Set##Rotation"))
								{
									if (actor.reference)
									{
										actor.reference->K2_TeleportTo(actor.reference->K2_GetActorLocation(), SDK::FRotator(customRotation[0], customRotation[1], customRotation[2]));
										PlayActionSound(true);

										Features::ActorsList::Update();
									}
									else
										PlayActionSound(false);
								}

								ImGui::TextVectorColored("Scale:", actor.scale);
								static float customScale[3];
								if (ImGui::Button("Copy##Scale"))
								{
									customScale[0] = actor.scale.X;
									customScale[1] = actor.scale.Y;
									customScale[2] = actor.scale.Z;
									PlayActionSound(true);
								}
								ImGui::SameLine();
								ImGui::InputFloat3("##Scale", customScale);
								ImGui::SameLine();
								if (ImGui::Button("Set##Scale"))
								{
									if (actor.reference)
									{
										actor.reference->SetActorScale3D(actor.scale);
										PlayActionSound(true);

										Features::ActorsList::Update();
									}
									else
										PlayActionSound(false);
								}

								ImGui::NewLine();

								if (ImGui::Button("Make Static"))
								{
									if (actor.reference && actor.reference->RootComponent)
									{
										actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Static;
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Make Stationary"))
								{
									if (actor.reference && actor.reference->RootComponent)
									{
										actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Stationary;
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Make Movable"))
								{
									if (actor.reference && actor.reference->RootComponent)
									{
										actor.reference->RootComponent->Mobility = SDK::EComponentMobility::Movable;
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								ImGui::TextHint("Static - Never moves and relies entirely on baked lightmaps and shadows for lighting.\nLowest performance cost, ideal for architecture and environment pieces.\n\nStationary - Cannot move but allows changes to materials and visibility, and combines baked lighting with some dynamic shadow interactions.\nSlightly higher cost than Static, good for objects that stay in place but need minor runtime variations.\n\nMovable - Can move, rotate, scale, or animate and uses fully dynamic lighting and shadows.\nHighest performance cost, suited for characters, doors, vehicles, and interactive gameplay objects.");

								if (ImGui::Button("Enable Collision"))
								{
									if (actor.reference)
									{
										actor.reference->SetActorEnableCollision(true);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Disable Collision"))
								{
									if (actor.reference)
									{
										actor.reference->SetActorEnableCollision(false);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

								static bool visibilityPropagateToComponents = false;
								if (ImGui::Button("Set Visible"))
								{
									if (actor.reference)
									{
										Unreal::Actor::SetVisibility(actor.reference, true, visibilityPropagateToComponents);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Set Hidden"))
								{
									if (actor.reference)
									{
										Unreal::Actor::SetVisibility(actor.reference, false, visibilityPropagateToComponents);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								ImGui::Checkbox("Propagate To Components", &visibilityPropagateToComponents);

								if (ImGui::Button("Teleport To Actor"))
								{
									SDK::ACharacter* character = Unreal::Character::Get();
									if (character)
									{
										SDK::FHitResult hitResult;
										PlayActionSound(character->K2_SetActorLocation(actor.location, false, &hitResult, true));
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Teleport Actor To Me"))
								{
									if (actor.reference)
									{
										SDK::ACharacter* character = Unreal::Character::Get();
										if (character)
										{
											SDK::FVector location = character->K2_GetActorLocation();

											SDK::FHitResult hitResult;
											PlayActionSound(actor.reference->K2_SetActorLocation(location, false, &hitResult, true));
										}
										else
											PlayActionSound(false);
									}
									else
										PlayActionSound(false);
								}

								if (ImGui::Button("Destroy"))
								{
									if (actor.reference)
									{
										actor.reference->K2_DestroyActor();
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

								ImGui::NewLine();

								ImGui::Text("Custom Time Dilation");
								static float customTimeDilation = 1.0f;
								if (ImGui::Button("Get##CustomTimeDilation"))
								{
									if (actor.reference)
									{
										customTimeDilation = actor.reference->CustomTimeDilation;
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								ImGui::InputFloat("##CustomTimeDilation", &customTimeDilation, 0.1f, 1.0f);
								ImGui::SameLine();
								if (ImGui::Button("Set##CustomTimeDilation"))
								{
									if (actor.reference)
									{
										actor.reference->CustomTimeDilation = customTimeDilation;
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

								ImGui::NewLine();

								ImGui::Text("Blend Time");
								ImGui::SameLine();
								static float viewTargetBlendTime = 1.0f;
								ImGui::InputFloat("##ViewTargetBlendTime", &viewTargetBlendTime, 0.1f, 1.0f);

								ImGui::Text("Blend Exponent");
								ImGui::SameLine();
								static float viewTargetBlendExponent = 1.0f;
								ImGui::InputFloat("##ViewTargetBlendExponent", &viewTargetBlendExponent, 0.1f, 1.0f);

								if (ImGui::Button("View Target (Linear)"))
								{
									if (actor.reference)
									{
										Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Linear, viewTargetBlendTime, viewTargetBlendExponent);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("View Target (Cubic)"))
								{
									if (actor.reference)
									{
										Unreal::PlayerController::SetViewTarget(actor.reference, SDK::EViewTargetBlendFunction::VTBlend_Cubic, viewTargetBlendTime, viewTargetBlendExponent);
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

#ifdef ACTOR_KIND
								if (actor.kind != Unreal::Actor::E_ActorKind::General)
								{
									ImGui::NewLine();

									switch (actor.kind)
									{
										case Unreal::Actor::E_ActorKind::PointLight:
											if (SDK::APointLight* pointLight = static_cast<SDK::APointLight*>(actor.reference))
											{
												ImGui::SetFontTitle();
												ImGui::Text("Point Light Settings");
												ImGui::SetFontRegular();

												ImGui::BeginDisabled(pointLight->PointLightComponent == nullptr);
												if (ImGui::TreeNode("Details##PointLightSettings"))
												{
													if (SDK::UPointLightComponent* pointLightComponent = pointLight->PointLightComponent)
													{
														if (ImGui::Button("Enable Cast Shadows##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastShadows(true);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Shadows##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastShadows(false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														if (ImGui::Button("Enable Cast Volumetric Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastVolumetricShadow(true);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Volumetric Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastVolumetricShadow(false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}


														if (ImGui::Button("Enable Cast Deep Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastDeepShadow(true);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Deep Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastDeepShadow(false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														if (ImGui::Button("Enable Cast Raytaced Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastRaytracedShadow(true);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Raytaced Shadow##PointLight"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetCastRaytracedShadow(false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Intensity");
														static float pointLightIntensity = 0.0f;
														if (ImGui::Button("Get##PointLightIntensity"))
														{
															if (pointLightComponent)
															{
																pointLightIntensity = pointLightComponent->Intensity;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##PointLightIntensity", &pointLightIntensity, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##PointLightIntensity"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetIntensity(pointLightIntensity);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Source Radius");
														static float pointLightSourceRadius = 0.0f;
														if (ImGui::Button("Get##PointLightSourceRadius"))
														{
															if (pointLightComponent)
															{
																pointLightSourceRadius = pointLightComponent->SourceRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##PointLightSourceRadius", &pointLightSourceRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##PointLightSourceRadius"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetSourceRadius(pointLightSourceRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Soft Source Radius");
														static float pointLightSoftSourceRadius = 0.0f;
														if (ImGui::Button("Get##PointLightSoftSourceRadius"))
														{
															if (pointLightComponent)
															{
																pointLightSoftSourceRadius = pointLightComponent->SoftSourceRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##PointLightSoftSourceRadius", &pointLightSoftSourceRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##PointLightSoftSourceRadius"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetSoftSourceRadius(pointLightSoftSourceRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Attenuation Radius");
														static float pointLightAttenuationRadius = 0.0f;
														if (ImGui::Button("Get##PointLightAttenuationRadius"))
														{
															if (pointLightComponent)
															{
																pointLightAttenuationRadius = pointLightComponent->AttenuationRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##PointLightAttenuationRadius", &pointLightAttenuationRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##PointLightAttenuationRadius"))
														{
															if (pointLightComponent)
															{
																pointLightComponent->SetAttenuationRadius(pointLightAttenuationRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Color");
														static float pointLightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
														if (ImGui::Button("Get##PointLightColor"))
														{
															if (pointLightComponent)
															{
																/* ColorPicker4 can only understand normalized values (in range of 0.0f to 1.0f) */
																pointLightColor[0] = pointLightComponent->LightColor.R / 255.0f;
																pointLightColor[1] = pointLightComponent->LightColor.G / 255.0f;
																pointLightColor[2] = pointLightComponent->LightColor.B / 255.0f;
																pointLightColor[3] = pointLightComponent->LightColor.A / 255.0f;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Set##PointLightColor"))
														{
															if (pointLightComponent)
															{
																SDK::FLinearColor linearColor;
																linearColor.R = pointLightColor[0];
																linearColor.G = pointLightColor[1];
																linearColor.B = pointLightColor[2];
																linearColor.A = pointLightColor[3];

																pointLightComponent->SetLightColor(linearColor, false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::ColorPicker4("##PointLightColor", pointLightColor);
													}
													else
														ImGui::Text("Point Light Component Doesn't Exist!");

													ImGui::TreePop();
												}
												ImGui::EndDisabled();
											}
											break;

										case Unreal::Actor::E_ActorKind::SpotLight:
											if (SDK::ASpotLight* spotLight = static_cast<SDK::ASpotLight*>(actor.reference))
											{
												ImGui::SetFontTitle();
												ImGui::Text("Spot Light Settings");
												ImGui::SetFontRegular();

												ImGui::BeginDisabled(spotLight->SpotLightComponent == nullptr);
												if (ImGui::TreeNode("Details##SpotLightSettings"))
												{
													if (SDK::USpotLightComponent* spotLightComponent = spotLight->SpotLightComponent)
													{
														if (ImGui::Button("Enable Cast Shadows##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastShadows(true);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Shadows##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastShadows(false);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}

														if (ImGui::Button("Enable Cast Volumetric Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastVolumetricShadow(true);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Volumetric Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastVolumetricShadow(false);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}


														if (ImGui::Button("Enable Cast Deep Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastDeepShadow(true);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Deep Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastDeepShadow(false);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}

														if (ImGui::Button("Enable Cast Raytaced Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastRaytracedShadow(true);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Disable Cast Raytaced Shadow##SpotLight"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetCastRaytracedShadow(false);
																PlayActionSound(false);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Intensity");
														static float spotLightIntensity = 0.0f;
														if (ImGui::Button("Get##SpotLightIntensity"))
														{
															if (spotLightComponent)
															{
																spotLightIntensity = spotLightComponent->Intensity;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightIntensity", &spotLightIntensity, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightIntensity"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetIntensity(spotLightIntensity);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Source Radius");
														static float spotLightSourceRadius = 0.0f;
														if (ImGui::Button("Get##SpotLightSourceRadius"))
														{
															if (spotLightComponent)
															{
																spotLightSourceRadius = spotLightComponent->SourceRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightSourceRadius", &spotLightSourceRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightSourceRadius"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetSourceRadius(spotLightSourceRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Soft Source Radius");
														static float spotLightSoftSourceRadius = 0.0f;
														if (ImGui::Button("Get##SpotLightSoftSourceRadius"))
														{
															if (spotLightComponent)
															{
																spotLightSoftSourceRadius = spotLightComponent->SoftSourceRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightSoftSourceRadius", &spotLightSoftSourceRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightSoftSourceRadius"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetSoftSourceRadius(spotLightSoftSourceRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Attenuation Radius");
														static float spotLightAttenuationRadius = 0.0f;
														if (ImGui::Button("Get##SpotLightAttenuationRadius"))
														{
															if (spotLightComponent)
															{
																spotLightAttenuationRadius = spotLightComponent->AttenuationRadius;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightAttenuationRadius", &spotLightAttenuationRadius, 10.0f, 100.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightAttenuationRadius"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetAttenuationRadius(spotLightAttenuationRadius);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Inner Cone Angle");
														static float spotLightInnerConeAngle = 0.0f;
														if (ImGui::Button("Get##SpotLightInnerConeAngle"))
														{
															if (spotLightComponent)
															{
																spotLightInnerConeAngle = spotLightComponent->InnerConeAngle;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightInnerConeAngle", &spotLightInnerConeAngle, 1.0f, 10.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightInnerConeAngle"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetInnerConeAngle(spotLightInnerConeAngle);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Outer Cone Angle");
														static float spotLightOuterConeAngle = 0.0f;
														if (ImGui::Button("Get##SpotLightOuterConeAngle"))
														{
															if (spotLightComponent)
															{
																spotLightOuterConeAngle = spotLightComponent->OuterConeAngle;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##SpotLightOuterConeAngle", &spotLightOuterConeAngle, 1.0f, 10.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightOuterConeAngle"))
														{
															if (spotLightComponent)
															{
																spotLightComponent->SetOuterConeAngle(spotLightOuterConeAngle);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}

														ImGui::NewLine();

														ImGui::Text("Color");
														static float spotLightColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
														if (ImGui::Button("Get##SpotLightColor"))
														{
															if (spotLightComponent)
															{
																/* ColorPicker4 can only understand normalized values (in range of 0.0f to 1.0f) */
																spotLightColor[0] = spotLightComponent->LightColor.R / 255.0f;
																spotLightColor[1] = spotLightComponent->LightColor.G / 255.0f;
																spotLightColor[2] = spotLightComponent->LightColor.B / 255.0f;
																spotLightColor[3] = spotLightComponent->LightColor.A / 255.0f;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														if (ImGui::Button("Set##SpotLightColor"))
														{
															if (spotLightComponent)
															{
																SDK::FLinearColor linearColor;
																linearColor.R = spotLightColor[0];
																linearColor.G = spotLightColor[1];
																linearColor.B = spotLightColor[2];
																linearColor.A = spotLightColor[3];

																spotLightComponent->SetLightColor(linearColor, false);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::ColorPicker4("##SpotLightColor", spotLightColor);
													}
													else
														ImGui::Text("Spot Light Component Doesn't Exist!");

													ImGui::TreePop();
												}
												ImGui::EndDisabled();
											}
											break;

										case Unreal::Actor::E_ActorKind::Pawn:
											if (SDK::APawn* pawn = static_cast<SDK::APawn*>(actor.reference))
											{
#ifdef SOFT_PATH
												ImGui::SetFontTitle();
												ImGui::Text("Pawn Animation");
												ImGui::SetFontSmall();
												ImGui::Text("Dynamic Animation playing by soft path, for example \"/Game/Character/AnimAsset_Jump.AnimAsset_Jump\".");
												ImGui::SetFontRegular();

												if (ImGui::TreeNode("Details##PawnAnimation"))
												{
													ImGui::SetFontTitle();
													ImGui::Text("Animation Montage");
													ImGui::SetFontRegular();
													ImGui::Text("Animation Montage Path:");
													ImGui::SameLine();
													ImGui::InputText("##PawnAnimationMontage", Features::PawnAnimation::animationMontagePathBuffer, Features::PawnAnimation::animationMontagePathBufferSize);

													ImGui::Text("Start At:              ");
													ImGui::SameLine();
													ImGui::InputFloat("##PawnAnimationMontageStartAt", &Features::PawnAnimation::animationMontageStartAt, 0.1f, 1.0f);

													ImGui::Text("Play Rate:             ");
													ImGui::SameLine();
													ImGui::InputFloat("##PawnAnimationMontagePlayRate", &Features::PawnAnimation::animationMontagePlayRate, 0.1f, 1.0f);

													ImGui::Checkbox("Stop All Montages", &Features::PawnAnimation::animationMontageStopAllMontages);

													if (ImGui::Button("Play##PawnAnimationMontage"))
													{
														PlayActionSound(Unreal::Pawn::PlayAnimationMontage(pawn, Unreal::String::CString_ToFString(Features::PawnAnimation::animationMontagePathBuffer), Features::PawnAnimation::animationMontageStartAt, Features::PawnAnimation::animationMontagePlayRate, Features::PawnAnimation::animationMontageStopAllMontages));
													}

													ImGui::NewLine();

													ImGui::SetFontTitle();
													ImGui::Text("Animation Asset");
													ImGui::SetFontRegular();
													ImGui::Text("Animation Path:");
													ImGui::SameLine();
													ImGui::InputText("##PawnAnimation", Features::PawnAnimation::animationPathBuffer, Features::PawnAnimation::animationPathBufferSize);

													ImGui::Checkbox("Animation Looping", &Features::PawnAnimation::animationLooping);

													if (ImGui::Button("Play##PawnAnimation"))
													{
														PlayActionSound(Unreal::Pawn::PlayAnimation(pawn, Unreal::String::CString_ToFString(Features::PawnAnimation::animationPathBuffer), Features::PawnAnimation::animationLooping));
													}

													ImGui::TreePop();
												}

												ImGui::NewLine();
#endif

												ImGui::SetFontTitle();
												ImGui::Text("Pawn Actions");
												ImGui::SetFontRegular();

												if (ImGui::TreeNode("Details##PawnActions"))
												{
													if (ImGui::Button("Possess"))
													{
														if (pawn)
														{
															SDK::APlayerController* playerController = Unreal::PlayerController::Get();
															if (playerController)
															{
																playerController->Possess(pawn);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														else
															PlayActionSound(false);
													}

													ImGui::TreePop();
												}
											}
											break;

										case Unreal::Actor::E_ActorKind::TextRender:
											if (SDK::ATextRenderActor* textRender = static_cast<SDK::ATextRenderActor*>(actor.reference))
											{
												ImGui::SetFontTitle();
												ImGui::Text("Text Render Settings");
												ImGui::SetFontRegular();

												ImGui::BeginDisabled(textRender->TextRender == nullptr);
												if (ImGui::TreeNode("Details##TextRender"))
												{
													if (SDK::UTextRenderComponent* textRenderComponent = textRender->TextRender)
													{
														ImGui::Text("Content");
														static const size_t textRenderContentBufferSize = 255;
														static char textRenderContentBuffer[textRenderContentBufferSize] = {};
														if (ImGui::Button("Get##TextRenderContent"))
														{
															if (textRenderComponent)
															{
																strcpy_s(textRenderContentBuffer, textRenderComponent->Text.ToString().c_str());
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputText("##TextRenderContent", textRenderContentBuffer, textRenderContentBufferSize);

														ImGui::NewLine();

														ImGui::Text("Font Size");
														static float textRenderFontSize = 26.0f;
														if (ImGui::Button("Get##TextRenderFontSize"))
														{
															if (textRenderComponent)
															{
																textRenderFontSize = textRenderComponent->WorldSize;
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
														ImGui::SameLine();
														ImGui::InputFloat("##TextRenderFontSize", &textRenderFontSize, 1.0f, 10.0f);
														ImGui::SameLine();
														if (ImGui::Button("Set##TextRenderFontSize"))
														{
															if (textRenderComponent)
															{
																textRenderComponent->SetWorldSize(textRenderFontSize);
																PlayActionSound(true);
															}
															else
																PlayActionSound(false);
														}
													}
													else
														ImGui::Text("Text Render Component Doesn't Exist!");

													ImGui::TreePop();
												}

												ImGui::EndDisabled();
											}
											break;
									}
								}

								ImGui::NewLine();
#endif

								ImGui::SetFontTitle();
								ImGui::Text("Components");
								ImGui::SetFontRegular();
								if (ImGui::TreeNode("Details##Components"))
								{

									ImGui::InputText("Search Filter##Components", Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterBufferSize);
									ImGui::SameLine();
									ImGui::Spacing();
									ImGui::SameLine();
									ImGui::Checkbox("Case Sensitive##Components", &Features::ActorsList::componentsFilterCaseSensitive);

									ImGui::NewLine();

									std::vector<Unreal::ActorComponent::DataStructure> filteredComponents = Unreal::ActorComponent::FilterByObjectName(actor.components, Features::ActorsList::componentsFilterBuffer, Features::ActorsList::componentsFilterCaseSensitive);
									for (Unreal::ActorComponent::DataStructure& component : filteredComponents) // <-- Reference!
									{
										if (ImGui::TreeNode(component.objectName.c_str()))
										{
											ImGui::Text("Component Class: %s", component.className.c_str());
											ImGui::Text("Component Object: %s", component.objectName.c_str());

											ImGui::NewLine();

											ImGui::TextBoolColored("Is Active:", component.isActive);
											ImGui::TextBoolColored("Auto Activate:", component.autoActivate);
											ImGui::TextBoolColored("Editor Only:", component.editorOnly);
											if (ImGui::Button("Activate"))
											{
												if (component.reference)
												{
													component.reference->Activate(false);
													component.isActive = true;
													PlayActionSound(true);
												}
												else
													PlayActionSound(false);
											}
											ImGui::SameLine();
											if (ImGui::Button("Reset"))
											{
												if (component.reference)
												{
													component.reference->Activate(true);
													component.isActive = true;
													PlayActionSound(true);
												}
												else
													PlayActionSound(false);
											}
											ImGui::SameLine();
											if (ImGui::Button("Deactivate"))
											{
												if (component.reference)
												{
													component.reference->Deactivate();
													component.isActive = false;
													PlayActionSound(true);
												}
												else
													PlayActionSound(false);
											}

											ImGui::NewLine();

											ImGui::TextBoolColored("Net Addressible:", component.netAddressible);
											ImGui::TextBoolColored("Replicates:", component.replicates);

											ImGui::NewLine();

											ImGui::Text("Creation Method: %d", component.creationMethod);

											ImGui::TreePop();
										}
									}

									ImGui::TreePop();
								}

								ImGui::PopID();
								ImGui::TreePop();
							}
						}
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::Text("Widgets");
					ImGui::SetFontRegular();
					if (ImGui::CollapsingHeader("Details##Widgets"))
					{
#ifdef SOFT_PATH
						ImGui::SetFontTitle();
						ImGui::Text("Widget Construct");
						ImGui::SetFontSmall();
						ImGui::Text("Dynamic Widget construction by soft path, for example \"/Game/Widgets/WBP_MainMenu.WBP_MainMenu_C\".");
						ImGui::Text("Feature supports combined input using the '|' separator between paths.");
						ImGui::SetFontRegular();

						if (ImGui::TreeNode("Details##WidgetConstruct"))
						{
							ImGui::Text("Widget Path:");
							ImGui::SameLine();
							ImGui::InputText("##WidgetConstruct", Features::WidgetConstruct::widgetPathBuffer, Features::WidgetConstruct::widgetPathBufferSize);

							ImGui::Text("Z Order:    ");
							ImGui::SameLine();
							ImGui::InputInt("##WidgetZOrder", &Features::WidgetConstruct::zOrder, 1, 10);

							if (ImGui::Button("Construct Widget##WidgetConstruct"))
							{
								std::vector<SDK::FString> widgetPathCollection = Unreal::String::Split(Features::WidgetConstruct::widgetPathBuffer, '|');
								if (widgetPathCollection.size() > 0)
								{
									bool anyWidgetConstructed = false;

									for (SDK::FString& widgetPath : widgetPathCollection) // <-- Reference!
									{
										if (SDK::UUserWidget* widgetReference = Unreal::UserWidget::SoftConstruct(widgetPath))
										{
											widgetReference->AddToViewport(Features::WidgetConstruct::zOrder);
											anyWidgetConstructed = true;
										}
									}

									PlayActionSound(anyWidgetConstructed);
								}
								else
									PlayActionSound(false);
							}

							ImGui::TreePop();
						}

						ImGui::NewLine();
#endif

						if (ImGui::Button("Update##Widgets"))
						{
							Features::WidgetsList::Update();
							PlayActionSound(true);
						}
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::InputText("Search Filter##Widgets", Features::WidgetsList::filterBuffer, Features::WidgetsList::filterBufferSize);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::Checkbox("Case Sensitive##Widgets", &Features::WidgetsList::filterCaseSensitive);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::ObjectFilterModeComboBox("##Widgets", &Features::WidgetsList::filterMode);
						ImGui::SameLine();
						ImGui::Spacing();
						ImGui::SameLine();
						ImGui::Checkbox("Top Level Only##Widgets", &Features::WidgetsList::filterTopLevelOnly);

						ImGui::NewLine();

						if (ImGui::Button("Set Visible (All)##Widgets"))
						{
							Features::WidgetsList::storedWidgetsVisibility.clear();
							bool anyWidgetAffected = false;

							for (Unreal::UserWidget::DataStructure widget : Features::WidgetsList::filteredWidgets)
							{
								if (widget.reference == nullptr)
									continue;

								Features::WidgetsList::storedWidgetsVisibility.push_back({ widget.reference, widget.visibility });
								widget.reference->SetVisibility(SDK::ESlateVisibility::Visible);

								anyWidgetAffected = true;
							}

							PlayActionSound(anyWidgetAffected);
						}
						ImGui::SameLine();
						if (ImGui::Button("Set Hidden (All)##Widgets"))
						{
							Features::WidgetsList::storedWidgetsVisibility.clear();
							bool anyWidgetAffected = false;

							for (Unreal::UserWidget::DataStructure widget : Features::WidgetsList::filteredWidgets)
							{
								if (widget.reference == nullptr)
									continue;

								Features::WidgetsList::storedWidgetsVisibility.push_back({ widget.reference, widget.visibility });
								widget.reference->SetVisibility(SDK::ESlateVisibility::Hidden);

								anyWidgetAffected = true;
							}

							PlayActionSound(anyWidgetAffected);
						}
						ImGui::SameLine();
						if (ImGui::Button("Restore Previous State##Widgets"))
						{
							bool anyWidgetAffected = false;

							for (std::pair<SDK::UUserWidget*, SDK::ESlateVisibility> widgetVisibility : Features::WidgetsList::storedWidgetsVisibility)
							{
								if (widgetVisibility.first == nullptr)
									continue;

								widgetVisibility.first->SetVisibility(widgetVisibility.second);
								anyWidgetAffected = true;
							}

							PlayActionSound(anyWidgetAffected);
						}

						ImGui::NewLine();

						switch (Features::WidgetsList::filterMode)
						{
							case ImGui::E_ObjectFilterMode::ClassName:
								Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
								break;

							case ImGui::E_ObjectFilterMode::ObjectName:
								Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
								break;

							case ImGui::E_ObjectFilterMode::All:
								Features::WidgetsList::filteredWidgets = Unreal::UserWidget::FilterByClassAndObjectName(Features::WidgetsList::widgets, Features::WidgetsList::filterBuffer, Features::WidgetsList::filterCaseSensitive, Features::WidgetsList::filterTopLevelOnly);
								break;
						}

						for (Unreal::UserWidget::DataStructure& widget : Features::WidgetsList::filteredWidgets) // <-- Reference!
						{
							if (ImGui::TreeNode(widget.objectName.c_str()))
							{
								ImGui::PushID(widget.objectName.c_str());

								ImGui::BeginDisabled(std::strcmp(Features::ActorsList::filterBuffer, widget.objectName.c_str()) == 0);
								if (ImGui::Button("Focus On"))
								{
									std::snprintf(Features::WidgetsList::filterBuffer, sizeof(Features::WidgetsList::filterBuffer), widget.objectName.c_str());
									Features::WidgetsList::filterMode = ImGui::E_ObjectFilterMode::ObjectName;

									PlayActionSound(true);
								}
								ImGui::EndDisabled();

								ImGui::NewLine();

								ImGui::Text("Widget Class: %s", widget.className.c_str());
								ImGui::Text("Widget Object: %s", widget.objectName.c_str());

								ImGui::NewLine();

								ImGui::Text("Parent: %s", widget.parent ? widget.parent->GetFullName().c_str() : "None");

								ImGui::NewLine();

								ImGui::TextBoolColored("Is Top Level:", widget.isInViewport);
								ImGui::Text("Visibility: %d", widget.visibility);
								ImGui::SameLine();
								ImGui::TextHint("ESlateVisibility\n\n0 - Visible\n1 - Collapsed\n2 - Hidden\n3 - HitTestInvisible\n4 - SelfHitTestInvisible");
								static int32_t customVisibility = 0;
								ImGui::SliderInt("##CustomVisibility", &customVisibility, 0, 4);
								ImGui::SameLine();
								if (ImGui::Button("Set##Visibility"))
								{
									if (widget.reference)
									{
										widget.reference->SetVisibility(static_cast<SDK::ESlateVisibility>(customVisibility));
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

								ImGui::NewLine();

								if (ImGui::Button("Remove From Parent"))
								{
									if (widget.reference)
									{
										widget.reference->RemoveFromParent();
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}
								ImGui::SameLine();
								if (ImGui::Button("Remove From Viewport"))
								{
									if (widget.reference)
									{
										widget.reference->RemoveFromViewport();
										PlayActionSound(true);
									}
									else
										PlayActionSound(false);
								}

								ImGui::PopID();
								ImGui::TreePop();
							}
						}
					}

					ImGui::CategorySeparator();

					if (Features::Debug::wasProjectNameObtained)
						ImGui::Text("Project Name: %s", Features::Debug::projectName.c_str());

					if (Features::Debug::wasProjectPlatformObtained)
						ImGui::Text("Project Platform: %s", Features::Debug::projectPlatform.c_str());

					if (Features::Debug::wasUsernameObtained)
						ImGui::Text("Username: %s", Features::Debug::username.c_str());

					if (Features::Debug::wasCommandLineObtained)
					{
						ImGui::ReadOnlyInputText("Command Line:", Features::Debug::commandLine.c_str(), true);
					}

					ImGui::MenuSpacer();
				}

				ImGui::EndMenu();
			}




			SDK::UWorld* world = SDK::UWorld::GetWorld();
			SDK::ULevel* persistentLevel = world ? world->PersistentLevel : nullptr;
			SDK::AWorldSettings* worldSettings = persistentLevel ? persistentLevel->WorldSettings : nullptr;

			bool worldObtained = world && persistentLevel && worldSettings;
			ImGui::BeginDisabled(worldObtained == false);
			if (ImGui::BeginMenu("World"))
			{
				if (worldObtained)
				{
#ifdef SOFT_PATH
					ImGui::SetFontTitle();
					ImGui::Text("Level Instance");
					ImGui::SetFontSmall();
					ImGui::Text("Dynamic level loading by Level path, for example \"/Game/OpenWorld/Tile_X2Y8.Tile_X2Y8\".");
					ImGui::Text("Feature supports combined input using the '|' separator between paths.");
					ImGui::SetFontRegular();
					
					if (ImGui::TreeNode("Details##LoadLevelInstance"))
					{
						ImGui::Text("Level Path:    ");
						ImGui::SameLine();
						ImGui::InputText("##LoadLevelInstance", Features::LoadLevelInstance::levelPathBuffer, Features::LoadLevelInstance::levelPathBufferSize);

						ImGui::Text("Level Location:");
						ImGui::SameLine();
						ImGui::InputFloat3("##LevelLocationOffset", Features::LoadLevelInstance::locationOffset);

						ImGui::Text("Level Rotation:");
						ImGui::SameLine();
						ImGui::InputFloat3("##LevelRotationOffset", Features::LoadLevelInstance::rotationOffset);

						if (ImGui::Button("Load Level##LoadLevelInstance"))
						{
							std::vector<SDK::FString> levelPathCollection = Unreal::String::Split(Features::LoadLevelInstance::levelPathBuffer, '|');
							if (levelPathCollection.size() > 0)
							{
								bool anyLevelLoaded = false;
								SDK::FVector locationOffset = SDK::FVector(Features::LoadLevelInstance::locationOffset[0], Features::LoadLevelInstance::locationOffset[1], Features::LoadLevelInstance::locationOffset[2]);
								SDK::FRotator rotationOffset = SDK::FRotator(Features::LoadLevelInstance::rotationOffset[0], Features::LoadLevelInstance::rotationOffset[1], Features::LoadLevelInstance::rotationOffset[2]);

								for (SDK::FString levelPath : levelPathCollection)
								{
									if (Unreal::LevelStreaming::LoadLevelInstance(levelPath, locationOffset, rotationOffset))
										anyLevelLoaded = true;
								}

								PlayActionSound(anyLevelLoaded);
							}
							else
								PlayActionSound(false);
						}

						ImGui::TreePop();
					}

#ifdef LEVEL_SEQUENCE
					ImGui::NewLine();

					ImGui::SetFontTitle();
					ImGui::Text("Level Sequence");
					ImGui::SetFontSmall();
					ImGui::Text("Dynamic level sequence playing by soft path, for example \"/Game/OpenWorld/Sequences/LS_TowerExplosion.LS_TowerExplosion\".");
					ImGui::Text("Feature supports combined input using the '|' separator between paths.");
					ImGui::SetFontRegular();

					if (ImGui::TreeNode("Details##PlayLevelSequence"))
					{
						ImGui::Text("Level Sequence Path:");
						ImGui::SameLine();
						ImGui::InputText("##PlayLevelSequence", Features::PlayLevelSequence::levelSequencePathBuffer, Features::PlayLevelSequence::levelSequencePathBufferSize);

						ImGui::Text("Start Time:         ");
						ImGui::SameLine();
						ImGui::InputFloat("##LevelSequenceStartTime", &Features::PlayLevelSequence::startTime, 0.1f, 1.0f);

						ImGui::Text("Play Rate:          ");
						ImGui::SameLine();
						ImGui::InputFloat("##LevelSequencePlayRate", &Features::PlayLevelSequence::playRate, 0.1f, 1.0f);

						ImGui::Text("Loop Count:         ");
						ImGui::SameLine();
						ImGui::InputInt("##LevelSequenceLoopCount", &Features::PlayLevelSequence::loopCount, 1, 10);

						if (ImGui::Button("Create Level Sequence##PlayLevelSequence"))
						{
							std::vector<SDK::FString> levelSequencePathCollection = Unreal::String::Split(Features::PlayLevelSequence::levelSequencePathBuffer, '|');
							if (levelSequencePathCollection.size() > 0)
							{
								bool anySequenceCreated = false;

								for (SDK::FString levelSequencePath : levelSequencePathCollection)
								{
									if (Unreal::Level::CreateLevelSequence(levelSequencePath, Features::PlayLevelSequence::startTime, Features::PlayLevelSequence::playRate, Features::PlayLevelSequence::loopCount))
										anySequenceCreated = true;
								}

								PlayActionSound(anySequenceCreated);
							}
							else
								PlayActionSound(false);
						}

						ImGui::TreePop();
					}
#endif
					ImGui::NewLine();
#endif

					ImGui::SetFontTitle();
					ImGui::Text("Gravity");
					ImGui::SetFontRegular();
					if (ImGui::TreeNode("Details##WorldGravity"))
					{
						bool globalGravitySet = worldSettings->bGlobalGravitySet == 1;
						ImGui::Checkbox("Global Gravity Set", &globalGravitySet);
						worldSettings->bGlobalGravitySet = globalGravitySet ? 1 : 0;

						ImGui::BeginDisabled(globalGravitySet == false);
						ImGui::InputFloat("Global Gravity", &worldSettings->GlobalGravityZ, 0.1, 1.0);
						ImGui::EndDisabled();

						bool worldGravitySet = worldSettings->bWorldGravitySet == 1;
						ImGui::Checkbox("World Gravity Set", &worldGravitySet);
						worldSettings->bWorldGravitySet = worldGravitySet ? 1 : 0;

						ImGui::BeginDisabled(worldGravitySet == false);
						ImGui::InputFloat("World Gravity", &worldSettings->WorldGravityZ, 0.1, 1.0);
						ImGui::EndDisabled();

						ImGui::TreePop();
					}

					ImGui::CategorySeparator();

					ImGui::SetFontTitle();
					ImGui::Text("Time");
					ImGui::SetFontRegular();
					if (ImGui::TreeNode("Details##WorldTime"))
					{
						if (ImGui::Button("Game Pause"))
						{
							PlayActionSound(SDK::UGameplayStatics::SetGamePaused(world, true));
						}
						ImGui::SameLine();
						if (ImGui::Button("Game Unpause"))
						{
							PlayActionSound(SDK::UGameplayStatics::SetGamePaused(world, false));
						}

						ImGui::NewLine();

						ImGui::InputFloat("Minimum Time Dilation", &worldSettings->MinGlobalTimeDilation, 0.1, 1.0);
						ImGui::InputFloat("Maximum Time Dilation", &worldSettings->MaxGlobalTimeDilation, 0.1, 1.0);
						double timeDilation = worldSettings->TimeDilation;
						ImGui::InputDouble("Time Dilation", &timeDilation, 0.1, 1.0);
						worldSettings->TimeDilation = std::clamp(timeDilation, (double)worldSettings->MinGlobalTimeDilation, (double)worldSettings->MaxGlobalTimeDilation);

						ImGui::NewLine();

						ImGui::InputFloat("Demo Time Dilation", &worldSettings->DemoPlayTimeDilation, 0.1, 1.0);

						ImGui::TreePop();
					}

					ImGui::CategorySeparator();

					bool enableAISystem = worldSettings->bEnableAISystem == 1;
					ImGui::Checkbox("Enable AI System", &enableAISystem);
					worldSettings->bEnableAISystem = enableAISystem ? 1 : 0;

					bool enableNavigationSystem = worldSettings->bEnableNavigationSystem == 1;
					ImGui::Checkbox("Enable Navigation System", &enableNavigationSystem);
					worldSettings->bEnableNavigationSystem = enableNavigationSystem ? 1 : 0;

					ImGui::NewLine();

					ImGui::InputFloat("Kill Volume Z", &worldSettings->KillZ, 0.1, 1.0);
				}
				else
				{
					if (world == nullptr)
						ImGui::Text("World Doesn't Exist!");
					else if (persistentLevel == nullptr)
						ImGui::Text("Persistent Level Doesn't Exist!");
					else if (worldSettings == nullptr)
						ImGui::Text("World Settings Doesn't Exist!");
					else
						ImGui::Text("Something Went Wrong.");
				}

				ImGui::MenuSpacer();

				ImGui::EndMenu();
			}
			ImGui::EndDisabled();




			SDK::APlayerController* playerController = Unreal::PlayerController::Get();
			SDK::ACharacter* character = playerController ? playerController->Character : nullptr;
			SDK::UCharacterMovementComponent* movementComponent = (character && character->CharacterMovement) ? character->CharacterMovement : nullptr;

			bool characterObtained = playerController && character && movementComponent;
			ImGui::BeginDisabled(characterObtained == false);
			if (ImGui::BeginMenu("Character"))
			{
				if (characterObtained)
				{
					ImGui::Text("Character: %s", character->GetFullName().c_str());
					SDK::FVector characterLocation = character->K2_GetActorLocation();
					ImGui::TextVectorColored("Location:", characterLocation);
					SDK::FRotator characterRotation = character->K2_GetActorRotation();
					ImGui::TextRotatorColored("Rotation:", characterRotation);

					ImGui::NewLine();

					ImGui::SetFontTitle();
					ImGui::Text("Movement");
					ImGui::SetFontRegular();
					if (ImGui::TreeNode("Details##CharacterMovement"))
					{
						if (movementComponent->bCheatFlying)
							ImGui::Text("Character Is In %s Mode", character->bActorEnableCollision ? "Fly" : "Ghost");
						else
						{
							SDK::EMovementMode movementMode = movementComponent->MovementMode;
							switch (movementMode)
							{
							case SDK::EMovementMode::MOVE_Walking:
								ImGui::Text("Character Is Walking");
								break;

							case SDK::EMovementMode::MOVE_NavWalking:
								ImGui::Text("Character Is Nav Walking");
								break;

							case SDK::EMovementMode::MOVE_Falling:
								ImGui::Text("Character Is Falling");
								break;

							case SDK::EMovementMode::MOVE_Swimming:
								ImGui::Text("Character Is Swimming");
								break;

							case SDK::EMovementMode::MOVE_Flying:
								ImGui::Text("Character Is Flying");
								break;

							default:
								ImGui::Text("Character Is In %d Mode", movementMode);
								break;
							}
						}
						ImGui::Text("Custom Movement Mode: %d", movementComponent->CustomMovementMode);

						ImGui::NewLine();

						/* 0 corresponds for default vertical size. */
						static const ImVec2 buttonSize = { 128.0f, 0.0f };

						if (ImGui::Button("Ghost", buttonSize))
						{
							Features::CharacterMovement::Ghost();
						}
						ImGui::SameLine();
						if (ImGui::Button("Fly", buttonSize))
						{
							Features::CharacterMovement::Fly();
						}
						ImGui::SameLine();
						if (ImGui::Button("Walk", buttonSize))
						{
							Features::CharacterMovement::Walk();
						}

						ImGui::NewLine();

						ImGui::KeyBindingInput("Ghost Key Binding:##Ghost", &Keybindings::characterMovement_Ghost);
						ImGui::KeyBindingInput("Fly Key Binding:  ##Fly", &Keybindings::characterMovement_Fly);
						ImGui::KeyBindingInput("Walk Key Binding: ##Walk", &Keybindings::characterMovement_Walk);

						ImGui::NewLine();

						if (ImGui::Button("Enable Input"))
						{
							if (character)
							{
								character->EnableInput(playerController);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}
						ImGui::SameLine();
						if (ImGui::Button("Disable Input"))
						{
							if (character)
							{
								character->DisableInput(playerController);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}

						if (ImGui::Button("Ignore Move Input"))
						{
							if (playerController)
							{
								playerController->SetIgnoreMoveInput(true);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}
						ImGui::SameLine();
						if (ImGui::Button("Do Not Ignore Move Input"))
						{
							if (playerController)
							{
								playerController->SetIgnoreMoveInput(false);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}

						if (ImGui::Button("Ignore Look Input"))
						{
							if (playerController)
							{
								playerController->SetIgnoreLookInput(true);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}
						ImGui::SameLine();
						if (ImGui::Button("Do Not Ignore Look Input"))
						{
							if (playerController)
							{
								playerController->SetIgnoreLookInput(false);
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}

						if (ImGui::Button("Input Mode: Game Only"))
						{
							if (playerController)
							{
#ifdef UE5
								SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController, true);
#else
								SDK::UWidgetBlueprintLibrary::SetInputMode_GameOnly(playerController);
#endif
								PlayActionSound(true);
							}
							else
								PlayActionSound(false);
						}

						ImGui::NewLine();

						ImGui::SetFontTitle();
						ImGui::Text("Directional Movement");
						ImGui::SetFontSmall();
						ImGui::Text("When the character is Flying or in Ghost mode, moving forward teleports them in the direction the camera is facing,");
						ImGui::Text("allowing for quick and easy navigation through the world.");
						ImGui::SetFontRegular();
						ImGui::BeginDisabled(movementComponent->bCheatFlying == false);
						if (ImGui::TreeNode("Settings##DirectionalMovement"))
						{
							if (ImGui::Checkbox("Enabled##DirectionalMovement", &Features::DirectionalMovement::enabled))
							{
								if (Features::DirectionalMovement::enabled)
									Features::DirectionalMovement::StartThread();
								else
									Features::DirectionalMovement::InvalidateThread();
							}
							ImGui::InputDouble("Movement Step##DirectionalMovement", &Features::DirectionalMovement::step, 0.1, 1.0);
							if (ImGui::InputDouble("Movement Delay##DirectionalMovement", &Features::DirectionalMovement::delay, 0.01, 0.1))
							{
								if (Features::DirectionalMovement::delay < 0.001)
									Features::DirectionalMovement::delay = 0.001;
							}

							ImGui::TreePop();
						}
						ImGui::EndDisabled();

						ImGui::CategorySeparator();

						ImGui::InputFloat("Gravity Scale", &movementComponent->GravityScale, 0.1f, 1.0f);

						ImGui::NewLine();

						ImGui::InputFloat("Max Acceleration", &movementComponent->MaxAcceleration, 1.0f, 10.0f);
						ImGui::InputFloat("Max Step Height", &movementComponent->MaxStepHeight, 1.0f, 10.0f);
						ImGui::InputFloat("Weight", &movementComponent->Mass, 1.0f, 10.0f);

						ImGui::NewLine();

						ImGui::InputFloat("Max Walk Speed", &movementComponent->MaxWalkSpeed, 1.0f, 10.0f);
						ImGui::InputFloat("Max Crouch Speed", &movementComponent->MaxWalkSpeedCrouched, 1.0f, 10.0f);
						ImGui::InputFloat("Max Swim Speed", &movementComponent->MaxSwimSpeed, 1.0f, 10.0f);
						ImGui::InputFloat("Max Fly Speed", &movementComponent->MaxFlySpeed, 1.0f, 10.0f);
						ImGui::InputFloat("Max Custom Movement Speed", &movementComponent->MaxCustomMovementSpeed, 1.0f, 10.0f);

						ImGui::NewLine();

						ImGui::TextFloatColored("Walkable Floor Z:", movementComponent->WalkableFloorZ);

						ImGui::CategorySeparator();

						if (ImGui::Button("Jump"))
						{
							Features::CharacterMovement::Jump();
						}
						ImGui::InputInt("Jump Limit", &character->JumpMaxCount, 1, 1);
						ImGui::InputFloat("Jump Height", &movementComponent->JumpZVelocity, 0.1, 1.0);
						ImGui::KeyBindingInput("Jump Key Binding:##Jump", &Keybindings::characterMovement_Jump);

						ImGui::NewLine();

						if (ImGui::Button("Launch"))
						{
							Features::CharacterMovement::Launch();
						}
						ImGui::InputFloat3("Launch Velocity", Features::CharacterMovement::launchVelocity);
						ImGui::KeyBindingInput("Launch Key Binding:##Launch", &Keybindings::characterMovement_Launch);

						ImGui::NewLine();

						if (ImGui::Button("Dash"))
						{
							Features::CharacterMovement::Dash();
						}
						ImGui::InputDouble("Dash Strength", &Features::CharacterMovement::dashStrength, 0.1, 1.0);
						ImGui::KeyBindingInput("Dash Key Binding:##Dash", &Keybindings::characterMovement_Dash);

						ImGui::TreePop();
					}

					ImGui::CategorySeparator();

					SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
					ImGui::SetFontTitle();
					ImGui::Text("Camera");
					ImGui::SetFontRegular();
					ImGui::BeginDisabled(cameraManager == nullptr);
					if (ImGui::TreeNode("Details##Camera"))
					{
						if (cameraManager)
						{
							/* 0 corresponds for default vertical size. */
							static const ImVec2 buttonSize = { 204.0f, 0.0f };

							if (ImGui::Button("Start Fade", buttonSize))
							{
								Features::Camera::StartFade();
							}
							ImGui::SameLine();
							if (ImGui::Button("Stop Fade", buttonSize))
							{
								Features::Camera::StopFade();
							}

							if (ImGui::InputFloat("Fade From Alpha", &Features::Camera::fadeFromAlpha, 0.01f, 0.1f))
							{
								if (Features::Camera::fadeFromAlpha < 0.0f)
									Features::Camera::fadeFromAlpha = 0.0f;

								if (Features::Camera::fadeFromAlpha > 1.0f)
									Features::Camera::fadeFromAlpha = 1.0f;
							}

							if (ImGui::InputFloat("Fade To Alpha", &Features::Camera::fadeToAlpha, 0.01f, 0.1f))
							{
								if (Features::Camera::fadeToAlpha < 0.0f)
									Features::Camera::fadeToAlpha = 0.0f;

								if (Features::Camera::fadeToAlpha > 1.0f)
									Features::Camera::fadeToAlpha = 1.0f;
							}

							ImGui::InputFloat("Fade Duration", &Features::Camera::fadeDuration, 0.1f, 1.0f);
							ImGui::ColorPicker4("Fade Color", Features::Camera::fadeColor);

							ImGui::NewLine();

							ImGui::Checkbox("Fade Audio", &Features::Camera::fadeAudio);
							ImGui::Checkbox("Fade Persistent", &Features::Camera::fadePersistent);

							ImGui::NewLine();

							ImGui::KeyBindingInput("Start Fade Key Binding:", &Keybindings::characterCamera_StartFade);
							ImGui::KeyBindingInput("Stop Fade Key Binding:", &Keybindings::characterCamera_StopFade);
						}
						else
							ImGui::Text("Camera Manager Doesn't Exist!");

						ImGui::TreePop();
					}
					ImGui::EndDisabled();

					ImGui::MenuSpacer();
				}
				else
				{
					if (playerController == nullptr)
						ImGui::Text("Player Controller Doesn't Exist!");
					else if (character == nullptr)
						ImGui::Text("Character Doesn't Exist!");
					else if (movementComponent == nullptr)
						ImGui::Text("Movement Component Doesn't Exist!");
					else
						ImGui::Text("Something Went Wrong.");
				}

				ImGui::EndMenu();
			}
			ImGui::EndDisabled();




			if (ImGui::BeginMenu("Settings"))
			{
				ImGui::Checkbox("Enable Sound", &Features::Menu::enableSound);
				ImGui::Checkbox("Enable Console Output", &Features::Menu::enableConsoleOutput);

				ImGui::EndMenu();
			}




			ImGui::Text(" | ");




			ImGui::Text("Console:");
			ImGui::SameLine();
			ImGui::PushItemWidth(320);
			ImGui::InputText("##Console", Features::Console::consoleBuffer, Features::Console::consoleBufferSize);
			ImGui::SameLine();
			if (ImGui::Button("Execute"))
			{
				SDK::FString command = Unreal::String::CString_ToFString(Features::Console::consoleBuffer);
				if (command.Num() > 0)
				{
					GUI::PlayActionSound(Unreal::Console::Execute(command));
				}
				else
					GUI::PlayActionSound(false);
			}
			ImGui::PopItemWidth();


			ImGui::EndMainMenuBar();
		}
	}


#ifdef ACTOR_TRACE
	if (Features::ActorTrace::enabled)
	{
		if (Features::ActorTrace::showOnScreen)
		{
#ifdef UE5
			const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::object.objectName.c_str() : "No Object Traced";
#else
			const char* labelText = Features::ActorTrace::traceHit ? Features::ActorTrace::actor.objectName.c_str() : "No Actor Traced";
#endif
			ImVec2 labelSize = ImGui::CalcTextSize(labelText);

			ImVec2 labelPosition = ImVec2
			(
				/*
					Horizontal: ImGui Viewport center;
					Vertical: ImGui Viewport bottom - 12 pixels.

					Flooring the values allows to avoid potential subpixel conflicts.
				*/
				floorf(iViewPortPosition.x + (iViewPortSize.x - labelSize.x) * 0.5f),
				floorf(iViewPortSize.y - labelSize.y - 12.0f)
			);

			iDrawList->AddText(labelPosition, ImGui::GetColorU32(ImGuiCol_Text), labelText);
		}

		if (Features::ActorTrace::showLineTrace && Features::ActorTrace::traceCast)
		{
			SDK::FVector2D screenStartPosition;
			SDK::FVector2D screenEndPosition;

			/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
			SDK::APlayerController* playerController = Unreal::PlayerController::Get();
			bool startPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceStartLocation, &screenStartPosition, false);
			bool endPositionProjected = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, Features::ActorTrace::traceEndLocation, &screenEndPosition, false);

			/* Inverse Normalize RGBA values set by color picker. */
			ImU32 color = ImGui::ColorConvertFloat4ToU32(ImVec4(Features::ActorTrace::traceColor[0], Features::ActorTrace::traceColor[1], Features::ActorTrace::traceColor[2], Features::ActorTrace::traceColor[3]));

			static float traceStartCircleRadius;
			if (startPositionProjected)
				traceStartCircleRadius = Features::ActorTrace::traceThickness * 1.5f;

			static float traceEndCircleRadius;
			static float traceCrossSize;
			if (endPositionProjected)
			{
				traceEndCircleRadius = Features::ActorTrace::traceThickness * 1.75f;
				traceCrossSize = 8.0f + (Features::ActorTrace::traceThickness * 0.5f);
			}

			/* Both start and end position are within player view. */
			if (startPositionProjected && endPositionProjected)
			{
				ImVec2 startPosition = { (float)screenStartPosition.X, (float)screenStartPosition.Y };
				ImVec2 endPosition = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				/* Draw the trace. */
				iDrawList->AddLine(startPosition, endPosition, color, Features::ActorTrace::traceThickness);

				/* Draw a hollow circle to mark position where trace was sent from. */
				iDrawList->AddCircle(startPosition, traceStartCircleRadius, color);

				/*
					If trace has hit something, draw a cross to mark position where the trace hit;
					Otherwise draw a filled circle to mark position where the trace ends.
				*/
				if (Features::ActorTrace::traceHit)
				{
					iDrawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y - traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					iDrawList->AddLine({ endPosition.x - traceCrossSize, endPosition.y + traceCrossSize }, { endPosition.x + traceCrossSize, endPosition.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					iDrawList->AddCircleFilled(endPosition, traceEndCircleRadius, color);
			}
			/* Only start position is within player view. */
			else if (startPositionProjected)
			{
				ImVec2 position = { (float)screenStartPosition.X, (float)screenStartPosition.Y };

				iDrawList->AddCircle(position, traceStartCircleRadius, color);
			}
			/* Only end position is within player view. */
			else if (endPositionProjected)
			{
				ImVec2 position = { (float)screenEndPosition.X, (float)screenEndPosition.Y };

				if (Features::ActorTrace::traceHit)
				{
					iDrawList->AddLine({ position.x - traceCrossSize, position.y - traceCrossSize }, { position.x + traceCrossSize, position.y + traceCrossSize }, color, Features::ActorTrace::traceThickness);
					iDrawList->AddLine({ position.x - traceCrossSize, position.y + traceCrossSize }, { position.x + traceCrossSize, position.y - traceCrossSize }, color, Features::ActorTrace::traceThickness);
				}
				else
					iDrawList->AddCircleFilled(position, traceEndCircleRadius, color);
			}
		}
	}
#endif




#ifdef ACTORS_TRACKING
	if (Features::ActorsTracker::enabled)
	{
		SDK::APlayerController* playerController = Unreal::PlayerController::Get();
		if (playerController)
		{
			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				SDK::FVector2D screenPosition;
				if (SDK::UGameplayStatics::ProjectWorldToScreen(playerController, actor.location, &screenPosition, false))
				{
					ImU32 color;
					if (Features::ActorsList::filterCheckValidness)
						color = Math::ColorFloat4_ToU32(Unreal::Actor::IsValid(actor.reference) ? Features::ActorsList::color_Valid : Features::ActorsList::color_Invalid);
					else
						color = IM_COL32(255, 255, 255, 255);
					
					iDrawList->AddCircleFilled({ (float)screenPosition.X, (float)screenPosition.Y }, 8.0f, color);

					const char* labelText = actor.objectName.c_str();
					ImVec2 labelSize = ImGui::CalcTextSize(labelText);
					ImVec2 labelPosition = ImVec2
					(
						/* Flooring the values allows to avoid potential subpixel conflicts. */
						floorf(screenPosition.X - (labelSize.x * 0.5)),
						floorf(screenPosition.Y - 32.0f)
					);

					iDrawList->AddText(labelPosition, color, labelText);
				}
			}
		}
	}
#endif




#ifdef COLLISION_VISUALIZER
	if (Features::CollisionVisualizer::enabled)
	{
		/* UGameplayStatics::ProjectWorldToScreen() verify Player Controller reference within its code. */
		SDK::APlayerController* playerController = Unreal::PlayerController::Get();
		if (playerController)
		{
			SDK::FVector playerLocation = Unreal::PlayerController::GetLocation(0);

			for (Unreal::Actor::DataStructure& actor : Features::ActorsList::filteredActors) // <-- Reference!
			{
				if (actor.reference == nullptr)
					continue;

				ImU32 color = {};

				if (actor.reference->IsA(SDK::APawn::StaticClass()))
				{
					color = Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_Pawn);

					SDK::TArray<SDK::UActorComponent*> actorComponents = actor.reference->K2_GetComponentsByClass(SDK::UCapsuleComponent::StaticClass());
					if (actorComponents.Num() == 0)
						continue;

					for (SDK::UActorComponent* component : actorComponents)
					{
						SDK::UCapsuleComponent* capsuleComponent = static_cast<SDK::UCapsuleComponent*>(component);
						if (capsuleComponent == nullptr)
							continue;

						float capsuleRadius = capsuleComponent->GetScaledCapsuleRadius();
						float capsuleHalfHeight = capsuleComponent->GetScaledCapsuleHalfHeight();

						Unreal::Transform capsuleTransform = Unreal::ActorComponent::GetTransform(capsuleComponent);
						SDK::FVector capsuleUpVector = SDK::UKismetMathLibrary::GetUpVector(capsuleTransform.rotation);

						/* Construct an orthonormal basis (axis, U, V) for building capsule rings. */
						SDK::FVector ortho_Temp = (fabsf(capsuleUpVector.Z) < 0.99f) ? SDK::FVector(0.f, 0.f, 1.f) : SDK::FVector(0.f, 1.f, 0.f); // Choose a temporary vector that is not parallel to the capsule axis.
						SDK::FVector ortho_U = SDK::UKismetMathLibrary::Normal(SDK::UKismetMathLibrary::Cross_VectorVector(capsuleUpVector, ortho_Temp), 0.01f); // Compute 'U' as a normalized vector perpendicular to 'axis'.
						SDK::FVector ortho_V = SDK::UKismetMathLibrary::Normal(SDK::UKismetMathLibrary::Cross_VectorVector(capsuleUpVector, ortho_U), 0.01f); // Compute 'V' as a normalized vector perpendicular to both 'axis' and 'U'.

						const SDK::FVector capsuleTopLocation = capsuleTransform.location + capsuleUpVector * capsuleHalfHeight;
						const SDK::FVector capsuleBottomLocation = capsuleTransform.location - capsuleUpVector * capsuleHalfHeight;

						/* Project capsule centers to draw them later on. */
						SDK::FVector2D capsuleTop_Screen, capsuleBottom_Screen;
						const bool capsuleTop_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleTopLocation, &capsuleTop_Screen, false);
						const bool capsuleBottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, capsuleBottomLocation, &capsuleBottom_Screen, false);

						static const int32_t capsuleSegments = 24;
						for (int32_t i = 0; i < capsuleSegments; i++)
						{
							/*
								A ----------> B

								A - Current ring.
								B - Next ring.
							*/

							/* Compute the start (ringA_Angle) and end (ringB_Angle) angles for the current ring segment in radians. */
							const float ringA_Angle = (2.0f * Math::PI) * (float)i / (float)capsuleSegments;
							const float ringB_Angle = (2.0f * Math::PI) * (float)(i + 1) / (float)capsuleSegments;

							/* Compute points on the top and bottom rings using circular parametrization. */
							SDK::FVector ringA_Top = capsuleTopLocation + (ortho_U * cosf(ringA_Angle) + ortho_V * sinf(ringA_Angle)) * capsuleRadius;
							SDK::FVector ringB_Top = capsuleTopLocation + (ortho_U * cosf(ringB_Angle) + ortho_V * sinf(ringB_Angle)) * capsuleRadius;
							SDK::FVector ringA_Bottom = capsuleBottomLocation + (ortho_U * cosf(ringA_Angle) + ortho_V * sinf(ringA_Angle)) * capsuleRadius;
							SDK::FVector ringB_Bottom = capsuleBottomLocation + (ortho_U * cosf(ringB_Angle) + ortho_V * sinf(ringB_Angle)) * capsuleRadius;

							SDK::FVector2D ringA_Top_Screen, ringB_Top_Screen, ringA_Bottom_Screen, ringB_Bottom_Screen;
							bool ringA_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Top, &ringA_Top_Screen, false);
							bool ringB_Top_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Top, &ringB_Top_Screen, false);
							bool ringA_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringA_Bottom, &ringA_Bottom_Screen, false);
							bool ringB_Bottom_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, ringB_Bottom, &ringB_Bottom_Screen, false);

							/* Outlines the top edge. */
							if (ringA_Top_Project && ringB_Top_Project)
								iDrawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringB_Top_Screen.X, ringB_Top_Screen.Y), color, Features::CollisionVisualizer::thickness);

							/* Outlines the bottom edge. */
							if (ringA_Bottom_Project && ringB_Bottom_Project)
								iDrawList->AddLine(ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), ImVec2(ringB_Bottom_Screen.X, ringB_Bottom_Screen.Y), color, Features::CollisionVisualizer::thickness);

							/* Outlines side walls. */
							if (ringA_Top_Project && ringA_Bottom_Project)
								iDrawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), color, Features::CollisionVisualizer::thickness);

							/* Outlines ring points to top and bottom centers. */
							if (capsuleTop_Project && ringA_Top_Project)
								iDrawList->AddLine(ImVec2(ringA_Top_Screen.X, ringA_Top_Screen.Y), ImVec2(capsuleTop_Screen.X, capsuleTop_Screen.Y), color, Features::CollisionVisualizer::thickness);

							if (capsuleBottom_Project && ringA_Bottom_Project)
								iDrawList->AddLine(ImVec2(ringA_Bottom_Screen.X, ringA_Bottom_Screen.Y), ImVec2(capsuleBottom_Screen.X, capsuleBottom_Screen.Y), color, Features::CollisionVisualizer::thickness);
						}
					}
				}
				else
				{
					SDK::UBodySetup* bodySetup = nullptr;
					Unreal::Transform transform = {};

					if (actor.reference->IsA(SDK::AVolume::StaticClass()))
					{
						if (actor.reference->IsA(SDK::ATriggerVolume::StaticClass()))
							color = Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_TriggerVolume);
						else if (actor.reference->IsA(SDK::ABlockingVolume::StaticClass()))
							color = Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_BlockingVolume);
						else
							color = Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_UnknownVolume);

						SDK::AVolume* volume = static_cast<SDK::AVolume*>(actor.reference);
						if (volume->BrushComponent == nullptr)
							continue;

						SDK::UBrushComponent* brushComponent = volume->BrushComponent;
						if (brushComponent->BrushBodySetup == nullptr)
							continue;

						bodySetup = brushComponent->BrushBodySetup;
						transform = Unreal::ActorComponent::GetTransform(brushComponent);
					}
					else if (actor.reference->IsA(SDK::AStaticMeshActor::StaticClass()))
					{
						color = Math::ColorFloat4_ToU32(Features::CollisionVisualizer::color_StaticMesh);

						SDK::AStaticMeshActor* staticMeshActor = static_cast<SDK::AStaticMeshActor*>(actor.reference);
						if (staticMeshActor->StaticMeshComponent == nullptr)
							continue;

						SDK::UStaticMeshComponent* staticMeshComponent = staticMeshActor->StaticMeshComponent;
						if (staticMeshComponent->StaticMesh == nullptr)
							continue;

						SDK::UStaticMesh* staticMesh = staticMeshComponent->StaticMesh;
						if (staticMesh->BodySetup == nullptr)
							continue;

						bodySetup = staticMesh->BodySetup;
						transform = Unreal::ActorComponent::GetTransform(staticMeshComponent);
					}
					else
						continue;

					for (SDK::FKConvexElem& convexElement : bodySetup->AggGeom.ConvexElems)
					{
						const SDK::TArray<SDK::FVector>& vertexData = convexElement.VertexData;
						const size_t vertexDataLength = vertexData.Num();
						if (vertexDataLength == 0)
							continue;

						const SDK::TArray<int32_t>& indexData = convexElement.IndexData;
						const size_t indexDataLength = indexData.Num();
						if (indexDataLength < 3 || indexDataLength % 3 != 0)
							continue;

						for (int32_t i = 0; i + 2 < indexDataLength; i += 3)
						{
							int32_t A_Index = indexData[i];
							int32_t B_Index = indexData[i + 1];
							int32_t C_Index = indexData[i + 2];

							if (A_Index < 0 || A_Index >= vertexDataLength ||
								B_Index < 0 || B_Index >= vertexDataLength ||
								C_Index < 0 || C_Index >= vertexDataLength)
								continue;

							if (A_Index == B_Index || B_Index == C_Index || C_Index == A_Index)
								continue;

							SDK::FVector A_Local = vertexData[A_Index];
							SDK::FVector B_Local = vertexData[B_Index];
							SDK::FVector C_Local = vertexData[C_Index];

							SDK::FTransform fTransform = Math::Unreal_ToFTransform(transform);
							SDK::FVector A_World = SDK::UKismetMathLibrary::TransformLocation(fTransform, A_Local);
							SDK::FVector B_World = SDK::UKismetMathLibrary::TransformLocation(fTransform, B_Local);
							SDK::FVector C_World = SDK::UKismetMathLibrary::TransformLocation(fTransform, C_Local);

							SDK::FVector2D A_Screen, B_Screen, C_Screen;
							bool A_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, A_World, &A_Screen, false);
							bool B_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, B_World, &B_Screen, false);
							bool C_Project = SDK::UGameplayStatics::ProjectWorldToScreen(playerController, C_World, &C_Screen, false);

							if (A_Project && B_Project && C_Project)
							{
								iDrawList->AddLine(ImVec2(A_Screen.X, A_Screen.Y), ImVec2(B_Screen.X, B_Screen.Y), color, Features::CollisionVisualizer::thickness);
								iDrawList->AddLine(ImVec2(B_Screen.X, B_Screen.Y), ImVec2(C_Screen.X, C_Screen.Y), color, Features::CollisionVisualizer::thickness);
								iDrawList->AddLine(ImVec2(C_Screen.X, C_Screen.Y), ImVec2(A_Screen.X, A_Screen.Y), color, Features::CollisionVisualizer::thickness);
							}
						}
					}
				}
			}
		}
	}
#endif
}




void GUI::PlaySound(const E_Sound& soundToPlay)
{
	if (Features::Menu::enableSound == false)
		return;

	uint16_t soundFrequency;
	uint16_t soundDuration;

	switch (soundToPlay)
	{
	case E_Sound::BUTTON_PRESS:
		soundFrequency = 245;
		soundDuration = 50;
		break;

	case E_Sound::BUTTON_CANCEL:
		soundFrequency = 100;
		soundDuration = 150;
		break;

	case E_Sound::ACTION_SUCCESS:
		soundFrequency = 350;
		soundDuration = 300;
		break;

	case E_Sound::ACTION_ERROR:
		soundFrequency = 175;
		soundDuration = 300;
		break;

	default:
		soundFrequency = 500;
		soundDuration = 1000;
		break;
	}

	/*
		Dedicate sound playback in to separate thread.
		This prevents the main thread from blocking while Beep() is playing the sound.
	*/
	std::thread([=]()
		{
			Beep(soundFrequency, soundDuration);
		}).detach();
}






// ========================================================
// |            #GUI #SHARED #CALLS #SHAREDCALLS          |
// ========================================================
void Features::Debug::Update()
{
	SDK::UEngine* engine = Unreal::Engine::Get();
	if (Features::Debug::engine.reference = engine)
	{
		Features::Debug::engine.className = engine->Class->GetFullName();
		Features::Debug::engine.objectName = engine->GetFullName();

		Features::Debug::engine.fixedFrameRateEnabled = engine->bUseFixedFrameRate;
		Features::Debug::engine.fixedFrameRate = engine->FixedFrameRate;

		Features::Debug::engine.smoothFrameRateEnabled = engine->bSmoothFrameRate;
		Features::Debug::engine.smoothFrameRateRange = engine->SmoothedFrameRateRange;

		Features::Debug::engine.subtitlesEnabled = engine->bSubtitlesEnabled;
		Features::Debug::engine.subtitlesForcedOff = engine->bSubtitlesForcedOff;

		Features::Debug::engine.pauseOnLossOfFocus = engine->bPauseOnLossOfFocus;

		SDK::UGameViewportClient* viewportClient = engine->GameViewport;
		if (Features::Debug::engine.gameViewportClient.reference = viewportClient)
		{
			Features::Debug::engine.gameViewportClient.className = viewportClient->Class->GetFullName();
			Features::Debug::engine.gameViewportClient.objectName = viewportClient->GetFullName();

			SDK::UConsole* console = viewportClient->ViewportConsole;
			if (Features::Debug::engine.gameViewportClient.console.reference = console)
			{
				Features::Debug::engine.gameViewportClient.console.className = console->Class->GetFullName();
				Features::Debug::engine.gameViewportClient.console.objectName = console->GetFullName();
			}
		}
	}


	SDK::UGameInstance* gameInstance = Unreal::GameInstance::Get();
	if (Features::Debug::gameInstance.reference = gameInstance)
	{
		Features::Debug::gameInstance.className = gameInstance->Class->GetFullName();
		Features::Debug::gameInstance.objectName = gameInstance->GetFullName();

		SDK::UOnlineSession* onlineSession = gameInstance->OnlineSession;
		if (Features::Debug::gameInstance.onlineSession.reference = onlineSession)
		{
			Features::Debug::gameInstance.onlineSession.className = gameInstance->Class->GetFullName();
			Features::Debug::gameInstance.onlineSession.objectName = gameInstance->GetFullName();
		}
	}


	SDK::AGameModeBase* gameMode = Unreal::GameMode::Get();
	if (Features::Debug::gameMode.reference = gameMode)
	{
		Features::Debug::gameMode.className = gameMode->Class->GetFullName();
		Features::Debug::gameMode.objectName = gameMode->GetFullName();

		SDK::AGameSession* gameSession = gameMode->GameSession;
		if (Features::Debug::gameMode.gameSession.reference = gameSession)
		{
			Features::Debug::gameMode.gameSession.className = gameSession->Class->GetFullName();
			Features::Debug::gameMode.gameSession.objectName = gameSession->GetFullName();

			Features::Debug::gameMode.gameSession.maxPlayers = gameSession->MaxPlayers;
			Features::Debug::gameMode.gameSession.maxSpectators = gameSession->MaxSpectators;
			Features::Debug::gameMode.gameSession.maxPartySize = gameSession->MaxPartySize;
			Features::Debug::gameMode.gameSession.maxSplitScreensPerConnection = gameSession->MaxSplitscreensPerConnection;

			Features::Debug::gameMode.gameSession.sessionName = gameSession->SessionName.ToString();
		}

		Features::Debug::gameMode.playersCount = gameMode->GetNumPlayers();
		Features::Debug::gameMode.spectatorsCount = gameMode->GetNumSpectators();

		Features::Debug::gameMode.startPlayersAsSpectators = gameMode->bStartPlayersAsSpectators;
		Features::Debug::gameMode.defaultPlayerName = gameMode->DefaultPlayerName.ToString();

		Features::Debug::gameMode.useSeamlessTravel = gameMode->bUseSeamlessTravel;
		Features::Debug::gameMode.options = gameMode->OptionsString.ToString();

		Features::Debug::gameMode.isPausable = gameMode->bPauseable;
	}


	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (Features::Debug::playerController.reference = playerController)
	{
		Features::Debug::playerController.className = playerController->Class->GetFullName();
		Features::Debug::playerController.objectName = playerController->GetFullName();


		SDK::UPlayer* player = playerController->Player;
		if (Features::Debug::playerController.player.reference = player)
		{
			Features::Debug::playerController.player.className = player->Class->GetFullName();
			Features::Debug::playerController.player.objectName = player->GetFullName();
		}


		SDK::APawn* pawn = playerController->AcknowledgedPawn;
		if (Features::Debug::playerController.pawn.reference = pawn)
		{
			Features::Debug::playerController.pawn.className = pawn->Class->GetFullName();
			Features::Debug::playerController.pawn.objectName = pawn->GetFullName();

			Unreal::Transform pawnTransform = Unreal::Actor::GetTransform(pawn);
			Features::Debug::playerController.pawn.location = pawnTransform.location;
			Features::Debug::playerController.pawn.rotation = pawnTransform.rotation;
			Features::Debug::playerController.pawn.scale = pawnTransform.scale;

			Features::Debug::playerController.pawn.isControlled = pawn->IsControlled();
			Features::Debug::playerController.pawn.isPawnControlled = pawn->IsPawnControlled();
			Features::Debug::playerController.pawn.isPlayerControlled = pawn->IsPlayerControlled();
			Features::Debug::playerController.pawn.isLocallyControlled = pawn->IsLocallyControlled();
			Features::Debug::playerController.pawn.isBotControlled = pawn->IsBotControlled();
		}


		SDK::APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;
		if (Features::Debug::playerController.cameraManager.reference = cameraManager)
		{
			Features::Debug::playerController.cameraManager.className = cameraManager->Class->GetFullName();
			Features::Debug::playerController.cameraManager.objectName = cameraManager->GetFullName();

			Unreal::Transform cameraManagerTransform = Unreal::Actor::GetTransform(cameraManager);
			Features::Debug::playerController.cameraManager.location = cameraManagerTransform.location;
			Features::Debug::playerController.cameraManager.rotation = cameraManagerTransform.rotation;
			Features::Debug::playerController.cameraManager.scale = cameraManagerTransform.scale;
		}


		SDK::UCheatManager* cheatManager = playerController->CheatManager;
		if (Features::Debug::playerController.cheatManager.reference = cheatManager)
		{
			Features::Debug::playerController.cheatManager.className = cheatManager->Class->GetFullName();
			Features::Debug::playerController.cheatManager.objectName = cheatManager->GetFullName();
		}
	}


	SDK::UWorld* world = SDK::UWorld::GetWorld();
	if (Features::Debug::world.reference = world)
	{
		Features::Debug::world.className = world->Class->GetFullName();
		Features::Debug::world.objectName = world->GetFullName();

		if (SDK::AGameStateBase* gameState = world->GameState)
		{
			Features::Debug::world.gameState.reference = gameState;

			Features::Debug::world.gameState.className = gameState->Class->GetFullName();
			Features::Debug::world.gameState.objectName = gameState->GetFullName();
		}

		if (SDK::UNetDriver* netDriver = world->NetDriver)
		{
			Features::Debug::world.netDriver.reference = netDriver;

			Features::Debug::world.netDriver.className = netDriver->Class->GetFullName();
			Features::Debug::world.netDriver.objectName = netDriver->GetFullName();
		}

		if (SDK::UNetDriver* demoNetDriver = world->NetDriver)
		{
			Features::Debug::world.demoNetDriver.reference = demoNetDriver;

			Features::Debug::world.demoNetDriver.className = demoNetDriver->Class->GetFullName();
			Features::Debug::world.demoNetDriver.objectName = demoNetDriver->GetFullName();
		}

		if (SDK::ULevel* persistentLevel = world->PersistentLevel)
		{
			Features::Debug::world.persistentLevel.reference = persistentLevel;

			Features::Debug::world.persistentLevel.className = persistentLevel->Class->GetFullName();
			Features::Debug::world.persistentLevel.objectName = persistentLevel->GetFullName();

			Features::Debug::world.persistentLevel.isVisible = persistentLevel->bIsVisible;

			if (SDK::AWorldSettings* worldSettings = persistentLevel->WorldSettings)
			{
				Features::Debug::world.persistentLevel.worldSettings.reference = worldSettings;
				Features::Debug::world.persistentLevel.worldSettings.className = worldSettings->Class->GetFullName();
				Features::Debug::world.persistentLevel.worldSettings.objectName = worldSettings->GetFullName();

				Features::Debug::world.persistentLevel.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
				Features::Debug::world.persistentLevel.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

				Features::Debug::world.persistentLevel.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
			}
		}

		SDK::TArray<SDK::ULevelStreaming*> streamingLevels = world->StreamingLevels;
		if (streamingLevels.Num() > 0)
		{
			Features::Debug::world.streamingLevels.clear();

			for (SDK::ULevelStreaming* streamingLevel : streamingLevels)
			{
				if (streamingLevel == nullptr)
					continue;

#ifdef UE5
				std::string streamingLevelPath = streamingLevel->WorldAsset.ObjectID.AssetPath.AssetName.GetRawString();
#else
				std::string streamingLevelPath = streamingLevel->WorldAsset.ObjectID.AssetPathName.GetRawString();
#endif
				if (streamingLevelPath.empty())
					continue;

				Unreal::LevelStreaming::DataStructure levelStreamingData = {};

				levelStreamingData.reference = streamingLevel;
				levelStreamingData.className = streamingLevel->Class->GetFullName();
				levelStreamingData.objectName = streamingLevel->GetFullName();

				levelStreamingData.levelPath = streamingLevelPath;
				levelStreamingData.levelColor = streamingLevel->LevelColor;

				SDK::ULevel* loadedLevel = streamingLevel->LoadedLevel;
				if (levelStreamingData.level.reference = loadedLevel)
				{
					levelStreamingData.level.className = loadedLevel->Class->GetFullName();
					levelStreamingData.level.objectName = loadedLevel->GetFullName();

					levelStreamingData.level.isVisible = loadedLevel->bIsVisible;

					SDK::AWorldSettings* worldSettings = loadedLevel->WorldSettings;
					if (levelStreamingData.level.worldSettings.reference = worldSettings)
					{
						levelStreamingData.level.worldSettings.className = worldSettings->Class->GetFullName();
						levelStreamingData.level.worldSettings.objectName = worldSettings->GetFullName();

						levelStreamingData.level.worldSettings.highPriorityLoading = worldSettings->bHighPriorityLoading;
						levelStreamingData.level.worldSettings.localHighPriorityLoading = worldSettings->bHighPriorityLoadingLocal;

						levelStreamingData.level.worldSettings.unitsToMeters = worldSettings->WorldToMeters;
					}
				}

				Features::Debug::world.streamingLevels.push_back(levelStreamingData);
			}
		}

		Features::Debug::world.gameTimeInSeconds = SDK::UKismetSystemLibrary::GetGameTimeInSeconds(world);

		Features::Debug::world.isServer = SDK::UKismetSystemLibrary::IsServer(world);
		Features::Debug::world.isDedicatedServer = SDK::UKismetSystemLibrary::IsDedicatedServer(world);
		Features::Debug::world.isSplitScreen = SDK::UKismetSystemLibrary::IsSplitScreen(world);
		Features::Debug::world.isStandalone = SDK::UKismetSystemLibrary::IsStandalone(world);
	}


	if (Features::Debug::wasProjectNameObtained == false)
	{
		std::string projectName = SDK::UKismetSystemLibrary::GetGameName().ToString();
		if (projectName.empty() == false)
		{
			Features::Debug::projectName = projectName;
			Features::Debug::wasProjectNameObtained = true;
		}
	}


	if (Features::Debug::wasProjectPlatformObtained == false)
	{
		std::string projectPlatform = SDK::UGameplayStatics::GetPlatformName().ToString();
		if (projectPlatform.empty() == false)
		{
			Features::Debug::projectPlatform = projectPlatform;
			Features::Debug::wasProjectPlatformObtained = true;
		}
	}


	if (Features::Debug::wasProjectEngineVersionObtained == false)
	{
		std::string engineVersion = SDK::UKismetSystemLibrary::GetEngineVersion().ToString();
		if (engineVersion.empty() == false)
		{
			Features::Debug::projectEngineVersion = engineVersion;
			Features::Debug::wasProjectEngineVersionObtained = true;
		}
	}


	if (Features::Debug::wasUsernameObtained == false)
	{
		std::string username = SDK::UKismetSystemLibrary::GetPlatformUserName().ToString();
		if (username.empty() == false)
		{
			Features::Debug::username = username;
			Features::Debug::wasUsernameObtained = true;
		}
	}


	if (Features::Debug::wasCommandLineObtained == false)
	{
		LPWSTR lCommandLine = GetCommandLineW();
		std::wstring wCommandLine = std::wstring(lCommandLine);
		std::string commandLine = std::string(wCommandLine.begin(), wCommandLine.end());

		Features::Debug::commandLine = commandLine;
		Features::Debug::wasCommandLineObtained = true;
	}


	Features::Debug::lastUpdateTime = ImGui::GetTime();
}




void Features::ActorsList::Update()
{
	Features::ActorsList::actors.clear();

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(SDK::AActor::StaticClass()))
		{
			Unreal::Actor::DataStructure actorData = {};

			SDK::AActor* actor = static_cast<SDK::AActor*>(objectReference);
			actorData.reference = actor;
			actorData.superClassName = actor->Class->Super->GetFullName();
			actorData.className = actor->Class->GetFullName();
			actorData.objectName = actor->GetFullName();

#ifdef ACTOR_KIND
			actorData.kind = Unreal::Actor::GetActorKind(actor);
#endif

			Unreal::Transform actorTransform = Unreal::Actor::GetTransform(actor);
			actorData.location = actorTransform.location;
			actorData.rotation = actorTransform.rotation;
			actorData.scale = actorTransform.scale;

			SDK::TArray<SDK::UActorComponent*> actorComponents = actor->K2_GetComponentsByClass(SDK::UActorComponent::StaticClass());
			for (SDK::UActorComponent* component : actorComponents)
			{
				Unreal::ActorComponent::DataStructure componentData = {};

				componentData.reference = component;
				componentData.className = component->Class->GetFullName();
				componentData.objectName = component->GetFullName();

				componentData.isActive = component->bIsActive;
				componentData.autoActivate = component->bAutoActivate;
				componentData.editorOnly = component->bIsEditorOnly;

				componentData.netAddressible = component->bNetAddressable;
				componentData.replicates = component->bReplicates;

				componentData.creationMethod = component->CreationMethod;

				actorData.components.push_back(componentData);
			}

			Features::ActorsList::actors.push_back(actorData);
		}
	}
}




void Features::WidgetsList::Update()
{
	Features::WidgetsList::widgets.clear();

	int32_t objectsNum = SDK::UObject::GObjects->Num();
	for (int i = 0; i < objectsNum; i++)
	{
		SDK::UObject* objectReference = SDK::UObject::GObjects->GetByIndex(i);

		if (objectReference == nullptr || objectReference->IsDefaultObject())
			continue;

		if (objectReference->IsA(SDK::UUserWidget::StaticClass()))
		{
			Unreal::UserWidget::DataStructure widgetData = {};

			SDK::UUserWidget* widget = static_cast<SDK::UUserWidget*>(objectReference);
			widgetData.reference = widget;
			widgetData.className = widget->Class->GetFullName();
			widgetData.objectName = widget->GetFullName();

			widgetData.parent = widget->GetParent();

			widgetData.isInViewport = widget->IsInViewport();
			widgetData.visibility = widget->Visibility;

			Features::WidgetsList::widgets.push_back(widgetData);
		}
	}
}






// ========================================================
// |       #GUI #SHARED #FUNCTIONS #SHAREDFUNCTIONS       |
// ========================================================
void Features::CharacterMovement::Ghost()
{
	bool success = Unreal::Character::Ghost(0);

	if (Features::Menu::enableConsoleOutput)
		Unreal::Console::Print(success ? "[Character Movement] Ghost" : "[Character Movement] Switch to Ghost failed");

	GUI::PlayActionSound(success);
}

void Features::CharacterMovement::Fly()
{
	bool success = Unreal::Character::Fly(0);

	if (Features::Menu::enableConsoleOutput)
		Unreal::Console::Print(success ? "[Character Movement] Fly" : "[Character Movement] Switch to Fly failed");

	GUI::PlayActionSound(success);
}

void Features::CharacterMovement::Walk()
{
	bool success = Unreal::Character::Walk(0);

	if (Features::Menu::enableConsoleOutput)
		Unreal::Console::Print(success ? "[Character Movement] Walk" : "[Character Movement] Switch to Walk failed");

	GUI::PlayActionSound(success);
}




void Features::CharacterMovement::Jump()
{
	GUI::PlayActionSound(Unreal::Character::Jump(0));
}




void Features::CharacterMovement::Launch()
{
	GUI::PlayActionSound(Unreal::Character::Launch(0, { Features::CharacterMovement::launchVelocity[0], Features::CharacterMovement::launchVelocity[1], Features::CharacterMovement::launchVelocity[2] }));
}

void Features::CharacterMovement::Dash()
{
	SDK::ACharacter* character = Unreal::Character::Get();
	if (character == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FVector forwardVector = character->GetActorForwardVector();

	/* Dash shouldn't involve any vertical movement. */
	forwardVector.Z = 0.0;
	forwardVector.Normalize();

	SDK::FVector launchVelocity = forwardVector * Features::CharacterMovement::dashStrength;
	GUI::PlayActionSound(Unreal::Character::Launch(character, launchVelocity));
}




void Features::DirectionalMovement::Worker()
{
	while (GetThread())
	{
		/* See if we have a Player Controller alongside the Camera Manager. */
		SDK::APlayerController* playerController = Unreal::PlayerController::Get();
		if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
			continue;

		/* See if we have a Character under control and verify that Character is cheat flying. */
		SDK::ACharacter* character = playerController->Character;
		if (character == nullptr || character->CharacterMovement == nullptr || character->CharacterMovement->bCheatFlying != true)
			continue;

		/* Get Character velocity and see if we have any horizontal movement. */
		SDK::FVector characterVelocity = character->CharacterMovement->Velocity;
		if (characterVelocity.X == 0.0 && characterVelocity.Y == 0.0)
			continue;

		/* Normalize Character velocity (-1.0 to 1.0) and get Camera forward vector. */
		SDK::FVector characterVelocityNormalized = Math::Vector_Normalize(characterVelocity);
		SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();

		/*
			Compute the dot product of the normalized character velocity and the camera's forward vector.
			Result interpretation:
			  +1.0 -> character moves exactly forward,
			  -1.0 -> character moves exactly backward,
			   0.0 -> movement is perpendicular to the camera.
		*/
		double dotProduct = SDK::UKismetMathLibrary::Dot_VectorVector(characterVelocityNormalized, cameraForwardVector);
		if (dotProduct > 0.5) // Character is mostly targeting forward direction.
		{
			SDK::FVector currentLocation = character->K2_GetActorLocation();
			SDK::FVector finalLocation = SDK::UKismetMathLibrary::Add_VectorVector(currentLocation, cameraForwardVector * Features::DirectionalMovement::step);

			SDK::FHitResult hitResult;
			character->K2_SetActorLocation(finalLocation, true, &hitResult, false);
		}

		Sleep(Math::Seconds_ToMilliseconds(Features::DirectionalMovement::delay));
	}
}




void Features::Camera::StartFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	SDK::FLinearColor fadeColor;
	fadeColor.R = Features::Camera::fadeColor[0];
	fadeColor.G = Features::Camera::fadeColor[1];
	fadeColor.B = Features::Camera::fadeColor[2];
	fadeColor.A = Features::Camera::fadeColor[3];

	playerController->PlayerCameraManager->StartCameraFade(Features::Camera::fadeFromAlpha, Features::Camera::fadeToAlpha, Features::Camera::fadeDuration, fadeColor, Features::Camera::fadeAudio, Features::Camera::fadePersistent);
	GUI::PlayActionSound(true);
}

void Features::Camera::StopFade()
{
	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
	{
		GUI::PlayActionSound(false);
		return;
	}

	playerController->PlayerCameraManager->StopCameraFade();
	GUI::PlayActionSound(true);
}




bool Features::DirectionalMovement::StartThread()
{
	if (thread)
		return false;

	thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Features::DirectionalMovement::Worker, 0, 0, 0);
	return thread;
}

bool Features::DirectionalMovement::InvalidateThread()
{
	if (thread == nullptr)
		return false;

	if (CloseHandle(thread))
	{
		thread = nullptr;
		return true;
	}
	else
		return false;
}




#ifdef ACTOR_TRACE
bool Features::ActorTrace::Trace()
{
	SDK::UWorld* world = Unreal::World::Get();
	if (world == nullptr)
		return false;

	SDK::APlayerController* playerController = Unreal::PlayerController::Get();
	if (playerController == nullptr || playerController->PlayerCameraManager == nullptr)
		return false;

	SDK::FVector cameraLocation = playerController->PlayerCameraManager->K2_GetActorLocation();
	SDK::FVector cameraForwardVector = playerController->PlayerCameraManager->GetActorForwardVector();
	SDK::FVector traceEndLocation = cameraLocation + (cameraForwardVector * Features::ActorTrace::traceLength);

	SDK::TArray<SDK::AActor*> actorsToIgnore;
	if (SDK::ACharacter* character = Unreal::Character::Get())
		actorsToIgnore.Add(character);

	SDK::FHitResult hitResult;
	Features::ActorTrace::traceHit = SDK::UKismetSystemLibrary::LineTraceSingle(world, cameraLocation, traceEndLocation, SDK::ETraceTypeQuery::TraceTypeQuery1, false, actorsToIgnore, SDK::EDrawDebugTrace::ForDuration, &hitResult, true, SDK::FLinearColor(), SDK::FLinearColor(), 5.0f);
	if (traceHit)
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = hitResult.Location;

#ifdef UE5
		/* UE 5.3.2 and older: hitResult.HitObjectHandle.Actor.Get() */
		SDK::UObject* hitObject = hitResult.HitObjectHandle.ReferenceObject.Get();
		if (hitObject)
		{

			Features::ActorTrace::object.reference = hitObject;
			Features::ActorTrace::object.className = hitObject->Class->GetFullName();
			Features::ActorTrace::object.objectName = hitObject->GetFullName();

			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] " + Features::ActorTrace::object.objectName);
		}
		else
		{
			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] Didn't hit any object.");
		}
#else
		SDK::AActor* hitActor = hitResult.Actor.Get();
		if (hitActor)
		{

			Features::ActorTrace::actor.reference = hitActor;
			Features::ActorTrace::actor.className = hitActor->Class->GetFullName();
			Features::ActorTrace::actor.objectName = hitActor->GetFullName();

			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] " + Features::ActorTrace::actor.objectName);
		}
		else
		{
			if (Features::Menu::enableConsoleOutput)
				Unreal::Console::Print("[Actor Trace] Didn't hit any actor.");
		}
#endif
	}
	else
	{
		Features::ActorTrace::traceStartLocation = cameraLocation;
		Features::ActorTrace::traceEndLocation = traceEndLocation;
	}

	Features::ActorTrace::traceCast = true;
	return true;
}
#endif






void Keybindings::Process()
{
	if (ImGui::IsKeyBindingPressed(&Keybindings::general_MenuOpenClose))
		GUI::ToggleIsMenuActive();


	if (GUI::GetIsMenuActive() == false)
	{
#ifdef ACTOR_TRACE
		if (Features::ActorTrace::enabled)
		{
			if (ImGui::IsKeyBindingPressed(&Keybindings::debug_ActorTrace))
			{
				GUI::PlayActionSound(Features::ActorTrace::Trace());
			}
		}
#endif




		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Ghost))
		{
			Features::CharacterMovement::Ghost();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Fly))
		{
			Features::CharacterMovement::Fly();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Walk))
		{
			Features::CharacterMovement::Walk();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Jump))
		{
			Features::CharacterMovement::Jump();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Launch))
		{
			Features::CharacterMovement::Launch();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterMovement_Dash))
		{
			Features::CharacterMovement::Dash();
		}




		if (ImGui::IsKeyBindingPressed(&Keybindings::characterCamera_StartFade))
		{
			Features::Camera::StartFade();
		}

		if (ImGui::IsKeyBindingPressed(&Keybindings::characterCamera_StopFade))
		{
			Features::Camera::StopFade();
		}
	}
}