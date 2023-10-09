#include <bits/stdc++.h>
// #define MOD 1000000007
#define MOD 998244353
#define ll long long
#define ld long double
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
#define brep(i, n) for (ll i = (ll)(n - 1); i >= 0; i--)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define len(x) (ll)x.size()
#define pprint(x) cout << fixed << setprecision(12) << x << endl
#define bs(st, key) (st.find(key) != st.end() ? true : false)
#define lb(v, k) lower_bound(v.begin(), v.end(), k) 
#define ub(v, k) upper_bound(v.begin(), v.end(), k)
#define all(v) v.begin(), v.end()
using namespace std;

// const ll neighbor_vec[][2] = {{1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
const ll neighbor_vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const ld PI = 3.141592653589793238462643;

ll POW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a; if(n % 2 == 1) return a * POW(a, n - 1); ll t = POW(a, n / 2); return t * t;}
ll MODPOW(ll a, ll n){if(n == 0) return 1; if(n == 1) return a % MOD; if(n % 2 == 1) return (a * MODPOW(a, n - 1)) % MOD; ll t = MODPOW(a, n / 2); return (t * t) % MOD;}
ll MODINV(ll a){return MODPOW(a, MOD - 2);}
ll CEIL(ll a, ll b){ll ret = (a + b - 1) / b; return ret;}
ll max(ll a, ll b){if(a > b) return a; else return b;}
ll min(ll a, ll b){if(a > b) return b; else return a;}
double min(double a, double b){if(a > b) return b; else return a;}
ll max(ll a, ll b, ll c){ll d = max(a, b); return max(c, d);}
ll min(ll a, ll b, ll c){ll d = min(a, b); return min(c, d);}
void chmax(ll& a, ll b){if(b > a) a = b;}
void chmin(ll& a, ll b){if(a > b) a = b;}
void yes(bool b){if(b) cout << "Yes" << endl; else cout << "No" << endl;}
void print(){cout << endl;}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail){cout << head << " "; print(std::forward<Tail>(tail)...);}
template<typename T> void vprint(vector<T>& v){for(T x : v) cout << x << " "; cout << endl;}
using P = pair<ll, ll>;
bool sameP(P& p1, P& p2){if(p1.first == p2.first && p1.second == p2.second) return true; else return false;}
void print_pair(P& p){cout << p.first << " " << p.second << endl;}
using T = tuple<ll, ll, ll>; // ll x, y, z; tie(x, y, z) = T
template<typename T> using PQ = priority_queue<T>;
template<typename T> using IQ = priority_queue<T, vector<T>, greater<T>>;
using Mat = vector<vector<ll>>;
Mat init_mat(ll a, ll b){Mat ret(a, vector<ll>(b, 0)); return ret;}
Mat init_mat(ll a, ll b, ll c){Mat ret(a, vector<ll>(b, c)); return ret;}
template<typename T>
void print_mat(vector<vector<T>>& mat){rep(i, mat.size()){rep(j, mat[i].size()){cout << mat[i][j] << " ";}cout << endl;}}
using PMat = vector<vector<P>>;
PMat init_pmat(ll a, ll b){PMat ret(a, vector<P>(b, P(0, 0))); return ret;}
PMat init_pmat(ll a, ll b, P c){PMat ret(a, vector<P>(b, c)); return ret;}
using BMat = vector<vector<bool>>;
BMat init_bmat(ll a, ll b){BMat ret(a, vector<bool>(b, false)); return ret;}
BMat init_bmat(ll a, ll b, bool c){BMat ret(a, vector<bool>(b, c)); return ret;}
using DMat = vector<vector<double>>;
DMat init_dmat(ll a, ll b){DMat ret(a, vector<double>(b, 0.0)); return ret;}
DMat init_dmat(ll a, ll b, double c){DMat ret(a, vector<double>(b, c)); return ret;}
using Tensor = vector<vector<vector<ll>>>;
Tensor init_tensor(ll a, ll b, ll c){Tensor ret(a, Mat(b, vector<ll>(c, 0))); return ret;}
Tensor init_tensor(ll a, ll b, ll c, ll d){Tensor ret(a, Mat(b, vector<ll>(c, d))); return ret;}

using Graph = vector<vector<ll> >;
Graph init_graph(ll V){Graph ret; vector<ll> empty; rep(i, V) ret.push_back(empty); return ret;}

struct Edge{
    ll number, from, to; 
    ll cost;
    Edge(){}
    Edge(ll a) : to(a){}
    Edge(ll a, ll b) : to(a), cost(b){}
    Edge(ll a, ll b, ll c) : from(a), to(b), cost(c){}
    Edge(ll a, ll b, ll c, ll d) : number(a), from(b), to(c), cost(d){}
    bool operator > (const Edge& another) const{return cost > another.cost;}
    bool operator < (const Edge& another) const{return cost < another.cost;}
}; 
using EdgeGraph = vector<vector<Edge> >;
EdgeGraph init_edgeGraph(ll V){EdgeGraph ret; vector<Edge> empty; rep(i, V) ret.push_back(empty); return ret;}

random_device rd;
mt19937 eng(0);
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

// 入力
ll L, N, SIGMA; 

// 定数
const ll MAX_MEASURE_COUNT = 1e4; 
const Mat NEIGHBOR_VEC = {
    {0, 0}, 
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}, 
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}, 
    {2, 0}, {-2, 0}, {0, 2}, {0, -2}
}; 



// 向き
struct Direction{
    ll y, x;
    Direction(){}
    Direction(ll y_, ll x_) : y(y_), x(x_){
        assert(0 <= y && y < L && 0 <= x && x < L); 
    }
    inline ll get_hash(){ return y * L + x; }

    // 実装上分かりにくいのでdirectionは正にしているが、出力するときの大きさは異なる
    ll get_direction_size(){
        ll y_size = min(y, abs(y - L)); 
        ll x_size = min(x, abs(x - L)); 
        return y_size + x_size;  
    }
}; 

struct Place{
    ll y, x; 
    Place(){}
    Place(ll y_, ll x_) : y(y_), x(x_){}

    // 他点へのベクトルを取得する
    // このときベクトルは0以上L未満
    Direction get_direction(const Place& another){
        ll dy = (another.y - y + L) % L; 
        ll dx = (another.x - x + L) % L;
        assert(0 <= dy && dy < L && 0 <= dx && dx < L); 
        return Direction(dy, dx);  
    }

    // 距離を計算する
    ll calc_distance(const Place& another){
        ll dy = min((y - another.y + L) % L, (another.y - y + L) % L); 
        ll dx = min((x - another.x + L) % L, (another.x - x + L) % L); 
        return dy + dx; 
    }

    ll get_hash(){ return L * y + x; }

    bool operator == (const Place& another) const{return y == another.y && x == another.x;}
}; 


struct TargetMount{
    ll number; 
    Place place; 
    ll size; 

    TargetMount(){}
    TargetMount(ll number_, Place& place_, ll size_) : number(number_), place(place_), size(size_){}
}; 


struct Hole{
    ll number; 
    Place place; 
    TargetMount target_mount; 
    ll group; 
    bool set_target_mount_flag = false; 

    Hole(){}
    Hole(ll number_, Place place_) : number(number_), place(place_){}

    Direction get_target_direction(){ 
        assert(set_target_mount_flag); 
        return place.get_direction(target_mount.place); 
    }

    void set_group(ll group_){ 
        group = group_; 
    }

    void set_target_mount(TargetMount target_mount_){
        set_target_mount_flag = true; 
        target_mount = target_mount_; 
        assert(0 <= target_mount.place.y && target_mount.place.y < L && 0 <= target_mount.place.x && target_mount.place.x < L); 
    }
}; 

vector<Hole> hole_vec; 


struct Result{
    ll y, x; 
    ll measured_temp; 

    Result(){}
    Result(ll y_, ll x_, ll measured_temp_) : y(y_), x(x_), measured_temp(measured_temp_){}
}; 


enum class State{
    SUCCESS,   // 答えを見つけられた
    FAILURE,   // 答えを見つけられなかった
    TIMEOUT,   // 途中で回数制限を超えてしまった
}; 


enum class CellState{
    MINUS,    // マイナス
    ZERO,     // ない
    ONE,      // ある
    UNKNOWN   // まだ分からん
}; 


struct TournameResult{
    ll number;   // entranceとholeどちらでも使うため
    State state; 
    TournameResult(){}
    TournameResult(ll number_, State state_) : number(number_), state(state_){
        if(state == State::SUCCESS) assert(number >= 0); 
        else assert(number < 0); 
    } 
}; 


enum class Difficulty{
    VERY_EASY, 
    EASY, 
    MIDDLE, 
    HARD, 
}; 


namespace Norm{
    template<typename T>
    struct CumulativeSum{
        vector<T> v, sum; 
        ll n;
        
        CumulativeSum(){}
        CumulativeSum(vector<T>& v_) : v(v_){ init(); }
        
        void init(){
            n = v.size(); 
            sum.resize(n + 1, (T)0);
            rep(i, n) sum[i + 1] = sum[i] + v[i];
        }
        
        // [a, b)の和を出力
        T query(ll a, ll b){ return sum[b] - sum[a]; }
        
        // [0, b)の和を出力
        T query(ll b){ return sum[b]; }
        
        // 全ての和
        T getAllSum(){ return sum[n]; }
    }; 


    struct Norm{
        ll sigma; 
        ll sigma_2; 
        CumulativeSum<double> cs; 

        bool build_flag = false; 

        const ll CS_MIN = -5000; 
        const ll CS_MAX = 5000; 
        const double INTERVAL = 0.01; 
        const ll CS_SIZE = (CS_MAX - CS_MIN) / INTERVAL; 

        Norm(){}

        void build(ll sigma_){
            // 複数回buildしないようにする
            assert(!build_flag); 
            build_flag = true; 

            sigma = sigma_; 
            sigma_2 = sigma * sigma; 
            build_cs();
        }


        void build_cs(){
            assert(CS_MAX + CS_MIN == 0); 
            vector<double> v(CS_SIZE); 
            rep(i, CS_SIZE) v[i] = gauss((i + CS_MIN / INTERVAL) * INTERVAL, 0) * INTERVAL;
            cs = CumulativeSum<double>(v); 
        }


        // 平均がmuの時にxが出る確率
        double query(ll x, ll mu){
            if(x == 0){
                ll idx = ((0 - mu) - CS_MIN) / INTERVAL; 
                return cs.query(idx); 
            }
            else if(x == 1000){
                ll idx = ((1000 - mu) - CS_MIN) / INTERVAL; 
                return 1.0 - cs.query(idx); 
            }
            else return gauss(x, mu); 
        }


        inline double gauss(double x, double mu){
            return 1.0 / sqrt(2.0 * PI * sigma_2) * exp(-1 * pow(x - mu, 2) / (2.0 * sigma_2));     
        }
    }; 
}; 



struct PatternMaker{
    ll use_neighbor_vec_size; 
    ll time_limit; 
    bool minus_ok; 

    Mat hole_mat; 

    Mat pos_mat;
    vector<ll> pos_pattern_vec; 
    vector<set<ll>> pattern_st_vec; 
    set<ll> non_unique_pattern_st;   // uniqueではないpattern

    const vector<ll> BASE = {
        // 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072 
        1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147
    }; 

    PatternMaker(){}

    void init(ll use_neighbor_vec_size_, bool minus_ok_, ll time_limit_){
        // クラス変数割り当て
        use_neighbor_vec_size = use_neighbor_vec_size_; 
        minus_ok = minus_ok_; 
        time_limit = time_limit_; 

        // 初期構築
        pos_pattern_vec.clear();
        pos_pattern_vec.resize(N, 0); 
        pattern_st_vec.clear(); 
        pattern_st_vec.resize(BASE[BASE.size() - 1] * 3); 
        ll first_hash = 0; 
        rep(i, use_neighbor_vec_size) first_hash += BASE[i] * 1; 
        rep(i, N) pattern_st_vec[first_hash].insert(i); 
        rep(i, N) pos_pattern_vec[i] = first_hash; 
        non_unique_pattern_st.clear();
        non_unique_pattern_st.insert(first_hash);
        hole_mat = init_mat(L, L, -1); 
        pos_mat = init_mat(L, L, 1);
        for(Hole& hole : hole_vec){
            Place place = hole.place; 
            hole_mat[place.y][place.x] = hole.number; 
        }
    }

    // 構築に成功したかどうかを返す
    bool solve(){
        clock_t THIS_START = clock();  
        build_first_pos_mat_randomly(); 
        while(non_unique_pattern_st.size() != 0){
            if(clock() - THIS_START > time_limit) return false; 
            ll r = randInt(eng) % 2; 
            if(r == 0) transition_add(); 
            else transition_del(); 
            // transition_flip(); 
        }
        return true; 
    }

    // 適当にpos_matを初期化する
    void build_first_pos_mat_randomly(){
        for(Hole& hole : hole_vec){
            rep(i, use_neighbor_vec_size){
                ll r = randInt(eng) % 4;
                Place place = f(hole.place, i); 
                if(r == 0) flip(place, 2);  
                else flip(place, 1); 
            }
        }
    }


    // 色を塗る
    void transition_add(){
        // どのpattern
        ll r_1 = randInt(eng) % non_unique_pattern_st.size();
        auto it_1 = non_unique_pattern_st.begin(); 
        rep(_, r_1) it_1++; 
        ll target_pattern = *it_1;

        // どの穴
        ll r_2 = randInt(eng) % pattern_st_vec[target_pattern].size();
        auto it_2 = pattern_st_vec[target_pattern].begin(); 
        rep(_, r_2) it_2++; 
        ll target_hole_number = *it_2; 

        // どのplace
        vector<Place> target_place_vec; 
        Place target_hole_place = hole_vec[target_hole_number].place; 
        rep(i, use_neighbor_vec_size){
            Place place = f(target_hole_place, i); 
            if(pos_mat[place.y][place.x] == 1) target_place_vec.push_back(place); 
        }

        // 全部塗られているならごめんなさい
        if(target_place_vec.size() == 0) return; 

        // 場所を決定
        ll r_3 = randInt(eng) % target_place_vec.size(); 
        Place target_place = target_place_vec[r_3]; 

        // 色を消す前に前の値を保存しておく
        ll prev_value = pos_mat[target_place.y][target_place.x]; 

        // 値を決定する
        ll r_4; 
        if(minus_ok == false) r_4 = 2; 
        else r_4 = 2 * (randInt(eng) % 2); 

        // 実際に色を塗ってみる
        ll prev_non_unique_size = non_unique_pattern_st.size();   // 遷移前
        flip(target_place, r_4); 
        ll after_non_unique_size = non_unique_pattern_st.size();   // 遷移後

        // 悪化したなら元に戻す
        // 同点はacceptすることで遷移の幅を増やす
        if(prev_non_unique_size > after_non_unique_size && randInt(eng) % 5 != 0){ 
            // print("# add reject"); 
            flip(target_place, prev_value); 
            assert(prev_non_unique_size == non_unique_pattern_st.size());
        }
        // else print("# add accept"); 
    }


    // 色を消す
    void transition_del(){
        // どのpattern
        ll r_1 = randInt(eng) % non_unique_pattern_st.size();
        auto it_1 = non_unique_pattern_st.begin(); 
        rep(_, r_1) it_1++; 
        ll target_pattern = *it_1;

        // どの穴
        ll r_2 = randInt(eng) % pattern_st_vec[target_pattern].size();
        auto it_2 = pattern_st_vec[target_pattern].begin(); 
        rep(_, r_2) it_2++; 
        ll target_hole_number = *it_2; 

        // どのplace
        vector<Place> target_place_vec; 
        Place target_hole_place = hole_vec[target_hole_number].place; 
        rep(i, use_neighbor_vec_size){
            Place place = f(target_hole_place, i); 
            if(pos_mat[place.y][place.x] != 1) target_place_vec.push_back(place); 
        }

        // 全部消されてるならごめんなさい
        if(target_place_vec.size() == 0) return; 

        // 場所を決定
        ll r_3 = randInt(eng) % target_place_vec.size(); 
        Place target_place = target_place_vec[r_3]; 

        // 色を消す前に前の値を保存しておく
        ll prev_value = pos_mat[target_place.y][target_place.x]; 

        // 実際に色を消してみる
        ll prev_non_unique_size = non_unique_pattern_st.size();   // 遷移前
        flip(target_place, 1); 
        ll after_non_unique_size = non_unique_pattern_st.size();   // 遷移後

        // 悪化したなら元に戻す
        // 同点はacceptすることで遷移の幅を増やす
        if(prev_non_unique_size > after_non_unique_size && randInt(eng) % 5 != 0){ 
            // print("# del reject"); 
            flip(target_place, prev_value); 
            assert(prev_non_unique_size == non_unique_pattern_st.size());
        }
        // else print("# del accept"); 
    }


    // 色を塗る
    void transition_flip(){
        // どのpattern
        ll r_1 = randInt(eng) % non_unique_pattern_st.size();
        auto it_1 = non_unique_pattern_st.begin(); 
        rep(_, r_1) it_1++; 
        ll target_pattern = *it_1;

        // どの穴
        ll r_2 = randInt(eng) % pattern_st_vec[target_pattern].size();
        auto it_2 = pattern_st_vec[target_pattern].begin(); 
        rep(_, r_2) it_2++; 
        ll target_hole_number = *it_2; 

        // どのplace
        Place target_hole_place = hole_vec[target_hole_number].place; 
        ll r_3 = randInt(eng) % use_neighbor_vec_size; 
        Place target_place = f(target_hole_place, r_3); 

        // 値を決定
        // 同じでない値ならok
        ll prev_value = pos_mat[target_place.y][target_place.x];   // 前の値を保存しておく
        vector<ll> cand_vec;   // 候補
        rep(i, 3){
            if(i == prev_value) continue;   // 前と同じには遷移しない
            if(i == 0 && minus_ok == false) continue;   // マイナスが許されない時
            if(i == 1) cand_vec.push_back(i); 
            else if(i == 0 || i == 2){
                bool flag = true; 
                rep(k, 4){
                    ll dy = (target_place.y + neighbor_vec[k][0] + L) % L;
                    ll dx = (target_place.x + neighbor_vec[k][1] + L) % L;
                    if(abs(i - pos_mat[dy][dx]) >= 2) flag = false; 
                }
                if(flag) cand_vec.push_back(i); 
            }
        }

        if(cand_vec.size() == 0) return; 
        ll r_4 = cand_vec[randInt(eng) % cand_vec.size()]; 

        ll r_5 = randInt(eng) % 2; 
        if(r_5 == 0 && r_4 > prev_value) return; 
        if(r_5 == 1 && r_4 < prev_value) return; 
        
        // 実際に値を変えてみる
        ll prev_non_unique_size = non_unique_pattern_st.size();   // 遷移前
        flip(target_place, r_4); 
        ll after_non_unique_size = non_unique_pattern_st.size();   // 遷移後

        // 悪化したなら元に戻す
        // 同点はacceptすることで遷移の幅を増やす
        if(prev_non_unique_size > after_non_unique_size && randInt(eng) % 5 != 0){ 
            // print("# reject"); 
            flip(target_place, prev_value); 
            assert(prev_non_unique_size == non_unique_pattern_st.size());
        }
        // else print("# accept"); 
    }


    // 値をrに変更する時
    void flip(Place& place, ll r){
        // assert(pos_mat[place.y][place.x] == false); 
        ll p = pos_mat[place.y][place.x]; 
        // 同じなら何もしない
        if(pos_mat[place.y][place.x] == r) return; 

        pos_mat[place.y][place.x] = r;  
        rep(i, use_neighbor_vec_size){
            // placeに色を塗ったことでpatternに変化がある穴
            Place effective_place = inv(place, i); 
            ll hole_number = hole_mat[effective_place.y][effective_place.x]; 
            if(hole_number < 0) continue; 
            ll pos_pattern = pos_pattern_vec[hole_number]; 

            // pattern_st_vecから前のpatternを削除する
            auto it = pattern_st_vec[pos_pattern].find(hole_number); 
            assert(it != pattern_st_vec[pos_pattern].end()); 
            pattern_st_vec[pos_pattern].erase(it); 

            // 削除したときにuniqueになったかを判定
            if(pattern_st_vec[pos_pattern].size() == 1){
                auto it_2 = non_unique_pattern_st.find(pos_pattern); 
                assert(it_2 != non_unique_pattern_st.end()); 
                non_unique_pattern_st.erase(it_2); 
            }

            // new_patternを追加
            ll new_pattern = get_pattern(hole_number);
            pattern_st_vec[new_pattern].insert(hole_number); 
            pos_pattern_vec[hole_number] = new_pattern; 
            // print("add", effective_place.y, effective_place.x, pos_pattern, new_pattern); 

            /*
            print("# "); 
            print("#", p, "->", r);
            print("#", i, place.y, place.x, effective_place.y, effective_place.x); 
            print("# pos", pos_pattern);
            print("# new", new_pattern); 
            print("# ");
            */

            // 追加したときにuniqueでなくなったかもしれない
            if(pattern_st_vec[new_pattern].size() == 2) non_unique_pattern_st.insert(new_pattern); 
        }
    }


    void del_marginal_mount(){
        rep(i, L){
            rep(j, L){
                assert(non_unique_pattern_st.size() == 0); 
                if(pos_mat[i][j] != 1) continue; 
                ll prev_value = pos_mat[i][j]; 
                Place place(i, j); 
                flip(place, 1); 

                // ダメだったら元に戻す
                if(non_unique_pattern_st.size() > 0) flip(place, prev_value); 
            }
        }
    }


    ll think_best_index(vector<CellState>& cell_state_vec, set<ll>& already_used_pattern_st){
        assert(cell_state_vec.size() == use_neighbor_vec_size); 
        vector<ll> pos_probable_pattern_vec = get_probable_pattern_vec(cell_state_vec, already_used_pattern_st);
        ll pos_probable_pattern_vec_size = pos_probable_pattern_vec.size(); 
        if(pos_probable_pattern_vec_size == 1) return -1; 

        set<ll> st; 
        for(ll x : pos_probable_pattern_vec){
            rep(i, N){
                if(pos_pattern_vec[i] == x) st.insert(i); 
            }
        }
        // cout << "# cand :"; 
        // irep(it, st) cout << *it << " "; 
        // cout << endl;
        
        ll best_index = -1; 
        ll best_score = 1e10; 
        rep(i, use_neighbor_vec_size){
            if(cell_state_vec[i] != CellState::UNKNOWN) continue; 
            vector<CellState> v = {CellState::MINUS, CellState::ZERO, CellState::ONE}; 
            vector<ll> pattern_size_vec; 
            ll sum = 0; 
            // cout << "# prob " << i << "   "; 
            for(CellState& next_cell_state : v){
                vector<CellState> next_cell_state_vec = cell_state_vec; 
                next_cell_state_vec[i] = next_cell_state; 
                ll next_probable_pattern_vec_size = get_probable_pattern_vec(next_cell_state_vec, already_used_pattern_st).size(); 
                pattern_size_vec.push_back(next_probable_pattern_vec_size); 
                sum += next_probable_pattern_vec_size; 
                // score = max(score, pos_probable_pattern_vec_size - next_probable_pattern_vec_size); 
                // cout << next_probable_pattern_vec_size << " "; 
            }
            // cout << endl;
            ld average = (ld)sum / (ld)v.size(); 
            ld score = 0; 
            for(ll x : pattern_size_vec) score += pow(average - x, 2); 

            if(score < best_score){
                best_index = i; 
                best_score = score; 
            }
        }
        print("# best ", best_index);
        assert(best_index >= 0); 

        return best_index; 
    }


    ll get_hole_number(vector<CellState>& cell_state_vec, set<ll>& already_used_pattern_st){
        assert(cell_state_vec.size() == use_neighbor_vec_size); 
        vector<ll> pos_probable_pattern_vec = get_probable_pattern_vec(cell_state_vec, already_used_pattern_st); 
        assert(pos_probable_pattern_vec.size() != 0); 
        if(pos_probable_pattern_vec.size() > 1) return -1; 
        else{
            ll pattern = pos_probable_pattern_vec[0]; 
            return *pattern_st_vec[pattern].begin();
        }
    }


    // ありえるpatternを列挙する
    vector<ll> get_probable_pattern_vec(vector<CellState>& cell_state_vec, set<ll>& already_used_pattern_st){
        assert(cell_state_vec.size() == use_neighbor_vec_size); 
        vector<ll> pos_vec = {0}; 
        rep(i, use_neighbor_vec_size){
            vector<ll> next_vec; 
            for(ll pos : pos_vec){
                CellState cell_state = cell_state_vec[i]; 
                if(cell_state == CellState::MINUS || cell_state == CellState::UNKNOWN){
                    ll pattern = pos; 
                    next_vec.push_back(pattern); 
                }
                if(cell_state == CellState::ZERO || cell_state == CellState::UNKNOWN){
                    ll pattern = pos + BASE[i]; 
                    next_vec.push_back(pattern); 
                }
                if(cell_state == CellState::ONE || cell_state == CellState::UNKNOWN){
                    ll pattern = pos + BASE[i] * 2; 
                    next_vec.push_back(pattern); 
                }
            }
            pos_vec.clear(); 
            pos_vec = next_vec; 
        }

        // 存在する && 使われていないか
        vector<ll> ret; 
        for(ll x : pos_vec){
            if(pattern_st_vec[x].size() > 0 && bs(already_used_pattern_st, x) == false) ret.push_back(x); 
        }
        return ret; 
    }


    ll get_pattern(ll hole_number){
        ll ret = 0; 
        Place place = hole_vec[hole_number].place; 
        rep(i, use_neighbor_vec_size){
            Place pattern_place = f(place, i);
            ret += pos_mat[pattern_place.y][pattern_place.x] * BASE[i]; 
        }
        return ret; 
    }


    // 同じパターンのhole_numberを返す
    ll get_hole_number(vector<ll>& v){
        assert(v.size() == use_neighbor_vec_size); 
        ll pattern = 0; 
        rep(i, use_neighbor_vec_size){
            pattern += v[i] * BASE[i]; 
        }   
        if(pattern_st_vec[pattern].size() == 0){
            print("# not find"); 
            return -1; 
        }
        else{
            // assert(pattern_st_vec[pattern].size() == 1); 
            return *pattern_st_vec[pattern].begin(); 
        }
    }


    Place f(ll y, ll x, ll neighbor_index){
        assert(neighbor_index < NEIGHBOR_VEC.size()); 
        ll dy = (y + NEIGHBOR_VEC[neighbor_index][0] + L) % L; 
        ll dx = (x + NEIGHBOR_VEC[neighbor_index][1] + L) % L; 
        return Place(dy, dx); 
    }
    Place f(Place& place, ll neighbor_index){ return f(place.y, place.x, neighbor_index); }

    Place inv(ll y, ll x, ll neighbor_index){
        assert(neighbor_index < NEIGHBOR_VEC.size()); 
        ll dy = (y - NEIGHBOR_VEC[neighbor_index][0] + L) % L; 
        ll dx = (x - NEIGHBOR_VEC[neighbor_index][1] + L) % L; 
        return Place(dy, dx); 
    }
    Place inv(Place& place, ll neighbor_index){ return inv(place.y, place.x, neighbor_index); }
}; 



struct Solver{
    Mat temp_mat; 
    vector<ll> ans_vec;   // 出口の番号
    vector<bool> assigned_vec;   // すでに使われた出口
    vector<TargetMount> target_mount_vec;   // 位置特定用の山
    vector<set<ll>> direction_hash_collection;   // 各セルに山を作る時に使うベクトル
    Norm::Norm norm;   // 正規分布に関する計算を行う
    PatternMaker pattern_maker_list[20]; 

    ll measure_count = 0; 

    Difficulty DIFFICULTY;   // 問題の難易度 
    ll TARGET_MOUNT_TEMP;   // 位置特定用の山の高さ
    ll MARK_MOUNT_TEMP;   // 半分に分ける用の山の高さ

    // ll MIDDLE_GIVE_UP_MEASURE_COUNT = 40;  
    // ll HARD_GIVE_UP_MEASURE_COUNT = 40;  

    ll PRE_SEARCH_COUNT; 
    ll PRE_SEARCH_CUT_RATIO; 

    ll USE_NEIGHBOR_VEC_SIZE; 
    bool MINUS_OK; 

    Solver(){ init(); }

    void init(){
        ans_vec.resize(N, -1); 
        assigned_vec.resize(N, false); 

        norm.build(SIGMA); 
    }

    void solve(){
        set_param(); 
        set_temp_mat(); 
        print_temp_mat();
        if(DIFFICULTY == Difficulty::VERY_EASY) solve_very_easy();
        if(DIFFICULTY == Difficulty::EASY) solve_easy(); 
        if(DIFFICULTY == Difficulty::MIDDLE) solve_middle();
        if(DIFFICULTY == Difficulty::HARD) solve_hard(); 
        print_ans();
    }

    // 初期値設定関係
    //==================================================================================================================
    void set_param(){
        // 将来的には全てモンテカルロ
        if(SIGMA <= 9) DIFFICULTY = Difficulty::VERY_EASY;
        else if(SIGMA == 16 && N >= 70) DIFFICULTY = Difficulty::VERY_EASY;
        else if(SIGMA == 900 && N >= 95) DIFFICULTY = Difficulty::HARD; 
        else DIFFICULTY = Difficulty::MIDDLE; 

        // 山の高さ
        if(DIFFICULTY == Difficulty::VERY_EASY){
            if(SIGMA == 1){ 
                TARGET_MOUNT_TEMP = 10 * SIGMA; 
                MINUS_OK = true; 
            }
            if(SIGMA == 4){ 
                TARGET_MOUNT_TEMP = 6 * SIGMA; 
                MINUS_OK = true; 
            }
            if(SIGMA == 9){ 
                TARGET_MOUNT_TEMP = 4 * SIGMA; 
                MINUS_OK = false; 
            }
            if(SIGMA == 16){ 
                TARGET_MOUNT_TEMP = 3.5 * SIGMA;
                MINUS_OK = false; 
            }

            MARK_MOUNT_TEMP = TARGET_MOUNT_TEMP / 2;   
            PRE_SEARCH_COUNT = 5;         // 一応書いているが意味ない
            PRE_SEARCH_CUT_RATIO = 1e5;   // 一応書いているが意味ない
            assert(TARGET_MOUNT_TEMP <= 1000); 
        }
        else if(DIFFICULTY == Difficulty::HARD){
            MINUS_OK = false; 
            TARGET_MOUNT_TEMP = min(1000, 3 * SIGMA); 
            MARK_MOUNT_TEMP = TARGET_MOUNT_TEMP / 2;
            PRE_SEARCH_COUNT = 20; 
            PRE_SEARCH_CUT_RATIO = 1e4; 
        }
        else if(DIFFICULTY == Difficulty::EASY){
            assert(SIGMA <= 100); 
            TARGET_MOUNT_TEMP = 10 * SIGMA; 
            MARK_MOUNT_TEMP = TARGET_MOUNT_TEMP / 2;
        }
        else{
            if(SIGMA <= 144) TARGET_MOUNT_TEMP = SIGMA * 4;
            else TARGET_MOUNT_TEMP = min(1000, 3 * SIGMA); 
            MARK_MOUNT_TEMP = TARGET_MOUNT_TEMP / 2; 
        }
    }


    // 配置関係
    //==================================================================================================================
    void set_temp_mat(){
        if(DIFFICULTY == Difficulty::VERY_EASY || DIFFICULTY == Difficulty::HARD){
            set_temp_mat_pattern(); 
        }
        else{
            set_target_place(); 
            temp_mat = init_mat(L, L, 0); 

            // 位置特定用の穴
            for(TargetMount& target_mount : target_mount_vec){
                Place place = target_mount.place; 
                temp_mat[place.y][place.x] = target_mount.size; 
            }
        }
    }


    void set_temp_mat_pattern(){
        clock_t START = clock(); 
        ll first_use_neighbor_vec_size;
        if(MINUS_OK) first_use_neighbor_vec_size = 5; 
        else first_use_neighbor_vec_size = 8;  
        pattern_maker_list[first_use_neighbor_vec_size].init(first_use_neighbor_vec_size, MINUS_OK, 4e5);
        bool first_build_success = pattern_maker_list[first_use_neighbor_vec_size].solve(); 

        if(first_build_success){
            USE_NEIGHBOR_VEC_SIZE = first_use_neighbor_vec_size; 
            ll pos_use_neighbor_vec_size = first_use_neighbor_vec_size; 
            while(pos_use_neighbor_vec_size > 0){
                if(clock() - START >= 3e6) break;
                pos_use_neighbor_vec_size--; 
                pattern_maker_list[pos_use_neighbor_vec_size].init(pos_use_neighbor_vec_size, MINUS_OK, 4e5); 
                bool build_success = pattern_maker_list[pos_use_neighbor_vec_size].solve(); 
                if(build_success){
                    USE_NEIGHBOR_VEC_SIZE = pos_use_neighbor_vec_size; 
                }
                else break;
            }
        }
        else{
            ll pos_use_neighbor_vec_size = first_use_neighbor_vec_size; 
            while(pos_use_neighbor_vec_size > 0){
                pos_use_neighbor_vec_size++; 
                pattern_maker_list[pos_use_neighbor_vec_size].init(pos_use_neighbor_vec_size, MINUS_OK, 4e5); 
                bool build_success = pattern_maker_list[pos_use_neighbor_vec_size].solve(); 
                if(build_success){
                    USE_NEIGHBOR_VEC_SIZE = pos_use_neighbor_vec_size; 
                    break; 
                }
            }
        }
        pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].del_marginal_mount();   // 余計な山を消す
        print("# USE NEIGHBOR_VEC_SIZE :", USE_NEIGHBOR_VEC_SIZE);
     
        temp_mat = init_mat(L, L, 0); 
        rep(i, L){
            rep(j, L){
                if(DIFFICULTY == Difficulty::VERY_EASY){
                    temp_mat[i][j] = 500 + (pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].pos_mat[i][j] - 1) * TARGET_MOUNT_TEMP; 
                }
                else if(DIFFICULTY == Difficulty::HARD){
                    assert(1 <= pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].pos_mat[i][j] && pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].pos_mat[i][j] <= 2); 
                    temp_mat[i][j] = 1000 * (pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].pos_mat[i][j] - 1); 
                }
                else assert(false); 
            }
        }
    }


    // 位置特定用の山の位置を決める
    void set_target_place(){
        // assert(L * L != N);   // 空いているスペースがないパターン（後で別に処理するように書き換え）

        ll MAX_MOUNT_NUM; 
        if(SIGMA <= 49) MAX_MOUNT_NUM = 2; 
        else if(SIGMA == 64 && L >= 30) MAX_MOUNT_NUM = 2;
        else if(SIGMA == 81 && L >= 40) MAX_MOUNT_NUM = 2; 
        else MAX_MOUNT_NUM = 1; 
        assert(MAX_MOUNT_NUM <= 2);   // 3以上の挙動を想定していない

        build_direction_hash_collection(); 

        // 同じ大きさの山をMAX_MOUNT_NUM個置く
        // directionが重複しない必要があるため、MAX_MOUNT_NUMが大きいときは成功する可能性は低い
        ll best_score = 1e10; 
        vector<Place> best_target_place_vec; 
        set<ll> visit_target_place_vec_hash_st; 
        frep(i, 1, MAX_MOUNT_NUM + 1){
            ll count = 0; 
            ll USABLE_TIME = (i == 1 ? 1e5 : 2e6); 
            clock_t THIS_START = clock(); 
            while(clock() - THIS_START <= USABLE_TIME){
                vector<Place> target_place_vec = generate_random_place_vec(i); 

                // 同じ組合せは複数回試さない
                ll target_place_vec_hash = get_target_place_vec_hash(target_place_vec); 
                if(bs(visit_target_place_vec_hash_st, target_place_vec_hash)) continue; 
                else visit_target_place_vec_hash_st.insert(target_place_vec_hash); 

                count++; 

                if(check_multiple_direction(target_place_vec) == false) continue; 
                ll score = 0; 
                rep(hole_number, N){
                    ll assigned_index = assign_target_place(hole_number, target_place_vec); 
                    score += hole_vec[hole_number].place.calc_distance(target_place_vec[assigned_index]);   // 距離をスコアに加算
                }
                if(score < best_score){
                    best_score = score; 
                    best_target_place_vec = target_place_vec; 
                }
            }
            print("#", count);
        }
        assert(best_target_place_vec.size() > 0);

        rep(i, best_target_place_vec.size()){
            target_mount_vec.push_back(TargetMount(i, best_target_place_vec[i], TARGET_MOUNT_TEMP)); 
        }

        // 各holeにTargetMountをsetする
        rep(hole_number, N){
            ll assigned_index = assign_target_place(hole_number, best_target_place_vec); 
            assert(target_mount_vec[assigned_index].number == assigned_index); 
            hole_vec[hole_number].set_target_mount(target_mount_vec[assigned_index]); 
        } 
    }


    // 各セルに山を作った時のベクトルを保持
    void build_direction_hash_collection(){
        assert(direction_hash_collection.size() == 0); 
        direction_hash_collection.resize(L * L); 
        rep(y, L){
            rep(x, L){
                Place place(y, x); 
                ll place_hash = place.get_hash(); 
                rep(hole_number, N){
                    Direction direction = hole_vec[hole_number].place.get_direction(place); 
                    ll direction_hash = direction.get_hash();
                    direction_hash_collection[place_hash].insert(direction_hash); 
                }
            }
        }
    }


    // ベクトルに重複がないかチェックする
    bool check_multiple_direction(vector<Place>& target_plcae_vec){
        if(target_plcae_vec.size() == 1) return true; 
        set<ll> direction_hash_st; 
        rep(i, target_plcae_vec.size()){
            frep(j, i + 1, target_plcae_vec.size()){
                Place place_1 = target_plcae_vec[i]; 
                Place place_2 = target_plcae_vec[j]; 
                ll place_1_hash = place_1.get_hash(); 
                ll place_2_hash = place_2.get_hash(); 
                irep(it, direction_hash_collection[place_1_hash]){
                    if(bs(direction_hash_collection[place_2_hash], *it)){
                        return false; 
                    }
                }
            }
        }
        return true; 
    }


    // 場所をhashに変換する
    ll get_target_place_vec_hash(vector<Place>& target_place_vec){
        assert(target_place_vec.size() <= 2); 
        vector<ll> hash_vec; 
        for(Place& target_place : target_place_vec){
            hash_vec.push_back(target_place.y * L + target_place.x + 1); 
        }
        if(target_place_vec.size() == 0){
            return hash_vec[0]; 
        }
        else{
            return hash_vec[0] + hash_vec[1] * L * L; 
        }
    }


    // 穴を一番近いtarget_placeに割り当てる
    // 同率の場合はindexが小さいものを優先する
    ll assign_target_place(ll hole_number, vector<Place>& target_place_vec){
        ll size = target_place_vec.size(); 
        assert(size > 0); 
        ll best_score = 1e10; 
        ll best_index = -1;
        rep(i, size){
            ll score = hole_vec[hole_number].place.calc_distance(target_place_vec[i]); 
            if(best_score > score){
                best_score = score; 
                best_index = i; 
            }
        }
        assert(best_index >= 0); 
        return best_index; 
    }


    // 指定された数までPlaceを生成する
    vector<Place> generate_random_place_vec(ll generate_count){
        assert(generate_count > 0); 
        vector<Place> ret;
        while(ret.size() != generate_count){
            ll y = randInt(eng) % L; 
            ll x = randInt(eng) % L; 
            Place place(y, x); 
            bool flag = true; 
            rep(i, ret.size()){
                if(ret[i] == place) flag = false; 
            }
            ret.push_back(place); 
        } 
        return ret; 
    }


    vector<ll> think_best_combination(){
        ll half_n = N / 2; 
        vector<ll> ret; 
        rep(i, half_n) ret.push_back(i); 
        return ret; 
    }


    // 計測関係
    //==================================================================================================================
    void solve_very_easy(){
        assert(DIFFICULTY == Difficulty::VERY_EASY); 

        set<ll> already_used_pattern_st; 
        rep(entrance_number, N){
            TournameResult tournament_result = tournament_very_easy(entrance_number, already_used_pattern_st); 
            if(tournament_result.state == State::SUCCESS){ 
                ans_vec[entrance_number] = tournament_result.number;   
                assigned_vec[tournament_result.number] = true; 
                ll pattern = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].get_pattern(tournament_result.number); 
                assert(bs(already_used_pattern_st, pattern) == false);
                already_used_pattern_st.insert(pattern);
            }
            print("# count", measure_count);
            if(tournament_result.state == State::SUCCESS) print("# SUCCESS", tournament_result.number); 
            if(tournament_result.state == State::FAILURE) print("# FAILURE");
            if(tournament_result.state == State::TIMEOUT) print("# TIMEOUT");
        }
    }


    TournameResult tournament_very_easy(ll entrance_number, set<ll>& already_used_pattern_st){
        vector<CellState> cell_state_vec(USE_NEIGHBOR_VEC_SIZE);
        rep(i, USE_NEIGHBOR_VEC_SIZE) cell_state_vec[i] = CellState::UNKNOWN; 
        rep(_, USE_NEIGHBOR_VEC_SIZE){
            ll target_index = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].think_best_index(cell_state_vec, already_used_pattern_st); 
            if(target_index >= 0){
                vector<ld> estim_vec(3, 1.0);
                ll ans_index; 
                while(true){
                    Result result = measure(entrance_number, NEIGHBOR_VEC[target_index][0], NEIGHBOR_VEC[target_index][1]);
                    if(MINUS_OK){
                        ld t_01 = norm.query(result.measured_temp, 500 - TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 500);
                        ld t_21 = norm.query(result.measured_temp, 500 + TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 500);
                        ld t_10 = 1.0 / t_01; 
                        ld t_12 = 1.0 / t_21; 
                        estim_vec[0] *= t_01; 
                        estim_vec[2] *= t_21; 
                        estim_vec[1] *= min(t_10, t_12);
                    }
                    else{
                        ld t = norm.query(result.measured_temp, 500 + TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 500);
                        estim_vec[2] *= t; 
                        estim_vec[1] *= (1.0 / t); 
                        estim_vec[0] = 0; 
                    }

                    ld max_estim = get_v_max(estim_vec); 
                    if(max_estim >= 1e4){
                        ans_index = get_argmax(estim_vec); 
                        break; 
                    }
                } 
                if(ans_index == 0) cell_state_vec[target_index] = CellState::MINUS;
                if(ans_index == 1) cell_state_vec[target_index] = CellState::ZERO;
                if(ans_index == 2) cell_state_vec[target_index] = CellState::ONE;
            }
            ll hole_number = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].get_hole_number(cell_state_vec, already_used_pattern_st); 
            if(hole_number >= 0) return TournameResult(hole_number, State::SUCCESS); 
            else continue; 

            // エラーハンドリングがカス...
        } 
        assert(false);
    }


    void solve_easy(){
        assert(DIFFICULTY == Difficulty::EASY); 

        vector<P> cand_pair_vec;   // first: cost, second: hole_number
        rep(hole_number, N){
            Direction direction = hole_vec[hole_number].get_target_direction(); 
            cand_pair_vec.push_back(P(direction.get_direction_size(), hole_number)); 
        }
        sort(all(cand_pair_vec)); 
        for(P& cand_pair : cand_pair_vec){
            ll hole_number = cand_pair.second;
            TournameResult tournament_result = tournament_easy(hole_number); 
            if(tournament_result.state == State::SUCCESS) ans_vec[tournament_result.number] = hole_number; 
        }
    }


    TournameResult tournament_easy(ll hole_number){
        assert(DIFFICULTY == Difficulty::EASY); 

        // 解の候補
        vector<ll> cand_entrance_number_vec; 
        rep(entrance_number, N){
            if(ans_vec[entrance_number] < 0) cand_entrance_number_vec.push_back(entrance_number); 
        }

        vector<ld> estim_vec(N, 0); 
        for(ll entrance_number : cand_entrance_number_vec){
            if(!can_continue_measure()) return TournameResult(-1, State::TIMEOUT); 
            ld prob = 1.0;   // 山である確率
            while(true){
                Result result = measure(entrance_number, hole_vec[hole_number].get_target_direction());
                prob *= norm.query(result.measured_temp, TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 0);
                if(prob >= 1000) return TournameResult(entrance_number, State::SUCCESS); 
                 
            } 
        }

        // 上で決定しなかった場合はargmax 
        return TournameResult(get_argmax(estim_vec), State::SUCCESS); 
    }


    void solve_middle(){
        assert(DIFFICULTY == Difficulty::MIDDLE); 

        vector<P> cand_pair_vec;   // first: cost, second: hole_number
        rep(hole_number, N){
            Direction direction = hole_vec[hole_number].get_target_direction(); 
            cand_pair_vec.push_back(P(direction.get_direction_size(), hole_number)); 
        }
        sort(all(cand_pair_vec)); 
        rep(pos_count, cand_pair_vec.size()){
            assert(cand_pair_vec.size() == N); 
            P cand_pair = cand_pair_vec[pos_count]; 
            ll hole_number = cand_pair.second;
            TournameResult tournament_result = tournament_middle(hole_number, pos_count); 
            if(tournament_result.state == State::SUCCESS) ans_vec[tournament_result.number] = hole_number; 
            if(tournament_result.state == State::SUCCESS) print("# SUCCESS", tournament_result.number); 
            if(tournament_result.state == State::FAILURE) print("# FAILURE");
            if(tournament_result.state == State::TIMEOUT) print("# TIMEOUT");
        }
    }


    // 回数の参考にするために今何番目かを引数に入れておく
    TournameResult tournament_middle(ll hole_number, ll pos_count){
        assert(DIFFICULTY == Difficulty::MIDDLE); 

        // 解の候補
        vector<ll> cand_entrance_number_vec; 
        rep(entrance_number, N){
            if(ans_vec[entrance_number] < 0) cand_entrance_number_vec.push_back(entrance_number); 
        }

        ll measure_count = 0; 
        vector<ld> estim_vec(N, 0); 
        for(ll entrance_number : cand_entrance_number_vec) estim_vec[entrance_number] = 1.0 / (ld)cand_entrance_number_vec.size(); 
        while(true){
            if(!can_continue_measure()) return TournameResult(-1, State::TIMEOUT);   // あとでargmaxに直しておく
            measure_count++;
            
            ll entrance_number = get_argmax(estim_vec);
            Result result = measure(entrance_number, hole_vec[hole_number].get_target_direction());
            ld estim = norm.query(result.measured_temp, TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 0); 
            estim_vec[entrance_number] *= estim; 

            // 正規化
            ld sum = get_sum(estim_vec); 
            vector<ld> next_estim_vec(N);
            rep(i, N) next_estim_vec[i] = estim_vec[i] / sum;  
            estim_vec = next_estim_vec; 

            ld max_estim = get_v_max(estim_vec); 
            if(max_estim >= 0.9999) return TournameResult(get_argmax(estim_vec), State::SUCCESS); 

            // 指定回数探索してもまともな答えが見つからない場合、どこかで間違えてしまっているので諦める
            // if(measure_count == MIDDLE_GIVE_UP_MEASURE_COUNT) return TournameResult(-1, State::FAILURE); 
            if(measure_count >= (N - pos_count + 1) * 1e4 / N) return TournameResult(get_argmax(estim_vec), State::SUCCESS);
        }
        assert(false); 
    }


    void solve_hard(){
        assert(DIFFICULTY == Difficulty::HARD); 

        set<ll> already_used_pattern_st; 
        rep(entrance_number, N){
            TournameResult tournament_result = tournament_hard(entrance_number, already_used_pattern_st); 
            if(tournament_result.state == State::SUCCESS){ 
                ans_vec[entrance_number] = tournament_result.number;   
                assigned_vec[tournament_result.number] = true; 
                ll pattern = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].get_pattern(tournament_result.number); 
                assert(bs(already_used_pattern_st, pattern) == false);
                already_used_pattern_st.insert(pattern);
            }
            if(tournament_result.state == State::SUCCESS) print("# SUCCESS", tournament_result.number); 
            if(tournament_result.state == State::FAILURE) print("# FAILURE");
            if(tournament_result.state == State::TIMEOUT) print("# TIMEOUT");
        }
    }


    TournameResult tournament_hard(ll entrance_number, set<ll>& already_used_pattern_st){
        vector<CellState> cell_state_vec(USE_NEIGHBOR_VEC_SIZE);
        rep(i, USE_NEIGHBOR_VEC_SIZE) cell_state_vec[i] = CellState::UNKNOWN; 
        rep(_, USE_NEIGHBOR_VEC_SIZE){
            ll target_index = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].think_best_index(cell_state_vec, already_used_pattern_st); 
            if(target_index >= 0){
                ld prob = 1.0;   // 山である確率
                ll COUNT = 28; 
                rep(i, COUNT){
                    if(true){
                        ld temp_prob = prob; 
                        frep(j, i, COUNT) temp_prob *= norm.query(0, TARGET_MOUNT_TEMP) / norm.query(0, 0);
                        if(temp_prob > 1.0) break; 

                        temp_prob = prob; 
                        frep(j, i, COUNT) temp_prob *= norm.query(1000, TARGET_MOUNT_TEMP) / norm.query(1000, 0);
                        if(temp_prob < 1.0) break; 
                    }
                    if(!can_continue_measure()) return TournameResult(-1, State::TIMEOUT); 
                    Result result = measure(entrance_number, NEIGHBOR_VEC[target_index][0], NEIGHBOR_VEC[target_index][1]);
                    prob *= norm.query(result.measured_temp, TARGET_MOUNT_TEMP) / norm.query(result.measured_temp, 0);
                    if(prob >= 10000 || prob * 10000 < 1) break; 
                } 
                if(prob > 1.0) cell_state_vec[target_index] = CellState::ONE;
                else cell_state_vec[target_index] = CellState::ZERO; 
            }
            ll hole_number = pattern_maker_list[USE_NEIGHBOR_VEC_SIZE].get_hole_number(cell_state_vec, already_used_pattern_st); 
            if(hole_number >= 0) return TournameResult(hole_number, State::SUCCESS); 
            else continue; 

            // エラーハンドリングがカス...
        } 
        assert(false);
    }

    
    Result measure(ll entrance_number, ll y, ll x){
        assert(-L < y && y < L && -L <= x && x < L); 
        assert(measure_count < MAX_MEASURE_COUNT); 
        measure_count++;

        // 移動の絶対値が小さいほうが得なので、出力用に向きを修正する
        ll output_y = y; 
        if(abs(y - L) < abs(y)) output_y = y - L; 
        ll output_x = x;
        if(abs(x - L) < abs(x)) output_x = x - L; 

        print(entrance_number, output_y, output_x); 
        ll measured_temp; 
        cin >> measured_temp; 
        return Result(y, x, measured_temp); 
    }
    Result measure(ll entrance_number, Direction direction){ return measure(entrance_number, direction.y, direction.x); }


    // 5sigmaに収まっているかを確認
    bool check_result(Result& result, ll hole_number){
        assert(DIFFICULTY == Difficulty::VERY_EASY || DIFFICULTY == Difficulty::EASY);
        ll target_mount_size = get_target_mount_size(hole_number); 
        return target_mount_size - 5 * SIGMA <= result.measured_temp && result.measured_temp < target_mount_size + 5 * SIGMA; 
    }


    // その他
    //==================================================================================================================
    bool can_continue_measure(){
        return measure_count < MAX_MEASURE_COUNT; 
    }

    ll get_target_mount_size(ll hole_number){
        return hole_vec[hole_number].target_mount.size; 
    }

    template<typename T> T get_v_max(vector<T>& v){
        T best = -INT_MAX; 
        for(auto x : v){
            if(x > best) best = x; 
        }
        return best; 
    }

    template<typename T> ll get_argmax(vector<T>& v){
        T best = -INT_MAX; 
        ll ret = -1; 
        ll size = v.size(); 
        rep(i, size){
            if(v[i] > best){
                best = v[i]; 
                ret = i; 
            }
        }
        assert(ret >= 0); 
        return ret; 
    }

    template<typename T> T get_sum(vector<T>& v){
        T ret = 0; 
        for(auto x : v) ret += x; 
        return ret; 
    }
    
    void print_temp_mat(){
        print_mat(temp_mat); 
    }

    void print_ans(){
        print(-1, -1, -1); 
        rep(i, N){ 
            if(ans_vec[i] < 0) print(0);  
            else print(ans_vec[i]);
        }   
    }

    void surrender(){
        rep(i, L){
            rep(i, L){
                cout << 1 << " ";
            }
            cout << endl;
        }
        print(-1, -1, -1); 
        rep(i, N) print(0); 
    }
}; 


void input(){
    cin >> L >> N >> SIGMA; 
    hole_vec.resize(N); 
    rep(i, N){
        ll y, x;
        cin >> y >> x; 
        hole_vec[i] = Hole(i, Place(y, x)); 
    }
}


void solve(){
    input(); 
    Solver solver;
    solver.solve(); 
}


int main(){
    solve(); 
}
