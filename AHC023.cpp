#include <bits/stdc++.h>
#define ll long long
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define irep(it, mp) for (auto it = mp.begin(); it != mp.end(); it++)
#define frep(i, k, n) for (ll i = (ll)k; i < (ll)(n); i++)
using namespace std;

// 二次元配列
using Mat = vector<vector<ll>>;
Mat init_mat(ll a, ll b){Mat ret(a, vector<ll>(b, 0)); return ret;}
Mat init_mat(ll a, ll b, ll c){Mat ret(a, vector<ll>(b, c)); return ret;}
using BMat = vector<vector<bool>>;
BMat init_bmat(ll a, ll b){BMat ret(a, vector<bool>(b, false)); return ret;}
BMat init_bmat(ll a, ll b, bool c){BMat ret(a, vector<bool>(b, c)); return ret;}

// 出力
void print(){cout << endl;}
template <class Head, class... Tail> void print(Head&& head, Tail&&... tail){cout << head << " "; print(std::forward<Tail>(tail)...);}
template<typename T> void vprint(vector<T>& v){for(T x : v) cout << x << " "; cout << endl;}

// 乱数生成
random_device rd;
mt19937 eng(0);
uniform_int_distribution<> randInt(0, INT_MAX);
uniform_real_distribution<> uniform(0.0, 1.0);

// 隣接関係
const ll neighbor_vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};


// ===================================================================================================================================================
// ===================================================================================================================================================


// 入力
ll n, m; 
Mat input_color_mat;

// 
BMat input_neighbor_color_bmat;   // 入力時の隣接色
clock_t START_TIME; 

const ll END_TIME = 1980000; 


class DisjointSet{
public:
    vector<ll> rank, p;
    DisjointSet(){}
    DisjointSet(ll size){rank.resize(size, 0); p.resize(size, 0); for(ll i=0; i<size; i++) makeSet(i);}
    void makeSet(ll x){p[x]=x; rank[x]=0;}
    bool same(ll x, ll y){return findSet(x) == findSet(y);}
    void unite(ll x, ll y){link(findSet(x), findSet(y));}
    void link(ll x, ll y){if(rank[x]>rank[y]) p[y]=x; else{p[x]=y; if(rank[x]==rank[y]) rank[y]++;}}
    ll findSet(ll x){if(x!=p[x]) p[x]=findSet(p[x]); return p[x];}
};


struct Place{
    ll y, x; 
    ll hash; 

    Place(){}
    Place(ll y_, ll x_) : y(y_), x(x_){
        hash = place_to_hash(); 
    }

    ll place_to_hash(){ return y * (n + 2) + x; }

    // operator
    bool operator > (const Place& another) const{return hash > another.hash;}
    bool operator < (const Place& another) const{return hash < another.hash;}
    bool operator == (const Place& another) const{return hash == another.hash;}
    bool operator != (const Place& another) const{return hash != another.hash;}
}; 
inline ll calc_distance(Place& p1, Place& p2){ return abs(p1.y - p2.y) + abs(p1.x - p2.x); }
inline bool is_neighbor(Place& p1, Place& p2){ return calc_distance(p1, p2) == 1; }


struct State{
    Mat color_mat;   // 各座標での色
    vector<set<Place>> color_place_graph;   // 各色の場所
    Mat neighbor_color_count_mat;   // 色i, jが何回隣接したか

    const ll NO_COLOR = INT_MAX;   // 出力するとWAになる色、del->addするときにNO_COLORを経由する

    State(){}

    void init(Mat& next_color_mat){
        assert(next_color_mat.size() > 0); 
        ll h = next_color_mat.size(); 
        ll w = next_color_mat[0].size(); 
        color_mat = init_mat(h, w, NO_COLOR); 
        color_place_graph.clear(); 
        color_place_graph.resize(m); 
        neighbor_color_count_mat = init_mat(m, m); 

        rep(i, h){
            rep(j, w){
                ll color = next_color_mat[i][j]; 
                assert(0 <= color && color < m); 
                add(Place(i, j), color); 
            }
        }
    }
    
    // 色を消す
    // 消された箇所は0でもない色となる
    void del(Place place){
        ll y = place.y; 
        ll x = place.x; 
        assert(is_inside(y, x)); 
        
        ll color = color_mat[y][x]; 
        assert(0 <= color && color < m); 

        // color_place_graph 
        auto it = color_place_graph[color].find(place); 
        assert(it != color_place_graph[color].end()); 
        color_place_graph[color].erase(it); 

        // neighbor_color_count
        rep(k, 4){
            ll dy = y + neighbor_vec[k][0]; 
            ll dx = x + neighbor_vec[k][1]; 
            if(is_inside(dy, dx) == false) continue; 
            else{
                ll neighbor_color = color_mat[dy][dx]; 
                if(neighbor_color == NO_COLOR) continue;
                if(color == neighbor_color) continue; 
                neighbor_color_count_mat[color][neighbor_color]--; 
                neighbor_color_count_mat[neighbor_color][color]--; 
                assert(neighbor_color_count_mat[color][neighbor_color] >= 0); 
                assert(neighbor_color_count_mat[neighbor_color][color] >= 0); 
            }
        }

        // color_mat
        color_mat[y][x] = NO_COLOR; 
    }

    // 色を塗る
    void add(Place place, ll color){
        ll y = place.y; 
        ll x = place.x; 
        assert(is_inside(y, x)); 

        ll prev_color = color_mat[y][x]; 
        assert(prev_color == NO_COLOR); 

        // color_place_graph
        color_place_graph[color].insert(place); 
        color_mat[y][x] = color;

        // neighbor_color_count_mat
        rep(k, 4){
            ll dy = y + neighbor_vec[k][0]; 
            ll dx = x + neighbor_vec[k][1]; 
            if(is_inside(dy, dx) == false) continue; 
            else{
                ll neighbor_color = color_mat[dy][dx]; 
                if(neighbor_color == NO_COLOR) continue;   
                if(color == neighbor_color) continue; 
                assert(neighbor_color_count_mat[color][neighbor_color] >= 0); 
                assert(neighbor_color_count_mat[neighbor_color][color] >= 0); 
                neighbor_color_count_mat[color][neighbor_color]++; 
                neighbor_color_count_mat[neighbor_color][color]++; 
            }
        } 
    }

    // 色を消して塗る
    // この結果がルールを満たしている保証はない
    void change(Place place, ll color){
        del(place); 
        add(place, color); 
    }

    // 条件を満たしているかを確認する
    // 確認するのはplace_vecの周囲
    // FIXME: 0の計算量が大きいので無視しても良いかも
    bool check(vector<Place>& place_vec){
        ll h = color_mat.size();
        ll w = color_mat[0].size(); 

        // 確認が必要な色の列挙
        set<ll> target_colot_st; 
        for(Place& place : place_vec){
            rep(k, 4){
                ll dy = place.y + neighbor_vec[k][0]; 
                ll dx = place.x + neighbor_vec[k][1]; 
                if(is_inside(dy, dx) == false) continue; 
                else{
                    ll color = color_mat[dy][dx]; 
                    target_colot_st.insert(color); 
                }
            }
        }

        // 同色内での連結
        irep(it, target_colot_st){
            ll color = *it; 

            // 非連結ならこれ以上の計算は無駄なのでreturnする
            if(is_unified(color) == false) return false; 
        }

        // 隣接色
        irep(it, target_colot_st){
            ll color = *it; 

            if(is_neighbor_color_ok(color) == false) return false; 
        }

        // ここまで来ればok
        return true; 
    }
    bool check(Place place){
        vector<Place> place_vec{place}; 
        return check(place_vec); 
    }

    // その色が連結であるかを確認
    // 計算量: O(K^2)
    bool is_unified(ll color){
        if(color == 0) return true; 
        vector<Place> place_vec; 
        irep(it, color_place_graph[color]) place_vec.push_back(*it); 
        
        // size==0もあり得ることに注意
        ll size = place_vec.size(); 
        DisjointSet ds(size); 

        // 隣接をDisjointSetで管理する
        rep(i, size){
            frep(j, i + 1, size){
                assert(place_vec[i] != place_vec[j]); 

                // 隣接している
                if(is_neighbor(place_vec[i], place_vec[j])){
                    ds.unite(i, j); 
                }
            }
        }

        // 親の種類が一つなら連結
        set<ll> parent_st; 
        rep(i, size) parent_st.insert(ds.findSet(i)); 
        return parent_st.size() == 1; 
    }

    // 隣接色が入力と一致しているかを確認する
    // 計算量: O(m)
    bool is_neighbor_color_ok(ll color){
        if(color == 0) return true; 
        rep(neighbor_color, m){
            assert(neighbor_color_count_mat[color][neighbor_color] == neighbor_color_count_mat[neighbor_color][color]); 

            bool neighbor = neighbor_color_count_mat[color][neighbor_color] >= 1;   // 今の状態では隣接しているか
            if(input_neighbor_color_bmat[color][neighbor_color] != neighbor) return false; 
        }

        // ここまで来ればok
        return true; 
    }

    bool is_inside(ll y, ll x){
        ll h = color_mat.size();
        ll w = color_mat[0].size(); 
        return (0 <= y && y < h && 0 <= x && x < w); 
    }
    bool is_inside(Place& place){ return is_inside(place.y, place.x); }

    ll get_h(){ return color_mat.size(); }
    ll get_w(){ return color_mat[0].size(); }
    ll get_color(ll y, ll x){
        assert(is_inside(y, x)); 
        return color_mat[y][x]; 
    }
    ll get_color(Place& place){ return get_color(place.y, place.x); }
}; 


struct Solver{
    State state; 

    Solver(){ init(); }

    void init(){
        state.init(input_color_mat); 
    }

    void solve(){
        // first
        // 一行ずつ消す
        // 一周する毎にlevel()を実行し、更新が入らなかったら終了
        bool first_process_update = true; 
        while(first_process_update){
            first_process_update = false; 

            level(); 

            ll pos_y = 0; 
            while(pos_y < state.get_h()){
                bool result = erase_yoko(pos_y); 
                if(result == false) pos_y++; 
                else first_process_update = true; 
            }

            ll pos_x = 0; 
            while(pos_x < state.get_w()){
                bool result = erase_tate(pos_x); 
                if(result == false) pos_x++; 
                else first_process_update = true; 
            }
        }

        // second
        // 色を隣色に変える遷移をいれて、一行ずつ消す
        // ただし、色0は一行ずつ消すとき以外では発生しない
        while(clock() - START_TIME <= END_TIME / 2){
            change_random(); 
            level(); 

            ll pos_y = 0; 
            while(pos_y < state.get_h()){
                bool result = erase_yoko(pos_y); 
                if(result == false) pos_y++; 
                else first_process_update = true; 
            }

            ll pos_x = 0; 
            while(pos_x < state.get_w()){
                bool result = erase_tate(pos_x); 
                if(result == false) pos_x++; 
                else first_process_update = true; 
            }
        }

        // third
        // 色をランダムに変えて、0が多くなるようにする
        while(clock() - START_TIME <= END_TIME){
            transition_random();
        }
    }

    // y行目を削除する
    // 削除に成功したらtrue
    bool erase_yoko(ll y){
        ll h = state.get_h(); 
        ll w = state.get_w(); 

        assert(0 <= y && y < h); 
        if(y == 0 || y == h - 1) return false; 

        vector<Place> erase_place_vec;   // 今回消した座標
        map<ll, ll> prev_color_mp;  // key: x, value: color
        rep(x, w){
            Place place(y, x); 
            erase_place_vec.push_back(place); 
            prev_color_mp[x] = state.get_color(place); 

            // 一列消して詰めるという処理は計算が重いので、下の色に変えるという処理をする
            // これをしてもルールを満たしてるかどうかは変わらない
            ll after_color = state.get_color(y + 1, x); 
            state.change(place, after_color); 
        }

        if(state.check(erase_place_vec)){
            // ルールを満たしている
            // stateを正しいcolor_matに置き換える
            Mat next_color_mat = init_mat(h - 1, w); 
            rep(i, h){
                rep(j, w){
                    if(i < y) next_color_mat[i][j] = state.get_color(i, j); 
                    else if(i == y) continue; 
                    else next_color_mat[i - 1][j] = state.get_color(i, j);  
                }
            }

            state.init(next_color_mat); 
            return true; 
        }
        else{
            // ルールを満たしていないので元に戻す
            irep(it, prev_color_mp){
                ll x = it->first; 
                ll color = it->second; 
                state.change(Place(y, x), color); 
            }

            return false;
        }
    }

    // x行目を削除する
    // 削除に成功したらtrue
    bool erase_tate(ll x){
        ll h = state.get_h(); 
        ll w = state.get_w(); 

        assert(0 <= x && x < w); 
        if(x == 0 || x == w - 1) return false; 

        vector<Place> erase_place_vec;   // 今回消した座標
        map<ll, ll> prev_color_mp;  // key: y, value: color
        rep(y, h){
            Place place(y, x); 
            erase_place_vec.push_back(place); 
            prev_color_mp[y] = state.get_color(place); 

            // 一行消して詰めるという処理は計算が重いので、右の色に変えるという処理をする
            // これをしてもルールを満たしてるかどうかは変わらない
            ll after_color = state.get_color(y, x + 1); 
            state.change(place, after_color); 
        }

        if(state.check(erase_place_vec)){
            // ルールを満たしている
            // stateを正しいcolor_matに置き換える
            Mat next_color_mat = init_mat(h, w - 1); 
            rep(i, h){
                rep(j, w){
                    if(j < x) next_color_mat[i][j] = state.get_color(i, j); 
                    else if(j == x) continue; 
                    else next_color_mat[i][j - 1] = state.get_color(i, j);  
                }
            }

            state.init(next_color_mat); 
            return true; 
        }
        else{
            // ルールを満たしていないので元に戻す
            irep(it, prev_color_mp){
                ll y = it->first; 
                ll color = it->second; 
                state.change(Place(y, x), color); 
            }

            return false;
        }
    }


    // 色を変える山登り
    void transition_random(){
        ll h = state.get_h();
        ll w = state.get_w(); 

        ll y = randInt(eng) % h; 
        ll x = randInt(eng) % w; 
        ll my_color = state.get_color(y, x); 
        if(my_color == 0) return; 

        ll k = randInt(eng) % 4; 
        ll dy = y + neighbor_vec[k][0]; 
        ll dx = x + neighbor_vec[k][1]; 
        ll next_color = state.get_color(dy, dx); 

        if(my_color == next_color) return; 

        state.change(Place(y, x), next_color); 

        if(state.check(Place(y, x))){
            // 
        }
        else{
            state.change(Place(y, x), my_color); 
        }
    }


    // 三方を同じ色に囲まれているセルの色を、囲んでいる色に変える
    // 自分の色が1マスしかないときは、この処理を行えない
    // この方法は変更後にルールを守っているかの確認が不要
    void level(){
        ll h = state.get_h(); 
        ll w = state.get_w(); 

        // 周囲は0のマスなので関係ない
        frep(i, 1, h - 1){
            frep(j, 1, w - 1){
                ll my_color = state.get_color(i, j); 
                map<ll, ll> color_count_mp;   // 隣接色の数を数える
                rep(k, 4){
                    ll dy = i + neighbor_vec[k][0]; 
                    ll dx = j + neighbor_vec[k][1]; 
                    if(state.is_inside(dy, dx) == false) continue;   // あり得ないが一応
                    ll neighbor_color = state.get_color(dy, dx); 
                    color_count_mp[neighbor_color]++; 
                }

                // 条件に合致するか
                // 自分が1個、他色が3個であればok
                if(color_count_mp.size() != 2) continue; 
                if(color_count_mp[my_color] != 1) continue; 
                ll you_color; 
                irep(it, color_count_mp){
                    if(it->first != my_color) you_color = it->first;  
                }
                if(color_count_mp[you_color] != 3) continue; 

                // ここまで来れば条件を満たす
                state.change(Place(i, j), you_color); 
            }
        }
    }


    // 自分の色をランダムに隣の色にする
    void change_random(){
        const ll RATIO = 3;   // RATIO回に1回色を変える

        ll h = state.get_h(); 
        ll w = state.get_w(); 
        frep(i, 1, h - 1){
            frep(j, 1, w - 1){
                double prob = uniform(eng); 
                if(prob >= 1.0 / (double)RATIO) continue; 

                Place target_place(i, j);  
                ll prev_color = state.get_color(i, j); 

                // 次の色を決める
                // ただし、0と自色は許さない
                ll k = randInt(eng) % 4; 
                ll dy = i + neighbor_vec[k][0]; 
                ll dx = j + neighbor_vec[k][1]; 
                if(state.is_inside(dy, dx) == false) continue; 
                ll next_color = state.get_color(dy, dx); 
                if(next_color == 0) continue; 
                if(next_color == prev_color) continue; 

                // 色を変えてみる
                state.change(target_place, next_color); 

                // ルールを守っているか
                if(state.check(target_place)){
                    // ルールを守っているならそのまま
                }
                else{
                    // 巻き戻す
                    state.change(target_place, prev_color); 
                }
            }
        }
    }

    void print_ans(){
        ll h = state.get_h(); 
        ll w = state.get_w(); 
        frep(i, 1, n - 1){
            frep(j, 1, n - 1){
                if(i >= h || j >= w) cout << 0 << " "; 
                else cout << state.get_color(i, j) << " "; 
            }
            cout << endl;
        }
    }
}; 


void input(){
    START_TIME = clock(); 

    cin >> n >> m;
    m++;   // 0を考えておく
    n += 2;   // 周囲1マスは0で塗られていると認識

    input_color_mat = init_mat(n, n, 0); 
    frep(i, 1, n - 1){
        frep(j, 1, n - 1){
            cin >> input_color_mat[i][j];
        }
    }

    // 初期隣接色
    input_neighbor_color_bmat = init_bmat(m, m, false); 
    rep(i, n){
        rep(j, n){
            rep(k, 4){
                ll dy = i + neighbor_vec[k][0]; 
                ll dx = j + neighbor_vec[k][1]; 
                if(0 <= dy && dy < n && 0 <= dx && dx < n){
                    ll color_1 = input_color_mat[i][j]; 
                    ll color_2 = input_color_mat[dy][dx]; 
                    if(color_1 == color_2) continue;
                    input_neighbor_color_bmat[color_1][color_2] = true; 
                    input_neighbor_color_bmat[color_2][color_1] = true; 
                }
            }
        }
    }
}


int main(){
    input(); 
    Solver solver; 
    solver.solve(); 
    solver.print_ans();
}
