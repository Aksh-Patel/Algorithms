#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<string>
#include<cmath>
#define pb push_back
using namespace std;

int mul(vector<int> a,vector<int> b)
{
    if(a.size()==1 && b.size()==1)          // if only one number is left then simply multiply it
    {
        //cout<<a[0]*b[0]<<" ";
        return a[0]*b[0];
    }
    int m=a.size();
    int n=b.size();
    if(m>n)                                 // if length of a > b
    {
        if(m%2!=0)                          // makes length even
        {
            a.pb(0);    //temporary
            m++;
            for(int i=m;i>0;i--)            // inserting 0 at first to make it even
                a[i]=a[i-1];
            a[0]=0;
        }
        int diff=m-n;
        for(int i=1;i<=diff;i++)
            b.pb(0);
        for(int i=n-1;i>=0;i--)             // making size of both vector same
        {
            b[i+diff]=b[i];
        }
        for(int i=0;i<diff;i++)
            b[i]=0;
        n+=diff;
    }
    else                                    // if length of b>a
    {
        if(n%2!=0)                          // makes length even 
        {
            b.pb(0);    //temporary
            n++;
            for(int i=n;i>0;i--)            // inserting 0 at first to make it even
                b[i]=b[i-1];
            b[0]=0;
        }
        int diff=n-m;
        for(int i=0;i<diff;i++)
            a.pb(0);
        for(int i=m-1;i>=0;i--)             // making size of both vector same
        {
            a[i+diff]=a[i];
        }
        for(int i=0;i<diff;i++)
            a[i]=0;
        m+=diff;
    }
    
    vector<int> p1,p2,q1,q2,tempp1p2,tempq1q2,p1p2,q1q2;
    for(int i=0;i<m/2;i++)
    {
        p1.pb(a[i]);                                // p1 contains first half of a
        q1.pb(b[i]);                                // q1 contains first half of b
        p2.pb(a[m/2+i]);                            // p2 contains second half of a
        q2.pb(b[m/2+i]);                            // q2 contains second half of b
    }
    //----------------------------------------------- p1p2=p1+p2 , q1q2=q1+q2 (in binary)-------------------------
    int c1=0,c2=0;
    for(int i=p1.size()-1;i>=0;i--)
    {
        tempp1p2.pb((c1+p1[i]+p2[i])%2);
        c1=(c1+p1[i]+p2[i])/2;
        tempq1q2.pb((c2+q1[i]+q2[i])%2);
        c2=(c2+q1[i]+q2[i])/2;
    }
    if(c1==1 )
        tempp1p2.pb(1);
    if(c2==1)
        tempq1q2.pb(1);
    for(int i=tempp1p2.size()-1;i>=0;i--)
        p1p2.pb(tempp1p2[i]);
    for(int i=tempq1q2.size()-1;i>=0;i--)
        q1q2.pb(tempq1q2[i]);
    //------------------------------------------------------------------------------------------------------------
    int a1=mul(p1,q1);                                  // 1st recursive call
    int a2=mul(p2,q2);                                  // 2nd recursive call
    int a3=mul(p1p2,q1q2);  // a3=(p1+p2)*(q1+q2)       // 3rd recursive call
    int ans=a1*pow(2,m) + (a3-a1-a2)*pow(2,m/2) + a2;   // final ans
    //cout<<ans<<" ";
    return ans;
}

int main() {
    string x,y;
    cin>>x>>y;
    vector<int> a,b;
    for(int i=0;i<x.size();i++)         // storing first binary number
    {
        a.pb(((int)x[i]-48));
    }
    for(int i=0;i<y.size();i++)         // storing second binary number
    {
        b.pb(((int)y[i]-48));
    }
    int ans=mul(a,b);                   // function call
    cout<<"\nfinal ans: "<<ans;
    return 0;
}
