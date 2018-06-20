#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <string>
#include <cstring>
#define fori(i, l, a) for(int i=l; i<a; i++)
using namespace std;

const int MAX_INT = 2147483647;
const int MAX_RAND = 5000;

//加密过程中的几个参数
int global_n, global_e, p, q, oln;
long long global_d;

//判断一个整数是否是质数
bool isPrime(int n){
	if(n<2) return true;
	fori(i, 2, (int)sqrt((double)n)){
		if(n%i==0){
			return false;
		}
	}
	return true;
}

//生成随机的质数
int randomPrime(){
	while(true){
		int i = rand()%MAX_RAND;
		if(isPrime(i)) return i;
	}
}

//判断两个整数是否互质
int isPrimeEO(int a, int b){
    int temp=0;
    while(b!=0){
        temp=b;
        b=a%b;
        a=temp;
    }
    if(a==1) return true;
    else return false;
}

//快速求幂，返回结果=a^k%M
long long powMod(long long a,long long k,long long M){
    long long b=1;
    while(k>=1){
        if(k%2==1) b=a*b%M;
        a=(a%M)*(a%M)%M;
        k/=2;
    }
    return b;
}

//求a对于n的模反元素
long long calcModRev(int a, int n){
	long long rd = 1;
	while((rd%n*a)%n!=1){
		rd++;
	}
	return rd;
}

//生成一对公钥和私钥的串
void setKey(int* n, int* e, long long* d){
	p = randomPrime();
	q = p;
	while(p==q){
		q = randomPrime();
	}
    *n = p*q;
    oln = (p-1)*(q-1);
	*e = rand()%(oln-2)+2;
	while(!isPrimeEO(*e, oln)){
		*e = rand()%(oln-2)+2;
	}
	*d = calcModRev(*e, oln);
}

//对一个字符加密
long long encode(int raw){
	return powMod(raw, global_e, global_n);
}

//解密一个字符
int decode(long long pw){
	return powMod(pw, global_d, global_n);
}

//对字符串加密
void encrypt(char* rawString, int len, int* secretString){
	fori(i, 0, len){
		secretString[i]=encode((int)rawString[i]);
	}
}

//解密字符串
void decrypt(int* secretString, int len, char* rawString){
	fori(i, 0, len){
		rawString[i]=(char)decode(secretString[i]);
	}
}

int main(){
	srand((unsigned)time(NULL));    //为随机数设置种子
	while(true){    //检验公钥、私钥是否生成正确
		setKey(&global_n, &global_e, &global_d);
		if(decode(encode(15))==15) break;
	}
	cout<<"随机质数 (p, q) = ("<<p<<", "<<q<<")"<<endl;
	cout<<"p和q的乘积 n = "<<global_n<<endl;
	cout<<"与n的欧拉函数互质的整数 e = "<<global_e<<endl;
	cout<<"e对于n的欧拉函数的模反元素 d = "<<global_d<<endl;
	cout<<"公钥串：(n, e) = ("<<global_n<<", "<<global_e<<")"<<endl;
	cout<<"私钥串：(n, d) = ("<<global_n<<", "<<global_d<<")"<<endl;
	char* str = new char[201];
	char* str2 = new char[201];
	int* code = new int[200];
	while(true){
		cout<<"=================================="<<endl;
		cout<<"输入英文字符串（不超过200个字符，输入exit退出）："<<endl;
		cin>>str;
		if(strcmp(str, "exit")==0) break;
		encrypt(str, strlen(str), code);
		cout<<"加密字符串："<<endl;
		fori(i, 0, strlen(str)){
			cout<<code[i]<<flush;
		}
		decrypt(code, strlen(str), str2);
		cout<<endl<<"解密字符串："<<endl;
		fori(i, 0, strlen(str)){
			cout<<(char)str2[i]<<flush;
		}
		cout<<endl;
	}
	
	return 0;
}

