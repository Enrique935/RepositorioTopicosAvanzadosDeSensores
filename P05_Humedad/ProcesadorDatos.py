def eliminar_lineas_en_blanco(nombre_archivo_entrada):
    # Nombre del archivo de salida
    nombre_archivo_salida = nombre_archivo_entrada[:-4] + "_sin_lineas_en_blanco.txt"

    # Abrir el archivo de entrada en modo de lectura
    with open(nombre_archivo_entrada, 'r') as archivo_entrada:
        # Leer todas las líneas del archivo y eliminar las líneas en blanco
        lineas = [linea for linea in archivo_entrada if linea.strip()]

    # Escribir las líneas sin líneas en blanco en el archivo de salida
    with open(nombre_archivo_salida, 'w') as archivo_salida:
        archivo_salida.writelines(lineas)


def separar_datos_por_sensor(nombre_archivo_entrada):
    # Nombre de los archivos de salida para cada sensor
    nombre_archivo_aht20 = "datos_aht20.txt"
    nombre_archivo_dht11 = "datos_dht11.txt"

    # Abrir el archivo de entrada en modo de lectura
    with open(nombre_archivo_entrada, 'r') as archivo_entrada:
        # Leer todas las líneas del archivo
        lineas = archivo_entrada.readlines()

    # Abrir los archivos de salida en modo de escritura
    with open(nombre_archivo_aht20, 'w') as archivo_aht20, open(nombre_archivo_dht11, 'w') as archivo_dht11:
        # Iterar sobre todas las líneas del archivo
        for linea in lineas:
            # Si la línea no está en blanco
            if linea.strip():
                # Separar los datos de la línea
                datos = linea.split('\t')
                sensor = datos[0].split('_')[0]  # Obtener el nombre del sensor

                # Obtener los valores numéricos y escribirlos en el archivo correspondiente según el sensor
                valores = [valor.split(':')[1].strip().split()[0] for valor in datos]
                if sensor == "AHT20":
                    # Eliminar el símbolo % del dato de humedad
                    valores[1] = valores[1].replace('%', '')
                valores = '\t'.join(valores)

                if sensor == "AHT20":
                    archivo_aht20.write(valores + '\n')
                elif sensor == "DHT11":
                    archivo_dht11.write(valores + '\n')


# Nombre del archivo de entrada
nombre_archivo_entrada = "3_Fill_AmbientTemp_&_Vacuum.txt"

# Eliminar las líneas en blanco del archivo de entrada
eliminar_lineas_en_blanco(nombre_archivo_entrada)

# Obtener el nombre del archivo generado sin líneas en blanco
nombre_archivo_sin_lineas_en_blanco = nombre_archivo_entrada[:-4] + "_sin_lineas_en_blanco.txt"

# Separar los datos por sensor en archivos separados
separar_datos_por_sensor(nombre_archivo_sin_lineas_en_blanco)
