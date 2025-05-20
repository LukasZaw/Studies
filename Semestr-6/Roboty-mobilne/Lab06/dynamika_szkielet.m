%% ============================
%% TU JEST TWÓJ PLIK Z KINEMATYKI – ETAP 1
%% ============================
% Generuje: eta_ref i zeta_ref
% Użyj tych danych jako trajektorii referencyjnej dla dynamiki

clear all; clc; close all;

%% Parametry symulacji
% (pozostają jak w oryginale)
dt = 0.1;
ts = 50;
t = 0:dt:ts;

% ... (pozostała część kinematyki bez zmian)

%% ============================
%% ETAP 2: DYNAMIKA – SZKIELET DO UZUPEŁNIENIA
%% ============================

% Parametry fizyczne robota
m = 10;
J = 5;
kv = 0;
kr = 0;

% Parametry regulatora P
Kp_v = 2;
Kp_r = 3;

% Inicjalizacja zmiennych
v = 0;
r = 0;
eta_dyn(:,1) = eta_ref(:,1);

for i = 1:length(t)
    psi = eta_dyn(3,i);
    J_psi = [cos(psi), -sin(psi), 0;
             sin(psi),  cos(psi), 0;
                  0,         0,  1];

    u_ref = zeta_ref(1,i);
    r_ref = zeta_ref(3,i);

    % === TODO: zaimplementuj regulator P ===
    % F_cmd = ...
    % T_cmd = ...

    % === TODO: dodaj opory ruchu (kv, kr) ===
    % F = ...
    % T = ...

    % === TODO: oblicz przyspieszenia i integruj ===
    % a_v = ...
    % a_r = ...

    % v = ...
    % r = ...

    % zeta_dyn(:,i) = ...
    % eta_dot_dyn = ...
    % eta_dyn(:,i+1) = ...
end

%% Porównanie trajektorii
figure;
plot(eta_ref(1,:), eta_ref(2,:), 'k--'); hold on;
plot(eta_dyn(1,:), eta_dyn(2,:), 'b');
legend('Trajektoria referencyjna','Trajektoria dynamiczna');
title('Porównanie torów ruchu');
xlabel('x [m]'); ylabel('y [m]'); axis equal; grid on;