#include<bits/stdc++.h>

using namespace std;
typedef vector<int> vi;
typedef pair<int,int> pii;
typedef vector<int>::iterator vp;


int n;
vector<vector<vi>> B(9);
vector<vector<vi>> V(9);
vector<vector<vi>> W(9);
vector<vector<vi>> A(9);


//Bk is 2^k x 2^(k-1) * (k+2)
void build_B(int k){
    if(k==0){
        B[k]={{1}};
        return;
    }

    build_B(k-1);
    B[k]=vector<vi>(1<<k,vi((1<<(k-1))*(k+2)));
    


    //Top left
    for(int i=0;i<B[k-1].size();++i){
        for(int j=0;j<B[k-1][i].size();++j){
            B[k][i][j]=B[k-1][i][j];
        }
    }

    //Top middle
    for(int i=0;i<B[k-1].size();++i){
        for(int j=0;j<B[k-1][i].size();++j){
            B[k][i][B[k-1][i].size()+j]=(-1)*B[k-1][i][j];
        }
    }
    //Top right
    for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<(1<<(k-1));++j){
            B[k][i][2*B[k-1][0].size()+j]=(i==j?1:0);
        }
    }

    //Bottom left
    for(int i=0;i<B[k-1].size();++i){
        for(int j=0;j<B[k-1][i].size();++j){
            B[k][B[k-1].size()+i][j]=B[k-1][i][j];
        }
    }
    //Bottom middle
    for(int i=0;i<B[k-1].size();++i){
        for(int j=0;j<B[k-1][i].size();++j){
            B[k][B[k-1].size()+i][B[k-1][i].size()+j]=B[k-1][i][j];
        }
    }
    
    //Bottom right
     for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<(1<<(k-1));++j){
            B[k][B[k-1].size()+i][2*B[k-1][0].size()+j]=0;
        }
    }    

}

//All positive entries from B
void build_V(int k){
    if(k>0) build_V(k-1);

    V[k] = B[k];
    for(int i=0;i<V[k].size();++i){
        for(int j=0;j<V[k][i].size();++j){
            V[k][i][j]=(B[k][i][j]==1?1:0);
        }
    }
}
//All negative entries from B
void build_W(int k){
    if(k>0) build_W(k-1);

    W[k] = B[k];
    for(int i=0;i<W[k].size();++i){
        for(int j=0;j<W[k][i].size();++j){
            W[k][i][j]=(B[k][i][j]==-1?1:0);
        }
    }
}

//Ak is 2^k x 2^k-1 *k 
void build_A(int k){
    if(k==1){
        A[k]={{1},{0}};
        return;
    }
    build_A(k-1);
    A[k]=vector<vi> ((1<<k),vi((1<<(k-1))*k));
    //Top left
    for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<A[k-1][i].size();++j){
            A[k][i][j]=A[k-1][i][j];
        }
    }
    //Top right
    for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<V[k-1][i].size();++j){
            A[k][i][A[k-1][0].size()+j]=V[k-1][i][j];
        }
    }

    //Bottom left
    for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<A[k-1][i].size();++j){
            A[k][A[k-1].size()+i][j]=A[k-1][i][j];
        }
    }
    //Bottom right
    for(int i=0;i<(1<<(k-1));++i){
        for(int j=0;j<W[k-1][i].size();++j){
            A[k][A[k-1].size()+i][A[k-1][0].size()+j]=W[k-1][i][j];
        }
    }
}

void decode_B(int k, vp x_b, vp l_b){
    cerr << "deconding B with " << k <<'\n';
    if (k==0){
        cerr << "k=0 is " << *x_b << ' ' << *l_b<<'\n';
        *x_b=*l_b; //using B0 is 1x1 and equal to 1
        return;
    }
    cerr <<"L " <<k<<":";
    for(int i=0;i<(1<<k);++i) cerr <<' ' << *(l_b+i);
    cerr <<'\n';
    //for(int i=0;i<(1<<(k-1))*(k+2);++i) cerr <<"x " << i << ' ' <<*(x_b+i)<<'\n';
    vi l_p=vi(1<<(k-1));
    for(int i=0;i<(1<<(k-1));++i){
        l_p[i]= *(l_b+i)+*(l_b+(1<<(k-1))+i);
    }
    
    vi l_m=vi(1<<(k-1));
    for(int i=0;i<(1<<(k-1));++i){
        l_m[i]= *(l_b+(1<<(k-1))+i)-*(l_b+i);
    }
    int shift=(k==1?1:(1<<(k-2))*(k+1));
    //decode z
    for(int i=0;i<(1<<k-1);++i){
        int zi =  ((l_p[i]%2)+2)%2;
        *(x_b+2*shift+i) =zi;
        cerr << "z "<< i <<' ' << zi;
        l_p[i]-=zi;
        l_p[i]/=2;
        l_m[i] += zi;
        l_m[i]/=2;
    }
    //decode x
    decode_B(k-1,x_b,l_p.begin());
        
    //decode y
    decode_B(k-1,x_b+shift,l_m.begin());
}

void decode_A(int k, vp x_b, vp h_b){
    if(k==1){
        *x_b=*h_b;
        return;
    }
    cerr << "H "<< k << ": ";
    for(int i=0;i<(1<<k);++i) cerr << *(h_b+i);
    cerr << '\n';
    vi h_m=vi(1<<(k-1));
    for(int i=0;i<(1<<(k-1));++i){
        h_m[i]= *(h_b+i)-*(h_b+(1<<(k-1))+i);
    } 
    int shift = (k==1?1:+(1<<(k-2))*(k-1));
    //decode y
    decode_B(k-1,x_b+shift,h_m.begin());
    
    vi vy((1<<(k-1)),0);
    for(int i=0;i<(1<<k-1);++i){
        for(int j=0;j<V[k-1][0].size();++j){
            vy[i]+=V[k-1][i][j] * (*(x_b+shift+j));
        }
        cerr << "vy " << i << ' ' << vy[i]<<'\n';
    }
    for(int i=0;i<(1<<(k-1));++i){
        *(h_b+i) = *(h_b+i)-vy[i];
        cerr << "hb "<< i << ' ' << *(h_b+i)<<'\n';
    }
    //decode x
    decode_A(k-1,x_b,h_b);

}

template <typename Iterator>
//Iterators of type pii
int query(Iterator begin,Iterator end){
	cout << '?' <<'\n';
	vector<string> grid(n,string(n,'0'));
	for(Iterator it=begin; it != end;++it ){
		grid[it->first][it->second]='1';
	}	
	for(string s:grid){
		cout << s <<'\n'; 
	}
	cout << flush;
	int res;
	cin >> res;
	return res;
}

void answer(vector<pii>& lamps){
	cout << '!' <<'\n';
	vector<string> grid(n,string(n,'0'));
	for(auto [r,c]: lamps){
		grid[r][c]='1';
	}	
	for(string s:grid){
		cout << s <<'\n'; 
	}

	cout << flush;
}



int bs(int index, char rc, bool is_col, vi indices){
	vector<pii> q;
	for(int i: indices){
		if(rc == 'r'){
			q.push_back({index,i});
		} else {
			q.push_back({i,index});
		}
	}
	int tot = query(q.begin(),q.end());
	if(tot == indices.size()*n)
		return -1;
	if(tot == n){
		return *indices.begin();
	}
	int tot_num = tot/n - (tot==n?1:0);
	//cerr << tot_num << '\n';
	int l=0, u=indices.size();
	while(l != u-2){
		int m = (l+u)/2 +(l+u)%2;
		int res = query(q.begin()+l,q.begin()+m);	
		res = res/n - (res==n?1:0);
		//cerr<< res << ' ' << '\n';
		if(res == 0)
			return *(indices.begin()+l);
		if(res == tot_num)
			return *(indices.begin()+u-1);
		if(res > tot_num/2){
			l = m;
			tot_num = tot_num -res;
		} else {
			u = m;
			tot_num = res;
		}

	}
	vector<pii> q2 = {{0,0}};
	q2.push_back(*(q.begin()+l));
	int res=query(q2.begin(),q2.end());
	if((res == 2*n && ((rc == 'c' && is_col) || (rc =='r' && !is_col)))||(res<2*n &&(rc=='c'&&!is_col||rc=='r'&&is_col))) return *(indices.begin()+l);
	return *(indices.begin()+l+1);
}

//compute the number of lamps that are the same as is_col, res0 is res with (0,0) added
int same(int n, int i, int res, int res0, bool is_col){
    int lit,lit0,litj,lit0j;
    for(int j=0;j<=i;++j){
        lit=j*n+(i-j)*(n-j);
        if(lit==res) {
            litj=j;
            break;
        }
    }
    for(int j=0;j<=i;++j){
        lit0=j*n+(i+1-j)*(n-j);
        if(lit0==res0) {
            lit0j=j;
            break;
        }
    }

    if(lit0j>litj) return litj;
    else return i-litj;


    assert(false);
    return -1;
}


signed main(){
	cin >> n;
        int dist = n/20;
	vector<pii> q = {{0,0},{0,1},{0,2}};
	int res = query(q.begin(),q.end());
	bool is_col=true;
	if(res == n) is_col = false;
	else if(res ==2*n-1 || res == 3*n-2){
		int res2 = query(q.begin()+1,q.end());
		if((res == 2*n-1 && res2 == 2*n-1) || (res == 3*n-2 && res2 == 2*n)) is_col=false;
	}
	//cerr << is_col << '\n';
	vector<pii> cols;
        vi cols_c(n,0);
        vector<pii> rows;
        vi rows_c(n,0);
	vector<pii> res_v;
        vi res_c;
        
        build_B(6);
        build_V(6);
        build_W(6);
        build_A(6);
        if(is_col) {
            cols.push_back({0,0});
            cols_c[0]=1;
        } else {
            rows.push_back({0,0});
            rows_c[0]=1;
        }
        cerr << " is col "<< is_col<<'\n';
        cerr << "starting CW" <<'\n';
        while(int(cols.size())<n-dist && int(rows.size())<n-dist){
            int i=(is_col?0:1);
            int j=(is_col?1:0);
            vector<pii> q;
            while(i<n && j<n){
                if(rows_c[i]) {
                    ++i;
                    continue;
                }
                if(cols_c[j]) {
                    ++j;
                    continue;
                }
                q.push_back({i,j});
                ++i;
                ++j;
            }
            //figure out k;
            int k=0;
            while(q.size()>((1<<(k-1))*k)) ++k;
            cerr << "Query size: " << q.size() << " chosen k " << k <<'\n';

            vi h;
            for(int i=0;i<A[k].size()-1;++i){
                vector<pii> qi;
                for(int j=0;j<q.size();++j){
                    if(A[k][i][j]) qi.push_back(q[j]);
                    cerr << A[k][i][j] <<' ';
                }
                cerr << '\n';
                qi.push_back({0,0});
                h.push_back(same(n,qi.size()-1,query(qi.begin(),qi.end()-1),query(qi.begin(),qi.end()),is_col));

                cerr <<"result of q "<< i <<" is "<< h[i] << '\n';
            }
            h.push_back(0);
            vi x(A[k][0].size(),0);
            cerr << "res " << x.size()<<'\n';
            decode_A(k,x.begin(),h.begin());
            
            //if true then h[i]=1 means col, else it means row
            bool is_col_q = is_col;

            //vector<pii> test ={{0,0},{q[0].first,q[0].second}};
            
            for(int j=0;j<q.size();++j){
                cerr << "lamp " << q[j].first <<' ' << q[j].second << " state " << x[j]<<'\n';
                if((x[j]==1 && is_col_q) || x[j]==0 && !is_col_q) {
                    cols.push_back(q[j]);
                    cols_c[q[j].second]=1;
                    cerr << " Found col at " << q[j].first << ' ' << q[j].second << '\n';
                } else {
                    rows.push_back(q[j]);
                    rows_c[q[j].first]=1;
                    cerr << " Found row at " << q[j].first << ' ' << q[j].second << '\n';
                }
            }

        }

	char rc;
        if(cols.size()>rows.size()){
            res_v=cols;
            res_c=cols_c;
            cerr << "going for cols" <<'\n';
            rc='c';
        } else {
            res_v=rows;
            res_c=rows_c;
            cerr << "going for rows"<<'\n';
            rc='r';
        }
        
        for(int i=0;i<n;++i){
		if(res_c[i]) continue;

                vi indices(n);
		iota(indices.begin(),indices.end(),0);
		int res = bs(i,rc,is_col,indices);
		//cerr << res << '\n';
		if(res ==-1) {
			if(rc == 'c'){
				vector<pii> row;
				for(int j=0;j<n;++j) row.push_back({j,i});
				answer(row);
				return 0;
			}
			vector<pii> col;
			for(int j=0;j<n;++j) col.push_back({i,j});
			answer(col);
			return 0;
		}
		pii r;
		rc=='c'? r={res,i}:r={i,res};
		res_v.push_back(r);

	}

	answer(res_v);
	return 0;
}

