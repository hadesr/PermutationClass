#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool des(const vector<int>& v1, const vector<int>& v2) 
{ 
    return v1.size() > v2.size(); 
}

int gcd(int a, int b) 
{ 
    if (b == 0)
        return a; 
    return gcd(b, a % b); 
} 
  
long long int findlcm(vector<int> v)
{
    long long int ans = v[0]; 
  
    for (int i = 1; i < v.size(); i++) 
        ans = (((v[i] * ans))/(gcd(v[i], ans))); 
    return ans; 
}

class permutation
{
private:
	int length;
	int *p=NULL;

public:

	permutation(int n, int a[]);
	~permutation();
	permutation(permutation const &q);
	void operator=(permutation const &q);

	int size() const;
	int* to_array() const;

	permutation operator-() const;
	permutation operator*(permutation const &q) const;

	permutation square_root() const;
	permutation operator^(long long int i) const;
	bool is_power(permutation const &q) const;
	int log(permutation const &q) const;
};

permutation::permutation(int n, int a[])
{
	this->length = n;
	this->p = new int[n];
	for(int i=0;i<n;i++)
	{
		this->p[i] = a[i];
	}
}

permutation::~permutation()
{
	delete[] p;
}

permutation::permutation(permutation const &q)
{
	this->length = q.length;
	this->p = new int[length];
	for(int i=0;i<length;i++)
	{
		this->p[i] = q.p[i];
	}
}

void permutation::operator=(permutation const &q)
{
	this->length = q.length;
	delete[] this->p;
	this->p = new int[this->length];
	for(int i=0;i<length;i++)
		this->p[i] = q.p[i];
}

int permutation::size() const
{
	return this->length;
}

int *permutation::to_array() const
{
	int *a = new int[this->length];
	for(int i=0;i<length;i++)
		a[i] = this->p[i];
	return a;
}

permutation permutation::operator-() const
{
	int inv_p[this->length];

	for(int i=0;i<length;i++)
	{
		inv_p[this->p[i]] = i;
	}

	permutation inverse_per(length,inv_p);
	return inverse_per;
}

permutation permutation::operator*(permutation const &q) const
{
	int com_per[this->length];

	for(int i=0;i<length;i++)
	{
		com_per[i] = p[q.p[i]];
	}
	permutation c_p(length,com_per);
	return c_p;
}

permutation permutation::square_root() const
{
	vector<int> v(length);
	for(int i=0;i<length;i++)
		v[i] = p[i];

	vector<vector<int>> odd;
	vector<vector<int>> even;

	for(int i=0;i<v.size();i++)
	{
		if(v[i] != -1)
		{
			vector<int> vec;
			int j=v[i];
			vec.push_back(j);
			
			while(v[i] != v[j])
			{
				vec.push_back(v[j]);
				int k=j;
				j=v[j];
				v[k] = -1;
			}

			v[i] = -1;

			if(vec.size()%2 == 0)
				even.push_back(vec);
			else
				odd.push_back(vec);
		}
	}

	sort(even.begin(), even.end(), des);

	if(even.size() %2 != 0)
	{
		int alpha[length];
		for(int i=0;i<length;i++)
			alpha[i] = i;
		permutation beta(length,alpha);
		return beta;
	}
	else
	{
		for (int i = 0; i < even.size(); i=i+2)
		{
			vector<int> vec1,vec2;
			vec1 = even[i];
			vec2 = even[i+1];
			if(vec1.size() != vec2.size())
			{
				int alpha[length];
				for(int i=0;i<length;i++)
					alpha[i] = i;
				permutation beta(length,alpha);
				return beta;
			}
		}


		vector<int> final (v.size());

		for(int i=0;i<odd.size();i++)
		{
			vector<int> k= odd[i];

			if(k.size()==1)
			{
				final[k[0]] = k[0];
			}
			else
			{
				for(int l=0;l<k.size()/2;l++)
				{
					final[k[l]] = k[(k.size()/2)+l+1];
					final[k[(k.size()/2)+l+1]] = k[l+1];
				}
				final[k[k.size()/2]] = k[0];
			}
		}

		for(int i=0;i<even.size();i=i+2)
		{
			vector<int> v1,v2;
			v1 = even[i];
			v2 = even[i+1];

			for(int i=0;i<v1.size();i++)
			{
				final[v1[i]] = v2[i];
				if(i == v1.size()-1)
					final[v2[i]] = v1[0];
				else
					final[v2[i]] = v1[i+1];
			}
		}

		int alpha[length];
		for(int i=0;i<length;i++)
		{
			alpha[i] = final[i];
		}
		permutation beta(length,alpha);
		return beta;
	}
}

permutation permutation::operator^(long long int i) const
{
	if(i==0)
	{
		int alpha[length];
		for(int i=0;i<length;i++)
			alpha[i] = i;
		permutation beta(length,alpha);
		return beta;
	}

	vector<int> original(length);

	for(int i=0;i<length;i++)
		original[i] = p[i];

	vector<int> v(original.size());

	for(int i=0;i<original.size();i++)
		v[i] = original[i];

	vector<int> cycle_size;

	for(int i=0;i<v.size();i++)
	{
		if(v[i] != -1)
		{
			int l=1;
			int j=v[i];
			while(v[i] != v[j])
			{
				l++;
				int k=j;
				j=v[j];
				v[k] = -1;
			}
			v[i] = -1;
			cycle_size.push_back(l);
		}
	}
	
	long long int lcm = findlcm(cycle_size);
	long long int k = i%lcm;

	if(k==0)
		k = lcm;

	vector<int> final(original.size());

	for(int i=0;i<original.size();i++)
		final[i] = original[i];

	for(long long int i=0;i<k-1;i++)
	{
		for(int j=0;j<original.size();j++)
		{
			final[j] = original[final[j]];
		}
	}

	int alpha[length];
	for(int i=0;i<length;i++)
		alpha[i] = final[i];
	permutation beta(length,alpha);
	return beta;
}

bool permutation::is_power(permutation const &q) const
{
	if(length != q.length)
		return false;
	
	int is_identity = 1;

	for(int i=0;i<length;i++)
	{
		if(p[i] != i)
		{
			is_identity = 0;
			break;
		}
	}

	if(is_identity)
		return true;

	permutation P = *this;
	permutation Q = q;

	vector<int> v2(length);

	for(int i=0;i<length;i++)
	{

		for(int i=0;i<length;i++)
			v2[i] = Q.p[i];

		vector<int> vec;
		int j=v2[i];
		vec.push_back(j);
		while( i != v2[j])
		{
			vec.push_back(v2[j]);
			j=v2[j];
		}

		int d = vec.size();
		int index = -1;

		for(int j=0;j<d;j++)
		{
			if(vec[j] == P.p[i])
			{
				index = j+1;
				break;
			}
		}

		if(index == -1)
		{
			return false;
		}

		P = (Q^(d-index))*P;
		Q = Q^d;
	}
	return true;
}

int permutation::log(permutation const &q) const
{
	vector<int> v1(length),v2(length);

	for(int i=0;i<length;i++)
	{
		v1[i] = p[i];
		v2[i] = q.p[i];
	}

	vector<int> v1_size,v2_size;

	vector<int> v(v1.size());

	for(int i=0;i<v1.size();i++)
	{
		v[i] = v1[i];
	}

	for(int i=0;i<v.size();i++)
	{
		if(v[i] != -1)
		{
			int l=1;
			int j=v[i];
			while(v[i] != v[j])
			{
				l++;
				int k=j;
				j=v[j];
				v[k] = -1;
			}
			v[i] = -1;
			v1_size.push_back(l);
		}
	}

	for(int i=0;i<v1.size();i++)
	{
		v[i] = v2[i];
	}

	for(int i=0;i<v.size();i++)
	{
		if(v[i] != -1)
		{
			int l=1;
			int j=v[i];
			while(v[i] != v[j])
			{
				l++;
				int k=j;
				j=v[j];
				v[k] = -1;
			}
			v[i] = -1;
			v2_size.push_back(l);
		}
	}

	long long int v1_lcm = findlcm(v1_size);
	long long int v2_lcm = findlcm(v2_size);

	int req_i = v2_lcm/v1_lcm;

	vector<int> v4(v1.size());

	for(int i=0;i<v1.size();i++)
	{
		v4[i] = v2[i];
	}

	for(int j=0;j<req_i-1;j++)
	{
		for(int i=0;i<v1.size();i++)
		{
			v4[i] = v2[v4[i]];
		}
	}

	while(req_i <= v2_lcm)
	{
		int equal = 1;

		for(int i=0;i<v1.size();i++)
		{
			if(v4[i] != v1[i])
			{
				equal = 0;
				break;
			}
		}

		if(equal)
			return req_i;

		req_i++;

		for(int i=0;i<v4.size();i++)
		{
			v4[i] = v2[v4[i]];
		}
	}
	return -1;
}