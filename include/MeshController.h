//
//  MeshController.h
//  MeshPlayground
//
//  Created by Michail Vanis on 07/05/2013.
//
//

#ifndef MeshPlayground_MeshController_h
#define MeshPlayground_MeshController_h

#pragma once
#include "cinder/Vector.h"
#include "cinder/gl/gl.h"
#include "cinder/ObjLoader.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/AppBasic.h"
#include "VectorPoint.h"
#include <vector>

class MeshController {
public:
    MeshController();
    MeshController(std::string fileName);
    
    void draw();
    void update();
    void updateNormals();
    
    cinder::TriMesh mesh;
    cinder::gl::VboMesh vbo;
    cinder::gl::GlslProg shader;
    cinder::gl::Texture texture;
    float targetScale = 1.0f;
    float prevScale = 1.0f;
    cinder::AxisAlignedBox3f boundingBox;
    
    std::vector<VectorPoint> normals;
    
    bool drawNormals;
    bool drawWireframe;
};

#endif
