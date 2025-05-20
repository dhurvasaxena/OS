#include <stdio.h>  
int main(){  

  
    int n, m;  
    n = 5;                         
    m = 3;                         
    int alloc[5][3] = {{0, 1, 0},    
                       {2, 0, 0},   
                       {3, 0, 2},   
                       {2, 1, 1},    
                       {0, 0, 2}};   
  
    int max[5][3] = {{7, 5, 3},  // P0 // MAX Matrix  
                     {3, 2, 2},  // P1  
                     {9, 0, 2},  // P2  
                     {2, 2, 2},  // P3  
                     {4, 3, 3}}; // P4  
  
    int avail[3] = {3, 3, 2};
    int f[n], ans[n], ind = 0;  
    for (int k = 0; k < n; k++)  
    {  
        f[k] = 0;  
    }  
    int need[n][m];  
    for (int i = 0; i < n; i++)  
    {  
        for (int j = 0; j < m; j++)  
            need[i][j] = max[i][j] - alloc[i][j];  
    }  
    for (int k = 0; k < 5; k++)  
    {  
        for (int i = 0; i < n; i++)  
        {  
            if (f[i] == 0)  
            {  
                int flag = 0;  
                for (int j = 0; j < m; j++)  
                {  
                    if (need[i][j] > avail[j])  
                    {  
                        flag = 1;  
                        break;  
                    }  
                }  
                if (flag == 0)  
                {  
                    ans[ind++] = i;  
                    for (int y = 0; y < m; y++)  
                        avail[y] += alloc[i][y];  
                    f[i] = 1;  
                }  
            }  
        }  
    }
    int flag = 1;  
    for (int i = 0; i < n; i++)  
    {  
        if (f[i] == 0)  
        {  
            flag = 0;  
            printf("The following system is not safe");  
            break;  
        }  
    }  
    if (flag == 1)  
    {  
        printf("Following is the SAFE Sequence\n");  
        for (int i = 0; i < n - 1; i++)  
            printf(" P%d ->", ans[i]);  
        printf(" P%d", ans[n - 1]);  
    }  
    return (0);  

}