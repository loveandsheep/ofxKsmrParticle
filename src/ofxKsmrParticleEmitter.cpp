//
//  ofxKsmrParticleEmitter.cpp
//  openCLFluid_test
//
//  Created by Ovis aries on 2015/05/26.
//
//

#include "ofxKsmrParticleEmitter.h"

void ofxKsmrParticleEmitter::setup(int stockParticle)
{
	emitIndex = 0;
	verts.clear();
	colors.clear();
	for (int i = 0;i < stockParticle;i++){
		verts.push_back(ofVec3f(0,0,0));
		colors.push_back(ofFloatColor(1.0,1.0,1.0,1.0));
		pts.push_back(ofxKsmrParticleBasic());
		pts.back().setPhysics(1.0, 0.03);
	}
	
	vbo.setVertexData(&verts[0], stockParticle, GL_DYNAMIC_DRAW);
	vbo.setColorData(&colors[0], stockParticle, GL_DYNAMIC_DRAW);
	
	emt_pos.set(0, 0, 0);
	emt_vec.set(0, 0, 0);
	emt_rand = 0.0;
	life_frame = 60;
	life_rand = 0.0;
	emt_col.set(1.0,1.0,1.0,1.0);
}

void ofxKsmrParticleEmitter::update()
{
	for (int i = 0;i < pts.size();i++){
		pts[i].update();
		verts[i] = pts[i].getPosition();
		colors[i].a = 1.0 - pts[i].age / float(pts[i].life);
	}
	
	vbo.updateVertexData(&verts[0], verts.size());
	vbo.updateColorData(&colors[0], colors.size());
}

void ofxKsmrParticleEmitter::draw()
{
	vbo.draw(GL_POINTS, 0, verts.size());
}

void ofxKsmrParticleEmitter::emitParticle(int numParticle)
{
	for (int i = 0;i < numParticle;i++){
		bool emitted = false;
		while (!emitted) {
			if (!pts[emitIndex].isLive){
				pts[emitIndex].isLive = true;
				pts[emitIndex].age = 0;
				pts[emitIndex].setPosition(emt_pos);
				pts[emitIndex].setAcc(ofVec3f(0,0,0));
				pts[emitIndex].setVec(ofVec3f(emt_vec.x + ofRandomf() * emt_rand,
											  emt_vec.y + ofRandomf() * emt_rand,
											  emt_vec.z + ofRandomf() * emt_rand));
				pts[emitIndex].life = life_frame + life_rand * 30;
				colors[emitIndex] = emt_col;
				emitted = true;
			}
			emitIndex++;
			if (emitIndex >= pts.size()) emitIndex = 0;
		}
	}
}