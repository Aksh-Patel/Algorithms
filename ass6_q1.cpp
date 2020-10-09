#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define pb push_back
using namespace std;

int left(int i)
{
    return 2*i+1;
}

int right(int i)
{
    return 2*i+2;
}

int parent(int i)
{
    return i%2==0?i/2-1:i/2;
}

void heapify(vector<int> &v , int i)
{
    int leftIndex = left(i);
    int rightIndex = right(i);
    int largest;

    if( leftIndex <= v.size()-1 && v[leftIndex] > v[i] )
        largest = leftIndex;
    else 
        largest = i;

    if(rightIndex <= v.size()-1 && v[rightIndex] > v[largest] )
        largest = rightIndex;

    if(largest!=i)
    {
        int tmp = v[largest];
        v[largest]=v[i];
        v[i]=tmp;
        heapify(v,largest);
    }
    return;
}

void buildHeap(vector<int> &v)
{
    int n= v.size();
    for(int i=n/2; i >= 0 ;i--)
    {
        heapify(v,i);
    }
    return;
}

void heapSort(vector<int> v)
{
    vector<int> sortVec;
    int n=v.size();
    for(int i=n-1; i > 0 ; i--)
    {
        sortVec.pb(v[0]);
        // cout<<v[0]<<" ";
        int tmp = v[0];
        v[0] = v[i];
        v[i] = tmp;
        v.pop_back();

        heapify(v,0);
    }
    sortVec.pb(v[0]);
    // cout<<v[0]<<"\n";
    cout<<"\nAfter Heap Sort: ";
    for(int i=0;i<sortVec.size();i++)
    {
        cout<<sortVec[i]<<" ";
    }
    cout<<endl;
    return;
}

void insertPriorityQueue(vector<int> &v,int x)
{
    v.pb(x);
    int i=v.size()-1;
    //cout<<"i is: "<<i<<" ";
    while( i > 0  &&  v[i] > v[parent(i)] )
    {
        int tmp = v[i];
        v[i]=v[parent(i)];
        v[parent(i)]=tmp;
        i=parent(i);
    }
    return;
}

int  removeMaxPriorityQueue(vector<int> &v)
{
    int max = v[0];
    v[0]=v[v.size()-1];
    v.pop_back();
    heapify(v,0);
    return max;
}

void modifyPriorityQueue(vector<int> &v,int index,int newValue)
{
    int oldValue = v[index];
    v[index] = newValue;
    if(newValue > oldValue)         // violation on upper side
    {
        while( index > 0  &&  v[index] > v[parent(index)] )
        {
            int tmp = v[index];
            v[index] = v[parent(index)];
            v[parent(index)] = tmp;
            index = parent(index);
        }
    }
    else if(newValue < oldValue)    // violation on lower side
    {
        heapify(v,index);
    }
    return;
}

int findIndexPriorityQueue(vector<int> &v,int value)
{
    for(int i=0;i<v.size();i++)
    {
        if(v[i]==value)
        {
            return i;
        }
    }
    cout<<"element not found!!!";
    return 0;    
}

int deletePriorityQueue(vector<int> &v,int index)
{
    int deletedElement = v[index];
    v[index] = v[v.size()-1];
    v.pop_back();

    int oldValue = deletedElement;
    int newValue = v[index];
    if(newValue > oldValue)         // violation on upper side
    {
        while( index > 0  &&  v[index] > v[parent(index)] )
        {
            int tmp = v[index];
            v[index] = v[parent(index)];
            v[parent(index)] = tmp;
            index = parent(index);
        }
    }
    else if(newValue < oldValue)    // violation on lower side
    {
        heapify(v,index);
    }
    return deletedElement;
}

int main()
{
    int n,tmp;
    cout<<"Enter total number of elements: ";
    cin>>n;
    vector<int> v;
    cout<<"Enter elements values: ";
    for(int i=0;i<n;i++)
    {
        cin>>tmp;
        v.pb(tmp);
    }

    //-------------------------------------------------    Part 1      -----------------------------

    buildHeap(v);

    cout<<"\nAfter Building Heap: ";
    for(int i=0;i<n;i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;

    heapSort(v);
    

    //---------------------------------------------        Part 2           ----------------------------------
    //---------------------------------------------     Priority Queue     -----------------------------------
    while(1)
    {
        int choice;
        
        cout<<"\n\n1: Insert Element\n";
        cout<<"2: Extract Maximum\n";
        cout<<"3: Modify Queue\n";
        cout<<"4: Find Index\n";
        cout<<"5: Delete Element\n";
        cout<<"6: Quit\n\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        cout<<endl;
        switch(choice)
        {
            case 1: 
            {
                int newElementValue;
                cout<<"Enter the value of the new element to insert: ";
                cin>>newElementValue;
                insertPriorityQueue(v,newElementValue);
                cout<<"After Inserting "<<newElementValue<<" ::  ";
                for(int i=0;i<v.size();i++)
                {
                    cout<<v[i]<<" ";
                }
                cout<<endl;
                break;
            }

            case 2:
            {
                int max = removeMaxPriorityQueue(v);
                cout<<"Maximum element is: "<<max<<endl;
                cout<<"After Extracting Maximum element: ";
                for(int i=0;i<v.size();i++)
                {
                    cout<<v[i]<<" ";
                }
                cout<<endl;
                break;
            }

            case 3:
            {
                int index,value;
                cout<<"Enter Index and new value of element you want to modify: ";
                cin>>index>>value;
                modifyPriorityQueue(v,index,value);
                cout<<"Modified Priority Queue: ";
                for(int i=0;i<v.size();i++)
                {
                    cout<<v[i]<<" ";
                }
                cout<<endl;
                break;
            }

            case 4:
            {
                int value;
                cout<<"Enter the value of element you want to find index: ";
                cin>>value;
                int index = findIndexPriorityQueue(v,value);
                cout<<"index is: "<<index<<endl;
                break;
            }

            case 5:
            {
                int value;
                cout<<"Enter the element you want to delete: ";
                cin>>value;
                int index = findIndexPriorityQueue(v,value);
                deletePriorityQueue(v,index);
                cout<<"After Deleting: ";
                for(int i=0;i<v.size();i++)
                {
                    cout<<v[i]<<" ";
                }
                cout<<endl;
                break;
            }

            case 6:
            {
                exit(0);
            }
        }
    }
    
    
    return 0;
}
