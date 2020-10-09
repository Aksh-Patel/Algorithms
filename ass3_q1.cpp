#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<array>
#include<bits/stdc++.h>
#define pb push_back 
using namespace std;

void closestPair(vector<int> a,int *x,int *y)
{
    if(a.size()==1)                 
    return;
    if(a.size()==2)                         //if size is 2 the simply check the distance between those numbers
    {
        if(a[1]-a[0] < *y-*x)
            {
                *x=a[0];
                *y=a[1];
                // cout<<"hi";
            }
        return;
    }
    int n=a.size();
    vector<int> a1,a2;
    for(int i=0;i<n/2;i++)              // stores 1st half in a1
    {
        a1.pb(a[i]);
        // cout<<a1[i];
    }
    for(int i=n/2;i<n;i++)              // stores 2nd half in a2
    {
        a2.pb(a[i]);
        // cout<<a2[i-n/2];
    }
    closestPair(a1,x,y);                // 1st recursive call
    closestPair(a2,x,y);                // 2nd recursive call
    if(a2[0]-a1[n/2-1] < *y-*x)         // if the pair is across the boundary
    {
        *x=a1[n/2-1];
        *y=a2[0];
    }
    return;
}

int main() {
    int n,tmp,x,y;
    x=-999999;                          // stores 1st element of pair which has minimum distance
    y=9999999;                          // stores 2nd element of pair which has minimum distance
    int* x1=&x;
    int* y1=&y;
    cin>>n;
    vector<int> a;
    for(int i=0;i<n;i++)                // storing points in vector
    {
        cin>>tmp;
        a.pb(tmp);
    }
    sort(a.begin(),a.end());            // sorting vector
    closestPair(a,x1,y1);               // function call
    cout<<"closest pair is: "<<*x1<<" "<<*y1;
    return 0;
}
