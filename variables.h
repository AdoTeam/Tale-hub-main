#ifndef VARIABLES_H
#define VARIABLES_H

#include "imgui.h"

// --- HİLE DEĞİŞKENLERİ (Hook'ların ve menünün ortak kullandığı alan) ---
inline bool g_GodMode = false;
inline bool g_AutoCrit = false;
inline bool g_SpeedHack = false;
inline float g_SpeedValue = 1.0f;

// --- GÖRSEL & TEMA DEĞİŞKENLERİ ---
inline float g_WindowAlpha = 0.85f; 
inline ImVec4 g_ThemeColor = ImVec4(0.35f, 0.25f, 0.85f, 1.0f); // Varsayılan Mor/Mavi Tema
inline int g_SelectedTab = 0;       // 0: Main, 1: Visual, 2: Misc, 3: Settings

#endif

