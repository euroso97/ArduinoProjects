import serial
import matplotlib.pyplot as plt
import time
import math
import re

time.sleep(1)

res_voltage_photocell = []
res_current_photocell = []
res_resistance_photocell = []

#For 1% increment
duty_cycle = [float(i) for i in range(0,101)]

#For 5 point averaging
#for k in range(21):

def get_data(resistor=10000):
    arduino = serial.Serial('COM4',9600, timeout=3)
    voltage_photocell = []
    current_photocell = []
    resistance_photocell = []
    arduino.reset_output_buffer()
    arduino.reset_input_buffer()
    
    for duty_cycle in range(0,101): # 1% increment
        readval = arduino.readline().decode("utf-8").strip()
        try:
            if(readval[0]=='D'):
                v_total_photo = 0 
                cnt = 0
                for i in range(0,25):
                    v_photo = float(arduino.readline().decode("utf-8").strip())
                    v_total_photo += v_photo
                    cnt += 1
                v_measured = round(v_total_photo/cnt,4)
                i_measured = round((5-v_measured)/resistor,8)
                r_measured = round(5*resistor/v_measured-10000,4)
                voltage_photocell.append(v_measured)
                current_photocell.append(i_measured)
                resistance_photocell.append(r_measured)
                print("Cycle: %2d | Voltage: %.2f | Current: %.8f | Resistance: %.2f" % (duty_cycle, v_measured, i_measured, r_measured))
        except:
            pass
    arduino.close()
    return voltage_photocell, current_photocell, resistance_photocell
    

def plot_moving_sqr(x,y,title,labelx,labely):
    xx=[]
    yy=[i for i in range(5,101,5)]
    for i in range(5,101,5): #5,10,15,20...
        avg_square=0
        for j in range(i-5,i): #0,1,2,3,4
            avg_square+=y[j]
        xx.append(avg_square/5.0)
    plt.plot(yy,xx, marker ='.')
    plt.title(title);
    plt.xlabel(labelx);
    plt.ylabel(labely);
    plt.show()
    
    
res_voltage_photocell, res_current_photocell, res_resistance_photocell = get_data()

res_mA_photocell = [i*1000 for i in res_current_photocell]

plot_moving_sqr(duty_cycle,res_voltage_photocell,'Photocell Voltage v. Duty Cycle 5 slot moving average','Duty cycle (%)','voltage (V)')
plot_moving_sqr(duty_cycle,res_mA_photocell,'Photocell Current v. Duty Cycle 5 slot moving average','Duty cycle (%)','current (mA)')
plot_moving_sqr(duty_cycle,res_resistance_photocell,'Photocell Resistance v. Duty Cycle 5 slot moving average','Duty cycle (%)','Resistance (Ohm)')

