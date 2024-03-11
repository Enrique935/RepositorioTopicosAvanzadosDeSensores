# Importar los módulos necesarios
import tkinter as tk
from tkinter import ttk
import serial
from serial.tools import list_ports
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Crear una ventana con Tkinter
window = tk.Tk()
window.title("PythonSerial By Rendón Industries")
window.geometry("500x300")

# Crear una etiqueta para mostrar el puerto seleccionado
label = tk.Label(window, text="Puerto:")
label.pack()

# Crear una lista desplegable para elegir el puerto
ports = list_ports.comports()
port_names = [p.device for p in ports]
combo = ttk.Combobox(window, values=port_names)
combo.pack()

# Crear un widget Text para mostrar la lectura serial
text = tk.Text(window, height=10, width=40)
text.pack()

# Crear una variable global para el puerto serial
ser = None

# Crear una lista para almacenar los datos de lectura serial
data_list = []

# Crear una función para conectar al puerto y leer el serial
def connect():
    global ser
    port = combo.get()
    if port:
        try:
            if ser is None:
                ser = serial.Serial(port, 9600)
            data = ser.readline().decode('utf-8').rstrip()
            print(data)
            with open("lectura_serial.txt", "a") as file:
                file.write(data + "\n")
            try:
                numeric_data = float(data)
                data_list.append(numeric_data)
            except ValueError:
                print("Dato no es numérico")
            return data
        except Exception as e:
            print(e)
            return "Error al leer el serial"
    else:
        print("Por favor, elige un puerto")
        return ""

# Crear una función para actualizar el widget Text con la lectura serial
def update_text():
    data = connect()
    text.delete(1.0, tk.END)
    text.insert(tk.END, data)
    window.after(100, update_text)

# Crear una función para graficar los datos
def plot_data():
    if data_list:  # Verificar si hay datos para graficar
        plt.figure('Lectura Serial')
        plt.plot(data_list, '-o', label='Datos')
        plt.title('Gráfico de Lectura Serial')
        plt.xlabel('Muestras')
        plt.ylabel('Valor')
        plt.legend()
        plt.show()
    else:
        print("No hay datos para graficar.")

# Crear un botón para iniciar la actualización del widget Text
button = tk.Button(window, text="Iniciar", command=update_text)
button.pack()

# Crear un botón para graficar los datos
plot_button = tk.Button(window, text="Graficar", command=plot_data)
plot_button.pack()

# Crear un botón para salir del programa
exit_button = tk.Button(window, text="Salir", command=window.destroy)
exit_button.pack()

# Iniciar el bucle principal de la ventana
window.mainloop()
