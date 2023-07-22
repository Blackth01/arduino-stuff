import tkinter as tk
import threading
import serial
import time

from pygame import mixer

SERIAL_PORT = '/dev/ttyACM0'
BAUD_RATE = 9600

# Images file paths
IMAGE_FILE_NORMAL = 'assets/normal_img.png'
IMAGE_FILE_SCARY = 'assets/scary_img.png'

# Creating main window
window = tk.Tk()

# Creating a canvas to display the background image
canvas = tk.Canvas(window, width=window.winfo_screenwidth(), height=window.winfo_screenheight())
canvas.pack()

# Loading the images
image_normal = tk.PhotoImage(file=IMAGE_FILE_NORMAL)
image_scary = tk.PhotoImage(file=IMAGE_FILE_SCARY)

current_image = canvas.create_image(0, 0, anchor=tk.NW, image=image_normal)

mixer.init()

arduino = serial.Serial(SERIAL_PORT, BAUD_RATE)

print("Waiting 5 seconds to connect to arduino serial port")

# Waiting some seconds in order for the serial to connect
time.sleep(5)

current_mode = "NOT_SCARY"

def change_image(arduino, canvas, current_image, current_mode):

    while True:
        arduino_input = arduino.read().decode()

        if arduino_input == 'S':
            if current_mode == "NOT_SCARY":
                mixer.music.load("assets/scary_sound.mp3")
                mixer.music.play()
                canvas.itemconfig(current_image, image=image_scary)
                current_mode = "SCARY"
        elif arduino_input == 'N':
            if current_mode == "SCARY":
                mixer.music.stop()
                canvas.itemconfig(current_image, image=image_normal)
                current_mode = "NOT_SCARY"
        else:
            print(f"Invalid input: {arduino_input}.")
        time.sleep(0.1)

change_img_thread = threading.Thread(target=change_image, args=(arduino, canvas, current_image, current_mode))
change_img_thread.daemon = True  # Thread will be terminated when the main program ends
change_img_thread.start()

window.mainloop()
