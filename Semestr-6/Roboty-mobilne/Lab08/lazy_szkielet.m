clc; clear; close all;

%% [1] Mapa i przeszkody (student sam je definiuje)
map = binaryOccupancyMap(500, 500, 1);

obstacles = {
    [0 140], [280 300];
    [360 380], [0 60];
    [340 500], [280 300];
    [360 380], [360 500];
    [110 430], [135 155];
    [260 280], [155 390];
};

figure; hold on;
axis([0 500 0 500]); axis square;
title('Lazy PRM – Twoja mapa'); xlabel('X'); ylabel('Y');

for i = 1:size(obstacles, 1)
    xRange = obstacles{i,1}(1):obstacles{i,1}(2)-1;
    yRange = obstacles{i,2}(1):obstacles{i,2}(2)-1;
    [X, Y] = meshgrid(xRange, yRange);
    XY = [X(:), Y(:)];
    setOccupancy(map, XY, ones(size(XY,1),1));
    fill(obstacles{i,1}([1 2 2 1]), obstacles{i,2}([1 1 2 2]), 'r');
end

inflate(map, 1);

%% [2] Start i cel
start = [50 50];
goal = [450 450];

if getOccupancy(map, start) > 0 || getOccupancy(map, goal) > 0
    error('Start lub cel znajduje się w przeszkodzie!');
end

%% [3] Planer Lazy PRM
prm = mobileRobotPRM(map, 150);
prm.ConnectionDistance = 20;

path = findpath(prm, start, goal);

attempts = 0;
while isempty(path) && attempts < 5
    prm.NumNodes = prm.NumNodes + 50;
    prm.ConnectionDistance = prm.ConnectionDistance + 10;
    update(prm);
    path = findpath(prm, start, goal);
    attempts = attempts + 1;
end

%% [4] Rysowanie
show(prm); hold on;

if ~isempty(path)
    plot(path(:,1), path(:,2), 'b-', 'LineWidth', 2);
    plot(start(1), start(2), 'go', 'MarkerSize', 10, 'LineWidth', 2);
    plot(goal(1), goal(2), 'gx', 'MarkerSize', 10, 'LineWidth', 2);
    legend('Lazy PRM','Ścieżka','Start','Cel');
else
    disp('Lazy PRM nie znalazł ścieżki.');
end

% Obliczanie ścieżki
totalDistance = 0;
for i = 1:size(path,1)-1
    dx = path(i+1,1) - path(i,1);
    dy = path(i+1,2) - path(i,2);
    segmentLength = sqrt(dx^2 + dy^2);
    totalDistance = totalDistance + segmentLength;
end

% Wyświetlanie
distanceText = sprintf('Długość ścieżki: %.2f mm', totalDistance);
text(10, 490, distanceText, 'FontSize', 12, 'BackgroundColor', 'white', 'EdgeColor', 'black');
