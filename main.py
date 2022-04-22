from flask import Flask, render_template, redirect, url_for
import serial, configparser, time, threading

app = Flask(__name__)
config = configparser.ConfigParser()
config.read("config.ini")
arduino_com = serial.Serial(
    config.get("COM", "PORT"),
    baudrate=config.getint("COM", "BAUDRATE"),
    timeout=config.getfloat("COM", "TIMEOUT")
)
RUNNING = True
selected_option = 2

def sercom():
    while RUNNING:
        arduino_com.write((selected_option).to_bytes(2, 'little'))
        data = arduino_com.read()
        print(data)
        time.sleep(1)

sercom_thread = threading.Thread(target=sercom)
sercom_thread.start()

@app.route("/")
def index():
    return render_template("index.html", selected_option=selected_option)

@app.route("/linear")
def linear():
    global selected_option
    selected_option = 2
    return redirect(url_for("index"))

@app.route("/count")
def count():
    global selected_option
    selected_option = 1
    return redirect(url_for("index"))

@app.route("/block")
def block():
    global selected_option
    selected_option = 3
    return redirect(url_for("index"))

if __name__=="__main__":
    app.run(host="0.0.0.0", port=5000)
    RUNNING = False