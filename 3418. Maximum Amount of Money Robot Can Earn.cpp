#include <bits/stdc++.h>

using namespace std;
/*
get the state definition
dp[i][j][k]
(i,j) coordinates , k is the number of used neutralization
if you don't use neutralization
    dp[i][j][0] = max(dp[i-1][j][0],dp[i][j-1][0]) +coins[i-1][j-1]
if you will use
     int topNotUse = dp[i - 1][j][k] + coins[i - 1][j - 1];
     int leftNotUse = dp[i][j - 1][k] + coins[i - 1][j - 1];
     int topUse = dp[i - 1][j][k - 1] + max(coins[i - 1][j - 1], 0);
     int leftUse = dp[i][j - 1][k - 1] + max(coins[i - 1][j - 1], 0);
     dp[i][j][k] = max(dp[i][j][k], max(topNotUse, max(topUse, max(leftNotUse, leftUse))));

  return dp[m][n][2];
*/
class Solution
{
public:
    int maximumAmount(vector<vector<int>> &coins)
    {
        int m = coins.size();
        int n = coins[0].size();
        vector dp(m + 1, vector(n + 1, array<int, 3>{INT_MIN / 2, INT_MIN / 2, INT_MIN / 2}));
        dp[1][1][0] = coins[0][0];
        for (int k = 1; k <= 2; k++)
        {
            dp[1][1][k] = max(coins[0][0], 0);
        }

        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (i == 1 && j == 1)
                    continue;
                dp[i][j][0] = max(dp[i - 1][j][0], dp[i][j - 1][0]) + coins[i - 1][j - 1];
                for (int k = 1; k <= 2; k++)
                {
                    int topNotUse = dp[i - 1][j][k] + coins[i - 1][j - 1];
                    int leftNotUse = dp[i][j - 1][k] + coins[i - 1][j - 1];
                    int topUse = dp[i - 1][j][k - 1] + max(coins[i - 1][j - 1], 0);
                    int leftUse = dp[i][j - 1][k - 1] + max(coins[i - 1][j - 1], 0);
                    dp[i][j][k] = max(dp[i][j][k], max(topNotUse, max(topUse, max(leftNotUse, leftUse))));
                }
            }
        }
        return dp[m][n][2];
    }
};