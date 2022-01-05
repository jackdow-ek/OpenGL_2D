#include "GuiControl.hpp"
#include<imgui/imgui.h>
#include<imgui/imgui_impl_glfw.h>
#include<imgui/imgui_impl_opengl3.h>
#include<iostream>

GuiControl::GuiControl()
{

}
void GuiControl::init(GLFWwindow* window)
{
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 130");
    ImGui::StyleColorsClassic();
}
void GuiControl::createFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GuiControl::setAngle(float *angle)
{
    this->angle = angle;
}
void GuiControl::setSca(glm::vec2* scale)
{
    this->sca = scale;
}
void GuiControl::setPos(glm::vec2* pos)
{
    this->vecPos = pos;
}

void GuiControl::createFrameItems()
{
    ImGui::Begin("imgui penceresi");
    ImGui::SliderFloat("dondurme",angle,0,360);
    ImGui::SliderFloat2("hareket",(float*)vecPos,-1.0f,1.0f);
    ImGui::SliderFloat2("olcek",(float*)sca,0,1.0f);


    ImGui::RadioButton("Kare",&secilenSekil,0);ImGui::SameLine();
    ImGui::RadioButton("Daire",&secilenSekil,1);ImGui::SameLine();
    ImGui::RadioButton("Altigen",&secilenSekil,2);ImGui::SameLine();
    ImGui::RadioButton("Ucgen",&secilenSekil,3);   

    if(ImGui::Button("Sil Beni"))
    {
        silinen = 1;
        sekilsil((TYPE)silinen);
    }
    ImGui::SameLine();
    if(ImGui::Button("Tikla Beni"))
    {
        
        tiklaSekilOlustur((SHAPETYPE)secilenSekil);
    }
    ImGui::End();
}
void GuiControl::draw()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
