#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<array>
#include<bits/stdc++.h>
#include<math.h>
#define pb push_back 
using namespace std;

bool sortcol0( const vector<int>& v1, const vector<int>& v2 )       // sort vector on the basis of 0th column(x coordinate)
{ 
    return v1[0] < v2[0]; 
} 
bool sortcol1( const vector<int>& v1, const vector<int>& v2 )       // sort vector on the basis of 1st column(y coordinate)
{ 
    return v1[1] < v2[1]; 
} 

void closestPair(vector<vector<int>> a,int *m1,int *n1,int *m2,int *n2)             // DIVIDE AND CONQUER
{
    if(a.size()==1)
        return;
    if(a.size()==2)                     // if size = 2 the simply check that pair
    {
        int x1,y1,x2,y2;
        x1=a[0][0];
        y1=a[0][1];
        x2=a[1][0];
        y2=a[1][1];
        //cout<<x1<<y1<<x2<<y2<<endl;
        if(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) < sqrt(pow(*m1-*m2,2)+pow(*n1-*n2,2)))         // if the new pair distance is small
            {                                                                             // then change the ans pair
                *m1=x1;     *n1=y1;
                *m2=x2;     *n2=y2;
                //cout<<"hi";
            }
        return;
    }

    int n=a.size();
    vector<vector<int>> a1,a2,sy;
    for(int i=0;i<n/2;i++)
    {
        a1.pb(a[i]);                                        // a1 stores the 1st half
        //cout<<a1[i][0]<<" "<<a1[i][1];
    }
    //cout<<endl;
    for(int i=n/2;i<n;i++)
    {
        a2.pb(a[i]);                                        // a2 stores the 2nd half
        //cout<<a2[i-n/2][0]<<" "<<a2[i-n/2][1];
    }
    closestPair(a1,m1,n1,m2,n2);                            // 1st recursive call
    closestPair(a2,m1,n1,m2,n2);                            // 2nd recursive call

    //------------------------------------------------------------------------- CROSS PAIR---------------------------------------------------------

    int minDistn=sqrt(pow(*m1-*m2,2)+pow(*n1-*n2,2));   
    int lowerLimit=a2[0][0]-minDistn;                               // SETTING LEFT BOUNDARY
    int upperLimit=a2[0][0]+minDistn;                               // SETTING RIGHT BOUNDARY
    
    for(int i=0;i<n;i++)
    {
        if(a[i][0] >= lowerLimit && a[i][0] <= upperLimit)          // IF THE ELEMENT IS BETWEEN THE LEFT AND RIGHT BOUNDARY THE STORES IT INTO sy
        {
            sy.pb(a[i]);
        }
    }
    // for(int i=0;i<sy.size();i++)
    // {
    //     cout<<sy[i][0]<<" "<<sy[i][1]<<endl;
    // }
    sort(sy.begin(), sy.end(),sortcol1);                        // sort sy according to y coordinate

    for(int i=0;i<sy.size();i++)                                // FOR EACH sy WE CHECK UPTO 15 ELEMENTS NEXT TO IT
    {
        for(int j=i;j<sy.size()-1;j++)                          
        {
            if(j-i>15)                                          // IF ELEMENT IS 16 POSITION FAR THEN BREAK
                break;
            int x1,y1,x2,y2;
            x1=sy[i][0];
            y1=sy[i][1];
            x2=sy[i+1][0];
            y2=sy[i+1][1];
            //cout<<x1<<y1<<x2<<y2<<endl;
            if(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) < sqrt(pow(*m1-*m2,2)+pow(*n1-*n2,2)))        // if the new pair distance is small
                {                                                                            // then change the ans pair
                    *m1=x1;     *n1=y1;
                    *m2=x2;     *n2=y2;
                    //cout<<"hi";
            }
        }
    }
    return;
}

void bruteForce(vector<vector<int>> v)
{
    int m1,n1,m2,n2;
    m1=-99999;      // stores 1st x
    n1=-99999;      // stores 1st y
    m2=99999;      // stores 2nd x
    n2=99999;      // stores 2nd y
    for(int i=0;i<v.size();i++)                           // for every element check the smallest pair
    {
        int x1,y1,x2,y2;
        x1=v[i][0];
        y1=v[i][1];
        for(int j=i+1;j<v.size();j++)                   // iterate from i+1 to last element
        {
            x2=v[j][0];
            y2=v[j][1];
            if(sqrt(pow(x1-x2,2)+pow(y1-y2,2)) < sqrt(pow(m1-m2,2)+pow(n1-n2,2)))       // if the new pair distance is small 
                {                                                                       // then change the ans pair
                    m1=x1;  n1=y1;
                    m2=x2;  n2=y2;
                    //cout<<"hi";
            }
        }
    }
    cout<<"BRUTE FORCE : closest pair is: ("<<m1<<","<<n1<<") , ("<<m2<<","<<n2<<")\n";
    return;
}

int main() {
    int n,tmp1,tmp2,m1,n1,m2,n2;
    m1=-99999;                  // stores 1st x
    n1=-99999;                  // stores 1st y
    m2=99999;                   // stores 2nd x
    n2=99999;                   // stores 2nd y
    int* x1=&m1;    int* y1=&n1;    int* x2=&m2;    int* y2=&n2;

    cin>>n;
    vector<vector<int>> a;
    for(int i=0;i<n;i++)
    {
        vector<int> v;
        cin>>tmp1>>tmp2;
        v.pb(tmp1);                             // stores x,y coordinate in vector v
        v.pb(tmp2);
        a.pb(v);                                // pushes vector v in a (2d vector)
    }
    sort(a.begin(), a.end(),sortcol0);          // sort 2d vector on the basis of x coordinate

    bruteForce(a);                              // ans by brute force method

    closestPair(a,x1,y1,x2,y2);                 // ans by divide and conquer algorithm

    cout<<"DIVIDE AND CONQUER ALGORITHM : closest pair is: ("<<*x1<<","<<*y1<<") , ("<<*x2<<","<<*y2<<")";
    return 0;
}
