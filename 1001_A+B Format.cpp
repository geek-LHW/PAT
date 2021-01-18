#include<iostream>
#include<string>
using namespace std;
int main(){
    int a,b;
    scanf("%d%d",&a,&b);
    //先忽略正负，转成字符串
    string s1 = to_string(abs(a+b));
    //字符串长度
    int len = s1.length();
    //答案
    string answer = "";
    //如果长度小于四位则直接输出
    if(len<4){
        printf("%s",to_string(a+b).c_str());
    }
    else{
        while(len>3){
            answer = "," + s1.substr(len - 3, 3) + answer;
            len = len - 3;
        }
        answer =s1.substr(0,len)+answer;
        //如果开头是负号，加上
        if(to_string(a+b).substr(0,1)=="-"){
            answer = '-'+answer;
        }
        printf("%s", answer.c_str());
    }
    return 0;
}