clear

% Записуємо початкові дані
delta_t = 0.01;
T = 5;
t = 0:delta_t:T;
y = load("f14.txt");
N = length(y);

% Будуємо графік спостережень
figure
plot(t,y), grid

% Дискретне перетворення Фур'є за початковими даними
fourier_func = zeros(1,N);
for m = 1:N
    for j = 1:N
        fourier_func(m) = fourier_func(m) + 1/N*y(j)*exp(1)^(-1i*2*pi/N*m*j);
    end
end

figure
% Знаходимо delta_f і будуємо графік перетворення Фур'є для показу
% екстремумів
delta_f = 1/T;
n = length(t);
plot(abs(fourier_func)),grid
f = 0:delta_f:round(n/2) * delta_f;

figure
plot(f,abs(fourier_func(1:round(n/2)+1)))

% Знаходимо локальні максимуми і частоти
fourier_func=abs(fourier_func);
counter = 0;
extr = zeros(2,1);
for j = 3:round(N/2)-1
    if(fourier_func(j) > fourier_func(j+1) && fourier_func(j) > fourier_func(j-1) && abs(fourier_func(j)-fourier_func(j+1)) > 1)
        counter = counter + 1;
        extr(counter) = j*delta_f
    end
end

% Будуємо та розв'язуємо систему рівнянь, щоб знайти коефіцієнти при
% частотах
f_sin = sin(2*pi*extr(1)*t);

A = [sum(t.^6), sum(t.^5), sum(t.^4), sum(f_sin.*t.^3), sum(t.^3);
     sum(t.^5), sum(t.^4), sum(t.^3), sum(f_sin.*t.^2), sum(t.^2);
     sum(t.^4), sum(t.^3), sum(t.^2), sum(f_sin.*t),    sum(t);
     sum(f_sin.*t.^3), sum(f_sin.*t.^2), sum(f_sin.*t), sum(f_sin.*f_sin), sum(N*f_sin);
     sum(t.^3), sum(t.^2), sum(t), sum(N*f_sin), N];

c = [sum(y.*t.^3), sum(y.*t.^2), sum(y.*t), sum(y.*f_sin),  sum(y)];

a = inv(A)*c'
temp = a'

% Отримана апроксимуюча функція
aprox_f = a(1).*t.^3 + a(2).*t.^2 + a(3).*t + a(4).*f_sin +a(5);

% Графік апроксимуючої функції
figure
plot(t, aprox_f), grid

% Середньоквадратична похибка
error_value = sum((aprox_f-y).^2)