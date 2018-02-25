#include <stdio.h>
#include "slash.h"

#define total 10
#define amplitude 1
#define frequency 1
#define period 100

unsigned long long output = 1;
unsigned long long slashRandom() {
  output = output * 0xA01731A5AC74E8DBULL;
  output = (output >> 8) | (output << 56);
  return output;
}

double noiseValues[period * period];
double slashNoise2D(double x, double y) {
  // Frequency
  x = x * frequency;
  y = y * frequency;

  // Floor to integer
  unsigned long long xi = (unsigned long long)x;
  unsigned long long yi = (unsigned long long)y;

  // Find period values
  unsigned long long xp = xi % period;
  unsigned long long yp = yi % period;

  // Find output values
  double oa = noiseValues[xp * period + yp];
  double ob = noiseValues[xp * period + (yp == period - 1 ? yp : yp + 1)];
  double oc = noiseValues[(xp == period - 1 ? xp : xp + 1) * period + (yp == period - 1 ? yp : yp + 1)];
  double od = noiseValues[(xp == period - 1 ? xp : xp + 1) * period + yp];

  // Map x, y -> [0, 1]
  x = x - xi;
  y = y - yi;

  // Smoothly map x : [0, 1] -> [oa, od]
  double oad = x * x * x * (x * (x * (6 * od - 6 * oa) + (15 * oa - 15 * od)) + (10 * od - 10 * oa)) + oa;

  // Smoothly map x : [0, 1] -> [ob, oc]
  double obc = x * x * x * (x * (x * (6 * oc - 6 * ob) + (15 * ob - 15 * oc)) + (10 * oc - 10 * ob)) + ob;

  // Smoothly map y : [0, 1] -> [oad, obc] & Amplify
  return (y * y * y * (y * (y * (6 * obc - 6 * oad) + (15 * oad - 15 * obc)) + (10 * obc - 10 * oad)) + oad) * amplitude;
}

int main() {
  for(int i = 0; i < (period * period); i++) {
    noiseValues[i] = (double)((__float128)slashRandom() / (__float128)0xFFFFFFFFFFFFFFFFULL);
  }

  for(double x = 0; x < total; x += 0.1) {
    for(double y = 0; y < total; y += 0.1) {
      printf("%lf	%lf %lf\n", x, y, slashNoise2D(x, y));
    }
  }

  return 0;
}
