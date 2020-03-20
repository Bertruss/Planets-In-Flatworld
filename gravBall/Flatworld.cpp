#include "Flatworld.h"
#include <algorithm>
#include <cmath>

struct forceVec {
	float x;
	float y;
};

//allow for the addition of different approaches for comparison
void Flatworld::Sim(int TickCount) {
	for(int i = 0; i < TickCount; i++) {
		switch (simSett) {
			default:
				laughablyNaiveSim();
		}
	}
}

//adds random ball
bool Flatworld::addBall() {
	if (matter.size() == matter.max_size()) {
		return false;
	}
	ball randball;
	randball.posx = (float)(rand() % xdim + 1);
	randball.posy = (float)(rand() % ydim + 1);
	randball.velmag = (float)(rand() % ydim/100 + 1);
	randball.velvec = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * M_PI;
	randball.mass = (float)(rand() % 950000+50000);
	randball.rad = (float)(rand() % ydim / 1000 + 1);
	randball.stat = false;
	matter.push_back(randball);
	return true;
}

//adds ball of given params
bool Flatworld::addBall(float x, float y, float mass, float rad, float velmag, float velvec, bool stat) {
	if (matter.size() == matter.max_size()) {
		return false;
	}
	ball randball;
	randball.posx = x;
	randball.posy = y;
	randball.velmag = velmag; //not greater than 
	randball.velvec = velvec;
	randball.mass = mass;
	randball.rad = rad;
	randball.stat = stat;
	matter.push_back(randball);
	return true;
}

void Flatworld::laughablyNaiveSim(){
	std::vector<forceVec> forceNet; //rolling sum of net forces felt on object at moment of tick
	forceNet.resize(matter.size());
	
	for(int i = 0; i < matter.size(); i++) {
		//current kinetic energy of object i
		ball obj1 = matter[i];
		float energy = (obj1.mass / 2) * pow(obj1.velmag, 2);

		//computing net force on particle i
		for (int j = i + 1; j < matter.size(); j++) {			
			ball obj2 = matter[j];
			
			//relative x y positions
			float xdelt = obj2.posx - obj1.posx;
			float ydelt = obj2.posy - obj1.posy;

			//(distance between the obj)^2
			float dist2 = pow(abs(xdelt), 2) + pow(abs(ydelt), 2);
			float force = (G * obj1.mass * obj2.mass) / dist2;

			//force vector magnitudes along x and y axes, acting on obj1
			float Fx = force * xdelt / sqrtf(dist2);
			float Fy = force * ydelt / sqrtf(dist2);
			forceNet[i].x += Fx;
			forceNet[i].y += Fy;
			forceNet[j].x -= Fx; //equal and opposite force on both objects
			forceNet[j].y -= Fy;
		}

		//new velocity along x and y axes
		float xVd = (forceNet[i].x / obj1.mass * tickInterval) + matter[i].velmag * cosf(matter[i].velvec);
		float yVd = (forceNet[i].y / obj1.mass * tickInterval) + matter[i].velmag * sinf(matter[i].velvec);
		
		//update model velocity
		matter[i].velmag = sqrtf(pow(xVd, 2) + pow(yVd, 2));
		matter[i].velvec = atanf(yVd / xVd);

		//update position using updated velocity
		matter[i].posx += xVd * tickInterval;
		matter[i].posy += yVd * tickInterval;
	}
}

void Flatworld::render(){ //??

}

int main() {
	Flatworld* beta = new Flatworld();

}