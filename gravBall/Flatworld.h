#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
# define M_PI           (float)3.14159265358979323846  /* pi */
# define M_G			(float).0000000000667430  /* gravitational constant */

struct forceVec {
	float x;
	float y;
};

struct ball {
	float posx; 
	float posy;
	float velmag; // in m/s
	float velvec; // in radians deviance counter-clockwise from the x axis
	float mass; //in kg TODO:...or maybe large power of ten kg's ?
	float rad; //collisions are annoying...ignore for now
	bool stat; //toggle for whether the particle is mobile
};

class Flatworld {
	public:
		Flatworld(int xdim, int ydim, int MaxObj, float tickInterval) : xdim(xdim), ydim(ydim), simSett(1), tickInterval((float)0.01) {
			matter.reserve(MaxObj);
		}
		//demomode?
		Flatworld() : xdim(10*10^9), ydim(10*10^9), simSett(1), tickInterval((float)0.01) {
			matter.reserve(2);
			addBall((float)(5*10^9), (float)(5*10^9), (float)(6*10^24), (float)(8 * 10 ^ 6), (float)0.0, (float)0.0, true); //da earf
			addBall((float)(9 * 10 ^ 9), (float)(5 * 10 ^ 9), (float)(7 * 10 ^ 22), (float)(2*10^6), (float)(36*10^5), (float)(1/4*M_PI), false); //da mooooon
		}
		bool addBall(); //adds random ball
		bool addBall(float x, float y, float mass, float rad, float velmag, float velvec, bool stat); //adds ball of given params
		void setGmult(int mult);
		void setTickInterval(float newinterval);
		void reset();
		void Sim(int TickCount); //progress simulation by given number of ticks, updates location 
	private:
		void laughablyNaiveSim();
		int xdim; // in meters
		int ydim; // in meters
		float tickInterval; // in seconds, amount of "realtime" progressed by every update of the simulation. smaller tick ~ more accurate sim.
		int simSett; //chooses simulation approach. 
		float Gmult = 1;
		float G = (float)0.0000000000667430;
		std::vector<ball> matter;
};
