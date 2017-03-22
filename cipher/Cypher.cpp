#include<iostream>
#include<vector>
#include<string>
#include<vector>
#include<math.h>

using namespace std;

string Caeser_cipher(string x);
string Monoalphabetic_cipher(string x);
string Playfair_cipher(string x);
string Row_transposition(string x);
string Product_cipher(string x);
vector<string> Slice_string(string x, int a);
string toBinary(int n);
int toDecimal(string x);
string Vernam_cipher(string x);
string XOR(string a, string b);
int main()
{
	string plaintext="sentfrommyiphone";
	cout<<"Plaintext: sentfrommyiphone"<<endl;
	cout<<"Caeser_cypher:"<<Caeser_cipher(plaintext)<<endl<<"Monoalphabetic_cypher:"<<Monoalphabetic_cipher(plaintext)<<endl<<"Playfair_cypher:"<<Playfair_cipher(plaintext)<<endl<<"Row_transposition:"<<Row_transposition(plaintext)<<endl<<"Product_cipher:"<<Product_cipher(plaintext)<<endl;
	cout<<"Vernam_cipher:"<<Vernam_cipher(plaintext)<<endl;
	system("PAUSE");
}
string Caeser_cipher(string x)
{
	string output="";
	for(int i=0;i<x.size();i++)
	{
		if(x[i]>=65 && x[i]<=90)
		{
			x[i]+=3;
			if(x[i]>90)
			{
				x[i]-=26;
			}
			output+=x[i];
		}
		else if(x[i]>=97 && x[i]<=122)
		{
			x[i]+=3;
			if(x[i]>122)
			{
				x[i]-=26;
			}
			output+=x[i];
		}
	}
	return output;
}
string Monoalphabetic_cipher(string x)
{
	string output="";
	string table1="abcdefghijklmnopqrstuvwxyz";
	string table2="QWERTYUIOPASDFGHJKLZXCVBNM";
	for(int i=0;i<x.size();i++)
	{
		for(int j=0;j<table1.size();j++)
		{
			if(x[i]==table1[j])
			{
				output+=table2[j];
			}
		}
	}
	return output;
}
string Playfair_cipher(string x)
{
	string key="dpabcefghiklmnoqrstuvwxyz";
    string output="";
	char **table = new char*[5];
    for(int i = 0; i < 5; ++i) 
    {
    table[i] = new char[5];
    }
	for(int i=0, count=0;i<5;i++)
	{
		for(int j=0;j<5;j++)
		{
			table[i][j]=key[count];
			count++;
		}
	}
	for(int i=0;i<x.size();i+=2)
	{
		char com=x[i];
		char com2=x[i+1];
		int posax=0;
		int posay=0;
		int posbx=0;
		int posby=0;		
		for(int x=0;x<5;x++)
		{
			for(int y=0;y<5;y++)
			{
				if(table[x][y]==com)
				{
					posax=x;
					posay=y;
				}
			}
		}
		for(int x=0;x<5;x++)
		{
			for(int y=0;y<5;y++)
			{
				if(table[x][y]==com2)
				{
					posbx=x;
					posby=y;
				}
			}
		}
		
		if(posax==posbx)
		{
			posay=(posay+1)%5;
			posby=(posby+1)%5;
			output+=table[posax][posay];
			output+=table[posbx][posby];
		}
		else if(posay==posby)
		{
			posax=(posax+1)%5;
			posbx=(posbx+1)%5;
			output+=table[posax][posay];
			output+=table[posbx][posby];
		}
		else
		{
			int holder=posby;
			posby=posay;
			posay=holder;
			output+=table[posax][posay];
			output+=table[posbx][posby];
		}
		
	}
	return output;
}
string Row_transposition(string x)
{
	string result="";
	string key="52834671";	
	int number=x.size()/key.size();
	vector<string> holder=Slice_string(x, number);
	holder.insert(holder.begin(), key);
	for(int i=0;i<10;i++)
	{
		for(int j=0;j<key.size();j++)
		{
			if((holder[0][j]-48)==i)
			{
				for(int a=0;a<number;a++)
				{
					result+=holder[1+a][j];
				}
			}
		}
	}
	return result;
}
vector<string> Slice_string(string x, int a)
{
	string holder="";
	vector<string> data;
	if(x.size()%a==0)
	{
		int number=x.size()/a;
		for(int i=0;i<a;i++)
		{
			holder="";
			for(int j=0;j<number;j++)
			{
				holder=holder+x[j+i*number];
			}
			data.push_back(holder);
		}
	}
	return data;
}
string Product_cipher(string x)
{
	string result="";
	int key[16];
	char output[16];
	key[0]=15, key[1]=11, key[2]=2, key[3]=10, key[4]=16, key[5]=3, key[6]=7, key[7]=14, key[8]=4, key[9]=12, key[10]=9, key[11]=6, key[12]=1, key[13]=5, key[14]=8, key[15]=3;
	for(int i=0;i<x.size();i++)
	{
		for(int j=0;j<16;j++)
		{
			if((i+1)==key[j])
			{
				output[j]=x[i];
				break;
			}
		}
	}
	for(int i=0;i<16;i++)
	{
		result+=output[i];
	}
	return result;
}
string toBinary(int n)
{
	string fix="";
    string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    for(int i=0;i<(5-r.size());i++)
	{
		fix+="0";
	}
    r=fix+r;
    return r;
}
string XOR(string a, string b)
{
	string result="";
	for(int i=0;i<a.size();i++)
	{
		if(a[i]==b[i])
		{
			result+="0";
		}
		else
		{
			result+="1";
		}
	}
	return result;
}
string Vernam_cipher(string x)
{
	string result="";
	string decipher;
	int holder1, holder2;
	string alpha="abcdefghijklmnopqrstuvwxyz";
	string key="kmt";
	for(int i=0;key.size()<x.size();i++)
	{
		key+=x[i];
	}
	for(int i=0;i<x.size();i++)
	{
		holder1=0;
		holder2=0;
		for(int j=0;j<alpha.size();j++)
		{
			if(x[i]==alpha[j])
			{
				holder1=j;
			}
			if(key[i]==alpha[j])
			{
				holder2=j;
			}
		}
		decipher=XOR(toBinary(holder1),toBinary(holder2));
		for(int i=0;i<alpha.size();i++)
		{
			if(toDecimal(decipher)%26==i)
			{
				result+=alpha[i];
			}
		}
	}
	return result;
}
int toDecimal(string x)
{
	int result=0;
	for(int i=0;i<x.size();i++)
	{
		if(x[x.size()-i-1]=='1')
		{
			result+=pow(2,i);
		}
	}
	return result;
}
