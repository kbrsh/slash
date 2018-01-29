#include "slash.h"
#include "stdio.h"

#define total 100
#define amplitude 1
#define frequency 1
#define period 10

unsigned long long output = 1;
unsigned long long slashRandom() {
  output = output * 0xA01731A5AC74E8DBULL;
  output = (output >> 8) | (output << 56);
  return output;
}

double noiseValues[period];
double slashNoise(double x) {
  // Frequency
  x = x * frequency;

  // Floor to integer
  unsigned long long xi = (unsigned long long)x;

  // Find output values
  unsigned long long xp = xi % period;
  double ya = noiseValues[xp];
  double yb = noiseValues[xp == period - 1 ? xp : xp + 1];

  // Map x -> [0, 1]
  x = x - xi;

  // Smoothly map x : [0, 1] -> [ya, yb] & Amplify
  return (x * x * x * (x * (x * (6 * yb - 6 * ya) + (15 * ya - 15 * yb)) + (10 * yb - 10 * ya)) + ya) * amplitude;
}

int main() {
  for(int i = 0; i < period; i++) {
    noiseValues[i] = (double)((__float128)slashRandom() / (__float128)0xFFFFFFFFFFFFFFFFULL);
  }

  for(double x = 0; x < total; x += 0.1) {
    printf("%lf	%lf\n", x, slashNoise(x));
  }

  return 0;
}
