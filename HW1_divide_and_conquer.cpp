#include<iostream>
#include<vector>
#include<fstream>
#include<string>

using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::string;

int correct_weight;

int sumWeight(const vector<int>& coins, const int& start, const int& end)
{
    int tmp = 0;
    for(int i = start ; i <= end; i++)
        tmp += coins[i];
    return tmp;
}

bool NotEqualWeightMulti(const vector<int>& coins, const int& start1, const int& end1, const int& start2, const int& end2)
{
    return sumWeight(coins, start1, end1) != sumWeight(coins, start2, end2);
}

bool EqualWeightSingle(const vector<int>& coins, const int& index1, const int& index2)
{
    return coins[index1] == coins[index2];
}

int Find(const vector<int>& coins, int start, int end)
{
    int N = end-start+1;
    int interval = N/4;
    if(N >= 4)
    {
        if(NotEqualWeightMulti(coins, start, start+interval-1, start+interval, start+2*interval-1))
        {
            correct_weight = coins[end];
            return Find(coins, start, start+2*interval-1);
        }
        else if(NotEqualWeightMulti(coins, start+2*interval, start+3*interval-1, start+3*interval, start+4*interval-1))
        {
            correct_weight = coins[start];
            return Find(coins, start+2*interval, start+4*interval-1);
        }
        else
        {
            correct_weight = coins[start];
            return Find(coins, start+4*interval, end);
        }
    }
    else if(N == 3)
    {
        if(EqualWeightSingle(coins, start, start+1))
        {
            return start+2;
        }
        else if(EqualWeightSingle(coins, start+1, start+2))
        {
            return start;
        }
        else 
            return start+1;
    }
    else if(N == 2)
    {
        if(coins[start] == correct_weight) 
            return start+1;
        else    
            return start;
    }
    else
    {
        return start;
    }
}

int FindFake(const vector<int>& coins)
{
    return Find(coins,0,coins.size()-1);
}

int main()
{
    int N;
    vector<int> coins;

    while(cin>>N)
    {
        coins.resize(N);
        for(int i = 0;i < N;i++)
        {
            cin>>coins[i];
        }
        cout<<FindFake(coins)<<endl;
    }
}