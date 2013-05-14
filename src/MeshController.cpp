//
//  MeshController.cpp
//  MeshPlayground
//
//  Created by Michail Vanis on 07/05/2013.
//
//

#include "MeshController.h"

using namespace ci;
using namespace std;

MeshController::MeshController() {
}

MeshController::MeshController(string fileName) {
    
    targetScale = 100.0f;
    
    // OBJ
    try {
        ObjLoader loader((DataSourceRef)app::loadAsset(fileName));
        loader.load(&mesh);
        app::console() << "Successfully opened OBJ." << endl;
    }
    catch( ... ) {
        app::console() << "OBJ filename invalid. Creating empty mesh..." << endl;
    }
    vbo = gl::VboMesh(mesh);
    boundingBox = mesh.calcBoundingBox();
    
    // TRANSLATE MESH
    for( size_t v = 0; v < mesh.getVertices().size(); ++v ) {
        mesh.getVertices()[v] = (mesh.getVertices()[v]-boundingBox.getCenter()) * targetScale;
    }
    for( size_t v = 0; v < mesh.getVertices().size(); ++v ) {
        mesh.getVertices()[v] = mesh.getVertices()[v]-boundingBox.getCenter();
    }
    mesh.recalculateNormals();
    updateNormals();
    vbo = gl::VboMesh(mesh);
    
}

void MeshController::update() {
    // Mesh scaling
    if(targetScale != prevScale) {
        
        // Scale and translate mesh
        for( size_t v = 0; v < mesh.getVertices().size(); ++v ) {
            mesh.getVertices()[v] = (mesh.getVertices()[v]-boundingBox.getCenter()) / prevScale * targetScale;
        }
        
        boundingBox = mesh.calcBoundingBox();
        
        // Recenter mesh
        for( size_t v = 0; v < mesh.getVertices().size(); ++v ) {
            mesh.getVertices()[v] = mesh.getVertices()[v]-boundingBox.getCenter();
        }
        
        boundingBox = mesh.calcBoundingBox();
        
        // Update VBO
        vbo = gl::VboMesh(mesh);
        prevScale = targetScale;
        
        // Update normals
        updateNormals();
    }
}

void MeshController::draw() {
    
    // OBJ
    gl::pushMatrices();
    if(drawWireframe) {
        gl::color(0.5f, 0.5f, 0.5f);
        gl::enableWireframe();
        gl::draw(vbo);
        gl::disableWireframe();
    }
    gl::color(1.0f, 1.0f, 1.0f);
    gl::draw(vbo);
    gl::popMatrices();
    
    gl::pushMatrices();
    gl::color(1.0f, 0.0f, 0.0f);
    if(drawNormals) {
        for(vector<VectorPoint>::iterator v=normals.begin(); v<normals.end(); ++v) {
            v->draw();
        }
    }
    gl::popMatrices();
}

// Calculate all centroids and normals from all triangles in current mesh.
void MeshController::updateNormals() {
    
    normals.clear();
    for(size_t i = 0; i < mesh.getNumTriangles(); i++) {
        Vec3f a, b, c, centroid, norm;
        mesh.getTriangleVertices(i, &a, &b, &c);
        
        // Calculate centroid
        centroid.x = (a.x + b.x + c.x)/3;
        centroid.y = (a.y + b.y + c.y)/3;
        centroid.z = (a.z + b.z + c.z)/3;
        
        // Calculate normal
        Vec3f u, v;
        u = b - a;
        v = c - a;
        norm.x = u.y * v.z - u.z * v.y;
        norm.y = u.z * v.x - u.x * v.z;
        norm.z = u.x * v.y - u.y * v.x;
        
        norm.safeNormalize();
        
        // Store VectorPoint
        normals.push_back(VectorPoint(centroid, norm, 1.0f));
    }
}