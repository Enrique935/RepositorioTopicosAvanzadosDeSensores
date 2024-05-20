# Importar los módulos tkinter y ttk para la interfaz gráfica
import tkinter as tk
import serial, time
from tkinter import ttk

# Importar el módulo pyserial para la comunicación serial
from serial.tools import list_ports

# Crear una ventana con Tkinter
window = tk.Tk()
window.title("PythonSerial By Rendón Industries") # Agregar el título de la ventana
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

# Crear una función para conectar al puerto y leer el serial
def connect():
    global ser # Usar la variable global
    port = combo.get()
    if port:
        try:
            # Abrir el puerto solo si no está abierto
            if ser is None:
                ser = serial.Serial(port, 9600)
            # Leer una línea del serial y decodificarla
            data = ser.readline().decode('utf-8')
            # Mostrar la lectura en la consola
            print(data)
            # Abrir el archivo de texto en modo de agregar
            file = open("lectura_serial.txt", "a")
            # Escribir la lectura serial en el archivo de texto
            file.write(data + "\n")
            # Cerrar el archivo de texto
            file.close()
            # Devolver la lectura
            return data
        except Exception as e:
            # Mostrar el error en la consola
            print(e)
            # Devolver un mensaje de error
            return "Error al leer el serial"
    else:
        # Mostrar un mensaje si no se seleccionó ningún puerto
        print("Por favor, elige un puerto")
        # Devolver un mensaje vacío
        return ""

# Crear una función para actualizar el widget Text con la lectura serial
def update_text():
    # Obtener la lectura serial
    data = connect()
    # Borrar el contenido anterior del widget Text
    text.delete(1.0, tk.END)
    # Insertar la lectura serial en el widget Text
    text.insert(tk.END, data)
    # Llamar a esta función cada 100 milisegundos
    window.after(100, update_text)

# Crear un botón para iniciar la actualización del widget Text
button = tk.Button(window, text="Iniciar", command=update_text)
button.pack()

# Crear un botón para salir del programa
exit_button = tk.Button(window, text="Salir", command=window.destroy)
exit_button.pack()

# Iniciar el bucle principal de la ventana
window.mainloop()
