%% --- Automation Addicted #2 ---

%   Kalman Filter: implementation on Arduino UNO board
%   Author: Alessandro D'Alio
%   YouTube: Automation Addicted
%   "Follow me and subscribe to my channel for more videos!"


clc
clear all;
global a;

% ricerca della porta COM per Arduino
if ~isempty(instrfind)
    fclose(instrfind);
    delete(instrfind);
end

% creazione oggetto Arduino
a=arduino();

% numero di campioni da leggere
samples=600;

% inizializzazione vettore campioni
v = zeros(samples,1);

% lettura da sensore LM35DZ
i=1;
while i <= samples
    v(i) = readVoltage(a,'A0')*100;
    i = i + 1;
end

% calcolo varianza sul rumore di misura R
R = var(v)
