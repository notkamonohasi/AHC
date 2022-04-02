//バグるのでいったん前のバージョン
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
#include <queue>
#include <math.h>
#include <bitset>
#include <map>
#include <vector>
#include <cstdio>
#include <climits>
#include <set>
#include <random>
#include <time.h>
#define ll long long
#define ld long double
#define N 16
#define M 5000
#define T 1000
using namespace std;

const ll INF = LLONG_MAX;
//cout << fixed << setprecision(10) << ans << endl;
pair<ll, ll> vec[4] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
pair<ll, ll> all_vec[8] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1), 
        make_pair(1, 1), make_pair(-1, 1), make_pair(1, -1), make_pair(-1, -1)};
pair<ll, ll> vec0[1] = {make_pair(0, 0)};
pair<ll, ll> vec1[4] = {make_pair(1, 0), make_pair(0, 1), make_pair(-1, 0), make_pair(0, -1)};
pair<ll, ll> vec2[8] = {make_pair(2, 0), make_pair(1, 1), make_pair(0, 2), make_pair(-2, 0), make_pair(-1, 1), 
        make_pair(1, -1), make_pair(-1, -1), make_pair(0, -2)};
pair<ll, ll> vec3[12] = {make_pair(3, 0), make_pair(2, 1), make_pair(1, 2), make_pair(0, 3), 
        make_pair(-3, 0), make_pair(-2, 1), make_pair(2, -1), make_pair(-2, -1), 
        make_pair(-1, 2), make_pair(1, -2), make_pair(-1, -2), make_pair(0, -3)};
random_device seed_gen;
mt19937 engine(seed_gen());
uniform_real_distribution<> dist(0.1, 0.2);
uniform_real_distribution<> dist2(0.0, 1.0);

ll sum = 0;

//パラメータ 有効範囲は基本的に-1
ll beamsearch_width = 3;
ll future_width = 10;
ll num_selected_place = 4;   //最終的には必要なくね？
ll num_selected_neighbor_place = 2;
ld discount_rate = 0.5;
ll heatmap_depth = 4;
ll max_selected_vec_size = 4;
ll min_selected_vec_size = 2;
ll not_buy_track_time = 850;
ld P1 = 100.0;      //現金とトラック
ld P2 = 1.0;   //連続
ld P3 = 100.0;       //周り
ld P4 = P1;       //heatmap

//入力
ll n, m, t;
ll veget_data[M][5];

//時間計測
clock_t start_time = 0;
clock_t before_time = 0;
clock_t now_time = 0;

class Place{
public : 
    ll x;
    ll y;
    
    Place(ll a, ll b){
        x = a;
        y = b;
    }
    
    //先に宣言だけしておきたい時用
    Place(){}
    
    void print(){
        cout << x << " " << y << "   ";
    }
};

class Veget{
public : 
    ll x;
    ll y;
    ll start;
    ll end;
    ll val;
    
    Veget(ll a, ll b, ll c, ll d, ll e){
        x = a;
        y = b;
        start = c;
        end = d;
        val = e;
    }
    
    void print(){
        cout << x << " " << y << " " << start << " " << end << " " << val << endl;;
    }
};

class Opera{
public : 
    ll type;
    vector<ll> opera_vec;
    
    Opera(ll a, vector<ll> b){
        type = a;
        for(ll p : b) opera_vec.push_back(p);
    }
    
    void print(){
        for(ll k = 0; k < opera_vec.size(); k++){
            if(k != opera_vec.size() - 1) cout << opera_vec[k] << " ";
            else cout << opera_vec[k];
        }
        cout << endl;
    }
};

class Money_and_veget_vec{
public : 
    ll money;
    vector<Veget> veget_vec;
    
    Money_and_veget_vec(ll a, vector<Veget> b){
        money = a;
        for(Veget p : b) veget_vec.push_back(p);
    }
    
    void print(){
        cout << "money : " << money << endl;
        for(Veget veget : veget_vec) veget.print();
    }
};

class Class_for_bfs{
public : 
    vector<Place> track_vec;
    vector<Veget> veget_vec;
    vector<Opera> opera_vec;
    ll money;
    ld score;
    
    Class_for_bfs(){}   //とりあえず宣言だけしておきたい時用
    
    Class_for_bfs(vector<Place> a, vector<Veget> b, vector<Opera> c, ll d, ll e){   
        for(auto x : a) track_vec.push_back(x);
        for(auto x : b) veget_vec.push_back(x);
        for(auto x : c) opera_vec.push_back(x);
        money = d;
        score = e;
    }
    
    vector<Place> return_track_vec(){
        vector<Place> ret;
        for(auto x : track_vec) ret.push_back(x);
        return ret;
    }
    
    vector<Veget> return_veget_vec(){
        vector<Veget> ret;
        for(auto x : veget_vec) ret.push_back(x);
        return ret;
    }
    
    vector<Opera> return_opera_vec(){
        vector<Opera> ret;
        for(auto x : opera_vec) ret.push_back(x);
        return ret;
    } 
    
    void make_opera_vec_empty(){
        opera_vec = {};
    }
};

class Depth_and_place{
public : 
    ll depth;
    Place place;

    Depth_and_place(ll a, Place b){
        depth = a;
        place = b;
    }
};

bool judge_in_field(ll x, ll y){
    if(x < 0 || x >= n) return false;
    if(y < 0 || y >= n) return false;
    return true;
}

//引き値をtrack_vec_vecにすれば計算量を改善できる
Money_and_veget_vec calculate_after_operataion(vector<Place> track_vec, vector<Veget> veget_vec){
    //return 
    ll money = 0;
    vector<Veget> next_veget_vec;

    //bfsで何個収穫機がつながっているかを探していく
    //track_field作成
    bool track_field[n][n];
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            track_field[i][j] = false;
        }
    }
    for(Place track : track_vec) track_field[track.x][track.y] = true;
    //track_field作成終了
    
    //veget毎にbfsを行う
    for(Veget veget : veget_vec){
        //時間の節約、これがfalseなら後の操作は無駄
        if(track_field[veget.x][veget.y] == false){
            next_veget_vec.push_back(veget);
            continue;
        }

        //初期設定
        queue<Place> bfs_que;
        ll num_track = 0;
        Place first_bfs_place = Place(veget.x, veget.y);
        bfs_que.push(first_bfs_place);
        bool not_seen_place[n][n];
        for(ll i = 0; i < n; i++){
            for(ll j = 0; j < n; j++){
                not_seen_place[i][j] = true;
            }
        }
        not_seen_place[veget.x][veget.y] = false;
        //初期設定終了
        
        //bfs開始
        while(bfs_que.empty() == false){
            Place target_place = bfs_que.front();
            bfs_que.pop();
            ll x = target_place.x;
            ll y = target_place.y;
            if(track_field[x][y] == true){
                num_track++;
                for(ll k = 0; k < 4; k++){
                    ll dx = x + vec[k].first;
                    ll dy = y + vec[k].second;
                    if(judge_in_field(dx, dy) == false) continue;
                    if(not_seen_place[dx][dy] == false) continue;
                    not_seen_place[dx][dy] = false;
                    Place next_bfs_place = Place(dx, dy);
                    bfs_que.push(next_bfs_place);
                }
            }
        }
        //bfs終了
    
        money += veget.val * num_track;
    }
    
    //返り値用classの作成
    Money_and_veget_vec ret(money, next_veget_vec);
    
    return ret;
}

vector<vector<Place>> search_continuous_track(vector<Place> track_vec){
    vector<vector<Place>> ret;   //これを返り値にする
    bool track_field[n][n], not_seen_field[n][n];
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            track_field[i][j] = false;
            not_seen_field[i][j] = false;   //とりあえず最初はfalseにして、収穫機があるところだけtrueにする
        }
    }
    for(Place track : track_vec){ 
        track_field[track.x][track.y] = true;
        not_seen_field[track.x][track.y] = true;
    }
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            if(track_field[i][j] == false) continue;
            if(not_seen_field[i][j] == false) continue;
            
            queue<Place> search_queue;
            vector<Place> continuous_track_vec;   //retの中身
            Place first_place(i, j);
            search_queue.push(first_place);
            continuous_track_vec.push_back(first_place);
            not_seen_field[i][j] = false;

            //bfs開始
            while(search_queue.empty() == false){
                Place place = search_queue.front();
                search_queue.pop();
                for(ll k = 0; k < 4; k++){
                    ll dx = place.x + vec[k].first;
                    ll dy = place.y + vec[k].second;
                    if(judge_in_field(dx, dy) == false) continue;
                    if(not_seen_field[dx][dy] == false) continue;

                    not_seen_field[dx][dy] = false;
                    Place next_place(dx, dy);
                    search_queue.push(next_place);
                    continuous_track_vec.push_back(next_place);
                }
            }
            //bfs終了

            ret.push_back(continuous_track_vec);
        }
    }

    return ret;
}

ll judge_where_space(Place place){
    //1なら四隅、2なら辺中央、3なら真ん中
    if(place.x == 0 || place.x == n - 1){
        if(place.y == 0 || place.y == n - 1) return 1;
        else return 2;
    }
    else{
        if(place.y == 0 || place.y == n - 1) return 2;
        else return 3;
    }
}

vector<ll> count_around_space(vector<vector<Place>> track_vec_vec){
    vector<ll> ret;
    for(vector<Place> track_vec : track_vec_vec){
        //count開始
        //計算量を少なくするために一部ハードコーディング
        if(track_vec.size() == 1) ret.push_back(judge_where_space(track_vec[0]));
        else if(track_vec.size() == 2){
            Place track1 = track_vec[0];
            Place track2 = track_vec[1];
            ll criterion = judge_where_space(track1) * judge_where_space(track2);
            if(criterion == 2) ret.push_back(3);
            else if(criterion == 6) ret.push_back(5);
            else if(criterion == 9) ret.push_back(6);
            //else ret.push_back(4);   //<-ありえないけど一応入れておく
        }
        else{
            bool not_seen_field[n][n];
            ll continuous_count = 0;
            //初期化しなくていい可能性あり、危険だからやらないけど
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    not_seen_field[i][j] = true;
                }
            }
            for(Place track : track_vec){
                for(ll k = 0; k < 4; k++){
                    ll dx = track.x + vec[k].first;
                    ll dy = track.y + vec[k].second;
                    if(judge_in_field(dx, dy) == false) continue;
                    if(not_seen_field[dx][dy] == true){
                        not_seen_field[dx][dy] = false;
                        continuous_count++;
                    }
                }
            }
            //count終了

            ret.push_back(continuous_count);
        }
    }

    return ret;
}

ld calculate_heatmap_score(vector<vector<Place>> track_vec_vec, ld heatmap[N][N]){
    ld score = 0;
    ll continuous_track_field[n][n];
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            continuous_track_field[i][j] = 0;
        }
    }
    for(vector<Place> track_vec : track_vec_vec){
        ll track_vec_size = track_vec.size();
        for(Place track : track_vec){
            continuous_track_field[track.x][track.y] = track_vec_size;
        }
    }
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            score += heatmap[i][j] * continuous_track_field[i][j];
        }
    }

    return score;
}

//ターン毎に変える可能性あり、900ターン以降は0など
ld calculate_score_track_num(ll track_num, ll pos_depth){
    //track_num >= 7 で価値が逆転する
    if(pos_depth <= not_buy_track_time){ 
        ld basic_score = 6 * pow(track_num + 1, 2); 
        return basic_score * 10000;
    }
    else return -10.0 * pow(track_num + 1, 6);
}

ld calculate_score_continuous_track(vector<vector<Place>> track_vec_vec){
    ld score = 0.0;
    for(vector<Place> track_vec : track_vec_vec){
        ll track_vec_size = track_vec.size();
        score += pow(track_vec_size, 3);
    }
    
    return score;
}

ld calculate_score_around_space(vector<vector<Place>> track_vec_vec){
    ld score = 0.0;
    vector<ll> num_around_space_vec = count_around_space(track_vec_vec);
    for(ll k = 0; k < num_around_space_vec.size(); k++){
        ld basic_score = num_around_space_vec[k];
        score += pow(basic_score, 3);
    }
    return score;
}

ll calculate_score(vector<Place> track_vec, ll money, ld heatmap[N][N], ll pos_depth){
    vector<vector<Place>> track_vec_vec = search_continuous_track(track_vec);
    ld score_track_num = calculate_score_track_num(track_vec.size(), pos_depth);
    ld score_continuous_track = calculate_score_continuous_track(track_vec_vec);
    ld score_around_space = calculate_score_around_space(track_vec_vec);
    ld heatmap_score = calculate_heatmap_score(track_vec_vec, heatmap);

    ld total_score = P1 * (money + score_track_num) + P2 * score_continuous_track + 
            P3 * score_around_space + P4 * heatmap_score + dist(engine);
    total_score *= 100.0;
    ll final_score = total_score;   //ld -> ll 小数をそのまま扱うのは挙動が不穏すぎる
    return final_score;
}

vector<Place> return_edge_track(vector<Place> first_track_vec, ld heatmap[N][N]){
    vector<vector<Place>> track_vec_vec = search_continuous_track(first_track_vec);
    bool track_field[n][n];
    vector<Place> ret, potential_selected_track_vec, not_selected_track_vec;
    
    //potential_selected_track_vec, notの作成
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            track_field[i][j] = false;
        }
    }
    for(Place track : first_track_vec) track_field[track.x][track.y] = true;
    for(Place track : first_track_vec){
        ll num_track = 0;
        for(ll k = 0; k < 4; k++){
            ll dx = track.x + vec[k].first;
            ll dy = track.y + vec[k].second;
            if(judge_in_field(dx, dy) == false) continue;
            if(track_field[dx][dy] == true) num_track++;
        }
        if(num_track == 0 || num_track == 1) ret.push_back(track);
        else if(num_track == 2) not_selected_track_vec.push_back(track);
        else potential_selected_track_vec.push_back(track);
    }
    
    //potentialから外しても問題ないのを探す
    for(vector<Place> track_vec : track_vec_vec){
        for(Place track : track_vec){
            //potentialにあるかどうか判断
            bool point = false;
            for(Place potential_track : potential_selected_track_vec){
                if(track.x == potential_track.x && track.y == potential_track.y) point = true;
            }
            if(point == false) continue;   //potentialにないなら終わり
            
            //何個つながるか
            Place first_track;
            for(ll k = 0; k < 4; k++){
                ll dx = track.x + vec[k].first;
                ll dy = track.y + vec[k].second;
                if(judge_in_field(dx, dy) == false) continue;
                if(track_field[dx][dy] == true){
                    first_track = Place(dx, dy);
                    break;
                }
            }
            
            queue<Place> bfs_que;
            ll num_track = 1;
            bool not_seen_field[n][n];
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    not_seen_field[i][j] = true;
                }
            }
            not_seen_field[first_track.x][first_track.y] = false;
            track_field[track.x][track.y] = false;   //対象の位置を変えるので、ここは収穫機をないことにする
            bfs_que.push(first_track);
            
            while(bfs_que.empty() == false){
                Place bfs_track = bfs_que.front();
                bfs_que.pop();
                for(ll k = 0; k < 4; k++){
                    ll dx = bfs_track.x + vec[k].first;
                    ll dy = bfs_track.y + vec[k].second;
                    if(judge_in_field(dx, dy) == false) continue;
                    if(not_seen_field[dx][dy] == false) continue;
                    if(track_field[dx][dy] == true){
                        not_seen_field[dx][dy] = false;
                        Place next_place(dx, dy);
                        bfs_que.push(next_place);
                        num_track++;
                    }
                }
            }
            if(track_vec.size() == num_track + 1) ret.push_back(track);
            track_field[track.x][track.y] = true;   //もとに戻しておく
        }
    }
    
    ll new_min_selected_vec_size;   //selectedに最低でも入れる数
    if(min_selected_vec_size >= first_track_vec.size()) new_min_selected_vec_size = first_track_vec.size();   //そもそも収穫機の数が少ないなら仕方ない...
    else new_min_selected_vec_size = min_selected_vec_size;
    
    if(new_min_selected_vec_size <= ret.size() && ret.size() <= max_selected_vec_size) return ret;
    else{    //このままでは返り値のsizeが小さすぎる、または大きすぎるとき
        vector<vector<Place>> track_vec_vec = search_continuous_track(first_track_vec);
        ll num_track_field[n][n], track_heatmap_field[n][n];   //llにしておきます
        vector<ll> score_vec;
        vector<Place> new_ret;    //このケースはこれを返り値にする
        for(ll i = 0; i < n; i++){
            for(ll j = 0; j < n; j++){
                num_track_field[i][j] = 0;
            }
        }
        for(vector<Place> track_vec : track_vec_vec){
            ll track_vec_size = track_vec.size();
            for(Place track : track_vec) num_track_field[track.x][track.y] = track_vec_size;
        }
        for(Place place : first_track_vec){
            ll x = place.x;
            ll y = place.y;
            track_heatmap_field[x][y] = (heatmap[x][y] * num_track_field[x][y] + dist(engine)) * 1000;
        }
        
        ll necessary_score;
        
        if(ret.size() > max_selected_vec_size){  //retが多すぎだった場合
            for(Place track : ret) score_vec.push_back(track_heatmap_field[track.x][track.y]);
            sort(score_vec.begin(), score_vec.end());
            necessary_score = score_vec[max_selected_vec_size - 1];   //-1しないと一つ大きくとっちゃうので
            for(Place track : ret){
                if(track_heatmap_field[track.x][track.y] <= necessary_score) new_ret.push_back(track);   //今回は珍しく"<"です
            }
        }
        else{   //retが少なすぎだった場合
            vector<Place> target_track_vec;   //track_vecからretを除いた
            for(Place track : first_track_vec){
                bool not_duplicate = true;   //trackがretに含まれているか
                for(Place ret_track : ret){
                    if(track.x == ret_track.x || track.y == ret_track.y) not_duplicate = false;
                }
                if(not_duplicate == true) target_track_vec.push_back(track);
            }
            for(Place track : ret) new_ret.push_back(track);
            for(Place track : target_track_vec) score_vec.push_back(track_heatmap_field[track.x][track.y]);
            sort(score_vec.begin(), score_vec.end());
            necessary_score = score_vec[min_selected_vec_size - new_ret.size() - 1];   //-1しないと一つ大きくとっちゃうので
            for(Place place : target_track_vec){
                if(track_heatmap_field[place.x][place.y] <= necessary_score) new_ret.push_back(place);   //今回は珍しく"<"です
            }
        }
        
        return new_ret;
    }
}

vector<Place> return_not_edge_track(vector<Place> track_vec, vector<Place> selected_track_vec){
    vector<Place> ret;
    bool selected_track_field[n][n];
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            selected_track_field[i][j] = false;
        }
    }
    for(Place track : selected_track_vec) selected_track_field[track.x][track.y] = true;
    for(Place track : track_vec){   
        if(selected_track_field[track.x][track.y] == false) ret.push_back(track);    //selectedに入ってないやつを全部入れるという発想です
    }
    
    return ret;
}

vector<Place> select_neighbor_cluster_place(vector<Place> first_track_vec, ld heatmap[N][N]){   //後でtrack_vecを使いたいので名前は変えときます
    vector<vector<Place>> track_vec_vec = search_continuous_track(first_track_vec);
    ll track_field[n][n];
    ll on_track_field[n][n];   //すでに収穫機があるか
    ll track_heatmap_field[n][n];
    vector<ll> score_vec;
    vector<Place> selected_place_vec;
    
    //on_track_fieldの作成
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            on_track_field[i][j] = false;
        }
    }
    for(vector<Place> track_vec : track_vec_vec){
        for(Place track : track_vec) on_track_field[track.x][track.y] = true;
    }
    
    //クラスターの隣のマスを探す
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            track_field[i][j] = 0;
        }
    }
    for(vector<Place> track_vec : track_vec_vec){
        ll track_vec_size = track_vec.size();
        for(Place track : track_vec){
            for(ll k = 0; k < 4; k++){
                ll dx = track.x + vec[k].first;
                ll dy = track.y + vec[k].second;
                if(judge_in_field(dx, dy) == false) continue;
                if(track_field[dx][dy] < track_vec_size) track_field[dx][dy] = track_vec_size;
            }
        }
    }
    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            track_heatmap_field[i][j] = (heatmap[i][j] * track_field[i][j] + dist(engine)) * 10000;
            if(on_track_field[i][j] == true) track_heatmap_field[i][j] = dist(engine) * 10000;   //トラックがある場所においても仕方ない
            score_vec.push_back(track_heatmap_field[i][j]);
        }
    }

    sort(score_vec.begin(), score_vec.end());
    reverse(score_vec.begin(), score_vec.end());
    ld necessary_score = score_vec[num_selected_neighbor_place];

    for(ll i = 0; i < n; i++){
        for(ll j = 0; j < n; j++){
            if(track_heatmap_field[i][j] >= necessary_score){
                Place selected_place(i, j);
                selected_place_vec.push_back(selected_place);
            }
        }
    }

    return selected_place_vec;
}

ld distribute_time(ll pos_depth){
    ll phase = pos_depth / 100;
    switch(phase){
        case 0 : 
            return 0.06;
        case 1 : 
            return 0.07;
        case 2 : 
            return 0.09;
        case 3 : 
            return 0.10;
        case 4 : 
            return 0.11;
        case 5 : 
            return 0.12;
        case 6 : 
            return 0.12;
        case 7 : 
            return 0.12;
        case 8 : 
            return 0.10;
        case 9 : 
            return 0.10;
        default :     //ありえないけど一応ね
            return 0.10;
    }
}

clock_t return_target_time(ll pos_depth){    //軽く時間調整
    clock_t target_time;
    if(pos_depth >= 900) target_time = 1825000;
    else if(pos_depth >= 800) target_time = 1800000;
    else target_time = 1775000;

    return target_time;
}

clock_t calculate_usable_time(clock_t now_time, ll pos_depth){
    ld sum_usable_time_weight = 0;
    for(ll time = pos_depth; time < 1000; time++){
        sum_usable_time_weight += (distribute_time(time) / 100);
    }
    ld usable_time_weight = distribute_time(pos_depth) / (20 * sum_usable_time_weight);   //5ターンで使える時間
    clock_t ret = (return_target_time(pos_depth) - now_time) * usable_time_weight;

    return ret;
}

void adjust_parameters(clock_t before_time, clock_t now_time, ll pos_depth){
    //計算時間に関係するパラメータの調整, 5ターン毎に調整を行う(1ターン毎だとノイズの影響が大きすぎる)
    //序盤は打てる種類が少なく、終盤はもはや貪欲でいいので、中盤に計算リソースを集中させる
    //計算時間は1.8秒となる様に調整する
    //950ターン目以降は調整しない
    if(pos_depth % 5 != 0 || pos_depth > 970 || pos_depth == 0) return;
    clock_t usable_time = calculate_usable_time(now_time, pos_depth);
    clock_t used_time = now_time - before_time;   //5ターンの間に使った時間

    if(used_time < usable_time * 0.95){    //計算時間が予定より少ない
        if(dist2(engine) > 0.5) beamsearch_width++;
        else max_selected_vec_size++;
    }
    
    if(used_time > usable_time * 1.05){
        if(dist2(engine) > 0.5) beamsearch_width--;
        else max_selected_vec_size--;   //計算時間が予定より少ない
        if(beamsearch_width <= 2){   //減りすぎは困るため
            beamsearch_width++;
            if(max_selected_vec_size > min_selected_vec_size) max_selected_vec_size--;
        }
        if(max_selected_vec_size < min_selected_vec_size){
            max_selected_vec_size++;
            if(beamsearch_width > 2) beamsearch_width--;
        }
    }
    
    //時間に関係ないパラメータ
    if(pos_depth >= not_buy_track_time) P1 = 1000.0;
    P4 = P1;
    if(num_selected_place >= 1){
        if(pos_depth % 100 == 0) num_selected_place--;
    }
}

void BFS_and_beamserch(){
    //初期設定
    ll pos_depth = 0;
    vector<Place> first_track_vec; 
    vector<Veget> first_veget_vec;
    vector<Opera> first_opera_vec;
    Class_for_bfs first_class_for_bfs(first_track_vec, first_veget_vec, first_opera_vec, 1, 0);
    queue<Class_for_bfs> bfs_que;
    bfs_que.push(first_class_for_bfs);
    //初期設定終了

    //ヒートマップ作成
    ld first_heatmap[t][n][n];
    for(ll i = 0; i < m; i++){
        ll first_x = veget_data[i][0];
        ll first_y = veget_data[i][1];
        ll start = veget_data[i][2];
        //ll end = veget_data[i][3];   //<-使わない
        ll val = veget_data[i][4];
        
        //bfsで隣接しているマスを探していく
        //初期設定
        queue<Depth_and_place> bfs_que;
        bool not_seen_place[n][n];
        Place first_place(first_x, first_y);
        Depth_and_place first_depth_and_place(0, first_place);
        bfs_que.push(first_depth_and_place);
        for(ll i = 0; i < n; i++){
            for(ll j = 0; j < n; j++){
                not_seen_place[i][j] = true;
            }
        }
        not_seen_place[first_x][first_y] = false;
        //初期設定完了

        //ヒートマップbfs開始
        while(bfs_que.empty() == false){
            Depth_and_place target = bfs_que.front();
            bfs_que.pop();
            Place target_place = target.place;
            ll x = target_place.x;
            ll y = target_place.y;
            for(ll k = 1; k <= heatmap_depth; k++){
                if(start - k < 0) continue;
                first_heatmap[start - k][x][y] += val * pow(discount_rate, target.depth) *
                        ((1 / (heatmap_depth + 1)) * (heatmap_depth - k + 1));
            }

            for(ll k = 0; k < 4; k++){
                ll dx = x + vec[k].first;
                ll dy = y + vec[k].second;
                if(judge_in_field(dx, dy) == false) continue;
                if(not_seen_place[dx][dy] == false) continue;
                if(target.depth == heatmap_depth){   //これ以上は深く潜らない
                    not_seen_place[dx][dy] = false;
                    Place next_place(dx, dy);
                    Depth_and_place next_target(target.depth + 1, next_place);
                    bfs_que.push(next_target);
                }
            }
        }
        //ヒートマップbfs終了
    }
    //ヒートマップの作成終了

    //bfs開始
    while(pos_depth != t){
        
        //cout << pos_depth << endl;
        
        queue<Class_for_bfs> next_bfs_que;
        vector<ld> score_vec;
        
        //ビームサーチ開始
        while(bfs_que.empty() == false){
            
            //cout << "bfs_que_size : " << bfs_que.size() << endl;
            
            Class_for_bfs target = bfs_que.front();
            bfs_que.pop();
            
            //veget_vecの更新
            vector<Veget> before_veget_vec = target.return_veget_vec();
            vector<Veget> now_veget_vec;
            for(Veget p : before_veget_vec){
                if(p.end >= pos_depth) now_veget_vec.push_back(p);
            }
            for(ll i = 0; i < m; i++){   //高速化の余地あり
                if(veget_data[i][2] == pos_depth){
                    Veget new_veget(veget_data[i][0], veget_data[i][1], veget_data[i][2], 
                            veget_data[i][3], veget_data[i][4]);
                    now_veget_vec.push_back(new_veget);
                }
            }
            //veget_vecの更新終了
            
            //first_heatmapとnow_veget_vecからheatmapを作成する
            ld heatmap[n][n];
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    heatmap[i][j] = first_heatmap[pos_depth][i][j];
                }
            }
            for(Veget veget : now_veget_vec){
                ll x = veget.x;
                ll y = veget.y;
                //ll start = veget.start;   <-使わない
                ll end = veget.end;
                ll val = veget.val;

                heatmap[x][y] += val;
                if(pos_depth + 1 <= end){
                    for(ll k = 0; k < 4; k++){
                        ll dx = x + vec1[k].first;
                        ll dy = y + vec1[k].second;
                        if(judge_in_field(dx, dy) == false) continue;
                        heatmap[dx][dy] += val * pow(discount_rate, 1);
                    } 
                }
                if(pos_depth + 2 <= end){
                    for(ll k = 0; k < 8; k++){
                        ll dx = x + vec2[k].first;
                        ll dy = y + vec2[k].second;
                        if(judge_in_field(dx, dy) == false) continue;
                        heatmap[dx][dy] += val * pow(discount_rate, 2);
                    } 
                }
                if(pos_depth + 3 <= end){
                    for(ll k = 0; k < 12; k++){
                        ll dx = x + vec3[k].first;
                        ll dy = y + vec3[k].second;
                        if(judge_in_field(dx, dy) == false) continue;
                        heatmap[dx][dy] += val * pow(discount_rate, 3);
                    } 
                }
            }
            //heatmapの作成終了
            
            //heatmap_for_selected_place_vecの作成, ldを扱うのは不安
            ll heatmap_for_selected_place_vec[n][n];
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    heatmap_for_selected_place_vec[i][j] = (heatmap[i][j] + dist(engine)) * 10000;
                }
            }

            //全てのスコアを集計し、必要なスコアを計算
            vector<ll> heatmap_val;
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    heatmap_val.push_back(heatmap_for_selected_place_vec[i][j]);  
                }
            }
            sort(heatmap_val.begin(), heatmap_val.end());
            reverse(heatmap_val.begin(), heatmap_val.end());
            ld necessary_heatmap = heatmap_val[num_selected_place];
            //集計、計算終了
            
            //selected_place_vec作成
            vector<Place> selected_place_vec;
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    if(heatmap_for_selected_place_vec[i][j] >= necessary_heatmap){
                        Place selected_place(i, j);
                        selected_place_vec.push_back(selected_place); 
                    }
                }
            }

            //selected_neighbor_place_vec作成
            ld heatmap_NN[N][N];   //<-関数の引値にできる様にする、後で他にも使う
            for(ll i = 0; i < N; i++){
                for(ll j = 0; j < N; j++){
                    heatmap_NN[i][j] = heatmap[i][j];
                }
            }
            vector<Place> before_track_vec = target.return_track_vec();
            vector<Place> selected_neighbor_place_vec = 
                    select_neighbor_cluster_place(before_track_vec, heatmap_NN);
            
            //selected_neighbor_place_vec と selected_place_vec を selected_place_vec に融合する
            for(Place place : selected_neighbor_place_vec) selected_place_vec.push_back(place);
            
            //track_field作成
            bool track_field[n][n];   //そこに収穫機があるかどうか
            for(ll i = 0; i < n; i++){
                for(ll j = 0; j < n; j++){
                    track_field[i][j] = false;
                }
            }
            vector<Place> track_vec_for_making_field = target.return_track_vec();
            for(auto p : track_vec_for_making_field) track_field[p.x][p.y] = true;
            //track_field作成終了
            
            //収穫機を買うパターン タイプ1
            if(target.money >= pow((target.track_vec.size() + 1), 3) && pos_depth < not_buy_track_time){   //所持金が収穫機の価格より大きかったら
                //多すぎるし無駄なので制限する必要あり、3ターン以内の野菜の周辺など
                //future_veget_field、selected_place_vec作成
                ll future_veget_field[n][n];
                for(ll i = 0; i < n; i++){
                    for(ll j = 0; j < n; j++){
                        future_veget_field[i][j] = 0;
                    }
                }
                vector<Place> track_vec_for_veget_field = target.return_track_vec();
                vector<Veget> veget_vec_for_veget_field = target.return_veget_vec();
                //for(Veget veget : veget_vec_for_veget_field){
                    //track_veget_field[veget.x][veget.y] 
                //}
                
                for(Place place : selected_place_vec){
                    ll x = place.x;
                    ll y = place.y;
                    if(track_field[x][y] == true) continue;
                    else{
                        vector<Place> track_vec = target.return_track_vec();
                        vector<Veget> veget_vec;
                        for(Veget p : now_veget_vec) veget_vec.push_back(p);
                        vector<Opera> opera_vec = target.return_opera_vec();
                            
                        Place new_track(x, y);
                        track_vec.push_back(new_track);
                        vector<ll> vec_for_opera = {x, y};
                        Opera new_opera(1, vec_for_opera);
                        opera_vec.push_back(new_opera);
                        ll money = target.money - pow((target.track_vec.size() + 1), 3);   
                            
                        //収穫を行う
                        Money_and_veget_vec money_and_veget_vec = 
                                calculate_after_operataion(track_vec, veget_vec);
                        ll new_money = money + money_and_veget_vec.money;
                        vector<Veget> new_veget_vec;
                        for(Veget veget : money_and_veget_vec.veget_vec) new_veget_vec.push_back(veget);
                        //収穫の処理終了
                            
                        ld heatmap_for_score[N][N];   //固定超配列の長さがNじゃないと動かない
                        for(ll i = 0; i < N; i++){
                            for(ll j = 0; j < N; j++){
                                heatmap_for_score[i][j] = heatmap[i][j];
                            }
                        }
                        ld score = calculate_score(track_vec, new_money, heatmap_for_score, pos_depth);
                        score_vec.push_back(score);
                            
                        Class_for_bfs next_target(track_vec, new_veget_vec, opera_vec, new_money, score);
                        next_bfs_que.push(next_target);
                    }
                }
            }
            
            //収穫機を移動させるパターン タイプ2   //<-変える時は絶対に買った方が良いので
            else{
                vector<Place> now_track_vec = target.return_track_vec();
                vector<Place> selected_track_vec = return_edge_track(now_track_vec, heatmap_NN);
                vector<Place> not_selected_track_vec = return_not_edge_track(now_track_vec, selected_track_vec);
            
                for(ll k = 0; k < selected_track_vec.size(); k++){   //k番目を(x, y)に移動する
                    for(Place place : selected_place_vec){
                        ll x = place.x;
                        ll y = place.y;
                        if(track_field[x][y] == true) continue;   //すでに収穫機がある場所には移動できないので <-最初からこれをselected_place_vecに入れなければいいんじゃ？
                        
                        vector<Veget> veget_vec;
                        for(Veget veget : now_veget_vec) veget_vec.push_back(veget);
                        
                        //移動後のtrack_vecを作成
                        Place new_track(x, y);
                        vector<Place> track_vec;
                        for(Place not_selected_track : not_selected_track_vec) track_vec.push_back(not_selected_track);
                        for(ll l = 0; l < selected_track_vec.size(); l++){
                            if(l == k) track_vec.push_back(new_track);   //k番目を(x, y)に移動する
                            else track_vec.push_back(selected_track_vec[l]);   //それ以外は現状維持
                        }
                        //移動後のtrack_vec作成終了

                        vector<ll> vec_for_opera = {selected_track_vec[k].x, selected_track_vec[k].y, x, y};
                        Opera new_opera(2, vec_for_opera);
                        vector<Opera> opera_vec = target.return_opera_vec();
                        opera_vec.push_back(new_opera);
                        
                        //収穫を行う
                        Money_and_veget_vec money_and_veget_vec = 
                                calculate_after_operataion(track_vec, veget_vec);
                        ll new_money = target.money + money_and_veget_vec.money;
                        vector<Veget> new_veget_vec;
                        for(Veget veget : money_and_veget_vec.veget_vec) new_veget_vec.push_back(veget);
                        //収穫の処理終了
                        
                        ld heatmap_for_score[N][N];   //固定超配列の長さがNじゃないと動かない
                        for(ll i = 0; i < N; i++){
                            for(ll j = 0; j < N; j++){
                                heatmap_for_score[i][j] = heatmap[i][j];
                            }
                        }
                        ld score = calculate_score(track_vec, new_money, heatmap_for_score, pos_depth);
                        score_vec.push_back(score);
                        
                        Class_for_bfs next_target(track_vec, new_veget_vec, opera_vec, new_money, score);   
                        next_bfs_que.push(next_target);
                    }
                }
            }
        }
        
        //cout << "next_bfs_que_size : " << next_bfs_que.size() << endl;
        
        //bfs_que作成
        sort(score_vec.begin(), score_vec.end());
        reverse(score_vec.begin(), score_vec.end());
        ld necessary_score, max_score;
        if(beamsearch_width < next_bfs_que.size()) necessary_score = score_vec[beamsearch_width - 1];  
        else necessary_score = -1 * INF;   //ビームサーチ幅より数が少ない時はなんでもよい
        max_score = score_vec[0];
        
        while(next_bfs_que.empty() == false){
            Class_for_bfs next_Class_for_bfs = next_bfs_que.front();
            next_bfs_que.pop();
            if(next_Class_for_bfs.score >= necessary_score) bfs_que.push(next_Class_for_bfs);
        }
        //bfs作成終了
        //ビームサーチ終了
        
        //100ターン毎にOperaを出力する
        //Opera_vecが長すぎると時間がかかるため
        Class_for_bfs best_Class_for_bfs;
        
        if(pos_depth % 100 == 99 || pos_depth == t - 1){
            while(bfs_que.empty() == false){
                Class_for_bfs target_class_for_bfs = bfs_que.front();
                bfs_que.pop();
                if(target_class_for_bfs.score >= max_score - 1.0){ 
                    best_Class_for_bfs = target_class_for_bfs;
                    
                    //解答を出力
                    for(Opera opera : best_Class_for_bfs.opera_vec){
                        //cout << sum << " ";
                        opera.print();
                        sum++;
                    }
                    //cout << sum << " " << pos_depth << endl;
                    //sum = 0;
                    
                    //更新
                    while(bfs_que.empty() == false) bfs_que.pop();
                    best_Class_for_bfs.make_opera_vec_empty();
                    bfs_que.push(best_Class_for_bfs);
                    break;
                }
            }
        }    
        
        //cout << pos_depth << " " << bfs_que.size() << endl;

        if(pos_depth % 5 == 0){    //5ターン毎に時間計測
            before_time = now_time;
            now_time = clock();
            //cout << pos_depth << " " << now_time << endl;
        }

        adjust_parameters(before_time, now_time, pos_depth);
        
        pos_depth++;
        
    }
}

int main(void){
    cin >> n >> m >> t;
    for(ll i = 0; i < m; i++){
        cin >> veget_data[i][0]  >> veget_data[i][1]  >> veget_data[i][2]  >> veget_data[i][3]  >> veget_data[i][4];
    }
    
    BFS_and_beamserch();
    
}
