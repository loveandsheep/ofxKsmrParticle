//
//  ofxKsmrParticleField.cpp
//  ofxKsmrParticleSample
//
//  Created by Ovis aries on 2015/05/25.
//
//

#include "ofxKsmrParticleField.h"

ofxKsmrParticleField::ofxKsmrParticleField(int numParticles){

	resetParticles(numParticles);
	
}

ofxKsmrParticleField::~ofxKsmrParticleField(){
	
}

void ofxKsmrParticleField::setupFieldFromImage(ofPtr<ofImage> img, int numParticle, bool changeColor)
{
	resetParticles(numParticle);
	changeDefaultFromImage(img, changeColor);
}

void ofxKsmrParticleField::changeDefaultFromImage(ofPtr<ofImage> img, bool changeColor)
{
	ofVec2f size = ofVec2f(img->getWidth(), img->getHeight());
	ofVec3f targPt;
	ofVec2f centerOffset = size / 2.0;
	ofFloatColor cl;
	for (int i = 0;i < pts.size();i++){

		cl.set(0, 0, 0, 0.0);
		while (cl.a < 0.01f && (cl.a < 1.0 || cl.b < 1.0 || cl.g < 1.0)){
			targPt.set(ofRandomuf() * size.x,
					   ofRandomuf() * size.y, 0);
			cl = ofFloatColor(img->getColor(targPt.x, targPt.y));
		}
		
		if (changeColor)
		{
			pts[i].setPosition(targPt - centerOffset);
			vertices[i].set(targPt - centerOffset);
			color[i].set(cl);
		}
		
		pts[i].setDefaultPos(targPt - centerOffset);
		
	}
	
	vbo.updateVertexData(&vertices[0], vertices.size());
	vbo.updateColorData(&color[0], color.size());
	
}

void ofxKsmrParticleField::update()
{
	
	for (int i = 0;i < pts.size();i++)
	{
		pts[i].update();
		
		for (int j = 0;j < atractors.size();j++)
		{
			atractor *at = &atractors[j];
			pts[i].atract(at->pos, at->radius, at->amount);
		}
		
		vertices[i] = pts[i].getPosition();
	}
	
	vbo.updateVertexData(&vertices[0], vertices.size());
	vbo.updateColorData(&color[0], color.size());
}

void ofxKsmrParticleField::draw()
{
	vbo.draw(GL_POINTS, 0, vertices.size());
}

void ofxKsmrParticleField::setPhysicsRandom()
{
	for (int i = 0;i < pts.size();i++)
	{
		pts[i].setPhysics(ofRandomuf() * 5 + 1.0, ofRandom(0.01,0.03));
	}
}

void ofxKsmrParticleField::setPhysics(float mas, float fric){
	for (int i = 0;i < pts.size();i++)
	{
		pts[i].setPhysics(mas, fric);
	}
}

void ofxKsmrParticleField::setVertex(int num, ofVec3f v){
	if (0 <= num && num < vertices.size())
	{
		vertices[num] = v;
	}
}

void ofxKsmrParticleField::resetParticles(int numP)
{
	
	vertices.clear();
	color.clear();
	pts.clear();
	
	for (int i = 0;i < numP;i++)
	{
		vertices.push_back(ofVec3f(ofRandomf()*100,
								   ofRandomf()*100,ofRandomf()*100));
		color	.push_back(ofFloatColor(1,1,1,1));
		pts		.push_back(ofxKsmrParticleBasic(vertices.back()));
	}

	vbo.clear();
	vbo.setVertexData(&vertices[0]	, numP, GL_DYNAMIC_DRAW);
	vbo.setColorData(&color[0]		, numP, GL_DYNAMIC_DRAW);
}

void ofxKsmrParticleField::setAllApproach(float pct)
{
	for (int i = 0;i < pts.size();i++)
	{
		pts[i].setApproach(pct);
	}
}

void ofxKsmrParticleField::resetVertices(const vector<ofVec3f> &pt, const vector<ofFloatColor> &cols)
{
	vertices.clear();
	pts.clear();
	color.clear();
	
	for (int i = 0;i < pt.size();i++)
	{
		vertices.push_back(ofVec3f(pt[i]));
		color.push_back(ofFloatColor(cols[i]));
		pts.push_back(ofxKsmrParticleBasic(vertices.back()));
	}
	
	vbo.clear();
	vbo.setVertexData(&vertices[0], vertices.size(), GL_DYNAMIC_DRAW);
	vbo.setColorData(&color[0], color.size(), GL_DYNAMIC_DRAW);
}

void ofxKsmrParticleField::addAtractor(ofVec3f pos, float radius, float amount)
{
	atractors.push_back(atractor());
	atractors.back().pos = pos;
	atractors.back().radius = radius;
	atractors.back().amount = amount;
}

void ofxKsmrParticleField::setAlpha(float alpha)
{
	for (int i = 0;i < color.size();i++)
	{
		color[i].a = alpha;
	}
	vbo.updateColorData(&color[0], color.size());
}