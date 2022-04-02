#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <string>
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
#define H 30
#define W 30
#define T 300
#define INF 10000
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

// パラメータ ------------------------------------------------------------------------------------------------------
int limit_dog_count = 3;
int limit_distance = 5;
int change_necessary_animal_num_time[] = {0, 0, 180, 200};
// ----------------------------------------------------------------------------------------------------------------

int ANIMAL_KIND = 6;   // 本当は5だが開集合なので
int middle = W / 2;
int pair_num = 0;   // Human_pairのセット数
int rest_num = 0;   // 余っている人間の数
int killing_room_max_y;
int dog_count = 0;
int kill_dog_time = 0;

int vec[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

int n, m;
int t = 0;
map<int, int> animal_field[H][W];
bool wall_field[H][W];

// 壁の置き場所(犬を前処理しないとき)
vector<int> tate5{4, 9, 14, 19, 24};
vector<int> tate6{3, 8, 12, 17, 21, 26};
vector<int> tate7{2, 6, 10, 14, 18, 22, 26};
vector<int> tate8{2, 5, 9, 12, 16, 20, 23, 26};
vector<int> tate9{2, 5, 8, 11, 14, 17, 20, 23, 26};
vector<int> tate10{1, 4, 7, 10, 13, 16, 19, 22, 25, 28};
vector<int> yoko5{10, 19};
vector<int> yoko6{7, 15, 22};
vector<int> yoko7{7, 15, 22};
vector<int> yoko8{7, 15, 22};
vector<int> yoko9{7, 15, 22};
vector<int> yoko10{7, 15, 22};
vector<vector<int> > row_wall_vec_vec = {tate5, tate6, tate7, tate8, tate9, tate10};
vector<vector<int> > col_road_vec_vec = {yoko5, yoko6, yoko7, yoko8, yoko9, yoko10};

// 壁の置き場所(犬を前処理するとき)
vector<int> dog_tate5{6, 11, 16, 21, 26};
vector<int> dog_tate6{7, 11, 15, 19, 23, 27};
vector<int> dog_tate7{6, 9, 12, 15, 18, 22, 25};
vector<int> dog_tate8{6, 9, 12, 15, 18, 21, 24, 27};
vector<int> dog_tate9{5, 7, 10, 13, 16, 19, 22, 25, 28};
vector<int> dog_tate10{5, 7, 9, 12, 15, 18, 20, 23, 26, 28};
vector<vector<int> > dog_row_wall_vec_vec = {dog_tate5, dog_tate6, dog_tate7, dog_tate8, dog_tate9, dog_tate10};
vector<vector<int> > dog_col_road_vec_vec = {yoko5, yoko6, yoko7, yoko8, yoko9, yoko10};

vector<int> row_wall_vec;
vector<int> col_road_vec;

// 初期位置
vector<int> first_place_vec;
vector<int> pair0{};
vector<int> pair1{4};
vector<int> pair2{4, H - 1};
vector<int> pair3{4, 17, H - 1};
vector<int> first_place_vec_list[] = {pair0, pair1, pair2, pair3};
string ans_list[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

vector<string> pair_direction{"D", "D", "D", "D"};
vector<string> rest_direction{"U", "U"};

int total_min_y = 0;
int animal_min_y = H - 1;
int animal_max_y = 0;

int phase = 0;
int necessary_animal_num = 2;


class Place{
public : 
    int x, y;
    Place(int a, int b){
        x = b;
        y = a;
    }
    Place(){};
    
    bool operator > (const Place& another) const{
        if(y > another.y) return true;
        else if(y < another.y) return false;
        else{
            if(x > another.x) return true;
            else return false;
        }
    }
    bool operator < (const Place& another) const{
        if(y < another.y) return true;
        else if(y > another.y) return false;
        else{
            if(x < another.x) return true;
            else return false;
        }
    }
    bool operator == (const Place& another) const{
        if(x == another.x && y == another.y) return true;
        else return false;
    }
    
    
    void update(string s){
        if(s == "U") y = y + 1;
        else if(s == "D") y = y - 1;
        else if(s == "L") x = x - 1;
        else if(s == "R") x = x + 1;
        else cout << "------ something wrong in place.update!! ------" << endl;
    }


    void print(){ 
        cout << x << " " << y << endl;
    }
};


class Action{
public : 
    int kind;   // 0なら移動   1なら障害物
    string direction;
    
    Action(int a, string s){
        kind = a;
        direction = s;
    }
    
    Action(){}
};


class Animal{
public : 
    int number;
    int kind;   // 動物さんの種類
    Place place;
    
    Animal(int a, int b, Place p){
        number = a;
        kind = b;
        place = Place(p.y, p.x);
    }
    
    Animal(){}
    
    void update(string s){
        rep(i, s.size()){
            if(s[i] == 'U') place.y = place.y - 1;
            else if(s[i] == 'D') place.y = place.y + 1;
            else if(s[i] == 'L') place.x = place.x - 1;
            else if(s[i] == 'R')place.x = place.x + 1;
            else cout << "something wrong in animal.update" << endl;
        }
    }
};


class Human{
public : 
    int number;
    int phase;  
    Place place;
    queue<Action> action_queue;
    int road;
    
    Human(int a, Place p){
        number = a;
        place = p;
        phase = 0;
    }
    
    Human(int a, Place p, queue<Action> q){
        number = a;
        place = p;
        while(q.empty() == false){
            Action action = q.front();   q.pop();
            action_queue.push(action);
        }
    }
    
    Human(){}
    
    // operator
    bool operator > (const Human& another) const{
        if(place > another.place) return true;
        else if(place < another.place) return false;
        else{
            if(place > another.place) return true;
            else return false;
        }
    }
    bool operator < (const Human& another) const{
        if(place < another.place) return true;
        else if(place > another.place) return false;
        else{
            if(place < another.place) return true;
            else return false;
        }
    }

    void update(string s){
        if(s == "U") place.y = place.y - 1;
        else if(s == "D") place.y = place.y + 1;
        else if(s == "L") place.x = place.x - 1;
        else if(s == "R") place.x = place.x + 1;
        else if(s == ".") {}
        else if(s == "u") wall_field[place.y - 1][place.x] = true;
        else if(s == "d") wall_field[place.y + 1][place.x] = true;
        else if(s == "l") wall_field[place.y][place.x - 1] = true;
        else if(s == "r") wall_field[place.y][place.x + 1] = true;
        else cout << "something error in human.update " << s << endl; 
    }
};


class Room{
public : 
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int number;
    string direction;
    map<int, int> animal_map;   // 部屋内の動物
    map<string, int> remain_space;
    vector<int> remain_y;
    int animal_num = 0;
    bool closed = false;
    bool must_open = false;

    Room(int a, int b, int c, int d, int e){
        min_y = a;
        max_y = b;
        min_x = c;
        max_x = d;
        number = e;

        if(min_x == 0) direction = "L";
        else if(max_x == W - 1) direction = "R";
        else direction = "C";
        
        if(direction == "L") remain_space["L"] = 0;
        else remain_space["L"] = max_y - min_y + 1;
        if(direction == "R") remain_space["R"] = 0;
        else remain_space["R"] = max_y - min_y + 1;
    }

    Room(){}

    void update(){
        // 壁を置く場所に何マス余裕があるか
        if(direction == "L"){
            remain_space["R"] = max_y - min_y + 1;
            for(int i = min_y; i <= max_y; i++){
                if(wall_field[i][max_x] == true) remain_space["R"]--;
            }
        }
        else if(direction == "R"){
            remain_space["L"] = max_y - min_y + 1;
            for(int i = min_y; i <= max_y; i++){
                if(wall_field[i][min_x] == true) remain_space["L"]--;
            }
        }
        else{
            remain_space["L"] = max_y - min_y + 1;
            remain_space["R"] = max_y - min_y + 1;
            for(int i = min_y; i <= max_y; i++){
                if(wall_field[i][max_x] == true) remain_space["R"]--;
                if(wall_field[i][min_x] == true) remain_space["L"]--;
            }
        }
        
        // 部屋が閉じられているかを確認する
        if(remain_space["L"] == 0 && remain_space["R"] == 0) closed = true;

        // animal_mapを初期化
        for(int i = 0; i < ANIMAL_KIND; i++) animal_map[i] = 0;

        // 閉じ込められている動物はカウントしない
        if(closed == true) animal_num = 0;
        else{
            animal_num = 0;
            for(int i = min_y; i <= max_y; i++){
                for(int j = min_x; j <= max_x; j++){
                    rep(k, ANIMAL_KIND){
                        animal_map[k] += animal_field[i][j][k];
                        animal_num += animal_field[i][j][k];
                    }
                }
            }
        }

        // まだ壁を置かれていない場所
        remain_y.clear();   // 一旦初期化
        for(int i = min_y; i <= max_y; i++){
            if(wall_field[i][min_x] == false && wall_field[i][max_x] == false) remain_y.push_back(i);
        }
    }
};


template< typename A, typename B >
class Pair{
public : 
    A first;
    B second;

    Pair(A a, B b){
        first = a;
        second = b;
    }
    Pair(){}

    bool operator > (const Pair& another) const{
        if(second > another.second) return true;
        else return false;
    }
    bool operator < (const Pair& another) const{
        if(second < another.second) return true;
        else return false;
    }
};


class PairAction{
public : 
    vector<Pair<int, string> > pair_action_vec;
    int score;

    PairAction(Pair<int, string> a, Pair<int, string> b, int c){
        pair_action_vec.push_back(a);
        pair_action_vec.push_back(b);
        score = c;
    }

    PairAction(Pair<int, string> a, int b){
        pair_action_vec.push_back(a);
        score = b;
    }

    PairAction(){}

    bool operator > (const PairAction& another) const{
        if(score > another.score) return true;
        else return false;
    }

    bool operator < (const PairAction& another) const{
        if(score < another.score) return true;
        else return false;
    }
};
// ------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------
vector<Animal> animal_vec;
vector<Human> human_vec;
vector<int> pair_vec_list[H];
vector<int> rest_vec;
map<int, Room> room_map_list[H];
// ------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------
bool in_vector(int a, vector<int> vec){
    bool ret = false;
    rep(i, vec.size()){
        if(a == vec[i]) ret = true;
    }

    return ret;
}


void restart_field(){
    rep(i, H){
        rep(j, W){
            rep(k, ANIMAL_KIND){
                animal_field[i][j][k] = 0;
            }
        }
    }
}


// (i, j)に動物がいるか
bool exist_animal(int i, int j){
    bool ret = false;
    rep(k, ANIMAL_KIND){
        if(animal_field[i][j][k] >= 1) ret = true;
    }

    return ret;
}


bool judge_inside(int y, int x){
    if(y < 0) return false;
    else if(y >= H) return false;
    else if(x < 0) return false;
    else if(x >= W) return false;
    else return true;
}


int calc_distance(Place p1, Place p2){
    int ret = abs(p1.x - p2.x) + abs(p1.y - p2.y);
    return ret;
}


//  placeにいるhumanがsの方向に障害物をおければtrue
bool judge_install(Place place, string s){
    int y = place.y;
    int x = place.x;
    if(s == "d") y++;
    else if(s == "u") y--;
    else if(s == "l") x--;
    else if(s == "r") x++;
    else cout << "something wrong in judge_install" << endl;
    
    bool ret = true;
    if(exist_animal(y, x) == true || wall_field[y][x] == true) ret = false;   // そこに動物がいる、またはすでに壁があるなら無理
    rep(i, 4){
        int dy = y + vec[i][0];
        int dx = x + vec[i][1];
        if(judge_inside(dy, dx) == false) continue;
        else{
            if(exist_animal(dy, dx) == true){
                ret = false;
                break;
            }
        }
    }

    return ret;
}


// [min_y, max_y]に障害物を設置できるか
bool judge_multi_install(int min_y, int max_y, int x, string s){
    bool ret = true;
    for(int i = min_y; i <= max_y; i++){
        Place place(i, x);
        if(judge_install(place, s) == false){
            ret = false;
            break;
        }
    }

    return ret;
}


// [a, b], [c, d]
map<int, int> make_animal_map(int min_y, int max_y, int min_x, int max_x){
    map<int, int> ret;
    for(int i = min_y; i <= max_y; i++){
        for(int j = min_x; j <= max_x; j++){
            rep(k, ANIMAL_KIND){
                ret[k] += animal_field[i][j][k];
            }
        }
    }

    return ret;
}


int count_animal(map<int, int> animal_map){
    int ret = 0;
    for(int i = 1; i < ANIMAL_KIND; i++){ 
        ret += animal_map[i];
    }

    return ret;
}


// yがどこの部屋か、壁の横なら-1を返す
int return_room_index(int y){
    rep(i, row_wall_vec.size() + 1){
        if(room_map_list[i][0].min_y <= y && y <= room_map_list[i][0].max_y) return i;
    }
    return -1;
}


// placeがどの部屋に属しているか
Pair<int, int> return_room_index(Place place){
    int x = place.x;
    int y = place.y;

    // killing_dog_roomにいる場合は-2
    Pair<int, int> killing_room_pair(-2, -2);
    if(1 <= x && x <= W - 2 && y <= total_min_y - 1) return killing_room_pair;

    // killing_dog_roomの横にいる場合は、その下の部屋の番号を返す
    if(total_min_y != 0){
        Pair<int, int> left_margin(0, 0);
        Pair<int, int> right_margin(0, col_road_vec.size());
        if(x == 0 && y < total_min_y) return left_margin;
        else if(x == W - 1 && y < total_min_y) return right_margin;
    }

    // 普通のケース
    rep(i, row_wall_vec.size() + 1){
        rep(j, col_road_vec.size() + 1){
            Room room = room_map_list[i][j];
            Pair<int, int> pair(i, j);
            if(room.min_y <= y && y <= room.max_y && room.min_x <= x && x <= room.max_x) return pair;
        }
    }

    // 上の状況でreturnしないのは道路にいる時
    Pair<int, int> road_pair(-1, -1);
    return road_pair;
}


// まだ捕まっていない動物のindexを出力
vector<int> return_running_animal_vec(){
    vector<int> ret;
    rep(i, n){
        Pair<int, int> room_pair = return_room_index(animal_vec[i].place);
        
        if(room_pair.first == -1) ret.push_back(i);   // 道路にいる時
        else if(room_pair.first == -2) {}   // killing_dog_roomにいる時
        else{
            Room room = room_map_list[room_pair.first][room_pair.second];
            if(room.closed == true) continue;
            else ret.push_back(i);
        }
    }

    return ret;
}


string make_ans(){
    string ret = "";
    rep(i, m){
        ret += ans_list[i];
        ans_list[i] = ".";   // ついでに初期化
    }

    return ret;
}


void update(){
    // 時間を進める
    t++;

    // 囲うのに必要な動物の数を減らす
    if(t >= change_necessary_animal_num_time[pair_num]) necessary_animal_num = 1;
    else necessary_animal_num = 2;   // 序盤pair_numの数が不安定なので予備

    // animal_field及びanimal_vecのupdate
    restart_field();   // 盤面を全て0にする
    rep(j, n){
        string s;
        cin >> s;
        animal_vec[j].update(s);
        animal_field[animal_vec[j].place.y][animal_vec[j].place.x][animal_vec[j].kind]++;
    }

    // 部屋作成前ならこれ以降の処理は行わない
    if(phase == 0) return;   

    // 各部屋のupdate
    rep(i, row_wall_vec.size() + 1){
        rep(j, col_road_vec.size() + 1){
            room_map_list[i][j].update();
        }
    }

    // 各部屋のupdate, この部屋を封鎖すると左右の行き来ができなくなってしまう場合は封鎖できない様にする
    rep(i, row_wall_vec.size() + 1){
        rep(j, col_road_vec.size() + 1){
            // 閉じている部屋及び、中央ではない部屋は考えなくて良い
            if(room_map_list[i][j].closed == true || room_map_list[i][j].direction != "C") continue;

            int open_count = 0;
            rep(k, row_wall_vec.size() + 1){
                if(room_map_list[k][j].closed == false) open_count++;
            }
            if(open_count == 1) room_map_list[i][j].must_open = true;
            else if(open_count == 0) cout << "something wrong in update" << endl; 
        }
    }

    // animal_min_y, animal_max_yのupdate
    vector<int> room_min_y_vec;   // ←グローバルで持っておけよ...
    vector<int> room_max_y_vec{total_min_y};
    animal_min_y = H - 1;
    animal_max_y = 0;
    rep(i, row_wall_vec.size() + 1){
        room_min_y_vec.push_back(room_map_list[i][0].min_y);
        room_max_y_vec.push_back(room_map_list[i][0].max_y);
        rep(j, col_road_vec.size() + 1){
            if(room_map_list[i][j].animal_num >= 1){ 
                animal_min_y = min(animal_min_y, room_map_list[i][j].min_y);
                animal_max_y = max(animal_max_y, room_map_list[i][j].max_y);
            }
        }
    }
    room_min_y_vec.push_back(H - 1);
    rep(i, col_road_vec.size()){
        rep(j, room_max_y_vec.size() - 1){
            int road = col_road_vec[i];
            if(count_animal(make_animal_map(room_min_y_vec[j], room_min_y_vec[j + 1], road, road)) >= 1){
                animal_min_y = min(animal_min_y, room_min_y_vec[j]);
            }
            if(count_animal(make_animal_map(room_max_y_vec[j], room_max_y_vec[j + 1], road, road)) >= 1){
                animal_max_y = max(animal_max_y, room_max_y_vec[j + 1]);
            }
        }
    }

    // ほとんど同じ場所を同じ向きに進むのは効率が悪いので、人間同士の距離が近すぎる時は向きを変える
    // ループに陥る可能性があるので、乱数を入れておく
    // 場所による補正は下で行う
    rep(i, pair_num){
        rep(j, pair_num){
            if(i == j) continue;
            Human human1 = human_vec[pair_vec_list[i][0]];
            Human human2 = human_vec[pair_vec_list[j][0]];
            if(pair_direction[i] == pair_direction[j] && abs(human1.place.y - human2.place.y) <= limit_distance){
                if(rand() % 2 == 0){
                    pair_direction[i] = "U";
                    pair_direction[j] = "D";
                }
                else{
                    pair_direction[i] = "D";
                    pair_direction[j] = "U";
                }
            }
        }
    }

    // humanのdirectionをupdate, room_min_y, room_max_yを使うので、位置はここ
    rep(i, pair_num){
        int y = human_vec[pair_vec_list[i][0]].place.y;
        if(y == total_min_y) pair_direction[i] = "D";
        else if(y == H - 1) pair_direction[i] = "U";
        else if(y <= animal_min_y) pair_direction[i] = "D";
        else if(y >= animal_max_y) pair_direction[i] = "U";
    }

    // 余っている人間の進行方向を変える
    rep(i, rest_num){
        int y = human_vec[rest_vec[i]].place.y;
        if(y == total_min_y) rest_direction[i] = "D";
        else if(y == H - 1) rest_direction[i] = "U";
        else if(y <= animal_min_y) rest_direction[i] = "D";
        else if(y >= animal_max_y) rest_direction[i] = "U";
    }
}


void all_room_update(){
    rep(i, row_wall_vec.size() + 1){
        rep(j, col_road_vec.size() + 1){
            room_map_list[i][j].update();
        }
    }
}


// make_all_vecとセットで(0, 1, 2), (0, 1, 3), ... , (a-1, a-2, a-3)を作る(重複を許さない)
void dfs_for_make_all_vec(int i, int size, int range_start, int range_end, vector<int>& buf, vector<string>& ret_vec){
    if(i == 0) buf.resize(size);
    if(i == size) {
        string ret = "";
        for(int i = 0; i < buf.size(); ++i) ret += to_string(buf[i]);
        ret_vec.push_back(ret);
    }
    else{
        for(int j = range_start; j < range_end; j++){
            buf[i] = j;
            dfs_for_make_all_vec(i + 1, size, range_start, range_end, buf, ret_vec);
        }
    }
}

vector<string> make_all_vec(int size, int range_start, int range_end, bool permit_duplicate = false){
    vector<int> buf;
    vector<string> ret, ret_memo;
    dfs_for_make_all_vec(0, size, range_start, range_end, buf, ret_memo);
    rep(i, ret_memo.size()){
        string str = ret_memo[i];
        map<char, int> mp;
        bool point = true;
        rep(j, str.size()){
            if(mp[str[j]] == 0) mp[str[j]]++;
            else point = false;
        }
        if(point == true) ret.push_back(str);
        else if(permit_duplicate == true) ret.push_back(str);
    }
    return ret;
}


// 直線状の動きに必要なActionをqueueに追加
void make_move_queue(Place pos, Place target, queue<Action>& que){
    if(pos.x != target.x && pos.y != target.y) cout << "something wrong in make_action_queue" << endl;

    if(pos.x == target.x){
        if(target.y > pos.y){
            rep(i, target.y - pos.y){
                Action action(0, "D");
                que.push(action);
            }
        }
        else{
            rep(i, pos.y - target.y){
                Action action(0, "U");
                que.push(action);
            }
        }
    }
    else{
        if(target.x > pos.x){
            rep(i, target.x - pos.x){
                Action action(0, "R");
                que.push(action);
            }
        }
        else{
            rep(i, pos.x - target.x){
                Action action(0, "L");
                que.push(action);
            }
        }
    }
}
// -------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------------------------------
void make_action_queue_for_killing_dogs(int index){
    Place pos = human_vec[index].place;

    // 位置によっては事故るので補正する
    if(pos.y == killing_room_max_y + 1){
        Action action(0, "U");
        human_vec[index].action_queue.push(action);
        pos.y = pos.y - 1;
    }

    // [0, middle - 1]に壁を作る
    if(index == 0){
        Place relay1(pos.y, middle - 1);
        Place relay2(killing_room_max_y, middle - 1);
        make_move_queue(pos, relay1, human_vec[index].action_queue);
        make_move_queue(relay1, relay2, human_vec[index].action_queue);

        rep(i, middle - 1){
            Action action1(1, "d");
            human_vec[index].action_queue.push(action1);
            Action action2(0, "L");
            human_vec[index].action_queue.push(action2);
        }
    }

    // [middle, W - 1]に壁を作る
    else if(index == 1){
        Place relay1(pos.y, middle);
        Place relay2(killing_room_max_y, middle);
        make_move_queue(pos, relay1, human_vec[index].action_queue);
        make_move_queue(relay1, relay2, human_vec[index].action_queue);

        rep(i, W - middle - 1){
            Action action1(1, "d");
            human_vec[index].action_queue.push(action1);
            Action action2(0, "R");
            human_vec[index].action_queue.push(action2);
        }
    }

    else{
        int target_x = (index % 2) * (W - 1);
        int target_y = int((index - 2) / 2);
        if((m == 9 || m == 10) && index >= 8) target_y = 0;   // 壁からはみ出るので補正
        Place relay(pos.y, target_x);
        Place target(target_y, target_x);
        make_move_queue(pos, relay, human_vec[index].action_queue);
        make_move_queue(relay, target, human_vec[index].action_queue);
    }
}


void kill_dogs(){
    if(m == 5){ 
        total_min_y = 3;
        killing_room_max_y = 1;
    }
    else{ 
        total_min_y = 4;
        killing_room_max_y = 2;
    }

    // 行動を決定
    sort(human_vec.begin(), human_vec.end());
    for(int i = 0; i < m; i++) make_action_queue_for_killing_dogs(i);

    // 人間を動かす
    while(t < T){
        int finish_num = 0;   // 壁の作成と移動が終わった人の数
        rep(i, m){
            if(human_vec[i].action_queue.empty() == true){ 
                ans_list[human_vec[i].number] = ".";
                finish_num++;
            }
            else{
                Action action = human_vec[i].action_queue.front();
                if(action.kind == 0){
                    human_vec[i].action_queue.pop();
                    ans_list[human_vec[i].number] = action.direction;
                    human_vec[i].update(action.direction);
                }
                else if(action.kind == 1 && judge_install(human_vec[i].place, action.direction) == true){
                    human_vec[i].action_queue.pop();
                    ans_list[human_vec[i].number] = action.direction;
                    human_vec[i].update(action.direction);
                }
                else ans_list[human_vec[i].number] = ".";   // 何もしなかった時はqueue.popしない
            }
        }

        if(finish_num == m) break;   // 出力をせず終了する
        else{
            cout << make_ans() << endl;
            update();
        }
    }

    // 犬を閉じ込める
    while(t < T){
        map<int, int> killing_room_map = make_animal_map(0, killing_room_max_y, 1, W - 2);
        bool point = false;
        if(killing_room_map[4] == dog_count){
            if(judge_multi_install(0, killing_room_max_y, 0, "r") == true && judge_multi_install(0, killing_room_max_y, W - 1, "l") == true){
                point = true;
                kill_dog_time = t;
                rep(i, m){
                    if(human_vec[i].place.x == 0){
                        ans_list[human_vec[i].number] = "r";
                        human_vec[i].update("r");
                    }
                    else{
                        ans_list[human_vec[i].number] = "l";
                        human_vec[i].update("l");
                    }
                }
            }
        }

        cout << make_ans() << endl;
        update();
        if(point == true) break;
    }

    phase++;   // 犬閉じ込め終了
}
// -------------------------------------------------------------------------------------------------------------------------------


// -------------------------------------------------------------------------------------------------------------------------------
queue<Action> make_action_queue_for_building_row_wall(Place pos, Place target, int road_index, int row_index){
    // pos → relay → target → ... → next_target
    queue<Action> ret;
    Place relay(target.y, pos.x);
    Place next_target(target.y, col_road_vec[road_index]);

    // confine_animals開始時の場所
    int assemble_y;
    if(row_index >= first_place_vec.size()) assemble_y = target.y;
    else assemble_y = first_place_vec[row_index];
    Place assemble_place(assemble_y, col_road_vec[road_index]);

    // まず壁を作り始める地点まで移動する
    make_move_queue(pos, relay, ret);
    make_move_queue(relay, target, ret);

    // 2ターン停止する　これは犬を囲む時は、人間が目の前にいるからである
    if(dog_count >= limit_dog_count){
        Action stop(0, ".");
        ret.push(stop);
        ret.push(stop);
    }

    // 壁を作る
    int pos_x = target.x;
    if(target.x == 0){
        rep(i, W){
            if(in_vector(pos_x, col_road_vec) == true){
                Action action(0, "R");
                ret.push(action);
                pos_x += 1;
            }
            else if(pos_x == W - 1){
                Action action(1, "d");
                ret.push(action);
            }
            else{
                Action action1(1, "d");
                Action action2(0, "R");
                ret.push(action1);
                ret.push(action2);
                pos_x += 1;
            }
        }
    }
    else if(target.x == W - 1){
        rep(i, W){
            if(in_vector(pos_x, col_road_vec) == true){
                Action action(0, "L");
                ret.push(action);
                pos_x -= 1;
            }
            else if(pos_x == 0){
                Action action(1, "d");
                ret.push(action);
            }
            else{
                Action action1(1, "d");
                Action action2(0, "L");
                ret.push(action1);
                ret.push(action2);
                pos_x -= 1;
            }
        }
    }
    else cout << "something wrong in make_action_queue_for_building_row_wall " << target.x << endl;

    Place after_building_place(target.y, pos_x);
    make_move_queue(after_building_place, next_target, ret);
    make_move_queue(next_target, assemble_place, ret);

    return ret;
}


void make_walls(){
    // 部屋を作成
    int pos_min_y = total_min_y;
    int pos_max_y = row_wall_vec[0] - 1;
    rep(i, row_wall_vec.size() + 1){
        int pos_min_x = 0;
        int pos_max_x = col_road_vec[0] - 1;
        rep(j, col_road_vec.size() + 1){
            Room room(pos_min_y, pos_max_y, pos_min_x, pos_max_x, i * col_road_vec.size() + j);
            room_map_list[i][j] = room;
            if(j != col_road_vec.size() - 1){
                pos_min_x = col_road_vec[j] + 1;
                pos_max_x = col_road_vec[j + 1] - 1;
            }
            else{
                pos_min_x = col_road_vec[j] + 1;
                pos_max_x = W - 1;
            }
        }
        if(i != row_wall_vec.size() - 1){
            pos_min_y = row_wall_vec[i] + 1;
            pos_max_y = row_wall_vec[i + 1] - 1;
        }
        else{
            pos_min_y = row_wall_vec[i] + 1;
            pos_max_y = H - 1;
        }
    }

    // 各Humanがどう移動するのか
    sort(human_vec.begin(), human_vec.end());
    rep(i, row_wall_vec.size()){
        Place target_place;
        if(human_vec[i].place.x < middle) target_place = Place(row_wall_vec[i] - 1, 0);
        else target_place = Place(row_wall_vec[i] - 1, W - 1);
        int col = i % col_road_vec.size();
        int row = int(i / col_road_vec.size());

        // pairがいる
        if(row < pair_num){
            human_vec[i].action_queue = make_action_queue_for_building_row_wall(human_vec[i].place, target_place, col, row);
            human_vec[i].road = col;
            pair_vec_list[row].push_back(i);
        }

        // pairがいない。こいつらは端に寄せる
        else{
            if(col == 1) col = col_road_vec.size() - 1;
            human_vec[i].action_queue = make_action_queue_for_building_row_wall(human_vec[i].place, target_place, col, row);
            human_vec[i].road = col;
            rest_vec.push_back(i);
            rest_num++;
        }
    }

    // 人間を動かす
    while(t < T){
        int finish_num = 0;   // 壁の作成と移動が終わった人の数
        rep(i, m){
            if(human_vec[i].action_queue.empty() == true){ 
                ans_list[human_vec[i].number] = ".";
                finish_num++;
            }
            else{
                Action action = human_vec[i].action_queue.front();
                if(action.kind == 0){
                    human_vec[i].action_queue.pop();
                    ans_list[human_vec[i].number] = action.direction;
                    human_vec[i].update(action.direction);
                }
                else if(action.kind == 1 && judge_install(human_vec[i].place, action.direction) == true && t > kill_dog_time + 5){   // 早く置きすぎるとerror
                    human_vec[i].action_queue.pop();
                    ans_list[human_vec[i].number] = action.direction;
                    human_vec[i].update(action.direction);
                }
                else ans_list[human_vec[i].number] = ".";   // 何もしなかった時はqueue.popしない
            }
        }

        if(finish_num == m) break;   // 出力をせず終了する
        else{
            cout << make_ans() << endl;
            update();
        }
    }

    phase++;   // 壁作成終了
}
// ------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------
int calc_score_in_confine_animals(Pair<int, string> pair){
    Human human = human_vec[pair.first];
    int y = human.place.y;
    int x = human.place.x;
    int road_index = human.road;
    int room_index = return_room_index(y);
    string direction = pair.second;

    // 置けない場所
    if(judge_install(human.place, direction) == false) return -1 * INF;

    // 左端の部屋のケース
    if(road_index == 0 && direction == "l"){
        Room room = room_map_list[room_index][0];
        if(room.remain_space["R"] == 1 && room.animal_num >= necessary_animal_num) return room.animal_num * 10;
        else if(room.remain_space["R"] == 1 && room.animal_num != 0) return -1 * INF;   // 閉じ込められないのに置いてしまうケース
        else if(room.remain_space["R"] == 1 && room.animal_num == 0) return -1 * INF;   // 中に動物がいないのに封鎖してしまっている
        else return 1;
    }

    // 右端の部屋のケース
    else if(road_index == col_road_vec.size() - 1 && direction == "r"){
        Room room = room_map_list[room_index][road_index + 1];
        if(room.remain_space["L"] == 1 && room.animal_num >= necessary_animal_num) return room.animal_num * 10;
        else if(room.remain_space["L"] == 1 && room.animal_num != 0) return -1 * INF;   // 閉じ込められないのに置いてしまうケース
        else if(room.remain_space["L"] == 1 && room.animal_num == 0) return -1 * INF;
        else return 1;
    }

    // 中央の部屋のケース(room_map_list[room_index][road_index])
    else if(direction == "l"){
        Room room = room_map_list[room_index][road_index];
        if(room.must_open == true) return -1 * INF;   // これを閉じると左右が分断されてしまう
        else if(room.remain_space["R"] == 1 && room.animal_num >= necessary_animal_num) return room.animal_num * 10;   // 真ん中の部屋ならRでもLでも良い
        else if(room.remain_space["R"] == 1 && room.animal_num != 0) return -1 * INF;   // 閉じ込められないのに置いてしまうケース
        else if(room.remain_space["R"] == 1 && room.animal_num == 0) return -1 * INF;
        else return 2;
    }

    // 中央の部屋のケース(room_map_list[room_index][road_index + 1])
    else if(direction == "r"){
        Room room = room_map_list[room_index][road_index + 1];
        if(room.must_open == true) return -1 * INF;   // これを閉じると左右が分断されてしまう
        else if(room.remain_space["R"] == 1 && room.animal_num >= necessary_animal_num) return room.animal_num * 10;
        else if(room.remain_space["R"] == 1 && room.animal_num != 0) return -1 * INF;   // 閉じ込められないのに置いてしまうケース
        else if(room.remain_space["R"] == 1 && room.animal_num == 0) return -1 * INF;
        else return 2;
    }

    else{ 
        cout << "something wrong in calc_score_in_confine_animals" << endl;
        return -1;   // これがないとエラー
    }
}


// 引数が一つの同名の関数をオーバーロードしている。おけるかどうかの判定を行い、実際の計算は元の関数に投げる
int calc_score_in_confine_animals(Pair<int, string> pair1, Pair<int, string> pair2){
    Human human1 = human_vec[pair1.first];
    Human human2 = human_vec[pair2.first];
    string direction1 = pair1.second;
    string direction2 = pair2.second;

    // 置けない場所
    if(judge_install(human1.place, direction1) == false) return -1 * INF;
    else if(judge_install(human2.place, direction2) == false) return -1 * INF;
    else return calc_score_in_confine_animals(pair1);
}


// あまりの行動を決定
void confine_animals_every_rest(int rest_index){
    Human human = human_vec[rest_vec[rest_index]];
    int y = human.place.y;
    int x = human.place.x;
    int road_index = human.road;
    int room_index = return_room_index(y);
    bool point = false;   // これがtrueなら進む

    // 一番左の道路にいる
    if(road_index == 0){
        if(room_index == -1 || judge_install(human.place, "l") == false) point = true;
        else{
            Room room = room_map_list[room_index][road_index];
            if(room.remain_space["R"] == 1 && room.animal_num >= necessary_animal_num){
                ans_list[human.number] = "l";
                human_vec[rest_vec[rest_index]].update("l");
            }
            else if(room.remain_space["R"] == 1 && room.animal_num != 0) point = true;   // 動物が足りない
            else if(room.remain_space["R"] == 1 && room.animal_num == 0) point = true;  // 中に動物がいない
            else{
                ans_list[human.number] = "l";
                human_vec[rest_vec[rest_index]].update("l");
            }
        }
    }

    // 一番右の道路にいる
    else if(road_index == col_road_vec.size() - 1){
        if(room_index == -1 || judge_install(human.place, "r") == false) point = true;
        else{
            Room room = room_map_list[room_index][road_index];
            if(room.remain_space["L"] == 1 && room.animal_num >= necessary_animal_num){
                ans_list[human.number] = "r";
                human_vec[rest_vec[rest_index]].update("r");
            }
            else if(room.remain_space["L"] == 1 && room.animal_num != 0) point = true;  // 動物が足りない
            else if(room.remain_space["L"] == 1 && room.animal_num == 0) point = true;  // 中に動物がいない
            else{
                ans_list[human.number] = "r";
                human_vec[rest_vec[rest_index]].update("r");
            }
        }
    }
    else cout << "something wrong in confine_animals_every_rest " << road_index << endl;

    if(point == true){
        ans_list[human.number] = rest_direction[rest_index];
        human_vec[rest_vec[rest_index]].update(rest_direction[rest_index]);
    }
}


// pairの行動を決定
void confine_animals_every_pair(int pair_index){
    vector<int> pair_vec = pair_vec_list[pair_index];

    // ペアを、座標が左から右になる様に並び替える
    // Pairのfirstはhuman_vecのindex, secondは横方向の座標
    vector<Pair<int, int> > index_and_col_vec;
    rep(i, pair_vec.size()){
        int index = pair_vec[i];
        Pair<int, int> index_and_col(index, human_vec[index].place.x);
        index_and_col_vec.push_back(index_and_col);
    }
    sort(index_and_col_vec.begin(), index_and_col_vec.end());

    // 有り得る全ての行動をpriority_queueに入れる
    priority_queue<PairAction> pq;
    bool action_list[m];   // すでに行動が決定しているか
    for(int i = 0; i < m; i++) action_list[i] = false;
    rep(i, index_and_col_vec.size()){
        int human_index = index_and_col_vec[i].first;

        // 左側と協力
        if(i != 0){
            Pair<int, string> pair1(human_index, "l");
            Pair<int, string> pair2(human_index - 1, "r");
            PairAction pair_action(pair1, pair2, calc_score_in_confine_animals(pair1, pair2));
            pq.push(pair_action);
        }

        // 右側と協力
        if(i != index_and_col_vec.size() - 1){
            Pair<int, string> pair1(human_index, "r");
            Pair<int, string> pair2(human_index + 1, "l");
            PairAction pair_action(pair1, pair2, calc_score_in_confine_animals(pair1, pair2));
            pq.push(pair_action);
        }

        // 一番左
        if(i == 0){
            Pair<int, string> pair(human_index, "l");
            PairAction pair_action(pair, calc_score_in_confine_animals(pair));
            pq.push(pair_action);
        }

        // 一番右
        if(i == index_and_col_vec.size() - 1){
            Pair<int, string> pair(human_index, "r");
            PairAction pair_action(pair, calc_score_in_confine_animals(pair));
            pq.push(pair_action);
        }
    }

    // 行動を決定する
    bool no_wall_point = true;   // 誰も壁をおかないとtrue
    while(pq.empty() == false){
        PairAction target = pq.top();
        pq.pop();
        vector<Pair<int, string> > pair_action_vec = target.pair_action_vec;

        // スコアが負なのはダメ
        if(target.score < 0) continue;

        // 行動決定済みなのを指名していないか
        bool point = true;
        rep(i, pair_action_vec.size()){
            if(action_list[pair_action_vec[i].first] == true) point = false;   // 行動決定済みならだめ
        }

        // 行動をans_list, action_listに反映
        if(point == true){
            rep(i, pair_action_vec.size()){
                int human_number = human_vec[pair_action_vec[i].first].number;
                ans_list[human_number] = pair_action_vec[i].second;
                action_list[pair_action_vec[i].first] = true;
                human_vec[pair_action_vec[i].first].update(pair_action_vec[i].second);
                no_wall_point = false;
            }
        }
    }

    // 誰も壁を置かないなら進む
    if(no_wall_point == true){
        rep(i, pair_vec.size()){
            int human_index = pair_vec[i];
            ans_list[human_vec[human_index].number] = pair_direction[pair_index];
            human_vec[human_index].update(pair_direction[pair_index]);
        }
    }

    // pairの行動を決定するごとに部屋の状態をupdateする
    all_room_update();
}


void confine_animals(){
    while(t < T){
        // for(int i = 0; i < rest_num; i++) confine_animals_every_rest(i);
        for(int i = 0; i < pair_num; i++) confine_animals_every_pair(i);
        cout << make_ans() << endl;
        update();

        // 終了条件
        vector<int> running_animal_vec = return_running_animal_vec();   // まだ捕まっていない動物
        if(running_animal_vec.size() <= pair_num){
            break;
            phase++;
        }
    }
}
// ------------------------------------------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------------------------------------------
vector<int> pair_target;


vector<int> decide_target(){
    vector<int> running_animal_vec = return_running_animal_vec();
    int remain_num = running_animal_vec.size();   // 残りの動物の数, たまにremain_num != pair_numとなってしまう, 絶対にremain_num >= pair_num
    int min_distance_list[remain_num][pair_num];
    rep(i, remain_num){
        rep(j, pair_num){
            min_distance_list[i][j] = 0;
        }
    }

    // 各動物とhuman_pairの最短距離を計算
    rep(i, remain_num){
        int animal_index = running_animal_vec[i];
        rep(j, pair_num){
            int min_distance = INF;
            rep(k, pair_vec_list[j].size()){
                int human_index = pair_vec_list[j][k];
                int distance = calc_distance(animal_vec[animal_index].place, human_vec[human_index].place);
                min_distance = min(distance, min_distance);
            }
            min_distance_list[i][j] = min_distance;
        }
    }

    // ミニマックス戦略
    vector<string> all_vec = make_all_vec(pair_num, 0, remain_num, true);
    string best_combination = "";
    int best_score = INF;
    rep(i, all_vec.size()){
        int score = 0;
        string str = all_vec[i];
        map<int, int> min_distance_map;
        for(int j = 0; j < remain_num; j++) min_distance_map[j] = INF;

        // j桁目のpairがstr[j]のanimalを担当する
        rep(j, pair_num){   // pair_num == str.size()
            min_distance_map[str[j] - '0'] = min(min_distance_map[j], min_distance_list[str[j] - '0'][j]);
        }

        rep(j, remain_num){
            score = max(score, min_distance_map[j]);
        }
        if(score < best_score){
            best_score = score;
            best_combination = str;
        }
    }

    // 出力
    // 全滅させたら-1を出力
    vector<int> ret;
    if(remain_num == 0){
        for(int i = 0; i < pair_num; i++) ret.push_back(-1);
    }
    else{
        for(int i = 0; i < pair_num; i++) ret.push_back(running_animal_vec[best_combination[i] - '0']);
    }

    return ret;
}


void tactics_every_pair(int pair_index){
    int target = pair_target[pair_index];

    // ターゲットがいない時
    if(target == -1) return;   

    Animal target_animal = animal_vec[target];
    Pair<int, int> target_room_pair = return_room_index(target_animal.place);
    vector<int> pair_vec = pair_vec_list[pair_index];
    int human_y = human_vec[pair_vec[0]].place.y;
    
    // targetが道路にいる時
    if(target_room_pair.first == -1){
        string direction = "";
        if(human_y == target_animal.place.y) direction = ".";
        else if(human_y > target_animal.place.y) direction = "U";
        else direction = "D";

        rep(i, pair_vec.size()){
            int human_index = pair_vec[i];
            if(human_y == total_min_y && direction == "U"){   // kill_dog_roomの横に入ってしまった時
                ans_list[human_vec[human_index].number] = ".";
                human_vec[human_index].update(".");
            }
            else{   
                ans_list[human_vec[human_index].number] = direction;
                human_vec[human_index].update(direction);
            }
        }
    }

    // targetが部屋にいる時
    else{
        Room target_room = room_map_list[target_room_pair.first][target_room_pair.second];

        // 閉じ込めに成功したら何もしない
        if(target_room.remain_y.size() == 0){
            rep(i, pair_vec.size()){
                int human_index = pair_vec[i];
                ans_list[human_vec[human_index].number] = ".";
                human_vec[human_index].update(".");   
                return;   // ここでプログラムを終了      
            }
        }

        int target_y = target_room.remain_y[0];

        // 移動する時
        if(human_y != target_y){
            string direction = "";
            if(human_y > target_y) direction = "U";
            else if(human_y < target_y) direction = "D";
            rep(i, pair_vec.size()){
                int human_index = pair_vec[i];
                ans_list[human_vec[human_index].number] = direction;
                human_vec[human_index].update(direction);
            }
        }

        // 移動せずに壁を置く時
        else{  
            // 誰が壁を置かないといけないのか
            int target_x_left = target_room.min_x - 1;
            int target_x_right = target_room.max_x + 1;
            int left_index = -1;
            int right_index = -1;
            rep(i, pair_vec.size()){
                if(human_vec[pair_vec[i]].place.x == target_x_left) left_index = pair_vec[i];
                else if(human_vec[pair_vec[i]].place.x == target_x_right) right_index = pair_vec[i];
            }

            // 壁をおけるかどうかを確認する
            bool point = true;
            if(target_x_left != -1){
                if(judge_install(human_vec[left_index].place, "r") == false) point = false;
            }
            if(target_x_right != W){
                if(judge_install(human_vec[right_index].place, "l") == false) point = false;
            }
            if(target_room.must_open == true) point = false;   // この部屋を閉じると分断されてしまう

            // 行動を出力
            if(point == true){   // 壁をおけるとき
                rep(i, pair_vec.size()){
                    int human_index = pair_vec[i];
                    if(human_index == left_index){
                        ans_list[human_vec[human_index].number] = "r";
                        human_vec[human_index].update("r");
                    }
                    else if(human_index == right_index){
                        ans_list[human_vec[human_index].number] = "l";
                        human_vec[human_index].update("l");
                    }
                    else{
                        ans_list[human_vec[human_index].number] = ".";
                        human_vec[human_index].update(".");
                    }
                }
            }
            else{   // 壁をおけない時
                rep(i, pair_vec.size()){
                    int human_index = pair_vec[i];
                    ans_list[human_vec[human_index].number] = ".";
                    human_vec[human_index].update(".");         
                }
            }
        }
    }
}


void chase_animals(){
    while(t < T){
        pair_target = decide_target();   // targetは毎ターン更新する
        for(int i = 0; i < pair_num; i++) tactics_every_pair(i);
        cout << make_ans() << endl;
        update();
    }
}


int main(){
    // 適当に初期化
    rep(i, H){
        rep(j, W){
            wall_field[i][j] = false;
        }
    }
    restart_field();
    
    // 入力1
    cin >> n;
    rep(i, n){
        int a, b, c;
        cin >> a >> b >> c;   a--;   b--;
        Place place(a, b);
        Animal animal(i, c, place);
        animal_vec.push_back(animal);
        animal_field[a][b][c]++;
        if(c == 4) dog_count++;
    }
    
    // 入力2
    cin >> m;
    rep(i, m){
        int a, b;
        cin >> a >> b;   a--;   b--;
        Place place(a, b);
        Human human(i, place);
        human_vec.push_back(human);
    }

    // 入力によってパラメータを調整
    if(dog_count >= limit_dog_count){
        row_wall_vec = dog_row_wall_vec_vec[m - 5];
        col_road_vec = col_road_vec_vec[m - 5];   // 変更する可能性あり
    }
    else{
        row_wall_vec = row_wall_vec_vec[m - 5];
        col_road_vec = col_road_vec_vec[m - 5];
    }
    pair_num = int(m / col_road_vec.size());
    first_place_vec = first_place_vec_list[pair_num];

    // 行動
    // 犬を最初に処理する
    if(dog_count >= limit_dog_count) kill_dogs();
    else phase++;   // kill_dogsを行わないのでphaseをここで進める

    // 仕切りを作る
    make_walls();

    // 動物を閉じ込めていく
    confine_animals();

    // 動物が少なくなったら、担当を決めて狙い撃ちにする
    chase_animals();
}
