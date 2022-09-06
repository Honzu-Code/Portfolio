import mysql.connector


db = mysql.connector.connect(
    host="localhost",
    user="root",
    passwd="qOw3JuP302X6H2wXmj$",
    database="snakes"
)

mycursor = db.cursor()

mycursor.execute("SELECT TO_SECONDS(NOW())")

current_time = mycursor.fetchone()

mycursor.execute("SELECT * from players WHERE confirmedemail = 0")

unconfirmedusers = mycursor.fetchall()

if not unconfirmedusers:
    print("No Users to delete")
else:
    how_much = len(unconfirmedusers)
    for x in range(how_much):
        mycursor.execute("SELECT TO_SECONDS(%s)",[unconfirmedusers[x][15]])
        time_unconfirmed_users = mycursor.fetchone()
        if current_time[0] > time_unconfirmed_users[0] + 10800:
            mycursor.execute("DELETE FROM players WHERE id = %s",[unconfirmedusers[x][0]])
            db.commit()
