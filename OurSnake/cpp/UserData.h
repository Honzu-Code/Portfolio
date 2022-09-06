#ifndef USERDATA
#define USERDATA

#define MYSQL_url "tcp://127.0.0.1:3306"
#define MYSQL_user "root"
#define MYSQL_pwd "qOw3JuP302X6H2wXmj$"
#define MYSQL_schema "snakes"

#include <thread>
#include <string>
#include <iostream>
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
#include <cppconn/prepared_statement.h>

using std::cout;
using std::endl;
using std::string;
using std::thread;
using namespace sql;

struct UserData{
    bool guest = true;
    string user;
    string nick;
    string skin;
    string key;

    static bool isKeyValid(string key){
        cout << "Begin of function isKeyValid" << endl;
        if(key.size() <= 20){
            cout << "User requested guest mode." << endl;
            return true; // guest mode.
        }
        cout << "Key = " << key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE keyplayer=?");
        cout << "After initialisation of pstmt" << endl;

        pstmt->setString(1,key);
        cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        cout << "After initialisation of res" << endl;

        if(res->next())
          {
          delete pstmt;
          delete con;
          delete res;
          cout << "After res->next() and delete 3 pointers" << endl;
          cout << "End of function: isKeyValid" << endl << endl;
          return true;}
        else
         {
          delete pstmt;
          delete con;
          delete res;
          cout << "After else and delete 3 pointers" << endl;
          cout << "End of function: isKeyValid" << endl << endl;
          return false;}

    }

    UserData(){}

    UserData(string key){
        if(key.size() <= 20 && UserData::isKeyValid(key)){
            this.loadData(key);
            this.key = key;
            this.guest = false;
        }else if(key.size() <= 20){
            this.guest = true;
            this.nick = key;
        }
    }

    void loadData(string key){
        // use key to set username, nick and skin from mysql
        cout << "Begin of UserData.loadData" << endl;
        cout << "Key = " << key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE keyplayer=?");
        cout << "After initialisation of pstmt" << endl;

        pstmt->setString(1,key);
        cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        cout << "After initialisation of res" << endl;

        if(res->next())
        {
          cout << "Before res->next()" << endl;

          this->user = res->getString("login");
          cout << "After this->user " << this->user << endl;

          this->skin = res->getString("snakeskin");
          cout << "After this->skin " << this->skin << endl;

          this->nick = res->getString("nick");
          cout << "After this->nick "<< this->nick << endl;

          this->key = res->getString("keyplayer");
        }
        cout << "After res->next()" << endl;
        delete pstmt;
        delete con;
        delete res;
        cout << "After delete pointers" << endl;
        cout << "End of contructor UserData" << endl << endl;
    }

    void save_score(Snake snake){
        if(this->guest){
            cout << "Guests have no score tracking." << endl;
            return;
        }
        cout << "Begin of save_score" << endl;
        cout << "this->key = " << this->key << endl;
        sql::PreparedStatement *pstmt;
        sql::Connection *con;
        sql::ResultSet *res;
        sql::Driver *driver;
        cout << "After deklarations pointers" << endl;

        driver = get_driver_instance();
        cout << "After initialization of driver" << endl;

        con = driver->connect(MYSQL_url, MYSQL_user, MYSQL_pwd);
        cout << "After initialisation of con" << endl;

        con->setSchema(MYSQL_schema);
        cout << "After setSchema for con" << endl;

        pstmt = con->prepareStatement("SELECT * FROM players WHERE keyplayer=?");
        cout << "After initialisation of pstmt" << endl;

        cout << "This-user = " << this->key << endl;
        pstmt->setString(1,this->key);
        cout << "After 1 setString for pstmt" << endl;

        res = pstmt->executeQuery();
        cout << "After initialisation of res" << endl;

        int score = 0;
        int kills = 0;
        int deaths = 0;
        int which = 0;
        int new_level = 0;
        int pointsranking = 0;
        cout << "After deklarations of 3 variables,before res->next()" << endl;

        if(res->next())
        {
            cout << "Begin of res->next()" << endl;

            score = res->getInt("pointslevel");
            cout << "After score = " << score << endl;

            kills = res->getInt("win");
            cout << "After kills = " << score << endl;

            deaths = res->getInt("defeat");
            cout << "After deaths = " << deaths << endl;

            score += int(snake.score);
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
           pointsranking = (kills * 20) - (deaths * 10);
           if(pointsranking < 0)
              pointsranking = 0;

            cout << "After maths" << endl;
        }
        cout << "Before initialisation of pstmt" << endl;
        pstmt = con->prepareStatement("UPDATE players SET pointslevel=?,win=?,defeat=?,level=?,pointsranking=? WHERE keyplayer=?");
        cout << "After initialisation of pstmt" << endl;

        pstmt->setInt(1,score);
        cout << "After setInt 1 = " << score << endl;

        pstmt->setInt(2,kills);
        cout << "After setInt 2 = " << kills << endl;

        pstmt->setInt(3,deaths);
        cout << "After setInt 3 = " << deaths << endl;

        pstmt->setInt(4,new_level);

        pstmt->setInt(5,pointsranking);

        pstmt->setString(6,this->key);
        cout << "After setString 4 = " << this->key << endl;

        pstmt->executeUpdate();
        cout << "After executeUpdate()" << endl;

        delete res;
        delete pstmt;
        delete con;
        cout << "After deletes of pointers" << endl;
        cout << "End of save_score" << endl << endl;
    }
};

#endif USERDATA
