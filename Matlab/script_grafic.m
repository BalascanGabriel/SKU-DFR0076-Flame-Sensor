clc
clear all

s = serialport("COM9",57600)

vector=[];
valoare=read(s,1,"uint16")
while true
    valoare=read(s,1,"uint16")
    vector(end+1)=valoare;
    h=area(vector)
    grid on
    set(h(1),'FaceColor',[1 0 0])
    drawnow;
end