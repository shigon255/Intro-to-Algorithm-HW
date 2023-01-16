#include <iostream>
#include <vector>

int main()
{
    // input part
    int n, m;
    std::cin>>n>>m;

    std::vector<std::vector<int> > profit(n, std::vector<int>(m+1));
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            std::cin>>profit[i][j];
        }
    }

    // initialize dp table
    // dp: Op_profit in the report, which indicates the maximum profit
    // By building up the dp table, the maximum profit that n projects using m resources are able to  produce can be found (dp[n][m] )
    std::vector<std::vector<int> > dp(n+1, std::vector<int>(m+1));
    for(int j=0;j<m+1;j++)
    {
        dp[0][j] = 0;
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            dp[i][j] = -1;
        }
    }

    // trace: For (i,j), record k such that the dp[i-1][j-k]+profit[i-1][k] result in the max profit
    // Using trace, how the resources are allocated to each project can be found (for debug)
    /*
    std::vector<std::vector<int> > trace(n+1, std::vector<int>(m+1));

    for(int i=0;i<n+1;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            trace[i][j] = -1;
        }
    }
    */  


    // dp: dp[i][j] = max_k(dp[i-1][j-k]+profit[i-1][k]), 0 <= k <= j
    for(int i=1;i<n+1;i++)
    {
        for(int j=0;j<m+1;j++)
        {
            // case: 0 resource to be added to project i (k=0)
            if(dp[i][j] < dp[i-1][j])
            {
                dp[i][j] = dp[i-1][j];
                // trace[i][j] = 0;
            }
            for(int k=0; k<=j;k++)
            {
                if(dp[i][j] < dp[i-1][j-k]+profit[i-1][k])
                {
                    dp[i][j] = dp[i-1][j-k]+profit[i-1][k];
                    // trace[i][j] = k; 
                }
            }
        }
    }

    // Output the maximum profit
    std::cout << dp[n][m];

    // Finding how the resources are allocated (for debug)
    /*
    std::vector<int> path;
    int tmpj = m;
    for(int i=n;i>0;i--)
    {
        path.push_back(trace[i][tmpj]);
        tmpj -= trace[i][tmpj];
    }

    for(int i=n-1;i>=0;i--)
    {
        std::cout<<"Project "<<n-i<<" allocate "<<path[i]<<" resources"<<std::endl;
    }
    for(auto v:trace)
    {
        for(auto c:v)
        {
            std::cout<<c<<" ";
        }
        std::cout<<std::endl;
    }
    */
}