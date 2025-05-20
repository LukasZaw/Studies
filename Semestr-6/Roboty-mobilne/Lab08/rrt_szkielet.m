clc; clear; close all;

%% [1] Tworzenie mapy z przeszkodami (Twoja mapa)
map = binaryOccupancyMap(500, 500, 1);

% Wprowadź własne przeszkody w formacie [xmin xmax], [ymin ymax]
obstacles = {
    [0 140], [280 300];
    [360 380], [0 60];
    [340 500], [280 300];
    [360 380], [360 500];
    [110 430], [135 155];
    [260 280], [155 390];
};


% Rysowanie i ustawianie przeszkód
figure; hold on;
axis([0 500 0 500]); axis square;
title('RRT – Twoja mapa'); xlabel('X'); ylabel('Y');

for i = 1:size(obstacles, 1)
    xRange = obstacles{i,1}(1):obstacles{i,1}(2)-1;
    yRange = obstacles{i,2}(1):obstacles{i,2}(2)-1;
    [X, Y] = meshgrid(xRange, yRange);
    XY = [X(:), Y(:)];
    setOccupancy(map, XY, ones(size(XY,1),1));
    fill(obstacles{i,1}([1 2 2 1]), obstacles{i,2}([1 1 2 2]), 'r');
end

inflate(map, 1);  % zwiększenie "grubości" przeszkód (opcjonalnie)

%% [2] Start i cel
start = [50 50];
goal = [450 450];

if getOccupancy(map, start) > 0 || getOccupancy(map, goal) > 0
    error('Start lub cel znajduje się w przeszkodzie!');
end

%% [3] Tworzenie planera RRT
stateSpace = stateSpaceSE2;
stateSpace.StateBounds = [0 500; 0 500; -pi pi];

validator = validatorOccupancyMap(stateSpace);
validator.Map = map;
validator.ValidationDistance = 1;

planner = plannerRRT(stateSpace, validator);
planner.MaxConnectionDistance = 10;
planner.MaxIterations = 3000;

%% [4] Planowanie ścieżki
pathObj = plan(planner, [start 0], [goal 0]);

%% [5] Rysowanie wyniku
if ~isempty(pathObj)
    pathStates = pathObj.States;
    hPath = plot(pathStates(:,1), pathStates(:,2), 'b-', 'LineWidth', 2);
    hStart = plot(start(1), start(2), 'go', 'MarkerSize', 10, 'LineWidth', 2);
    hGoal = plot(goal(1), goal(2), 'gx', 'MarkerSize', 10, 'LineWidth', 2);
    hObs = fill([-10 -10 -9 -9], [-10 -9 -9 -10], 'r');

    legend([hObs, hPath, hStart, hGoal], {'Przeszkody','Ścieżka RRT','Start','Cel'});
else
    disp('RRT nie znalazł ścieżki.');
end

% Obliczanie długości ścieżki
totalDistance = 0;
for i = 1:size(pathStates,1)-1
    dx = pathStates(i+1,1) - pathStates(i,1);
    dy = pathStates(i+1,2) - pathStates(i,2);
    segmentLength = sqrt(dx^2 + dy^2);
    totalDistance = totalDistance + segmentLength;
end

% Wyświetlanie długości ścieżki na wykresie
distanceText = sprintf('Długość ścieżki: %.2f mm', totalDistance);
text(10, 490, distanceText, 'FontSize', 10, 'BackgroundColor', 'white', 'EdgeColor', 'black');
