%% Kinematyka robota mobilnego
clear all; clc; close all;

%% Parametry symulacji
dt=0.1; % krok ca�kowania
ts=20; % czas symulacji
t=0:dt:ts; % czas symulacji

%% Warunki pocz�tkowe
x0=0;
y0=0;
psi0=0;

eta0=[x0;y0;psi0];

eta(:, 1) = eta0; % przypisanie pocz�tkowych warunk�w

%% Start p�tli

r_trajectory = 1; % promie� okr�gu
center_x = 2; % x �rodek okr�gu
center_y = 2; % y �rodek okr�gu

for i=1:length(t)
    % Nowa trajektoria - ruch po okr�gu
    x_desired = center_x + r_trajectory * cos(0.1 * t(i));
    y_desired = center_y + r_trajectory * sin(0.1 * t(i));
    
    % Wyznaczanie kierunku (orientacji) na trajektorii
    psi = atan2(y_desired - eta(2,i), x_desired - eta(1,i));
    
    % Jakobian macierzy:
    J_psi=[cos(psi),-sin(psi),0;
           sin(psi),cos(psi),0;
           0,0,1];
    
    % Pr�dko�ci
    u = 0.5; % pr�dko�� liniowa w kierunku x
    v = 0.0; % pr�dko�� w kierunku y
    r = 0.2; % pr�dko�� k�towa

    zeta(:,i)=[u;v;r];
    
    eta_dot(:,i) = J_psi*zeta(:,i);
    
    eta(:,i+1) = eta(:,i)+dt*eta_dot(:,i); % metoda Eulera
end

% Wydruk funkcji
figure
plot(t, eta(1,1:i),'r-');
hold on
plot(t, eta(2,1:i),'b-');
hold on
plot(t, eta(3,1:i),'g-');
xlabel('t[s]');
ylabel('x[m], y[m], \psi[rad]');
legend('x','y','\psi'), set(gca,'fontsize',12);

figure
plot(eta(1,1:i), eta(2,1:i));
xlabel('x[m]');
ylabel('y[m]');
set(gca,'fontsize',12);

%% Animacja ruchu robota mobilnego
l=0.6; % d�ugo�� platformy
w=0.4; % szeroko�� platformy

% Wsp�rz�dne opisuj�ce kszta�t platformy
mr_co=[-l/2,l/2,l/2,-l/2,-l/2;
        -w/2,-w/2,w/2,w/2,-w/2];

figure
for i=1:length(t) % pocz�tek animacji
    psi = eta(3,i);
    R_psi = [cos(psi), -sin(psi);
             sin(psi), cos(psi)]; % macierz rotacji
    v_pos = R_psi * mr_co;

    fill(v_pos(1,:) + eta(1,i), v_pos(2,:) + eta(2,i), 'g') % robot
    hold on, grid on; axis([-1 3 -1 3]), axis square

    plot(eta(1,1:i), eta(2,1:i), 'b-'); % �cie�ka ruchu

    legend('MR','Path'), set(gca,'fontsize',12)
    xlabel('x[m]'); ylabel('y[m]');
    pause(0.1);
    hold off
end
