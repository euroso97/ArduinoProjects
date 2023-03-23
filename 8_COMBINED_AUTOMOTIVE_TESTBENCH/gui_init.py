# -*- coding: utf-8 -*-
"""
Created on Thu Mar 16 21:49:19 2023

@author: Kyunglok Baik
"""
from tkinter import * 
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
import tkinter as tk
import serial
import matplotlib.pyplot as plt
import time


arduino = serial.Serial('COM4',9600, timeout=3)
arduino.reset_output_buffer()
arduino.reset_input_buffer()

window = Tk()
window.title('ECE303 Final Project Python GUI')
window.geometry("800x900") # Adjust the resolution here

frame=Frame(window)
frame.pack(side=TOP)

frame_distance = Frame(window)
frame_distance.pack(side=TOP)

frame_power = Frame(window)
frame_power.pack(side=TOP)

text_led_indicators = Label(master=window, text="LED Indicators", bg='white', height = 2, width = 50, font=("Arial", 14))
text_led_indicators.pack(side=TOP)
frame_led = Frame(master=window)
frame_led.pack(side=TOP)
frame_headlight = Frame(master=window)
frame_headlight.pack(side=TOP)

text_temp_indicators = Label(master=window, text="Battary Temperature", bg='white', height = 2, width = 50, font=("Arial", 14))
text_temp_indicators.pack(side=TOP)
frame_temp = Frame(window)
frame_temp.pack(side=TOP)

text_coolant_indicators = Label(master=window, text="Coolant", bg='white', height = 2, width = 50, font=("Arial", 14))
text_coolant_indicators.pack(side=TOP)
frame_coolant = Frame(window)
frame_coolant.pack(side=TOP)

curr_line=""


def on():
    #### READ ####
    bytesToRead = arduino.inWaiting()
    serial_output = str(arduino.read(bytesToRead),'UTF-8').strip()
    #print(serial_output)
    #### PARSE and VERIFY ####
    try:
        params = serial_output.split('\r\n')[0].strip().split(',') # 1:distance, 2:power-level, 3:temp, 4:coolant_warning
        distance=params[0].strip()
        powerlvl=params[1].strip()
        temp=params[2].strip()
        coolwarn=params[3].strip()
        headlight1=params[4].strip()
        headlight2=params[5].strip()
        
        #### UPDATE Config ####
        
        # Update values
        distance_val.config(text=distance)
        power_val.config(text=powerlvl)
        temp_val.config(text=temp)
        
        fdistance=float(distance)
        #print(fdistance)
        
        # Update LEDs
        if(fdistance<30):
            g_led.config(bg='green')
        else:
            g_led.config(bg='white')

        if(fdistance<20):
            y_led.config(bg='yellow')
        else:
            y_led.config(bg='white')
            
        if(fdistance<10):
            r_led.config(bg='red')
        else:
            r_led.config(bg='white')
            
        if(headlight1=='0'):
            head1_led.config(bg='white')
        elif(headlight1=='150'):
            head1_led.config(bg='pink')
        elif(headlight1=='255'):
            head1_led.config(bg='red')
            
        if(headlight2=='0'):
            head2_led.config(bg='white')
        elif(headlight2=='150'):
            head2_led.config(bg='pink')
        elif(headlight2=='255'):
            head2_led.config(bg='red')
        


        # Temperature warning
        if(float(temp)>80):
            temp_low.config(bg='white')
            temp_high.config(bg='red')
        else:
            temp_low.config(bg='green')
            temp_high.config(bg='white')
            
        
        # Coolant Status
        if(coolwarn=='1'):
            cool_low.config(bg='white')
            cool_high.config(bg='red')
        else:
            cool_low.config(bg='green')
            cool_high.config(bg='white')
        

    except:
        pass
    
    
    #### UPDATE GUI 500ms ####
    window.after(300,on)
        

start_button = Button(master = frame, text = "Start", command = on, height = 2, width = 50)
start_button.pack(padx=5, pady=10, side=LEFT)

distance_text = Label(master=frame_distance, text="Distance (cm): ", bg='grey', height = 2, width = 24, font=("Arial", 18))
distance_text.pack(padx=5, pady=20, side=LEFT)
distance_val = Label(master=frame_distance, text="..", bg='grey', height = 2, width = 24, font=("Arial", 18))
distance_val.pack(padx=5, pady=20, side=LEFT)

power_text = Label(master=frame_power, text="Power (%): ", bg='grey', height = 2, width = 24, font=("Arial", 18))
power_text.pack(padx=5, pady=20, side=LEFT)
power_val = Label(master=frame_power, text="..", bg='grey', height = 2, width = 24, font=("Arial", 18))
power_val.pack(padx=5, pady=20, side=LEFT)

g_led=Label(master=frame_led, text='GREEN', borderwidth=1, relief="solid", height = 5, width = 10, font=("Arial", 12))
g_led.pack(padx=30, pady=20, side=LEFT)
y_led=Label(master=frame_led, text='YELLOW', borderwidth=1, relief="solid", height = 5, width = 10, font=("Arial", 12))
y_led.pack(padx=30, pady=20, side=LEFT)
r_led=Label(master=frame_led, text='RED', borderwidth=1, relief="solid", height = 5, width = 10, font=("Arial", 12))
r_led.pack(padx=30, pady=20, side=LEFT)

head1_led=Label(master=frame_headlight, text='HEADLIGHT1', bg="white", borderwidth=1, relief="solid", padx=20, pady=20)
head1_led.pack(pady=20, side=LEFT)
head2_led=Label(master=frame_headlight, text='HEADLIGHT2', bg="white", borderwidth=1, relief="solid", padx=20, pady=20)
head2_led.pack(padx=20, pady=20, side=LEFT)

temp_text = Label(master=frame_temp, text="Temperature (F): ", bg='grey', height = 2, width = 16, font=("Arial", 18))
temp_text.pack(padx=5, pady=20, side=LEFT)
temp_val = Label(master=frame_temp, text="..", bg='grey', height = 2, width = 8, font=("Arial", 18))
temp_val.pack(padx=5, pady=20, side=LEFT)
temp_low = Label(master=frame_temp, text="Good", bg='green', height = 2, width = 12, font=("Arial", 18))
temp_low.pack(side=LEFT)
temp_high = Label(master=frame_temp, text="HIGH", bg='white', height = 2, width = 12, font=("Arial", 18))
temp_high.pack(side=LEFT)

cool_text = Label(master=frame_coolant, text="Coolant Status: ", bg='grey', height = 2, width = 16, font=("Arial", 18))
cool_text.pack(padx=5, pady=20, side=LEFT)
cool_low = Label(master=frame_coolant, text="GOOD", bg='green', height = 2, width = 16, font=("Arial", 18))
cool_low.pack(padx=5, pady=20, side=LEFT)
cool_high = Label(master=frame_coolant, text="LOW WARNING", bg='white', height = 2, width = 16, font=("Arial", 18))
cool_high.pack(padx=5, pady=20, side=LEFT)


window.mainloop()