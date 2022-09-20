# usename:nguyencuusuu@gmail.com
# pass:56839680Cs
# useId:new1

# Imports
#-------------------------------------------------------------------------------
import pyrebase
import datetime

def Create_data(listdata):
    # data = {"Age": 21, "Name": "Jenna", "Employed": True}
    data = {"Plant1":listdata[0],
            "Plant2":listdata[1],
            "Plant3":listdata[2],
            "Plant4":listdata[3],
    }
    return data
#-------------------------------------------------------------------------------
def Push_data(data):
# Config/setup------------------------------------------------------------------
    firebaseConfig = {
    "apiKey": "AIzaSyBqNIA39bpDpaI2J-3vRnznegxRiuO2alo",
    "authDomain": "new1-b591a.firebaseapp.com",
    "databaseURL": "https://new1-b591a-default-rtdb.firebaseio.com",
    "projectId": "new1-b591a",
    "storageBucket": "new1-b591a.appspot.com",
    "messagingSenderId": "267303177288",
    "appId": "1:267303177288:web:bd28111af230d52011dc7d",
    "measurementId": "G-N260M3SWG4"
    };

    firebase = pyrebase.initialize_app(firebaseConfig)
    db = firebase.database()
# Push data---------------------------------------------------------------------
    db.push(data)
    db.child("Plant").child(datetime.datetime.now().date()).set(data)
    return