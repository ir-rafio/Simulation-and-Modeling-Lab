#include <bits/stdc++.h>
#include "Simulator.hpp"
#include "RandomNumber.hpp"

int main()
{
    srand(time(0));
    int j, m=30;
    double arvMean=10, srvMin=3.5, srvMax=4.5, crewMin=6, crewMax=11, crewDelayMin=2.5, crewDelayMax=3.5;
    Simulator s(arvMean, srvMin, srvMax, crewMin, crewMax, crewDelayMin, crewDelayMax);

    std::ofstream res("result.csv");
	res << "Max Delay" << ',' << "Average Delay" << ',' << "Max Queue Length" << ',' << "Average Queue Length" << ',' << "Busy Ratio" << ',' << "Idle Ratio" << ',' << "Hogged out Ratio" << '\n';

    double maxDelay=0, avgDelay=0, maxQ=0, avgQ=0, util=0, hog=0;
	for(j=0; j<m; j++)
    {
        s.reset(arvMean, srvMin, srvMax, crewMin, crewMax, crewDelayMin, crewDelayMax);
        s.run();

        maxDelay+=s.maxDelay();
        avgDelay+=s.avgDelay();
        maxQ+=s.maxQLength();
        avgQ+=s.avgQLength();
        util+=s.utilizationRatio();
        hog+=s.hogoutRatio();
    }

    res << maxDelay/m << ',' << avgDelay/m << ',' << maxQ/m << ',' << avgQ/m << ',' << util/m << ',' << 1-util/m << ',' << hog/m << '\n';

    return 0;
}
