#include "rotating.h"

// Calculate X coordinate after projection
float calculateX(int i, int j, int k) {
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

// Calculate Y coordinate after projection
float calculateY(int i, int j, int k) {
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

// Calculate Z coordinate after projection
float calculateZ(int i, int j, int k) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

// Calculate and render a surface of the cube
void calculateForSurface(float cubeX, float cubeY, float cubeZ, char ch) {
  x = calculateX(cubeX, cubeY, cubeZ);
  y = calculateY(cubeX, cubeY, cubeZ);
  z = calculateZ(cubeX, cubeY, cubeZ) + distanceFromCam;

  if (z == 0) {
    z = 1e-6; // Avoid division by zero
  }

  ooz = 1 / z;

  xp = (int)(width / 2 + horizontalOffset + K1 * ooz * x * 2);
  yp = (int)(height / 2 + K1 * ooz * y);

  idx = xp + yp * width;
  if (idx >= 0 && idx < width * height) {
    if (ooz > zBuffer[idx]) {
      zBuffer[idx] = ooz;
      buffer[idx] = ch;
    }
  }
}

void RunCube(int delay) {
  std::cout<<"\x1b[2J"; // Clear the screen

  std::chrono::steady_clock::time_point start_time = std::chrono::steady_clock::now();
  while (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start_time) <= std::chrono::seconds(5)) {
    memset(buffer, backgroundASCIICode, width * height); // Clear the buffer
    memset(zBuffer, 0, width * height * sizeof(float)); // Clear the z-buffer

    // Rotate the cube
    A += incrementSpeed;
    B += incrementSpeed;
    C += 0.01;

    // Render the cubes
    for (float cubeX = -20; cubeX < 20; cubeX += 0.5) {
      for (float cubeY = -20; cubeY < 20; cubeY += 0.5) {
        calculateForSurface(cubeX, cubeY, -20, '@');
        calculateForSurface(20, cubeY, cubeX, '$');
        calculateForSurface(-20, cubeY, -cubeX, '~');
        calculateForSurface(-cubeX, cubeY, 20, '#');
        calculateForSurface(cubeX, -20, -cubeY, ';');
        calculateForSurface(cubeX, 20, cubeY, '+');
      }
    }

    std::cout<<"\x1b[H"; // Move the cursor to (0, 0)

    // Display the rendered frame
    for (int k = 0; k < width * height; k++) {
      std::cout<<buffer[k];
      if (k % width == width - 1) {
        std::cout<<'\n';
      }
    }

    std::this_thread::sleep_for(std::chrono::microseconds(delay)); // Sleep to control frame rate
  }
  std::cout<<"########### Done animating the cube ###########"<<std::endl;
}