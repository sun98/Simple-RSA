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

//���ܹ����еļ�������
int global_n, global_e, p, q, oln;
long long global_d;

//�ж�һ�������Ƿ�������
bool isPrime(int n){
	if(n<2) return true;
	fori(i, 2, (int)sqrt((double)n)){
		if(n%i==0){
			return false;
		}
	}
	return true;
}

//�������������
int randomPrime(){
	while(true){
		int i = rand()%MAX_RAND;
		if(isPrime(i)) return i;
	}
}

//�ж����������Ƿ���
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

//�������ݣ����ؽ��=a^k%M
long long powMod(long long a,long long k,long long M){
    long long b=1;
    while(k>=1){
        if(k%2==1) b=a*b%M;
        a=(a%M)*(a%M)%M;
        k/=2;
    }
    return b;
}

//��a����n��ģ��Ԫ��
long long calcModRev(int a, int n){
	long long rd = 1;
	while((rd%n*a)%n!=1){
		rd++;
	}
	return rd;
}

//����һ�Թ�Կ��˽Կ�Ĵ�
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

//��һ���ַ�����
long long encode(int raw){
	return powMod(raw, global_e, global_n);
}

//����һ���ַ�
int decode(long long pw){
	return powMod(pw, global_d, global_n);
}

//���ַ�������
void encrypt(char* rawString, int len, int* secretString){
	fori(i, 0, len){
		secretString[i]=encode((int)rawString[i]);
	}
}

//�����ַ���
void decrypt(int* secretString, int len, char* rawString){
	fori(i, 0, len){
		rawString[i]=(char)decode(secretString[i]);
	}
}

int main(){
	srand((unsigned)time(NULL));    //Ϊ�������������
	while(true){    //���鹫Կ��˽Կ�Ƿ�������ȷ
		setKey(&global_n, &global_e, &global_d);
		if(decode(encode(15))==15) break;
	}
	cout<<"������� (p, q) = ("<<p<<", "<<q<<")"<<endl;
	cout<<"p��q�ĳ˻� n = "<<global_n<<endl;
	cout<<"��n��ŷ���������ʵ����� e = "<<global_e<<endl;
	cout<<"e����n��ŷ��������ģ��Ԫ�� d = "<<global_d<<endl;
	cout<<"��Կ����(n, e) = ("<<global_n<<", "<<global_e<<")"<<endl;
	cout<<"˽Կ����(n, d) = ("<<global_n<<", "<<global_d<<")"<<endl;
	char* str = new char[201];
	char* str2 = new char[201];
	int* code = new int[200];
	while(true){
		cout<<"=================================="<<endl;
		cout<<"����Ӣ���ַ�����������200���ַ�������exit�˳�����"<<endl;
		cin>>str;
		if(strcmp(str, "exit")==0) break;
		encrypt(str, strlen(str), code);
		cout<<"�����ַ�����"<<endl;
		fori(i, 0, strlen(str)){
			cout<<code[i]<<flush;
		}
		decrypt(code, strlen(str), str2);
		cout<<endl<<"�����ַ�����"<<endl;
		fori(i, 0, strlen(str)){
			cout<<(char)str2[i]<<flush;
		}
		cout<<endl;
	}
	
	return 0;
}

