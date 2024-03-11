% Datos de distancia
datos = [88 89 92 91 100 97 110 107 116 114 117 115 111 108 117 114 111 108 98 100 100 97 95 89 84 82 81 77 76 75 70 76 75 75 75 71 74 76 77 79 82 84 90 93 97 99 104 110 109 122 130 129 141 137 135 135 131 126 123 116 86];

% Ángulos desde 0 hasta 180 grados avanzando de 3 en 3
angulos = 0:3:180;

% Convertir ángulos a radianes
angulos_rad = deg2rad(angulos);

% Graficar en coordenadas polares
polarplot(angulos_rad, datos, 'o-');
title('Graficador de objetos 2D');
