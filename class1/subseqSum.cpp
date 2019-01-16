#include<iostream>
using namespace std;

template<typename T>
T subseqSum(T array[], int length)
{
    T max = 0, sum = 0;
    for(int i=0; i<length; i++){
        sum += array[i];
        if(sum>max)
            max = sum;
        else if(sum<0)
            sum = 0;
    }
    return max;
}

int main()
{
    int array[6] = {-2,11,-4,13,-5,-2};
    cout << "the subsequence sum is " << subseqSum(array,sizeof(array)/sizeof(array[1])) << endl;
    return 0;
}
