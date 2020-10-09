#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define pb push_back
using namespace std;

int getMedian(vector<int> v)            // returns median
{
    int n=v.size();
    sort(v.begin(),v.end());
    return n%2!=0 ? v[n/2] : (v[n/2-1]+v[n/2])/2;
}

//------------------------------------------------------------------------------------------------------------

int getPivot(vector<int> v)             // recursively get Median of Medians
{
    if(v.size() ==1)
        return v[0];

    int n=v.size();
    vector<int> medians;
    
    int i;
    for(i=0;i+4<n;i=i+5)        
    {
        vector<int> tmp;
        tmp.pb(v[i]);
        tmp.pb(v[i+1]);
        tmp.pb(v[i+2]);
        tmp.pb(v[i+3]);
        tmp.pb(v[i+4]);
        medians.pb(getMedian(tmp));
    }
    vector<int> tmp;    // for vector having elements not a multiple of 5
    if(i<n)
        tmp.pb(v[i]);
    if(i+1<n)
        tmp.pb(v[i+1]);
    if(i+2<n)
        tmp.pb(v[i+2]);
    if(i+3<n)
        tmp.pb(v[i+3]);
    if(tmp.size()>0)
        medians.pb(getMedian(tmp));

    // for(int i=0;i<medians.size();i++)
    // {
    //     cout<<medians[i]<<" ";
    // }
    // cout<<endl;

    return getPivot(medians);                   // recursive call

}

//----------------------------------------------------------------------------------------------------------------

void kSmallest(vector<int> v,int k)
{
    int pivot=getPivot(v);            // get pivot recursively
    
    int n=v.size();
    vector<int> a,b,m;
    for(int i=0;i<n;i++)              // loop for dividing the elements into 3 groups
    {
        if(v[i]<pivot)
        {
            a.pb(v[i]);               // 1------- "a" vector containing elements smaller than pivot
        }
        else if(v[i]>pivot)
        {
            b.pb(v[i]);               // 2-------- "b" vector containing elements greater than pivot
        }
        else
        {
            m.pb(v[i]);               // 3-------- "m" vector containing elements = to pivot
        }
    }
    if(a.size() >= k)
    {
        kSmallest(a,k);                         // if k is in left part
    }
    else if(a.size()+m.size() < k)
    {
        kSmallest(b,k-a.size()-m.size());       // if k is in right part
    }
    else
    {
        cout<<"My answer: "<<m[0]<<" ";         // if k is in middle part then return
        return;
    }
    return;
}

//----------------------------------------------------------------------------------------------------------

int main() {
    int n,k,tmp;
    cin>>n>>k;
    vector<int> v;
    for(int i=0;i<n;i++)
    {
        cin>>tmp;
        v.pb(tmp);
    }  

    kSmallest(v,k);
    
    sort(v.begin(),v.end());            // just for checking
    cout<<"\nRight ans: "<<v[k-1];      
    return 0;
}
