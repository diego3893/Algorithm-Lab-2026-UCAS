#include <cstdio>
#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <algorithm>

using namespace std;
void add_string(string s1, string s2, string &ans);
void minus_string(string s1, string s2, string &ans); // 需要s1>s2，内部处理
void get_sign(string s1, string s2, string &ans);
/**
 * @brief 比较高精度整数，带符号比较
 * 
 * @param s1 整数1
 * @param s2 整数2
 * @return int 1:s1>s2; 0:s1==s2; -1:s1<s2
 */
int cmp_string(string s1, string s2);
string abs_string(string s);

int main(){
    string s1, s2;
    string ans;
    ans.clear();
    cin >> s1;
    cin >> s2;
    if((s1[0]=='-' && s2[0]=='-') || (s1[0]!='-' && s2[0]!='-')){
        add_string(s1, s2, ans);
    }else{
        minus_string(s1, s2, ans);
    }
    while(ans.length()>1 && ans.back()=='0'){
        ans.pop_back();
    }
    get_sign(s1, s2, ans);
    reverse(ans.begin(), ans.end());
    cout << ans;

    return 0;
}

int cmp_string(string s1, string s2){ 
    if(s1[0]=='-' && s2[0]!='-'){
        return -1;
    }
    if(s1[0]!='-' && s2[0]=='-'){
        return 1;
    }
    int s1_len = s1.length(), s2_len = s2.length();
    if(s1[0]=='-' && s2[0]=='-'){
        if(s1_len > s2_len){
            return -1;
        }
        if(s1_len < s2_len){
            return 1;
        }
        for(int i=0; i<s1_len; ++i){
            if(s1[i] > s2[i]){
                return -1;
            }
            if(s1[i] < s2[i]){
                return 1;
            }
        }
        return 0;
    }
    if(s1[0]!='-' && s2[0]!='-'){
        if(s1_len > s2_len){
            return 1;
        }
        if(s1_len < s2_len){
            return -1;
        }
        for(int i=0; i<s1_len; ++i){
            if(s1[i] > s2[i]){
                return 1;
            }
            if(s1[i] < s2[i]){
                return -1;
            }
        }
        return 0;
    }
    return 0;
}

string abs_string(string s){
    string abs_str;
    if(s[0] == '-'){
        abs_str = s.substr(1);
    }else{
        abs_str = s;
    }
    return abs_str;
}

void get_sign(string s1, string s2, string &ans){
    if(s1[0]=='-' && s2[0]=='-'){
        ans.push_back('-');
    }
    if(s1[0]!='-' && s2[0]!='-'){

    }
    if(s1[0]=='-' && s2[0]!='-'){
        s1 = abs_string(s1);
        s2 = abs_string(s2);
        if(cmp_string(s1, s2) == 1){
            ans.push_back('-');
        }
    }
    if(s1[0]!='-' && s2[0]=='-'){
        s1 = abs_string(s1);
        s2 = abs_string(s2);
        if(cmp_string(s1, s2) == -1){
            ans.push_back('-');
        }
    }
    return;
}

void add_string(string s1, string s2, string &ans){
    s1 = abs_string(s1);
    s2 = abs_string(s2);
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int s1_len = s1.length(), s2_len = s2.length();
    string longer_s;
    int min_len, max_len;
    if(s1_len >= s2_len){
        min_len = s2_len;
        max_len = s1_len;
        longer_s = s1;
    }else{
        min_len = s1_len;
        max_len = s2_len;
        longer_s = s2;
    }
    int c_in = 0;
    for(int i=0; i<min_len; ++i){
        char c;
        int s1_num = s1[i]-'0', s2_num = s2[i]-'0';
        int ans_num = s1_num+s2_num+c_in;
        c = ans_num%10+'0';
        c_in = ans_num/10;
        ans.push_back(c);
    }
    int idx = min_len;
    while(c_in){
        char c;
        int s_num, ans_num;
        s_num = (idx<max_len) ? (longer_s[idx]-'0') : 0;
        ans_num = s_num+c_in;
        c = ans_num%10+'0';
        c_in = ans_num/10;
        ans.push_back(c);
        idx++;
    }
    while(idx < max_len){
        ans.push_back(longer_s[idx]);
        idx++;
    }
    return;
}

void minus_string(string s1, string s2, string &ans){
    s1 = abs_string(s1);
    s2 = abs_string(s2);
    if(cmp_string(s1, s2) == 0){
        ans.push_back('0');
        return;
    }
    if(cmp_string(s1, s2) == -1){
        swap(s1, s2);
    }
    reverse(s1.begin(), s1.end());
    reverse(s2.begin(), s2.end());
    int s1_len = s1.length(), s2_len = s2.length();
    string longer_s;
    int min_len, max_len;
    if(s1_len >= s2_len){
        min_len = s2_len;
        max_len = s1_len;
        longer_s = s1;
    }else{
        min_len = s1_len;
        max_len = s2_len;
        longer_s = s2;
    }
    int d_in = 0;
    for(int i=0; i<min_len; ++i){
        char c;
        int s1_num = s1[i]-'0', s2_num = s2[i]-'0';
        int ans_num = s1_num-s2_num-d_in;
        if(ans_num < 0){
            d_in = 1;
            ans_num += 10;
        }else{
            d_in = 0;
        }
        c = ans_num+'0';
        ans.push_back(c);
    }
    int idx = min_len;
    while(d_in){
        char c;
        int s_num, ans_num;
        s_num = (idx<max_len) ? (longer_s[idx]-'0') : 0;
        ans_num = s_num-d_in;
        if(ans_num < 0){
            d_in = 1;
            ans_num += 10;
        }else{
            d_in = 0;
        }
        c = ans_num+'0';
        ans.push_back(c);
        idx++;
    }
    while(idx < max_len){
        ans.push_back(longer_s[idx]);
        idx++;
    }
    return;
}