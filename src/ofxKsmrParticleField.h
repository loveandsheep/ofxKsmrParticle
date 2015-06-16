//
//  ofxKsmrParticleField.h
//  ofxKsmrParticleSample
//
//  Created by Ovis aries on 2015/05/25.
//
//

#ifndef __ofxKsmrParticleSample__ofxKsmrPartileField__
#define __ofxKsmrParticleSample__ofxKsmrPartileField__

#include "ofMain.h"
#include "ofxKsmrParticleBasic.h"

struct atractor{
	ofVec3f pos;
	float radius;
	float amount;
};

class ofxKsmrParticleField{
public:
	
	ofxKsmrParticleField(int numParticles = 5000);
	~ofxKsmrParticleField();

	void setupFieldFromImage(ofPtr<ofImage> img, int numParticle, bool changeColor = true);
	void changeDefaultFromImage(ofPtr<ofImage> img, bool changeColor = true);
	
	void update();
	void draw();
	
	void addAtractor(ofVec3f pos, float radius, float amount = 1.0);
	
	void setPhysicsRandom();
	void setPhysics(float mas, float fric);
	
	void setAllApproach(float pct);
	void setAlpha(float alpha);
	void setVertex(int num, ofVec3f v);
	const vector<ofVec3f> & getVertices(){return vertices;}
	const vector<ofFloatColor> & getColors(){return color;}
	const vector<ofxKsmrParticleBasic> & getPts(){return pts;}
	
	vector<atractor> atractors;
	vector<ofFloatColor> color;
	ofxKsmrParticleBasic & getPt(int num){if (0 <= num && num < pts.size())return pts[num];}
	
	void resetVertices(const vector<ofVec3f> & pt, const vector<ofFloatColor> & cols);
	
protected:
	
	void resetParticles(int numP);
	ofVbo vbo;
	
	vector<ofVec3f> vertices;
	vector<ofxKsmrParticleBasic> pts;
	
};

#endif /* defined(__ofxKsmrParticleSample__ofxKsmrPartileField__) */
