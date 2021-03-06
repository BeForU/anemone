/**
* This file is part of Anemone.
*
* Anemone is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* The Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Anemone is distributed in the hope that it will be useful,
*
* But WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Anemone.
*
*   If not, see <http://www.gnu.org/licenses/>.
*
**/

#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#pragma comment(linker,"\"/manifestdependency:type='win32' name = 'Microsoft.Windows.Common-Controls' version = '6.0.0.0' processorArchitecture = '*' publicKeyToken = '6595b64144ccf1df' language = '*'\"")

// Windows Header
#include <windows.h>
#include <process.h>
#include <commdlg.h>

// disable 4819 charset warnings
#pragma warning(disable: 4819)

// skia-compatiblity
#undef max
#undef min

// c runtime
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <thread>
#include <chrono>

extern int guide_opacity;
extern bool mouse_evt;
extern std::wstring strBuff;
extern std::vector<std::wstring> vecBuff;
extern int n_selLine;

#include "ConfigManager.h"
extern ConfigManager CfgMgr;