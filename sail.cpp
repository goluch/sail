#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <iostream>
#include <string>
//#include "stdafx.h"
#include "koala/graph/graph.h"
#include "koala/io/text.h"
#include "koala/algorithm/weights.h"

#include <fstream>

using namespace std;
using namespace Koala;
using namespace Koala::IO;

int main(int argc, char* argv[])
{
	float denseGrid(int x,int y,float fi,float dx,float dy,int ix,int jx);
	int ChartPoint(float fi,float la,float Slat, float Slon,float Lat_Step,float Lon_Step,int nEW);
	int rumb(double direction,int nRumb);
	int roundPoint(double number);
	FILE *fileV, *fileU;
	const int chartEW =84;
	const int chartSN =42;
	const int nodes= 3528;
	float SLAT=54.217;//poczatek mapy
    float SLON=18.069;  //poczatek mapy
	float LAT_STEP=0.017121951219512;
    float LON_STEP=0.017132530120482;
	 float tabWindx[chartSN][chartEW];       ////     ^Y   ------->x
	 float tabWindy[chartSN][chartEW];
	 float tabWindxyS[chartSN][chartEW];
	 float tabWindxyD[chartSN][chartEW];
	 
	 


	 
//	 SLAT=54.217 N
//SLON=18.069 E
//LAT_STEP=0.017121951219512
//LON_STEP=0.017132530120482
//Number of cell U (E-W):84
//Number of cells V (S-N):42 



	 float **tabNextToWpt = new float *[nodes];
for ( int k = 0; k < nodes; k++ )
   tabNextToWpt[k] = new float [nodes];



int landSea[chartSN][chartEW]={
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};






	  float Vs16 [36][16]={///wspó³czynniki zmiany predkoœci max 16 m/s
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
	{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2},
		{-1,0.2,0.4,0.45,0.5,0.65,0.8,0.7,0.6,0.7,0.8,0.65,0.5,0.45,0.4,0.2}
	};

	  fileU = fopen("u.csv","r");//rb
	  fileV = fopen("v.csv","r");//rb
	
	 float f;
	 char l[10];

	   if (fileU!=NULL){
  //  cout<<"ok file"<<endl;
	   }else cout<<"no file - u.csv";

	   if (fileV!=NULL){
  //  cout<<"ok file"<<endl;
	   }else cout<<"no file - v.csv";

	   for (int i=0;i<chartSN;i++){
		   for (int j=0;j<chartEW;j++){
			   if (i==0&j==0){	
				   fscanf (fileV, "%c%c%c%c%c%c%c%c%g",l,l,l,l,l,l,l,l,&f);
			   }
			   else{
				   fscanf (fileV, "%c%f",l,&f);
			   }
			   tabWindx[i][j]=f;
		   }
	   }
	   fclose (fileV);

	   for (int i=0;i<chartSN;i++){
		   for (int j=0;j<chartEW;j++){
			   if (i==0&j==0){	
				   fscanf (fileU, "%c%c%c%c%c%c%c%c%g",l,l,l,l,l,l,l,l,&f);
			   }
			   else{
				   fscanf (fileU, "%c%f",l,&f);
			   }
			   tabWindy[i][j]=f;
		   }
	   }
	   fclose (fileU);
// DIRECTION=57.29578*(ATAN2(UGRD,VGRD))+180 
//SPEED=SQRT(UGRD*UGRD+VGRD*VGRD) 

  for ( int i = 0; i < chartSN; i++ )
	for ( int j = 0; j < chartEW; j++ ){
		 tabWindxyD[i][j]=57.29578*(atan2(tabWindx[i][j],tabWindy[i][j]))+180;
		 tabWindxyS[i][j]=sqrt(tabWindx[i][j]*tabWindx[i][j]+tabWindy[i][j]*tabWindy[i][j]);
			
	}
 //
	 for ( int i = 0; i < chartSN; i++ )
	 for ( int j = 0; j < chartEW; j++ ){
	//	 cout<<i<<j<<"  "; 
	//	 cout<<endl<<"nR : "<<tabWindxyD[i][j]<<" ";//trzeba zmniejszyæ do 16 kierunków
	//	   cout<<" Dir : "<<rumb(tabWindxyD[i][j],16)<<" ";//trzeba zmniejszyæ do 16 kierunków
	//      cout<<"S : "<<roundPoint(tabWindxyS[i][j])<<endl;//trzeba stopniowaæ prêdkoœæ co 1 m/s 
		  tabWindxyD[i][j]=rumb(tabWindxyD[i][j],16); //przejscie na odczyt wiatru w skali Rumbowej np. skala 0 do 15 rumbów co 22,5
		  tabWindxyS[i][j]=roundPoint(tabWindxyS[i][j]); // pr wiatru co 1m/s

	 }

	// http://localhost/sail/ws/?string=19.168052673339844,54.49915638719443,18.92017364501953,54.611845593021656,Ship1
	 ////////////////////////macierz sasiedztwa

	 float d; //droga miedzy wpt
	
	
	 int x,p=0;
	 int heading;
	 heading=0;
	 int windD;
	 int windS;
	 int nX=chartSN;
	 int nY=chartEW;
	
	 float fStart,fEnd;
	  float lStart,lEnd;


	  vector<char*> v;
	char* chars_array = strtok(argv[1], ",");
	while (chars_array)
	{
		v.push_back(chars_array);
		chars_array = strtok(NULL, ",");
	}
	

	fStart=stof(v[1]);lStart=stof(v[0]);fEnd=stof(v[3]);lEnd=stof(v[2]);


	  int startPoint=ChartPoint(fStart,lStart,SLAT, SLON,LAT_STEP,LON_STEP,chartEW);
	  int endPoint=ChartPoint(fEnd,lEnd,SLAT, SLON,LAT_STEP,LON_STEP,chartEW); 

	  
	//http://localhost/sail/ws/?string=18.281593322753906,54.233731647827426,18.27198028564453,54.261414171490685,Ship1


typedef Graph<int, int> MyGraph;

MyGraph g;
MyGraph::PVertex V[nodes];
MyGraph::PEdge tmpE;
for (int i=0;i<nodes;i++)
	V[i]=g.addVert(i);
//for (int i=0;i<nodes*16;i++)
//MyGraph::PEdge E[i];

int k=0;
AssocArray < MyGraph::PEdge, DijkstraHeap::EdgeLabs < int > > edgeMap;  
AssocArray < MyGraph::PVertex, DijkstraHeap::VertLabs < int, MyGraph > > vertMap;	

vector < MyGraph::PVertex > vecV;
vector < MyGraph::PEdge > vecE;


	   for ( int i = 0; i < chartSN; i++ ){
		   for ( int j = 0; j < chartEW; j++ ){
			    if(landSea[i][j]!=1/*&&
						   landSea[i+1][j]!=1&&
						   landSea[i+2][j+1]!=1&&
						   landSea[i-1][j]!=1&&
						   landSea[i-2][j+1]!=1&&
						   landSea[i][j+1]!=1&&
						   landSea[i-2][j-1]!=1&&
						   landSea[i][j-1]!=1&&
						   landSea[i-1][j-2]!=1&&
						   landSea[i+1][j+1]!=1&&
						   landSea[i+1][j-1]!=1&&
						   landSea[i-1][j+1]!=1&&
						   landSea[i-1][j-1]!=1&&
						   landSea[i-1][j+2]!=1&&
						   landSea[i+2][j-1]!=1&&
						   landSea[i+1][j-2]!=1&&
						   landSea[i+1][j+2]!=1*/){
			   for  (int r = -2; r <=2; r++){           //dooko³a punktu,
				   for (int c = -2; c <=2; c++){
					  
						  
                if ((r==0&&c==2)|(r==2&&c==0)|(r==-2&&c==0)|(r==0&&c==-2)|(r==2&&c==2)|(r==-2&&c==-2)|(r==2&&c==-2)|(r==-2&&c==2))
					int a=1;
				else{
					   if (i+r>=0&j+c>=0&i+r<nX&j+c<nY){
						   if (r==-1&&c==0){
							   heading=0;
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);//
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);//œrednia wiatru na odcinku
							   d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
						   }
						   else if (r==-2&c==1){
							   heading=1;
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i-1][j]+tabWindxyD[i-1][j+1])/2)/3);//œrednia wiatru na odcinku srqrt(5)
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i-1][j]+tabWindxyS[i-1][j+1])/2)/3);
					///
					///
							   d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
						   }
                    else if (r==-1&&c==1){
						heading=2;
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
						d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
					}
                    else if (r==-1&c==2){
						heading=3;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i][j+1]+tabWindxyD[i-1][j+1])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
						d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
					}
                    else if (r==0&&c==1){
						heading=4;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
						d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
					}
                    else if (r==1 && c==2){
						heading=5;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i][j+1]+tabWindxyD[i+1][j+1])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i][j+1]+tabWindxyS[i+1][j+1])/2)/3);
						d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);//odleg³oœæ odcinka
					}
                    else if (r==1&&c==1)
					{heading=6;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}//odleg³oœæ odcinka}
                    else if (r==2&c==1)
					{heading=7;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i+1][j]+tabWindxyD[i+1][j+1])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i+1][j]+tabWindxyS[i+1][j+1])/2)/3);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==1&&c==0)
					{heading=8;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==2&c==-1)
					{heading=9;///d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i+1][j-1]+tabWindxyD[i+1][j])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i+1][j-1]+tabWindxyS[i+1][j])/2)/3);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==1&&c==-1)
					{heading=10;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==1&c==-2)
					{heading=11;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i+1][j-1]+tabWindxyD[i][j-1])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i+1][j-1]+tabWindxyS[i][j-1])/2)/3);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==0&&c==-1)
					{heading=12;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==-1&c==-2)
					{heading=13;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i-1][j-1]+tabWindxyD[i][j-1])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i-1][j-1]+tabWindxyS[i][j-1])/2)/3);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                    else if (r==-1&&c==-1   )
					{heading=14;///d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP);
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c])/2);////œrednia wiatru na odcinku
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c])/2);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
					}
                   else if (r==-2&c==-1)
				   {heading=15;//d=denseGrid(i,j,(SLON+SLAT)/2,LAT_STEP,LON_STEP); 
					windD=roundPoint((tabWindxyD[i][j]+tabWindxyD[i+r][j+c]+(tabWindxyD[i-1][j-1]+tabWindxyD[i-1][j])/2)/3);
					windS=roundPoint((tabWindxyS[i][j]+tabWindxyS[i+r][j+c]+(tabWindxyS[i-1][j-1]+tabWindxyS[i-1][j])/2)/3);
					d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);

					}
                    else if (r==0&&c==0)//punkt œrodkowy, 
					{heading=100;
				  d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
				   }
					//else if(r==0&&c==2|r==2&&c==0|r==-2&&c==0|r==0&&c==-2|r==2&&c==2|r==-2&&c==-2|r==2&&c==-2|r==-2&&c==2){
				



       x=heading-windD; //wind from mapgrid
                    
        if (x<0) {
            x=x+16;
		}
       
        
        if (heading==100){
            x=0; 
			windS=0;
		}
       int timeToNextWpt;
		float mpsToknot=1.943844;
	  timeToNextWpt=1000000 * d/(mpsToknot*(Vs16[windS][x]));   ///d -droga do nastepnego wpt w Mm, windS si³a wiatru w m/s, x kierunek, Vs16 charakterystyka biegunowa S¯, wynik czs w godzinach
       

	   		tabNextToWpt[0][0]=d/(Vs16[1][x]);
	   int xx;
	   int yy;
	   xx=(i)*nY+j;
	   yy= (i+r)*nY+j+c;
	   if ( timeToNextWpt>0){
		   
		tabNextToWpt[xx][yy]= timeToNextWpt;
		tmpE=g.addArc(V[xx],V[yy],k);     //E tablica Assoc
		edgeMap[tmpE].length=timeToNextWpt;
		//cout<<edgeMap[tmpE].length;
		k++;
	   }
	   }
	   }
}
}
}
}
}




//http://localhost/sail/ws/?string=18.116798400878903,54.29108203342648,18.110618591308594,54.33033903700911,Ship1
//18.2345,54.6789,WNW,19.0231,55.1426,SSE


// Do Debugowania

//Set<MyGraph::PEdge> debugEdges;
//debugEdges = g.getEdgeSet(V[endPoint], V[startPoint]);
//
//	for (MyGraph::PEdge e = debugEdges.first(); e; e = debugEdges.next(e))
//		cout << e->info << " " << edgeMap[e].length << endl;
//	cout << endl;

//fstream fileGraph;
//	fileGraph.open("graph.txt", ios_base::out);
//	writeGraphText(g, fileGraph, RG_VertexLists | RG_Info);
//	fileGraph.close();


double distance = DijkstraHeap::distances(g, vertMap, edgeMap, V[startPoint], V[endPoint]);
int z, latest_z = 0, nLatLon;
float Lat,Lon;
int eLen = DijkstraHeap::getPath(g, vertMap, V[endPoint], DijkstraHeap::outPath(back_inserter(vecV), blackHole));
	//cout << "Vertices on the path:";

//nLatLon=vecV[0]->info;
	//		Lat=SLAT+ceil(nLatLon/chartEW)*LAT_STEP;
	//		Lon=SLON+(nLatLon%chartEW)*LON_STEP;
		//	cout <<Lon<<","<<Lat<<",";



		for (int i = 0; i <= eLen-1; i++) {
			z=(vecV[i]->info)-(vecV[i+1]->info);			
			nLatLon=vecV[i]->info;
			Lat=SLAT+ceil(nLatLon/chartEW)*LAT_STEP;
			Lon=SLON+(nLatLon%chartEW)*LON_STEP;
	
			if (z != latest_z) {

				latest_z = z;

			cout <<Lon<<","<<Lat<<",";
			// dodane przez Goluch
			// pomijanie identycznych oznaczen kursów


				switch (z) {
				case chartEW: cout << "N";
					break;
				case 2 * chartEW - 1: cout << "NNE";
					break;
				case chartEW - 1: cout << "NE";
					break;
				case chartEW - 2: cout << "ENE";
					break;
				case -1: cout << "E";
					break;
				case -(chartEW + 2) : cout << "ESE";
					break;
				case -(chartEW + 1) : cout << "SE";
					break;
				case -(2 * chartEW + 1) : cout << "SSE";
					break;
				case -chartEW: cout << "S";
					break;
				case -(2 * chartEW - 1) : cout << "SSW";
					break;
				case -(chartEW - 1) : cout << "SW";
					break;
				case -(chartEW - 2) : cout << "WSW";
					break;
				case 1: cout << "W";
					break;
				case chartEW + 2: cout << "WNW";
					break;
				case chartEW + 1: cout << "NW";
					break;
				case 2 * chartEW + 1: cout << "NNW";
					break;
				default: cout << "ERROR";
				}
				
				if (i <eLen - 1)cout << ",";
			}			
		}

//writeGraphText(g, cout, RG_VertexLists | RG_Info);

		return 0;
}




int roundPoint(double number)
 {
    return (number >= 0) ? (int)(number + 0.5) : (int)(number - 0.5);
 }
 

int rumb(double direction,int nRumb)
 {
	 int result=((direction +360/(2*nRumb)) /360)* nRumb;
	 
	 if(result>=nRumb)
		 result=result-nRumb;

	return result;
 }
float denseGrid(int x,int y,float fi,float dx,float dy,int ix,int jx){///d=denseGrid(r,c,SLAT,LAT_STEP,LON_STEP,i,j);
 float b;
 fi=fi +ix*dx;
	 if (x>1|x<-1){
		 b=pow(pow(dx*cos(fi),2)+pow(2*dy,2),0.5); //uwzgledniamy zboczenie naw.

	 }else if(y>1|y<-1){
		 b=pow(pow(2*dx*cos(fi),2)+pow(dy,2),0.5);
	 }else 
	 {
	  b=pow(pow(dx*cos(fi),2)+pow(dy,2),0.5);
	 }

 return b;
 }


int ChartPoint(float fi,float la,float Slat, float Slon,float Lat_Step,float Lon_Step,int nEW){
	int tab[2];
	int x,y,pUV;
	y=int((fi-Slat)/Lat_Step);
	x=int((la-Slon)/Lon_Step);

	   pUV=y*nEW+x;


	
	return pUV;
}