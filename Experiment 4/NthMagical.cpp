class Solution {
public:
const int mod=1e9+7;
long long lcm(int a,int b){
    return (a*b)/(__gcd(a,b));
}
    int nthMagicalNumber(int n, int a, int b) {
        long long lc=lcm(a,b);
        long long low=1, high=1ll*n*min(a,b);
        while(low<high){
            long long mid=low+(high-low)/2;
            long long count=(mid/a)+(mid/b)-(mid/lc);

            if(count<n){
                low=mid+1;
            }
            else{
                high=mid;
            }
        }
     return low%mod;   
    }
};