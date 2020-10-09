#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define pb push_back
using namespace std;

int main()
{
    int n;
    string s;
    cout<<"Enter the string: ";
    cin>>s;
    n=s.size();                 // n = size of string
    char tmp;
    
    int a=0;                    // a initially points to index 0
    for(int i=0;i<n;i++)        
    {
        if(s[i]!='g')
        {
            break;
        }
        a++;
    }

   // cout<<a<<" ";             // a points to element other than green from start

    
    for(int i=a+1;i<n;i++)      // if the element is green than replace it with the element at a and do a++
    {
        if(s[i]=='g')           // swap
        {
            tmp = s[i];
            s[i] = s[a];
            s[a] = tmp;
            a++;
            // cout<<i<<" ";
        }
    }
    
    for(int i=a;i<n;i++)        
    {
        if(s[i]!='y')
        {
            break;
        }
        a++;
    }

    for(int i=a+1;i<n;i++)      // if the element is yellow then replace it with the element at a and do a++
    {
        if(s[i]=='y')           // swap
        {
            tmp = s[i];
            s[i] = s[a];
            s[a] = tmp;
            a++;
            //cout<<"hello  ";
        }
    }
    
    cout<<"SORTED STRING :  ";

    for(int i=0;i<n;i++)
    {
        cout<<s[i];             // finally the sorted string
    }
    return 0;
}