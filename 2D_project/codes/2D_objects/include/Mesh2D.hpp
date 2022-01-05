#ifndef Mesh_hpp
#define Mesh_hpp

#include<glm/mat3x3.hpp>
#include<glm/vec2.hpp>
#include<glm/vec4.hpp>
#include<vector>
#include "VertexArrayObject.hpp"
class ShaderProgram;
class MeshManager;


class Mesh2D
{
public:
    void rotate(float angle);
    void setPosition(const glm::vec2& pos);
    void setAngle(float angle);
    void setColor(const glm::vec4& color);
    void setScale(const glm::vec2& scale);
    void draw(ShaderProgram& shader);
    void update();
    bool getColorActive();
    glm::vec2 getPosition();
    void setColorActive(bool active);
    Mesh2D();
private:
    
    bool                colorActive;
    bool                isActive;
    glm::mat3           mtxWorld;
    glm::vec2           position;
    glm::vec2           scale;
    glm::vec4           color;
    float               angle;
    VertexArrayObject   vertexArrayObject;  
    friend MeshManager;
};
typedef std::vector<Mesh2D*> Mesh2DList;

#endif