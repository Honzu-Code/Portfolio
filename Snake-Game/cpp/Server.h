#ifndef SERVER
#define SERVER

#define MYSQL_url "tcp://127.0.0.1:3306"
#define MYSQL_user "test"
#define MYSQL_pwd "LovePy$1"
#define MYSQL_schema "snakes"

#define SERVER_SNAKE_CAN_COLLIDE_ITSELF true
#define SERVER_KILLED_SNAKE_FOOD_DENSITY 15 // one per 20 px
#define SERVER_MIN_FOOD_PER_SNAKE 10
#define SERVER_KEEP_OBJECT_DISTANCE 900
#define SERVER_SPAWN_MIN_FOOD_DISTANCE 300
#define SERVER_SPAWN_MAX_FOOD_DISTANCE 750
#define SERVER_SNAKE_EAT_DISTANCE 20
#define SERVER_BULLET_KILL_DISTANCE 10
#define VISIBLE_DISTANCE_RADIUS 800

#define EVENT_NEW_SNAKE     1
#define EVENT_NEW_FOOD      2
#define EVENT_NEW_BULLET    3
#define EVENT_GAME_BORDER   4
#define EVENT_FOLLOW_SNAKE  16
#define EVENT_SNAKE_TICK    17
#define EVENT_BULLET_TICK   18
#define EVENT_FOOD_TICK     19
#define EVENT_REMOVE_SNAKE  32
#define EVENT_REMOVE_FOOD   33
#define EVENT_REMOVE_BULLET 34
#define EVENT_YOU_DIED      48
#define EVENT_SCOREBOARD    64

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Point.h"
#include "Vector.h"
#include "Food.h"
#include "Bullet.h"
#include "Snake.h"
#include "Rect.h"

#include <map>
#include <exception>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <string>

#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <cppconn/prepared_statement.h>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using std::cout;
using std::endl;
using std::string;
using std::thread;
using namespace sql;

std::vector<string> players;

int levels[100] = {0,100,200,300,500,800,1300,2000,3000,5000,8000,13000,21000,32000,44000,57000,
72000,89000,109000,131000,156000,183000,213000,245000,280000,320000,365000,415000,
470000,530000,595000,665000,740000,820000,905000,995000,1090000,1190000,1295000,1405000,
1520000,1640000,1770000,1910000,2060000,2220000,2390000,2570000,2760000,2960000,
3170000,3390000,3630000,3880000,4140000,4420000,4720000,5040000,5400000,5780000,6180000,6600000,7040000,
7500000,7980000,8480000,9010000,9570000,10160000,10800000,11480000,12210000,12990000,
13840000,14740000,15740000,16840000,18040000,19340000,20740000,22240000,23840000,25540000,27340000,29240000,
31240000,33440000,35840000,38440000,41740000,45740000,50240000,55240000,61240000,68240000,76240000,85240000,98240000,114240000,134240000};



struct UserData{
    bool guest = false;
    string user;
    string nick = SNAKE_DEFAULT_NAME;
    string skin = SNAKE_DEFAULT_SKIN;
    string key;
    int id;


    void set_Online()
    {
        if(guest)
            return;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::Driver *driver;
        driver = get_driver_instance();
        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        con->setSchema(MYSQL_schema);
        pstmt = con->prepareStatement("UPDATE players SET online=1 WHERE id=?");
        pstmt->setInt(1,this->id);
        pstmt->executeUpdate();
        delete pstmt;
        delete con;
    }
    bool can_Play()
    {
        if(guest)
            return true;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        driver = get_driver_instance();
        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        con->setSchema(MYSQL_schema);
        pstmt = con->prepareStatement("SELECT * FROM players WHERE id=?");
        pstmt->setInt(1,this->id);
        res = pstmt->executeQuery();
        if(res->next())
        {
            if(res->getInt("online"))
               {
                  delete pstmt;
                  delete con;
                  delete res;
                  return false;
               }
            else
              {
                  delete pstmt;
                  delete con;
                  delete res;
                  return true;
              }
        }
        delete pstmt;
        delete con;
        delete res;
        return false;
    }
    static bool isKeyValid(string key){
        //cout << "Begin of function isKeyValid" << endl;
        //cout << "Key = " << key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        //cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        //cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        //cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        //cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE keyplayer=?");
        //cout << "After initialisation of pstmt" << endl;

        pstmt->setString(1,key);
        //cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        //cout << "After initialisation of res" << endl;

        if(res->next())
          {
          //cout << "After res->next() and delete 3 pointers" << endl;
          //cout << "End of function: isKeyValid" << endl << endl;
          //string player = res->getString("nick");
          //if(std::find(players.begin(), players.end(), player) != players.end())
          //return false;
          //players.push_back(player);
          delete pstmt;
          delete con;
          delete res;
          return true;}
        else
         {
          delete pstmt;
          delete con;
          delete res;
          //cout << "After else and delete 3 pointers" << endl;
          //cout << "End of function: isKeyValid" << endl << endl;
          return false;}

    }

    UserData(){}

    UserData(string key){
        if(UserData::isKeyValid(key)){
            this->loadData(key);
            this->key = key;
            this->guest = false;
        }else if(key.size() <= 20){
            this->nick = key;
            this->guest = true;
        }
    }

    void loadData(string key){
        // use key to set username, nick and skin from mysql
        //cout << "Begin of constructor UserData" << endl;
        //cout << "Key = " << key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        //cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        //cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        //cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        //cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE keyplayer=?");
        //cout << "After initialisation of pstmt" << endl;

        pstmt->setString(1,key);
        //cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        //cout << "After initialisation of res" << endl;

        if(res->next())
        {
          //cout << "Before res->next()" << endl;

          this->user = res->getString("login");
          //cout << "After this->user " << this->user << endl;

          this->skin = res->getString("snakeskin");
          //cout << "After this->skin " << this->skin << endl;

          this->nick = res->getString("nick");
          //cout << "After this->nick "<< this->nick << endl;

          this->key = res->getString("keyplayer");

          this->id = res->getInt("id");
        }
        //cout << "After res->next()" << endl;
        delete pstmt;
        delete con;
        delete res;
        //cout << "After delete pointers" << endl;
        //cout << "End of contructor UserData" << endl << endl;

    }

    void save_score(Snake snake){
        if(this->guest){
            cout << "Guests have no score tracking." << endl;
            return;
        }
        //cout << "Begin of save_score" << endl;
        //cout << "this->key = " << this->key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::ResultSet *res2;
        sql::ResultSet *res3;
        sql::Driver *driver;
        //cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        //cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        //cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        //cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE id=?");
        //cout << "After initialisation of pstmt" << endl;

        //cout << "This-user = " << this->nick << endl;
        pstmt->setInt(1,this->id);
        //cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        //cout << "After initialisation of res" << endl;

        int score = 0;
        int kills = 0;
        int deaths = 0;
        int which = 0;
        int new_level = 0;
        int pointsranking = 0;
        string status = "";
        long long int vip_current_time = 0;
        long long int current_time = 0;

        //cout << "After deklarations of 3 variables,before res->next()" << endl;

        if(res->next())
        {
            //cout << "Begin of res->next()" << endl;

            score = res->getInt("pointslevel");
            //cout << "After score = " << score << endl;

            kills = res->getInt("win");
            //cout << "After kills = " << score << endl;

            deaths = res->getInt("defeat");
            //cout << "After deaths = " << deaths << endl;

            status = res->getString("status");


            pstmt = con->prepareStatement("SELECT TO_SECONDS(?)");
            pstmt->setString(1,res->getString("timevip"));
            res2 = pstmt->executeQuery();
            res2->next();

            vip_current_time = std::stoll(res2->getString(1));

            pstmt = con->prepareStatement("SELECT TO_SECONDS(NOW())");
            res3 = pstmt->executeQuery();
            res3->next();

            current_time = std::stoll(res3->getString(1));

            //cout << "current time = " << current_time << endl;

            if(vip_current_time > current_time)
              score += int(snake.score) * 2;
            else
              {
                  score += int(snake.score);
                  status = "Player";
              }

            kills += snake.kills;
            deaths += 1;
           for(int level = 0; level<100; level++)
           {
               if(score < levels[level])
               {
                   new_level = which;
                   break;
               }
               which++;
           }
           if(vip_current_time > current_time)
             pointsranking = (kills * 40) - (deaths * 10);
           else
             pointsranking = (kills * 20) - (deaths * 10);

           if(pointsranking < 0)
              pointsranking = 0;

            cout << "After maths" << endl;
            delete res;
            delete res2;
            delete res3;
        }
        //cout << "Before initialisation of pstmt" << endl;
        pstmt = con->prepareStatement("UPDATE players SET pointslevel=?,win=?,defeat=?,level=?,pointsranking=?,status=?,online=0 WHERE id=?");
        //cout << "After initialisation of pstmt" << endl;

        pstmt->setInt(1,score);
        //cout << "After setInt 1 = " << score << endl;

        pstmt->setInt(2,kills);
        //cout << "After setInt 2 = " << kills << endl;

        pstmt->setInt(3,deaths);
        //cout << "After setInt 3 = " << deaths << endl;

        pstmt->setInt(4,new_level);

        pstmt->setInt(5,pointsranking);

        pstmt->setString(6,status);

        pstmt->setInt(7,this->id);
        //cout << "After setString 4 = " << this->id << endl;

        pstmt->executeUpdate();
        //cout << "After executeUpdate()" << endl;

        delete pstmt;
        delete con;
        //cout << "After deletes of pointers" << endl;
        //cout << "End of save_score" << endl << endl;
    }

};


class Server
{
  typedef std::map<connection_hdl, int, std::owner_less<connection_hdl>> con_list;
  typedef std::map<connection_hdl, UserData, std::owner_less<connection_hdl>> user_list;
  server m_server;
  con_list m_connections;
  user_list users;
  vector<thread*> webSocketThreads;

  vector<thread*> mathThreads; // I'll implement this later
public:
  vector<Snake> snakes;
  vector<Food> food;
  vector<Bullet> bullets;
  Rect border = Rect(0, 0, 4000, 4000);

  Server(uint16_t port) {
    srand(time(NULL));
    m_server.init_asio();

    m_server.set_open_handler(bind(&Server::on_open,this,::_1));
    m_server.set_close_handler(bind(&Server::on_close,this,::_1));
    m_server.set_message_handler(bind(&Server::on_message,this,::_1,::_2));
    m_server.set_fail_handler(bind(&Server::on_fail,this,::_1));
    m_server.clear_access_channels(websocketpp::log::alevel::all);
    cout << "Snake Server listening at port: " << port << endl;
    m_server.listen(port);
    m_server.start_accept();
    this->webSocketThreads.push_back(new thread(&server::run, &m_server));

  }

  void on_open(connection_hdl hdl) {
    m_connections[hdl] = -1;
  }

  void on_fail(connection_hdl hdl)
  {
      cout << "connection fail" << endl;
  }

  void on_close(connection_hdl hdl) {
    auto it = m_connections.find(hdl);
    if (it == m_connections.end()) {
        throw std::invalid_argument("No data available for session");
    }
    try
    {
    int& id = it->second;
    int snakeIndex = this->find_snake(id);
    //cout << "Here on_close!" << endl;
    m_connections.erase(hdl);
    //cout << "Here on_close2!" << endl;
    //cout << "Here on_close3!" << endl;
	users.erase(hdl);
    //cout << "Here on_close4!" << endl;
    if(snakeIndex != -1)
      this->snakes[snakeIndex].alive = false;}
    catch (const websocketpp::exception &e) {//by safety, I just go with `const std::exception` so that it grabs any potential exceptions out there.
      std::cout << "Exception in method foo() because: " << e.what() /* log the cause of the exception */ << std::endl;
      }
  }

  void close_connection(connection_hdl hdl){
    // https://github.com/zaphoyd/websocketpp/issues/545
    this->m_server.pause_reading(hdl);
    cout << "Forcefully closing a connection!" << endl;
    this->m_server.close(hdl,websocketpp::close::status::force_tcp_drop, "");
    this->on_close(hdl);
  }

  void on_message(connection_hdl hdl, server::message_ptr msg) {
    auto it = m_connections.find(hdl);
    if (it == m_connections.end()) {
      throw std::invalid_argument("No data available for session");
    }
    handle_message(hdl, it->second, msg->get_payload());
  }

  void broadcast (char event, string data){
    for(int i = 0; i < (int) this->snakes.size(); i++){
      if(!this->snakes[i].alive)
        continue;
      this->send(this->snakes[i], event, data);
    }
  }

  void rangeBroadcast(Food food){
    for(int i = 0; i < (int) this->snakes.size(); i++){
      int cpoints = this->snakes[i].controlPoints.size();
      if(cpoints < 2 || !this->snakes[i].alive)
        continue;
      Point head = this->snakes[i].controlPoints.back();
      Point prevHead = this->snakes[i].controlPoints[cpoints - 2];
      Point position(food.x, food.y);
      Point prevPosition(food.lastX, food.lastY);
      float distance = position.distance(head);
      float lastDistance = prevPosition.distance(prevHead);
      float v = VISIBLE_DISTANCE_RADIUS;
      if(distance <= v && lastDistance > v){
        this->send(this->snakes[i], EVENT_NEW_FOOD, food.encode());
      }else if(distance <= v){
        // this->send(this->snakes[i], EVENT_FOOD_TICK, food.encode());
      }else if(distance > v && lastDistance <= v){
        this->send(this->snakes[i], EVENT_REMOVE_FOOD, food.encodeId());
      }
    }
  }

  void rangeBroadcast(Bullet bullet){
    for(int i = 0; i < (int) this->snakes.size(); i++){
      int cpoints = this->snakes[i].controlPoints.size();
      if(cpoints < 2 || !this->snakes[i].alive)
        continue;
      Point head = this->snakes[i].controlPoints.back();
      Point prevHead = this->snakes[i].controlPoints[cpoints - 2];
      Point position(bullet.x, bullet.y);
      Point prevPosition(bullet.lastX, bullet.lastY);
      float distance = position.distance(head);
      float lastDistance = prevPosition.distance(prevHead);
      float v = VISIBLE_DISTANCE_RADIUS;
      if(distance <= v && lastDistance > v){
        this->send(this->snakes[i], EVENT_NEW_BULLET, bullet.encode());
      }else if(distance <= v){
        // this->send(this->snakes[i], EVENT_BULLET_TICK, bullet.encode());
      }else if(distance > v && lastDistance <= v){
        this->send(this->snakes[i], EVENT_REMOVE_BULLET, bullet.encodeId());
      }
    }
  }

  void rangeBroadcast(Snake snake){ // don't broadcast snakes with control points < 2
    if(snake.controlPoints.size() < 2){
      std::cout << "Told you, don't rangeBroadcast ";
      std::cout << "snakes with controlPoints.size() < 2" << std::endl;
      // This can save us time if we let that kind of bug somewhere.
      return;
    }

    for(int i = 0; i < (int) this->snakes.size(); i++){
      int cpoints = this->snakes[i].controlPoints.size();
      if(cpoints < 2 || !this->snakes[i].alive)
        continue;
      Point head = this->snakes[i].controlPoints.back();
      Point prevHead = this->snakes[i].controlPoints[cpoints - 2];

      Point position = snake.controlPoints.back();
      Point prevPosition = snake.controlPoints[snake.controlPoints.size() - 2];
      float distance = position.distance(head);
      float lastDistance = prevPosition.distance(prevHead);
      float v = VISIBLE_DISTANCE_RADIUS + snake.length;
      if(distance <= v && lastDistance > v){
        this->send(this->snakes[i], EVENT_NEW_SNAKE, snake.encode());
      }else if(distance <= v){
        this->send(this->snakes[i], EVENT_SNAKE_TICK, snake.encodeDataFromTick());
      }else if(distance > v && lastDistance <= v){
        this->send(this->snakes[i], EVENT_REMOVE_SNAKE, snake.encodeId());
      }
    }
  }

  // use this one when spawning things, because others may not send correct spawn message.
  void rangeBroadcast(char event, string data, Point position, float extraDistance = 0){
    for(int i = 0; i < (int) this->snakes.size(); i++){
      int cpoints = this->snakes[i].controlPoints.size();
      if(cpoints < 1 || !this->snakes[i].alive)
        continue;
      Point head = this->snakes[i].controlPoints.back();
      float distance = position.distance(head);
      float v = VISIBLE_DISTANCE_RADIUS;
      if(extraDistance > 0){
        v += extraDistance;
      }
      if(distance <= v){
        this->send(this->snakes[i], event, data);
      }
    }
  }

  void send (int id, char event, string data = ""){
    auto it = m_connections.begin();
    while (it != m_connections.end()) {
      if(it->second == id){
        m_server.send(it->first, event + data, websocketpp::frame::opcode::binary);
        return;
      }
      it++;
    }
  }

  void send (Snake &snake, char event, string data = ""){
    if(snake.alive){
      m_server.send(snake.hdl, event + data, websocketpp::frame::opcode::binary);
    }
  }

  bool is_user_authorized(connection_hdl hdl){
    auto it = users.find(hdl);
    return it != users.end();
  }

  void create_snake(string name, string skin, connection_hdl hdl);
  void create_snake(connection_hdl hdl);
  void handle_message(connection_hdl hdl, int id, string message){
    int index = this->find_snake(id);
    if(index == -1){
		if(!this->is_user_authorized(hdl)){
            cout << "Authorization!" << endl;
            if(message.size() <= 20){ // guest
                string &name = message;
                cout << "Guest." << endl;
                UserData data = UserData(name);
                users[hdl] = data;
            }else if(UserData::isKeyValid(message)){
                string &key = message;
                cout << "User." << endl;
                UserData data = UserData(key);
                users[hdl] = data;
            }
			return;
		}
		if(message == "respawn"){
            if(users[hdl].can_Play())
            {
              users[hdl].set_Online();
              UserData data = users[hdl];
              this->create_snake(data.nick, data.skin, hdl);
            }
        }
      return;
    }

    const char* cmsg = message.c_str();
    float float1 = 0;
    switch(cmsg[0]){
      case 's':
        if(this->snakes[index].can_shoot()){
          Bullet b = this->snakes[index].spawn_bullet();
          this->bullets.push_back(b);
          this->rangeBroadcast(EVENT_NEW_BULLET, b.encode(), (Point) b);
          // we shall move this out, or hackers will have shotguns.
        }
        break;

      case 'd':
        if(message.size() != 5){
          cout << "Snake " << id << " sends sus direction len " << (message.size() - 1) << endl;
          break;
        }

        memcpy(&(float1), cmsg + 1, sizeof(float1));
        this->snakes[index].direction = float1;
        break;

      default:
        cout << "Snake " << id << " sends sus prefix " << cmsg[0] << endl;
        break;
    }
  }
  bool snake_exists(int id){
    for(int i = 0; i < (int) snakes.size(); i++){
      if(snakes[i].id == id){
        return true;
      }
    }
    return false;
  }
  int find_snake(int id){
    for(int i = 0; i < (int) snakes.size(); i++){
      if(snakes[i].id == id){
        return i;
      }
    }
    return -1;
  }
  void loop();
  int find_colliding(Snake &snake);
  bool do_lines_cross(Point line1_a,Point line1_b,Point line2_a,Point line2_b);
  void respawn_snake(Snake &snake);
  void kill(Snake &snake, string inform = "");
  void deleteSnake(Snake &snake);
  void clearDeadSnakes();
  void turn_snake_to_food(Snake &snake);
  bool apply_border(Snake &snake);
  bool keep_food(Food &food);
  void spawn_food();
  void create_food(Point position,Vector movement, float size);
  bool keep_bullet(Bullet &bullet);
  bool inDistance(float x, float y, float ax, float ay, float bx, float by, float s);
  void updateScoreboard();
  std::string getScoreboard();
  std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdate = std::chrono::high_resolution_clock::now();
};

void Server::create_snake(connection_hdl hdl){
  this->create_snake(SNAKE_DEFAULT_NAME, SNAKE_DEFAULT_SKIN, hdl);
}

void Server::create_snake(string name, string skin, connection_hdl hdl)
{
  Snake snake;
  if(name != SNAKE_DEFAULT_NAME || skin != SNAKE_DEFAULT_SKIN)
    snake = Snake(name, skin);
  else
    snake = Snake();
  snake.direction = 2 * M_PI * (rand() / (float) RAND_MAX);
  int startX = this->border.x + this->border.w * (0.05 + 0.9 * (rand() / (float) RAND_MAX));
  int startY = this->border.y + this->border.h * (0.05 + 0.9 * (rand() / (float) RAND_MAX));
  Point start(startX, startY);
  snake.controlPoints.push_back(start);
  snake.move();
  Point head = snake.controlPoints.back();
  m_connections[hdl] = snake.id;
  snake.hdl = hdl;
  snake.userData = &users[hdl];

  for(uint i = 0; i < this->snakes.size(); i++){
    Point otherhead = this->snakes[i].controlPoints.back();
    float distance = otherhead.distance(head);
    float v = VISIBLE_DISTANCE_RADIUS + snake.length + this->snakes[i].length;
    if(distance <= v)
      this->send(snake, EVENT_NEW_SNAKE, this->snakes[i].encode());
  }

  for(uint i = 0; i < this->food.size(); i++){
    Point food = (Point) this->food[i];
    float distance = food.distance(head);
    float v = VISIBLE_DISTANCE_RADIUS + this->food[i].length;
    if(distance <= v)
      this->send(snake, EVENT_NEW_FOOD, this->food[i].encode());
  }

  for(uint i = 0; i < this->bullets.size(); i++){
    Point bullet = (Point) this->bullets[i];
    float distance = bullet.distance(head);
    float v = VISIBLE_DISTANCE_RADIUS;
    if(distance <= v)
      this->send(snake, EVENT_NEW_BULLET, this->bullets[i].encode());
  }

  this->snakes.push_back(snake);
  this->rangeBroadcast(EVENT_NEW_SNAKE, snake.encode(), start, snake.length);
  this->send(snake, EVENT_FOLLOW_SNAKE, snake.encodeId());
  this->send(snake, EVENT_GAME_BORDER, this->border.encode());
}

void Server::loop()
{
  // auto start = std::chrono::high_resolution_clock::now();

  this->clearDeadSnakes();

  for(int snake = 0; snake < (int) this->snakes.size(); snake++)
     this->snakes[snake].tick();

  for(int food = 0; food < (int) this->food.size(); food++)
     this->food[food].tick();

  for(int bullet = 0; bullet < (int) this->bullets.size(); bullet++)
     this->bullets[bullet].tick();

  this->clearDeadSnakes();

  for(int snake = 0; snake < (int) this->snakes.size(); snake++){
    if(this->apply_border(this->snakes[snake])){
       this->kill(this->snakes[snake], "You left the battle zone.");
    }
  }

  for(int snake = 0; snake < (int) this->snakes.size(); snake++){
    int collidingId = this->find_colliding(this->snakes[snake]);
    if(collidingId != -1){
      int killer_index = this->find_snake(collidingId);
      int lenDifference = this->snakes[killer_index].length - this->snakes[snake].length;
      if(lenDifference > 120){
        lenDifference = 120;
      }else if(lenDifference < -150){
        lenDifference = -150;
      }
      if(killer_index != snake){
		  this->snakes[killer_index].kills++;
		  this->snakes[killer_index].score += 75 - lenDifference / 2;
	  }
      this->kill(this->snakes[snake], "You crashed into " + this->snakes[killer_index].name);
    }
  }

  for(int food = this->food.size() - 1; food >= 0; food--)
    if(!this->keep_food(this->food[food])){
      this->rangeBroadcast(EVENT_REMOVE_FOOD, this->food[food].encodeId(), Point(this->food[food].x, this->food[food].y), 80);
      this->food.erase(this->food.begin() + food);
    }


  this->clearDeadSnakes();
  for(int bullet = this->bullets.size() - 1; bullet >= 0; bullet--)
    if(!this->keep_bullet(this->bullets[bullet])){
      this->rangeBroadcast(EVENT_REMOVE_BULLET, this->bullets[bullet].encodeId(), Point(this->bullets[bullet].x, this->bullets[bullet].y));
      this->bullets.erase(this->bullets.begin() + bullet);
    }

  this->clearDeadSnakes();
  while (this->food.size() < this->snakes.size() * SERVER_MIN_FOOD_PER_SNAKE){
    this->spawn_food();
  }

  this->clearDeadSnakes();
  for(int i = 0; i < (int) this->snakes.size(); i++)
    this->rangeBroadcast(this->snakes[i]);
  for(uint i = 0; i < (uint) this->food.size(); i++)
    this->rangeBroadcast(this->food[i]);
  for(uint i = 0; i < (uint) this->bullets.size(); i++)
    this->rangeBroadcast(this->bullets[i]);

  this->updateScoreboard();

  // auto finish = std::chrono::high_resolution_clock::now();
  // std::chrono::duration<double> elapsed = finish - start;
  // std::cout << "Elapsed time mathematic + broadcast: " << elapsed.count() << " s\n";
}

bool Server::apply_border(Snake &snake)
{
  return !this->border.contains(snake.controlPoints.back());
}

int Server::find_colliding(Snake &snake)
{
  for(int i = 0; i < (int) this->snakes.size(); i++)
  {
    #if !SERVER_SNAKE_CAN_COLLIDE_ITSELF
      if(snake == this->snakes[i])
         continue;
    #endif

    if(snake.is_colliding(this->snakes[i])){
      return this->snakes[i].id;
    }
  }
  return -1;
}

void Server::respawn_snake(Snake &snake)
{
  this->turn_snake_to_food(snake);
  this->rangeBroadcast(EVENT_REMOVE_SNAKE, snake.encode(), snake.controlPoints.back(), snake.length);
  snake.reset();
  snake.direction = 2 * M_PI * (rand() / (float) RAND_MAX);
  int startX = this->border.x + this->border.w * (0.05 + 0.9 * (rand() / (float) RAND_MAX));
  int startY = this->border.y + this->border.h * (0.05 + 0.9 * (rand() / (float) RAND_MAX));
  snake.controlPoints.push_back(Point(startX, startY));
  snake.move();
  this->rangeBroadcast(EVENT_NEW_SNAKE, snake.encode(), snake.controlPoints.back(), snake.length);
}

void Server::kill(Snake &snake, string message)
{
  if(snake.alive){
    // todo: send score to server.
  }

  snake.alive = false;
  if(message.size())
    this->send(snake.id, EVENT_YOU_DIED, message);
}

void Server::deleteSnake(Snake &snake){
  auto it = m_connections.begin();
  while (it != m_connections.end()) {
    int& id = it->second;

    if(snake.id == id){
      it->second = -1;
      break;
    }
    it++;
  }

  for(int i = 0; i < (int) this->snakes.size(); i++){
    if(this->snakes[i] == snake){
      this->turn_snake_to_food(snake);
      ((UserData*) (snake.userData))->save_score(snake);
      this->snakes.erase(this->snakes.begin() + i);
      break;
    }
  }
}

void Server::clearDeadSnakes(){
  int counter = 0;
  vector<string> encodedRemovedSnakeIds;
  vector<Point> removedSnakeHeads;
  vector<int> removedSnakeLengths;

  for(int i = this->snakes.size() - 1; i >= 0; i--){
    if(!this->snakes[i].alive){
      encodedRemovedSnakeIds.push_back(this->snakes[i].encodeId());
      removedSnakeHeads.push_back(this->snakes[i].controlPoints.back());
      removedSnakeLengths.push_back(this->snakes[i].length);
      counter++;
      this->deleteSnake(this->snakes[i]);
    }
  }

  for(int i = 0; i < counter; i++){
      this->rangeBroadcast(EVENT_REMOVE_SNAKE,
                           encodedRemovedSnakeIds[i],
                           removedSnakeHeads[i],
                           removedSnakeLengths[i] + 50);
  }
}

void Server::turn_snake_to_food(Snake &snake)
{
  int count = snake.length / SERVER_KILLED_SNAKE_FOOD_DENSITY;
  float step = snake.length / (float) count;
  float passed = 0;

  for(int i = 1; i < (int) snake.controlPoints.size() - 1; i++)
  {
    Point p1 = snake.controlPoints[i - 1];
    Point p2 = snake.controlPoints[i];
    Point v(p2.x - p1.x, p2.y - p1.y);
    float direction = atan2(v.y, v.x);
    float unprocessedLength = hypot(v.x, v.y);
    float processedLength = 0;
    while(unprocessedLength > 0){
      if(passed + unprocessedLength < step){
        passed += unprocessedLength;
        break;
      }
      processedLength += step - passed;
      unprocessedLength -= step - passed;
      passed = 0;

      Vector amplitude(2 * M_PI * (rand() / (float) RAND_MAX), 10 * (rand() / (float) RAND_MAX));
      Point position(p1.x, p1.y);
      Vector offset(direction, processedLength);
      offset.apply_on(position);
      amplitude.apply_on(position);
      this->create_food(position, Vector(0, 0), 3 + (rand() % 2));
    }
  }
}

bool Server::keep_food(Food &food)
{
  bool keep = false;
  for(int snakeIndex = 0; snakeIndex < (int) this->snakes.size(); snakeIndex++)
  {
    Snake& snake = this->snakes[snakeIndex];
    Point& camera = snake.controlPoints.back();
    float distance = hypot(camera.x - food.x, camera.y - food.y);

    if(distance > SERVER_KEEP_OBJECT_DISTANCE)
      continue;
    keep = true;

    if(distance < FOOD_DODGE_DISTANCE){
      float direction = atan2(food.y - camera.y, food.x - camera.x);
      food.dodge_to(direction);
    }

    if(distance < SERVER_SNAKE_EAT_DISTANCE){
      snake.consume_food(food);
      return false;
    }
  }
  return keep;
}

void Server::spawn_food()
{
  if (!this->snakes.size())
    return;
  int index = rand() % this->snakes.size();
  vector<Point> points = this->snakes[index].controlPoints;
  Point point = points.back();
  Point position(point.x,point.y);
  int difference = SERVER_SPAWN_MAX_FOOD_DISTANCE - SERVER_SPAWN_MIN_FOOD_DISTANCE;
  int distance = SERVER_SPAWN_MIN_FOOD_DISTANCE + rand() % difference;
  Vector random_vector(2 * M_PI * (rand() / (float) RAND_MAX), distance);
  random_vector.apply_on(position);
  Vector movement(2 * M_PI * (rand() / (float) RAND_MAX),rand() % 10 + 1);
  int size = rand() % 7 + 1;
  this->create_food(position, movement, size);
}

void Server::create_food(Point position, Vector movement, float size)
{
  Food food(position, movement, size);
  this->food.push_back(food);
  this->rangeBroadcast(EVENT_NEW_FOOD, food.encode(), position);
}

bool Server::keep_bullet(Bullet& bullet)
{
  bool keep = false;
  for(int snakeIndex = 0; snakeIndex < (int) this->snakes.size(); snakeIndex++)
  {
    Snake& snake = this->snakes[snakeIndex];
    Point& camera = snake.controlPoints[snake.controlPoints.size() - 1];
    float distance = hypot(camera.x - bullet.x, camera.y - bullet.y);

    if(bullet.owner != snake.id && distance < SERVER_BULLET_KILL_DISTANCE + bullet.length / 2)
    {
      // i'll make this if better next time.
      int killer_index = this->find_snake(bullet.owner);
      if(killer_index != -1){
        this->snakes[killer_index].kills++;
        float distance = this->snakes[killer_index].controlPoints.back().distance(camera);
        if(distance > 1000){
            distance = 1000; // so max bonus score is 100
        }
        this->snakes[killer_index].score += 25 + distance / 10;
        this->kill(snake, "You were shot by " + this->snakes[killer_index].name);
      }else{
        this->kill(snake, "The guy who sniped you is already dead.");
      }
      return false;
    }

    if(distance > SERVER_KEEP_OBJECT_DISTANCE)
      continue;

    keep = true;

    if(distance > snake.length)
      continue;

    //if(bullet.owner != snake.id)
    for(int i = 1; i < (int) snake.controlPoints.size() - 1; i++)
    {
      Point p1 = snake.controlPoints[i - 1];
      Point p2 = snake.controlPoints[i];
      int r = bullet.length;
      if(this->inDistance(bullet.x, bullet.y, p1.x, p1.y, p2.x, p2.y, r))
        return false;
    }
  }
  return keep;
}

bool Server::inDistance(float x, float y, float ax, float ay, float bx, float by, float s)
{
  float a = ay - by;
  float b = bx - ax;
  float c = ax * by - ay * bx;
  if(hypot(a,b) != 0)
  {
    float d = abs((a * x + b * y + c) / hypot(a,b));
    if(x < fmin(ax,bx) - s)
       return false;
    if(y < min(ay,by) - s)
       return false;
    if(x > max(ax,bx) + s)
       return false;
    if(y > max(ay,by) + s)
       return false;
    return d <= s;
  }
  return hypot(ax-x, ay-y) <= s;
}

void Server::updateScoreboard(){
  auto now = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = now - this->lastUpdate;
  auto delay = std::chrono::milliseconds(1000);
  if(elapsed > delay){
    std::string scoreboardData = this->getScoreboard();
    this->broadcast(EVENT_SCOREBOARD, scoreboardData);
    this->lastUpdate = now;
  }
}

std::string Server::getScoreboard(){
  std::string scoreboardData = "";
  for(int i = 0; i < (int) this->snakes.size(); i++){
    if(!this->snakes[i].alive){
      continue;
    }
    scoreboardData += this->snakes[i].encodeScore();
  }
  return scoreboardData;
}


#endif
