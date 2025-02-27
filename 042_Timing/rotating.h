#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std::literals::chrono_literals;

static float A = 0.0, B = 0.0, C = 0.0; // Rotation angles for the cube
static const int width = 160, height = 44; // Width and height of the terminal window
static float zBuffer[160 * 44]; // Z-buffer for depth calculations
static char buffer[160 * 44]; // Buffer for storing ASCII characters
static int backgroundASCIICode = ' '; // ASCII character for the background
static int distanceFromCam = 100; // Distance from the camera to the cube
static float horizontalOffset = 0; // Horizontal offset for projection
static float K1 = 40; // Projection constant
static float incrementSpeed = 0.07; // Rotation speed (adjust as needed)

static float x, y, z; // 3D coordinates
static float ooz; // One over z (reciprocal of z)
static int xp, yp; // Screen coordinates
static int idx; // Buffer index

// Calculate X coordinate after projection
float calculateX(int i, int j, int k);

// Calculate Y coordinate after projection
float calculateY(int i, int j, int k);

// Calculate Z coordinate after projection
float calculateZ(int i, int j, int k);

// Calculate and render a surface of the cube
void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch);

void RunCube(int delay);