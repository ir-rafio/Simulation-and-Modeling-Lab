#include <bits/stdc++.h>
#include "Simulator.hpp"
#include "RandomNumber.hpp"

int main()
{
    srand(time(0));
    int i, j, n=9, m=30;
    int threshold[]={20, 20, 20, 20, 40, 40, 40, 60, 60}, cap[]={40, 60, 80, 100, 60, 80, 100, 80, 100};
    double orderingCost, holdingCost, shortageCost, cost;
    Simulator s(20, 40);

    std::ofstream res("result.csv");
    res << "Order Threshold" << ',' << "Inventory Capacity" << ',' << "Average Ordering Cost" << ',' << "Average Holding Cost" << ',' << "Average Shortage Cost" << ',' << "Average Cost" << '\n';

    for(i=0; i<n; i++)
    {
        orderingCost=0;
        holdingCost=0;
        shortageCost=0;
        cost=0;

        for(j=0; j<m; j++)
        {
            s.reset(threshold[i], cap[i]);
            s.run();

            orderingCost+=s.avgOrderingCost();
            holdingCost+=s.avgHoldingCost();
            shortageCost+=s.avgShortageCost();
            cost+=s.avgCost();
        }

        res << threshold[i] << ',' << cap[i] << ',' << orderingCost/m << ',' << holdingCost/m << ',' << shortageCost/m << ',' << cost/m << '\n';
    }

    return 0;
}
