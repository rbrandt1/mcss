#ifndef COMMON_H
#define COMMON_H

#include <omp.h>

#include <chrono>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>
#include <type_traits>
#include <utility>

#if defined(SINGLE)
using real_type = float;
#else   // SINGLE
using real_type = double;
#endif  // SINGLE

enum Material { WATER, AIR, BONE, TISSUE, GOLD };

real_type computeScrParam(const Material &mat, real_type ptot2);

real_type computeMFP(const Material &mat, real_type beta2, real_type scrpar);

real_type sampleCosTheta(real_type scrpar, real_type rn);

void rotateToLabFrame(real_type &u, real_type &v, real_type &w,
                      const real_type &u1, const real_type &u2,
                      const real_type &u3);

const real_type kMolierBc[] = {877.879, 1.02281, 1645.05, 888.813,
                               12481.2};  // 1/mm

const real_type kMolierXc2[] = {0.0661905, 7.88813e-05, 0.17879, 0.0647072,
                                9.72643};      // MeV^2/mm
const real_type kPI = 3.14159265358979323846;  // Pi

const real_type kMASS = 0.510998910;  // electron mass [MeV]
const real_type theEKin = 0.128;      // [MeV]

const real_type thePC2 = theEKin * (theEKin + 2.0 * kMASS);
const real_type theBeta2 = thePC2 / (thePC2 + kMASS * kMASS);

const int longiDistNumBin = 201;
const real_type longiDistInvD = (longiDistNumBin - 1.0) / 2.0;

const int transDistNumBin = 101;
const real_type transDistInvD = (transDistNumBin - 1.0) / 1.0;

struct Track {
    real_type fPosition[3]{};   // rx, ry, rz
    real_type fDirection[3]{};  // dx, dy, dz normalised to 1
    real_type fTrackLength{};   // cumulative track length

    Track() { Reset(); }

    void Reset() {
        fPosition[0] = 0.0;
        fPosition[1] = 0.0;
        fPosition[2] = 0.0;

        fDirection[0] = 0.0;
        fDirection[1] = 0.0;
        fDirection[2] = 1.0;

        fTrackLength = 0.0;
    }
};

struct Histograms {
    std::vector<real_type> longiHist;
    std::vector<real_type> transHist;
    Histograms(const unsigned long longBins, const unsigned long transBins)
        : longiHist(longBins), transHist(transBins) {}

    Histograms(std::vector<real_type> longi_hist,
               std::vector<real_type> trans_hist)
        : longiHist(std::move(longi_hist)), transHist(std::move(trans_hist)) {}
    Histograms() = default;
};
#endif