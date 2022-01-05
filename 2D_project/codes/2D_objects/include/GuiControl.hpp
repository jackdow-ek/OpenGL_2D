#ifndef GuiControl_hpp
#define GuiControl_hpp
#include <glm/vec2.hpp>
#include <functional>
class GLFWwindow;

enum SHAPETYPE
{
    SHAPE_SQUARE=0,
    SHAPE_CIRCLE=1,
    SHAPE_HEXAGON=2,
    SHAPE_TRIANGLE=3    
};
enum TYPE
{
    sil=1
};

typedef std::function<void(SHAPETYPE)>  SekilOlusturFonksiyonu;
typedef std::function<void(TYPE)>  SekilSilme;
class GuiControl
{
public:
    GuiControl();
    void init(GLFWwindow* window);
    void createFrame();
    void createFrameItems();
    void draw();
    void setPos(glm::vec2* pos);
    void setSca(glm::vec2* scale);
    void setAngle(float* angle);
    SekilOlusturFonksiyonu tiklaSekilOlustur;
    SekilSilme sekilsil;
    int silinen;
private:
    int secilenSekil;
    float*  angle;
    glm::vec2* vecPos;
    glm::vec2* sca;
};

#endif