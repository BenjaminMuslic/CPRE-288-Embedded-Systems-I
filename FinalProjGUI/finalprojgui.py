'%matplotlib inline'
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Button
import serial.tools.list_ports as COMs
import socket
import tkinter as tk

def socket_connection():
    host = '192.168.1.1'
    port = 288
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((host, port))
    return sock

sock = socket_connection()

def get_screen_resolution():
    root = tk.Tk()
    root.withdraw()  # Hide the Tkinter root window
    screen_width = root.winfo_screenwidth()
    screen_height = root.winfo_screenheight()
    return screen_width, screen_height

fig = plt.figure(facecolor='k')
win = fig.canvas.manager.window
screen_res = get_screen_resolution()
dpi = 150.0
fig.set_dpi(dpi)

ax = fig.add_subplot(111, polar=True, facecolor='#006d70')
ax.set_position([-0.05, -0.05, 1.1, 1.05])

r_max = 100.0
ax.set_ylim([0.0, r_max])
ax.set_xlim([0.0, np.pi])
ax.tick_params(axis='both', colors='w')
ax.grid(color='w', alpha=0.5)
ax.set_rticks(np.linspace(0.0, r_max, 5))
ax.set_thetagrids(np.linspace(0.0, 180.0, 10))

angles = np.arange(0, 181, 1)
theta = angles * (np.pi / 180.0)
dists = np.ones((len(angles),)) * r_max

pols, = ax.plot(theta, dists, linestyle='', marker='o', markerfacecolor='w',
                markeredgecolor='#EFEFEF', markeredgewidth=1.0,
                markersize=10.0, alpha=0.9)
line1, = ax.plot(theta, dists, color='w', linewidth=4.0)

fig.set_size_inches(0.96 * (screen_res[0] / dpi), 0.96 * (screen_res[1] / dpi))
plot_res = fig.get_window_extent().bounds
win.geometry('+{0:1.0f}+{1:1.0f}'.format((screen_res[0] / 2.0) - (plot_res[2] / 2.0),
                                            (screen_res[1] / 2.0) - (plot_res[3] / 2.0)))

fig.canvas.toolbar.pack_forget()
win.wm_title('Arduino Radar')

fig.canvas.draw()
axbackground = fig.canvas.copy_from_bbox(ax.bbox)

def stop_event(event):
    global stop_bool
    stop_bool = 1

prog_stop_ax = fig.add_axes([0.85, 0.025, 0.125, 0.05])
pstop = Button(prog_stop_ax, 'Stop Program', color='#FCFCFC', hovercolor='w')
pstop.on_clicked(stop_event)

def close_event(event):
    global stop_bool, close_bool
    if stop_bool:
        plt.close('all')
    stop_bool = 1
    close_bool = 1

close_ax = fig.add_axes([0.025, 0.025, 0.125, 0.05])
close_but = Button(close_ax, 'Close Plot', color='#FCFCFC', hovercolor='w')
close_but.on_clicked(close_event)

plt.ion()
fig.canvas.draw()
axbackground = fig.canvas.copy_from_bbox(ax.bbox)

data = ','.join(['100'] * 181)

stop_bool = False
close_bool = False
sock_file = sock.makefile()

while True:
    try:
        if stop_bool or close_bool:
            break
        data_received = sock_file.readline().strip()
        if data_received:
            data = data_received

        dists = np.array(data.split(','), dtype=float)
        if len(dists) == len(theta):
            pols.set_data(theta, dists)
            line1.set_data(theta, dists)

        fig.canvas.restore_region(axbackground)
        ax.draw_artist(pols)
        ax.draw_artist(line1)
        fig.canvas.blit(ax.bbox)
        fig.canvas.flush_events()

    except KeyboardInterrupt:
        plt.close('all')
        print('Keyboard Interrupt')
        break

# sock_file.close()
# sock.close()
plt.show()