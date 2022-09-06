from flask import Flask, render_template, url_for, request, redirect, session, jsonify, make_response,send_from_directory
import os
from flask_bcrypt import Bcrypt
from flaskext.mysql import MySQL
from itsdangerous import URLSafeTimedSerializer, SignatureExpired
import random
import string
import json
from app_config import set_app_config, default_app_port
from datetime import datetime, timedelta

app = Flask(__name__, static_url_path='/static')

app.secret_key = os.urandom(20)

mysql = MySQL()

set_app_config(app)
# app.config['MONGO_URI'] = 'mongodb://localhost:27017/myDatabase'

# mongo = PyMongo(app)
bcrypt = Bcrypt(app)
mysql.init_app(app)

s = URLSafeTimedSerializer(app.secret_key)

levels = [0,100,200,300,500,800,1300,2000,3000,5000,8000,13000,21000,32000,44000,57000,
72000,89000,109000,131000,156000,183000,213000,245000,280000,320000,365000,415000,
470000,530000,595000,665000,740000,820000,905000,995000,1090000,1190000,1295000,1405000,
1520000,1640000,1770000,1910000,2060000,2220000,2390000,2570000,2760000,2960000,
3170000,3390000,3630000,3880000,4140000,4420000,4720000,5040000,5400000,5780000,6180000,6600000,7040000,
7500000,7980000,8480000,9010000,9570000,10160000,10800000,11480000,12210000,12990000,
13840000,14740000,15740000,16840000,18040000,19340000,20740000,22240000,23840000,25540000,27340000,29240000,
31240000,33440000,35840000,38440000,41740000,45740000,50240000,55240000,61240000,68240000,76240000,85240000,98240000,114240000,134240000]


def get_key(length):
    code = string.ascii_letters + string.digits
    result = ''.join(random.choice(code) for i in range(length))
    return result

def update_one_user_data(nick):
    conn = mysql.connect()
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[nick])
    current_player = cursor.fetchone()
    if current_player is None:
            session.pop('username',None)
            return redirect(url_for('login'))

    #new_level = 0
    pointslevel = current_player[7]
    #which = 0
    for level in levels:
        if(pointslevel < level):
            session['tonextlevel'] = level
            #new_level = which
            break
        #which += 1
    #win = player[9]
    #defeat = player[10]
    #pointsranking = (win * 20) - (defeat * 10)
    #if(pointsranking < 0):
    #    pointsranking = 0
    ranking = 0
    cursor.execute("SELECT * FROM players ORDER BY pointsranking DESC")
    players = cursor.fetchall() 
    for player in players:
        if(player[11] > current_player[11]):
            ranking += 1
            continue
        elif(player[11] == current_player[11]):
            if(player[1] != nick):
                ranking += 1
            continue
        break
    cursor.execute("UPDATE players SET ranking = %s WHERE keyplayer =%s",[ranking,nick])
    conn.commit() 
    cursor.close()
     


@app.route('/')
def index():
    if 'username' in session:
        return redirect(url_for('home'))
    now_date = datetime.now()    
    session['playerdate'] = str(now_date)
    session['trylogin'] = 1
    return render_template('guest.html')

@app.route('/login', methods=['POST', 'GET'])
def login():
    if session.get('playerdate') is None and session.get('trylogin') is None:
        now_date = datetime.now()    
        session['playerdate'] = str(now_date)
        session['trylogin'] = 1
    if request.method == "POST":
        now_time = datetime.now()
        if(str(now_time) >= session['playerdate']):
            if(session['trylogin'] == 3):
                session['playerdate'] = str(now_time + timedelta(minutes=5))
                session['trylogin'] = 1
                return render_template('login.html',message="You have to wait 5 mins, before next login")
        if(str(now_time) <= session['playerdate']):
            return render_template('login.html',message="You have to wait 5 mins, before next login")
        conn = mysql.connect()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM players WHERE login =%s",
                       [request.form["login"]])
        myresult = cursor.fetchone()  
        if myresult:
            if bcrypt.check_password_hash(myresult[3],request.form['password']):
                if myresult[14]:
                    session['username'] = myresult[1]
                    code = get_key(24)
                    cursor.execute("SELECT * FROM players WHERE nick = %s",[session["username"]])        
                    myresult3 = cursor.fetchone()
                    cursor.execute("SELECT TO_SECONDS(%s)",[myresult3[15]])
                    to_seconds_vip = cursor.fetchone()
                    cursor.execute("SELECT TO_SECONDS(NOW())")
                    current_time = cursor.fetchone()
                    if(current_time[0] > to_seconds_vip[0]):
                        cursor.execute("UPDATE players SET status = 'Player' WHERE nick = %s",[session['username']])
                        conn.commit()
                    cursor.execute(
                    "SELECT * FROM players WHERE keyplayer =%s", [code])
                    myresult2 = cursor.fetchone()
                    if myresult2:
                        while not myresult2:
                                        code = get_key(24)
                                        cursor.execute("SELECT * FROM players WHERE keyplayer =%s", [code])
                                        myresult2 = cursor.fetchone()
                    cursor.execute("UPDATE players SET keyplayer =%s WHERE nick =%s",[code,session['username']])
                    conn.commit()
                    cursor.execute(
                    "SELECT * FROM players WHERE keyplayer =%s", [code])
                    myresult4 = cursor.fetchone()
                    session['username'] = myresult4[13]
                    print(myresult4[13])
                    cursor.close()
                    update_one_user_data(session['username'])
                    return redirect(url_for('home'))
                else:
                    session['trylogin'] += 1
                    return render_template('login.html',message="You don't confirmed your email yet")
            else:
                cursor.close()
                session['trylogin'] += 1
                return render_template('login.html',message="Invalid username or password")
        cursor.close()
        session['trylogin'] += 1
        return render_template('login.html',message="Invalid username or password")
    return render_template('login.html')

@app.route('/register', methods=['POST','GET'])
def register():
    if request.method == "POST":
        conn = mysql.connect()
        print("here1")
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM players WHERE nick = %s OR email = %s",[request.form["nick"],request.form['email']])
        myresult = cursor.fetchone()

        if not myresult:
            hashpass = bcrypt.generate_password_hash(request.form['password']).decode("utf-8")
            code = get_key(24)
            cursor.execute("SELECT * FROM players WHERE keyplayer =%s",[code])
            myresult2 = cursor.fetchone()
            if myresult2:
                while not myresult2:
                    code = get_key(24)
                    cursor.execute("SELECT * FROM players WHERE keyplayer =%s",[code])
                    myresult2 = cursor.fetchone()
            new_user = (request.form["nick"],request.form["login"],hashpass,request.form["email"],"Player",1,0,0,0,0,0,"static/images/sprites/snake01.png",code,True,False)
            cursor.execute("INSERT INTO players (nick,login,pwd,email,status,level,pointslevel,ranking,win,defeat,pointsranking,snakeskin,keyplayer,confirmedemail,online) \
            VALUES (%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)",new_user)
            conn.commit()
            cursor.close()
            return redirect('home')
            #update_one_user_data(request.form['nick'])
        cursor.close()
        return render_template('register.html',message="That user already exists")
    return render_template('register.html')

@app.route('/home')
def home():
    if 'username' in session:
        conn = mysql.connect()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
        myresult = cursor.fetchone()
        if myresult is None:
            session.pop('username',None)
            return redirect(url_for('login'))
        cursor.close()
        return render_template('home.html',username=myresult[1],player_status=myresult[5],type_choose = "main_home")
    else:
        return redirect(url_for('login'))

#@app.route('/upgrade', methods=['POST','GET'])
#def upgrade():
#    if 'username' in session:
#        conn = mysql.connect()
#        cursor = conn.cursor()
#        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
#        myresult_before = cursor.fetchone()
#        if myresult_before is None:
#            session.pop('username',None)
#            return redirect(url_for('login'))
#        cursor.execute("UPDATE players SET timevip = TIMESTAMPADD(MINUTE,15,current_timestamp) WHERE keyplayer = %s",[session['username']]) 
#        conn.commit()
#        cursor.execute("UPDATE players SET status = 'VIP' WHERE keyplayer = %s",[session['username']])  
#        conn.commit()
#        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
#        myresult = cursor.fetchone()
#        cursor.close()
#        return render_template('home.html',username=myresult[1],player_status=myresult[5],type_choose = "main_home",text = "good")
#    return render_template('login.html')


@app.route('/logout',methods=['GET'])
def logout():
    session.pop('username',None)
    return redirect(url_for('login'))

@app.route('/logo',methods=['GET'])
def logo():
    if 'username' in session:
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

@app.route('/play',methods=['GET'])
def play():
    if 'username' in session:
        conn = mysql.connect()
        cursor = conn.cursor()
        code = get_key(24)
        cursor.execute("SELECT * FROM players WHERE keyplayer =%s", [code])
        myresult2 = cursor.fetchone()
        if myresult2:
            while not myresult2:
                    code = get_key(24)
                    cursor.execute("SELECT * FROM players WHERE keyplayer =%s", [code])
                    myresult2 = cursor.fetchone()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
        myresult = cursor.fetchone()
        if myresult is None:
            session.pop('username',None)
            return redirect(url_for('login'))
        cursor.execute("UPDATE players SET keyplayer =%s WHERE keyplayer =%s",[code,session['username']])
        conn.commit()
        cursor.execute("SELECT * FROM players WHERE keyplayer =%s", [code])
        new_key = cursor.fetchone()
        session['username'] = code
        if new_key[16] == 0:
            cursor.close()
            return render_template("client.html",key=str(code),backURL="/back")
        else: 
            cursor.close()
            return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

@app.route('/back',methods=['GET'])
def back():
    if 'username' in session:
        update_one_user_data(session['username'])
        return redirect(url_for('home'))
    else:
        return redirect(url_for('login'))

@app.route('/statistic',methods=['GET'])
def statistic():
    if 'username' in session:
        conn = mysql.connect()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])        
        myresult = cursor.fetchone()
        if myresult is None:
            session.pop('username',None)
            return redirect(url_for('login'))
        cursor.execute("SELECT TO_SECONDS(%s)",[myresult[15]])
        to_seconds_vip = cursor.fetchone()
        cursor.execute("SELECT TO_SECONDS(NOW())")
        current_time = cursor.fetchone()
        if(current_time[0] > to_seconds_vip[0]):
            cursor.execute("UPDATE players SET status = 'Player' WHERE keyplayer = %s",[session['username']])
            conn.commit()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])        
        send_to_player = []
        myresult2 = cursor.fetchone()
        send_to_player.append(myresult2[6])
        send_to_player.append(myresult2[7])
        send_to_player.append(myresult2[8])
        send_to_player.append(myresult2[9])
        send_to_player.append(myresult2[10])
        send_to_player.append(myresult2[11])
        cursor.close()
        return render_template('home.html',username=myresult2[1],player_status=myresult2[5], \
                               type_choose = "see_statistic",statistic = json.dumps(send_to_player),nextlevel=session['tonextlevel'])
    else:
        return redirect(url_for('login'))

@app.route('/ranking',methods=['GET','POST'])
def ranking():
    if 'username' in session:
        # value = request.args.get('value')
        conn = mysql.connect()
        cursor = conn.cursor()
        z = []
        level_array = []
        ranking_array = []

        cursor.execute("SELECT * FROM players ORDER BY pointslevel DESC LIMIT 100")
        myresult_by_level = cursor.fetchall()
        cursor.execute("SELECT * FROM players ORDER BY pointsranking DESC LIMIT 100")
        myresult_by_ranking_points = cursor.fetchall()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
        myresult = cursor.fetchone()
        if myresult is None:
            session.pop('username',None)
            return redirect(url_for('login'))
        for x in myresult_by_level:
            z.append(x[1])
            z.append(x[6])
            z.append(x[7])
            level_array.append(z)
            z = []
        for x in myresult_by_ranking_points:
            z.append(x[1])
            z.append(x[9])
            z.append(x[10])
            z.append(x[11])
            ranking_array.append(z)
            z = []
        cursor.close()
        return render_template('home.html',username=myresult[1],player_status=myresult[5], \
                               type_choose = "see_ranking",data_table_level_points=json.dumps(level_array), \
                               data_table_ranking_points=json.dumps(ranking_array))
    else:
        return redirect(url_for('login'))

@app.route('/shop',methods=['GET','POST'])
def shop():
    if 'username' in session:
        conn = mysql.connect()
        cursor = conn.cursor()
        cursor.execute("SELECT * FROM players WHERE keyplayer = %s",[session["username"]])
        myresult = cursor.fetchone()
        if myresult is None:
            session.pop('username',None)
            return redirect(url_for('login'))
        if request.method == "POST":
            if request.form['data'] == 'Skin1':
                if myresult[6] >= 1:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake01.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin2':
                if myresult[6] >= 3:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake02.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin3':
                if myresult[6] >= 5:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake03.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin4':
                if myresult[6] >= 7:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake04.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin5':
                if myresult[6] >= 9:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake05.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin6':
                if myresult[6] >= 11:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake06.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin7':
                if myresult[6] >= 13:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake07.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin8':
                if myresult[6] >= 15:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake08.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin9':
                if myresult[6] >= 17:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake09.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin10':
                if myresult[6] >= 19:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake10.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin11':
                if myresult[6] >= 21:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake11.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin12':
                if myresult[6] >= 23:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake12.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin13':
                if myresult[6] >= 25:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake13.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin14':
                if myresult[6] >= 27:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake14.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin15':
                if myresult[6] >= 29:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake15.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin16':
                if myresult[6] >= 31:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake16.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin17':
                if myresult[6] >= 33:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake17.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin18':
                if myresult[6] >= 35:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake18.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin19':
                if myresult[6] >= 37:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake19.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin20':
                if myresult[6] >= 39:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake20.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin21':
                if myresult[6] >= 41:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake21.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin22':
                if myresult[6] >= 43:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake22.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin23':
                if myresult[6] >= 45:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake23.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin24':
                if myresult[6] >= 47:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake24.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin25':
                if myresult[6] >= 49:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake25.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin26':
                if myresult[6] >= 51:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake26.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin27':
                if myresult[6] >= 53:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake27.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin28':
                if myresult[6] >= 55:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake28.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin29':
                if myresult[6] >= 57:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake29.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin30':
                if myresult[6] >= 59:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake30.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin31':
                if myresult[6] >= 61:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake31.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin32':
                if myresult[6] >= 63:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake32.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin33':
                if myresult[6] >= 65:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake33.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin34':
                if myresult[6] >= 67:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake34.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin35':
                if myresult[6] >= 69:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake35.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin36':
                if myresult[6] >= 71:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake36.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin37':
                if myresult[6] >= 73:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake37.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin38':
                if myresult[6] >= 75:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake38.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin39':
                if myresult[6] >= 77:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake39.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin40':
                if myresult[6] >= 79:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake40.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin41':
                if myresult[6] >= 81:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake41.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin42':
                if myresult[6] >= 83:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake42.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin43':
                if myresult[6] >= 85:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake43.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin44':
                if myresult[6] >= 87:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake44.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin45':
                if myresult[6] >= 89:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake45.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin46':
                if myresult[6] >= 91:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake46.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin47':
                if myresult[6] >= 93:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake47.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin48':
                if myresult[6] >= 95:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake48.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin49':
                if myresult[6] >= 97:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake49.png' WHERE keyplayer = %s",[session["username"]])
            elif request.form['data'] == 'Skin50':
                if myresult[6] >= 99:
                    cursor.execute("UPDATE players SET snakeskin = 'static/images/sprites/snake50.png' WHERE keyplayer = %s",[session["username"]])
        conn.commit()
        cursor.close()
        return render_template('home.html',username=myresult[1],player_status=myresult[5],type_choose =  "see_shop",choosed_skin=myresult[12])
    else:
        return redirect(url_for('login'))

@app.route('/guest',methods=['GET','POST'])
def quest():
    if request.method == "POST":
        return render_template('client.html',key = (request.form['nick'] or "Anon"), backURL="/guest")
    else:
        return render_template('guest.html')
#@app.route('/<foldername>/<path:filename>')
#def uploaded_file(foldername,filename):
#    return redirect(url_for('login'))

#if __name__ == '__main__':
#    app.run(debug=False,port=default_app_port())
