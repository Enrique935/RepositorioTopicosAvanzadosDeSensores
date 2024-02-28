# Especifica el nombre de tu archivo
nombre_archivo = 'Muestreo5horas.txt'

# Leer todas las líneas del archivo y eliminar líneas vacías o que contienen solo espacios
with open(nombre_archivo, 'r') as file:
    lineas = [linea.strip() for linea in file.readlines() if linea.strip()]

# Inicializar listas para almacenar latitudes y longitudes
latitudes = []
longitudes = []

# Iterar sobre las líneas del archivo y separar latitudes y longitudes
for i in range(0, len(lineas), 2):  # Incrementar de 2 en 2 para tomar las latitudes
    latitud = float(lineas[i])
    longitud = float(lineas[i + 1])

    # Agregar las coordenadas a las listas
    latitudes.append(latitud)
    longitudes.append(longitud)

# Calcular el promedio de latitudes y longitudes
cantidad_coordenadas = len(latitudes)

if latitudes and longitudes:  # Verificar que haya datos antes de calcular el promedio
    promedio_latitudes = sum(latitudes) / cantidad_coordenadas
    promedio_longitudes = sum(longitudes) / cantidad_coordenadas

    # Imprimir los resultados
    print(f"Cantidad de Coordenadas: {cantidad_coordenadas}")
    print(f"Promedio de Latitudes: {promedio_latitudes}")
    print(f"Promedio de Longitudes: {promedio_longitudes}")
else:
    print("No hay datos válidos para calcular el promedio.")
