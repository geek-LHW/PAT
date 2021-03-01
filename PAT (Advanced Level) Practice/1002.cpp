#include<iostream>
#include<iomanip>
using namespace std;

int main(){
    double Poly[1001] = {0}; 
    //多项式A
    int k;
    scanf("%d", &k);
    for (int i = 0; i < k;i++){
        int exp;
        double coef;
        scanf("%d%lf", &exp, &coef);
        Poly[exp] = coef;
    }
    //多项式B
    scanf("%d", &k);
    for (int i = 0; i < k;i++){
        int exp;
        double coef;
        scanf("%d%lf", &exp, &coef);
        Poly[exp] += coef;
    }
    //统计多项式非零项
    int num = 0;
    for (int i = 0; i <1001;i++){
        if(Poly[i]!=0){
            num++;
        }  
    }
    printf("%d", num);
    //打印
    for (int i = 1000; i >=0;i--){
        if(Poly[i]!=0){
            printf(" %d %0.1f", i,Poly[i]);
        }  
    }    
    return 0;
}