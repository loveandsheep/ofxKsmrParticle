//
//  ofxKsmrParticleEmitter.h
//  openCLFluid_test
//
//  Created by Ovis aries on 2015/05/26.
//
//

#ifndef __openCLFluid_test__ofxKsmrParticleEmitter__
#define __openCLFluid_test__ofxKsmrParticleEmitter__

#include "ofMain.h"
#include "ofxKsmrParticleBasic.h"

class ofxKsmrParticleEmitter{
public:
	
	void setup(int stockParticle = 3000);
	void update();
	void draw();
	
	void emitParticle(int numParticle);

	void setEmitColor(ofFloatColor col){emt_col = col;}
	void setEmitPosition(ofVec3f pos){emt_pos = pos;}
	void setEmitDirection(ofVec3f vec){emt_vec = vec;}
	void setEmitRandomness(float pct){emt_rand = pct;}
	void setEmitLife(int frame, float randomness = 0.0f)
	{
		life_frame = frame;
		life_rand = randomness;
	};
	
	ofFloatColor emt_col;
	ofVec3f emt_pos;
	ofVec3f emt_vec;
	float	emt_rand;
	int		life_frame;
	float	life_rand;
	
	int emitIndex;
	
	vector<ofxKsmrParticleBasic> pts;
	vector<ofVec3f> verts;
	vector<ofFloatColor> colors;
	
	ofVbo vbo;
};

#endif /* defined(__openCLFluid_test__ofxKsmrParticleEmitter__) */
