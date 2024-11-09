% Wczytaj dane z pliku CSV
data = readtable('new_mag1.csv');

% Wydobądź dane magnetometru
magX = data.Mag_x;
magY = data.Mag_y;
magZ = data.Mag_z;

% Oblicz średnie wartości dla każdej osi (bias)
biasX = mean(magX);
biasY = mean(magY);
biasZ = mean(magZ);

% Skoryguj dane magnetometru (hard iron correction)
correctedMagX = magX - biasX;
correctedMagY = magY - biasY;
correctedMagZ = magZ - biasZ;

% Dodaj skorygowane dane do tabeli
data.Corrected_Mag_x = correctedMagX;
data.Corrected_Mag_y = correctedMagY;
data.Corrected_Mag_z = correctedMagZ;

% Zapisz skorygowane dane do nowego pliku CSV
writetable(data, 'skorygowane_dane.csv');

% Wyświetl dane przed i po korekcji na wykresie 3D
figure;

% Wykres danych przed korekcją
subplot(1, 2, 1);
scatter3(magX, magY, magZ, 10, 'b', 'filled');
title('Dane przed korekcją');
xlabel('Mag_x');
ylabel('Mag_y');
zlabel('Mag_z');
grid on;
axis equal;

% Wykres danych po korekcji
subplot(1, 2, 2);
scatter3(correctedMagX, correctedMagY, correctedMagZ, 10, 'r', 'filled');
title('Dane po korekcji');
xlabel('Corrected Mag_x');
ylabel('Corrected Mag_y');
zlabel('Corrected Mag_z');
grid on;
axis equal;

% Wyświetl informację o zakończeniu
disp('Korekcja hard iron zakończona i zapisano dane do "skorygowane_dane.csv".');
