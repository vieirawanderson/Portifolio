/* ---------------------------------------------------------------------------
**
** HookesLaw.cpp
** Use Hookes Law with Springs and Dampers to make an convincent animation of
** a the motion (waves) of a liquid drop on a volume of the same liquid.
**
** Authors: Castro de Almeida, Ana Carolina (anacarolina@csu.fullerton.edu)
** 			Vieira, Wanderson Felipe (vieira@csu.fullerton.edu)
**
** --------------------------------------------------------------------------*/

#include <iostream>
#include <list>
#include <vector>
#include "GFXMath.h"


#ifndef SQUARE_OF_TWO
#define SQUARE_OF_TWO        1.41421356237
#endif

using namespace std;

/* ----- CLASS VERTEX BEGIN ----- */
class Vertex
{
public:
	int index;
	bool inside;
	Vec3 newPosition;
	Vec3 oldPosition;
	float acceleration, velocity, damperFactor, k;

	Vertex(int, Vec3, bool);
	
};

Vertex::Vertex(int newIndex, Vec3 position, bool isInside){
	index = newIndex;
	inside = isInside; // if on border this should be false
	oldPosition = position;
	newPosition = position;
	acceleration = 0;
	velocity = -0.0;
	damperFactor = 0.02;
	// damperFactor = 0.025;
	// k = 0.01;
	k = 0.0125;
	
}
/* ----- CLASS VERTEX END ----- */

/* ----- CLASS MESH BEGIN ----- */
class Mesh
{
public:
	int height, width;
	vector<Vertex> vertexList;
	vector<Vertex> verticesInside;
	vector<int> indexBuffer;
	int dist;
	float k, damperFactor, gravity;
	short damperHeight;

	Mesh(int, int, int);
	void generateVertices();
	void triangleStrip();
	void waves();
	void calculateForce(int);
	float deltaX(Vertex, Vertex);
	float getSinBetween(Vertex, Vertex);
	void getVertexList();
	void getVerticesInside();
	void getIndexBuffer();
	void getVertex(int);
};

Mesh::Mesh(int newHeight, int newWidth, int newDistance){

	height = newHeight;
	width = newWidth;
	dist = newDistance;
	damperHeight = 10.0;
	//k = 0.0125;
	//damperFactor = 0.025;

	generateVertices();
	triangleStrip();

	int initialVertex = width*height/2;
	if (width%2 == 0){
		initialVertex +=  - width/2;
	}
	int n = verticesInside[initialVertex].index; // starting vertex acceleration
	vertexList[n].velocity = -0.7;
	vertexList[n].damperFactor = 0.0075;

	//Just put more two force mass to apply in other verteces
	vertexList[n+5].velocity = -0.7;
	vertexList[n+5].damperFactor = 0.0075;

	vertexList[n-5].velocity = -0.7;
	vertexList[n-5].damperFactor = 0.0075;
}

void Mesh::generateVertices(void){
	int index = 0;
	int widthAux = width + 2; // sum 2 to height so we can have a fake border with null vertices
	int heightAux = height + 2; // sum 2 to height so we can have a fake border with null vertices

	// create a vector with all the vertices on the mesh (vertexList) and a vector with all the vertices that are not in the border (verticesInside)
	for (int i = 0; i<heightAux; i++){
		for (int j = 0; j<widthAux; j++){

			if (i == 0 || i == height + 1 || j == 0 || j == width + 1){
				vertexList.push_back(Vertex(index, Vec3(i*dist,damperHeight,j*dist), false)); // have to multiply i and j by dist to give the right displacement
			}
			else{
				vertexList.push_back(Vertex(index, Vec3(i*dist,damperHeight,j*dist), true)); // have to multiply i and j by dist to give the right displacement
				verticesInside.push_back(vertexList[index]);
			}
			
			index++;
		}
	}
}


void Mesh::triangleStrip(void){
	for (int i = 0; i < verticesInside.size() - width; i++){
		// indexBuffer.push_back(i); // get index for verticesInside vector
		// indexBuffer.push_back(i+width); // get index for verticesInside vector
		indexBuffer.push_back(verticesInside[i].index); // get index for vertexList vector
		indexBuffer.push_back(verticesInside[i+width].index); // get index for vertexList vector
		// if the vertex is the last one, then we should repeat 'i + width' and 'i+1' to generate the degenerate triangles
		if ((i+1) % width == 0 && (i+width+1<verticesInside.size())){
			// indexBuffer.push_back(i+width); // get index for verticesInside vector
			// indexBuffer.push_back(i+1); // get index for verticesInside vector
			indexBuffer.push_back(verticesInside[i+width].index); // get index for vertexList vector
			indexBuffer.push_back(verticesInside[i+1].index); // get index for vertexList vector
		}
	}
}


void Mesh::waves(void){
	// update vertices positions
	for (int i = 0; i < verticesInside.size();i++){
		vertexList[verticesInside[i].index].oldPosition = vertexList[verticesInside[i].index].newPosition;

	}

	// calculate force of the vertices
	for (int i = 0; i < verticesInside.size();i++){
		// verticesInside[i] = calculateForce(verticesInside[i]);
		calculateForce(verticesInside[i].index);
	}
}

void Mesh::calculateForce(int n){
	float x = vertexList[n].oldPosition[1] - damperHeight;
	vertexList[n].acceleration = -(vertexList[n].k * x) - (vertexList[n].damperFactor * vertexList[n].velocity);
	
	float forceAdj;
	int widthAux = width + 2; // width must be incremented by 2 in order to count the null vertices at the border
	
	Vertex adj = vertexList[n-widthAux]; // upper neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;
	//vertexList[n-widthAux].velocity += (deltaX(vertexList[n], adj)) * 0.025;

	adj = vertexList[n-widthAux+1]; // upper diagonal neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;

	adj = vertexList[n-1]; // left neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;


	adj = vertexList[n+1]; // right neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;


	adj = vertexList[n+widthAux-1]; // lower diagonal neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;


	adj = vertexList[n+widthAux]; // lower neighbor
	forceAdj = -k * (deltaX(vertexList[n], adj)) * getSinBetween(vertexList[n], adj) * adj.inside;
	vertexList[n].acceleration += forceAdj;


	vertexList[n].newPosition[1] = vertexList[n].oldPosition[1] + vertexList[n].velocity;
	vertexList[n].velocity += vertexList[n].acceleration;

	//SPREAD
	float aux = 0.08; //setted value to decrease atenuation caused by Euler's method

	// Trying to apply some force to the neighbors
	vertexList[n-widthAux].velocity -= vertexList[n].acceleration*aux;
	vertexList[n-widthAux+1].velocity -= vertexList[n].acceleration*aux;
	vertexList[n-1].velocity -= vertexList[n].acceleration*aux;
	vertexList[n+1].velocity -= vertexList[n].acceleration*aux;
	vertexList[n+widthAux-1].velocity -= vertexList[n].acceleration*aux;
	vertexList[n+widthAux].velocity -= vertexList[n].acceleration*aux;

}

float Mesh::deltaX(Vertex v, Vertex adjacent){
	int index = v.index;
	int adjIndex = adjacent.index;
	float x0 = dist, x1;

	if (adjIndex == index - (width+2) + 1 || adjIndex == index + (width+2) - 1){
		x0 = SQUARE_OF_TWO * dist;
	}

	x1 = distance(v.oldPosition, adjacent.oldPosition);
	
	return x1 - x0;
}

float Mesh::getSinBetween(Vertex v, Vertex adjacent){
	float deltaY = adjacent.oldPosition[1] - v.oldPosition[1];
	float x1 = distance(adjacent.oldPosition, v.oldPosition);

	return deltaY/x1;
}

void Mesh::getVertexList(void){
	// print the vertexList vector
	for (int i = 0; i < vertexList.size();i++){
		cout<<"Index: "<<vertexList[i].index<<" Inside: "<<vertexList[i].inside<<" Position: "<<vertexList[i].oldPosition;
	}
	cout<<""<<endl;
}

void Mesh::getIndexBuffer(void){
	// print the verticesInside vector
	cout<<"Index buffer: "<<endl;
	for (int i = 0; i <indexBuffer.size(); i++){
		cout<<indexBuffer[i]<<" ";
	}
	cout<<""<<endl;
}

void Mesh::getVerticesInside(void){
	// print the verticesInside vector
	for (int i = 0; i < verticesInside.size();i++){
		cout<<"Index: "<<verticesInside[i].index<<" Position: "<<verticesInside[i].oldPosition;
	}
	cout<<""<<endl;
}

void Mesh::getVertex(int n){
	// print the especified vertex
	cout<<"Index: "<<vertexList[n].index<<" Position: "<<vertexList[n].oldPosition;
	cout<<"Velocity: "<<vertexList[n].velocity<<" Acceleration: "<<vertexList[n].acceleration<<endl;
	cout<<""<<endl;
}
/* ----- CLASS MESH END ----- */

// int main(){

// 	Mesh m = Mesh(20,20,1);
// 	// m.waves();
// 	// m.getVertexList();
// 	// m.getVerticesInside();

// 	for (int j = 0; j < 500; j++)
// 		m.waves();

// 	//m.triangleStrip();
// 	//m.getIndexBuffer();
// 	//m.waves();

// 	return (0);
// }
