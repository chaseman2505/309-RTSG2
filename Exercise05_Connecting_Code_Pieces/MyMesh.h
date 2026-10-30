// Course: IGME 309
// Student Name: YOUR NAME
// Friday Exercise: 05
#ifndef MY_MESH_H
#define MY_MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace std;
using namespace glm;

class MyMesh
{
private:
    unsigned int vertNum, triNum;
    float* vertices;
    unsigned int* indices;
    float* vertColors;
    unsigned int vbo_id, cbo_id, ibo_id;

public:
    MyMesh();
    ~MyMesh();

    bool loadFromOBJ(const char* fileName);
    void prepareBufferObjects();
    void draw();
    void drawImmediate();
    unsigned int getVertNum() const { return vertNum; }
    unsigned int getTriNum() const { return triNum; }
};
#endif
