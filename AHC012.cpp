#include <bits/stdc++.h>
//#define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define len(x) (ll)x.size()
#define print(x) cout << x << endl
#define nprint(x) cout << x << " "
#define dprint(a, b) cout << a << " " << b << endl
#define tprint(a, b, c) cout << a << " " << b << " " << c << endl
#define fprint(a, b, c, d) cout << a << " " << b << " " << c << " " << d << endl
#define pprint(x) cout << fixed << setprecision(10) << x << endl
#define vprint(v) for(auto x : v) cout << x << " ";   cout << endl
#define bs(v, k) binary_search(v.begin(), v.end(), k)
#define lb(v, k) lower_bound(v.begin(), v.end(), k)
#define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
using namespace std;

//const ll INF = LLONG_MAX;
//const ll LIMIT = pow(2, 60);
//const ll vec[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
//const ll vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
//const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a; if(n % 2 == 1) return (a * POW(a, n - 1)); ll t = POW(a, n / 2); return (t * t);}
ll CEIL(ll a, ll b){ll ret = (a + b - 1) / b; return ret;}
ll max(ll a, ll b){if(a > b) return a; else return b;}
ll min(ll a, ll b){if(a > b) return b; else return a;}
ll max(ll a, ll b, ll c){ll d = max(a, b); return max(c, d);}
ll min(ll a, ll b, ll c){ll d = min(a, b); return min(c, d);}
void yes(bool b){if(b) cout << "Yes" << endl; else cout << "No" << endl;}
using P = pair<ll, ll>;
using T = tuple<ll, ll, ll>; // ll x, y, z; tie(x, y, z) = T
using Graph = vector<vector<ll> >;
using Mat = vector<vector<ll> >;
template<typename T> using PQ = priority_queue<T>;
template<typename T> using IQ = priority_queue<T, vector<T>, greater<T>>;
Graph init_graph(ll V){Graph ret; vector<ll> empty; rep(i, V) ret.push_back(empty); return ret;}
Mat init_mat(ll a, ll b){Mat ret; vector<ll> empty; rep(i, b) empty.push_back(0); rep(i, a) ret.push_back(empty); return ret;}

/* パラメータ */
const float START_TEMP =  1500; // 開始時の温度
const float END_TEMP   =  100; // 終了時の温度
const float END_TIME   =  1950000; // 終了時間
const ll MIN_INITIAL = 20; 
const ll FIRST_TOTAL_MIN = 50; 
const ll RANGE = 100; 
const ll INITIAL_TIME = 100000; 

random_device rd;
mt19937 eng(rd());
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

ll n, k;
ll A[11]; 
ll totalA = 0; 
vector<P> berry; 
set<ll> yokoNG, tateNG; 
const ll MAX = 10000; 

clock_t start; 

// target以下の数を返す
ll my_lower_bound(vector<ll>& vec, ll target){
    target++;
    auto itr = lower_bound(vec.begin(), vec.end(), target);
    ll ret = distance(vec.begin(), itr);
    return ret;
}

vector<ll> vecErase(vector<ll> vec, ll tar){
    vector<ll> ret; 
    if(tar > len(vec)){
        cout << "ERROR in vecErase" << endl;
        exit(0); 
    }
    rep(i, len(vec)){
        if(i == tar) continue;
        else{
            ret.push_back(vec[i]);
        }
    }
    return ret; 
}

ll whereRoom(vector<ll>& tate, vector<ll>& yoko, P& p){
    ll y = my_lower_bound(yoko, p.first); 
    ll x = my_lower_bound(tate, p.second); 
    ll ret = y * (len(tate) + 1) + x; 
    return ret; 
}

vector<ll> makeVec(vector<ll> tate, vector<ll> yoko){
    ll maxIndex = (len(tate) + 1) * (len(yoko) + 1); 
    vector<ll> ret(maxIndex, 0); 
    for(auto p : berry){
        ll memo = whereRoom(tate, yoko, p); 
        if(memo > maxIndex){
            cout << len(tate) << " " << len(yoko) << " " << maxIndex << endl;
            cout << "ERROR : " << memo << endl;
        }
        ret[memo]++;
    }
    return ret; 
}

vector<ll> counter(vector<ll>& v){
    vector<ll> count(11); 
    for(auto c : v){
        if(c > 10) continue;
        else count[c]++;
    }
    return count;
}

double calcScore(vector<ll>& v){
    ll bunsi = 0; 
    frep(i, 1, 11){
        bunsi += min(A[i], v[i]); 
    }
    double ret = pow(10, 6) * (double)bunsi / (double)totalA; 
    return ret; 
}

double calcScore(vector<ll>& tate, vector<ll>& yoko){
    vector<ll> vec = makeVec(tate, yoko); 
    vector<ll> count = counter(vec); 
    double ret = calcScore(count); 
    return ret; 
}

int makeNextTate(vector<ll>& NG){
    while(true){
        int r = (randInt(eng) % (MAX * 2)) - MAX;
        if(bs(tateNG, r) == true || bs(NG, r) == true){
            continue;
        }
        else{
            return r; 
        }
    }
}

int makeNextYoko(vector<ll>& NG){
    while(true){
        int r = (randInt(eng) % (MAX * 2)) - MAX;
        if(bs(yokoNG, r) == true || bs(NG, r) == true){
            continue;
        }
        else{
            return r; 
        }
    }
}

pair<vector<ll>, vector<ll> > makeInitialAnswer(){
    int first_total = FIRST_TOTAL_MIN + (randInt(eng) % 20); 
    int tateSize = (randInt(eng) % (first_total - (MIN_INITIAL * 2))) + MIN_INITIAL; 
    int yokoSize = first_total - tateSize; 
    vector<ll> tate; 
    while(len(tate) != tateSize){
        int next = makeNextTate(tate); 
        tate.push_back(next); 
    }
    
    vector<ll> yoko; 
    while(len(yoko) != yokoSize){
        int next = makeNextYoko(yoko); 
        yoko.push_back(next); 
    }
    
    sort(tate.begin(), tate.end()); 
    sort(yoko.begin(), yoko.end()); 
    pair<vector<ll>, vector<ll> > p = make_pair(tate, yoko); 
    return p; 
}

pair<vector<ll>, vector<ll> > makeBestInitialAnswer(){
    double bestScore = 0.0;
    pair<vector<ll>, vector<ll> > best; 
    while(true){
        if(clock() - start > INITIAL_TIME) break;
        pair<vector<ll>, vector<ll> > cand = makeInitialAnswer(); 
        vector<ll> vec = makeVec(cand.first, cand.second); 
        vector<ll> countVec = counter(vec); 
        double score = calcScore(countVec); 
        if(score > bestScore){
            bestScore = score; 
            best = cand; 
        }
    }
    
    return best; 
}

pair<vector<ll>, vector<ll> > update(vector<ll> _tate, vector<ll> _yoko){
    vector<ll> tate = _tate; 
    vector<ll> yoko = _yoko; 
    bool point = true;

    while(point){
        int r = randInt(eng) % 4; 
        if(r == 0){
            int r2 = randInt(eng) % len(tate); 
            int pos = tate[r2]; 
            tate = vecErase(tate, r2); 
            while(true){
                int r3 = (randInt(eng) % (RANGE * 2)) - RANGE; 
                int next = pos + r3; 
                if(-1 * MAX < next && next < MAX){
                    tate.push_back(next); 
                    point = false;
                    break;
                }
                else continue;
            }
        }
        else if(r == 1){
            int r2 = randInt(eng) % len(yoko); 
            int pos = yoko[r2]; 
            yoko = vecErase(yoko, r2); 
            while(true){
                int r3 = (randInt(eng) % (RANGE * 2)) - RANGE; 
                int next = pos + r3; 
                if(-1 * MAX < next && next < MAX){
                    yoko.push_back(next); 
                    point = false;
                    break;
                }
                else continue;
            }
        }
        else if(r == 2){
            if(randInt(eng) % 2 == 0){
                int r3 = randInt(eng) % len(yoko); 
                yoko = vecErase(yoko, r3);
                point = false;
            }
            else{
                int r3 = randInt(eng) % len(tate); 
                tate = vecErase(tate, r3); 
                point = false;
            }
        }
        else if(r == 3){
            if(randInt(eng) % 2 == 0){
                if(len(tate) + len(yoko) >= k) continue;
                int next = makeNextYoko(yoko); 
                yoko.push_back(next); 
                point = false; 
            }
            else{
                if(len(tate) + len(yoko) >= k) continue;
                int next = makeNextTate(tate); 
                tate.push_back(next); 
                point = false;
            }
        }
        else{
            cout << "ERROR in update : " << r << endl;
            exit(0); 
        }
    }
    
    sort(tate.begin(), tate.end()); 
    sort(yoko.begin(), yoko.end()); 
    
    pair<vector<ll>, vector<ll> > ret = make_pair(tate, yoko); 
    return ret; 
}

pair<vector<ll>, vector<ll> > SA(vector<ll> firstTate, vector<ll> firstYoko){
    vector<ll> tate = firstTate; 
    vector<ll> yoko = firstYoko; 
    
    double bestScore = calcScore(firstTate, firstYoko); 
    vector<ll> bestTate = firstTate; 
    vector<ll> bestYoko = firstYoko; 
    double posScore = bestScore; 
    
    // 焼きなましスタート
    while(true){
        clock_t pos_time = clock();
        if(pos_time - start > END_TIME) break;
        
        float lapse = pos_time - start;
        float progressRatio = lapse / END_TIME;   // 進捗。開始時が0.0、終了時が1.0
        float temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;
        
        pair<vector<ll>, vector<ll> > next = update(tate, yoko); 
        double nextScore = calcScore(next.first, next.second); 
        double delta = nextScore - posScore;
        float probability = exp(delta / temp);
        
        if(nextScore > bestScore){
            bestScore = nextScore;
            bestTate = next.first; 
            bestYoko = next.second; 
        }
        
        if(probability > uniform(eng)){
            posScore = nextScore;
            tate = next.first; 
            yoko = next.second; 
        }
    }
    
    //cout << "bestscore : " << bestScore << endl;
    pair<vector<ll>, vector<ll> > ret = make_pair(bestTate, bestYoko); 
    return ret; 
}

void printAnswer(vector<ll>& tate, vector<ll>& yoko){
    cout << len(tate) + len(yoko) << endl;
    for(auto x : tate){
        cout << x << " 0 " << x << " 1" << endl; 
    }
    for(auto y : yoko){
        cout << "0 " << y << " 1 " << y << endl;
    }
} 

int main(){
    start = clock(); 
    cin >> n >> k; 
    frep(i, 1, 11){ 
        cin >> A[i]; 
        totalA += A[i]; 
    }
    rep(i, n){
        ll x, y; 
        cin >> x >> y; 
        yokoNG.insert(y); 
        tateNG.insert(x); 
        P p = make_pair(y, x);
        berry.push_back(p); 
    }
    
    pair<vector<ll>, vector<ll> > initialAnswer = makeBestInitialAnswer(); 
    pair<vector<ll>, vector<ll> > answer = SA(initialAnswer.first, initialAnswer.second); 
    printAnswer(answer.first, answer.second); 
}
