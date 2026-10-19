
#include <stdio.h>
#include <stdlib.h>

#define INF 1e9
#define MAX_N 16

int n;
int cost[MAX_N][MAX_N];
int dp[1 << MAX_N][MAX_N];

int tsp(int mask, int position) {
    if (mask == (1 << n) - 1) {
        return (cost[position][0] != -1) ? cost[position][0] : INF;
    }

    if (dp[mask][position] != -1) {
        return dp[mask][position];
    }

    int min_cost = INF;

    for (int next_city = 0; next_city < n; next_city++) {
        if ((mask & (1 << next_city)) == 0 && cost[position][next_city] != -1) {
            int new_cost = cost[position][next_city] + tsp(mask | (1 << next_city), next_city);
            if (new_cost < min_cost) {
                min_cost = new_cost;
            }
        }
    }

    return dp[mask][position] = min_cost;
}

int main() {
    if (scanf("%d", &n) != 1) return 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }

    int result = tsp(1, 0);

    if (result >= INF) {
        printf("-1\n");
    } else {
        printf("%d\n", result);
    }

    return 0;
}
