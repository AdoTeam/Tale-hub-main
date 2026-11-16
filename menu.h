#ifndef MENU_H
#define MENU_H

#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_android.h"
#include "Roboto-Regular.h"
#include "Icon.h"
#include "Iconcpp.h"
#include "variables.h" // Değişkenler artık buradan çekiliyor!
#include <string>

inline void SetupImgui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    int(*get_width)(void*);
    int(*get_height)(void*);
    get_width = (int (*)(void*)) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", "get_width", 0);
    get_height = (int (*)(void*)) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Screen", "get_height", 0);
    io.DisplaySize = ImVec2((float)get_width(0), (float)get_height(0));
    
    // Liquid Glass / Köşe Yuvarlatma Ayarları
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.ChildRounding = 7.0f;
    style.FrameRounding = 8.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 5.0f;
    style.GrabRounding = 7.0f;
    style.TabRounding = 7.0f;
    style.WindowBorderSize = 1.0f;

    ImGui_ImplOpenGL3_Init("#version 100");
    
    ImFontConfig font_cfg;
    io.Fonts->AddFontFromMemoryTTF(&Roboto_Regular, sizeof(Roboto_Regular), 32.0, &font_cfg, io.Fonts->GetGlyphRangesCyrillic());
    ImGui::GetStyle().ScaleAllSizes(3.0f);
}

inline void DrawMenu() {  
    // Sıvı Cam (Liquid Glass) Renk Paleti
    ImGuiStyle& style = ImGui::GetStyle();
    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.08f, 0.08f, 0.12f, g_WindowAlpha);
    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.12f, 0.12f, 0.18f, g_WindowAlpha * 0.7f);
    style.Colors[ImGuiCol_Border] = ImVec4(g_ThemeColor.x, g_ThemeColor.y, g_ThemeColor.z, 0.6f);
    style.Colors[ImGuiCol_Button] = ImVec4(0.18f, 0.18f, 0.25f, 0.8f);
    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(g_ThemeColor.x, g_ThemeColor.y, g_ThemeColor.z, 0.7f);
    style.Colors[ImGuiCol_ButtonActive] = ImVec4(g_ThemeColor.x, g_ThemeColor.y, g_ThemeColor.z, 1.0f);
    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.28f, 0.9f);

    const ImVec2 window_size = ImVec2(800, 500);
    ImGui::SetNextWindowSize(window_size, ImGuiCond_Once);
    
    ImGui::Begin("##MetichModMenu", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
    
    // --- ÜST KISIM: BAŞLIK VE KATEGORİ SEKMELERİ ---
    ImGui::BeginChild("HeaderBar", ImVec2(0, 70), true);
    
    // Sol üst büyük Metich yazısı
    ImGui::PushStyleColor(ImGuiCol_Text, g_ThemeColor);
    ImGui::SetWindowFontScale(1.4f);
    ImGui::Text("Metich");
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();

    ImGui::SameLine(130);

    float tabWidth = 140.0f;
    float spacing = 8.0f;

    if (ImGui::Button("Main", ImVec2(tabWidth, 40))) g_SelectedTab = 0;
    ImGui::SameLine(0, spacing);
    if (ImGui::Button("Visual", ImVec2(tabWidth, 40))) g_SelectedTab = 1;
    ImGui::SameLine(0, spacing);
    if (ImGui::Button("Login", ImVec2(tabWidth, 40))) g_SelectedTab = 2;
    ImGui::SameLine(0, spacing);
    if (ImGui::Button("Settings", ImVec2(tabWidth, 40))) g_SelectedTab = 3;

    ImGui::EndChild();

    ImGui::Spacing();

    // --- ALT KISIM: İÇERİK ALANI ---
    ImGui::BeginChild("ContentArea", ImVec2(0, 0), true);
    
    if (g_SelectedTab == 0) {
        ImGui::Text("Combat & Main Features");
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("GodMode (Immortal)", &g_GodMode);
        ImGui::Spacing();
        ImGui::Checkbox("Auto Critical Hit", &g_AutoCrit);
        ImGui::Spacing();
        ImGui::Checkbox("Speed Hack", &g_SpeedHack);
        
        if (g_SpeedHack) {
            ImGui::Indent(20.0f);
            ImGui::SliderFloat("Speed Rate", &g_SpeedValue, 1.0f, 5.0f, "%.1fx");
            ImGui::Unindent(20.0f);
        }
    }
    else if (g_SelectedTab == 1) {
        ImGui::Text("Visual & ESP Options");
        ImGui::Separator();
        ImGui::Spacing();
        static bool espBox = false;
        static bool espLine = false;
        ImGui::Checkbox("Player Box ESP", &espBox);
        ImGui::Spacing();
        ImGui::Checkbox("Snaplines", &espLine);
    }
    else if (g_SelectedTab == 2) {
        ImGui::Text("Miscellaneous Tools");
        ImGui::Separator();
        ImGui::Spacing();
        static bool fovChanger = false;
        ImGui::Checkbox("Unlock Custom FOV", &fovChanger);
    }
    else if (g_SelectedTab == 3) {
        ImGui::Text("Liquid Glass & Menu Settings");
        ImGui::Separator();
        ImGui::Spacing();
        
        ImGui::Text("Menu Transparency");
        ImGui::SliderFloat("##alpha", &g_WindowAlpha, 0.3f, 1.0f);
        
        ImGui::Spacing();
        ImGui::Text("Accent Color");
        ImGui::ColorEdit4("##theme", (float*)&g_ThemeColor);
    }

    ImGui::EndChild();

    ImGui::End();  
}

#endif

