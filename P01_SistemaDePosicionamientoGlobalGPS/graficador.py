# Lee las coordenadas del archivo eliminando líneas en blanco
with open('Sondeo.txt', 'r') as file:
    lines = [line.strip() for line in file if line.strip()]

# Reescribe los datos en un nuevo archivo
with open('Coordenadas.txt', 'w') as output_file:
    for line in lines:
        output_file.write(f"{line}\n")

print("Datos reescritos en 'Coordenadas.txt'.")

# Lee las coordenadas del archivo eliminando líneas en blanco
with open('Coordenadas.txt', 'r') as file:
    lines = [line.strip() for line in file if line.strip()]

# Reescribe los datos en un nuevo archivo con el formato especificado para coordenadas
with open('GoogleEarth.csv', 'w') as output_file:
    for i in range(0, len(lines), 2):
        latitud = lines[i]
        longitud = lines[i + 1]

        # Formatear la salida con espacio después del segundo caracter
        formatted_output = f"{i // 2 + 1},{latitud[:2]} {latitud[2:]},-{longitud[:3]} {longitud[3:]}"

        output_file.write(formatted_output + '\n')

print("Datos reescritos en 'GoogleEarth.csv'.")
