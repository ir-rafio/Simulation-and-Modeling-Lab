#include <bits/stdc++.h>
#include "Simulator.hpp"
#include "RandomNumber.hpp"

int main()
{
    srand(time(0));
    int i, j, n=20, m=30;
    double arvMean=5, srvMean=0;
    double maxDelay, avgDelay, maxQ, avgQ, util, runtime;
    Simulator s(arvMean, srvMean);

    std::ofstream res("result.csv");
	res << "Arrival Mean" << ',' << "Service Mean" << ',' << "Traffic Intensity" << ',' << "Max Delay" << ',' << "Average Delay" << ',' << "Max Queue Length" << ',' << "Average Queue Length" << ',' << "Busy Ratio" << ',' << "Idle Ratio" << ',' << "Total Runtime" << '\n';

	for(i=1; i<n; i++)
	{
	    srvMean=arvMean*i*3/n;
	    maxDelay=0;
        avgDelay=0;
        maxQ=0;
        avgQ=0;
        util=0;
        runtime=0;

	    for(j=0; j<m; j++)
        {
            s.reset(arvMean, srvMean);
            s.run();

            maxDelay+=s.maxDelay();
            avgDelay+=s.avgDelay();
            maxQ+=s.maxQLength();
            avgQ+=s.avgQLength();
            util+=s.utilizationRatio();
            runtime+=s.now();
        }

        res << arvMean << ',' << srvMean << ',' << srvMean/arvMean/3 << ',' << maxDelay/m << ',' << avgDelay/m << ',' << maxQ/m << ',' << avgQ/m << ',' << util/m << ',' << 1-util/m << ',' << runtime/m << '\n';
	}

    // getchar();
    return 0;
}
