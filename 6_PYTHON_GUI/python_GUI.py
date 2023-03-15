# -*- coding: utf-8 -*-
"""
Created on Thu Mar  2 11:21:18 2023

@author: Kyunglok Baik
"""

from tkinter import * 
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
import tkinter as tk
import serial
import matplotlib.pyplot as plt

curr_duty_cycle=0
window = Tk()
  
window.title('Module 6 GUI Kyunglok Baik')
  
window.geometry("1500x500")
frame1 = Frame(window)
frame1.pack()
frame2 = Frame(window)
frame2.pack(side=BOTTOM)
frame3 = Frame(window)
frame3.pack(side=BOTTOM)

def plot(status=curr_duty_cycle):
    resistor=10000
    voltage_photocell = []
    current_photocell = []
    resistance_photocell = []
    arduino = serial.Serial('COM4',9600, timeout=3)
    arduino.reset_output_buffer()
    arduino.reset_input_buffer()
    
  
    fig = Figure(figsize = (10, 5), dpi = 100)
    
    # adding the subplot
    plot1 = fig.add_subplot(131)
    plot1.set_title("Photocell current versus\n duty cycle")
    plot1.set_xlabel("Duty Cycle (%)")
    plot1.set_ylabel("Current (mA)")
    
    plot2 = fig.add_subplot(132)
    plot2.set_title("Photocell voltage versus\n duty cycle")
    plot2.set_xlabel("Duty Cycle (%)")
    plot2.set_ylabel("Voltage (V)")
    
    plot3 = fig.add_subplot(133) 
    plot3.set_title("Photocell resistance versus\n duty cycle")
    plot3.set_xlabel("Duty Cycle (%)")
    plot3.set_ylabel("Resistance (KΩ)")
    fig.tight_layout(pad=1.0)
    canvas = FigureCanvasTkAgg(fig, master = window)  
    
    for duty_cycle in range(1,101): # 1% increment
        duty_cycle_status.config(text=str(duty_cycle))
        readval = arduino.readline().decode("utf-8").strip()
        try:
            if(readval[0]=='D'):
                v_total_photo = 0 
                cnt = 0
                for trial in range(0,25):
                    v_photo = float(arduino.readline().decode("utf-8").strip())
                    v_total_photo += v_photo
                    cnt += 1
                v_measured = round(v_total_photo/cnt,4)
                i_measured = round((5-v_measured)/resistor*1000,8) # mA adjusted
                r_measured = round((5*resistor/v_measured-10000)/1000,4) # Kilo ohms adjusted
                voltage_photocell.append(v_measured)
                current_photocell.append(i_measured)
                resistance_photocell.append(r_measured)
                print("Cycle: %2d | Voltage: %.2f | Current: %.8f | Resistance: %.2f" % (duty_cycle, v_measured, i_measured, r_measured))
                plot1.plot(range(len(current_photocell)),current_photocell)
                plot2.plot(range(len(voltage_photocell)),voltage_photocell)
                plot3.plot(range(len(resistance_photocell)),resistance_photocell)
                canvas.draw()
                canvas.flush_events()
                canvas.get_tk_widget().pack(side=BOTTOM)
                toolbar = NavigationToolbar2Tk(canvas,window)
                toolbar.update()
                canvas.get_tk_widget().pack(side=BOTTOM)
        except:
            pass
    arduino.close()
  
  
start_button = Button(master = frame1, text = "Start", command = plot, height = 2, width = 20)
start_button.pack(padx=5, pady=10, side=LEFT)
duty_cycle_text = Label(master = frame1, text="Current Duty Cycle (%): ")
duty_cycle_text.pack(padx=5, pady=20, side=LEFT)
duty_cycle_status = Label(master = frame1)
duty_cycle_status.pack(padx=5, pady=20, side=LEFT)


window.mainloop()