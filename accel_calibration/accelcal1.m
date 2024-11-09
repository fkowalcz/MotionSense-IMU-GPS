% Utworzenie macierzy danych, łącząc wszystkie odczyty
% Każdy zestaw danych powinien zawierać wiele próbek dla każdej orientacji.
% Jeśli masz tylko pojedyncze odczyty, po prostu je połącz.

% Dane dla orientacji "X w górę" 
accelDataXUp = [9.4963, -0.0695, 0.0042];

% Dane dla orientacji "Y w górę"
accelDataYUp = [-0.3221, 9.6843, -0.0449];

% Dane dla orientacji "Z w górę"
accelDataZUp = [-0.1844, -0.1251, 9.6549];

% Dane dla orientacji "X w dół"
accelDataXDown = [-10.1309, 0.0020, -0.2455];

% Dane dla orientacji "Y w dół"
accelDataYDown = [-0.4221, -9.8058, -0.3838];

% Dane dla orientacji "Z w dół"
accelDataZDown = [-0.4018, -0.0066, -9.8884];

% Połącz wszystkie dane w jedną macierz
allData = [
    accelDataXUp;
    accelDataXDown;
    accelDataYUp;
    accelDataYDown;
    accelDataZUp;
    accelDataZDown
];

disp('Macierz danych utworzona!');

% Przeprowadzenie kalibracji akcelerometru
[calibrationParams, residuals] = accelcal(allData);

% Wyświetlenie wyników kalibracji
disp('Parametry kalibracji:');
disp(calibrationParams);

% Wyświetlenie błędów resztkowych
disp('Błędy resztkowe:');
disp(residuals);

%--------------------- Dobór współczynnika alpha dla filtracji akcelerometru -------------------------

% Wczytanie danych z pliku CSV
dataTable = readtable('acceldata1.csv');

% Wyodrębnienie kolumn z danymi z akcelerometru
timestamp = dataTable.timestamp;
Accel_X = dataTable.Accel_x;
Accel_Y = dataTable.Accel_y;
Accel_Z = dataTable.Accel_z;

% Częstotliwość próbkowania (ustalona na 100 Hz)
fs = 100;  % 100 Hz

% Wybór częstotliwości odcięcia (dostosuj do swojej aplikacji)
fc = 1;  % Przykład: 5 Hz, można zmieniać w zależności od potrzeb

% Obliczenie współczynnika alpha
alpha = (2 * pi * fc) / (2 * pi * fc + fs);
disp(['Współczynnik alpha: ', num2str(alpha)]);

% Filtracja dolnoprzepustowa danych z akcelerometru
% Inicjalizacja przefiltrowanych danych
Filtered_Accel_X = zeros(size(Accel_X));
Filtered_Accel_Y = zeros(size(Accel_Y));
Filtered_Accel_Z = zeros(size(Accel_Z));

% Wstępne wartości początkowe
Filtered_Accel_X(1) = Accel_X(1);
Filtered_Accel_Y(1) = Accel_Y(1);
Filtered_Accel_Z(1) = Accel_Z(1);

% Stosowanie filtru dolnoprzepustowego do każdej osi
for i = 2:length(Accel_X)
    Filtered_Accel_X(i) = alpha * Accel_X(i) + (1 - alpha) * Filtered_Accel_X(i - 1);
    Filtered_Accel_Y(i) = alpha * Accel_Y(i) + (1 - alpha) * Filtered_Accel_Y(i - 1);
    Filtered_Accel_Z(i) = alpha * Accel_Z(i) + (1 - alpha) * Filtered_Accel_Z(i - 1);
end

% Wykresy porównujące surowe i przefiltrowane dane
figure;

% Wykres dla osi X
subplot(3, 1, 1);
plot(timestamp, Accel_X, 'r-', 'DisplayName', 'Surowe dane');
hold on;
plot(timestamp, Filtered_Accel_X, 'b-', 'DisplayName', 'Przefiltrowane dane');
xlabel('Czas (ms)');
ylabel('Accel X (m/s^2)');
title('Filtracja dolnoprzepustowa - Accel X');
legend;
grid on;

% Wykres dla osi Y
subplot(3, 1, 2);
plot(timestamp, Accel_Y, 'r-', 'DisplayName', 'Surowe dane');
hold on;
plot(timestamp, Filtered_Accel_Y, 'b-', 'DisplayName', 'Przefiltrowane dane');
xlabel('Czas (ms)');
ylabel('Accel Y (m/s^2)');
title('Filtracja dolnoprzepustowa - Accel Y');
legend;
grid on;

% Wykres dla osi Z
subplot(3, 1, 3);
plot(timestamp, Accel_Z, 'r-', 'DisplayName', 'Surowe dane');
hold on;
plot(timestamp, Filtered_Accel_Z, 'b-', 'DisplayName', 'Przefiltrowane dane');
xlabel('Czas (ms)');
ylabel('Accel Z (m/s^2)');
title('Filtracja dolnoprzepustowa - Accel Z');
legend;
grid on;
