% Wczytanie danych z pliku CSV
dataTable = readtable('acceldata1.csv');

% Wyodrębnienie kolumn z danymi z akcelerometru
Accel_X = dataTable.Accel_x;
Accel_Y = dataTable.Accel_y;
Accel_Z = dataTable.Accel_z;

% Ustawienie częstotliwości próbkowania (w Hz)
fs = 100;  % Przykład: 100 Hz

% Obliczenie osi czasu w sekundach
n = length(Accel_X);  % Liczba próbek
timeInSeconds = (0:n-1) / fs;  % Oś czasu w sekundach

% Definicja parametrów kalibracji (zgodnych z implementacją w C)
calibrationMatrix = [
    0.9997, 0.0036, -0.0129;
   -0.0049, 1.0065, -0.0174;
   -0.0112, 0.0061, 1.0039
];
bias = [0.3255, 0.0559, 0.1460];  % Wektor przesunięć

% Kalibracja danych z akcelerometru
calibratedData = zeros(length(Accel_X), 3);
for i = 1:length(Accel_X)
    % Odczyt surowych danych
    rawData = [Accel_X(i); Accel_Y(i); Accel_Z(i)];
    
    % Korekcja danych: (rawData - bias) * calibrationMatrix
    correctedData = calibrationMatrix * (rawData - bias');
    
    % Zapisanie skorygowanych danych
    calibratedData(i, :) = correctedData';
end

% Rozdzielenie skorygowanych danych
Calibrated_Accel_X = calibratedData(:, 1);
Calibrated_Accel_Y = calibratedData(:, 2);
Calibrated_Accel_Z = calibratedData(:, 3);

% --------------------- Dobór współczynnika alpha dla filtracji akcelerometru -------------------------

% Wybór częstotliwości odcięcia (dostosuj do swojej aplikacji)
fc = 1;  % Przykład: 1 Hz, można zmieniać w zależności od potrzeb

% Obliczenie współczynnika alpha
alpha = (2 * pi * fc) / (2 * pi * fc + fs);
disp(['Współczynnik alpha: ', num2str(alpha)]);

% Filtracja dolnoprzepustowa danych z akcelerometru (po kalibracji)
% Inicjalizacja przefiltrowanych danych
Filtered_Accel_X = zeros(size(Calibrated_Accel_X));
Filtered_Accel_Y = zeros(size(Calibrated_Accel_Y));
Filtered_Accel_Z = zeros(size(Calibrated_Accel_Z));

% Wstępne wartości początkowe
Filtered_Accel_X(1) = Calibrated_Accel_X(1);
Filtered_Accel_Y(1) = Calibrated_Accel_Y(1);
Filtered_Accel_Z(1) = Calibrated_Accel_Z(1);

% Stosowanie filtru dolnoprzepustowego do każdej osi
for i = 2:length(Calibrated_Accel_X)
    Filtered_Accel_X(i) = alpha * Calibrated_Accel_X(i) + (1 - alpha) * Filtered_Accel_X(i - 1);
    Filtered_Accel_Y(i) = alpha * Calibrated_Accel_Y(i) + (1 - alpha) * Filtered_Accel_Y(i - 1);
    Filtered_Accel_Z(i) = alpha * Calibrated_Accel_Z(i) + (1 - alpha) * Filtered_Accel_Z(i - 1);
end

% --------------------- Wizualizacja danych -------------------------

% Ustawienie grubości linii i wielkości legendy
lineWidth = 2;  % Przykładowa grubość linii
legendFontSize = 20;  % Przykładowa wielkość czcionki legendy

% Wykres dla osi X w osobnym oknie
figure;
plot(timeInSeconds, Accel_X, 'r-', 'LineWidth', lineWidth, 'DisplayName', 'Surowe dane');
hold on;
plot(timeInSeconds, Calibrated_Accel_X, 'g-', 'LineWidth', lineWidth, 'DisplayName', 'Po kalibracji');
plot(timeInSeconds, Filtered_Accel_X, 'b-', 'LineWidth', lineWidth, 'DisplayName', 'Po filtracji');
xlabel('Czas (s)');
ylabel('Accel X (m/s^2)');
title('Porównanie - Accel X');
legendObj = legend;
set(legendObj, 'FontSize', legendFontSize);  % Zmiana wielkości czcionki legendy
grid on;

% Wykres dla osi Y w osobnym oknie
figure;
plot(timeInSeconds, Accel_Y, 'r-', 'LineWidth', lineWidth, 'DisplayName', 'Surowe dane');
hold on;
plot(timeInSeconds, Calibrated_Accel_Y, 'g-', 'LineWidth', lineWidth, 'DisplayName', 'Po kalibracji');
plot(timeInSeconds, Filtered_Accel_Y, 'b-', 'LineWidth', lineWidth, 'DisplayName', 'Po filtracji');
xlabel('Czas (s)');
ylabel('Accel Y (m/s^2)');
title('Porównanie - Accel Y');
legendObj = legend;
set(legendObj, 'FontSize', legendFontSize);  % Zmiana wielkości czcionki legendy
grid on;

% Wykres dla osi Z w osobnym oknie
figure;
plot(timeInSeconds, Accel_Z, 'r-', 'LineWidth', lineWidth, 'DisplayName', 'Surowe dane');
hold on;
plot(timeInSeconds, Calibrated_Accel_Z, 'g-', 'LineWidth', lineWidth, 'DisplayName', 'Po kalibracji');
plot(timeInSeconds, Filtered_Accel_Z, 'b-', 'LineWidth', lineWidth, 'DisplayName', 'Po filtracji');
xlabel('Czas (s)');
ylabel('Accel Z (m/s^2)');
title('Porównanie - Accel Z');
legendObj = legend;
set(legendObj, 'FontSize', legendFontSize);  % Zmiana wielkości czcionki legendy
grid on;
